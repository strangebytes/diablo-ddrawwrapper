#define VC_EXTRALEAN
#include <Windows.h>
#include <initguid.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <ddraw.h>

#ifndef H_DDW
#define H_DDW

// Global function def
void debugMessage(int, char*, char*);

// Forward class declarations
class FAR IDirectDrawWrapper;
class FAR IDirectDrawPaletteWrapper;
class FAR IDirectDrawClipperWrapper;
class FAR IDirectDrawSurfaceWrapper;
class FAR IDirectDrawColorControlWrapper;
class FAR IDirectDrawGammaControlWrapper;

// Custom vertex format
const DWORD D3DFVF_TLVERTEX = D3DFVF_XYZRHW | D3DFVF_TEX1;

// Custom vertex
struct TLVERTEX
{
	float x;
	float y;
	float z;
	float rhw;
	float u;
	float v;
};

/*
 * IDirectDrawWrapper Class
 */
class FAR IDirectDrawWrapper : public IDirectDraw
{
// Implemented interfaces
public:
	/*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID riid, LPVOID FAR * ppvObj);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	/*** IDirectDraw methods ***/
	HRESULT __stdcall Compact();
    HRESULT __stdcall CreateClipper(DWORD dwFlags, LPDIRECTDRAWCLIPPER FAR *lplpDDClipper, IUnknown FAR *pUnkOuter);
	HRESULT __stdcall CreatePalette(DWORD dwFlags, LPPALETTEENTRY lpDDColorArray, LPDIRECTDRAWPALETTE FAR *lplpDDPalette, IUnknown FAR *pUnkOuter);
	HRESULT __stdcall CreateSurface(LPDDSURFACEDESC lpDDSurfaceDes, LPDIRECTDRAWSURFACE FAR *lplpDDSurface, IUnknown FAR *pUnkOuter);
    HRESULT __stdcall DuplicateSurface(LPDIRECTDRAWSURFACE lpDDSurface, LPDIRECTDRAWSURFACE FAR *lplpDupDDSurface);
    HRESULT __stdcall EnumDisplayModes(DWORD dwFlags, LPDDSURFACEDESC lpDDSurfaceDesc, LPVOID lpContext, LPDDENUMMODESCALLBACK lpEnumModesCallback);
    HRESULT __stdcall EnumSurfaces(DWORD dwFlags, LPDDSURFACEDESC lpDDSD, LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpEnumSurfacesCallback);
	HRESULT __stdcall FlipToGDISurface();
	HRESULT __stdcall GetCaps(LPDDCAPS lpDDDriverCaps, LPDDCAPS lpDDHELCaps);
	HRESULT __stdcall GetDisplayMode(LPDDSURFACEDESC lpDDSurfaceDesc);
    HRESULT __stdcall GetFourCCCodes(LPDWORD lpNumCodes, LPDWORD lpCodes);
    HRESULT __stdcall GetGDISurface(LPDIRECTDRAWSURFACE FAR *lplpGDIDDSSurface);
    HRESULT __stdcall GetMonitorFrequency(LPDWORD lpdwFrequency);
    HRESULT __stdcall GetScanLine(LPDWORD lpdwScanLine);
    HRESULT __stdcall GetVerticalBlankStatus(LPBOOL lpbIsInVB);
    HRESULT __stdcall Initialize(GUID FAR *lpGUID);
    HRESULT __stdcall RestoreDisplayMode();
	HRESULT __stdcall SetCooperativeLevel(HWND hWnd, DWORD dwFlags);
	HRESULT __stdcall SetDisplayMode(DWORD dwWidth, DWORD dwHeight, DWORD dwBPP);
	// HRESULT __stdcall SetDisplayMode(DWORD dwWidth, DWORD dwHeight, DWORD dwBPP, DWORD dwRefreshRate, DWORD dwFlags);
	HRESULT __stdcall WaitForVerticalBlank(DWORD dwFlags,HANDLE hEvent);
	/*** Added in the v2 interface ***/
	HRESULT __stdcall GetAvailableVideoMem(LPDDSCAPS2 lpDDSCaps2, LPDWORD lpdwTotal, LPDWORD lpdwFree);
	/*** Added in the V4 Interface ***/
	HRESULT __stdcall EvaluateMode(DWORD dwFlags, DWORD *pSecondsUntilTimeout);
	HRESULT __stdcall GetDeviceIdentifier(LPDDDEVICEIDENTIFIER2 lpdddi, DWORD dwFlags);
	HRESULT __stdcall GetSurfaceFromDC(HDC hdc, LPDIRECTDRAWSURFACE7 *lpDDS);
	HRESULT __stdcall RestoreAllSurfaces();
	HRESULT __stdcall StartModeTest(LPSIZE lpModesToTest, DWORD dwNumEntries, DWORD dwFlags);
	HRESULT __stdcall TestCooperativeLevel();

