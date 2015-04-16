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

#include <fstream>
#include "FileHelper.h"

namespace TextFormator {

void FileHelper::save(std::ostream& stream, Lines& lines)
{
    for (Lines::iterator i=lines.begin(); i != lines.end(); ++i)
    {
        stream << (*i).c_str() << std::endl;
    }
}

bool FileHelper::open(const std::string file_name, Lines& lines)
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

bool FileHelper::save(const std::string file_name, Lines& lines)
{
    std::ofstream file(file_name.c_str(), std::ios::out);
    if (!file) 
    {
        return false;
    }

    save(file, lines);

    return true;        
}

} // namespace TextFormator