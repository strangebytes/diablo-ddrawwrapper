#include "DirectDrawWrapper.h"
#include "resource.h"

/*******************
**IUnknown methods**
********************/

// Retrieves pointers to the supported interfaces on an object.
HRESULT __stdcall IDirectDrawWrapper::QueryInterface(REFIID riid, LPVOID FAR * ppvObj)
{	
	debugMessage(1, "IDirectDrawWrapper::QueryInterface", "Partially Implemented");

	// Provide the directdraw interface for all versions up to 7
	if(riid == IID_IDirectDraw || riid == IID_IDirectDraw2 || riid == IID_IDirectDraw4 || riid == IID_IDirectDraw7)
	{
		// Set pointer to this interface
		ppvObj = (LPVOID *)this;
		// Increment reference count
		AddRef();
		// Return success
		return S_OK;
	}

	//interface not supported
	return E_NOINTERFACE;
}

// Increments the reference count for an interface on an object.
ULONG __stdcall IDirectDrawWrapper::AddRef()
{
	debugMessage(1, "IDirectDrawWrapper::AddRef", "Partially Implemented");

	// Increment reference count
	ReferenceCount++;
	// Return current reference count
	return ReferenceCount;
}

// Decrements the reference count for an interface on an object.
ULONG __stdcall IDirectDrawWrapper::Release()
{
	debugMessage(1, "IDirectDrawWrapper::Release", "Partially Implemented");

	// Decrement reference count
	ReferenceCount--;
	// If reference count reaches 0 then free object
	if(ReferenceCount == 0)
	{
		// Should free objects
	}
	// Return new reference count
	return ReferenceCount;
}

/**********************
**IDirectDraw methods**
***********************/

// This method is not currently implemented.
HRESULT __stdcall IDirectDrawWrapper::Compact()
{
	debugMessage(0, "IDirectDrawWrapper::Compact", "Unsupported in DirectDraw");

	return DD_OK;
}

// Creates a DirectDrawClipper object.
HRESULT __stdcall IDirectDrawWrapper::CreateClipper(DWORD dwFlags, LPDIRECTDRAWCLIPPER FAR *lplpDDClipper, IUnknown FAR *pUnkOuter)
{
	char message[2048] = "\0";
	sprintf_s(message, 2048, "Partially Supported dwFlags: %d", dwFlags);
	debugMessage(1, "IDirectDrawWrapper::CreateClipper", message);

	// Create new IDirectDrawClipperWrapper with the given flags
	IDirectDrawClipperWrapper *lpDDClipper = new IDirectDrawClipperWrapper();
	if(lpDDClipper == NULL) return DDERR_OUTOFMEMORY; //OOM Fail
	// Initialize the clipper wrapper
	HRESULT hr = lpDDClipper->WrapperInitialize(dwFlags);
	// If fail then return result
	if(hr != DD_OK) return hr;


	// Set the address to the new object
	*lplpDDClipper = (LPDIRECTDRAWCLIPPER)lpDDClipper;

	// If creation was successful
	if(lpDDClipper != NULL)
		return DD_OK;
	else
		return DDERR_OUTOFMEMORY;  //OOM Fail
}

// Creates a DirectDrawPalette object for this DirectDraw object.
HRESULT __stdcall IDirectDrawWrapper::CreatePalette(DWORD dwFlags, LPPALETTEENTRY lpDDColorArray, LPDIRECTDRAWPALETTE FAR *lplpDDPalette, IUnknown FAR *pUnkOuter)
{
	char message[2048] = "\0";
	sprintf_s(message, 2048, "Created dwFlags: %d", dwFlags);

	// Create new IDirectDrawPaletteWrapper with the given flags and palette entries
	IDirectDrawPaletteWrapper *lpDDPalette = new IDirectDrawPaletteWrapper();
	if(lpDDPalette == NULL) return DDERR_OUTOFMEMORY; //OOM Fail
	// Initialize the palette wrapper
	HRESULT hr = lpDDPalette->WrapperInitialize(dwFlags, lpDDColorArray, lplpDDPalette);
	// If fail then return result
	if(hr != DD_OK) return hr;

	// Set the address to the new object
	*lplpDDPalette = (LPDIRECTDRAWPALETTE)lpDDPalette;
	
	debugMessage(2, "IDirectDrawWrapper::CreatePalette", message);

	// If creation was successful
	return DD_OK;
} 

// Creates a DirectDrawSurface object for this DirectDraw object.
HRESULT __stdcall IDirectDrawWrapper::CreateSurface(LPDDSURFACEDESC lpDDSurfaceDesc, LPDIRECTDRAWSURFACE FAR *lplpDDSurface, IUnknown FAR *pUnkOuter)
{
	char message[2048] = "\0";
	sprintf_s(message, 2048, "lpDDSurfaceDesc->dwFlags:: %d", lpDDSurfaceDesc->dwFlags);

	// Create our surface wrapper and return success
	lpAttachedSurface = new IDirectDrawSurfaceWrapper(this);
	if(lpAttachedSurface == NULL) return DDERR_OUTOFMEMORY; //OOM Fail
	// Initialize the surface wrapper
	HRESULT hr = lpAttachedSurface->WrapperInitialize(lpDDSurfaceDesc, displayModeWidth, displayModeHeight, displayWidth, displayHeight);
	// If fail then return result
	if(hr != DD_OK) return hr;

	// Set the address to the new object
	*lplpDDSurface = (LPDIRECTDRAWSURFACE)lpAttachedSurface;
	
	debugMessage(2, "IDirectDrawWrapper::CreateSurface", message);

	// If creation was successful
	return DD_OK;
}

// Duplicates a DirectDrawSurface object.
HRESULT __stdcall IDirectDrawWrapper::DuplicateSurface(LPDIRECTDRAWSURFACE lpDDSurface, LPDIRECTDRAWSURFACE FAR *lplpDupDDSurface)
{
	//***Unimplemented***
	debugMessage(0, "DirectDrawWrapper::DuplicateSurface", "Not Implemented");
	return DDERR_GENERIC;

	/*
    DDERR_CANTDUPLICATE
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_OUTOFMEMORY
    DDERR_SURFACELOST
	*/
}

// Enumerates all the display modes that the hardware exposes through the 
// DirectDraw object and that are compatible with a provided surface description.
HRESULT __stdcall IDirectDrawWrapper::EnumDisplayModes(DWORD dwFlags, LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext, LPDDENUMMODESCALLBACK lpEnumModesCallback)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawWrapper::EnumDisplayModes", "Not Implemented");

	if(lpDDSurfaceDesc == NULL)
	{
		//enumerate all available display modes
		//call lpEnumModesCallback on each match
		//HRESULT WINAPI EnumModesCallback2(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext);
		//lpEnumModesCallback(<surface desc for video mode>, lpContext);
		//if returns DDENUMRET_OK continue
		//else if returns DDENUMRET_CANCEL cancel enumeration
		//if dwFlags & DDEDM_REFRESHRATES, modes with different refresh rates are unique
		//if dwFlags & DDEDM_STANDARDVGAMODES, include Mode 13 and 320x200x8 Mode X
	}
	else
	{
		//check available display modes against lpDDSurfaceDesc
		//call lpEnumModesCallback on each match
		//HRESULT WINAPI EnumModesCallback2(LPDDSURFACEDESC2 lpDDSurfaceDesc, LPVOID lpContext);
		//lpEnumModesCallback(<surface desc for video mode>, lpContext);
		//if returns DDENUMRET_OK continue
		//else if returns DDENUMRET_CANCEL cancel enumeration
		//if dwFlags & DDEDM_REFRESHRATES, modes with different refresh rates are unique
		//if dwFlags & DDEDM_STANDARDVGAMODES, include Mode 13 and 320x200x8 Mode X
	}
	return DDERR_GENERIC;
	
	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
	*/
}

// Enumerates all the existing or possible surfaces that 
// meet the specified surface description. 
HRESULT __stdcall IDirectDrawWrapper::EnumSurfaces(DWORD dwFlags, LPDDSURFACEDESC lpDDSD, LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpEnumSurfacesCallback)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawWrapper::EnumSurfaces", "Not Implemented");

	if(dwFlags & DDENUMSURFACES_CANBECREATED)
	{
		if(dwFlags & DDENUMSURFACES_MATCH)
		{
			//Searches for any surface that matches the surface description in lpDDSD.
			//EnumSurfacesCallback7
			//lpEnumSurfacesCallback(LPDIRECTDRAWSURFACE7 lpDDSurface, LPDDSURFACEDESC2 lpDDSurfaceDesc, lpContext);
		}
		//CANBECREATED must be used with MATCH
		else
		{
			return DDERR_INVALIDPARAMS;
		}
	}
	else if(dwFlags & DDENUMSURFACES_DOESEXIST)
	{
		if(dwFlags & DDENUMSURFACES_ALL)
		{
			//Enumerates all surfaces that meet the search criterion.
			//EnumSurfacesCallback7
			//lpEnumSurfacesCallback(LPDIRECTDRAWSURFACE7 lpDDSurface, LPDDSURFACEDESC2 lpDDSurfaceDesc, lpContext);
		}
		else if(dwFlags & DDENUMSURFACES_MATCH)
		{
			//Searches for any surface that matches the surface description.
			//EnumSurfacesCallback7
			//lpEnumSurfacesCallback(LPDIRECTDRAWSURFACE7 lpDDSurface, LPDDSURFACEDESC2 lpDDSurfaceDesc, lpContext);
		}
		else if(dwFlags & DDENUMSURFACES_NOMATCH)
		{
			//Searches for any surface that does not match the surface description.
			//EnumSurfacesCallback7
			//lpEnumSurfacesCallback(LPDIRECTDRAWSURFACE7 lpDDSurface, LPDDSURFACEDESC2 lpDDSurfaceDesc, lpContext);
		}
	}

	return DDERR_GENERIC;

	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
	*/
}

