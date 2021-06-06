#include "S4ModApi.h"
#pragma comment(lib, "S4ModApi")

#ifdef _DEBUG
#include <sstream>
#endif
#include <stdint.h>

// Defines
#define MAX_POSITIONS 3
#define X_UPPER_LEFT_OFFSET 0x1208CE8
#define Y_UPPER_LEFT_OFFSET 0x1208CF8
#define X_SIZE_OFFSET		0x0D695B8
#define Y_SIZE_OFFSET		0x0D695AC

// Statics
static S4API s4; // the interface to the Settlers 4 Mod API
static short savedXPositions[MAX_POSITIONS];
static short savedYPositions[MAX_POSITIONS];
static short lastKeyStates[MAX_POSITIONS];
static char keys[MAX_POSITIONS] = { VK_F5 , VK_F8 , VK_F9 };

void SaveCameraLocation(uint32_t index)
{
	DWORD S4_Main = (DWORD)GetModuleHandleA(NULL);
	DWORD mapSize = s4->MapSize();

	short xUpperLeft = *(short*)(S4_Main + X_UPPER_LEFT_OFFSET);
	short yUpperLeft = *(short*)(S4_Main + Y_UPPER_LEFT_OFFSET);

	short xSize = *(short*)(S4_Main + X_SIZE_OFFSET) * 2;
	short ySize = *(short*)(S4_Main + Y_SIZE_OFFSET) * 2;

	savedYPositions[index] = yUpperLeft + ySize;

	float percentage = savedYPositions[index] / (float)mapSize;

	savedXPositions[index] = xUpperLeft + xSize + (short)(percentage * mapSize * 0.5f);

#ifdef _DEBUG
	std::stringstream ss;
	ss << "Saved screen position x: " << savedXPositions[index] << " and y: " << savedYPositions[index];

	s4->ShowTextMessage(ss.str().c_str(), 0, 0);
#endif
}

void LoadCameraLocation(uint32_t index)
{
	s4->MapSetScreenPos(savedXPositions[index], savedYPositions[index]);

#ifdef _DEBUG
	std::stringstream ss;
	ss << "Loaded screen position x: " << savedXPositions[index] << " and y: " << savedYPositions[index];

	s4->ShowTextMessage(ss.str().c_str(), 0, 0);
#endif
}

HRESULT S4HCALL OnTick(DWORD dwTick, BOOL bHasEvent, BOOL bIsDelayed)
{
	if (bIsDelayed || !s4->IsCurrentlyOnScreen(S4_GUI_ENUM::S4_SCREEN_INGAME))
	{
		return (HRESULT)0;
	}

	if (GetKeyState(VK_CONTROL) & 0x8000)
	{
		for (uint32_t i = 0; i < MAX_POSITIONS; i++)
		{
			char key = keys[i];
			short keyState = GetKeyState(key);

			if (keyState & 0x8000 && keyState != lastKeyStates[i])
			{
				SaveCameraLocation(i);
			}

			lastKeyStates[i] = keyState;
		}
	}
	else
	{
		for (uint32_t i = 0; i < MAX_POSITIONS; i++)
		{
			char key = keys[i];
			short keyState = GetKeyState(key);

			if (keyState & 0x8000 && keyState != lastKeyStates[i])
			{
				LoadCameraLocation(i);
			}

			lastKeyStates[i] = keyState;
		}
	}

	return (HRESULT)0;
}

static void CleanUp()
{
	if (NULL != s4)
	{
		s4->Release();
		s4 = NULL;
	}
};

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		s4 = S4ApiCreate(); // get an interface to the mod api
		if (NULL == s4) break;

		s4->AddTickListener(OnTick);
	}
	break;
    case DLL_THREAD_ATTACH:
		break;
    case DLL_THREAD_DETACH:
		break;
    case DLL_PROCESS_DETACH:
	{
		CleanUp();
	}
        break;
    }
    return TRUE;
}

