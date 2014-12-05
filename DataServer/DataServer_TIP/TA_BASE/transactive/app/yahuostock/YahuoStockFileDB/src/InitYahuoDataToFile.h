#ifndef __CLASS_INIT_YAHUO_DATA_TO_FILE_H__
#define __CLASS_INIT_YAHUO_DATA_TO_FILE_H__


#include <string>


class CInitYahuoDataToFile
{
public:
	CInitYahuoDataToFile();
	virtual ~CInitYahuoDataToFile();
public:
	void getAndSaveHistoryData(const std::string& strSymbolUse);
private:
	void _SaveDataToFile(const std::string& strSymbolUse, const std::string& strData);


};


#endif //__CLASS_INIT_YAHUO_DATA_TO_FILE_H__