// Makes the surface that the GDI writes to the primary surface.
HRESULT __stdcall IDirectDrawWrapper::FlipToGDISurface()
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawWrapper::FlipToGDISurface", "Not Implemented");

	/*
	You can call FlipToGDISurface at the end of a page-flipping
	application to ensure that the display memory that the GDI
	writes to is visible.

	You can also use FlipToGDISurface to make the GDI surface
	the primary surface so that normal windows, such as dialog
	boxes, can be displayed in full-screen mode. The hardware
	must have the DDCAPS2_CANRENDERWINDOWED capability.
	*/

	return DDERR_GENERIC;
	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_NOTFOUND
	*/
}

// Retrieves the capabilities of the device driver for the hardware and the hardware emulation layer (HEL).
HRESULT __stdcall IDirectDrawWrapper::GetCaps(LPDDCAPS lpDDDriverCaps, LPDDCAPS lpDDHELCaps)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawWrapper::GetCaps", "Not Implemented");

	//both params cannot be null
	if(lpDDDriverCaps == NULL && lpDDHELCaps == NULL) return DDERR_INVALIDPARAMS;

	//if driver caps is not null
	if(lpDDDriverCaps != NULL)
	{
		//lpDDDriverCaps receives the capabilities of the hardware, as reported by the device driver
	}
	//if HEL caps is not null
	if(lpDDHELCaps != NULL)
	{
		//lpDDHELCaps receives the capabilities of the HEL
	}

	return DDERR_GENERIC;
	/*
    DDERR_INVALIDOBJECT
	*/
}

// Retrieves the current display mode.
HRESULT __stdcall IDirectDrawWrapper::GetDisplayMode(LPDDSURFACEDESC lpDDSurfaceDesc)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawWrapper::GetDisplayMode", "Not Implemented");

	// lpDDSurfaceDesc cannot be null
	if(lpDDSurfaceDesc == NULL) return DDERR_INVALIDPARAMS;

	// lpDDSurfaceDesc receives a description of the current surface

	return DDERR_GENERIC;

	/*
    DDERR_INVALIDOBJECT
    DDERR_UNSUPPORTEDMODE
	*/
}

// Retrieves the four-character codes (FOURCC) that are supported by the 
// DirectDraw object. This method can also retrieve the number of codes that are supported. 
HRESULT __stdcall IDirectDrawWrapper::GetFourCCCodes(LPDWORD lpNumCodes, LPDWORD lpCodes)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawWrapper::GetFourCCCodes", "Not Implemented");

	// lpNumCodes cannot be null
	if(lpNumCodes == NULL) return DDERR_INVALIDPARAMS;

	// if no array is provided to hold FOURCC codes then return the count
	if(lpCodes == NULL)
	{
		//lpNumCodes = number of supported FOURCCs
	}
	else
	{
		//lpNumCodes is less than the total number of FOURCC codes
		//if(lpNumCodes < <FOURCC code count>)
		//{
		//	fill lpCodes with the first lpNumCodes we have
		//  set lpNumCodes to the number of available FOURCC codes
		//}
		//else
		//{
		//	fill lpCodes with all FOURCC codes we have
		//  [should lpNumCodes be set to the true number of FOURCC codes?]
		//}
	}
	
	return DDERR_GENERIC;

	/*
	DDERR_INVALIDOBJECT
	*/
}

// Retrieves the DirectDrawSurface object that currently represents
// the surface memory that GDI is treating as the primary surface.
HRESULT __stdcall IDirectDrawWrapper::GetGDISurface(LPDIRECTDRAWSURFACE FAR *lplpGDIDDSSurface)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawWrapper::GetGDISurface", "Not Implemented");

	// lplpGDIDDSSurface cannot be null
	if(lplpGDIDDSSurface == NULL) return DDERR_INVALIDPARAMS;

	// set lplpGDIDDSSurface to the interface for the surface 
    // that currently controls the GDI's primary surface memory.

	return DDERR_GENERIC;
	
	/*
    DDERR_INVALIDOBJECT
    DDERR_NOTFOUND
	*/
}

//Retrieves the frequency of the monitor that the DirectDraw object controls.
HRESULT __stdcall IDirectDrawWrapper::GetMonitorFrequency(LPDWORD lpdwFrequency)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawWrapper::GetMonitorFrequency", "Not Implemented");

	// lpdwFrequency cannot be null
	if(lpdwFrequency == NULL) return DDERR_INVALIDPARAMS;

	// lpdwFrequency receives the monitor frequency, in Hz

	return DDERR_GENERIC;
	/*
    DDERR_INVALIDOBJECT
    DDERR_UNSUPPORTED
	*/
}

//Retrieves the scan line that is currently being drawn on the monitor.
HRESULT __stdcall IDirectDrawWrapper::GetScanLine(LPDWORD lpdwScanLine)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawWrapper::GetScanLine", "Not Implemented");

	// lpdwScanLine cannot be null
	if(lpdwScanLine == NULL) return DDERR_INVALIDPARAMS;

	// lpdwScanLine receives the scan line that the display is currently drawing.

	/*
	Scan lines are reported as zero-based integers. The returned scan line value
	is in the range from 0 through n, where 0 is the first visible scan line on
	the screen and n is the last visible scan line, plus any scan lines that occur
	during the vertical blank period. So, in a case where an application is running
	at a resolution of 640×480 and there are 12 scan lines during vblank, the values
	returned by this method range from 0 through 491.
	*/

	return DDERR_GENERIC;
	/*
    DDERR_INVALIDOBJECT
    DDERR_UNSUPPORTED
    DDERR_VERTICALBLANKINPROGRESS
	*/
}

//Retrieves the status of the vertical blank.
HRESULT __stdcall IDirectDrawWrapper::GetVerticalBlankStatus(LPBOOL lpbIsInVB)
{
	// NOTE: Disabled for performance
	// debugMessage(1, "IDirectDrawWrapper::GetVerticalBlankStatus", "Partially Implemented");

	// lpbIsInVB cannot be null
	if(lpbIsInVB == NULL) return DDERR_INVALIDPARAMS;

	// lpbIsInVB is TRUE if a vertical blank is occurring, and FALSE otherwise.

	// since vertical blank drawing is handled by the VSYNC in d3d9 we are never in vertical blank
	lpbIsInVB = FALSE;

	return DD_OK;

	/*
	DDERR_INVALIDOBJECT
	*/
}

// Initializes a DirectDraw object that was created by using the CoCreateInstance COM function.
HRESULT __stdcall IDirectDrawWrapper::Initialize(GUID FAR *lpGUID)
{
	debugMessage(1, "IDirectDrawWrapper::Initialize", "Partially Implemented");

	// If you already used the DirectDrawCreate function to create a
    // DirectDraw object, this method returns DDERR_ALREADYINITIALIZED
	return DDERR_ALREADYINITIALIZED;

	/*
    DDERR_ALREADYINITIALIZED
    DDERR_DIRECTDRAWALREADYCREATED
    DDERR_GENERIC
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_NODIRECTDRAWHW
    DDERR_NODIRECTDRAWSUPPORT
    DDERR_OUTOFMEMORY
	*/
}

// Resets the mode of the display device hardware for the primary 
// surface to what it was before the IDirectDraw7::SetDisplayMode
// method was called. Exclusive-level access is required to use this method.
HRESULT __stdcall IDirectDrawWrapper::RestoreDisplayMode()
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawWrapper::RestoreDisplayMode", "Not Implemented");

	return DDERR_GENERIC;

	/*
    DDERR_GENERIC
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_LOCKEDSURFACES
    DDERR_NOEXCLUSIVEMODE
	*/
}