	// Constructor/destructor
	IDirectDrawWrapper();
	~IDirectDrawWrapper();

	// Helper functions
	HRESULT WrapperInitialize(WNDPROC wp, HMODULE hMod);
	HRESULT Present();
	BOOL MenuKey(WPARAM vKey);
	void DoSnapshot();
	void ToggleFullscreen();

	// Display window handle
	HWND hWnd;
	WNDPROC lpPrevWndFunc;
	WNDPROC WndProc;
	HMODULE hModule;

	// Current display mode
	bool isWindowed;

	// Application display mode
	DWORD displayModeWidth;
	DWORD displayModeHeight;

	// Display resolution
	UINT displayWidth;
	UINT displayHeight;

	// Saved display resolutions for fullscreen and windowed
	UINT displayWidthWindowed;
	UINT displayHeightWindowed;
	UINT displayWidthFullscreen;
	UINT displayHeightFullscreen;

// Custom functions and variables
private:
	// Helper function to set window mode to match display mode
	void AdjustWindow();
	bool CreateD3DDevice();
	bool CreateSurfaceTexture();
	bool ReinitDevice();
	bool CheckD3DFailure(HRESULT hr, char *location, char *message);

	IDirectDrawSurfaceWrapper *lpAttachedSurface;

	// Reference count
	ULONG ReferenceCount;

	// Direct3D9 Objects
	LPDIRECT3D9 d3d9Object;
	LPDIRECT3DDEVICE9 d3d9Device;
	D3DPRESENT_PARAMETERS presParams;
	LPDIRECT3DTEXTURE9 surfaceTexture;
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

	LPD3DXSPRITE d3dSprite;
	LPDIRECT3DTEXTURE9 menuTexture;
	int curMenuFrame;
	int menuLocations[5];
	RECT menuSprites[18];

    // Flags and settings
	BOOL inMenu;
	int curMenu;
	int menuWindowedResolution;
	int windowedResolutionCount;
	POINT* windowedResolutions;
	int menuFullscreenResolution;
	int fullscreenResolutionCount;
	POINT* fullscreenResolutions;
	UINT* fullscreenRefreshes;

	bool menuWindowed;
	bool menuvSync;

	// Last window position
	POINT lastPosition;
	// Vsync enabled
	bool vSync;
	// Refresh rate for fullscreen
	UINT refreshRate;
};

/*
 * IDirectDrawPalette Wrapper
 */
class FAR IDirectDrawPaletteWrapper : public IDirectDrawPalette
{
// Implemented interfaces
public:
	/*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID riid, LPVOID FAR * ppvObj);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	/*** IDirectDrawPalette methods ***/
	HRESULT __stdcall GetCaps(LPDWORD lpdwCaps);
	HRESULT __stdcall GetEntries(DWORD dwFlags, DWORD dwBase, DWORD dwNumEntries, LPPALETTEENTRY lpEntries);
	HRESULT __stdcall Initialize(LPDIRECTDRAW lpDDW, DWORD dwFlags, LPPALETTEENTRY lpDDColorTable);
	HRESULT __stdcall SetEntries(DWORD dwFlags,DWORD dwStartingEntry,DWORD dwCount, LPPALETTEENTRY lpEntries);
	
	// Constructor/destructor
	IDirectDrawPaletteWrapper();
	~IDirectDrawPaletteWrapper();
	// Helper functions
	HRESULT WrapperInitialize(DWORD dwFlags, LPPALETTEENTRY lpDDColorArray, LPDIRECTDRAWPALETTE FAR *lplpDDPalette);

	// Rgb translated palette
	UINT32 *rgbPalette;
	// Raw palette data
	LPPALETTEENTRY rawPalette;

// Custom functions and variables
private:
	// Reference count
	ULONG ReferenceCount;
	
	// Palette flags
	DWORD paletteCaps;

	// Number of palette entries
	int entryCount;
	// Raw palette has alpha data
	bool hasAlpha;
};

/*
 * IDirectDrawClipper Wrapper
 */
