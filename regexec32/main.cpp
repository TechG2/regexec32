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

    // converter
    const size_t newsize = strlen(argv[1]) + 1;
    wchar_t* wcstring = new wchar_t[newsize];
    size_t convertedChars = 0;
    mbstowcs_s(&convertedChars, wcstring, newsize, argv[1], _TRUNCATE);

    // Create wstring for message
    std::wstring message = L"The module \"";
    message += std::wstring(wcstring);
    message += L"\" has been loaded, but entry point DllRegisterServer was not found.\n\nMake sure that \"";
    message += std::wstring(wcstring);
    message += L"\" is a valid OCX or file, then try again.";

    // Dll Load + execute
    HMODULE hModule = LoadLibraryA(argv[1]);
    if (hModule == NULL) {
        return 1;
    }

    MessageBoxW(NULL, message.c_str(), L"RegExec32", MB_ICONERROR | MB_OK);

    // Del dll
    FreeLibrary(hModule);
    FreeConsole();
    return 0;
}
