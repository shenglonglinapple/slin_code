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

#ifndef _GENERAL_DEFINE_H_
#define _GENERAL_DEFINE_H_
//
#include <map>
#include <string>
#include <vector>
#include <list>
//
namespace TextFormator {

typedef std::string Line;
typedef std::list<Line> Lines;

typedef std::string SessionKey;
typedef std::string SessionValue;
typedef std::map<SessionKey, SessionValue> SessionType;

typedef std::string TokenType;
typedef std::vector<TokenType> TokenTypes;

struct TokenInfo {
    TokenType type;
    std::string token;
};

typedef std::vector<TokenInfo> TokensInfo;
typedef std::vector<TokensInfo > TokensInfoList;

} // namespace TextFormator

#endif // _GENERAL_DEFINE_H_