//Determines the top-level behavior of the application.
HRESULT __stdcall IDirectDrawWrapper::SetCooperativeLevel(HWND in_hWnd, DWORD dwFlags)
{
	char message[2048] = "\0";
	sprintf_s(message, 2048, "Completed in_hWnd: 0x%X, dwFlags: %d", (UINT)in_hWnd, dwFlags);

	if(in_hWnd == NULL) 
	{
		// message[0] = 0;
		debugMessage(0, "IDirectDrawWrapper::SetCooperativeLevel", "Unimplemented for NULL window handle");
		return DDERR_GENERIC;
	}

	// Set display window
	hWnd = in_hWnd;
	
	// Install new wndproc
	lpPrevWndFunc = (WNDPROC)GetWindowLong(hWnd, GWL_WNDPROC);
	if(SetWindowLong(hWnd, GWL_WNDPROC, (LONG)WndProc) == 0)
	{
		debugMessage(0, "IDirectDrawWrapper::SetCooperativeLevel", "Failed to overload WNDPROC");
	}

	// Adjust the display window to match the current display mode
	AdjustWindow();

	// Create the requested d3d device for this display mode, report error on failure
	if(!CreateD3DDevice())
	{
		MessageBox(NULL, TEXT("Error creating Direct3D9 Device"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return DDERR_GENERIC;
	}

	debugMessage(2, "IDirectDrawWrapper::SetCooperativeLevel", message);

	return DD_OK;

	/*
	DDSCL_ALLOWMODEX
    Allows the use of Mode X display modes. This flag can be used only if the DDSCL_EXCLUSIVE and DDSCL_FULLSCREEN flags are present.

	DDSCL_ALLOWREBOOT
    Allows CTRL+ALT+DEL to function while in exclusive (full-screen) mode.

	DDSCL_CREATEDEVICEWINDOW
    This flag is supported in Windows 98 and Windows 2000 only. Indicates that DirectDraw will create and manage a default device window for this DirectDraw object.

	DDSCL_EXCLUSIVE
    Requests the exclusive level. This flag must be used with the DDSCL_FULLSCREEN flag.

	DDSCL_FPUPRESERVE
    The calling application cares about the FPU state and does not want Direct3D to modify it in ways visible to the application. In this mode, Direct3D saves and restores the FPU state every time that it needs to modify the FPU state.

	DDSCL_FPUSETUP
    The calling application is likely to keep the FPU set up for optimal Direct3D performance (single precision and exceptions disabled), so Direct3D does not need to explicitly set the FPU each time. This is the default state.

	DDSCL_FULLSCREEN
    The exclusive-mode owner is responsible for the entire primary surface. The GDI can be ignored. This flag must be used with the DDSCL_EXCLUSIVE flag.

	DDSCL_MULTITHREADED
    Requests multithread-safe DirectDraw behavior. This causes Direct3D to take the global critical section more frequently.

	DDSCL_NORMAL
    The application functions as a typical Windows application. This flag cannot be used with the DDSCL_ALLOWMODEX, DDSCL_EXCLUSIVE, or DDSCL_FULLSCREEN flags.

	DDSCL_NOWINDOWCHANGES
    DirectDraw is not allowed to minimize or restore the application window on activation.

	DDSCL_SETDEVICEWINDOW
    This flag is supported in Windows 98 and Windows 2000 only. Indicates that the hWnd parameter is the window handle of the device window for this DirectDraw object. This flag cannot be used with the DDSCL_SETFOCUSWINDOW flag.

	DDSCL_SETFOCUSWINDOW
    This flag is supported in Windows 98 and Windows 2000 only. Indicates that the hWnd parameter is the window handle of the focus window for this DirectDraw object. This flag cannot be used with the DDSCL_SETDEVICEWINDOW flag.
	*/

	/*
    DDERR_EXCLUSIVEMODEALREADYSET
    DDERR_HWNDALREADYSET
    DDERR_HWNDSUBCLASSED
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_OUTOFMEMORY
	*/
}

// Sets the mode of the display-device hardware.
HRESULT __stdcall IDirectDrawWrapper::SetDisplayMode(DWORD dwWidth, DWORD dwHeight, DWORD dwBPP)
{
	char message[2048] = "\0";
	sprintf_s(message, "Complete dwWidth: %d, dwHeight: %d, dwBPP: %d", dwWidth, dwHeight, dwBPP);

	// Set display mode to dwWidth x dwHeight with dwBPP color depth
	displayModeWidth = dwWidth;
	displayModeHeight = dwHeight;

	// Ignore color depth

	// Init textures to new display mode
	if(!CreateSurfaceTexture())
	{
		MessageBox(NULL, TEXT("Error creating Direct3D9 surface texture"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return DDERR_GENERIC;
	}

	debugMessage(2, "IDirectDrawWrapper::SetDisplayMode", message);

	return DD_OK;
	/*
    DDERR_GENERIC
    DDERR_INVALIDMODE
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_LOCKEDSURFACES
    DDERR_NOEXCLUSIVEMODE
    DDERR_SURFACEBUSY
    DDERR_UNSUPPORTED
    DDERR_UNSUPPORTEDMODE
    DDERR_WASSTILLDRAWING
	*/
}


// Sets the mode of the display-device hardware(IDirectDraw2 or higher).
/*HRESULT __stdcall IDirectDrawWrapper::SetDisplayMode(DWORD dwWidth, DWORD dwHeight, DWORD dwBPP, DWORD dwRefreshRate, DWORD dwFlags)
{
	message[0] = 0;
	sprintf_s(message, 2048, "dwWidth: %d, dwHeight: %d, dwBPP: %d, swRefreshRate: %d, ", dwWidth, dwHeight, dwBPP, dwRefreshRate);
	if(dwFlags & DDSDM_STANDARDVGAMODE) strcat_s(message, 2048, ", DDSDM_STANDARDVGAMODE");
	location[0] = 0;
	sprintf_s(location, 2048, "IDirectDrawWrapper::SetDisplayMode");
	debugCallback(2, location, message);

	if(dwFlags & DDSDM_STANDARDVGAMODE)
	{
		//use Mode 13 instead of Mode X 320x200x8 mode
	}

	if(dwRefreshRate == 0)
	{
		//set display mode to dwWidth x dwHeight with dwBPP color depth with default refresh rate
	}
	else
	{
		//set display mode to dwWidth x dwHeight with dwBPP color depth with dwRefreshRate refresh rate
	}

	displayModeWidth = dwWidth;
	displayModeHeight = dwHeight;

	//ignore color depth


	return DD_OK;
	
    DDERR_GENERIC
    DDERR_INVALIDMODE
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_LOCKEDSURFACES
    DDERR_NOEXCLUSIVEMODE
    DDERR_SURFACEBUSY
    DDERR_UNSUPPORTED
    DDERR_UNSUPPORTEDMODE
    DDERR_WASSTILLDRAWING
	
}*/

// Helps the application synchronize itself with the vertical-blank interval.
HRESULT __stdcall IDirectDrawWrapper::WaitForVerticalBlank(DWORD dwFlags, HANDLE hEvent)
{
	// NOTE: Disabled for performance
	// debugMessage(1, "IDirectDrawWrapper::WaitForVerticalBlank", "Partially Supported");

	if(dwFlags & DDWAITVB_BLOCKBEGIN)
	{
		// Return when vertical blank begins
	}
	else if(dwFlags & DDWAITVB_BLOCKBEGINEVENT)
	{
		// Triggers an event when the vertical blank begins. This value is not currently supported.
		return DDERR_UNSUPPORTED;
	}
	else if(dwFlags & DDWAITVB_BLOCKEND)
	{
		// Return when the vertical-blank interval ends and the display begins.
	}

	// Vblank supported by vsync so just immediately return
	return DD_OK;

	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_UNSUPPORTED
    DDERR_WASSTILLDRAWING
	*/
}

/****************************
**Added in the V2 interface**
*****************************/

// Retrieves the total amount of display memory available and the
// amount of display memory currently free for a given type of surface.
HRESULT __stdcall IDirectDrawWrapper::GetAvailableVideoMem(LPDDSCAPS2 lpDDSCaps2, LPDWORD lpdwTotal, LPDWORD lpdwFree)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawWrapper::GetAvailableVideoMem", "Not Implemented");

	//no parameters may be null
	if(lpDDSCaps2 == NULL || lpdwTotal == NULL || lpdwFree == NULL) return DDERR_INVALIDPARAMS;

	//lpdwTotal receives the total amount of display memory available, in bytes. 
	//The value received reflects the total video memory, minus the video memory 
	//required for the primary surface and any private caches that the display driver reserves.

	//lpdwFree receives the amount of display memory currently free that can be allocated for 
	//a surface that matches the capabilities specified by the structure at lpDDSCaps2

	return DDERR_GENERIC;
	
	/*
    DDERR_INVALIDCAPS
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_NODIRECTDRAWHW
	*/
}

/****************************
**Added in the V4 interface**
*****************************/

// Used after a call to IDirectDraw7::StartModeTest to pass or fail each mode that the 
// test presents and to step through the modes until the test is complete. 
HRESULT __stdcall IDirectDrawWrapper::EvaluateMode(DWORD dwFlags, DWORD *pSecondsUntilTimeout)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawWrapper::EvaluateMode", "Not Implemented");

	//pSecondsUntilTimeout cannot be null
	if(pSecondsUntilTimeout == NULL) return DDERR_INVALIDPARAMS;

	/*
	DDEM_MODEPASSED
    The mode being tested has passed.

	DDEM_MODEFAILED
    The mode being tested has failed.
	*/

	/*
	You can use EvaluateMode in conjunction with the IDirectDraw7::StartModeTest method to determine 
	the maximum refresh rate that an EDID monitor and display adapter combination can support for each 
	screen resolution.

	Specifically, a call to IDirectDraw7::StartModeTest directs DirectDraw to establish a set of testable 
	resolutions and to display a mode based on the first resolution in the set. Subsequent calls to 
	EvaluateMode can be used to pass or fail each mode and to advance the test to the next display mode. 
	The method steps through the testable resolutions starting with the highest refresh rate supported for 
	a given resolution. After a refresh rate for a given resolution passes, testing of lower refresh rates 
	for that resolution is skipped.

	When the test is initiated, or whenever a mode is passed or failed, DirectDraw begins a 15 second timeout. 
	An application can monitor the time remaining without passing or failing the current mode by calling 
	EvaluateMode with a value of 0 for the dwFlags argument. Note that DirectDraw only changes modes or 
	terminates the test when EvaluateMode is called. However, if an application calls EvaluateMode after 
	the timeout period has elapsed, the current mode fails, regardless of the value passed to the dwFlags 
	parameter. 
	*/

	return DDERR_GENERIC;

	/*
    DDERR_TESTFINISHED
    DDERR_NEWMODE
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_NOTFOUND
	*/
}

// Obtains information about the device driver. This method can be used, with caution, 
// to recognize specific hardware installations to implement workarounds for poor driver or chipset behavior. 
HRESULT __stdcall IDirectDrawWrapper::GetDeviceIdentifier(LPDDDEVICEIDENTIFIER2 lpdddi, DWORD dwFlags)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawWrapper::GetDeviceIdentifier", "Not Implemented");

	// lpdddi cannot be null
	if(lpdddi == NULL) return DDERR_INVALIDPARAMS;

	// Only valid flag
	if(dwFlags == DDGDI_GETHOSTIDENTIFIER)
	{
		//Causes GetDeviceIdentifier to return information about the host (typically 2-D) adapter in a 
		//system equipped with a stacked secondary 3-D adapter. Such an adapter appears to the application 
		//as if it were part of the host adapter, but is typically located on a separate card.
	}
	else
	{
		//information on the stacked secondary is returned because this most accurately reflects the
		//qualities of the DirectDraw object involved.
	}

	return DDERR_GENERIC;
}


// Retrieves the IDirectDrawSurface7 interface for a surface, based on its GDI device context handle.
HRESULT __stdcall IDirectDrawWrapper::GetSurfaceFromDC(HDC hdc, LPDIRECTDRAWSURFACE7 *lpDDS)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawWrapper::GetSurfaceFromDC", "Not Implemented");

	// lpDDS cannot be null
	if(lpDDS == NULL) return DDERR_INVALIDPARAMS;

	// lpDDS is filled with a pointer to the IDirectDrawSurface7 interface
    // for the surface if the call succeeds for the display device context hdc
	
	// This method succeeds only for device context handles that identify 
    // surfaces already associated with the DirectDraw object. 

	return DDERR_GENERIC;
	
	/*	
    DDERR_GENERIC
    DDERR_INVALIDPARAMS
    DDERR_OUTOFMEMORY
	DDERR_NOTFOUND
	*/
}

