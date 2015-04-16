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

#ifndef _FILE_FINDER_H_
#define _FILE_FINDER_H_

#if defined(__MSC_VER__)
//
#include <io.h>
#include <list>
#include <vector>
#include <string>
//
namespace TextFormator {

/**
 * Helper class used for get and traverse all files 
 * in specified directory and subdirectories.
 *
 * <em>IMPORTANT:</em>This class can only work under Microsoft Visual C++ platform now.
 *
 * @see FileHelper
 */
class FileFinder
{
public:
    typedef std::vector<std::string> Filters;

    /**
     * Constructor for FileFinder.
     * @param filter a string that specify filter you can apply to the file
     * @param directory a string that specify base directory to find, 
     *                  default for current directory, 
     *                  DO NOT end up with character '\'
     * @param include_subdir indicate whether include subdirectories or not
     */
    FileFinder(const std::string filter, 
               const std::string directory = ".", 
               bool  include_subdir = true);

    /**
     * Constructor for FileFinder.
     * @param filters a series of strings that specify filters 
     *               you can apply to the file
     * @param directory a string specify that base directory to find, 
     *                  default for current directory, 
     *                  DO NOT end up with character '\'
     * @param include_subdir indicate whether include subdirectories or not
     */
    FileFinder(Filters filters, 
               const std::string directory = ".", 
               bool include_subdir = true);

    /**
     * Ensure the "position" point to the valid elment.
     * @return true the "position" is valid, 
     *         false the "position" is invalid
     */
    bool hasMoreElements();

    /**
     * Retrieve full path of the current file, 
     * and set the "position" to the next file.
     * @return the full path of the current file
     */
    std::string nextElement();

    /**
     * set the "position" to the start of list.
     * Call this method firstly, if you want to call 
     * hasMoreElements() and nextElement() repeadly.
     */
    void reset();

private:
    typedef std::list<std::string> FilePaths;

    Filters _filters;
    FilePaths _file_paths;
    FilePaths::iterator _file_paths_pos;
    FilePaths::iterator _file_paths_end;

    void findAllFiles(const std::string base_dir);
    bool isDirectory(const _finddata_t& find_data);
    void findFilesInDirectory(const std::string directory);
    void makeFullPath(const std::string dir, const std::string file, 
        std::string& full_path);
};

} // namespace TextFormator

#endif // __WINDOWS__

#endif // _FILE_HELPER_H_