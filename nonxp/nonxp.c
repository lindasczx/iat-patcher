#include "getcpuid.h"
#include <windows.h>

typedef struct {
	unsigned int MMX :1;
	unsigned int SSE :1;
	unsigned int SSE2 :1;
	unsigned int SSE3 :1;
	unsigned int SSE3S :1;
	unsigned int SSE41 :1;
	unsigned int SSE42 :1;
	unsigned int AVX :1;
	unsigned int AVX2 :1;
	unsigned int XOP :1;
} SIMD_VERSION;

int Is2003 = 0;
int Is2003OrGreater = 0;
SIMD_VERSION SIMD_Version = {0};
int __sse2_available = 0;

void GetSIMDVersion() {
	memset(&SIMD_Version, 0, sizeof(SIMD_Version));
	unsigned int CPUInfo[4][4] = {0};
	unsigned int idcount, idcount2;
	getcpuid(CPUInfo[0], 0);
	idcount = CPUInfo[0][0];
	getcpuid(CPUInfo[0], 0x80000000);
	idcount2 = CPUInfo[0][0];
	if (idcount >= 7)
		getcpuidex(CPUInfo[3], 7, 0);
	if (idcount2 >= 1)
		getcpuid(CPUInfo[2], 0x80000001);
	if (idcount >= 1)
		getcpuid(CPUInfo[1], 1);
	if (CPUInfo[3][1] & 0x20)
		SIMD_Version.AVX2 = 1;
	if (CPUInfo[1][2] & 0x10000000)
		SIMD_Version.AVX = 1;
	if (CPUInfo[2][2] & 0x800)
		SIMD_Version.XOP = 1;
	if (CPUInfo[1][2] & 0x100000)
		SIMD_Version.SSE42 = 1;
	if (CPUInfo[1][2] & 0x80000)
		SIMD_Version.SSE41 = 1;
	if (CPUInfo[1][2] & 0x200)
		SIMD_Version.SSE3S = 1;
	if (CPUInfo[1][2] & 0x1)
		SIMD_Version.SSE3 = 1;
	if (CPUInfo[1][3] & 0x4000000)
		SIMD_Version.SSE2 = 1;
	if (CPUInfo[1][3] & 0x2000000)
		SIMD_Version.SSE = 1;
	if (CPUInfo[1][3] & 0x800000)
		SIMD_Version.MMX = 1;

	if (SIMD_Version.SSE2)
		__sse2_available = 1;
}

BOOL WINAPI DllMain (HINSTANCE hInst, DWORD reason, LPVOID reserved)
{
	unsigned int ver, major, minor;
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		GetSIMDVersion();
		ver = GetVersion();
		major = ver & 0xFF;
		minor = ver >> 8 & 0xFF;
		if (major == 5 && minor >= 2 || major >= 6) {
			Is2003OrGreater = 1;
			if (major == 5 && minor == 2)
				Is2003 = 1;
			else
				Is2003 = 0;
		} else {
			Is2003OrGreater = 0;
			Is2003 = 0;
		}
		break;
		
	case DLL_PROCESS_DETACH:
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}
