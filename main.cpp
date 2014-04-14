#include "stdafx.h"

#include <windows.h>
#include <vfw.h>
#include <stdio.h>
#include <iostream>

#include "Timer.h"
#include "AutoCamCapture.h"

int _tmain(int argc, _TCHAR* argv[])
{
	FreeConsole();

	Timer tm;
	tm.start();

	int photoCounter = 0;
	int maxPhotos = 50;
	bool bExit = false;
	int secondsTimer = 5;

	while (!bExit)
	{
		if (tm.isTimeout(secondsTimer))
		{
			tm.start();
			AutoCamCapture::GetInstance()->CapturePhoto();

			/*++photoCounter;
			if (photoCounter > maxPhotos)
			{
				bExit = true;
			}*/
		}
	}
 
	return 0;
}