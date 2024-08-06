// include/EmojiTools.hpp
#ifndef __EMOJITOOLS_H__
#define __EMOJITOOLS_H__

#include <string>
#include <fstream>
#include <vector>
#include <map>

#if __cplusplus < 202002L
using char8_t = char; // C++17 and older
#endif

#ifndef size_t
using size_t = decltype(sizeof(0));
#endif

class EmojiTools
{
public:
    /// @brief Construct a new EmojiTools object
    EmojiTools();

private:
    bool isPopulated{false};
    struct EmojiPropertiesStructure
    {
        std::vector<char32_t> emojiCodePoints;
        std::string emojiGroup;
        std::string emojiSubGroup;
        std::string emojiUnicodeVersion;
        std::string emojiTextDescription;
    };
    std::map<int, EmojiPropertiesStructure> emojiPropertiesMap;

    void constructEmojiPropertiesMap(std::map<int, EmojiPropertiesStructure> &epm, std::ifstream &file);
    std::ifstream loadEmojiAssets();

public:
    
    std::string getEmojiCodePoint(char32_t *emojiCodePoints, size_t length);

    std::string getEmojiGroupsDelimitered(char32_t delimiter);
    std::vector<std::string> getEmojiGroupsList();

    std::string getEmojiSubGroupsDelimitered(char32_t delimiter);
    std::vector<std::string> getEmojiSubGroupsList();



    std::string getSubGroupsText(std::string delimiter);
    void printEmojiCodePoint(char32_t *emojiCodePoints, size_t length);
    void printEmojiGroupWDescription(std::string emojiGroup);
    void printEmojiGroup(std::string emojiGroup);
    void printEmojiSubGroupWDescription(std::string emojiSubGroup);
    void printEmojiSubGroup(std::string emojiSubGroup);
    void printGroupsText();
    void printSubGroupsText();
    void printEmojiDescription(std::string emojiDescription);
    void visualTest();
};

#endif // __EMOJITOOLS_H__