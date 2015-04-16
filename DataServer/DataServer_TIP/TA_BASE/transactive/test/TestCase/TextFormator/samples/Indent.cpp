///////////////////////////////////////////////////////////////////
// This program is a demostration about how to use TextFormator.
// It can parse c++/java program and output indentedly.
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
#include "../src/extend/IndentFormatHandlers.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "This program is a demostration about how to use TextFormator." << std::endl;
        std::cout << "It can parse c++/java program and output indentedly." << std::endl;
        std::cout << "The file java.kwd and cpp.kwd which contain keywords information " << std::endl;
        std::cout << "should be put into the same directory with this program." << std::endl;
        std::cout << std::endl << "Written by Morning, mailto:moyingzz@etang.com" << std::endl;
        std::cout << std::endl << "[Usage]:Indent in_file_name out_file_name" << std::endl;
        return -1;
    }

    // open source file
    TextFormator::Lines in_lines;
    std::string in_file_name(argv[1]);
    if (false == TextFormator::FileHelper::open(argv[1], in_lines))
    {
        std::cout << "Source file open error!" << std::endl;
        return -1;
    }

    // open keyword file
    std::string::size_type pos = in_file_name.find_last_of('.');
    if (pos == std::string::npos)
    {
        std::cout << "Unknown file format!" << std::endl;
        return -1;
    }
    std::string language = in_file_name.substr(pos+1);
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

    // indent
    TextFormator::Indent::space_num = 4;
    TextFormator::Indent::NormalFormatHandler noh;
    TextFormator::Indent::WhitespaceFormatHandler woh;
    TextFormator::Indent::OperatorFormatHandler ooh;

    TextFormator::LineFormator lf;
    TextFormator::TokenType indent_type_array[] = 
        {"NUMBER", "IDENTIFIER", "KEYWORD", "STRING"};
    TextFormator::TokenTypes indent_types(indent_type_array, indent_type_array+4);
    lf.registFormatHandler(indent_types, &noh);
    lf.registFormatHandler("WHITESPACE", &woh);
    lf.registFormatHandler("OPERATOR", &ooh);
    lf.format(lp.getTokensInfoList());

    // output
    TextFormator::Lines out_lines = lf.getFormattedLines();
    TextFormator::FileHelper::save(argv[2], out_lines);

    std::cout << "Indent " << in_file_name << " successfully." << std::endl;

    return 0;
}