#ifndef _BASE64HELPER_H_
#define _BASE64HELPER_H_
//
#include <string>
//
namespace MUtils {

class Base64Helper
{
public:

    // convert from Base64 to ANSI
    static std::string encode(const std::string in_str);

    // convert from ANSI to Base64
    static std::string decode(const std::string in_str);

private:

    // encode table
    const static std::string _base64_encode_chars;
 
    // decode table
    const static char _base64_decode_chars[128];
};

} // namespace MUtils

#endif  // _BASE64HELPER_H_