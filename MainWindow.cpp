#include "WindowClass.h"




int WINAPI                                  //APIENTRY is an alias for WINAPI.
wWinMain( HINSTANCE hInstance,        // The operating system uses this value to identify the executable (EXE) when it is loaded in memory. 
		  HINSTANCE hPrevInstance,         //hPrevInstance has no meaning. It was used in 16-bit Windows, but is now always zero.
	      LPWSTR lpCmdline,                    //contains the command-line arguments as a Unicode string.
	      int nCmdShow)                        //nCmdShow is a flag that says whether the main application window will be minimized, maximized, or shown normally.
{

		WindowClass window;

		window.Initialize(hInstance, false);

		while (window.ProcessMessage() == true)
		{

		}
		return 0;

}