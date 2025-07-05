#include <napi.h>
#include <windows.h>

Napi::Boolean SetWindowToDesktop(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || !info[0].IsBuffer()) {
        Napi::TypeError::New(env, "Expected a Buffer argument").ThrowAsJavaScriptException();
        return Napi::Boolean::New(env, false);
    }

    // Get HWND from buffer
    HWND hwnd = *reinterpret_cast<HWND*>(info[0].As<Napi::Buffer<char>>().Data());

    // Find the Progman window (the desktop's parent)
    HWND progman = FindWindowW(L"Progman", NULL);
    HWND workerw = NULL;

    // Send message to Progman to spawn WorkerW
    SendMessageTimeoutW(progman, 0x052C, 0, 0, SMTO_NORMAL, 1000, nullptr);

    // Find the WorkerW window
    HWND desktop = NULL;
    HWND shellViewWin = NULL;
    HWND temp = NULL;

    workerw = FindWindowExW(NULL, NULL, L"WorkerW", NULL);
    while (workerw != NULL) {
        temp = FindWindowExW(workerw, NULL, L"SHELLDLL_DefView", NULL);
        if (temp != NULL) {
            shellViewWin = temp;
            desktop = workerw;
            break;
        }
        workerw = FindWindowExW(NULL, workerw, L"WorkerW", NULL);
    }

    if (!desktop) {
        desktop = progman;
    }

    // Set parent
    SetParent(hwnd, desktop);

    return Napi::Boolean::New(env, true);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("setWindowToDesktop", Napi::Function::New(env, SetWindowToDesktop));
    return exports;
}

NODE_API_MODULE(desktop_parent, Init)