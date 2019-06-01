#include "DirectDrawWrapper.h"
#include <math.h>

/*******************
**IUnknown methods**
********************/

// Retrieves pointers to the supported interfaces on an object.
HRESULT __stdcall IDirectDrawSurfaceWrapper::QueryInterface(REFIID riid, LPVOID FAR * ppvObj)
{	
	debugMessage(1, "IDirectDrawSurfaceWrapper::QueryInterface", "Partially Implemented");

	// Provide the directdraw interface for all versions up to 7
	if(riid == IID_IDirectDrawPalette)
	{
		// Set pointer to this interface
		ppvObj = (LPVOID *)this;
		// Increment reference count
		AddRef();
		// Return success
		return S_OK;
	}

	// Interface not supported
	return E_NOINTERFACE;
}

// Increments the reference count for an interface on an object.
ULONG __stdcall IDirectDrawSurfaceWrapper::AddRef()
{
	debugMessage(1, "IDirectDrawSurfaceWrapper::AddRef", "Partially Implemented");

	// Increment reference count
	ReferenceCount++;
	// Return current reference count
	return ReferenceCount;
}

// Decrements the reference count for an interface on an object.
ULONG __stdcall IDirectDrawSurfaceWrapper::Release()
{
	debugMessage(1, "IDirectDrawSurfaceWrapper::Release", "Partially Implemented");

	// Decrement reference count
	ReferenceCount--;
	// If reference count reaches 0 then free object
	if(ReferenceCount == 0)
	{
		//Free objects
	}
	// Return new reference count
	return ReferenceCount;
}

/*****************************
**IDirectDrawSurface methods**
******************************/

// Attaches the specified z-buffer surface to this surface. 
HRESULT __stdcall IDirectDrawSurfaceWrapper::AddAttachedSurface(LPDIRECTDRAWSURFACE lpDDSurface)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawSurfaceWrapper::Release", "Not Implemented");

	//lpDDSurface cannot be null
	if(lpDDSurface == NULL) return DDERR_INVALIDPARAMS;

	// Attach z-buffer lpDDSurface to this surface

	// Increment ref count
	//((IDirectDrawSurfaceWrapper*)lpDDSurface)->AddRef();

	return DDERR_GENERIC;

	/*
    DDERR_CANNOTATTACHSURFACE
    DDERR_GENERIC
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_SURFACEALREADYATTACHED
    DDERR_SURFACELOST
    DDERR_WASSTILLDRAWING
	*/
}

// The IDirectDrawSurface7::AddOverlayDirtyRect method is not currently implemented.
HRESULT __stdcall IDirectDrawSurfaceWrapper::AddOverlayDirtyRect(LPRECT lpRect)
{
	debugMessage(0, "IDirectDrawSurfaceWrapper::Release", "Unsupported in DirectDraw");
	return DDERR_UNSUPPORTED;
}

// Performs a bit block transfer (bitblt). This method does not support z-buffering
// or alpha blending during bitblt operations.
HRESULT __stdcall IDirectDrawSurfaceWrapper::Blt(LPRECT lpDestRect, LPDIRECTDRAWSURFACE lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawSurfaceWrapper::Blt", "Not Implemented");

	//lpDDSrcSurface cannot be null
	if(lpDDSrcSurface == NULL) return DDERR_INVALIDPARAMS;

	//DDBLT_ALPHA and DDBLT_ZBUFFER flags are unsupported
	if(dwFlags & DDBLT_ZBUFFER) return DDERR_UNSUPPORTED;

	RECT destRect;
	if(lpDestRect == NULL)
	{
		// Fill destRect with bounds of this surface
	}
	else
	{
		// Copy dest rect
		memcpy(&destRect, lpDestRect, sizeof(RECT));
	}
	RECT srcRect;
	if(lpSrcRect == NULL)
	{
		// Fill srcRect with bounds of lpDDSrcSurface
	}
	else
	{
		// Copy source rect
		memcpy(&srcRect, lpSrcRect, sizeof(RECT));
	}

	/*
	DDBLT_COLORFILL
    Uses the dwFillColor member of the DDBLTFX structure as the RGB color that fills the destination rectangle on the destination surface.

	DDBLT_DDFX
    Uses the dwDDFX member of the DDBLTFX structure to specify the effects to use for this bitblt.

	DDBLT_DDROPS
    Uses the dwDDROP member of the DDBLTFX structure to specify the raster operations (ROPS) that are not part of the Win32 API.

	DDBLT_DEPTHFILL
    Uses the dwFillDepth member of the DDBLTFX structure as the depth value with which to fill the destination rectangle on the destination z-buffer surface.

	DDBLT_KEYDESTOVERRIDE
    Uses the ddckDestColorkey member of the DDBLTFX structure as the color key for the destination surface.

	DDBLT_KEYSRCOVERRIDE
    Uses the ddckSrcColorkey member of the DDBLTFX structure as the color key for the source surface.

	DDBLT_ROP
    Uses the dwROP member of the DDBLTFX structure for the ROP for this bitblt. These ROPs are the same as those defined in the Win32 API.

	DDBLT_ROTATIONANGLE
    Uses the dwRotationAngle member of the DDBLTFX structure as the rotation angle (specified in 1/100s of a degree) for the surface.

	*Color key flags*
	DDBLT_KEYDEST
    Uses the color key that is associated with the destination surface.

	DDBLT_KEYSRC
    Uses the color key that is associated with the source surface.

	*Behavior flags*
	DDBLT_ASYNC
    Performs this bitblt asynchronously through the first in, first out (FIFO) hardware in the order received. If no room is available in the FIFO hardware, the call fails.

	DDBLT_DONOTWAIT
    Returns without bitbltting and also returns DDERR_WASSTILLDRAWING if the bitbltter is busy.

	DDBLT_WAIT
    Postpones the DDERR_WASSTILLDRAWING return value if the bitbltter is busy, and returns as soon as the bitblt can be set up or another error occurs
	*/

	return DDERR_GENERIC;

	/*
    DDERR_GENERIC
    DDERR_INVALIDCLIPLIST
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_INVALIDRECT
    DDERR_NOALPHAHW
    DDERR_NOBLTHW
    DDERR_NOCLIPLIST
    DDERR_NODDROPSHW
    DDERR_NOMIRRORHW
    DDERR_NORASTEROPHW
    DDERR_NOROTATIONHW
    DDERR_NOSTRETCHHW
    DDERR_NOZBUFFERHW
    DDERR_SURFACEBUSY
    DDERR_SURFACELOST
    DDERR_UNSUPPORTED
    DDERR_WASSTILLDRAWING
	*/
}

// The IDirectDrawSurface7::BltBatch method is not currently implemented. 
HRESULT __stdcall IDirectDrawSurfaceWrapper::BltBatch(LPDDBLTBATCH lpDDBltBatch, DWORD dwCount, DWORD dwFlags)
{
	debugMessage(0, "IDirectDrawSurfaceWrapper::BltBatch", "Unsupported in DirectDraw");
	return DDERR_UNSUPPORTED;
}

// Performs a source copy bitblt or transparent bitblt by using a source color 
// key or destination color key. (no scaling)
HRESULT __stdcall IDirectDrawSurfaceWrapper::BltFast(DWORD dwX, DWORD dwY, LPDIRECTDRAWSURFACE lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawSurfaceWrapper::BltFast", "Not Implemented");

	if(lpDDSrcSurface == NULL) return DDERR_INVALIDPARAMS;

	// BltFast works only on display memory surfaces and cannot clip when 
    // it performs a bitblt operation. If you use this method on a surface 
    // with an attached clipper, the call fails, and the method returns DDERR_UNSUPPORTED.

	/*
	DDBLTFAST_DESTCOLORKEY
    A transparent bitblt that uses the destination color key.

	DDBLTFAST_NOCOLORKEY
    A normal copy bitblt with no transparency.

	DDBLTFAST_SRCCOLORKEY
    A transparent bitblt that uses the source color key.

	DDBLTFAST_WAIT
    Postpones the DDERR_WASSTILLDRAWING message if the bitbltter is busy, and returns as soon as the bitblt can be set up or another error occurs
	*/

	return DDERR_GENERIC;

	/*
    DDERR_EXCEPTION
    DDERR_GENERIC
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_INVALIDRECT
    DDERR_NOBLTHW
    DDERR_SURFACEBUSY
    DDERR_SURFACELOST
    DDERR_UNSUPPORTED
    DDERR_WASSTILLDRAWING
	*/
}

