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

#ifndef _PARSE_HANDLER_H_
#define _PARSE_HANDLER_H_
//
#include "../GeneralDefine.h"
#include "../helper/Context.h"
//
namespace TextFormator {

/**
 * Abstract class of parse handler
 *
 * All parse handlers should be a subclass of ParseHandler.
 * In subclasses, you can override accept method to redefine action
 * for specific token
 */
class ParseHandler
{
private:
    int _priority;

protected:
    enum {
        MAX_PRIORITY = 0, 
        NORM_PRIORITY = 5, 
        MIN_PRIORITY = 10
    };

    ParseHandler(int priority = NORM_PRIORITY)
         : _priority(priority)
    {};

public:
    /**
     * Parse current line from current position.
     * This method will adjust current position after parsing
     * @param line a line of text
     * @param pos current character position
     * @param context used to keep information among handlers
     * @param token_info used to keep parsed result, if possible
     * @return return true if parse successfully, else return false
     */
    virtual bool accept(const Line& line, Line::size_type& pos, 
        Context& context, TokenInfo& token_info)
    {
        return true;
    };

    /**
     * Get priority of handler
     * @return priority of handler
     */
    int getPriority() const
    {
        return _priority;
    };
};

} // namespace TextFormator

#endif // _PARSE_HANDLER_H_