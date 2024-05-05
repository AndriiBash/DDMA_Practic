#include "stdafx.h"
#include "AsyncClient.h"
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define MAX_LOADSTRING 100

HINSTANCE hInst;
TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI NetThread(LPVOID lpParam)
{
  SOCKET sClient;
  char szBuffer[1024];
  int ret, i;
  struct sockaddr_in server;
  struct hostent* host = NULL;
  char szServerName[1024], szMessage[1024];
  strcpy(szMessage, "Hello! This is asynchronous server");
  strcpy(szServerName, "127.0.0.1");
  sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sClient == INVALID_SOCKET) {
    MessageBox(0, (LPCSTR)"Can't create socket", (LPCSTR)"Error", 0);
    return 1;
  }
  server.sin_family = AF_INET;
  server.sin_port = htons(777);
  server.sin_addr.s_addr = inet_addr(szServerName);
  if (server.sin_addr.s_addr == INADDR_NONE) 
  {
    host = gethostbyname(szServerName);
    if (host == NULL)
    {
      MessageBox(0, (LPCSTR)"Unable to resolve server",
        (LPCSTR)"Error", 0);
      return 1;
    }
    CopyMemory(&server.sin_addr, host->h_addr_list[0], host->h_length);
  }

  if (connect(sClient, (struct sockaddr*)&server, sizeof(server)) ==
    SOCKET_ERROR)
  {
    MessageBox(0, (LPCSTR)"Connect failed", (LPCSTR)"Error", 0);
    return 1;
  }

  ret = send(sClient, szMessage, strlen(szMessage), 0);

  if (ret == SOCKET_ERROR)
  {
    MessageBox(0, (LPCSTR)"Send failed", (LPCSTR)"Error", 0);
  }

  Sleep(1000);
  char szRecvBuff[1024 * 10];
  ret = recv(sClient, szRecvBuff, sizeof(szRecvBuff), 0);

  if (ret != SOCKET_ERROR)
  {
    MessageBox(0, (LPCSTR)szRecvBuff, (LPCSTR)"Received data", 0);
  }
  else
  {
    MessageBox(0, (LPCSTR)"Recv failed", (LPCSTR)"Error", 0);
  }
  closesocket(sClient);
}
int APIENTRY _tWinMain(HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPTSTR lpCmdLine,
  int nCmdShow)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);
  MSG msg;
  HACCEL hAccelTable;
  LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadString(hInstance, IDC_ASYNCCLIENT, szWindowClass, MAX_LOADSTRING);
  MyRegisterClass(hInstance);

  if (!InitInstance(hInstance, nCmdShow))
  {
    return FALSE;
  }

  hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASYNCCLIENT));
  WSADATA wsd;

  if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
  {
    MessageBox(0, (LPCSTR)"Can't load WinSock", (LPCSTR)"Error", 0);
    return 0;
  }

  HANDLE hNetThread;
  DWORD dwNetThreadld;
  hNetThread = CreateThread(NULL, 0, NetThread, 0, 0, &dwNetThreadld);

  while (GetMessage(&msg, NULL, 0, 0))
  {
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  WSACleanup();
  return (int)msg.wParam;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
  WNDCLASSEX wcex;
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASYNCCLIENT));
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = MAKEINTRESOURCE(IDC_ASYNCCLIENT);
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
  return RegisterClassEx(&wcex);
}