// Restores all the surfaces that were created for the DirectDraw object, in the order that they were created. 
HRESULT __stdcall IDirectDrawWrapper::RestoreAllSurfaces()
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawWrapper::RestoreAllSurfaces", "Not Implemented");

	// This method is provided for convenience. Effectively, this method calls the IDirectDrawSurface7::Restore 
	// method for each surface that is created by this DirectDraw object. 

	return DDERR_GENERIC;
	
	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
	*/
}

// Initiates a test to update the system registry with refresh rate information for the current display adapter 
// and monitor combination. A call to this method is typically followed by calls to IDirectDraw7::EvaluateMode to
// pass or fail modes displayed by the test. 
HRESULT __stdcall IDirectDrawWrapper::StartModeTest(LPSIZE lpModesToTest, DWORD dwNumEntries, DWORD dwFlags)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawWrapper::StartModeTest", "Not Implemented");

	if(lpModesToTest == NULL && dwNumEntries == 0 && dwFlags == 0)
	{
		// Clear existing refresh rate information from the registry.
	}

	/*
	You can use the StartModeTest method together with the IDirectDraw7::EvaluateMode method to determine 
	the maximum refresh rate that an EDID monitor and display adapter combination can support for each screen 
	resolution. The results of the testing are stored in the system registry and affect the operation of 
	IDirectDraw7::EnumDisplayModes when that method is called with the DDEDM_REFRESHRATES flag set. 
	*/

	/*
	StartModeTest succeeds only with monitors that contain EDID data. If the monitor is not EDID-compliant, 
	StartModeTest returns DDERR_TESTFINISHED without testing any modes. If the EDID table does not contain values
	higher than 60 Hz, no modes are tested. Refresh rates higher than 100 Hz are tested only if the EDID table
	contains values higher than 85 Hz. 
	*/


	if(dwFlags & DDSMT_ISTESTREQUIRED)
	{
		//StartModeTest does not initiate a test, but instead returns a value that indicates whether 
		//it is possible or necessary to test the resolutions that the lpModesToTest and dwNumEntries
		//parameters identify.
		
		/*
		DDERR_NEWMODE
		DDERR_NODRIVERSUPPORT
		DDERR_NOMONITORINFORMATION
		DDERR_TESTFINISHED
		*/
	}
	else
	{
		//lpModesToTest is an array of dwNumEntries elements that describe, in terms of screen resolutions, the modes that should be tested.
	}

	return DDERR_GENERIC;
	
	/*
    DDERR_CURRENTLYNOTAVAIL
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_NOEXCLUSIVEMODE
    DDERR_NOTFOUND
    DDERR_TESTFINISHED
	*/
}

// Reports the current cooperative-level status of the DirectDraw device for a windowed or full-screen application. 
HRESULT __stdcall IDirectDrawWrapper::TestCooperativeLevel()
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawWrapper::TestCooperativeLevel", "Not Implemented");

	// If the calling application can continue then return OK

	return DDERR_GENERIC;

	/*
    DDERR_INVALIDOBJECT
    DDERR_EXCLUSIVEMODEALREADYSET
    DDERR_NOEXCLUSIVEMODE
    DDERR_WRONGMODE
	*/
}

