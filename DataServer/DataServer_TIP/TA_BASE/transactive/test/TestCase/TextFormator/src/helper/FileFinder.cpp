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

#include "../Portability.h"

#if defined(__MSC_VER__)

#include <stack>
#include "FileFinder.h"

namespace TextFormator {

FileFinder::FileFinder(const std::string filter, 
                       const std::string directory, 
                       bool include_subdir)
{
    _filters.push_back(filter);
    if (include_subdir)
    {
        findAllFiles(directory);
    }
    else
    {
        findFilesInDirectory(directory);
    }
    reset();
}

FileFinder::FileFinder(Filters filters, 
                       const std::string directory, 
                       bool include_subdir)
{
    _filters = filters;
    if (include_subdir)
    {
        findAllFiles(directory);
    }
    else
    {
        findFilesInDirectory(directory);
    }
    reset();
}

void FileFinder::findAllFiles(const std::string base_dir)
{
    _finddata_t file_data;
    long file_handle;
    std::stack<std::string> dir_stack;
    std::string dir_to_find;
    std::string cur_dir;
    std::string full_path;

    dir_stack.push(base_dir);
    while ( !dir_stack.empty() )
    {
        cur_dir = dir_stack.top();
        findFilesInDirectory(cur_dir);
  
        dir_stack.pop();

        makeFullPath(cur_dir, "*.*", dir_to_find);
   
        if ( ( file_handle = 
                _findfirst(dir_to_find.c_str(), &file_data) ) == -1L )
            continue;

        if ( isDirectory(file_data) )
        {
            makeFullPath(cur_dir, file_data.name, full_path);
            dir_stack.push(full_path);
        }

        while ( _findnext( file_handle, &file_data ) == 0 )
        {
            if (isDirectory(file_data))
            {
                makeFullPath(cur_dir, file_data.name, full_path);
                dir_stack.push(full_path);
            }
        }
    }
}

bool FileFinder::isDirectory(const _finddata_t& find_data)
{
    return ( strcmp(find_data.name, ".")!=0 ) && 
           ( strcmp(find_data.name, "..")!=0 ) && 
           ( find_data.attrib & _A_SUBDIR ) ;
}

void FileFinder::findFilesInDirectory(const std::string directory)
{
    _finddata_t file_data;
    long file_handle;
    std::string dir_to_find;
    std::string full_path;

    for (Filters::iterator i = _filters.begin(); 
         i != _filters.end(); ++i)
    {
        makeFullPath(directory, *i, dir_to_find);

        if ( ( file_handle = 
                _findfirst(dir_to_find.c_str(), &file_data) ) == -1L )
            continue;

        makeFullPath(directory, file_data.name, full_path);
        _file_paths.push_back(full_path);

        while ( _findnext( file_handle, &file_data ) == 0 )
        {
            makeFullPath(directory, file_data.name, full_path);
            _file_paths.push_back(full_path);
        }
    }
}

bool FileFinder::hasMoreElements()
{
    return _file_paths_pos != _file_paths_end;
}

std::string FileFinder::nextElement()
{
    return *(_file_paths_pos++);
}

void FileFinder::reset()
{
    _file_paths_pos = _file_paths.begin();
    _file_paths_end = _file_paths.end();
}

void FileFinder::makeFullPath(const std::string dir, const std::string file, 
                              std::string& full_path)
{
    full_path = dir;
    full_path += "\\";
    full_path += file;
}

} // namespace TextFormator

#endif // __MSC_VER__