// src/Utf8Tools.cpp
#include "../include/Utf8Tools.hpp"
#include "../include/hlog.hpp"

#include <assert.h>
#include <map>
#include <filesystem>
#include <iostream>

char8_t *Utf8Tools::encodeUtf8(char32_t emojiCodePoint, char8_t *buffer8)
{
    constexpr auto byte = [](char32_t x)
    {
        assert(x <= 0x100); // 256
        return static_cast<char8_t>(x);
    };

    char32_t continuation = 0b1000'0000; // 128
    if (emojiCodePoint >= 65536)
    {
        *buffer8++ = byte(0b1111'0000 | (emojiCodePoint >> 18));
        *buffer8++ = byte(continuation | ((emojiCodePoint >> 12) & 0b0011'1111));
        *buffer8++ = byte(continuation | ((emojiCodePoint >> 6) & 0b0011'1111));
        *buffer8++ = byte(continuation | (emojiCodePoint & 0b0011'1111));
    }
    else if (emojiCodePoint >= 2048)
    {
        *buffer8++ = byte(0b1110'0000 | (emojiCodePoint >> 12));
        *buffer8++ = byte(continuation | ((emojiCodePoint >> 6) & 0b0011'1111));
        *buffer8++ = byte(continuation | (emojiCodePoint & 0b0011'1111));
    }
    else if (emojiCodePoint >= 128)
    {
        *buffer8++ = byte(0b1100'0000 | (emojiCodePoint >> 6));
        *buffer8++ = byte(continuation | (emojiCodePoint & 0b0011'1111));
    }
    else
    {
        *buffer8++ = byte(emojiCodePoint);
    }

    return buffer8;
}

char8_t *Utf8Tools::encodeUtf8Sequence(const char32_t *emojiCodePoints, size_t length, char8_t *buffer8)
{
    for (size_t i = 0; i < length; ++i)
    {
        buffer8 = encodeUtf8(emojiCodePoints[i], buffer8);
    }
    return buffer8;
}