// Default constructor
IDirectDrawWrapper::IDirectDrawWrapper()
{
	// Init vars
	hWnd = NULL;
	WndProc = NULL;
	lpPrevWndFunc = NULL;
	hModule = NULL;

	ReferenceCount = 0;

	lpAttachedSurface = NULL;

	// Init objects
	d3d9Object = NULL;
	d3d9Device = NULL;
	surfaceTexture = NULL;
	vertexBuffer = NULL;

    // Sprite Info
	d3dSprite = NULL;
	menuTexture = NULL;
	curMenuFrame = 0;
	menuLocations[0] = 117;
	menuLocations[1] = 162;
	menuLocations[2] = 208;
	menuLocations[3] = 253;
	menuLocations[4] = 298;
	//0
	menuSprites[0].left = 0;
	menuSprites[0].top = 0;
	menuSprites[0].right = 30;
	menuSprites[0].bottom = 32;
	//1
	menuSprites[1].left = menuSprites[0].right;
	menuSprites[1].top = 0;
	menuSprites[1].right = menuSprites[1].left + 14;
	menuSprites[1].bottom = 32;
	//2
	menuSprites[2].left = menuSprites[1].right;
	menuSprites[2].top = 0;
	menuSprites[2].right = menuSprites[2].left + 22;
	menuSprites[2].bottom = 32;
	//3
	menuSprites[3].left = menuSprites[2].right;
	menuSprites[3].top = 0;
	menuSprites[3].right = menuSprites[3].left + 21;
	menuSprites[3].bottom = 32;
	//4
	menuSprites[4].left = menuSprites[3].right;
	menuSprites[4].top = 0;
	menuSprites[4].right = menuSprites[4].left + 23;
	menuSprites[4].bottom = 32;
	//5
	menuSprites[5].left = menuSprites[4].right;
	menuSprites[5].top = 0;
	menuSprites[5].right = menuSprites[5].left + 21;
	menuSprites[5].bottom = 32;
	//6
	menuSprites[6].left = menuSprites[5].right;
	menuSprites[6].top = 0;
	menuSprites[6].right = menuSprites[6].left + 20;
	menuSprites[6].bottom = 32;
	//7
	menuSprites[7].left = menuSprites[6].right;
	menuSprites[7].top = 0;
	menuSprites[7].right = menuSprites[7].left + 21;
	menuSprites[7].bottom = 32;
	//8
	menuSprites[8].left = menuSprites[7].right;
	menuSprites[8].top = 0;
	menuSprites[8].right = menuSprites[8].left + 20;
	menuSprites[8].bottom = 32;
	//9
	menuSprites[9].left = menuSprites[8].right;
	menuSprites[9].top = 0;
	menuSprites[9].right = menuSprites[9].left + 21;
	menuSprites[9].bottom = 32;
	//x
	menuSprites[10].left = menuSprites[9].right;
	menuSprites[10].top = 0;
	menuSprites[10].right = menuSprites[10].left + 25;
	menuSprites[10].bottom = 32;
	//RESOLUTION
	menuSprites[11].left = 0;
	menuSprites[11].top = 32;
	menuSprites[11].right = 246;
	menuSprites[11].bottom = 64;
	//FULLSCREEN:
	menuSprites[12].left = 0;
	menuSprites[12].top = 64;
	menuSprites[12].right = 243;
	menuSprites[12].bottom = 96;
	//VSYNC:
	menuSprites[13].left = 0;
	menuSprites[13].top = 96;
	menuSprites[13].right = 144;
	menuSprites[13].bottom = 128;
	//ACCEPT
	menuSprites[14].left = 0;
	menuSprites[14].top = 128;
	menuSprites[14].right = 151;
	menuSprites[14].bottom = 160;
	//ON
	menuSprites[15].left = 160;
	menuSprites[15].top = 96;
	menuSprites[15].right = menuSprites[15].left + 55;
	menuSprites[15].bottom = 128;
	//OFF
	menuSprites[16].left = 160;
	menuSprites[16].top = 128;
	menuSprites[16].right = menuSprites[15].left + 69;
	menuSprites[16].bottom = 160;
	//Diablo Logo
	menuSprites[17].left = 0;
	menuSprites[17].top = 256;
	menuSprites[17].right = 295;
	menuSprites[17].bottom = 356;

	inMenu = false;
	curMenu = 0;
    // Resolutions
	windowedResolutions = new POINT[10];
	windowedResolutionCount = 10;
	windowedResolutions[0].x = 640;
	windowedResolutions[0].y = 480;
	windowedResolutions[1].x = 800;
	windowedResolutions[1].y = 600;
	windowedResolutions[2].x = 960;
	windowedResolutions[2].y = 720;
	windowedResolutions[3].x = 1024;
	windowedResolutions[3].y = 768;
	windowedResolutions[4].x = 1152;
	windowedResolutions[4].y = 864;
	windowedResolutions[5].x = 1280;
	windowedResolutions[5].y = 960;
	windowedResolutions[6].x = 1400;
	windowedResolutions[6].y = 1050;
	windowedResolutions[7].x = 1440;
	windowedResolutions[7].y = 1080;
	windowedResolutions[8].x = 1600;
	windowedResolutions[8].y = 1200;
	windowedResolutions[9].x = 1920;
	windowedResolutions[9].y = 1440;

	fullscreenResolutionCount = 0;
	fullscreenResolutions = NULL;
	fullscreenRefreshes = NULL;

	// Load settings from ini file
	wchar_t curPath[MAX_PATH];
	wchar_t filename[MAX_PATH];
	wchar_t temp[1024];

	// Get current working directory
	GetCurrentDirectory(MAX_PATH, curPath);
	wsprintf(filename, TEXT("%s\\ddraw_settings.ini"), curPath);
	// Get windowed resolution
	GetPrivateProfileString(TEXT("video"), TEXT("windowedResolution"), TEXT("640x480"), temp, 1024, filename);
	for(int i = 0; i < 1024 || temp[i] == TEXT('\0'); i++)
	{
		// Split on x or X
		if(temp[i] == TEXT('x') || temp[i] == TEXT('X'))
		{
			temp[i] = TEXT('\0');
			// Attempt to convert to int
			displayWidthWindowed = _wtoi(temp);
			displayHeightWindowed = _wtoi(&(temp[i + 1]));
			// Failure to convert use default
			if(displayWidthWindowed == 0 || displayHeightWindowed == 0)
			{
				displayWidthWindowed = 640;
				displayHeightWindowed = 480;
			}
			break;
		}
	}
	// Get fullscreen resolution
	GetPrivateProfileString(TEXT("video"), TEXT("fullscreenResolution"), TEXT("640x480"), temp, 1024, filename);
	for(int i = 0; i < 1024 || temp[i] == TEXT('\0'); i++)
	{
		// Split on x or X
		if(temp[i] == TEXT('x') || temp[i] == TEXT('X'))
		{
			temp[i] = TEXT('\0');
			// Attempt to convert to int
			displayWidthFullscreen = _wtoi(temp);
			displayHeightFullscreen = _wtoi(&(temp[i + 1]));
			// Failure to convert use default
			if(displayWidthFullscreen == 0 || displayHeightFullscreen == 0)
			{
				displayWidthFullscreen = 640;
				displayHeightFullscreen = 480;
			}
			break;
		}
	}
	// Default to fullscreen mode?
	GetPrivateProfileString(TEXT("video"), TEXT("fullscreen"), TEXT("0"), temp, 1024, filename);
	if(temp[0] == TEXT('1'))
	{
		isWindowed = false;
	}
	else
	{
		isWindowed = true;
	}
	// Set the resolution
	if(isWindowed)
	{
		displayWidth = displayWidthWindowed;
		displayHeight = displayHeightWindowed;
	}
	else
	{
		displayWidth = displayWidthFullscreen;
		displayHeight = displayHeightFullscreen;
	}
	GetPrivateProfileString(TEXT("video"), TEXT("vsync"), TEXT("1"), temp, 1024, filename);
	if(temp[0] == TEXT('1'))
	{
		vSync = false;
	}
	else
	{
		vSync = true;
	}

	GetPrivateProfileString(TEXT("video"), TEXT("refresh"), TEXT("60"), temp, 1024, filename);
	refreshRate = _wtoi(temp);
	// Failure to convert set to default
	if(refreshRate == 0)
	{
		refreshRate = 60;
	}

	// Load settings from registry or ini file or set defaults
	lastPosition.x = 100;
	lastPosition.y = 100;

	// Increment reference count
	AddRef();

	debugMessage(2, "IDirectDrawWrapper::IDirectDrawWrapper", "Created");
}

// Default destructor
IDirectDrawWrapper::~IDirectDrawWrapper()
{
	//**Free d3d objects**

	// Release existing vertex buffer
	if(vertexBuffer != NULL)
	{
		vertexBuffer->Release();
		vertexBuffer = NULL;
	}

	// Release existing surface texture
	if(surfaceTexture != NULL)
	{
		surfaceTexture->Release();
		surfaceTexture = NULL;
	}
	if(d3dSprite != NULL)
	{
		d3dSprite->Release();
		d3dSprite = NULL;
	}

	if(menuTexture != NULL)
	{
		menuTexture->Release();
		menuTexture = NULL;
	}

	// Release existing d3ddevice(buggy, not in thread?)
	if(d3d9Device != NULL)
	{
		//d3d9Device->Release();
		d3d9Device = NULL;
	}
	
	// Release existing d3dobject
	if(d3d9Object != NULL)
	{
		d3d9Object->Release();
		d3d9Device = NULL;
	}

	// Release allocated memory
	if(windowedResolutions != NULL)
	{
		delete windowedResolutions;
		windowedResolutions = NULL;
		windowedResolutionCount = 0;
	}
	if(fullscreenResolutions != NULL)
	{
		delete fullscreenResolutions;
		fullscreenResolutions = NULL;
		fullscreenResolutions = 0;
	}

	//release this reference
	//Release();

	// Free objects
	debugMessage(2, "IDirectDrawWrapper::~IDirectDrawWrapper", "Destroyed");
}

// Initialize wrapper function
HRESULT IDirectDrawWrapper::WrapperInitialize(WNDPROC wp, HMODULE hMod)
{
	// Save new wndproc
	WndProc = wp;

	// Save the module
	hModule = hMod;

	// Create Direct3D9 device
	d3d9Object = Direct3DCreate9(D3D_SDK_VERSION);
	if(d3d9Object == NULL)
	{
		debugMessage(0, "IDirectDrawWrapper::WrapperInitialize", "Failed to create Direct3D9 object");
		MessageBox(NULL, TEXT("Failed to create Direct3D9 object."), TEXT("Fatal Error"), MB_OK | MB_ICONERROR);
		// Error creation directdraw
		return DDERR_GENERIC;
	}

	debugMessage(2, "IDirectDrawWrapper::WrapperInitialize", "Initialized");

	// Success
	return DD_OK;
}

/* Helper function to present the d3d surface
 * 
 */