// Detaches one or more attached surfaces.
HRESULT __stdcall IDirectDrawSurfaceWrapper::DeleteAttachedSurface(DWORD dwFlags, LPDIRECTDRAWSURFACE lpDDSAttachedSurface)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawSurfaceWrapper::DeleteAttachedSurface", "Not Implemented");

	if(lpDDSAttachedSurface == NULL)
	{
		// Unattach all surfaces and decrement ref counts
	}
	else
	{
		// Unattach lpDDSAttachedSurface and decrement ref count
	}

	/*
	Implicit attachments, those formed by DirectDraw rather than the IDirectDrawSurface7::AddAttachedSurface 
    method, cannot be detached.

	Detaching surfaces from a flipping chain can alter other surfaces in the chain. If a front buffer is detached from 
	a flipping chain, the next surface in the chain becomes the front buffer, and the following surface becomes the back 
	buffer. If a back buffer is detached from a chain, the following surface becomes a back buffer. If a plain surface 
	is detached from a chain, the chain simply becomes shorter. If a flipping chain has only two surfaces and they are 
	detached, the chain is destroyed, and both surfaces return to their previous designation
	*/

	return DDERR_GENERIC;
	
	/*
    DDERR_CANNOTDETACHSURFACE
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_SURFACELOST
    DDERR_SURFACENOTATTACHED
	*/
}

// Enumerates all the surfaces that are attached to this surface.
HRESULT __stdcall IDirectDrawSurfaceWrapper::EnumAttachedSurfaces(LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpEnumSurfacesCallback)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawSurfaceWrapper::EnumAttachedSurfaces", "Not Implemented");

	if(lpEnumSurfacesCallback == NULL) return DDERR_INVALIDPARAMS;

	//for each surface attached to this surface
	//{
		 //HRESULT res = lpEnumSurfacesCallback(current surface interface, DDSURFACEDESC2 of the current surface, lpContext);
		 //if(res == DDENUMRET_CANCEL) break;
	//}

	/*
	EnumAttachedSurfaces enumerates only those surfaces that are directly attached to this surface. For example, in a flipping 
	chain of three or more surfaces, only one surface is enumerated because each surface is attached only to the next surface 
	in the flipping chain. In such a configuration, you can call EnumAttachedSurfaces on each successive surface to walk the 
	entire flipping chain.

	EnumAttachedSurfaces differs from its counterparts in previous interface versions in that it accepts a pointer to an 
	EnumSurfacesCallback7 function, rather than an EnumSurfacesCallback or EnumSurfacesCallback2 function. 
	*/

	return DDERR_GENERIC;

	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_SURFACELOST
	*/
}

// Enumerates the overlay surfaces on the specified destination. You can enumerate the overlays
// in front-to-back or back-to-front order.
HRESULT __stdcall IDirectDrawSurfaceWrapper::EnumOverlayZOrders(DWORD dwFlags, LPVOID lpContext, LPDDENUMSURFACESCALLBACK lpfnCallback)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawSurfaceWrapper::EnumOverlayZOrders", "Not Implemented");

	if(lpfnCallback == NULL) return DDERR_INVALIDPARAMS;

	/*
	DDENUMOVERLAYZ_BACKTOFRONT
    Enumerates overlays back to front.

	DDENUMOVERLAYZ_FRONTTOBACK
    Enumerates overlays front to back.
	*/

	//for each overlay surface attached to this surface
	//{
		//HRESULT res = lpEnumSurfacesCallback(current surface interface, DDSURFACEDESC2 of the current surface, lpContext);
		//if(res == DDENUMRET_CANCEL) break;
	//}

	return DDERR_GENERIC;
	/*	
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
	*/
}

// Makes the surface memory that is associated with the DDSCAPS_BACKBUFFER surface become associated
// with the front-buffer surface.
HRESULT __stdcall IDirectDrawSurfaceWrapper::Flip(LPDIRECTDRAWSURFACE lpDDSurfaceTargetOverride, DWORD dwFlags)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawSurfaceWrapper::Flip", "Not Implemented");

	if(lpDDSurfaceTargetOverride == NULL)
	{
		//flip to next buffer in the chain
	}
	else
	{
		//flip to surfacelpDDSurfaceTargetOverride
	}

	/*
	DDFLIP_DONOTWAIT
    On IDirectDrawSurface7 interfaces, the default is DDFLIP_WAIT. If you want to override the default and use time when the 
	accelerator is busy (as denoted by the DDERR_WASSTILLDRAWING return value), use DDFLIP_DONOTWAIT.

	DDFLIP_EVEN
    For use only when displaying video in an overlay surface. The new surface contains data from the even field of a video signal.
	This flag cannot be used with the DDFLIP_ODD flag.

	DDFLIP_STEREO
    DirectDraw flips and displays a main stereo surface. When this flag is set, stereo autoflipping is enabled. 
	The hardware automatically flips between the left and right buffers during each screen refresh.

	DDFLIP_INTERVAL2
	DDFLIP_INTERVAL3
	DDFLIP_INTERVAL4
    The DDFLIP_INTERVAL2, DDFLIP_INTERVAL3, and DDFLIP_INTERVAL4 flags indicate how many vertical retraces to wait between each flip. The default is 1.
	DirectDraw returns DERR_WASSTILLDRAWING for each surface involved in the flip until the specified number of vertical retraces has occurred. 
	If DDFLIP_INTERVAL2 is set, DirectDraw flips on every second vertical sync; if DDFLIP_INTERVAL3, on every third sync; and if DDFLIP_INTERVAL4, 
	on every fourth sync.
    These flags are effective only if DDCAPS2_FLIPINTERVAL bit is set in the dwCaps2 member of the DDCAPS structure that is returned for the display hardware.

	DDFLIP_NOVSYNC
    Causes DirectDraw to perform the physical flip as close as possible to the next scan line. Subsequent operations that 
	involve the two flipped surfaces do not check whether the physical flip has finished—that is, they do not return 
	DDERR_WASSTILLDRAWING for that reason (but might for other reasons). This allows an application to perform flips at 
	a higher frequency than the monitor refresh rate, but might introduce visible artifacts.
    If DDCAPS2_FLIPNOVSYNC is not set in the dwCaps2 member of the DDCAPS structure that is returned for the display hardware, DDFLIP_NOVSYNC has no effect.

	DDFLIP_ODD
    For use only when displaying video in an overlay surface. The new surface contains data from the odd field of a video signal. 
	This flag cannot be used with the DDFLIP_EVEN flag.

	DDFLIP_WAIT
    Typically, if the flip cannot be set up because the state of the display hardware is not appropriate, the DDERR_WASSTILLDRAWING 
	error returns immediately, and no flip occurs. Setting this flag causes Flip to continue trying to flip if it receives the 
	DDERR_WASSTILLDRAWING error from the hardware abstraction layer (HAL). Flip does not return until the flipping operation 
	has been successfully set up or another error, such as DDERR_SURFACEBUSY, is returne
	*/

	return DDERR_GENERIC;
	
	/*
    DDERR_GENERIC
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_NOFLIPHW
    DDERR_NOTFLIPPABLE
    DDERR_SURFACEBUSY
    DDERR_SURFACELOST
    DDERR_UNSUPPORTED
    DDERR_WASSTILLDRAWING
	*/
}

// Obtains the attached surface that has the specified capabilities, and increments the
// reference count of the retrieved interface.
HRESULT __stdcall IDirectDrawSurfaceWrapper::GetAttachedSurface(LPDDSCAPS lpDDSCaps, LPDIRECTDRAWSURFACE FAR *lplpDDAttachedSurface)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawSurfaceWrapper::GetAttachedSurface", "Not Implemented");


	//lplpDDAttachedSurface cannot be null
	if(lplpDDAttachedSurface == NULL) return DDERR_INVALIDPARAMS;

	/*
	Attachments are used to connect multiple DirectDrawSurface objects into complex structures, like the complex structures required to
	support 3-D page flipping with z-buffers. GetAttachedSurface fails if more than one surface is attached that matches the capabilities
	requested. In this case, the application must use the IDirectDrawSurface7::EnumAttachedSurfaces method to obtain the attached surfaces.
	*/

	return DDERR_GENERIC;

	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_NOTFOUND
    DDERR_SURFACELOST
	*/
}