class FAR IDirectDrawClipperWrapper : public IDirectDrawClipper
{
// Implemented interfaces
public:
	/*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID riid, LPVOID FAR * ppvObj);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	/*** IDirectDrawClipper methods ***/
	HRESULT __stdcall GetClipList(LPRECT lpRect, LPRGNDATA lpClipList, LPDWORD lpdwSize);
	HRESULT __stdcall GetHWnd(HWND FAR *lphWnd);
	HRESULT __stdcall Initialize(LPDIRECTDRAW lpDD, DWORD dwFlags);
	HRESULT __stdcall IsClipListChanged(BOOL FAR *lpbChanged);
	HRESULT __stdcall SetClipList(LPRGNDATA lpClipList, DWORD dwFlags);
	HRESULT __stdcall SetHWnd(DWORD dwFlags, HWND hWnd);
	
	// Constructor/destructor
	IDirectDrawClipperWrapper();
	~IDirectDrawClipperWrapper();
	// Helper functions
	HRESULT WrapperInitialize(DWORD dwFlags);

// Custom functions and variables
private:
	// Reference count
	ULONG ReferenceCount;
	// Associated hwnd
	bool hasHwnd;
	HWND hWnd;
};

/*
 * IDirectDrawSurface Wrapper
 */
class FAR IDirectDrawSurfaceWrapper : public IDirectDrawSurface
{
// Implemented interfaces
public:
	/*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID riid, LPVOID FAR * ppvObj);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	/*** IDirectDrawSurface methods ***/
	HRESULT __stdcall AddAttachedSurface(LPDIRECTDRAWSURFACE lpDDSurface);
    HRESULT __stdcall AddOverlayDirtyRect(LPRECT lpRect);
    HRESULT __stdcall Blt(LPRECT lpDestRect,LPDIRECTDRAWSURFACE lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx);
    HRESULT __stdcall BltBatch(LPDDBLTBATCH lpDDBltBatch, DWORD dwCount, DWORD dwFlags);
    HRESULT __stdcall BltFast(DWORD dwX, DWORD dwY, LPDIRECTDRAWSURFACE lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags);
    HRESULT __stdcall DeleteAttachedSurface(DWORD dwFlags,LPDIRECTDRAWSURFACE lpDDSAttachedSurface);
    HRESULT __stdcall EnumAttachedSurfaces(LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpEnumSurfacesCallback);
    HRESULT __stdcall EnumOverlayZOrders(DWORD dwFlags, LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpfnCallback);
    HRESULT __stdcall Flip(LPDIRECTDRAWSURFACE lpDDSurfaceTargetOverride, DWORD dwFlags);
    HRESULT __stdcall GetAttachedSurface(LPDDSCAPS lpDDSCaps, LPDIRECTDRAWSURFACE FAR *lplpDDAttachedSurface);
    HRESULT __stdcall GetBltStatus(DWORD dwFlags);
	HRESULT __stdcall GetCaps(LPDDSCAPS lpDDSCaps);
    HRESULT __stdcall GetClipper(LPDIRECTDRAWCLIPPER FAR *lplpDDClipper);
    HRESULT __stdcall GetColorKey(DWORD dwFlags, LPDDCOLORKEY lpDDColorKey);
    HRESULT __stdcall GetDC(HDC FAR *lphDC);
    HRESULT __stdcall GetFlipStatus(DWORD dwFlags);
    HRESULT __stdcall GetOverlayPosition(LPLONG lplX, LPLONG lplY);
    HRESULT __stdcall GetPalette(LPDIRECTDRAWPALETTE FAR *lplpDDPalette);
    HRESULT __stdcall GetPixelFormat(LPDDPIXELFORMAT lpDDPixelFormat);
    HRESULT __stdcall GetSurfaceDesc(LPDDSURFACEDESC lpDDSurfaceDesc);
    HRESULT __stdcall Initialize(LPDIRECTDRAW lpDD, LPDDSURFACEDESC lpDDSurfaceDesc);
    HRESULT __stdcall IsLost();
	HRESULT __stdcall Lock(LPRECT lpDestRect, LPDDSURFACEDESC lpDDSurfaceDesc, DWORD dwFlags, HANDLE hEvent);
    HRESULT __stdcall ReleaseDC(HDC hDC);
    HRESULT __stdcall Restore();
    HRESULT __stdcall SetClipper(LPDIRECTDRAWCLIPPER lpDDClipper);
    HRESULT __stdcall SetColorKey(DWORD dwFlags, LPDDCOLORKEY lpDDColorKey);
    HRESULT __stdcall SetOverlayPosition(LONG lX, LONG lY);
	HRESULT __stdcall SetPalette(LPDIRECTDRAWPALETTE lpDDPalette);
	HRESULT __stdcall Unlock(LPVOID lpRect);
	HRESULT __stdcall Unlock(LPRECT lpRect);
    HRESULT __stdcall UpdateOverlay(LPRECT lpSrcRect, LPDIRECTDRAWSURFACE lpDDDestSurface, LPRECT lpDestRect, DWORD dwFlags, LPDDOVERLAYFX lpDDOverlayFx);
    HRESULT __stdcall UpdateOverlayDisplay(DWORD dwFlags);
    HRESULT __stdcall UpdateOverlayZOrder(DWORD dwFlags, LPDIRECTDRAWSURFACE lpDDSReference);
	/*** Added in the v2 interface ***/
	HRESULT __stdcall GetDDInterface(LPVOID FAR *lplpDD);
	HRESULT __stdcall PageLock(DWORD dwFlags);
	HRESULT __stdcall PageUnlock(DWORD dwFlags);
	/*** Added in the v3 interface ***/
	HRESULT __stdcall SetSurfaceDesc(LPDDSURFACEDESC2 lpDDsd2, DWORD dwFlags);
	/*** Added in the v4 interface ***/
    HRESULT __stdcall ChangeUniquenessValue();
    HRESULT __stdcall FreePrivateData(REFGUID guidTag);
    HRESULT __stdcall GetPrivateData(REFGUID guidTag, LPVOID lpBuffer, LPDWORD lpcbBufferSize);
    HRESULT __stdcall GetUniquenessValue(LPDWORD lpValue);
	HRESULT __stdcall SetPrivateData(REFGUID guidTag, LPVOID lpData, DWORD cbSize, DWORD dwFlags);
	/*** Texture7 methods ***/
    HRESULT __stdcall SetPriority(DWORD dwPriority);
    HRESULT __stdcall GetPriority(LPDWORD lpdwPriority);
    HRESULT __stdcall SetLOD(LPDWORD lpdwMaxLOD);
    HRESULT __stdcall GetLOD(DWORD dwMaxLOD);