HRESULT IDirectDrawWrapper::Present()
{
	// Make sure the device exists
	if(d3d9Device == NULL)
	{
		debugMessage(0, "IDirectDrawWrapper::Present","Present called when d3d9device doesn't exist");
		return false;
	}

	// Make sure surface texture exists
	if(surfaceTexture == NULL)
	{
		debugMessage(0, "IDirectDrawWrapper::Present","Present called when texture doesn't exist");
		return false;
	}

	// Make sure the attached surface exists
	if(lpAttachedSurface != NULL)
	{
		// Lock full dynamic texture
		D3DLOCKED_RECT d3dlrect;
		if(surfaceTexture->LockRect(0, &d3dlrect, NULL, D3DLOCK_DISCARD) != D3D_OK)
		{
			debugMessage(0, "IDirectDrawWrapper::Present","Failed to lock texture memory");
			return false;
		}

		// Copy bits to texture by scanline observing pitch
		for(DWORD y = 0; y < displayModeHeight; y++)
		{
			memcpy((BYTE *)d3dlrect.pBits + (y * d3dlrect.Pitch), &lpAttachedSurface->rgbVideoMem[y * displayModeWidth], displayModeWidth * sizeof(UINT32));
		}

		// Unlock dynamic texture
		if(surfaceTexture->UnlockRect(NULL) != D3D_OK)
		{	
			debugMessage(0, "IDirectDrawWrapper::Present","Failed to unlock texture memory");
			return false;
		}
	}
	else
	{
		debugMessage(1, "IDirectDrawWrapper::Present","Attempt to Present with no attached surface");
	}

	if(d3d9Device->Clear(0, NULL, D3DCLEAR_TARGET, 0xFF000000, 1.0f, 0) != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::Present","Failed to clear device");
		return false;
	}

	if(d3d9Device->BeginScene() != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::Present","Failed to begin scene");
		return false;
	}

	// Set texture
	if(d3d9Device->SetTexture(0, surfaceTexture) != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::Present","Failed to set texture");
		return false;
	}
	
	// Draw primitive
	if(d3d9Device->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 2) != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::Present","Failed to draw primitive");
		return false;
	}

	// Display menu options
	if(inMenu)
	{
		// Begin sprite draw
		d3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
		
		// Set scaling transform for current window size, if required
		if(displayWidth != displayModeWidth && displayHeight != displayModeHeight)
		{
			D3DXVECTOR2 scaling((FLOAT)displayWidth / (FLOAT)displayModeWidth, (FLOAT)displayHeight / (FLOAT)displayModeHeight);
			D3DXMATRIX mat;
			D3DXMatrixTransformation2D(&mat,NULL,0.0,&scaling,NULL,0.0,NULL);
			d3dSprite->SetTransform(&mat);
		}
		
		
		D3DXVECTOR3 pos;	
		pos.z = 0.0f;
		int selectionLeft, selectionRight;

		// Custom Diablo Logo
		pos.x = (640 - menuSprites[17].right) / 2.0f;
		pos.y = 3;
		d3dSprite->Draw(menuTexture, &menuSprites[17], NULL, &pos, 0xFFFFFFFF);

		// RESOLUTION
		pos.x = (640 - menuSprites[11].right) / 2.0f;
		pos.y = (float)menuLocations[0];
		d3dSprite->Draw(menuTexture, &menuSprites[11], NULL, &pos, 0xFFFFFFFF);

		pos.y = (float)menuLocations[1];
		// Print display string
		char temp[1024];
		// If windowed selected
		if(menuWindowed)
			sprintf_s(temp, 1024, "%dx%d", windowedResolutions[menuWindowedResolution].x, windowedResolutions[menuWindowedResolution].y);
		// If fullscreen selected
		else
			sprintf_s(temp, 1024, "%dx%dx%d", fullscreenResolutions[menuFullscreenResolution].x, fullscreenResolutions[menuFullscreenResolution].y, fullscreenRefreshes[menuFullscreenResolution]);
		// Step through resolution string and calculate string width for centering
		int resolutionStringWidth = 0;
		for(UINT i = 0; i < strlen(temp); i++)
		{
			// If number
			if(temp[i] != 'x')
			{
				resolutionStringWidth += menuSprites[temp[i] - 48].right - menuSprites[temp[i] - 48].left;
			}
			else
			{
				resolutionStringWidth += menuSprites[10].right - menuSprites[10].left;
			}
		}
		pos.x = (640 - resolutionStringWidth) / 2.0f;
		// Set location for menu selection marker
		if(curMenu == 0)
		{
			selectionLeft = (int)pos.x - 52;
			selectionRight = (int)pos.x + resolutionStringWidth + 10;
		}
		// Daw resolution string
		for(UINT i = 0; i < strlen(temp); i++)
		{
			// If number
			if(temp[i] != 'x')
			{
				d3dSprite->Draw(menuTexture, &menuSprites[temp[i] - 48], NULL, &pos, 0xFFFFFFFF);
				pos.x += menuSprites[temp[i] - 48].right - menuSprites[temp[i] - 48].left;
			}
			else
			{
				d3dSprite->Draw(menuTexture, &menuSprites[10], NULL, &pos, 0xFFFFFFFF);
				pos.x += menuSprites[10].right - menuSprites[10].left;
			}
		}

		// FULLSCREEN:
		pos.x = (640 - (menuSprites[12].right + (menuSprites[16].right - menuSprites[16].left) + 10)) / 2.0f;
		pos.y = (float)menuLocations[2];
		// Set location for menu selection marker
		if(curMenu == 1)
		{
			selectionLeft = (int)pos.x - 52;
			selectionRight = (int)pos.x + menuSprites[12].right + (menuSprites[16].right - menuSprites[16].left) + 20;
		}
		d3dSprite->Draw(menuTexture, &menuSprites[12], NULL, &pos, 0xFFFFFFFF);
		// OFF
		if(menuWindowed)
		{
			pos.x += menuSprites[12].right + 10;
			d3dSprite->Draw(menuTexture, &menuSprites[16], NULL, &pos, 0xFFFFFFFF);
		}
		// ON
		else
		{
			pos.x += menuSprites[12].right + 10 + 14;
			d3dSprite->Draw(menuTexture, &menuSprites[15], NULL, &pos, 0xFFFFFFFF);
		}
		
		// VSYNC:
		pos.x = (640 - (menuSprites[13].right + (menuSprites[16].right - menuSprites[16].left) + 10)) / 2.0f;
		pos.y = (float)menuLocations[3];
		// Set location for menu selection marker
		if(curMenu == 2)
		{
			selectionLeft = (int)pos.x - 52;
			selectionRight = (int)pos.x + menuSprites[13].right + (menuSprites[16].right - menuSprites[16].left) + 20;
		}
		d3dSprite->Draw(menuTexture, &menuSprites[13], NULL, &pos, 0xFFFFFFFF);
		// OFF
		if(!menuvSync)
		{
			pos.x += menuSprites[13].right + 10;
			d3dSprite->Draw(menuTexture, &menuSprites[16], NULL, &pos, 0xFFFFFFFF);
		}
		// ON
		else
		{
			pos.x += menuSprites[13].right + 10 + 14;
			d3dSprite->Draw(menuTexture, &menuSprites[15], NULL, &pos, 0xFFFFFFFF);
		}

		// ACCEPT
		pos.x = (640 - menuSprites[14].right) / 2.0f;
		pos.y = (float)menuLocations[4];
		// Set location for menu selection marker
		if(curMenu == 3)
		{
			selectionLeft = (int)pos.x - 52;
			selectionRight = (int)pos.x + menuSprites[14].right + 10;
		}
		d3dSprite->Draw(menuTexture, &menuSprites[14], NULL, &pos, 0xFFFFFFFF);

		// Draw pentagram icon
		RECT sLoc;
		sLoc.left = 42 * (curMenuFrame % 4);
		sLoc.top = 160 + (42 * (int)(curMenuFrame / 4));
		sLoc.right = sLoc.left + 42;
		sLoc.bottom = sLoc.top + 42;
		curMenuFrame++;
		if(curMenuFrame > 7) curMenuFrame = 0;

		pos.x = (float)selectionLeft;
		pos.y = menuLocations[curMenu + 1] - 5.0f;
		d3dSprite->Draw(menuTexture,&sLoc,NULL,&pos,0xFFFFFFFF);
		pos.x = (float)selectionRight;
		d3dSprite->Draw(menuTexture,&sLoc,NULL,&pos,0xFFFFFFFF);

		// End sprite drawing
		d3dSprite->End();
	}

	// And... End scene
	if(d3d9Device->EndScene() != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::Present","Failed to end scene");
		return false;
	}

	// Present everthing!
	HRESULT hr = d3d9Device->Present( NULL, NULL, NULL, NULL );
	// Device lost
	if(hr == D3DERR_DEVICELOST)
	{
		debugMessage(1, "IDirectDrawWrapper::Present","Device lost");
		// Attempt to reinit device
		return ReinitDevice();
	}
	else if(hr != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::Present", "Failed to present scene");
		return false;
	}

	return true;
}

/* Helper function for handling menu key press
 * vKey - key pressed
 */
BOOL IDirectDrawWrapper::MenuKey(WPARAM vKey)
{
	if(vKey == VK_OEM_3)
	{
		if(inMenu == TRUE)
			// No longer in the menu
			inMenu = FALSE;
		else
		{
			curMenu = 0;
            
			// Init to current settings
			menuWindowed = isWindowed;
			menuvSync = vSync;
			menuWindowedResolution = 0;
			menuFullscreenResolution = 0;
			for(int i = 0; i < windowedResolutionCount; i++)
			{
				if(windowedResolutions[i].x == displayWidthWindowed && windowedResolutions[i].y == displayHeightWindowed)
				{
					menuWindowedResolution = i;
					break;
				}
			}
			menuFullscreenResolution = 0;
			for(int i = 0; i < fullscreenResolutionCount; i++)
			{
				if(fullscreenResolutions[i].x == displayWidthFullscreen && fullscreenResolutions[i].y == displayHeightFullscreen && fullscreenRefreshes[i] == refreshRate)
				{
					menuFullscreenResolution = i;
					break;
				}
			}
			// We are in the menu
			inMenu = TRUE;
		}
		Present();
	}
	else if(vKey == VK_ESCAPE)
	{
		inMenu = FALSE;
		Present();
	}
	else if(vKey == VK_DOWN)
	{
		curMenu++;
		if(curMenu > 3) curMenu = 0;
		Present();
	}
	else if(vKey == VK_UP)
	{
		curMenu--;
		if(curMenu < 0) curMenu = 3;
		Present();
	}
	else if(vKey == VK_RIGHT)
	{
		if(curMenu == 0)
		{
			if(menuWindowed)
			{
				menuWindowedResolution++;
				if(menuWindowedResolution >= windowedResolutionCount) menuWindowedResolution = 0;
			}
			else
			{
				menuFullscreenResolution++;
				if(menuFullscreenResolution >= fullscreenResolutionCount) menuFullscreenResolution = 0;
			}
		}
		else if(curMenu == 1)
		{
			if(menuWindowed) 
				menuWindowed = false;
			else
				menuWindowed = true;
		}
		else if(curMenu == 2)
		{
			if(menuvSync)
				menuvSync = false;
			else
				menuvSync = true;
		}
		Present();
	}
	else if(vKey == VK_LEFT)
	{
		if(curMenu == 0)
		{
			if(menuWindowed)
			{
				menuWindowedResolution--;
				if(menuWindowedResolution < 0) menuWindowedResolution = windowedResolutionCount - 1;
			}
			else
			{
				menuFullscreenResolution--;
				if(menuFullscreenResolution < 0) menuFullscreenResolution = fullscreenResolutionCount - 1;
			}
		}
		else if(curMenu == 1)
		{
			if(menuWindowed) 
				menuWindowed = false;
			else
				menuWindowed = true;
		}
		else if(curMenu == 2)
		{
			if(menuvSync)
				menuvSync = false;
			else
				menuvSync = true;
		}
		Present();
	}
	else if(vKey == VK_RETURN)
	{
		inMenu = false;

		// Changing from full screen to window mode
		if(!isWindowed && menuWindowed)
		{
			// Go back to desktop resolution first so adjust window won't fail
			presParams.Windowed = true;
			d3d9Device->Reset(&presParams);
		}
		isWindowed = menuWindowed;
		if(menuWindowed)
		{
			displayWidth = windowedResolutions[menuWindowedResolution].x;
			displayHeight = windowedResolutions[menuWindowedResolution].y;
			displayWidthWindowed = displayWidth;
			displayHeightWindowed = displayHeight;
		}
		else
		{
			displayWidth = fullscreenResolutions[menuFullscreenResolution].x;
			displayHeight = fullscreenResolutions[menuFullscreenResolution].y;
			refreshRate = fullscreenRefreshes[menuFullscreenResolution];
			displayWidthFullscreen = displayWidth;
			displayHeightFullscreen = displayHeight;
		}
		vSync = menuvSync;
		AdjustWindow();
		CreateD3DDevice();
		CreateSurfaceTexture();
		Present();

		// Write changes to ini file
		wchar_t curPath[MAX_PATH];
		wchar_t filename[MAX_PATH];
		wchar_t temp[1024];

		// Get current working directory
		GetCurrentDirectory(MAX_PATH, curPath);
		wsprintf(filename, TEXT("%s\\ddraw_settings.ini"), curPath);	
		temp[0] = '\0';
		wsprintf(temp, TEXT("%dx%d"), displayWidthWindowed, displayHeightWindowed);
		WritePrivateProfileString(TEXT("video"), TEXT("windowedResolution"), temp, filename);
		temp[0] = '\0';
		wsprintf(temp, TEXT("%dx%d"), displayWidthFullscreen, displayHeightFullscreen);
		WritePrivateProfileString(TEXT("video"), TEXT("fullscreenResolution"), temp, filename);
		temp[0] = '\0';
		wsprintf(temp, TEXT("%d"), refreshRate);
		WritePrivateProfileString(TEXT("video"), TEXT("refresh"), temp, filename);
		temp[0] = '\0';
		wsprintf(temp, TEXT("%d"), isWindowed ? 0 : 1);
		WritePrivateProfileString(TEXT("video"), TEXT("fullscreen"), temp, filename);
		temp[0] = '\0';
		wsprintf(temp, TEXT("%d"), vSync ? 1 : 0);
		WritePrivateProfileString(TEXT("video"), TEXT("vsync"), temp, filename);
	}

	return inMenu;
}

