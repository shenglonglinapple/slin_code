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

#ifndef _FORMAT_HANDLER_H_
#define _FORMAT_HANDLER_H_
//
#include "../helper/Context.h"
//
namespace TextFormator {

/**
 * Abstract class of format handler.
 *
 * All format handlers should be a subclass of FormatHandler.
 * In subclasses, you can override format method to redefine action
 * for specific token
 */
class FormatHandler
{
protected:
    FormatHandler()
    {};

    const TokenInfo& getTokenInfo(Context& context, TokensInfo::size_type pos = -1)
    {
        const TokensInfo& tokens_info = *(context.getTokensInfo());
        if (pos == -1)
        {
            pos = context.getCurTokenPos();
        }
        return tokens_info[pos];
    }

public:
    /**
     * Format current token.
     * @param token_info token information
     * @param context used to keep information among handlers
     */
    virtual void format(TokenInfo& token_info, Context& context)
    {};
};

} // namespace TextFormator

#endif // _FORMAT_HANDLER_H_