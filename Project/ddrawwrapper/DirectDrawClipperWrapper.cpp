#include "DirectDrawWrapper.h"

/*******************
**IUnknown methods**
********************/

// Retrieves pointers to the supported interfaces on an object.
HRESULT __stdcall IDirectDrawClipperWrapper::QueryInterface(REFIID riid, LPVOID FAR * ppvObj)
{	
	debugMessage(1, "IDirectDrawClipperWrapper::QueryInterface", "Partially Implemented");

	// Provide the directdraw interface for all versions up to 7
	if(riid == IID_IDirectDrawClipper)
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
ULONG __stdcall IDirectDrawClipperWrapper::AddRef()
{
	debugMessage(1, "IDirectDrawClipperWrapper::AddRef", "Partially Implemented");

	// Increment reference count
	ReferenceCount++;
	// Return current reference count
	return ReferenceCount;
}

// Decrements the reference count for an interface on an object.
ULONG __stdcall IDirectDrawClipperWrapper::Release()
{
	debugMessage(1, "IDirectDrawClipperWrapper::Release", "Partially Implemented");

	// Decrement reference count
	ReferenceCount--;
	// If reference count reaches 0 then free object
	if(ReferenceCount == 0)
	{
		// Free objects here, skip for now
	}
	// Return new reference count
	return ReferenceCount;
}

/*****************************
**IDirectDrawClipper methods**
******************************/

// Retrieves a copy of the clip list that is associated with a DirectDrawClipper 
// object. To select a subset of the clip list, you can pass a rectangle that clips
// the clip list. 
HRESULT __stdcall IDirectDrawClipperWrapper::GetClipList(LPRECT lpRect, LPRGNDATA lpClipList, LPDWORD lpdwSize)
{
	// ***Unimplemented***
	debugMessage(0, "IDirectDrawClipperWrapper::GetClipList", "Not Implemented");

	if(lpClipList == NULL)
	{
		if(lpRect == NULL) {
			// lpdwSize = memory required to hold entire clip list
		}
		else
		{
			// lpdwSize = memory required to clip list in region lpRect
		}
	}
	else
	{
		if(lpRect == NULL) {
			// lpClipList =  RGNDATA structure that receives the resulting copy of the entire clip list.
		}
		else
		{
			// lpClipList =  RGNDATA structure that receives the resulting copy of the clip list in region lpRect
		}
		
	}

	return DDERR_GENERIC;

	/*
    DDERR_GENERIC
    DDERR_INVALIDCLIPLIST
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_NOCLIPLIST
    DDERR_REGIONTOOSMALL
	*/
}

// Retrieves the window handle that was previously associated with this 
// DirectDrawClipper object by the IDirectDrawClipper::SetHWnd method. 
HRESULT __stdcall IDirectDrawClipperWrapper::GetHWnd(HWND FAR *lphWnd)
{
	debugMessage(1, "IDirectDrawClipperWrapper::GetHWnd", "Partially Implemented");

	// lphWnd cannot be null
	if(lphWnd == NULL) return DDERR_INVALIDPARAMS;

	// Set lphWnd to associated window handle
	*lphWnd = hWnd;

	// Success
	return DD_OK;
}

// Initializes a DirectDrawClipper object that was created by using the 
// CoCreateInstance COM function.
HRESULT __stdcall IDirectDrawClipperWrapper::Initialize(LPDIRECTDRAW lpDD, DWORD dwFlags)
{
	debugMessage(1, "IDirectDrawClipperWrapper::Initialize", "Partially Implemented");
	if(lpDD == NULL)
	{
		// An independent DirectDrawClipper object is initialized; a call of this 
		// type is equivalent to using the DirectDrawCreateClipper function. 
	}
	else
	{
		// Call constructor
	}

	// Overload to already init
	return DDERR_ALREADYINITIALIZED;

	/*
    DDERR_ALREADYINITIALIZED
    DDERR_INVALIDPARAMS
	*/
}

// Retrieves the status of the clip list if a window handle is associated
// with a DirectDrawClipper object.
HRESULT __stdcall IDirectDrawClipperWrapper::IsClipListChanged(BOOL FAR *lpbChanged)
{
	// ***Unimplemented***
	debugMessage(0, "IDirectDrawClipperWrapper::Initialize", "Not Implemented");

	// lpbChanged cannot be null
	if(lpbChanged == NULL) return DDERR_INVALIDPARAMS;

	// lpbChanged is TRUE if the clip list has changed, and FALSE otherwise.

	return DDERR_GENERIC;
	
	/*
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
	*/
}

// Sets or deletes the clip list that is used by the IDirectDrawSurface7::Blt,
// IDirectDrawSurface7::BltBatch, and IDirectDrawSurface7::UpdateOverlay methods 
// on surfaces to which the parent DirectDrawClipper object is attached.
HRESULT __stdcall IDirectDrawClipperWrapper::SetClipList(LPRGNDATA lpClipList, DWORD dwFlags)
{
	// ***Unimplemented***
	debugMessage(0, "IDirectDrawClipperWrapper::SetClipList", "Not Implemented");

	//You cannot set the clip list if a window handle is already associated
    // with the DirectDrawClipper objet.
	if(hasHwnd)
	{
		return DDERR_CLIPPERISUSINGHWND;
	}

	// ******NOTE:  If you call IDirectDrawSurface7::BltFast on a surface with an attached 
    // clipper, it returns DDERR_UNSUPPORTED.
	if(lpClipList == NULL)
	{
		// Delete associated clip list if it exists
	}
	else
	{
		// Set clip list to lpClipList
	}

	return DDERR_GENERIC;

	/*
    DDERR_INVALIDCLIPLIST
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_OUTOFMEMORY
	*/
}

// Sets the window handle that the clipper object uses to obtain clipping information
HRESULT __stdcall IDirectDrawClipperWrapper::SetHWnd(DWORD dwFlags, HWND in_hWnd)
{
	debugMessage(1, "IDirectDrawClipperWrapper::SetHWnd", "Partially Implemented");

	hasHwnd = true;
	hWnd = in_hWnd;

	// Load clip list from window

	return DD_OK;
    
	/*
    DDERR_INVALIDCLIPLIST
    DDERR_INVALIDOBJECT
    DDERR_INVALIDPARAMS
    DDERR_OUTOFMEMORY
	*/
}

// Default constructor
IDirectDrawClipperWrapper::IDirectDrawClipperWrapper()
{
	// Init variables
	hasHwnd = false;
	hWnd = NULL;

	ReferenceCount = 0;

	// Add reference
	AddRef();

	debugMessage(2, "IDirectDrawClipperWrapper::IDirectDrawClipperWrapper", "Created");
}

// Default destructor
IDirectDrawClipperWrapper::~IDirectDrawClipperWrapper()
{
	// Release reference
	Release();

	debugMessage(2, "IDirectDrawClipperWrapper::~IDirectDrawClipperWrapper", "Destroyed");
}

// Initialize wrapper function
HRESULT IDirectDrawClipperWrapper::WrapperInitialize(DWORD dwFlags)
{
	debugMessage(2, "IDirectDrawClipperWrapper::WrapperInitialize", "Initialized");
	return DD_OK;
}