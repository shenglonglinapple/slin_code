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

#ifndef _CONCRETE_PARSE_HANDLERS_H_
#define _CONCRETE_PARSE_HANDLERS_H_
//
#include "../GeneralDefine.h"
#include "../core/ParseHandler.h"
#include <iostream>
//
namespace TextFormator {

/**
 * Subclass of ParseHandler used to parse string from source text.
 * @see ParseHandler
 */
class StringParseHandler : public ParseHandler
{
public:
    StringParseHandler() : ParseHandler(MAX_PRIORITY)
    {}

    virtual bool accept(const Line& line, Line::size_type& pos, 
        Context& context, TokenInfo& token_info)
    {
        if (0 == context.session().get("comment").compare("T"))
            return false;

        if (line[pos]!='\"' && line[pos]!='\'')
            return false;

        Line::size_type pos0;
        for (pos0=pos+1; pos0<line.length(); ++pos0)
        {
            if (line[pos]=='\"' && line[pos0]=='\"' && line[pos0-1]!='\\')
                break;
            if (line[pos]=='\"' && line[pos0]=='\"' && 
                line[pos0-1]=='\\' && line[pos0-2]=='\\')
                break;
            if (line[pos]=='\'' && line[pos0]=='\'' && line[pos0-1]!='\\')
                break;
            if (line[pos]=='\'' && line[pos0]=='\'' && 
                line[pos0-1]=='\\' && line[pos0-2]=='\\')
                break;
        }

        token_info.token.assign(line, pos, pos0+1-pos);
        token_info.type = "STRING";
        pos = pos0+1;
        return true;
    }
};

/**
 * Subclass of ParseHandler used to parse number from source text.
 * @see ParseHandler
 */
class NumberParseHandler : public ParseHandler
{
public:
    virtual bool accept(const Line& line, Line::size_type& pos, 
        Context& context, TokenInfo& token_info)
    {
        if (!isdigit(line[pos]))
            return false;

        Line::size_type pos0;
        for (pos0=pos+1; pos0<line.length(); ++pos0)
        {
            if (!isdigit(line[pos0]))
                break;
        }

        token_info.token.assign(line, pos, pos0-pos);
        token_info.type = "NUMBER";
        pos = pos0;
        return true;
    }
};

/**
 * Subclass of ParseHandler used to parse operator from source text.
 * @see ParseHandler
 */
class OperatorParseHandler : public ParseHandler
{
private:
    const std::string _operators;

public:
    OperatorParseHandler() : _operators("+-*/%~!|<>=()[]{}#,.?:;&\\")
    {}

    virtual bool accept(const Line& line, Line::size_type& pos, 
        Context& context, TokenInfo& token_info)
    {
        if (Line::npos == _operators.find(line[pos]))
            return false;

        Line::size_type pos0;
        for (pos0=pos+1; pos0<line.length(); ++pos0)
        {
            if (Line::npos == _operators.find(line[pos0]))
                break;
            if (line[pos0]=='/' && line[pos0+1]=='/')
                break;
        }

        token_info.token.assign(line, pos, pos0-pos);
        token_info.type = "OPERATOR";
        pos = pos0;
        return true;
    }
};

/**
 * Subclass of ParseHandler used to parse identifier from source text.
 * @see ParseHandler
 */
class IdentifierParseHandler : public ParseHandler
{
private:
    typedef std::list<std::string> Keywords;
    Keywords* _keywords;

    bool isKeyword(const std::string token)
    {
        if (NULL == _keywords)
            return false;

        for (Keywords::iterator i=_keywords->begin(); 
             i!=_keywords->end(); ++i)
        {
            if (0 == (*i).compare(token))
            {
                return true;
            }
        }
        return false;
    };

public:
    IdentifierParseHandler(Keywords* keywords = NULL)
        : _keywords(keywords)
    {
    }

    void setKeywords(Keywords* keywords)
    {
        _keywords = keywords;
    }

    virtual bool accept(const Line& line, Line::size_type& pos, 
        Context& context, TokenInfo& token_info)
    {
        if (!isalpha(line[pos]) && line[pos]!='_')
            return false;

        Line::size_type pos0;
        for (pos0=pos+1; pos0<line.length(); ++pos0)
        {
            if (!isalpha(line[pos0]) && line[pos0]!='_' && !isdigit(line[pos0]))
                break;
        }

        token_info.token.assign(line, pos, pos0-pos);
        token_info.type = isKeyword(token_info.token) ? "KEYWORD" : "IDENTIFIER";
        pos = pos0;
        return true;
    }
};

/**
 * Subclass of ParseHandler used to parse whitespace from source text.
 * @see ParseHandler
 */
class WhitespaceParseHandler : public ParseHandler
{
private:
    const std::string _whitespace;

public:
    WhitespaceParseHandler() : _whitespace(" \t")
    {}

    virtual bool accept(const Line& line, Line::size_type& pos, 
        Context& context, TokenInfo& token_info)
    {
        if (Line::npos == _whitespace.find(line[pos]))
            return false;

        Line::size_type pos0;
        for (pos0=pos+1; pos0<line.length(); ++pos0)
        {
            if (Line::npos == _whitespace.find(line[pos0]))
                break;
        }

        token_info.token.assign(line, pos, pos0-pos);
        token_info.type = "WHITESPACE";
        pos = pos0;
        return true;
    }
};

/**
 * Subclass of ParseHandler used to parse comment from source text.
 * @see ParseHandler
 */
class CommentParseHandler : public ParseHandler
{
public:
    CommentParseHandler() : ParseHandler(MAX_PRIORITY)
    {}

    virtual bool accept(const Line& line, Line::size_type& pos, 
        Context& context, TokenInfo& token_info)
    {
        bool is_comment = (0 == context.session().get("comment").compare("T"));

        if (line.empty() && is_comment)
        {
            token_info.token = "";
            token_info.type = "COMMENT";
            pos = 0;
            return true;
        }

        if (line[pos]=='/' && line[pos+1]=='/')
        {
            token_info.token.assign(line, pos, line.length()-pos);
            token_info.type = "COMMENT";
            pos = line.length();
            return true;
        }

        if ((line[pos]!='/' || line[pos+1]!='*') && !is_comment)
            return false;

        Line::size_type pos0;
        std::string nest = context.session().get("nest");
        for (pos0=pos; pos0<line.length(); ++pos0)
        {
            if (line[pos0]=='/' && line[pos0+1]=='*')
            {
                nest += "#";
                ++pos0;
            }
            else if (line[pos0]=='*' && line[pos0+1]=='/')
            {
                nest.assign(nest, 0, nest.length()-1);
                ++pos0;
            }
            if (nest.empty())
            {
                ++pos0;
                break;
            }
        }

        token_info.token.assign(line, pos, pos0-pos);
        token_info.type = "COMMENT";
        pos = pos0;
        context.session().set("nest", nest);
        if (nest.empty())
            context.session().set("comment", "F");
        else
            context.session().set("comment", "T");
        return true;
    }
};

} // namespace TextFormator

#endif // _CONCRETE_PARSE_HANDLERS_H_