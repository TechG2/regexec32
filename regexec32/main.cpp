#include <windows.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }

    // console
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONIN$", "r", stdin);
    freopen_s(&fp, "CONOUT$", "w", stdout);
    freopen_s(&fp, "CONOUT$", "w", stderr);

    // Dll Load + execute
    HMODULE hModule = LoadLibraryA(argv[1]);
    if (hModule == NULL) {
        return 1;
    }

    MessageBox(NULL, L"test", L"Error", MB_ICONERROR | MB_OK);

    // Del dll
    FreeLibrary(hModule);
    FreeConsole();
    return 0;
}
