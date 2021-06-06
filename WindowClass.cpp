#include "WindowClass.h"

LRESULT WindowClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		
	case WM_KEYDOWN:
	{

	}

	
	case WM_KEYUP:
	{

	}

	
	default:
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
	}
}





LRESULT WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// All other messages pass to the message handler in the system class.
	default:
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
		//return ApplicationHandle->MessageHandler(hwnd, umsg, wparam, lparam);
	}
	}
}

void WindowClass::RegisterWindowClass()
{
	WNDCLASSEX wc;

	m_applicationName = L"MyEngine";

	//��������
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	//ע�ᴰ��
	RegisterClassEx(&wc);
}

void WindowClass::SetupWindowSize()
{
	DEVMODE dmScreenSettings;

	if (FULL_SCREEN)
	{
		// ��ȡ����ֱ���
		screenWidth = GetSystemMetrics(SM_CXSCREEN);
		screenHeight = GetSystemMetrics(SM_CYSCREEN);
		
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		//����ȫ����ʾ
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		posX = posY = 0;
	}
	else
	{
		// �����ڵ�������Ļ�м�
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
		
	
	}


}



bool WindowClass::Initialize(HINSTANCE hInstance, bool fullScreen)
{
	

	RegisterWindowClass();
	SetupWindowSize();

	// ��������
	m_hwnd = CreateWindowEx(
		WS_EX_APPWINDOW, 
		m_applicationName, 
		m_applicationName,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		posX,
		posY,
		screenWidth, 
		screenHeight,
		NULL, 
		NULL, 
		m_hinstance, 
		NULL);

	//��ʾ����
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	//�������
	//ShowCursor(false);

	return true;
}

bool WindowClass::ProcessMessage()
{

	MSG msg;  //������Ϣ
	ZeroMemory(&msg, sizeof(MSG)); // ��ʼ��
	while (
		PeekMessage(
			&msg, //������Ϣ
			m_hwnd,
			0,   
			0,   
			PM_REMOVE) //�����ɾ��
		)
	{
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	}

	// 
	if (msg.message == WM_NULL)
	{
		if (!IsWindow(m_hwnd))
		{
			m_hwnd = NULL; 
			UnregisterClass(m_applicationName, m_hinstance);
			return false;
		}
	}

	return true;
}


WindowClass::~WindowClass()

{
	if (m_hwnd != NULL)
	{
		UnregisterClass(m_applicationName, m_hinstance);
		DestroyWindow(m_hwnd);
	}
}