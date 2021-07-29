#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <direct.h>
#include <io.h> 
#include <conio.h>
#include <urlmon.h>
#include <objidl.h>
#include <cstdio>
#include <wininet.h>
#include <shlobj.h>
#include "tinyxml.h"

#pragma comment(lib,"urlmon.lib")
#pragma comment(lib, "user32.lib")

//#define NO_WIN32_LEAN_AND_MEAN 

using namespace std;

void Stealth()
{
    HWND Stealth;
    AllocConsole();
    Stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(Stealth, 0);
}

int ApplyWallpaper(const char* szFileDir, int displayStyle)
{

    WCHAR wsz[MAX_PATH];
    MultiByteToWideChar(
        CP_ACP,
        0,
        szFileDir,
        -1,
        wsz,
        MAX_PATH
    );
    CoInitialize(NULL);
    std::wstring x = wsz;

    DWORD dwStyle = displayStyle;
    HRESULT hr;
    IActiveDesktop* pIAD;
    hr = CoCreateInstance(CLSID_ActiveDesktop, NULL, CLSCTX_INPROC_SERVER,
        IID_IActiveDesktop, (void**)&pIAD);
    if (!SUCCEEDED(hr))
    {
        int errNum = GetLastError();
        return errNum;
    }
    hr = pIAD->SetWallpaper(x.c_str(), 0);
    if (!SUCCEEDED(hr))
    {
        int errNum = GetLastError();
        return errNum;
    }
    WALLPAPEROPT wpo;
    wpo.dwSize = sizeof(wpo);
    wpo.dwStyle = dwStyle;
    hr = pIAD->SetWallpaperOptions(&wpo, 0);
    if (!SUCCEEDED(hr))
    {
        int errNum = GetLastError();
        return errNum;
    }
    hr = pIAD->ApplyChanges(AD_APPLY_ALL);
    if (!SUCCEEDED(hr))
    {
        int errNum = GetLastError();
        return errNum;
    }
    pIAD->Release();

    CoUninitialize();
    return TRUE;
}

void get_pic_url()
{
    TiXmlDocument doc;
    const char* xmlFile = "C:\\Program Files\\The0d0re C00per\\Bing Backgrouds\\XML\\INDEX.xml";
    if (doc.LoadFile(xmlFile))
    {
        cout << "Load file -----------------> DONE" << endl;
    }
    else {
        cout << "Can not parse xml!!" << endl;
        MessageBoxA(NULL, "Can not parse xml!! Please restart the program and try again!!", "WARNING!", MB_OK);
    }

    TiXmlElement* images = doc.RootElement();
    TiXmlElement* image = images->FirstChildElement("image");

    string WebPicturedomain = "http://www.bing.com";
    string WebPictureUrl = "";

    if (image != NULL)
        WebPictureUrl = image->FirstChildElement("url")->GetText();

    string WebPictureFullpath = WebPicturedomain + WebPictureUrl;
    cout << "Today Wallpaper Url Successful analysis!" << std::endl;
    cout << "The address is:" << std::endl;
    cout << WebPictureFullpath << std::endl;

    string pic_FolderPath = "C:\\Program Files\\The0d0re C00per\\Bing Backgrouds\\PIC";
    if (0 != _access(pic_FolderPath.c_str(), 0))
    {
        _mkdir(pic_FolderPath.c_str());
    }

    string pic_url = WebPictureFullpath;
    size_t len0 = pic_url.length();
    int nmlen0 = MultiByteToWideChar(CP_ACP, 0, pic_url.c_str(), len0 + 1, NULL, 0);
    wchar_t* buffer0 = new wchar_t[nmlen0];
    MultiByteToWideChar(CP_ACP, 0, pic_url.c_str(), len0 + 1, buffer0, nmlen0);
    HRESULT hr0 = URLDownloadToFile(NULL, buffer0, _T("C:\\Program Files\\The0d0re C00per\\Bing Backgrouds\\PIC\\Today Wallpaper.png"), 0, NULL);
    if (hr0 == S_OK)
    {
        cout << "Wallpaper Successfully Download!!!" << std::endl;

        if (ApplyWallpaper("C:\\Program Files\\The0d0re C00per\\Bing Backgrouds\\PIC\\Today Wallpaper.png", 0))
        {
            std::cout << "Wallpaper Set!!" << std::endl;
            MessageBoxA(NULL, "Wallpaper Set!!", "Bing Backgrounds Getter", MB_OK);
        }
        else
        {
            std::cout << "Failed to Set Wallpaper!!" << std::endl;
            MessageBoxA(NULL, "Failed to Set Wallpaper!!", "WARNING!", MB_OK);
        }
    }
    else
    {
        std::cout << "Wallpaper download failed!Please check whether the network connection is normal!" << std::endl;
        MessageBoxA(NULL, "Wallpaper download failed!Please check whether the network connection is normal!", "WARNING!", MB_OK);
    }
}


/*
int _tmain(int argc, char* argv[])
{
    Stealth();
    string xml_FolderPath = "C:\\Program Files\\The0d0re C00per\\Bing Backgrouds\\XML";
    if (0 != _access(xml_FolderPath.c_str(), 0))
    {
        _mkdir(xml_FolderPath.c_str());
    }
    string xml_url = "https://cn.bing.com/HPImageArchive.aspx?format=xml&idx=0&n=1";
    size_t len = xml_url.length();
    int nmlen = MultiByteToWideChar(CP_ACP, 0, xml_url.c_str(), len + 1, NULL, 0);
    wchar_t* buffer = new wchar_t[nmlen];
    MultiByteToWideChar(CP_ACP, 0, xml_url.c_str(), len + 1, buffer, nmlen);
    HRESULT hr = URLDownloadToFile(NULL, buffer, _T("C:\\Program Files\\The0d0re C00per\\Bing Backgrouds\\XML\\INDEX.xml"), 0, NULL);
    if (hr == S_OK)
    {
        cout << "Download XML -----------------> DONE" << endl;
        get_pic_url();
    }
    else
    {
        std::cout << "Xml download failed!Please check whether the network connection is normal!" << std::endl;
        MessageBoxA(NULL, "Xml download failed!Please check whether the network connection is normal!", "WARNING!", MB_OK);
        return 0;
    }

    return 0;
}*/

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    Stealth();
    string xml_FolderPath = "C:\\Program Files\\The0d0re C00per\\Bing Backgrouds\\XML";
    if (0 != _access(xml_FolderPath.c_str(), 0))
    {
        _mkdir(xml_FolderPath.c_str());
    }
    string xml_url = "https://cn.bing.com/HPImageArchive.aspx?format=xml&idx=0&n=1";
    size_t len = xml_url.length();
    int nmlen = MultiByteToWideChar(CP_ACP, 0, xml_url.c_str(), len + 1, NULL, 0);
    wchar_t* buffer = new wchar_t[nmlen];
    MultiByteToWideChar(CP_ACP, 0, xml_url.c_str(), len + 1, buffer, nmlen);
    HRESULT hr = URLDownloadToFile(NULL, buffer, _T("C:\\Program Files\\The0d0re C00per\\Bing Backgrouds\\XML\\INDEX.xml"), 0, NULL);
    if (hr == S_OK)
    {
        cout << "Download XML -----------------> DONE" << endl;
        get_pic_url();
    }
    else
    {
        std::cout << "Xml download failed!Please check whether the network connection is normal!" << std::endl;
        MessageBoxA(NULL, "Xml download failed!Please check whether the network connection is normal!", "WARNING!", MB_OK);
        return 0;
    }

    return 0;
}