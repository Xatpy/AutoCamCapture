#include "AutoCamCapture.h"

#include "Util.h"

#include <windows.h>
#include <gdiplus.h>

#include <iostream>
#include <string>

#include <stdio.h>

//singleton
AutoCamCapture* AutoCamCapture::pInstance = 0;

AutoCamCapture* AutoCamCapture::GetInstance()
{
	if (pInstance == 0)
	{
		pInstance = new AutoCamCapture();
	}
	return pInstance;
}

bool AutoCamCapture::CapturePhoto()
{
	std::string direction="CommandCam.exe ";

	::PROCESS_INFORMATION vProcessInfo;
	::STARTUPINFOA        vStartupInfo;

	::ZeroMemory(&vProcessInfo, sizeof(::PROCESS_INFORMATION));
	::ZeroMemory(&vStartupInfo, sizeof(::STARTUPINFO));
	vStartupInfo.cb = sizeof(::STARTUPINFO);

	//CommandCam program
	//Source: https://github.com/tedburke/CommandCam
	::CreateProcessA("CommandCam.exe ",
           (LPSTR)direction.c_str(),
             NULL,
             NULL,
             FALSE,
             //CREATE_DEFAULT_ERROR_MODE,
						 CREATE_NO_WINDOW,
             NULL,
             NULL,
             &vStartupInfo,
             &vProcessInfo);
	
	std::wstring file = L"image.bmp";
	if (Util::checkIfFileExists(Util::WStringToString(file)))
	{		
		//Created image from camera, I am goint to convert to JPG
		if (ConvertImageBMPToJPG(file))
		{			
			//I delete the BMP image
			remove(Util::WStringToString(file).c_str());
		}
		else
		{
			std::cout << "Error creating JPG image." << std::endl;
			return false;
		}		
	}
	else
	{
		std::cout << "Error capturing photo from web cam. Is cam connected?" << std::endl;
		return false;
	}

	return true;
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	using namespace Gdiplus;

   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}

bool AutoCamCapture::ConvertImageBMPToJPG(std::wstring wFile)
{
	using namespace Gdiplus;

	GdiplusStartupInput startupInput;
	ULONG_PTR token;
	GdiplusStartup(&token, &startupInput, NULL);
	CLSID clsid;
	GetEncoderClsid(L"image/jpeg", &clsid);
	//Bitmap SrcBitmap(L"image.bmp",0);
	Bitmap SrcBitmap(wFile.c_str(),0);
	
	//Al fichero resultante le voy poner de nombre la fecha-hora.jpg
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime ( &rawtime );

	std::string resultFile(Util::getDate(timeinfo));
	resultFile += (Util::getDate(timeinfo));
	resultFile += "-"; //separador entre la fecha y la hora
	resultFile += Util::getTime(timeinfo);
	resultFile += ".jpg";

	std::wstring wnamefile = Util::StringToWString(resultFile);
	const WCHAR *pwcsName (wnamefile.c_str());		  

	if (SrcBitmap.Save(pwcsName, &clsid) == Status::Ok)
		return true;
	else
		return false;
}


