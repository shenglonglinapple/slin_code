///////////////////////////////////////////////////////////////////
// This program is a demostration about how to use TextFormator.
// It can parse c++/java program and output as colored html.
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
#include "../src/extend/HtmlFormatHandlers.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "This program is a demostration about how to use TextFormator." << std::endl;
        std::cout << "It can parse c++/java program and output as colored html." << std::endl;
        std::cout << "The file java.kwd and cpp.kwd which contain keywords information " << std::endl;
        std::cout << "should be put into the same directory with this program." << std::endl;
        std::cout << std::endl << "Written by Morning, mailto:moyingzz@etang.com" << std::endl;
        std::cout << std::endl << "[Usage]:Htmlize in_file_name out_file_name" << std::endl;
        return -1;
    }

    // open source file
    TextFormator::Lines in_lines;
    std::string in_file_name(argv[1]);
    if (false == TextFormator::FileHelper::open(in_file_name, in_lines))
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

    // htmlize
    TextFormator::Htmlize::BodyFormatHandler bfh;
    bfh.setColorSchema("STRING", "#a600ee");
    bfh.setColorSchema("COMMENT", "#c0dcc0");
    bfh.setColorSchema("IDENTIFIER", "#888888");
    bfh.setColorSchema("KEYWORD", "#a6caf0");
    bfh.setColorSchema("NUMBER", "#ff0000");
    bfh.setColorSchema("OPERATOR", "#0088aa");

    TextFormator::LineFormator lf;
    TextFormator::TokenType html_type_array[] = 
        {"STRING", "COMMENT", "IDENTIFIER", "KEYWORD", "NUMBER", "OPERATOR"};
    TextFormator::TokenTypes html_types(html_type_array, html_type_array+6);
    lf.registFormatHandler(html_types, &bfh);
    lf.format(lp.getTokensInfoList());

    // output
    TextFormator::Lines out_lines = lf.getFormattedLines();
    std::string title = argv[1];
    std::string bgcolor = "#000000";
    std::string head = "<html>\n<head>\n<title>";
    head += title;
    head += "</title>\n<meta name=\"generator\" content=\"TextFormator\">\n</head>\n<body bgcolor=\"";
    head += bgcolor;
    head += "\">\n<pre>\n";
    std::string tail = "</pre>\n</body></html>";
    out_lines.push_front(head);
    out_lines.push_back(tail);

    TextFormator::FileHelper::save(argv[2], out_lines);

    std::cout << "Htmlize " << in_file_name << " successfully." << std::endl;

    return 0;
}