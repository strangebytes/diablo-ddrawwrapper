#pragma comment(linker, "/EXPORT:DirectDrawCreate=_DirectDrawCreate@12")

#include "DirectDrawWrapper.h"
#include "resource.h"
#include "detours.h"
#include <stdio.h>
#include <math.h>

// Main thread ddrawwrapper object
IDirectDrawWrapper *lpDD = NULL;
// Original setcursorpos function pointer
static BOOL (WINAPI *TrueSetCursorPos)(int,int) = SetCursorPos;
static HMODULE (WINAPI *TrueLoadLibraryA)(LPCSTR) = GetModuleHandleA;

// Are we in the settings menu
BOOL inMenu;
// Dll start time
DWORD start_time;
// The level of debug to display
int debugLevel;
//debug display mode (-1 = none, 0 = console, 1 = file)
int debugDisplay;
//the debug file handle
FILE *debugFile;

// Dll hmodule
HMODULE hMod;

/* Helper function for throwing debug/error messages
 *
 * int level      - Debug level
 * char *location - Message location
 * char *message  - Message
 */
void debugMessage(int level, char *location, char *message)
{
	// If above the current level then skip totally
	if(level > debugLevel) return;

    // Calculate HMS
	DWORD cur_time = GetTickCount() - start_time;
	long hours = (long)floor((double)cur_time / (double)3600000.0);
	cur_time -= (hours * 3600000);
	int minutes = (int)floor((double)cur_time / (double)60000.0);
	cur_time -= (minutes * 60000);
	double seconds = (double)cur_time / (double)1000.0;

    // Build error message
	char text[4096] = "\0";
	if(level == 0)
	{
		sprintf_s(text, 4096, "%d:%d:%#.1f ERR %s %s\n", hours, minutes, seconds, location, message);
	}
	else if(level == 1)
	{
		sprintf_s(text, 4096, "%d:%d:%#.1f WRN %s %s\n", hours, minutes, seconds, location, message);
	}
	else if(level == 2)
	{
		sprintf_s(text, 4096, "%d:%d:%#.1f INF %s %s\n", hours, minutes, seconds, location, message);
	}
    // Output and flush
	printf_s(text);
	fflush(stdout);
}

// Override function for cursor position
BOOL WINAPI OverrideSetCursorPos(int X, int Y)
{
	// If ddraw object exists and windowed mode
	if(lpDD != NULL && lpDD->isWindowed)
	{
		// X,Y are relative to client area within the code
		// Get client area location
		POINT cpos;
		cpos.x = 0;
		cpos.y = 0;
		ClientToScreen(lpDD->hWnd, &cpos);

		// Calculate correct cursor offset and move
		BOOL res = TrueSetCursorPos(cpos.x + X, cpos.y + Y);
		return res;
	}
	return TrueSetCursorPos(X, Y);
}

// Override function for load library
/*HMODULE WINAPI OverrideLoadLibraryA(LPCSTR lpModuleName)
{
	printf_s("%s\n", lpModuleName);
	return TrueLoadLibraryA(lpModuleName);
}*/

// Pretty standard winproc
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        // On syskey down
		case WM_SYSKEYDOWN:
			// ALT+ENTER trap keydown
			if (wParam == VK_RETURN)
			{
				return 0;
			}
			break;
        // On syskey up
		case WM_SYSKEYUP:
			// ALT+ENTER trap keyup
			if (wParam == VK_RETURN)
			{
				// If DDW exists
				if(lpDD != NULL)
				{
					lpDD->ToggleFullscreen();
				}
				return 0;
			}
			break;
        // On keydown
		case WM_KEYDOWN:
			// Overload printscreen(save a snapshot of the current screen
			if(wParam == VK_SNAPSHOT)
			{
				return 0;
			}
			// Always pass ~ to menu
			if(wParam == VK_OEM_3)
			{
				return 0;
			}
			// Everything gets passed if we are in the menu
			if(inMenu)
			{
				return 0;
			}
			break;
        // On keyup
		case WM_KEYUP:
			// Overload printscreen(save a snapshot of the current screen)
			if(!inMenu && wParam == VK_SNAPSHOT)
			{
				lpDD->DoSnapshot();
				return 0;
			}
			// Always pass ~ to menu
			if(wParam == VK_OEM_3)
			{
				// Pass to menu and set inMenu to result
				inMenu = lpDD->MenuKey(VK_OEM_3);
				return 0;
			}
			// Everything gets passed if we are in the menu
			if(inMenu)
			{
				// Pass to menu and set inMenu to result
				inMenu = lpDD->MenuKey(wParam);
				return 0;
			}
			break;
        // On destroy window
		case WM_DESTROY:
			// Restore the orignal window proc if we have it
			if(lpDD->lpPrevWndFunc != NULL)
			{
				SetWindowLong(hwnd, GWL_WNDPROC, (LONG)lpDD->lpPrevWndFunc);
			}
			break;
    }
	// Call original windiow proc by default
    return CallWindowProc(lpDD->lpPrevWndFunc, hwnd, message, wParam, lParam);
}

