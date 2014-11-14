#include "core/CppSendEmailLib/src/FileHelper.h"

#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>

NS_BEGIN(TA_Base_Core)

TA_Base_Core::FileHelper::FileHelper()
{

}

TA_Base_Core::FileHelper::~FileHelper()
{

}



bool FileHelper::open( const std::string filename, std::string& content )
{
	FILE *file = fopen(filename.c_str(), "rb");

	if (file == NULL)
		return false;

	fseek(file, 0, SEEK_END);
	int len = ftell(file);
	rewind(file);

	char *buffer = new char[len];
	fread(buffer, sizeof(char), len, file);
	content.assign(buffer, len);
	delete[] buffer;
	buffer = NULL;

	fclose(file);
	return true;
}

bool FileHelper::open( const std::string file_name, std::vector<std::string>& lines )
{
	std::ifstream file(file_name.c_str(), std::ios::in);
	if (!file) 
	{
		return false;
	}

	lines.clear();
	char buffer[buffer_size];

	while (file.getline(buffer, buffer_size, '\n'))
	{
		lines.push_back(buffer);
	}

	return true;
}

NS_END(TA_Base_Core)

