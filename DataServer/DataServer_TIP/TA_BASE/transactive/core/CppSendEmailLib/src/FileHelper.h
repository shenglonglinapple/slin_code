#ifndef __CLASS_FILE_HELPER_H___
#define __CLASS_FILE_HELPER_H___

#include "core/utilities/src/UtilitiesCommonDef.h"

//
#include <string>
#include <vector>
//
NS_BEGIN(TA_Base_Core)


class FileHelper
{
private:
	enum 
	{ 
		buffer_size = 3000 
	};
public:
	FileHelper();
	virtual ~FileHelper();
public:
    // used to open binary file
    static bool open(const std::string filename, std::string& content);

    // used to open text file
    static bool open(const std::string file_name, std::vector<std::string>& lines);

};

NS_END(TA_Base_Core)

#endif // _FILE_HELPER_H_