// Obtains status about a bit block transfer (bitblt) operation.
HRESULT __stdcall IDirectDrawSurfaceWrapper::GetBltStatus(DWORD dwFlags)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawSurfaceWrapper::GetBltStatus", "Not Implemented");

	/*
	DDGBS_CANBLT
    Inquires whether a bitblt that involves this surface can occur immediately, and returns DD_OK if the bitblt can be completed.

	IS_ISBLTDONE
    Inquires whether the bitblt is done, and returns DD_OK if the last bitblt on this surface has completed.
	*/

	return DDERR_GENERIC;

	/*
	If it fails, the method returns DDERR_WASSTILLDRAWING if the bitbltter is busy, DDERR_NOBLTHW if there is no bitbltter, or one of the following error values:
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_NOBLTHW
    DDERR_SURFACEBUSY
    DDERR_SURFACELOST
    DDERR_UNSUPPORTED
    DDERR_WASSTILLDRAWING
	*/
}

// Retrieves the capabilities of this surface. These capabilities are not necessarily related
// to the capabilities of the display device.
HRESULT __stdcall IDirectDrawSurfaceWrapper::GetCaps(LPDDSCAPS lpDDSCaps)
{
	debugMessage(1, "IDirectDrawSurfaceWrapper::GetCaps", "Partially Implemented");

	//lpDDSCaps cannot be NULL
	if(lpDDSCaps == NULL) return DDERR_INVALIDPARAMS;

	memcpy(lpDDSCaps, &surfaceDesc.ddsCaps, sizeof(DDSCAPS));

	/*
	The IDirectDrawSurface7::GetCaps method differs from its counterpart in the IDirectDrawSurface3 interface in that 
	it accepts a pointer to a DDSCAPS2 structure, rather than the legacy DDSCAPS structure. 
	*/

	return DD_OK;
}

// Retrieves the DirectDrawClipper object that is associated with this surface, and increments
// the reference count of the returned clipper.
HRESULT __stdcall IDirectDrawSurfaceWrapper::GetClipper(LPDIRECTDRAWCLIPPER FAR *lplpDDClipper)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawSurfaceWrapper::GetClipper", "Not Implemented");

	//lplpDDClipper cannot be null
	if(lplpDDClipper == NULL) return DDERR_INVALIDPARAMS;

	return DDERR_GENERIC;
	/*	
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_NOCLIPPERATTACHED
	*/
}

// Retrieves the color key value for this surface.
HRESULT __stdcall IDirectDrawSurfaceWrapper::GetColorKey(DWORD dwFlags, LPDDCOLORKEY lpDDColorKey)
{
	debugMessage(1, "IDirectDrawSurfaceWrapper::GetColorKey", "Partially Implemented");

	//lpDDColorKey cannot be null
	if(lpDDColorKey == NULL) return DDERR_INVALIDPARAMS;

	if(dwFlags & DDCKEY_DESTBLT)
	{
		memcpy(lpDDColorKey, &colorKeys[0], sizeof(DDCOLORKEY));
	}
	else if(dwFlags & DDCKEY_DESTOVERLAY)
	{
		memcpy(lpDDColorKey, &colorKeys[1], sizeof(DDCOLORKEY));
	}
	else if(dwFlags & DDCKEY_SRCBLT)
	{
		memcpy(lpDDColorKey, &colorKeys[2], sizeof(DDCOLORKEY));
	}
	if(dwFlags & DDCKEY_SRCOVERLAY)
	{
		memcpy(lpDDColorKey, &colorKeys[3], sizeof(DDCOLORKEY));
	}

	/*
	DDCKEY_DESTBLT
    A color key or color space to be used as a destination color key for bit block transfer (bitblt) operations.

	DDCKEY_DESTOVERLAY
    A color key or color space to be used as a destination color key for overlay operations.

	DDCKEY_SRCBLT
    A color key or color space to be used as a source color key for bitblt operations.

	DDCKEY_SRCOVERLAY
    A color key or color space to be used as a source color key for overlay operations.
	*/

	return DD_OK;

	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_NOCOLORKEY
    DDERR_NOCOLORKEYHW
    DDERR_SURFACELOST
    DDERR_UNSUPPORTED
	*/
}

// Creates a GDI-compatible handle of a device context for this surface.
HRESULT __stdcall IDirectDrawSurfaceWrapper::GetDC(HDC FAR *lphDC)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawSurfaceWrapper::GetDC", "Not Implemented");

	// lphDC cannot but null
	if(lphDC == NULL) return DDERR_INVALIDPARAMS;

	// Create GDI-compatible handle device context for this surface and set lphDC to it

	return DDERR_GENERIC;

	/*
    DDERR_DCALREADYCREATED
    DDERR_GENERIC
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_INVALIDSURFACETYPE
    DDERR_SURFACELOST
    DDERR_UNSUPPORTED
    DDERR_WASSTILLDRAWING
	*/
}

// Retrieves status about whether this surface has finished its flipping process.
HRESULT __stdcall IDirectDrawSurfaceWrapper::GetFlipStatus(DWORD dwFlags)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawSurfaceWrapper::GetFlipStatus", "Not Implemented");

	/*
	DDGFS_CANFLIP
    Inquires whether this surface can be flipped immediately, and returns DD_OK if the flip can be completed.

	DDGFS_ISFLIPDONE
    Inquires whether the flip has finished, and returns DD_OK if the last flip on this surface has completed.
	*/

	return DDERR_GENERIC;

	/*
	If it fails, the method can return DDERR_WASSTILLDRAWING if the surface has not finished its flipping process, or one of the following error values:
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_INVALIDSURFACETYPE
    DDERR_SURFACEBUSY
    DDERR_SURFACELOST
    DDERR_UNSUPPORTED
    DDERR_WASSTILLDRAWING
	*/
}

// Retrieves the display coordinates of this surface. This method is used on a visible,
// active overlay surface (that is, a surface that has the DDSCAPS_OVERLAY flag set).
HRESULT __stdcall IDirectDrawSurfaceWrapper::GetOverlayPosition(LPLONG lplX, LPLONG lplY)
{
	debugMessage(1, "IDirectDrawSurfaceWrapper::GetOverlayPosition", "Partially Implemented");

	//lplX and lplY cannot be null
	if(lplX == NULL || lplY == NULL) return DDERR_INVALIDPARAMS;

	//set lplX and lplY to X,Y of this overlay surface
	*lplX = overlayX;
	*lplY = overlayY;

	return DD_OK;

	/*
    DDERR_GENERIC
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_INVALIDPOSITION
    DDERR_NOOVERLAYDEST
    DDERR_NOTAOVERLAYSURFACE
    DDERR_OVERLAYNOTVISIBLE
    DDERR_SURFACELOST
	*/
}

// Retrieves the DirectDrawPalette object that is associated with this surface,
// and increments the reference count of the returned palette.
HRESULT __stdcall IDirectDrawSurfaceWrapper::GetPalette(LPDIRECTDRAWPALETTE FAR *lplpDDPalette)
{
	debugMessage(1, "IDirectDrawSurfaceWrapper::GetPalette", "Partially Implemented");

	// lplpDDPalette cannot be null
	if(lplpDDPalette == NULL) return DDERR_INVALIDPARAMS;

	// No palette attached
	if(attachedPalette == NULL) return DDERR_NOPALETTEATTACHED;

	// Check exclusive mode

	// Return attached palette
	*lplpDDPalette = (LPDIRECTDRAWPALETTE)attachedPalette;
	// Increment ref count
	attachedPalette->AddRef();

	// Success
	return DD_OK;

	/*
    DDERR_GENERIC
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_NOEXCLUSIVEMODE
    DDERR_NOPALETTEATTACHED
    DDERR_SURFACELOST
    DDERR_UNSUPPORTED
	*/	
}

