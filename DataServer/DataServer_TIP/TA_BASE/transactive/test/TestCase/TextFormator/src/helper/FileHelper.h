////////////////////////////////////////////////////////////////////////////////
// The TextFormator Framework
// Version 0.9 beta
//
// Copyright (c) 2003 by Morning
// http://morningspace.51.net
// mailto:moyingzz@etang.com
//
// Permission to use, copy, modify, distribute and sell this program for any 
// purpose is hereby granted without fee, provided that the above copyright 
// notice appear in all copies and that both that copyright notice and this 
// permission notice appear in supporting documentation.
//
// It is provided "as is" without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

#ifndef _FILE_HELPER_H_
#define _FILE_HELPER_H_
//
#include "../GeneralDefine.h"
#include <string>
#include <iostream>
//
namespace TextFormator {

/**
 * Helper class used for open or save files
 */
class FileHelper
{
private:
    enum { buffer_size = 3000 };

public:
    /**
     * Write lines into output stream
     * @param stream output stream
     * @param lines used to store lines for output
     */
    static void save(std::ostream& stream, Lines& lines);

    /**
     * Read lines from file.
     * @param file_name indicate file to open
     * @param lines used to store lines read from file
     * @return if open sucessfully return true, else return false
     */
    static bool open(const std::string file_name, Lines& lines);
    /**
     * Write lines into file.
     * @param file_name indicate file to save
     * @param lines used to store lines for saving
     * @return if save sucessfully return true, else return false
     */
    static bool save(const std::string file_name, Lines& lines);
};

} // namespace TextFormator

#endif // _FILE_HELPER_H_