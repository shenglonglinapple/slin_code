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

#ifndef _HTML_FORMAT_HANDLERS_H_
#define _HTML_FORMAT_HANDLERS_H_
//
#include "../core/FormatHandler.h"
#include <string>
//
namespace TextFormator {

namespace Htmlize
{

/**
 * Subclass of FormatHandler used to convert source text into html text.
 * @see FormatHandler
 */
class BodyFormatHandler : public FormatHandler
{
private:
    typedef std::map<TokenType, std::string> ColorSchema;
    ColorSchema _color_schema;

    void adjust(std::string& token)
    {
        for (std::string::size_type pos=0; pos<token.length(); ++pos)
        {
            if (token[pos] == '<')
            {
                token.replace(pos, 1, "&lt;");
                pos+=4;
            }
            else if (token[pos] == '>')
            {
                token.replace(pos, 1, "&gt;");
                pos+=4;
            }
        }
    }

public:
    void setColorSchema(TokenType type, std::string color)
    {
        _color_schema.insert(ColorSchema::value_type(type, color));
    };

    virtual void format(TokenInfo& token_info, Context& context)
    {
        std::string color = _color_schema[token_info.type];
        std::string token = token_info.token;
        adjust(token);
        token_info.token = "<font color=\"" + color + "\">" + token + "</font>";
    };
};

} // namespace Htmlize

} // namespace TextFormator

#endif // _HTML_FORMAT_HANDLERS_H_