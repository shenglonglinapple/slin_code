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

#ifndef _SESSION_H_
#define _SESSION_H_
//
#include "../GeneralDefine.h"
//
namespace TextFormator {

/**
 * Keep some information for handlers in order to transfer message among them.
 */
class Session
{
private:
    SessionType _session;

public:
    /**
     * Put information into session.
     * @param key key of information
     * @param value value of information
     */
    void set(const SessionKey& key, const SessionValue& value)
    {
        SessionType::iterator i = _session.find(key);
        if (i == _session.end())
        {
            _session.insert(SessionType::value_type(key, value));
        }
        else
        {
            i->second = value;
        }
    }

    /**
     * Get information from session.
     * @param key key of information
     * @return value of information
     */
    const SessionValue get(const SessionKey& key)
    {
        return _session[key];
    }
};

} // namespace TextFormator

#endif // _SESSION_H_