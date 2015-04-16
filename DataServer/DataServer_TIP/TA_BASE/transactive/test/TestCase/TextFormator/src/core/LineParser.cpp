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

#include <iostream>
#include "LineParser.h"
#include "DefaultParseHandler.h"

namespace TextFormator {

LineParser::LineParser()
{
    // regist the default parse handler
    registParseHandler(new DefaultParseHandler());
}

LineParser::~LineParser()
{
    // delete the default parse handler
    delete _parse_handlers.rbegin()->second;
}

void LineParser::registParseHandler(ParseHandler* handler)
{
    _parse_handlers.insert(ParseHandlers::value_type(handler->getPriority(), handler));
}

void LineParser::unreigistParseHandler(ParseHandler* handler)
{
    for (ParseHandlers::iterator i=_parse_handlers.begin(); 
         i != _parse_handlers.end(); ++i)
    {
        if (i->second != handler)
            continue;
        _parse_handlers.erase(i);
        break;
    }
}

void LineParser::parse(Lines& lines)
{
    Context context;
    // be necessary if you call this method repeatedly
    _tokens_info_list.clear();
    for (Lines::iterator i=lines.begin(); i!=lines.end(); ++i)
    {
        TokensInfo tokens_info;
        parseLine(*i, tokens_info, context);
        _tokens_info_list.push_back(tokens_info);
    }
}

void LineParser::parseLine(const Line& line, TokensInfo& tokens_info, Context& context)
{
    Line::size_type pos = 0;
    TokenInfo token_info;
    do
    {
        for (ParseHandlers::iterator i=_parse_handlers.begin(); 
             i != _parse_handlers.end(); ++i)
        {
            if (!i->second->accept(line, pos, context, token_info))
                continue;
            tokens_info.push_back(token_info);
            break;
        }
    }
    while (pos < line.length());
}

TokensInfoList& LineParser::getTokensInfoList()
{
    return _tokens_info_list;
}

} // namespace TextFormator