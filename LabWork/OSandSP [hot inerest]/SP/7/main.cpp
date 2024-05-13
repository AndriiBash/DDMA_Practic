#include <windows.h>
#include <winuser.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <stdio.h>

using namespace std;


int main()
{
    LONG lResult;
    LONG lResult1;
    HKEY hKey;
    PCTSTR lpSubKey = TEXT("HelloKey\\");

    const int BUFFER_SIZE = 8192;
    wchar_t value[BUFFER_SIZE];

    DWORD bufferSize = BUFFER_SIZE;
    DWORD val;
    DWORD dataSize = sizeof(DWORD);
    HKEY h;

    if (RegCreateKeyEx(HKEY_CURRENT_USER, lpSubKey, 0, NULL,
        REG_SZ, KEY_WRITE, NULL, &h, NULL)!= ERROR_SUCCESS)
    {
        printf("Could not create the registry key.");
        abort();
    }

    lResult = RegOpenKeyEx(HKEY_CURRENT_USER,lpSubKey,0,KEY_SET_VALUE,&hKey);

    if (lResult != ERROR_SUCCESS)
    {
        printf("Key not found.\n");
        return FALSE;
    }

    PCTSTR lpName = TEXT("Param_1");
    PCTSTR lpValueEx = TEXT("Hello My Text");

    string s = "";

    wcout << "Input string param" << endl;

    getline(cin, s);

    wstring temp(s.begin(), s.end());

    lpValueEx = temp.c_str();

   
    lResult = RegSetValueEx(hKey,lpName,0, REG_SZ,(LPBYTE)lpValueEx,(DWORD)(lstrlen(lpValueEx) + 1)*sizeof(TCHAR));
    
    if (lResult != ERROR_SUCCESS)
    {
        printf("Function fails.\n");
        return FALSE;
    }


    PCTSTR lpParam = TEXT("Param_DWORD");
    DWORD par = 1000;

    wcout << "Input DWORD param" << endl;
    cin >> par;

    lResult1 = RegSetValueEx(hKey, lpParam, 0, REG_DWORD, (LPBYTE)&par, sizeof(par));

    if (lResult1 != ERROR_SUCCESS)
    {
        printf("Function fails.\n");
        return FALSE;
    }


    if (RegGetValue(HKEY_CURRENT_USER, lpSubKey, lpName, RRF_RT_ANY, nullptr, (PVOID)&value, &bufferSize) == ERROR_SUCCESS)
    {
        wcout << L"Display param string: " << value << endl;
    }

    if (RegGetValue(HKEY_CURRENT_USER, lpSubKey, lpParam, RRF_RT_REG_DWORD, nullptr, (PVOID)&val, &dataSize) == ERROR_SUCCESS)
    {
        wcout << L"Display param DWORD: " << val << endl;
    }

    int ind = 0;
    wcout << "Delete Value? 1 to delete 0 othrewise" << endl;
    cin >> ind;
    if (ind == 1) RegDeleteValue(h, lpParam);
    
    wcout << "Delete Key? 1 to delete 0 othrewise" << endl;
    cin >> ind;
    if (ind == 1)  RegDeleteKey(h, lpSubKey);

    lResult = RegCloseKey(hKey);
    return 0;
}

