///////////////////////////////////////////////////////////////////
// This program is a demostration about how to use TextFormator.
// It can process files as a batch. With this program and other 
// utilities such as Indent, Htmlize, etc., you can process c++
// source programs batchly.
//
// Written by Morning, mailto:moyingzz@etang.com
//
// Date:2003-4
///////////////////////////////////////////////////////////////////

#include <iostream>
#include "../src/Portability.h"
#include "../src/helper/FileFinder.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "This program is a demostration about how to use TextFormator." << std::endl;
        std::cout << "It can process files as a batch. With this program and other" << std::endl;
        std::cout << "utilities such as Indent, Htmlize, etc., you can process c++" << std::endl;
        std::cout << "source programs batchly." << std::endl;
        std::cout << std::endl << "Written by Morning, mailto:moyingzz@etang.com" << std::endl;
        std::cout << std::endl << "[Usage]:Batch command directory" << std::endl;
        return -1;
    }
    TextFormator::FileFinder::Filters filters;
    filters.push_back("*.cpp");
    filters.push_back("*.h");
    TextFormator::FileFinder ff(filters, argv[2], true);

    while (ff.hasMoreElements())
    {
        std::string file_path = ff.nextElement();
        std::string cmd = argv[1];
        cmd += " ";
        cmd += file_path;
        cmd += " ";
        file_path.replace(file_path.find_last_of('.'), 1, 1, '_');
        cmd += file_path.substr(file_path.find_last_of('\\')+1);
        cmd += ".html";
        system(cmd.c_str());
    }

    return 0;
}
