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

#ifndef _DEFAULT_PARSE_HANDLERS_H_
#define _DEFAULT_PARSE_HANDLERS_H_
//
#include "../GeneralDefine.h"
#include "ParseHandler.h"
//
namespace TextFormator {

/**
 * Default parse handler. No need to use explicitly.
 * The framework will call this handler.
 * @see ParseHandler
 */
class DefaultParseHandler : public ParseHandler
{
public:
    DefaultParseHandler() : ParseHandler(MIN_PRIORITY)
    {}

    virtual bool accept(const Line& line, Line::size_type& pos, 
        Context& context, TokenInfo& token_info)
    {
        token_info.token.assign(line, pos, line.length()-pos);
        token_info.type = "DEFAULT";
        pos = line.length();
        return true;
    }
};

} // namespace TextFormator

#endif // _DEFAULT_PARSE_HANDLERS_H_