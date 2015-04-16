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

#ifndef _LINE_FORMATOR_H_
#define _LINE_FORMATOR_H_
//
#include "../GeneralDefine.h"
#include "FormatHandler.h"
#include "../helper/Context.h"
#include <map>
//
namespace TextFormator {

/**
 * This class is used to format text line by line.
 * @see FormatHandler
 */
class LineFormator
{
private:
    typedef std::multimap<TokenType, FormatHandler*> FormatHandlers;

    FormatHandlers _format_handlers;
    Lines _formatted_lines;

    void formatLine(TokensInfo& tokens_info, Line& formatted_line, Context& context);

public:
    /**
     * Constructor for LineFormator.
     */
    LineFormator();

    /**
     * Destructor for LineFormator.
     */
    ~LineFormator();

    /**
     * format parsed result line by line.
     * @param token_info_list list including token information
     */
    void format(TokensInfoList& token_info_list);

    /**
     * regist format handler.
     * @param type indicate token type
     * @param handler concrete handler which determines 
     *                how to format text of specific token type
     */
    void registFormatHandler(TokenType type, FormatHandler* handler);

    /**
     * regist the same format handler for a set of types
     * @param types indicate token types
     * @param handler concrete handler which determines 
     *                how to format text of specific token type
     */
    void registFormatHandler(TokenTypes types, FormatHandler* handler);

    /**
     * unregist format handler.
     * @param handler concrete handler which determines 
     *                how to format text of specific token type
     */
    void unreigistFormatHandler(FormatHandler* handler);

    /**
     * get formatted result.
     * @return an array stand for the formatted text
     */
    Lines& getFormattedLines();
};

} // namespace TextFormator

#endif // _LINE_FORMATOR_H_