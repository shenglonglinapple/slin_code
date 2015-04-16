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

#ifndef _CONTEXT_H_
#define _CONTEXT_H_
//
#include "../GeneralDefine.h"
#include "Session.h"
//
namespace TextFormator {

/**
 * Indicate context while parsing or formatting text, and also 
 * keep some information for handlers in order to transfer message among them.
 * @see Session
 */
class Context
{
private:
    Session _session;
    const TokensInfo* _tokens_info;
    TokensInfo::size_type _cur_token_pos;
    TokensInfoList::size_type _cur_line_pos;

public:
    /**
     * Get session object.
     * @return reference of session object
     */
    Session& session()
    {
        return _session;
    };

    /**
     * Set token list of a text line.
     * @param tokens_info token list of a text line
     */
    void setTokensInfo(const TokensInfo* tokens_info)
    {
        _tokens_info = tokens_info;
    };

    /**
     * Get token list of a text line.
     * @return token list of a text line
     */
    const TokensInfo* getTokensInfo()
    {
        return _tokens_info;
    };

    /**
     * Set current position in the token list.
     * @param pos position point to current token
     */
    void setCurTokenPos(TokensInfo::size_type pos)
    {
        _cur_token_pos = pos;
    };

    /**
     * Get current position in the token list.
     * @return position point to current token
     */
    TokensInfo::size_type getCurTokenPos()
    {
        return _cur_token_pos;
    };

    /**
     * Set current line position.
     * @param pos current line position
     */
    void setCurLinePos(TokensInfoList::size_type pos)
    {
        _cur_line_pos = pos;
    }

    /**
     * Get current line position.
     * @return current line position
     */
    TokensInfoList::size_type getCurLinePos()
    {
        return _cur_line_pos;
    }
};

} // namespace TextFormator

#endif // _CONTEXT_H_