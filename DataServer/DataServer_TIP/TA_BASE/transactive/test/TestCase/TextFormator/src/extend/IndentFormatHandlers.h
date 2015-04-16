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

#ifndef _INDENT_FORMAT_HANDLERS_H_
#define _INDENT_FORMAT_HANDLERS_H_
//
#include "../core/FormatHandler.h"
#include <string>
//
namespace TextFormator {

namespace Indent
{

static int space_num = 4;

/**
 * Subclass of FormatHandler used to format source text indently.
 * @see FormatHandler
 */
class NormalFormatHandler : public FormatHandler
{
public:
    virtual void format(TokenInfo& token_info, Context& context)
    {
        std::string token = token_info.token;
        if (context.getCurTokenPos() != 0)
        {
            return;
        }
        std::string nest = context.session().get("nest");
        std::string spaces(space_num*nest.size(), ' ');
        token_info.token = spaces + token;
    };
};

/**
 * Subclass of FormatHandler used to format source text indently.
 * @see FormatHandler
 */
class WhitespaceFormatHandler : public FormatHandler
{
public:
    virtual void format(TokenInfo& token_info, Context& context)
    {
        std::string token = token_info.token;
        if (context.getCurTokenPos() != 0)
        {
            return;
        }
        std::string nest = context.session().get("nest");
        std::string spaces;
		TokensInfo::size_type cur_token_pos = context.getCurTokenPos();
		if (cur_token_pos == context.getTokensInfo()->size()-1)
		{
			spaces = "";
		}
		else
		{
			const TokenInfo& next_token_info = 
                getTokenInfo(context, cur_token_pos+1);
			if (next_token_info.type == "OPERATOR" && 
                next_token_info.token[0] == '}')
			{
				spaces.assign(space_num*(nest.size()-1), ' ');
			}
			else
			{
				spaces.assign(space_num*nest.size(), ' ');
			}
		}
        token_info.token = spaces;
    };
};

/**
 * Subclass of FormatHandler used to format source text indently.
 * @see FormatHandler
 */
class OperatorFormatHandler : public FormatHandler
{
public:
    virtual void format(TokenInfo& token_info, Context& context)
    {
        std::string old_token = token_info.token;
        std::string new_token;
        std::string nest = context.session().get("nest");
        std::string spaces;
        TokensInfo::size_type cur_pos = context.getCurTokenPos();
        bool is_first = true;
        for (std::string::size_type i = 0; i < old_token.length(); ++i)
        {
            if (old_token[i] == '{')
            {
                if (is_first)
                {
                    if (cur_pos==0)
                    {
                        spaces.assign(space_num*nest.size(), ' ');
                        new_token += spaces;
                        new_token += old_token[i];
                    }
                    else if (i==old_token.length()-1 && 
                            (getTokenInfo(context, cur_pos-1).type!="WHITESPACE" || 
                             context.getTokensInfo()->size()>2))
                    {
                        spaces.assign(space_num*nest.size(), ' ');
                        new_token += "\n";
                        new_token += spaces;
                        new_token += old_token[i];
                    }
                    else
                    {
                        new_token += old_token[i];
                    }
                    is_first = false;
                }
                else
                {
                    spaces.assign(space_num*nest.size(), ' ');
                    new_token += "\n";
                    new_token += spaces;
                    new_token += old_token[i];
                }
                nest += "#";
            }
            else if (old_token[i] == '}')
            {
                nest.assign(nest, 0, nest.length()-1);
                if (is_first)
                {
                    if (cur_pos==0)
                    {
                        spaces.assign(space_num*nest.size(), ' ');
                        new_token += spaces;
                        new_token += old_token[i];
                    }
                    else
                    {
                        new_token += old_token[i];
                    }
                    is_first = false;
                }
                else
                {
                    spaces.assign(space_num*nest.size(), ' ');
                    new_token += "\n";
                    new_token += spaces;
                    new_token += old_token[i];
                }
            }
            else if (old_token[i] == '(')
            {
                new_token += old_token[i];
                nest += "#";
            }
            else if (old_token[i] == ')')
            {
                nest.assign(nest, 0, nest.length()-1);
                new_token += old_token[i];
            }
            else
            {
                new_token += old_token[i];
            }
        }
        token_info.token = new_token;
        context.session().set("nest", nest);
    }
};
} // namespace Indent

} // namespace TextFormator

#endif // _INDENT_FORMAT_HANDLERS_H_