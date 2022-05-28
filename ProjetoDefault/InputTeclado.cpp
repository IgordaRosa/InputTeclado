// ProjetoDefault.cpp : Define o ponto de entrada para o aplicativo.
//

#include "header.h"

#define MAX_LOADSTRING 100

// Variáveis Globais:
HINSTANCE hInst;                                // instância atual

WCHAR szTitle[MAX_LOADSTRING];                  // O texto da barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // o nome da classe da janela principal

bool focus = true;
bool Fullscreen = false;
int WinX = 1280;
int WinY = 720;
bool vkKeys[256] = { 0 };

// Declarações de encaminhamento de funções incluídas nesse módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Inicializar cadeias de caracteres globais
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJETODEFAULT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realize a inicialização do aplicativo:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
    wcex.hCursor        = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR));
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+2);
    wcex.lpszMenuName   = L"";
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SICON));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd;
   if(Fullscreen)
   {
        hWnd = CreateWindowW(
        szWindowClass,
        szTitle,
        WS_POPUP,
        0,
        0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        nullptr,
        nullptr,
        hInstance,
        nullptr);
   }
   else
   {
        hWnd = CreateWindowW(
        szWindowClass,
        szTitle,
        WS_OVERLAPPED | WS_SYSMENU,
        GetSystemMetrics(SM_CXSCREEN) / 2 - WinX / 2,
        GetSystemMetrics(SM_CYSCREEN) / 2 - WinY / 2,
        WinX,
        WinY,
        nullptr,
        nullptr,
        hInstance,
        nullptr);
   }
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;

    switch (message)
    {
    case WM_KILLFOCUS:
        //strcpy(msg,"até mais!!");
        focus = false;
        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_SETFOCUS:
        //strcpy(msg, "bem vindo!!");
        focus = true;
        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_KEYDOWN:
        vkKeys[wParam] = true;
        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_KEYUP:
        vkKeys[wParam] = false;
        InvalidateRect(hWnd, NULL, TRUE);
        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &rect);

        if (vkKeys[VK_UP])
            DrawText(hdc, L"UP", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        if (vkKeys[VK_DOWN])
            DrawText(hdc, L"DOWN", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        if (vkKeys[VK_LEFT])
            DrawText(hdc, L"LEFT", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        if (vkKeys[VK_RIGHT])
            DrawText(hdc, L"RIGHT", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        if (vkKeys[VK_SPACE])
            DrawText(hdc, L"SPACE", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        rect.bottom -= 100;
        if (focus)
            DrawText(hdc, L"Bem vindo!!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        else
            DrawText(hdc, L"Ate mais!!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hWnd, &ps);

        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
