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

#include "LineFormator.h"

namespace TextFormator {

LineFormator::LineFormator()
{
}

LineFormator::~LineFormator()
{
}

Lines& LineFormator::getFormattedLines()
{
    return _formatted_lines;
}

void LineFormator::registFormatHandler(TokenType type, FormatHandler* handler)
{
    _format_handlers.insert(FormatHandlers::value_type(type, handler));
}

void LineFormator::registFormatHandler(TokenTypes types, FormatHandler* handler)
{
    for (TokenTypes::iterator i=types.begin(); 
         i != types.end(); ++i)
    {
         registFormatHandler(*i, handler);
    }
}

void LineFormator::unreigistFormatHandler(FormatHandler* handler)
{
    for (FormatHandlers::iterator i=_format_handlers.begin(); 
         i != _format_handlers.end(); ++i)
    {
        if (i->second != handler)
            continue;
        _format_handlers.erase(i);
    }
}

void LineFormator::format(TokensInfoList& tokens_info_list)
{
    Context context;
    _formatted_lines.clear();
    for (TokensInfoList::size_type i=0; i<tokens_info_list.size(); ++i)
    {
        Line formatted_line;
        if (tokens_info_list[i].size() != 0)
        {
            context.setCurLinePos(i);
            context.setTokensInfo(&(tokens_info_list[i]));
            formatLine(tokens_info_list[i], formatted_line, context);
        }
        _formatted_lines.push_back(formatted_line);
    }
}

void LineFormator::formatLine(TokensInfo& tokens_info, Line& formatted_line, Context& context)
{
    for (TokensInfo::size_type k=0; k<tokens_info.size(); ++k)
    {
        context.setCurTokenPos(k);
        std::pair<FormatHandlers::iterator, FormatHandlers::iterator> handlers = 
            _format_handlers.equal_range(tokens_info[k].type);

        for (FormatHandlers::iterator i=handlers.first; i!=handlers.second; ++i)
        {
            i->second->format(tokens_info[k], context);
        }
        formatted_line += tokens_info[k].token;
    }
}

} // namespace TextFormator