// Retrieves the color and pixel format of this surface.
HRESULT __stdcall IDirectDrawSurfaceWrapper::GetPixelFormat(LPDDPIXELFORMAT lpDDPixelFormat)
{
	debugMessage(1, "IDirectDrawSurfaceWrapper::GetPixelFormat", "Partially Implemented");

	// lpDDPixelFormat cannot be null
	if(lpDDPixelFormat == NULL) return DDERR_INVALIDPARAMS;

	// lpDDPixelFormat receives a detailed description of the current pixel and 
    // color space format of this surface.

	// Copy pixel format to lpDDPixelFormat
	memcpy(lpDDPixelFormat, &surfaceDesc.ddpfPixelFormat, sizeof(DDPIXELFORMAT));

	return DD_OK;

	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_INVALIDSURFACETYPE
	*/
}

// Retrieves a description of this surface in its current condition.
HRESULT __stdcall IDirectDrawSurfaceWrapper::GetSurfaceDesc(LPDDSURFACEDESC lpDDSurfaceDesc)
{
	debugMessage(1, "IDirectDrawSurfaceWrapper::GetSurfaceDesc", "Partially Implemented");

	// lpDDSurfaceDesc cannot be null
	if(lpDDSurfaceDesc == NULL) return DDERR_INVALIDPARAMS;

	// Fill lpDDSurfaceDesc with this surface description

	// Copy surfacedesc to lpDDSurfaceDesc
	memcpy(lpDDSurfaceDesc, &surfaceDesc, sizeof(DDSURFACEDESC));

	return DD_OK;

	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
	*/
}

// Initializes a DirectDrawSurface object.
HRESULT __stdcall IDirectDrawSurfaceWrapper::Initialize(LPDIRECTDRAW lpDD, LPDDSURFACEDESC lpDDSurfaceDesc)
{
	debugMessage(1, "IDirectDrawSurfaceWrapper::Initialize", "Partially Implemented");

	// Because the DirectDrawSurface object is initialized when it is created, 
    // this method always returns DDERR_ALREADYINITIALIZED.
	return DDERR_ALREADYINITIALIZED;
}

//Determines whether the surface memory that is associated with a DirectDrawSurface object has been freed.
HRESULT __stdcall IDirectDrawSurfaceWrapper::IsLost()
{
	// NOTE: Disabled for performance
	// debugMessage(2, "IDirectDrawSurfaceWrapper::IsLost", "Partially Implemented(Not Required)");

	// You can use this method to determine when you need to reallocate surface memory. 
    // When a DirectDrawSurface object loses its surface memory, most methods return 
    // DDERR_SURFACELOST and perform no other action.

	// Check if surface is lost or not, if not return OK

	// Surface never lost
	return DD_OK;

	/*	
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_SURFACELOST
	*/
}

// Obtains a pointer to the surface memory.
HRESULT __stdcall IDirectDrawSurfaceWrapper::Lock(LPRECT lpDestRect, LPDDSURFACEDESC lpDDSurfaceDesc, DWORD dwFlags, HANDLE hEvent)
{
	// lpDDSurfaceDesc cannot be null
	if(lpDDSurfaceDesc == NULL) return DDERR_INVALIDPARAMS;

	char message[2048] = "\0";

	lockVideoMem = NULL;
	if (surfaceTexture && *surfaceTexture)
	{
		D3DLOCKED_RECT LockedRect;
		if ((*surfaceTexture)->LockRect(0, &LockedRect, lpDestRect, 0) != D3D_OK)
		{
			return DDERR_GENERIC;
		}
		if (*surfaceTexture != lastSurfaceTexture)
		{
			memcpy(LockedRect.pBits, rawVideoMem, 640 * 480 * sizeof(BYTE));
		}
		lockVideoMem = (BYTE*)LockedRect.pBits;
	}

    // Check for destination rect
	//if(lpDestRect == NULL)
	//{
		// Copy desc to passed in desc
		memcpy(lpDDSurfaceDesc, &surfaceDesc, sizeof(DDSURFACEDESC));
		// Set video memory and pitch
		lpDDSurfaceDesc->lpSurface = lockVideoMem;
		lpDDSurfaceDesc->dwFlags |= DDSD_LPSURFACE;
		lpDDSurfaceDesc->lPitch = 640;
		lpDDSurfaceDesc->dwFlags |= DDSD_PITCH;
		//sprintf_s(message, 2048, "INF IDirectDrawSurfaceWrapper::Lock lpDestRect: NULL");
	//}
	//else 
	//{		
	//	sprintf_s(message, 2048, "Unsupported lpDestRect[%d,%d,%d,%d]", lpDestRect->left, lpDestRect->top, lpDestRect->right, lpDestRect->bottom);
	//}

	// NOTE: Disabled for performance
	/*if(dwFlags & DDLOCK_DONOTWAIT) strcat_s(message, 2048, ", DDLOCK_DONOTWAIT");
	if(dwFlags & DDLOCK_EVENT) strcat_s(message, 2048, ", DDLOCK_EVENT");
	if(dwFlags & DDLOCK_NOOVERWRITE) strcat_s(message, 2048, ", DDLOCK_NOOVERWRITE");
	if(dwFlags & DDLOCK_NOSYSLOCK) strcat_s(message, 2048, ", DDLOCK_NOSYSLOCK");
	if(dwFlags & DDLOCK_DISCARDCONTENTS) strcat_s(message, 2048, ", DDLOCK_DISCARDCONTENTS");
	if(dwFlags & DDLOCK_OKTOSWAP) strcat_s(message, 2048, ", DDLOCK_OKTOSWAP");
	if(dwFlags & DDLOCK_READONLY) strcat_s(message, 2048, ", DDLOCK_READONLY");
	if(dwFlags & DDLOCK_SURFACEMEMORYPTR) strcat_s(message, 2048, ", DDLOCK_SURFACEMEMORYPTR");
	if(dwFlags & DDLOCK_WAIT) strcat_s(message, 2048, ", DDLOCK_WAIT");
	if(dwFlags & DDLOCK_WRITEONLY) strcat_s(message, 2048, ", DDLOCK_WRITEONLY");

	if(lpDestRect == NULL)
	{
		debugMessage(2, "IDirectDrawSurfaceWrapper::Lock", message);
	}
	else
	/
		debugMessage(0, "IDirectDrawSurfaceWrapper::Lock", message);
		// Is error, unsupported
	  return DDERR_GENERIC;
	}*/

	/*
	DDLOCK_DONOTWAIT
    On IDirectDrawSurface7 interfaces, the default is DDLOCK_WAIT. If you want to override the default and use time when the accelerator is busy (as denoted by the DDERR_WASSTILLDRAWING return value), use DDLOCK_DONOTWAIT.

	DDLOCK_EVENT
    Not currently implemented.

	DDLOCK_NOOVERWRITE
    New for DirectX 7.0. Used only with Direct3D vertex-buffer locks. Indicates that no vertices that were referred to in a draw operation since the start of the frame (or the last lock without this flag) are modified during the lock. This can be useful when you want only to append data to the vertex buffer.

	DDLOCK_NOSYSLOCK
    Do not take the Win16Mutex (also known as Win16Lock). This flag is ignored when locking the primary surface.

	DDLOCK_DISCARDCONTENTS
    New for DirectX 7.0. Used only with Direct3D vertex-buffer locks. Indicates that no assumptions are made about the contents of the vertex buffer during this lock. This enables Direct3D or the driver to provide an alternative memory area as the vertex buffer. This is useful when you plan to clear the contents of the vertex buffer and fill in new data.

	DDLOCK_OKTOSWAP
    This flag is obsolete and was replaced by the DDLOCK_DISCARDCONTENTS flag.

	DDLOCK_READONLY
    Indicates that the surface being locked can only be read.

	DDLOCK_SURFACEMEMORYPTR
    Indicates that a valid memory pointer to the top of the specified rectangle should be returned. If no rectangle is specified, a pointer to the top of the surface is returned. This is the default.

	DDLOCK_WAIT
    If a lock cannot be obtained because a bit block transfer (bitblt) operation is in progress, Lock retries until a lock is obtained or another error occurs, such as DDERR_SURFACEBUSY.

	DDLOCK_WRITEONLY
    Indicates that the surface being locked is write-enabled.
	*/

	return DD_OK;

	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_OUTOFMEMORY
    DDERR_SURFACEBUSY
    DDERR_SURFACELOST
    DDERR_WASSTILLDRAWING
	*/
}