	// Constructor/destructor
	IDirectDrawSurfaceWrapper(IDirectDrawWrapper* parent);
	~IDirectDrawSurfaceWrapper();

	// Helper functions
	HRESULT WrapperInitialize(LPDDSURFACEDESC lpDDSurfaceDesc, DWORD displayModeWidth, DWORD displayModeHeight, DWORD displayWidth, DWORD displayHeight);
	BOOL ReInitialize(DWORD displayWidth, DWORD displayHeight);

	// RGB video memory
	UINT32 *rgbVideoMem;

//Custom functions and variables
private:
	// Reference count
	ULONG ReferenceCount;
	// Directdraw object that created this surface
	IDirectDrawWrapper *ddrawParent;
	// Associated palette
	IDirectDrawPaletteWrapper *attachedPalette;
	
	// Surface description
	DDSURFACEDESC surfaceDesc;
	LONG surfaceWidth;
	LONG surfaceHeight;

	// Color keys(DDCKEY_DESTBLT, DDCKEY_DESTOVERLAY, DDCKEY_SRCBLT, DDCKEY_SRCOVERLAY)
	DDCOLORKEY colorKeys[4];
	LONG overlayX, overlayY;

	// Virtual video memory
	BYTE *rawVideoMem;
};

/*
 * IDirectDrawColorControl
 */
class FAR IDirectDrawColorControlWrapper : public IDirectDrawColorControl
{
//implemented interfaces
public:
	/*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID riid, LPVOID FAR * ppvObj);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	/*** IDirectDrawColorControl methods ***/
	HRESULT __stdcall GetColorControls(LPDDCOLORCONTROL lpColorControl);
	HRESULT __stdcall SetColorControls(LPDDCOLORCONTROL lpColorControl);
	
	// Constructor/destructor
	IDirectDrawColorControlWrapper();
	~IDirectDrawColorControlWrapper();

// Custom functions and variables
private:
};

/*
 * IDirectDrawGammaControl
 */
class FAR IDirectDrawGammaControlWrapper : public IDirectDrawGammaControl
{
// Implemented interfaces
public:
	/*** IUnknown methods ***/
	HRESULT __stdcall QueryInterface(REFIID riid, LPVOID FAR * ppvObj);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	/*** IDirectDrawGammaControl methods ***/
	HRESULT __stdcall GetGammaRamp(DWORD dwFlags, LPDDGAMMARAMP lpRampData);
	HRESULT __stdcall SetGammaRamp(DWORD dwFlags, LPDDGAMMARAMP lpRampData);
	
	// Constructor/destructor
	IDirectDrawGammaControlWrapper();
	~IDirectDrawGammaControlWrapper();

// Custom functions and variables
private:
};

#endif