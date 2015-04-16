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

#ifndef _COUNT_FORMAT_HANDLERS_H_
#define _COUNT_FORMAT_HANDLERS_H_
//
#include "../core/FormatHandler.h"
//
namespace TextFormator {

namespace Count
{

/**
 * Subclass of FormatHandler used to make statistics about keywords.
 * @see FormatHandler
 */
class KeywordCountHandler : public FormatHandler
{
private:
    typedef std::map<std::string, int> KeywordsCount;
    KeywordsCount _keywords_count;

public:
    void clearResult()
    {
        for (KeywordsCount::iterator i=_keywords_count.begin(); 
             i!=_keywords_count.end(); ++i)
        {
             i->second = 0;
        }
    }

    void setKeywordToCount(std::string keyword)
    {
        _keywords_count.insert(KeywordsCount::value_type(keyword, 0));
    }

    int getKeywordCount(std::string keyword)
    {
        KeywordsCount::iterator i = _keywords_count.find(keyword);
        if (i != _keywords_count.end())
        {
            return i->second;
        }
        return 0;
    }

    virtual void format(TokenInfo& token_info, Context& context)
    {
        KeywordsCount::iterator i = _keywords_count.find(token_info.token);
        if (i != _keywords_count.end())
        {
            i->second++;
        }
    };
};

/**
 * Subclass of FormatHandler used to make statistics about comments.
 * @see FormatHandler
 */
class CommentCountHandler : public FormatHandler
{
private:
    int _pure_comment;
    int _mixed_comment;

public:
    CommentCountHandler()
    {
        clearResult();
    }

    void clearResult()
    {
        _pure_comment = 0;
        _mixed_comment = 0;
    }

    int getPureComment() const
    {
        return _pure_comment;
    }

    int getMixedComment() const
    {
        return _mixed_comment;
    }

    int getTotalComment() const
    {
        return _mixed_comment + _pure_comment;
    }

    virtual void format(TokenInfo& token_info, Context& context)
    {
        TokensInfo::size_type pos = context.getCurTokenPos();
        if (0 == pos)
        {
            _pure_comment++;
        }
        else
        {
            for (int i = pos-1; i>=0; i--)
            {
                if ("WHITESPACE" != getTokenInfo(context, i).type)
                {
                    _mixed_comment++;
                    return;
                }
            }
            _pure_comment++;
        }
    }
};

} // namespace Count

} // namespace TextFormator

#endif // _COUNT_FORMAT_HANDLERS_H_