// Releases the handle of a device context that was previously obtained by using the 
// IDirectDrawSurface7::GetDC method.
HRESULT __stdcall IDirectDrawSurfaceWrapper::ReleaseDC(HDC hDC)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawSurfaceWrapper::ReleaseDC", "Not Implemented");

	// Free hDc which is the handle of a device context that was previously obtained
    // by IDirectDrawSurface7::GetDC.

	return DDERR_GENERIC;

	/*
    DDERR_GENERIC
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_SURFACELOST
    DDERR_UNSUPPORTED
	*/
}

// Restores a surface that has been lost. This occurs when the surface memory that is 
// associated with the DirectDrawSurface object has been freed.
HRESULT __stdcall IDirectDrawSurfaceWrapper::Restore()
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawSurfaceWrapper::Restore", "Not Implemented");

	//restore this surface if it's been lost

	/*
	Restore restores the memory that was allocated for a surface, but does not reload any bitmaps that might have existed in the 
	surface before it was lost.

	A single call to Restore restores a DirectDrawSurface object's associated implicit surfaces (back buffers, and so on). 
	An attempt to restore an implicitly created surface results in an error. Restore does not work across explicit attachments 
	that were created by using the IDirectDrawSurface7::AddAttachedSurface method—each of these surfaces must be restored
	individually.
	*/

	return DDERR_GENERIC;
	/*
    DDERR_GENERIC
    DDERR_IMPLICITLYCREATED
    DDERR_INCOMPATIBLEPRIMARY
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_NOEXCLUSIVEMODE
    DDERR_OUTOFMEMORY
    DDERR_UNSUPPORTED
    DDERR_WRONGMODE
	*/
}

// Attaches a clipper object to, or deletes one from, this surface.
HRESULT __stdcall IDirectDrawSurfaceWrapper::SetClipper(LPDIRECTDRAWCLIPPER lpDDClipper)
{
	debugMessage(0, "IDirectDrawSurfaceWrapper::SetClipper", "Not Implemented");

	//if no clipper was passed in
	/*if(lpDDClipper == NULL)
	{
		//no clipper attached
		if(attachedClipper == NULL) return DDERR_NOCLIPPERATTACHED;
		//release attached clipper
		attachedClipper->Release();
		//no clipper attached
		attachedClipper = NULL;
	}
	else
	{
		//no clipper attached
		if(attachedClipper == NULL)
		{
			//check surface type for DDERR_INVALIDSURFACETYPE

			//attach the clipper
			attachedClipper = (IDirectDrawClipperWrapper *)lpDDClipper;
			//increment ref count
			attachedClipper->AddRef();
		}
		else
		{
			//I don't know what to do here, ignore?
		}
	}*/

	return DDERR_GENERIC;

	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_INVALIDSURFACETYPE
    DDERR_NOCLIPPERATTACHED
	*/
}

// Sets the color key value for the DirectDrawSurface object if the hardware supports
// color keys on a per-surface basis.
HRESULT __stdcall IDirectDrawSurfaceWrapper::SetColorKey(DWORD dwFlags, LPDDCOLORKEY lpDDColorKey)
{
	debugMessage(1, "IDirectDrawSurfaceWrapper::SetColorKey", "Partially Implemented");

	// lpDDColorKey cannot be null
	if(lpDDColorKey == NULL) return DDERR_INVALIDPARAMS;

	/*
	DDCKEY_COLORSPACE
    The structure contains a color space. Not set if the structure contains a single color key.
	*/

	//store color key information for the appropriate color key
	if(dwFlags & DDCKEY_DESTBLT)
	{
		memcpy(&colorKeys[0], lpDDColorKey, sizeof(DDCOLORKEY));
	}
	else if(dwFlags & DDCKEY_DESTOVERLAY)
	{
		memcpy(&colorKeys[1], lpDDColorKey, sizeof(DDCOLORKEY));
	}
	else if(dwFlags & DDCKEY_SRCBLT)
	{
		memcpy(&colorKeys[2], lpDDColorKey, sizeof(DDCOLORKEY));
	}
	if(dwFlags & DDCKEY_SRCOVERLAY)
	{
		memcpy(&colorKeys[3], lpDDColorKey, sizeof(DDCOLORKEY));
	}

	return DD_OK;

	/*
	DDERR_INVALIDOBJECT
	DDERR_INVALIDPARAMS
	DDERR_NOCOLORKEYHW
	DDERR_SURFACELOST
	DDERR_UNSUPPORTED
	*/
}

//Changes the display coordinates of an overlay surface.
HRESULT __stdcall IDirectDrawSurfaceWrapper::SetOverlayPosition(LONG lX, LONG lY)
{
	debugMessage(1, "IDirectDrawSurfaceWrapper::SetOverlayPosition", "Partially Implemented");

	// Store the new overlay position
	overlayX = lX;
	overlayY = lY;

	return DD_OK;

	/*
	DDERR_GENERIC
	DDERR_INVALIDOBJECT
	DDERR_INVALIDPARAMS
	DDERR_INVALIDPOSITION
	DDERR_NOOVERLAYDEST
	DDERR_NOTAOVERLAYSURFACE
	DDERR_OVERLAYNOTVISIBLE
	DDERR_SURFACELOST
	DDERR_UNSUPPORTED
	*/
}

// Attaches a palette object to (or detaches one from) a surface. The surface uses this palette 
// for all subsequent operations. The palette change takes place immediately, without regard to 
// refresh timing.
HRESULT __stdcall IDirectDrawSurfaceWrapper::SetPalette(LPDIRECTDRAWPALETTE lpDDPalette)
{
	char message[2048] = "\0";
	sprintf_s(message, 2048, "lpDDPalette: 0x%x", (UINT)lpDDPalette);
	debugMessage(2, "IDirectDrawSurfaceWrapper::SetPalette", message);

	// if lpDDPalette is NULL then detach the current palette
	if(lpDDPalette == NULL)
	{
		// Decrement ref count
		if(attachedPalette->Release() ==  0) delete attachedPalette;
		// Detach
		attachedPalette = NULL;
	}
	
	// When you call SetPalette to set a palette to a surface for the first time, 
    // SetPalette increments the palette's reference count; subsequent calls to 
    // SetPalette do not affect the palette's reference count.

	attachedPalette = (IDirectDrawPaletteWrapper *)lpDDPalette;

	return DD_OK;

	/*
    DDERR_GENERIC
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_INVALIDPIXELFORMAT
    DDERR_INVALIDSURFACETYPE
    DDERR_NOEXCLUSIVEMODE
    DDERR_NOPALETTEATTACHED
    DDERR_NOPALETTEHW
    DDERR_NOT8BITCOLOR
    DDERR_SURFACELOST
    DDERR_UNSUPPORTED
	*/
}

