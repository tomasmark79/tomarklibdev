//src/Utf8Tools.cpp
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


// std::ifstream Utf8Tools::getEmojiSequenceFileStream()
// {
//     std::string workingPath = std::filesystem::current_path();
//     std::string libraryPath = std::filesystem::canonical("/home/tomas/projects/cpp/tomarklibdev/tomarklib/src/Utf8Tools.cpp").parent_path();
//     std::string filePath = libraryPath + "/../assets/emoji-sequences.txt";
//     std::ifstream file(filePath);
//     return file;
// }

// int Utf8Tools::populateEmojiSequenceDataStructureMap(std::ifstream &file)
// {
//     if (file.is_open())
//     {
//         std::string line;
//         int startInt{0};
//         int endInt{0};
//         bool isCodePointWithSelector{false};
//         int effectiveLineCount{0};

//         while (std::getline(file, line))
//         {

//             // handle comments and empty lines
//             if (line[0] == '#' || line.empty())
//                 continue;

//             size_t firstSemiColon = line.find(";");
//             if (firstSemiColon == std::string::npos)
//                 continue;

//             ++effectiveLineCount;

//             // handle range
//             std::string token = line.substr(0, line.find(";"));
//             std::string range = token;

//             size_t rangePos = range.find("..");
//             if (rangePos != std::string::npos)
//             {
//                 // range of codepoints divided by ..
//                 std::string start = range.substr(0, rangePos);
//                 std::string end = range.substr(rangePos + 2);
//                 startInt = std::stoi(start, 0, 16);
//                 endInt = std::stoi(end, 0, 16);
//                 isCodePointWithSelector = false;
//             }
//             else
//             {
//                 // isDouble codepoint with a selector?
//                 size_t selectorPos = range.find(" ");
//                 if (selectorPos != std::string::npos)
//                 {
//                     std::string start = range.substr(0, selectorPos);
//                     std::string end = range.substr(selectorPos + 1);
//                     try
//                     {
//                         startInt = std::stoi(start, 0, 16);
//                         endInt = std::stoi(end, 0, 16);
//                         isCodePointWithSelector = true;
//                         // if stoi success then it is a double codepoint with a selector
//                         // std::cout << "double codepoint with a selector" << std::endl;
//                     }
//                     catch (const std::invalid_argument &e)
//                     {
//                         // single codepoint
//                         std::string start = range.substr(0, line.find(";"));
//                         std::string end = start;
//                         startInt = std::stoi(start, 0, 16);
//                         endInt = startInt;
//                         isCodePointWithSelector = false;
//                     }
//                 }
//             }

//             size_t secondSemiColon = line.find(';', firstSemiColon + 1);
//             if (secondSemiColon == std::string::npos)
//                 continue;

//             size_t hashPos = line.find('#', secondSemiColon + 1);
//             if (hashPos == std::string::npos)
//                 continue;

//             std::string key = line.substr(secondSemiColon + 1, hashPos - secondSemiColon - 1);

//             std::stringstream strELC = std::stringstream();
//             strELC << std::setw(10) << std::setfill('0') << std::dec << effectiveLineCount;
//             emojiSequenceDataStructure[strELC.str()] = {{startInt, endInt}, isCodePointWithSelector};
//         }

//         file.close(); // Remember to close the file when you're done
//         return emojiSequenceDataStructure.size();
//     }
//     else
//     {
//         assert(false); // Failed to open the file
//         return 0;
//     }
// }

// /// @brief Print emoji from code points
// /// @param emojiCodePoints array of code points
// /// @param length of the code points
// /// < key , < < start , end > , isCodePointWithSelector > >
// /// used structure - std::map<std::string, std::pair<std::pair<int, int>, bool>> emojiSequenceDataStructure;
// void Utf8Tools::printEmojiSequenceDataStructure()
// {
//     int emojiCount{0};
//     for (const auto &[strELC, value] : emojiSequenceDataStructure)
//     {

//         if (bool isCodePointWithSelector = value.second)
//         {
//             // isDouble codepoint with a selector
//             ++emojiCount;
//             char8_t buffer[10]{0};
//             char32_t emojiCodePoints[] = {static_cast<char32_t>(value.first.first), static_cast<char32_t>(value.first.second)};
//             char8_t *end = encodeUtf8Sequence(emojiCodePoints, 2, buffer);
//             *end = '\0'; // Null-terminating the string
//             std::cout << buffer << "\t" << std::hex << "SE: " << value.first.first << " " << value.first.second << "\t EmojiCount: " << std::dec << emojiCount << "\t ELC: " << strELC << std::endl;
//         }
//         else
//         {
//             // isInterval or single codepoint
//             for (int i = value.first.first; i <= value.first.second; ++i)
//             {
//                 ++emojiCount;
//                 char8_t buffer[10]{0};
//                 encodeUtf8(i, buffer);
//                 std::cout << buffer << "\t" << std::hex << "CP: " << std::uppercase << i << "\t EmojiCount: " << std::dec << emojiCount << "\t ELC: " << strELC << std::endl;
//             }
//         }
//     }
// }

// bool Utf8Tools::initEmojiSequenceDataStructure()
// {
//     std::ifstream file = getEmojiSequenceFileStream();
//     int count = populateEmojiSequenceDataStructureMap(file);
//     printEmojiSequenceDataStructure();
//     return count > 0;
// }

// #define br() std::cout << std::endl
// bool Utf8Tools::test()
// {
//     if (initEmojiSequenceDataStructure())

//         hlog::log(hlog::WARNING_SUCCESS, "Emoji sequence data structure initialized successfully!");
//     else
//         hlog::log(hlog::WARNING_ERROR, "Failed to initialize emoji sequence data structure!");

//     return true;
// }
