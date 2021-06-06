#pragma once
#include<Windows.h>

class WindowClass
{
public:

	~WindowClass();

	bool Initialize(HINSTANCE hInstance,bool fullScreen);
	bool ProcessMessage();
	void Shutdown();


	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	void RegisterWindowClass();
	void SetupWindowSize();
	LPCWSTR m_applicationName=NULL;
	HINSTANCE m_hinstance=NULL;
	HWND m_hwnd=NULL;
	int screenWidth=800;
	int screenHeight=600;
	int posX = 0;
	int posY = 0;
	bool FULL_SCREEN=false;


};


////////////////////////////////////////////////////////////////////////////////
//窗口过程函数原型
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


////////////////////////////////////////////////////////////////////////////////
//全局变量 
static WindowClass* ApplicationHandle = NULL;


