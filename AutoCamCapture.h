#pragma once

#ifndef CAM_CAPTURE_H
#define CAM_CAPTURE_H

//#include "stdafx.h"

#include <time.h>
#include <string>

class AutoCamCapture
{
	public: //static methods
    static AutoCamCapture*					GetInstance													();

		bool							CapturePhoto												();

	private:	  
		bool							ConvertImageBMPToJPG										(std::wstring wFile);

	private:
										AutoCamCapture													()								{};
  private: //data
		static AutoCamCapture*				pInstance;
};

#endif