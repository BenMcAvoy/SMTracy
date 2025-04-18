#define TRACY_ENABLE
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include "minhook.h"
#include "tracy/Tracy.hpp"

typedef void* (__cdecl* malloc_t)(size_t size);
typedef void* (__cdecl* realloc_t)(void* ptr, size_t new_size);

// Original function pointers
malloc_t original_malloc = nullptr;
realloc_t original_realloc = nullptr;

void* __cdecl hooked_malloc(size_t size) {
	ZoneScopedN("malloc");
    return original_malloc(size);
}

void* __cdecl hooked_realloc(void* ptr, size_t new_size) {
    ZoneScopedN("realloc");
    return original_realloc(ptr, new_size);
}

void* get_crt_symbol(const char* name) {
    HMODULE crt = GetModuleHandleA("ucrtbase.dll");
    if (!crt) crt = GetModuleHandleA("msvcrt.dll");
    return crt ? GetProcAddress(crt, name) : nullptr;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        MH_Initialize();

        void* malloc_addr = get_crt_symbol("malloc");
        void* realloc_addr = get_crt_symbol("realloc");

        if (malloc_addr) {
            MH_CreateHook(malloc_addr, &hooked_malloc, reinterpret_cast<void**>(&original_malloc));
            MH_EnableHook(malloc_addr);
        }

        if (realloc_addr) {
            MH_CreateHook(realloc_addr, &hooked_realloc, reinterpret_cast<void**>(&original_realloc));
            MH_EnableHook(realloc_addr);
        }
    }
    else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
        MH_Uninitialize();
    }
    return TRUE;
}