// Notifies DirectDraw that the direct surface manipulations are complete.
HRESULT __stdcall IDirectDrawSurfaceWrapper::Unlock(LPVOID lpRect)
{
	char message[2048] = "\0";

	// NOTE: Disabled for performance
	/*if(lpRect != 0)
	{
		sprintf_s(message, 2048, "Unsupported lpRect[%d,%d,%d,%d]", ((LPRECT)lpRect)->left, ((LPRECT)lpRect)->top, ((LPRECT)lpRect)->right, ((LPRECT)lpRect)->bottom);
		debugMessage(0, "IDirectDrawSurfaceWrapper::Unlock", message);
	}
	else
	{
		//sprintf_s(message, 2048, "lpRect: NULL");
		//debugMessage(2, "IDirectDrawSurfaceWrapper::Unlock", message);
	}*/
	
	// Always unlock full rect(fix)

	// Translate all of raw video memory to rgb video memory with palette
	if (!lockVideoMem)
	{
		return DDERR_GENERIC;
	}

	if (++frameCounter == 0)
	{
		memcpy(rawVideoMem, lockVideoMem, 640 * 480 * sizeof(BYTE));
	}

	for (long i = 0; i < 640 * 480; i++)
	{
		rgbVideoMem[i] = attachedPalette->rgbPalette[lockVideoMem[i]];
	}

	/*
	A pointer to a RECT structure that was used to lock the surface in the corresponding 
	call to the IDirectDrawSurface7::Lock method. This parameter can be NULL only if the 
	entire surface was locked by passing NULL in the lpDestRect parameter of the corresponding 
	call to the IDirectDrawSurface7::Lock method.
	
	Because you can call IDirectDrawSurface7::Lock multiple times for the same surface with 
	different destination rectangles, the pointer in lpRect links the calls to the 
	IDirectDrawSurface7::Lock and IDirectDrawSurface7::Unlock methods. 
	*/

	if (surfaceTexture && *surfaceTexture)
	{
		(*surfaceTexture)->UnlockRect(0);
		lastSurfaceTexture = *surfaceTexture;
	}
	lockVideoMem = NULL;

	// Present the surface
	if(!ddrawParent->Present())
	{
		// Failed to presnt the surface, error reporting handled previously
		return DDERR_GENERIC;
	}

	// Success
	return DD_OK;

	/*
    DDERR_GENERIC
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_INVALIDRECT
    DDERR_NOTLOCKED
    DDERR_SURFACELOST
	*/
}

// Repositions or modifies the visual attributes of an overlay surface. These
// surfaces must have the DDSCAPS_OVERLAY flag set.
HRESULT __stdcall IDirectDrawSurfaceWrapper::UpdateOverlay(LPRECT lpSrcRect, LPDIRECTDRAWSURFACE lpDDDestSurface, LPRECT lpDestRect, DWORD dwFlags, LPDDOVERLAYFX lpDDOverlayFx)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawSurfaceWrapper::UpdateOverlay", "Not Implemented");

	/*
	lpSrcRect [in]
    A pointer to a RECT structure that defines the x, y, width, and height of the region on the source surface being used as the overlay. This parameter can be NULL to hide an overlay or to indicate that the entire overlay surface is to be used and that the overlay surface conforms to any boundary and size-alignment restrictions imposed by the device driver.

	lpDDDestSurface [in]
    A pointer to the IDirectDrawSurface7 interface for the DirectDrawSurface object that is being overlaid.

	lpDestRect [in]
    A pointer to a RECT structure that defines the width, x, and height, y, of the region on the destination surface that the overlay should be moved to. This parameter can be NULL to hide the overlay.

	dwFlags [in]
    A combination of the following flags that determine the overlay update:

    DDOVER_ADDDIRTYRECT
        Adds a dirty rectangle to an emulated overlay surface.
    DDOVER_ALPHADEST
        Obsolete.
    DDOVER_ALPHADESTCONSTOVERRIDE
        Uses the dwAlphaDestConst member of the DDOVERLAYFX structure as the destination alpha channel for this overlay.
    DDOVER_ALPHADESTNEG
        Indicates that the destination surface becomes more transparent as the alpha value increases (0 is opaque).
    DDOVER_ALPHADESTSURFACEOVERRIDE
        Uses the lpDDSAlphaDest member of the DDOVERLAYFX structure as the alpha channel destination for this overlay.
    DDOVER_ALPHAEDGEBLEND
        Uses the dwAlphaEdgeBlend member of the DDOVERLAYFX structure as the alpha channel for the edges of the image that border the color key colors.
    DDOVER_ALPHASRC
        Uses either the alpha information in pixel format or the alpha channel surface attached to the source surface as the source alpha channel for this overlay.
    DDOVER_ALPHASRCCONSTOVERRIDE
        Uses the dwAlphaSrcConst member of the DDOVERLAYFX structure as the source alpha channel for this overlay.
    DDOVER_ALPHASRCNEG
        Indicates that the source surface becomes more transparent as the alpha value increases (0 is opaque).
    DDOVER_ALPHASRCSURFACEOVERRIDE
        Uses the lpDDSAlphaSrc member of the DDOVERLAYFX structure as the alpha channel source for this overlay.
    DDOVER_ARGBSCALEFACTORS
        New for DirectX 7.0. Indicates that the DDOVERLAYFX structure contains valid ARGB scaling factors.
    DDOVER_AUTOFLIP
        Automatically flips to the next surface in the flipping chain each time that a video port VSYNC occurs.
    DDOVER_BOB
        Displays each field of the interlaced video stream individually without causing any artifacts to display.
    DDOVER_BOBHARDWARE
        Bob operations are performed by using hardware, rather than by using software or being emulated. This flag must be used with the DDOVER_BOB flag.
    DDOVER_DDFX
        Uses the overlay FX flags in the lpDDOverlayFx parameter to define special overlay effects.
    DDOVER_DEGRADEARGBSCALING
        New for DirectX 7.0. ARGB scaling factors can be degraded to fit driver capabilities.
    DDOVER_HIDE
        Turns off this overlay.
    DDOVER_INTERLEAVED
        The surface memory is composed of interleaved fields.
    DDOVER_KEYDEST
        Uses the color key associated with the destination surface.
    DDOVER_KEYDESTOVERRIDE
        Uses the dckDestColorkey member of the DDOVERLAYFX structure as the color key for the destination surface.
    DDOVER_KEYSRC
        Uses the color key associated with the source surface.
    DDOVER_KEYSRCOVERRIDE
        Uses the dckSrcColorkey member of the DDOVERLAYFX structure as the color key for the source surface.
    DDOVER_OVERRIDEBOBWEAVE
        Bob and weave decisions should not be overridden by other interfaces.
    DDOVER_REFRESHALL
        Redraws the entire surface on an emulated overlayed surface.
    DDOVER_REFRESHDIRTYRECTS
        Redraws all dirty rectangles on an emulated overlayed surface.
    DDOVER_SHOW
        Turns on this overlay.

	lpDDOverlayFx [in]
		A pointer to the DDOVERLAYFX structure that describes the effects to be used. Can be NULL if the DDOVER_DDFX flag is not specified.
	*/
	
	return DDERR_GENERIC;
	
	/*
    DDERR_DEVICEDOESNTOWNSURFACE
    DDERR_GENERIC
    DDERR_HEIGHTALIGN
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_INVALIDRECT
    DDERR_INVALIDSURFACETYPE
    DDERR_NOSTRETCHHW
    DDERR_NOTAOVERLAYSURFACE
    DDERR_OUTOFCAPS
    DDERR_SURFACELOST
    DDERR_UNSUPPORTED
    DDERR_XALIGN
	*/
}

// The IDirectDrawSurface7::UpdateOverlayDisplay method is not currently implemented
HRESULT __stdcall IDirectDrawSurfaceWrapper::UpdateOverlayDisplay(DWORD dwFlags)
{
	debugMessage(0, "IDirectDrawSurfaceWrapper::UpdateOverlayDisplay", "Not Supported in DirectDraw");
	// Not supported
	return DDERR_UNSUPPORTED;
}

// Sets the z-order of an overlay.
HRESULT __stdcall IDirectDrawSurfaceWrapper::UpdateOverlayZOrder(DWORD dwFlags, LPDIRECTDRAWSURFACE lpDDSReference)
{
	debugMessage(0, "IDirectDrawSurfaceWrapper::UpdateOverlayZOrder", "Not Implemented");

	/*
	DDOVERZ_INSERTINBACKOF
    Inserts this overlay in the overlay chain behind the reference overlay.

	DDOVERZ_INSERTINFRONTOF
    Inserts this overlay in the overlay chain in front of the reference overlay.

	DDOVERZ_MOVEBACKWARD
    Moves this overlay one position backward in the overlay chain.

	DDOVERZ_MOVEFORWARD
    Moves this overlay one position forward in the overlay chain.

	DDOVERZ_SENDTOBACK
    Moves this overlay to the back of the overlay chain.

	DDOVERZ_SENDTOFRONT
    Moves this overlay to the front of the overlay chain.

	lpDDSReference [in]
    A pointer to the IDirectDrawSurface7 interface for the DirectDraw surface to be used as a relative position in the 
	overlay chain. This parameter is needed only for the DDOVERZ_INSERTINBACKOF and DDOVERZ_INSERTINFRONTOF flags.

	*/

	return DDERR_GENERIC;
	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_NOTAOVERLAYSURFACE
	*/
}

