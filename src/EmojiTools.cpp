// EmojiTools.cpp
#include "../include/EmojiTools.hpp"
#include "../include/Utf8Tools.hpp"
#include "../include/hlog.hpp"

#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <regex>

#define br() std::cout << std::endl
#define pr(a) std::cout << a

/// @brief Construct a new EmojiTools object
/// @param epm std::map
/// @param file std::ifstream
void EmojiTools::constructEmojiPropertiesMap(std::map<int, EmojiPropertiesStructure> &epm, std::ifstream &file)
{
    int mapKey = 0;
    std::vector<char32_t> emojiCodePoints;
    std::string emojiGroup;
    std::string emojiSubGroup;
    std::string emojiUnicodeVersion;
    std::string emojiTailDescription;
    std::string emojiTextDescription;
    std::string line;
    std::string token;

    // TODO Robust error handling (artefacted file, etc.)
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }
        else if (line[0] == '#' && (line.find("# subgroup:") == std::string::npos) && (line.find("# group:") == std::string::npos))
        {
            continue;
        }
        else if (line.find("# subgroup:") != std::string::npos)
        {

            emojiSubGroup = line.substr(12);
            // pr("\tSubgroup: ");pr(emojiSubGroup); br();
            continue;
        }
        else if (line.find("# group:") != std::string::npos)
        {
            emojiGroup = line.substr(9);
            // pr("Group: "); pr(emojiGroup); br();
            continue;
        }
        else if (
            (line[0] != '#') &&
            (line.find("#") != std::string::npos) &&
            (line.find("# subgroup:") == std::string::npos) &&
            (line.find("# group:") == std::string::npos))
        {

            std::string unicodeString = line.substr(0, line.find(";"));
            // pr("\t\t"); pr(unicodeString);

            std::istringstream iss(unicodeString);
            emojiCodePoints.clear();
            while (iss >> token)
            {
                token.erase(std::remove_if(token.begin(), token.end(), [](char c)
                                           { return !std::isxdigit(c); }),
                            token.end());

                uint32_t value;
                std::stringstream ss;
                ss << std::hex << token;
                ss >> value;
                emojiCodePoints.push_back(static_cast<char32_t>(value));
            }

            emojiTailDescription = line.substr(line.find("#") + 1);
            // pr("\t"); pr(emojiTailDescription); br();

            // regular expression for extract unicode version
            std::regex unicodeRegex(R"((E\d+\.\d+))");
            std::smatch unicodeMatch;
            if (std::regex_search(emojiTailDescription, unicodeMatch, unicodeRegex))
            {
                emojiUnicodeVersion = unicodeMatch[0];
                // pr("\t");pr("Unicode v.: "); pr(unicodeMatch[0]);
            }

            // extract emoji text description
            std::string::size_type unicodeVersionPos = emojiTailDescription.find(unicodeMatch[0]);
            if (unicodeVersionPos != std::string::npos)
            {
                emojiTextDescription = emojiTailDescription.substr(unicodeVersionPos + unicodeMatch[0].length() + 1, emojiTailDescription.size());
                // pr("\t");pr("Desc.: ");pr(emojiTextDescription);
            }

            // combine emoji character from code points
            char8_t buffer[32];
            Utf8Tools utf8tools;
            char8_t *end = utf8tools.encodeUtf8Sequence(emojiCodePoints.data(), emojiCodePoints.size(), buffer);
            *end = '\0'; // Null-terminating the string
            // pr("\t"); pr("Emoji: "); pr(reinterpret_cast<char *>(buffer)); br();
        }

        // create copy of structure
        EmojiPropertiesStructure eps;
        eps.emojiCodePoints = emojiCodePoints;
        eps.emojiGroup = emojiGroup;
        eps.emojiSubGroup = emojiSubGroup;
        eps.emojiUnicodeVersion = emojiUnicodeVersion;
        eps.emojiTextDescription = emojiTextDescription;

        // insert eps to epm
        epm.insert(std::pair<int, EmojiPropertiesStructure>(mapKey++, eps));

        // ***
        isPopulated = true;
    }
}

