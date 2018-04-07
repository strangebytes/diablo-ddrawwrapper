#include "DirectDrawWrapper.h"

/*******************
**IUnknown methods**
********************/

// Retrieves pointers to the supported interfaces on an object.
HRESULT __stdcall IDirectDrawPaletteWrapper::QueryInterface(REFIID riid, LPVOID FAR * ppvObj)
{		
	debugMessage(1, "IDirectDrawPaletteWrapper::QueryInterface", "Partially Implemented");

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
ULONG __stdcall IDirectDrawPaletteWrapper::AddRef()
{
	debugMessage(1, "IDirectDrawPaletteWrapper::AddRef", "Partially Implemented");

	// Increment reference count
	ReferenceCount++;
	// Return current reference count
	return ReferenceCount;
}

// Decrements the reference count for an interface on an object.
ULONG __stdcall IDirectDrawPaletteWrapper::Release()
{
	debugMessage(1, "IDirectDrawPaletteWrapper::Release", "Partially Implemented");

	// Decrement reference count
	ReferenceCount--;
	// If reference count reaches 0 then free object
	if(ReferenceCount == 0)
	{
		// Free objects
		if(rawPalette != NULL) delete rawPalette;
		if(rgbPalette != NULL) delete rgbPalette;
	}
	// Return new reference count
	return ReferenceCount;
}

/*****************************
**IDirectDrawPalette methods**
******************************/

// Retrieves the capabilities of the palette object.
HRESULT __stdcall IDirectDrawPaletteWrapper::GetCaps(LPDWORD lpdwCaps)
{
	debugMessage(1, "IDirectDrawPaletteWrapper::GetCaps", "Partially Implemented");

	// lpdwCaps cannot be null
	if(lpdwCaps == NULL) return DDERR_INVALIDPARAMS;
	
	// set return data to current palette caps
	*lpdwCaps = paletteCaps;

	return DD_OK;
}

// Retrieves palette values from a DirectDrawPalette object. 
HRESULT __stdcall IDirectDrawPaletteWrapper::GetEntries(DWORD dwFlags, DWORD dwBase, DWORD dwNumEntries, LPPALETTEENTRY lpEntries)
{    
	// lpEntries cannot be null and dwFlags must be 0
	if(lpEntries == NULL) return DDERR_INVALIDPARAMS;

	// Copy raw palette entries to lpEntries(size dwNumEntries) starting at dwBase
	memcpy(lpEntries, &(rawPalette[dwBase]), sizeof(PALETTEENTRY) * min(dwNumEntries, entryCount - dwBase));

	/* 
    // NOTE: Debugging disabled for performance
    debugMessage(2, "IDirectDrawPaletteWrapper::GetEntries", "Retrieved Palette Entries");

    char message[2048] = "\0";
	sprintf_s(message, 2048, "dwBase: %d, dwNumEntries: %d", dwBase, dwNumEntries);
	debugMessage(2, "IDirectDrawPaletteWrapper::GetEntries", message);
    */
    
	// dwNumEntries is the number of palette entries that can fit in the array that lpEntries 
    // specifies. The colors of the palette entries are returned in sequence, from the value
    // of the dwStartingEntry parameter through the value of the dwCount parameter minus 1. 
    // (These parameters are set by IDirectDrawPalette::SetEntries.) 

	return DD_OK;
}

// Initializes the DirectDrawPalette object.
HRESULT __stdcall IDirectDrawPaletteWrapper::Initialize(LPDIRECTDRAW lpDDW, DWORD dwFlags, LPPALETTEENTRY lpDDColorTable)
{
	debugMessage(1, "IDirectDrawPaletteWrapper::Initialize", "Partially Implemented");

	// This method always returns already initialized
	return DDERR_ALREADYINITIALIZED;
}

// Changes entries in a DirectDrawPalette object immediately.
HRESULT __stdcall IDirectDrawPaletteWrapper::SetEntries(DWORD dwFlags, DWORD dwStartingEntry, DWORD dwCount, LPPALETTEENTRY lpEntries)
{
	// lpEntries cannot be null and dwFlags must be 0
	if(lpEntries == NULL) return DDERR_INVALIDPARAMS;

	// Copy raw palette entries from dwStartingEntry and of count dwCount
	memcpy(&(rawPalette[dwStartingEntry]), lpEntries, sizeof(PALETTEENTRY) * min(dwCount, entryCount - dwStartingEntry));

	// Translate new raw pallete entries to RGB(make sure not to go off the end of the memory)
	for(int i = dwStartingEntry; i < min(dwStartingEntry + dwCount, entryCount - dwStartingEntry); i++)
	{
		// Translate the raw palette to ARGB
		if(hasAlpha)
		{
			// Include peFlags as 8bit alpha
			rgbPalette[i] = rawPalette[i].peFlags << 24;
			rgbPalette[i] |= rawPalette[i].peRed << 16;
			rgbPalette[i] |= rawPalette[i].peGreen << 8;
			rgbPalette[i] |= rawPalette[i].peBlue;
		}
		else
		{
			// Alpha is always 255
			rgbPalette[i] = 0xFF000000;
			rgbPalette[i] |= rawPalette[i].peRed << 16;
			rgbPalette[i] |= rawPalette[i].peGreen << 8;
			rgbPalette[i] |= rawPalette[i].peBlue;
		}
	}

	/* 
    // NOTE: Debugging disabled for performance
    debugMessage(2, "IDirectDrawPaletteWrapper::SetEntries", "Set Palette Entries");

	char message[2048] = "\0";
	sprintf_s(message, 2048, "dwStartingEntry: %d, dwCount: %d", dwStartingEntry, dwCount);
	debugMessage(2, "IDirectDrawPaletteWrapper::SetEntries", message); */

	return DD_OK;
}

// Default constructor
IDirectDrawPaletteWrapper::IDirectDrawPaletteWrapper()
{
	// Init vars
	rgbPalette = NULL;
	rawPalette = NULL;

	ReferenceCount = 0;
	paletteCaps = 0;
	
	entryCount = 0;
	hasAlpha = false;

	// Create with flags
	AddRef();

	debugMessage(2, "IDirectDrawPaletteWrapper::IDirectDrawPaletteWrapper", "Created");
}

// Default destructor
IDirectDrawPaletteWrapper::~IDirectDrawPaletteWrapper()
{
	// Free used memory
	if(rgbPalette != NULL) 
	{
		delete rgbPalette;
		rgbPalette = NULL;
	}
	if(rawPalette != NULL)
	{
		delete rawPalette;
		rawPalette = NULL;
	}

	// Clean up
	Release();

	debugMessage(2, "IDirectDrawPaletteWrapper::~IDirectDrawPaletteWrapper", "Destroyed");
}

// Initialize wrapper function
HRESULT IDirectDrawPaletteWrapper::WrapperInitialize(DWORD dwFlags, LPPALETTEENTRY lpDDColorArray, LPDIRECTDRAWPALETTE FAR *lplpDDPalette)
{
	// Save palette caps
	paletteCaps = dwFlags;

	// Default to 256 entries
	entryCount = 256;

	// Create palette of requested bit size
	if(dwFlags & DDPCAPS_1BIT)
	{
		entryCount = 2;
	}
	else if(dwFlags & DDPCAPS_2BIT)
	{
		entryCount = 4;
	}
	else if(dwFlags & DDPCAPS_4BIT)
	{
		entryCount = 16;
	}
	else if(dwFlags & DDPCAPS_8BIT || dwFlags & DDPCAPS_ALLOW256)
	{
		entryCount = 256;
	}

	// Allocate raw ddraw palette
	rawPalette = new PALETTEENTRY[entryCount];
	// Memory failed to allocate, return out of memory
	if(rawPalette == NULL) 
	{
		debugMessage(0, "IDirectDrawPaletteWrapper::WrapperInitialize", "Failed to allocate raw palette memory");
		return DDERR_OUTOFMEMORY;
	}

	// Copy inital palette into raw palette
	memcpy(rawPalette, lpDDColorArray, sizeof(PALETTEENTRY) * entryCount);
	
	// Check flags for alpha
	if(dwFlags & DDPCAPS_ALPHA)
	{
		hasAlpha = true;
	}
	else
	{
		hasAlpha = false;
	}

	// Allocate rgb palette
	rgbPalette = new UINT32[entryCount];
	// Memory failed to allocate, return out of memory
	if(rgbPalette == NULL) 
	{
		debugMessage(0, "IDirectDrawPaletteWrapper::WrapperInitialize", "Failed to allocate RGB palette memory");
		return DDERR_OUTOFMEMORY;
	}
	
	// For all entries
	for(int i = 0; i < entryCount; i++)
	{
		// Translate the raw palette to ARGB
		if(hasAlpha)
		{
			// Include peFlags as 8bit alpha
			rgbPalette[i] = rawPalette[i].peFlags << 24;
			rgbPalette[i] |= rawPalette[i].peRed << 16;
			rgbPalette[i] |= rawPalette[i].peGreen << 8;
			rgbPalette[i] |= rawPalette[i].peBlue;
		}
		else
		{
			// Alpha is always 255
			rgbPalette[i] = 0xFF000000;
			rgbPalette[i] |= rawPalette[i].peRed << 16;
			rgbPalette[i] |= rawPalette[i].peGreen << 8;
			rgbPalette[i] |= rawPalette[i].peBlue;
		}
	}

	char message[2048] = "\0";
	sprintf_s(message, 2048, "Initialized");
	if(dwFlags & DDPCAPS_1BIT) strcat_s(message, 2048, ", DDPCAPS_1BIT");
	if(dwFlags & DDPCAPS_2BIT) strcat_s(message, 2048, ", DDPCAPS_2BIT");
	if(dwFlags & DDPCAPS_4BIT) strcat_s(message, 2048, ", DDPCAPS_4BIT");
	if(dwFlags & DDPCAPS_8BIT) strcat_s(message, 2048, ", DDPCAPS_8BIT");
	if(dwFlags & DDPCAPS_8BITENTRIES) strcat_s(message, 2048, ", DDPCAPS_8BITENTRIES");
	if(dwFlags & DDPCAPS_ALPHA) strcat_s(message, 2048, ", DDPCAPS_ALPHA");
	if(dwFlags & DDPCAPS_ALLOW256) strcat_s(message, 2048, ", DDPCAPS_ALLOW256");
	if(dwFlags & DDPCAPS_INITIALIZE) strcat_s(message, 2048, ", DDPCAPS_INITIALIZE");
	if(dwFlags & DDPCAPS_PRIMARYSURFACE) strcat_s(message, 2048, ", DDPCAPS_PRIMARYSURFACE");
	if(dwFlags & DDPCAPS_PRIMARYSURFACELEFT) strcat_s(message, 2048, ", DDPCAPS_PRIMARYSURFACELEFT");
	if(dwFlags & DDPCAPS_VSYNC) strcat_s(message, 2048, ", DDPCAPS_VSYNC");
	debugMessage(2, "IDirectDrawPaletteWrapper::WrapperInitialize", message);
	
    // Success
	return DD_OK;
}