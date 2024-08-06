// include/Utf8Tools.hpp
#ifndef __UTF8TOOLS_H__
#define __UTF8TOOLS_H__

#include <fstream>

#if __cplusplus < 202002L
using char8_t = char;
#endif

class Utf8Tools
{
public:
    Utf8Tools() = default;

    /// @brief encode a UTF-8 code point
    /// @param emojiCodePoint
    /// @param buffer8
    /// @return char8_t*
    char8_t *encodeUtf8(char32_t emojiCodePoint, char8_t *buffer8);

    /// @brief encode a sequence of UTF-8 code points
    /// @param emojiCodePoints
    /// @param length
    /// @param buffer8
    /// @return char8_t*
    char8_t *encodeUtf8Sequence(const char32_t *emojiCodePoints, size_t length, char8_t *buffer8);
};

#endif // __UTF8TOOLS_H__