/* Helper function for toggling fullscreen
 *
 */ 
void IDirectDrawWrapper::ToggleFullscreen()
{
    // If windowed
	if(isWindowed)
	{
        // Switch to full screen
		isWindowed = false;
		displayWidth = displayWidthFullscreen;
		displayHeight = displayHeightFullscreen;
	}
	else
	{
        // Switch to windowed
		isWindowed = true;
		displayWidth = displayWidthWindowed;
		displayHeight = displayHeightWindowed;
		// Changing from full screen to window mode
		// Go back to desktop resolution first so adjust window won't fail
		presParams.Windowed = true;
		d3d9Device->Reset(&presParams);
	}
    // Adjust window
	AdjustWindow();
    // Recreated D3D objects
	CreateD3DDevice();
	CreateSurfaceTexture();

	Present();
}

/* Helper function for taking a screenshot
 *
 */ 
void IDirectDrawWrapper::DoSnapshot()
{
	wchar_t curPath[MAX_PATH];

	// Get current working directory
	GetCurrentDirectory(MAX_PATH, curPath);
	
	// Create filename first part "Diablo_YYYYMMDD_HHMMSS.png"
	wchar_t filename[MAX_PATH];
	SYSTEMTIME sysTime;
	GetSystemTime(&sysTime);
	wchar_t title[1024];
	GetWindowText(hWnd, title, 1024);
	wsprintf(filename, TEXT("%s\\%s_%.4d%.2d%.2d_%.2d%.2d%.2d.png"), curPath, title, sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	
	// Make sure it doesn't already exist
	WIN32_FIND_DATA findData;
	HANDLE findHandle = FindFirstFile(filename, &findData);
	int curFileNum = 1;
	while(findHandle != INVALID_HANDLE_VALUE)
	{
		// Close find
		FindClose(findHandle);
		// Add (num) to end of filename
		wsprintf(filename, TEXT("%s\\Diablo_%.4d%.2d%.2d_%.2d%.2d%.2d(%d).png"), curPath, sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond, curFileNum);
		// Increment current file
		curFileNum++;
		// Check if this exists
		findHandle = FindFirstFile(filename, &findData);
	}

    // Save texture to file
	if(D3DXSaveTextureToFile(filename, D3DXIFF_PNG, surfaceTexture, NULL) != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::DoSnapshot", "Error saving texture to file.");
		return;
	}

	debugMessage(2, "IDirectDrawWrapper::DoSnapshot", "Saved Screenshot");
}

/* Helper function for adjusting the window position
 *
 */ 
void IDirectDrawWrapper::AdjustWindow()
{
	// If we don't yet have the window quit without action
	if(hWnd == NULL) return;

    // window mode
	if(isWindowed)
	{
		// Window with border/caption
		SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE | WS_CAPTION);
		// Set window size
		SetWindowPos(hWnd, NULL, 0, 0, displayWidth, displayHeight, SWP_NOMOVE | SWP_NOZORDER);
		// Adjust for window decoration to ensure client area matches display size
		RECT tempRect;
		GetClientRect(hWnd, &tempRect);
		tempRect.right = (displayWidth - tempRect.right) + displayWidth;
		tempRect.bottom = (displayHeight - tempRect.bottom) + displayHeight;
		// Move window to last position and adjust size
		SetWindowPos(hWnd, NULL, lastPosition.x, lastPosition.y, tempRect.right, tempRect.bottom, SWP_NOZORDER);
	}
	else
	{
		// Window borderless and fullscreen size
		SetWindowLong(hWnd, GWL_STYLE, WS_VISIBLE);
		// Set full size
		SetWindowPos(hWnd, NULL, 0, 0, displayWidth, displayHeight, SWP_NOZORDER);
	}
	debugMessage(2, "IDirectDrawWrapper::AdjustWindow", "Complete");
}

/* Helper function to create/recreate D3D device
 *
 */ 
