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

#ifndef _LINE_PARSER_H_
#define _LINE_PARSER_H_
//
#include "../GeneralDefine.h"
#include "ParseHandler.h"
#include "../helper/Context.h"
#include <map>
//
namespace TextFormator {

/**
 * This class is used to parse text line by line.
 * @see ParseHandler
 */
class LineParser
{
private:
    typedef std::multimap<int, ParseHandler*> ParseHandlers;

    ParseHandlers _parse_handlers;
    TokensInfoList _tokens_info_list;

    void parseLine(const Line& line, TokensInfo& tokens_info, Context& context);

public:
    /**
     * Constructor for LineParser.
     */
    LineParser();

    /**
     * Destructor for LineParser.
     */
    ~LineParser();

    /**
     * Parse text line by line.
     * @param lines an array stand for the text
     */
    void parse(Lines& lines);

    /**
     * regist parse handler.
     * @param handler concrete handler which determines how to parse text
     */
    void registParseHandler(ParseHandler* handler);

    /**
     * unregist parse handler.
     * @param handler concrete handler which determines how to parse text
     */
    void unreigistParseHandler(ParseHandler* handler);

    /**
     * get parsed result, call this method after parse complete.
     * @return a list contain parsed result
     */
    TokensInfoList& getTokensInfoList();
};

} // namespace TextFormator

#endif // _LINE_PARSER_H_