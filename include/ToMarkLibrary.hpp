//ToMarkLib.hpp
#ifndef __TOMARKLIB_H__
#define __TOMARKLIB_H__

#include "Utf8Tools.hpp"
#include "EmojiTools.hpp"
#include "hlog.hpp"

#include <string>

namespace tomarklib
{
    const std::string_view getVersion() { return "0.0.1"; };
    EmojiTools emojitools;
}

#endif // __TOMARKLIB_H__