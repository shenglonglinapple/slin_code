///////////////////////////////////////////////////////////////////
// This program is a demostration about how to use TextFormator.
// It can parse c++/java program and do some simple statistics.
// The file java.kwd and cpp.kwd which contain keywords information 
// should be put into the same directory with this program.
//
// Written by Morning, mailto:moyingzz@etang.com
//
// Date:2003-4
///////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include "../src/GeneralDefine.h"
#include "../src/helper/FileHelper.h"
#include "../src/core/LineParser.h"
#include "../src/extend/ConcreteParseHandlers.h"
#include "../src/core/LineFormator.h"
#include "../src/extend/CountFormatHandlers.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "This program is a demostration about how to use TextFormator." << std::endl;
        std::cout << "It can parse c++/java program and do some simple statistics." << std::endl;
        std::cout << "The file java.kwd and cpp.kwd which contain keywords information " << std::endl;
        std::cout << "should be put into the same directory with this program." << std::endl;
        std::cout << std::endl << "Written by Morning, mailto:moyingzz@etang.com" << std::endl;
        std::cout << std::endl << "[Usage]:Count filename" << std::endl;
        return -1;
    }

    // open source file
    TextFormator::Lines in_lines;
    std::string file_name(argv[1]);
    if (false == TextFormator::FileHelper::open(file_name, in_lines))
    {
        std::cout << "Source file open error!" << std::endl;
        return -1;
    }

    // open keyword file
    std::string::size_type pos = file_name.find_last_of('.');
    if (pos == std::string::npos)
    {
        std::cout << "Unknown file format!" << std::endl;
        return -1;
    }
    std::string language = file_name.substr(pos+1);
    if (language == "h")
    {
        language = "cpp";
    }
    if (language!="java" && language!="cpp")
    {
        std::cout << "Unknown file format!" << std::endl;
        return -1;
    }
    language += ".kwd";
    TextFormator::Lines keywords;
    if (false == TextFormator::FileHelper::open(language, keywords))
    {
        std::cout << "Keyword file open error!" << std::endl;
        return -1;
    }

    // parse
    TextFormator::StringParseHandler sph;
    TextFormator::CommentParseHandler cph;
    TextFormator::IdentifierParseHandler iph(&keywords);
    TextFormator::NumberParseHandler nph;
    TextFormator::OperatorParseHandler oph;
    TextFormator::WhitespaceParseHandler wph;

    TextFormator::LineParser lp;
    lp.registParseHandler(&sph);
    lp.registParseHandler(&cph);
    lp.registParseHandler(&iph);
    lp.registParseHandler(&nph);
    lp.registParseHandler(&oph);
    lp.registParseHandler(&wph);
    lp.parse(in_lines);

    // count
    TextFormator::Count::KeywordCountHandler kfh;
    TextFormator::Count::CommentCountHandler cfh;
    kfh.setKeywordToCount("void");
    kfh.setKeywordToCount("for");

    TextFormator::LineFormator lf;
    lf.registFormatHandler("KEYWORD", &kfh);
    lf.registFormatHandler("COMMENT", &cfh);
    lf.format(lp.getTokensInfoList());

    // output
    std::cout << "Result of " << file_name << " output as follows:" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << "1)keywords summary" << std::endl;
    std::cout << "  void(" << kfh.getKeywordCount("void") << ")" << std::endl;
    std::cout << "  for(" << kfh.getKeywordCount("for") << ")" << std::endl;
    std::cout << "2)comments summary" << std::endl;
    std::cout << "  total comment:" << cfh.getTotalComment() << std::endl;
    std::cout << "  pure  comment:" << cfh.getPureComment() << std::endl;
    std::cout << "  mixed comment:" << cfh.getMixedComment() << std::endl;

    return 0;
}