/****************************
**Added in the V2 interface**
*****************************/

// Retrieves an interface to the DirectDraw object that was used to create this surface.
HRESULT __stdcall IDirectDrawSurfaceWrapper::GetDDInterface(LPVOID FAR *lplpDD)
{
	debugMessage(0, "IDirectDrawSurfaceWrapper::GetDDInterface", "Not Implemented");

	// lplpDD cannot be null
	if(lplpDD == NULL) return DDERR_INVALIDPARAMS;

	// Set lplpDD to directdraw object that created this surface
	*lplpDD = (IDirectDraw *)ddrawParent;

	return DD_OK;

	/*
	DDERR_INVALIDOBJECT
	DDERR_INVALIDPARAM
	*/
}

// Prevents a system-memory surface from being paged out while a bit block
// transfer (bitblt) operation that uses direct memory access (DMA) transfers
// to or from system memory is in progress.
HRESULT __stdcall IDirectDrawSurfaceWrapper::PageLock(DWORD dwFlags)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawSurfaceWrapper::PageLock", "Not Implemented");

	//dwFlags currently not used and must be set to 0.

	return DDERR_GENERIC;
	/*
    DDERR_CANTPAGELOCK
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_SURFACELOST
	*/
}

// Unlocks a system-memory surface, which then allows it to be paged out.
HRESULT __stdcall IDirectDrawSurfaceWrapper::PageUnlock(DWORD dwFlags)
{
	//***Unimplemented***
	debugMessage(0, "IDirectDrawSurfaceWrapper::PageUnlock", "Not Implemented");

	// dwFlags currently not used and must be set to 0.

	return DDERR_GENERIC;

	/*
    DDERR_CANTPAGEUNLOCK
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_NOTPAGELOCKED
    DDERR_SURFACELOST
	*/
}

/****************************
**Added in the V3 interface**
*****************************/

// Sets the characteristics of an existing surface.
HRESULT __stdcall IDirectDrawSurfaceWrapper::SetSurfaceDesc(LPDDSURFACEDESC2 lpDDsd2, DWORD dwFlags)
{
	debugMessage(0, "IDirectDrawSurfaceWrapper::SetSurfaceDesc", "Not Implemented");

	/*
	lpDDsd2 [in]
    A pointer to a DDSURFACEDESC2 structure that contains the new surface characteristics.

	dwFlags [in]
    Currently not used and must be set to 0.
	*/

	return DDERR_GENERIC;

	/*
    DDERR_INVALIDPARAMS
    DDERR_INVALIDOBJECT
    DDERR_SURFACELOST
    DDERR_SURFACEBUSY
    DDERR_INVALIDSURFACETYPE
    DDERR_INVALIDPIXELFORMAT
    DDERR_INVALIDCAPS
    DDERR_UNSUPPORTED
    DDERR_GENERIC
	*/
}

/****************************
**Added in the V4 interface**
*****************************/

// Manually updates the uniqueness value for this surface. 
HRESULT __stdcall IDirectDrawSurfaceWrapper::ChangeUniquenessValue()
{
	debugMessage(0, "IDirectDrawSurfaceWrapper::ChangeUniquenessValue", "Not Implemented");

	// DirectDraw automatically updates uniqueness values whenever the contents of a surface change.

	return DDERR_GENERIC;

	/*
    DDERR_EXCEPTION
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
	*/
}

// Frees the specified private data that is associated with this surface.
HRESULT __stdcall IDirectDrawSurfaceWrapper::FreePrivateData(REFGUID guidTag)
{
	debugMessage(0, "IDirectDrawSurfaceWrapper::FreePrivateData", "Not Implemented");

	//guidTag is a reference to (C++) or address of (C) the globally unique identifier 
	//that identifies the private data to be free

	//If the private data was set by using the DDSPD_IUNKNOWNPOINTER flag, 
	//FreePrivateData calls the IUnknown::Release method on the associated interface.

	return DDERR_GENERIC;

	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_NOTFOUND
	*/
}

// Copies the private data that is associated with this surface to a provided buffer.
HRESULT __stdcall IDirectDrawSurfaceWrapper::GetPrivateData(REFGUID guidTag, LPVOID lpBuffer, LPDWORD lpcbBufferSize)
{
	debugMessage(0, "IDirectDrawSurfaceWrapper::GetPrivateData", "Not Implemented");

	/*
	guidTag [in]
		Reference to (C++) or address of (C) the globally unique identifier that identifies the private data to be retrieved.
	lpBuffer [out]
		A pointer to a previously allocated buffer that receives the requested private data if the call succeeds. The application that calls this method must allocate and release this buffer.
	lpcbBufferSize [in, out]
		A pointer to a variable that contains the size value of the buffer at lpBuffer, in bytes. If this value is less than the actual size of the private data (such as 0), GetPrivateData sets the variable to the required buffer size, and then returns DDERR_MOREDATA.
	*/

	return DDERR_GENERIC;

	/*
    DDERR_EXPIRED
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_MOREDATA
    DDERR_NOTFOUND
    DDERR_OUTOFMEMORY
	*/
}

// Retrieves the current uniqueness value for this surface.
HRESULT __stdcall IDirectDrawSurfaceWrapper::GetUniquenessValue(LPDWORD lpValue)
{
	debugMessage(0, "IDirectDrawSurfaceWrapper::GetUniquenessValue", "Not Implemented");

	/*
	lpValue [out]
		A pointer to a variable that receives the surface's current uniqueness value if the call succeeds.
	*/

	return DDERR_GENERIC;

	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
	*/
}

//
HRESULT __stdcall IDirectDrawSurfaceWrapper::SetPrivateData(REFGUID guidTag, LPVOID lpData, DWORD cbSize, DWORD dwFlags)
{
	debugMessage(0, "IDirectDrawSurfaceWrapper::SetPrivateData", "Not Implemented");

	/*
	guidTag [in]
		Reference to (C++) or address of (C) the globally unique identifier that identifies the private data to be set.
	lpData [in]
		A pointer to a buffer that contains the data to be associated with the surface.
	cbSize [in]
		The size value of the buffer at lpData, in bytes.
	dwFlags [in]
		A value that can be set to one of the following flags. These flags describe the type of data being passed or request that the data be invalidated when the surface changes.
			(none)
				If no flags are specified, DirectDraw allocates memory to hold the data within the buffer and copies the data into the new buffer. The buffer allocated by DirectDraw is automatically freed, as appropriate.
			DDSPD_IUNKNOWNPOINTER
				The data at lpData is a pointer to an IUnknown interface. DirectDraw automatically calls the IUnknown::AddRef method of this interface. When this data is no longer needed, DirectDraw automatically calls the IUnknown::Release method of this interface.
			DDSPD_VOLATILE
				The buffer at lpData is only valid while the surface remains unchanged. If the surface's contents change, subsequent calls to the IDirectDrawSurface7::GetPrivateData method return DDERR_EXPIRED.
	*/

	return DDERR_GENERIC;

	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_OUTOFMEMORY
	*/
}

/*******************
**Texture7 Methods**
********************/

// Assigns the texture-management priority for this texture. This method 
// succeeds only on managed textures.
HRESULT __stdcall IDirectDrawSurfaceWrapper::SetPriority(DWORD dwPriority)
{
	debugMessage(0, "IDirectDrawSurfaceWrapper::SetPriority", "Not Implemented");

	/*
	dwPriority [in]
		A value that specifies the new texture-management priority for the texture.
	*/

	return DDERR_GENERIC;

	/*
	If it fails, the return value is an error. The method returns DDERR_INVALIDOBJECT 
    if the parameter is invalid or if the texture is not managed by Direct3D. 
	*/

}

