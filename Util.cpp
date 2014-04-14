#include "Util.h"

#include <sstream>
#include <windows.h>

namespace Util
{
std::string WStringToString(const std::wstring& s)
{
  std::string temp(s.length(),' ');
  std::copy(s.begin(),s.end(),temp.begin());
  return temp;
}

std::wstring StringToWString(const std::string& s)
{
  std::wstring temp(s.length(),' ');
  std::copy(s.begin(),s.end(),temp.begin());
  return temp;
}

char* getDate(struct tm *timeptr)
{
  static char result[26]; 

  sprintf(result, "%i_%02i_%02i",	1900 + timeptr->tm_year,
									timeptr->tm_mon + 1, //starts with 0
									timeptr->tm_mday );

  return result;
}

char* getTime(struct tm *timeptr)
{
  static char result[26];

  sprintf(result, "%02i_%02i_%02i",
    timeptr->tm_hour,
    timeptr->tm_min,
    timeptr->tm_sec);


  return result;
}

bool checkIfFileExists(std::string wFile)
{
	if (FILE *file = fopen(wFile.c_str(), "r")) 
	{
      fclose(file);
      return true;
	}
	else 
	{
		return false;
	}
}

}