/// @brief load emoji asset file from assets folder
/// @return std::ifstream if successful else library exits
std::ifstream EmojiTools::loadEmojiAssets()
{
    std::string assetFilePath = std::filesystem::current_path().string() + "/assets/emoji-test.txt";
    std::ifstream is(assetFilePath);
    if (!is)
    {
        hlog::log(hlog::WARNING_CRITICAL, "Failed to open emoji asset file: %s", assetFilePath.c_str());
        exit(1);
    }
    return is;
}

/// @brief Construct a new EmojiTools object
EmojiTools::EmojiTools()
{
    std::ifstream is = loadEmojiAssets();
    constructEmojiPropertiesMap(emojiPropertiesMap, is);
}

/// @brief receive emoji code points and return emoji character
/// @param emojiCodePoints as array of char32_t
/// @param length size_t of emojiCodePoints
/// @return std::string Emoji character
std::string EmojiTools::getEmojiCodePoint(char32_t *emojiCodePoints, size_t length)
{
    if (isPopulated)
    {
        char8_t buffer[32];
        Utf8Tools utf8tools;
        char8_t *end = utf8tools.encodeUtf8Sequence(emojiCodePoints, length, buffer);
        *end = '\0'; // Null-terminating the string
        return std::string(reinterpret_cast<char *>(buffer));
    }
    else
        return "";
}

/// @brief get all emoji groups delimitered
/// @param delimiter char32_t examples: ',' ';' '\n', etc.
/// @return std::string of emoji groups delimitered
std::string EmojiTools::getEmojiGroupsDelimitered(char32_t delimiter)
{
    if (isPopulated)
    {
        std::vector<std::string> vecGroups;
        std::string stringDelimiteredGroups;
        for (auto &epm : emojiPropertiesMap)
        {
            if (std::find(vecGroups.begin(), vecGroups.end(), epm.second.emojiGroup) == vecGroups.end())
            {
                vecGroups.push_back(epm.second.emojiGroup); // Groups map source
            }
        }
        for (auto &groupItem : vecGroups)
        {
            stringDelimiteredGroups += groupItem; 
            if (groupItem != vecGroups.back())
            {
                stringDelimiteredGroups += delimiter;
            }
        }
        return stringDelimiteredGroups;
    }
    return "";
}

/// @brief get all emoji groups list
/// @return std::vector of emoji groups
std::vector<std::string> EmojiTools::getEmojiGroupsList()
{
    if (isPopulated)
    {
        std::vector<std::string> vecGroups;

        for (auto &epm : emojiPropertiesMap)
        {
            if (std::find(vecGroups.begin(), vecGroups.end(), epm.second.emojiGroup) == vecGroups.end())
            {
                vecGroups.push_back(epm.second.emojiGroup); // Groups map source
            }
        }
        return vecGroups;
    }
    return {};
}


/// @brief get all emoji subgroups delimitered
/// @param delimiter char32_t examples: ',' ';' '\n', etc.
/// @return std::string of emoji subgroups delimitered
std::string EmojiTools::getEmojiSubGroupsDelimitered(char32_t delimiter)
{
    if (isPopulated)
    {
        std::vector<std::string> vecSubGroups;
        std::string stringDelimiteredSubGroups;
        for (auto &epm : emojiPropertiesMap)
        {
            if (std::find(vecSubGroups.begin(), vecSubGroups.end(), epm.second.emojiSubGroup) == vecSubGroups.end())
            {
                vecSubGroups.push_back(epm.second.emojiSubGroup); // SubGroups map source
            }
        }
        for (auto &subGroupItem : vecSubGroups)
        {
            stringDelimiteredSubGroups += subGroupItem;
            if (subGroupItem != vecSubGroups.back())
            {
                stringDelimiteredSubGroups += delimiter;
            }
        }
        return stringDelimiteredSubGroups;
    }
    return "";
}