POINT mousePos;

//A thread to bypass windows preventing hooks from modifying mouse position
DWORD WINAPI setMousePosThread(LPVOID lpParam) {
	SetCursorPos(mousePos.x, mousePos.y);
	return 0;
}

LRESULT CALLBACK mouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	POINT p;
	if (GetCursorPos(&p)) {
		if (lpDD != NULL && !lpDD->isWindowed) {
			mousePos.x = min(p.x, 640 - 1);
			mousePos.y = min(p.y, 480 - 1);
		}
		if (mousePos.x != p.x || mousePos.y != p.y) {
			long unsigned int nothing;
			HANDLE threadID = CreateThread(NULL, 0, setMousePosThread, NULL, 0, &nothing);
			CloseHandle(threadID);
		}
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

// Main dll entry
BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	LONG error;

	switch (ul_reason_for_call)
	{
	// Initial process attach
	case DLL_PROCESS_ATTACH:
		// Store module handle
		hMod = hModule;

		// Set default variables
		debugLevel = 0;
   		debugDisplay = -1;

		// Set time start
		start_time = GetTickCount();

		// Not in menu to start
		inMenu = false;
		
        // Retrieve command line arguments
		LPWSTR *szArgList;
		int argCount;
		szArgList = CommandLineToArgvW(GetCommandLine(), &argCount);
		
        // If arguments
        if(szArgList != NULL)
		{
			for(int i = 0; i < argCount; i++)
			{
                // If debug
				if(wcscmp(szArgList[i], L"/ddrawdebug") == 0) {
					debugDisplay = 0;
					debugLevel = 2;
					// Create the debug console
					AllocConsole();
					// Redirect stdout to console
					freopen( "CONOUT$", "wb", stdout);
					break;
				}
                // If ddrawlog
				else if(wcscmp(szArgList[i], L"/ddrawlog") == 0) {
					debugDisplay = 1;
					debugLevel = 2;
					// Redireect stdout to file
					char curPath[MAX_PATH];
					char filename[MAX_PATH];
					GetCurrentDirectoryA(MAX_PATH, curPath);
					sprintf_s(filename, MAX_PATH, "%s\\ddraw_debug.log", curPath);
					freopen_s(&debugFile, filename, "wb", stdout);
					break;
				}
			}
		}
		LocalFree(szArgList);

		// Set mouse hook
		SetWindowsHookEx(WH_MOUSE_LL, mouseHookProc, GetModuleHandle(NULL), NULL);
        
		// Hook setcursorpos
		DetourRestoreAfterWith();
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)TrueSetCursorPos, OverrideSetCursorPos);
		//DetourAttach(&(PVOID&)TrueLoadLibraryA, OverrideLoadLibraryA);
        error = DetourTransactionCommit();
        if (error == NO_ERROR) {
            debugMessage(2, "DllMain(DLL_PROCESS_ATTACH)", "Successfully detoured SetCursorPos");
        }
        else {
            debugMessage(1, "DllMain(DLL_PROCESS_ATTACH)", "Failed to detour SetCursorPos");
        }
		break;
	case DLL_THREAD_ATTACH:
		// Do nothing on thread attach
		break;
	case DLL_THREAD_DETACH:
		// Do nothing on thread detach
		break;
	case DLL_PROCESS_DETACH:		
		// Delete DirectDrawWrapper object
		delete lpDD;

		// Detach function hook
		DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourDetach(&(PVOID&)TrueSetCursorPos, OverrideSetCursorPos);
        error = DetourTransactionCommit();

        
		//cleanup debug console or file if exists
		if(debugDisplay == 0)
		{
			FreeConsole();
		}
		else if(debugDisplay == 1)
		{
			fclose(debugFile);
		}
        
		break;
	}
	return TRUE;
}

// Emulated direct draw create
extern HRESULT WINAPI DirectDrawCreate(GUID FAR* lpGUID, LPDIRECTDRAW FAR* lplpDD, IUnknown FAR* pUnkOuter)
{
	// Create directdraw object
	lpDD = new IDirectDrawWrapper();
	if(lpDD == NULL) 
	{
		debugMessage(0, "DirectDrawCreate", "Failed to create IDirectDrawWrapper.");
		return DDERR_OUTOFMEMORY;  // Simulate OOM error
	}
	
	// Initialize the ddraw object with new wndproc
	HRESULT hr = lpDD->WrapperInitialize(&WndProc, hMod);
	// If error then return error(message will have been taken care of already)
	if(hr != DD_OK) return hr;

	// Set return pointer to the newly created DirectDrawWrapper interface
	*lplpDD = (LPDIRECTDRAW)lpDD;
	
	// Return success
	return DD_OK;
}