// Retrieves the texture-management priority for this texture. This method 
// succeeds only on managed textures.
HRESULT __stdcall IDirectDrawSurfaceWrapper::GetPriority(LPDWORD lpdwPriority)
{
	debugMessage(0, "IDirectDrawSurfaceWrapper::GetPriority", "Not Implemented");

	/*
	lpdwPriority [out]
		A pointer to a variable that receives the texture priority if the call succeeds.
	*/

	return DDERR_GENERIC;

	/*
	If it fails, the return value is an error. The method returns DDERR_INVALIDOBJECT
    if the parameter is invalid or if the texture is not managed by Direct3D. 
	*/
}

// Sets the maximum level of detail (LOD) for a managed mipmap surface. This method 
// succeeds only on managed textures.
HRESULT __stdcall IDirectDrawSurfaceWrapper::SetLOD(LPDWORD lpdwMaxLOD)
{
	debugMessage(0, "IDirectDrawSurfaceWrapper::SetLOD", "Not Implemented");

	/*
	dwMaxLOD [in]
		The maximum LOD value to be set for the mipmap chain if the call succeeds.
	*/

	return DDERR_GENERIC;

	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
	*/
}

// Retrieves the maximum level of detail (LOD) currently set for a managed mipmap 
// surface. This method succeeds only on managed textures. 
HRESULT __stdcall IDirectDrawSurfaceWrapper::GetLOD(DWORD dwMaxLOD)
{
	debugMessage(0, "IDirectDrawSurfaceWrapper::GetLOD", "Not Implemented");

	/*
	lpdwMaxLOD [out]
		A pointer to a variable that receives the maximum LOD value if the call succeeds
	*/

	return DDERR_GENERIC;
	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
	*/
}

// Default constructo
IDirectDrawSurfaceWrapper::IDirectDrawSurfaceWrapper(IDirectDrawWrapper* parent)
{
	// Set parent
	ddrawParent = parent;

	// Init color keys
	for(int i = 0; i < 4; i++)
	{
		memset(&colorKeys[i], 0, sizeof(DDCOLORKEY));
	}
	// Init overlay
	overlayX = 0;
	overlayY = 0;

	// Init video memory pointers
	rawVideoMem = NULL;
	rgbVideoMem = NULL;

	// Add reference
	AddRef();
	
	debugMessage(2, "IDirectDrawSurfaceWrapper::IDirectDrawSurfaceWrapper", "Created");
}

// Default destructor
IDirectDrawSurfaceWrapper::~IDirectDrawSurfaceWrapper()
{
	// Free memory for internal structures
	if(rawVideoMem != NULL) {
		delete rawVideoMem;
		rawVideoMem = NULL;
	}
	if(rgbVideoMem != NULL) {
		delete rgbVideoMem;
		rgbVideoMem = NULL;
	}

    // Release reference
	Release();

	debugMessage(2, "IDirectDrawSurfaceWrapper::~IDirectDrawSurfaceWrapper", "Destroyed");
}

// Initialize wrapper function
HRESULT IDirectDrawSurfaceWrapper::WrapperInitialize(LPDIRECT3DTEXTURE9 *lpTexture, LPDDSURFACEDESC lpDDSurfaceDesc, DWORD displayModeWidth, DWORD displayModeHeight, DWORD displayWidth, DWORD displayHeight)
{
	//set width and height
	/*if(lpDDSurfaceDesc->dwFlags & DDSD_WIDTH)
	{
		surfaceWidth = lpDDSurfaceDesc->dwWidth;
	}
	else
	{
		surfaceWidth = displayModeWidth;		
	}
	if(lpDDSurfaceDesc->dwFlags & DDSD_HEIGHT)
	{
		surfaceHeight = lpDDSurfaceDesc->dwHeight;
	}
	else
	{
		surfaceHeight = displayModeHeight;
	}

	//allocate virtual video memory raw
	double indexSize = 1;
	if(lpDDSurfaceDesc->ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED1)
	{
		indexSize = 0.125;
	}
	else if(lpDDSurfaceDesc->ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED2)
	{
		indexSize = 0.25;
	}
	else if(lpDDSurfaceDesc->ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED4)
	{
		indexSize = 0.5;
	}
	else if(lpDDSurfaceDesc->ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED8 | lpDDSurfaceDesc->ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXEDTO8)
	{
		indexSize = 1;
	}*/

	surfaceWidth = displayModeWidth;
	surfaceHeight = displayModeHeight;

	surfaceTexture = lpTexture;
	lockVideoMem = nullptr;

	// Allocate virtual video memory RAW
	rawVideoMem = new BYTE[640 * 480];
	if(rawVideoMem == NULL)
	{
		debugMessage(0, "IDirectDrawSurfaceWrapper::WrapperInitialize", "Failed to allocate raw video memory");
		return DDERR_OUTOFMEMORY;
	}
	// Clear rgb memory
	ZeroMemory(rawVideoMem, 640 * 480 * sizeof(BYTE));

	// Allocate virtual video memory RGB
	rgbVideoMem = new UINT32[640 * 480];
	if(rgbVideoMem == NULL) 
	{
		debugMessage(0, "IDirectDrawSurfaceWrapper::WrapperInitialize", "Failed to allocate rgb video memory");
		return DDERR_OUTOFMEMORY;
	}
	// Clear rgb memory
	ZeroMemory(rgbVideoMem, 640 * 480 * sizeof(UINT32));

	// Copy surface description
	memcpy(&surfaceDesc, lpDDSurfaceDesc, sizeof(DDSURFACEDESC));

	char message[2048] = "\0";
	sprintf_s(message, 2048, "Initialized displayModeWidth: %d, displayModeHeight: %d, displayWidth: %d, displayHeight: %d", displayModeWidth, displayModeHeight, displayWidth, displayHeight);
	if(lpDDSurfaceDesc->dwFlags & DDSD_ALL) strcat_s(message, 2048, ", DDSD_ALL");
	if(lpDDSurfaceDesc->dwFlags & DDSD_ALPHABITDEPTH) strcat_s(message, 2048, ", DDSD_ALPHABITDEPTH");
	if(lpDDSurfaceDesc->dwFlags & DDSD_CAPS) strcat_s(message, 2048, ", DDSD_CAPS");
	if(lpDDSurfaceDesc->dwFlags & DDSD_CKDESTBLT) strcat_s(message, 2048, ", DDSD_CKDESTBLT");
	if(lpDDSurfaceDesc->dwFlags & DDSD_CKDESTOVERLAY) strcat_s(message, 2048, ", DDSD_CKDESTOVERLAY");
	if(lpDDSurfaceDesc->dwFlags & DDSD_HEIGHT) strcat_s(message, 2048, ", DDSD_HEIGHT");
	if(lpDDSurfaceDesc->dwFlags & DDSD_LINEARSIZE) strcat_s(message, 2048, ", DDSD_LINEARSIZE");
	if(lpDDSurfaceDesc->dwFlags & DDSD_LPSURFACE) strcat_s(message, 2048, ", DDSD_LPSURFACE");
	if(lpDDSurfaceDesc->dwFlags & DDSD_MIPMAPCOUNT) strcat_s(message, 2048, ", DDSD_MIPMAPCOUNT");
	if(lpDDSurfaceDesc->dwFlags & DDSD_PITCH) strcat_s(message, 2048, ", DDSD_PITCH");
	if(lpDDSurfaceDesc->dwFlags & DDSD_PIXELFORMAT) strcat_s(message, 2048, ", DDSD_PIXELFORMAT");
	if(lpDDSurfaceDesc->dwFlags & DDSD_REFRESHRATE) strcat_s(message, 2048, ", DDSD_REFRESHRATE");
	if(lpDDSurfaceDesc->dwFlags & DDSD_TEXTURESTAGE) strcat_s(message, 2048, ", DDSD_TEXTURESTAGE");
	if(lpDDSurfaceDesc->dwFlags & DDSD_WIDTH) strcat_s(message, 2048, ", DDSD_WIDTH");
	if(lpDDSurfaceDesc->dwFlags & DDSD_ZBUFFERBITDEPTH) strcat_s(message, 2048, ", DDSD_ZBUFFERBITDEPTH");
	debugMessage(2, "IDirectDrawSurfaceWrapper::WrapperInitialize", message);

	return DD_OK;
}