bool IDirectDrawWrapper::CreateD3DDevice()
{
	// Release existing vertex buffer
	if(vertexBuffer != NULL)
	{
		vertexBuffer->Release();
		vertexBuffer = NULL;
	}

	// Release existing surface texture
	if(surfaceTexture != NULL)
	{
		surfaceTexture->Release();
		surfaceTexture = NULL;
	}

    // Release sprite
	if(d3dSprite != NULL)
	{
		d3dSprite->Release();
		d3dSprite = NULL;
	}

    // Release texture
	if(menuTexture != NULL)
	{
		menuTexture ->Release();
		menuTexture  = NULL;
	}

	// Release existing d3d9device
	if(d3d9Device != NULL)
	{
		if(d3d9Device->Release() != D3D_OK)
		{
			debugMessage(0, "IDirectDrawWrapper::createD3DDevice","Unable to release Direct3D9 device");
			return false;
		}
		d3d9Device = NULL;
	}

	// Check device caps to make sure it supports dynamic textures
	D3DCAPS9 d3dcaps;
	ZeroMemory(&d3dcaps, sizeof(D3DCAPS9));
	if(d3d9Object->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dcaps) != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::createD3DDevice","Unable to retrieve device-specific information about the device");
		return false;
	}

	// Is dynamic textures flag set?
	if((d3dcaps.Caps2 & D3DCAPS2_DYNAMICTEXTURES) == 0)
	{
		// No dynamic textures
		debugMessage(0, "IDirectDrawWrapper::createD3DDevice","Device does not support dynamic textures");
		MessageBox(NULL, TEXT("This patch requires a d3d9 driver that supports dynamic textures."), TEXT("Driver Doesn't Meet Requirements"), MB_OK);
		return false;
	}
	
	ZeroMemory(&presParams,sizeof(presParams));
	// Set display window
	presParams.hDeviceWindow = hWnd;

	// Enumerate modes for format XRGB
	UINT modeCount = d3d9Object->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8);

	fullscreenResolutionCount = 0;
	if(fullscreenResolutions != NULL) delete fullscreenResolutions;
	fullscreenResolutions = new POINT[modeCount];
	if(fullscreenRefreshes != NULL) delete fullscreenRefreshes;
	fullscreenRefreshes = new UINT[modeCount];

	D3DDISPLAYMODE d3ddispmode;
	D3DDISPLAYMODE set_d3ddispmode;
	bool modeFound = false;
	// Loop through all modes looking for our requested resolution
	for(UINT i = 0; i < modeCount; i++)
	{
		// Get display modes here
		ZeroMemory(&d3ddispmode, sizeof(D3DDISPLAYMODE));
		if(d3d9Object->EnumAdapterModes(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8, i, &d3ddispmode) != D3D_OK)
		{
			debugMessage(0, "IDirectDrawWrapper::createD3DDevice","EnumAdapterModes failed");
			MessageBox(NULL, TEXT("Couldn't find full screen mode for requested format."), TEXT("Error Setting Mode"), MB_OK);
			return false;		
		}
		if(d3ddispmode.Width == displayWidth &&  d3ddispmode.Height == displayHeight && d3ddispmode.RefreshRate == refreshRate)
		{
			// Found a match
			modeFound = true;
			memcpy(&set_d3ddispmode, &d3ddispmode, sizeof(D3DDISPLAYMODE));
			menuFullscreenResolution = fullscreenResolutionCount;
		}

		// No modes above maximum size
		if(d3ddispmode.Width < 1920 && d3ddispmode.Height < 1440) {
			fullscreenResolutions[fullscreenResolutionCount].x = d3ddispmode.Width;
			fullscreenResolutions[fullscreenResolutionCount].y = d3ddispmode.Height;
			fullscreenRefreshes[fullscreenResolutionCount] = d3ddispmode.RefreshRate;
			fullscreenResolutionCount++;
		}
	}

	// Set parameters for the current display mode
	if(isWindowed)
	{
		// Window mode
		presParams.Windowed = TRUE;
		// Swap discard
		presParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
		// Unknown format
		presParams.BackBufferFormat = D3DFMT_UNKNOWN;
	}
	else
	{
		// No mode found
		if(!modeFound)
		{
			debugMessage(0, "IDirectDrawWrapper::createD3DDevice","Failed to find compatible fullscreen display mode");
			MessageBox(NULL, TEXT("Couldn't find full screen mode for requested format."), TEXT("Error Setting Mode"), MB_OK);
			return false;
		}
		// Fullscreen
		presParams.Windowed = FALSE;
		// width/height
		presParams.BackBufferWidth = set_d3ddispmode.Width;
		presParams.BackBufferHeight = set_d3ddispmode.Height;
		// Discard swap
		presParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
		// Display mode fullscreen format
		presParams.BackBufferFormat = set_d3ddispmode.Format;
		// Display mode refresh
		presParams.FullScreen_RefreshRateInHz = set_d3ddispmode.RefreshRate;
	}

	// Set vsync
	if(vSync)
	{
		presParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE; //VSYNC disabled
	}
	else
	{
		presParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //VSYNC enabled
	}

	// D3DCREATE_NOWINDOWCHANGES possible for alt+tab and mouse leaving window
	// create d3d device with hardware vertex processing if it's available
	if(d3dcaps.VertexProcessingCaps != 0)
	{
		if(d3d9Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &presParams, &d3d9Device) != D3D_OK)
		{
			debugMessage(0, "IDirectDrawWrapper::createD3DDevice","Failed to create Direct3D9 device");
			MessageBox(NULL, TEXT("Failed to create Direct3D9 device."), TEXT("Direct3D9 Device Error"), MB_OK);
			return false;
		}
	}
	else
	{
		if(d3d9Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &presParams, &d3d9Device) != D3D_OK)
		{
			debugMessage(0, "IDirectDrawWrapper::createD3DDevice","Failed to create Direct3D9 device");
			MessageBox(NULL, TEXT("Failed to create Direct3D9 device."), TEXT("Direct3D9 Device Error"), MB_OK);
			return false;
		}
	}

	// Create menu sprite
	if(D3DXCreateSprite(d3d9Device, &d3dSprite) != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::createD3DDevice","Failed to create Direct3DX9 sprite");
		MessageBox(NULL, TEXT("Failed to create Direct3DX9 sprite."), TEXT("Direct3DX9 Error"), MB_OK);
		return false;
	}

	debugMessage(2, "IDirectDrawWrapper::createD3DDevice", "Create D3D9 Object");
	
    // Success
	return true;
}

/* Helper function to create surface texture
 *
 */
bool IDirectDrawWrapper::CreateSurfaceTexture()
{
	// Release existing vertex buffer
	if(vertexBuffer != NULL)
	{
		vertexBuffer->Release();
		vertexBuffer = NULL;
	}

	// Release existing surface texture
	if(surfaceTexture != NULL)
	{
		surfaceTexture->Release();
		surfaceTexture = NULL;
	}

	if(menuTexture != NULL)
	{
		menuTexture->Release();
		menuTexture = NULL;
	}

	// Create managed dynamic texture to allow locking(debug as video size but change to display size)
	if(d3d9Device->CreateTexture(displayModeWidth, displayModeHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &surfaceTexture, NULL) != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::CreateSurfaceTexture","Unable to create surface texture");
		return false;
	}

	// Set vertex shader
	if(d3d9Device->SetVertexShader(NULL) != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::CreateSurfaceTexture","Unable to set vertex shader");
		return false;
	}
	// Set fv format
	if(d3d9Device->SetFVF(D3DFVF_TLVERTEX) != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::CreateSurfaceTexture","Unable to set the current vertex stream format");
		return false;
	}

	// Create vertex buffer
	if(d3d9Device->CreateVertexBuffer(sizeof(TLVERTEX) * 4, NULL, D3DFVF_TLVERTEX, D3DPOOL_MANAGED, &vertexBuffer, NULL) != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::CreateSurfaceTexture","Unable to create vertex buffer");
		return false;
	}
	
	// Set stream source
	if(d3d9Device->SetStreamSource(0, vertexBuffer, 0, sizeof(TLVERTEX)) != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::CreateSurfaceTexture","Unable to set vertex buffer stream source");
		return false;
	}
	// Set render states(no lighting)
	if(d3d9Device->SetRenderState(D3DRS_LIGHTING, FALSE) != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::CreateSurfaceTexture","Unable to set device render state(no lighting)");
		return false;
	}
	
	// Query the device to see if it supports anything other than point filtering
	if(d3d9Object->CheckDeviceFormat(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DUSAGE_QUERY_FILTER, D3DRTYPE_TEXTURE, D3DFMT_X8R8G8B8) == D3D_OK)
	{
		// Set scale mode to linear
		if(d3d9Device->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR) != DD_OK)
		{
			debugMessage(0, "IDirectDrawWrapper::CreateSurfaceTexture","Failed to set D3D device to LINEAR sampling");
			return false;
		}
	}
	else
	{
			debugMessage(1, "IDirectDrawWrapper::CreateSurfaceTexture","Device doesn't support linear sampling");
	}

	// Setup verticies (0,0,currentWidth,currentHeight)
	TLVERTEX* vertices;
	// Lock
	if(vertexBuffer->Lock(0, 0, (void**)&vertices, NULL) != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::CreateSurfaceTexture","Unable to lock vertex buffer");
		return false;
	}

	// Set vertex points
	// 0, 0
	vertices[0].x = -0.5f;
	vertices[0].y = -0.5f;
	vertices[0].z = 0.0f;
	vertices[0].rhw = 1.0f;
	vertices[0].u = 0.0f;
	vertices[0].v = 0.0f;

	// currentWidth, 0
	vertices[1].x = (float)displayWidth - 0.5f;
	vertices[1].y = -0.5f;
	vertices[1].z = 0.0f;
	vertices[1].rhw = 1.0f;
	vertices[1].u = 1.0f;
	vertices[1].v = 0.0f;

	// currentWidth, scaledHeight
	vertices[2].x = (float) displayWidth - 0.5f;
	vertices[2].y = (float) displayHeight - 0.5f;
	vertices[2].z = 0.0f;
	vertices[2].rhw = 1.0f;
	vertices[2].u = 1.0f;
	vertices[2].v = 1.0f;

	// 0, currentHeight
	vertices[3].x = -0.5f;
	vertices[3].y = (float) displayHeight - 0.5f;
	vertices[3].z = 0.0f;
	vertices[3].rhw = 1.0f;
	vertices[3].u = 0.0f;
	vertices[3].v = 1.0f;

    // Unlcok vertex buffer
	if(vertexBuffer->Unlock() != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::CreateSurfaceTexture","Unable to unlock vertex buffer");
		return false;
	}

	// Create menu text texture
	HRESULT hr = D3DXCreateTextureFromResource(d3d9Device, hModule, MAKEINTRESOURCE(SPRITEDATA), &menuTexture);
	if(hr != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::CreateSurfaceTexture","Unable to create texture from resource.");
		return false;
	}

	debugMessage(2, "IDirectDrawWrapper::CreateSurfaceTexture", "D3D9 Texture Created");
	return true;
}

// Helper function to reinitialize device
bool IDirectDrawWrapper::ReinitDevice()
{
	// Release existing vertex buffer
	if(vertexBuffer != NULL)
	{
		vertexBuffer->Release();
		vertexBuffer = NULL;
	}

	// Release existing surface texture
	if(surfaceTexture != NULL)
	{
		surfaceTexture->Release();
		surfaceTexture = NULL;
	}

    // Release sprite
	if(d3dSprite != NULL)
	{
		d3dSprite->Release();
		d3dSprite = NULL;
	}

    // Release texture
	if(menuTexture != NULL)
	{
		menuTexture->Release();
		menuTexture = NULL;
	}

	// Attempt to reset the device
	if(d3d9Device->Reset(&presParams) != D3D_OK)
	{
		debugMessage(0, "IDirectDrawWrapper::ReinitDevice","Failed to reset Direct3D9 device");
		MessageBox(NULL, TEXT("Failed to reset Direct3D9 device."), TEXT("Direct3D9 Error"), MB_OK);
		return false;
	}

	D3DXCreateSprite(d3d9Device, &d3dSprite);

	debugMessage(2, "IDirectDrawWrapper::ReinitDevice", "Reset device, now create texture");

	// Recreate the surface texutre
	return CreateSurfaceTexture();
}

