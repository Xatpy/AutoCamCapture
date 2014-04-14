#pragma once

#ifndef UTIL_H
#define UTIL_H

#include <string>

namespace Util
{
  std::string                   WStringToString						(const std::wstring& s);	
  std::wstring                  StringToWString						(const std::string& s);	
	char*						getDate								(struct tm *timeptr);	
	char*						getTime								(struct tm *timeptr);	
	bool						checkIfFileExists					(std::string wFile);
}

#endif 