/// @brief get all emoji subgroups list
/// @return std::vector of emoji subgroups
std::vector<std::string> EmojiTools::getEmojiSubGroupsList()
{
    if (isPopulated)
    {
        std::vector<std::string> vecSubGroups;

        for (auto &epm : emojiPropertiesMap)
        {
            if (std::find(vecSubGroups.begin(), vecSubGroups.end(), epm.second.emojiSubGroup) == vecSubGroups.end())
            {
                vecSubGroups.push_back(epm.second.emojiSubGroup); // SubGroups map source
            }
        }
        return vecSubGroups;
    }
    return {};
}















/// @brief
/// @param emojiCodePoints
/// @param length
void EmojiTools::printEmojiCodePoint(char32_t *emojiCodePoints, size_t length)
{
    char8_t buffer[32];
    Utf8Tools utf8tools;
    char8_t *end = utf8tools.encodeUtf8Sequence(emojiCodePoints, length, buffer);
    *end = '\0'; // Null-terminating the string
    std::cout << reinterpret_cast<char *>(buffer);
}

void EmojiTools::printEmojiGroupWDescription(std::string emojiGroup)
{
    if (isPopulated)
    {
        for (auto &epm : emojiPropertiesMap)
        {
            if (epm.second.emojiGroup == emojiGroup)
            {
                pr("Emoji: ");
                printEmojiCodePoint(epm.second.emojiCodePoints.data(), epm.second.emojiCodePoints.size());
                pr(" Group: ");
                pr(epm.second.emojiGroup);
                pr(" Subgroup: ");
                pr(epm.second.emojiSubGroup);
                pr(" Description: ");
                pr(epm.second.emojiTextDescription);
                pr(" Unicode version: ");
                pr(epm.second.emojiUnicodeVersion);
                br();
            }
        }
    }
}

void EmojiTools::printEmojiGroup(std::string emojiGroup)
{
    if (isPopulated)
    {
        for (auto &epm : emojiPropertiesMap)
        {
            if (epm.second.emojiGroup == emojiGroup)
            {
                printEmojiCodePoint(epm.second.emojiCodePoints.data(), epm.second.emojiCodePoints.size());
            }
        }
    }
}

void EmojiTools::printEmojiSubGroupWDescription(std::string emojiSubGroup)
{
    if (isPopulated)
    {
        for (auto &epm : emojiPropertiesMap)
        {
            if (epm.second.emojiSubGroup == emojiSubGroup)
            {
                pr("Emoji: ");
                printEmojiCodePoint(epm.second.emojiCodePoints.data(), epm.second.emojiCodePoints.size());
                pr(" Group: ");
                pr(epm.second.emojiGroup);
                pr(" Subgroup: ");
                pr(epm.second.emojiSubGroup);
                pr(" Description: ");
                pr(epm.second.emojiTextDescription);
                pr(" Unicode version: ");
                pr(epm.second.emojiUnicodeVersion);
                br();
            }
        }
    }
}

void EmojiTools::printEmojiSubGroup(std::string emojiSubGroup)
{
    if (isPopulated)
    {
        for (auto &epm : emojiPropertiesMap)
        {
            if (epm.second.emojiSubGroup == emojiSubGroup)
            {
                printEmojiCodePoint(epm.second.emojiCodePoints.data(), epm.second.emojiCodePoints.size());
            }
        }
    }
}

void EmojiTools::printGroupsText()
{
    if (isPopulated)
    {
        std::vector<std::string> groups;
        for (auto &epm : emojiPropertiesMap)
        {
            if (std::find(groups.begin(), groups.end(), epm.second.emojiGroup) == groups.end())
            {
                groups.push_back(epm.second.emojiGroup);
            }
        }

        for (auto &group : groups)
        {
            pr("Group: ");
            pr(group);
            br();
        }
    }
}

std::string EmojiTools::getSubGroupsText(std::string delimiter)
{
    if (isPopulated)
    {
        std::vector<std::string> subgroups;
        std::string strSubGroups;
        for (auto &epm : emojiPropertiesMap)
        {
            if (std::find(subgroups.begin(), subgroups.end(), epm.second.emojiSubGroup) == subgroups.end())
            {
                subgroups.push_back(epm.second.emojiSubGroup);
            }
        }

        for (auto &group : subgroups)
        {
            strSubGroups += group;
            if (group != subgroups.back())
            {
                strSubGroups += delimiter;
            }
        }
        return strSubGroups;
    }
    return "";
}

void EmojiTools::printSubGroupsText()
{
    if (isPopulated)
    {
        std::vector<std::string> subgroups;
        for (auto &epm : emojiPropertiesMap)
        {
            if (std::find(subgroups.begin(), subgroups.end(), epm.second.emojiSubGroup) == subgroups.end())
            {
                subgroups.push_back(epm.second.emojiSubGroup);
            }
        }

        for (auto &subgroup : subgroups)
        {
            pr("Subgroup: ");
            pr(subgroup);
            br();
        }
    }
}

void EmojiTools::visualTest()
{
    hlog::log(hlog::WARNING_SUCCESS, "Visual Testing EmojiTools");

    char32_t emojiCodePoint[1] = {0x1F600}; // 😀
    printEmojiCodePoint(emojiCodePoint, 1);
    pr(getEmojiCodePoint(emojiCodePoint, 1));
    br();
    char32_t emojiCodePointWSelector[2] = {0x2764, 0x200D}; // ❤‍
    printEmojiCodePoint(emojiCodePointWSelector, 2);
    pr(getEmojiCodePoint(emojiCodePointWSelector, 2));
    br();
    char32_t emojiCodePointWSelector3[3] = {0x2764, 0x200D, 0x1F525}; // ❤‍🔥
    printEmojiCodePoint(emojiCodePointWSelector3, 3);
    pr(getEmojiCodePoint(emojiCodePointWSelector3, 3));
    br();
    char32_t emojiCodePointWSelector4[4] = {0x2764, 0xFE0F, 0x200D, 0x1F525}; // ❤️‍🔥
    printEmojiCodePoint(emojiCodePointWSelector4, 4);
    pr(getEmojiCodePoint(emojiCodePointWSelector4, 4));
    br();
    char32_t emojiCodePointWSelector7[7] = {0x1F9D1, 0x1F3FF, 0x200D, 0x1F9AF, 0x200D, 0x27A1, 0xFE0F}; // 🧑🏿‍🦯‍➡️
    printEmojiCodePoint(emojiCodePointWSelector7, 7);
    pr(getEmojiCodePoint(emojiCodePointWSelector7, 7));
    br();
    hlog::log(hlog::WARNING_SUCCESS, "If you are seeing Emoji characters above, the test is successful!");
    hlog::log(hlog::WARNING_ERROR, "If you aren't seeing Emoji characters above, the test is unsuccessful!");
    br();
    hlog::log(hlog::WARNING_SUCCESS, "printEmojiGroup(\"Smileys & Emotion\");");
    printEmojiGroup("Smileys & Emotion");
    br();
    br();
    hlog::log(hlog::WARNING_SUCCESS, "printEmojiSubGroup(\"face-sleepy\");");
    printEmojiSubGroup("face-sleepy");
    br();
    br();
    hlog::log(hlog::WARNING_SUCCESS, "printGroupsText();");
    printGroupsText();
    br();
    hlog::log(hlog::WARNING_SUCCESS, "printSubGroupsText();");
    printSubGroupsText();
    br();
    hlog::log(hlog::WARNING_SUCCESS, "printEmojiSubGroup(\"zodiac\");");
    printEmojiSubGroup("zodiac");
    br();
    br();
    hlog::log(hlog::WARNING_SUCCESS, "printEmojiSubGroup(\"math\");");
    printEmojiSubGroup("math");
    br();
    br();
    hlog::log(hlog::WARNING_SUCCESS, "getGroupsText(\",\")");
    //pr(getGroupsText(","));
    br();
    br();
    hlog::log(hlog::WARNING_SUCCESS, "getGroupsText(\"|\")");
    //pr(getGroupsText("|"));
    br();
    br();
    hlog::log(hlog::WARNING_SUCCESS, "getSubGroupsText(\";\")");
    pr(getSubGroupsText(";"));
    br();
    br();
    hlog::log(hlog::WARNING_SUCCESS, "getSubGroupsText(\"*\")");
    pr(getSubGroupsText("*"));
    br();
    br();
}
