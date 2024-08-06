//Caller.cpp
#include <iostream>
#include "include/ToMarkLibrary.hpp"

#define br() std::cout << std::endl

int main(int, char **)
{
    std::cout << "ToMarkLib version: " << tomarklib::getVersion() << std::endl;

    // this is a test
    // tomarklib::emojitools.visualTest();

    // some useful functions
    std::cout << tomarklib::emojitools.getEmojiGroupsDelimitered(';') << std::endl;
    std::cout << tomarklib::emojitools.getEmojiGroupsDelimitered('\n') << std::endl;
    std::vector<std::string> vecEmojiGroups = tomarklib::emojitools.getEmojiGroupsList();

    std::cout << tomarklib::emojitools.getEmojiSubGroupsDelimitered(';') << std::endl;
    std::cout << tomarklib::emojitools.getEmojiSubGroupsDelimitered('\n') << std::endl;
    std::vector<std::string> vecEmojiSubGroups = tomarklib::emojitools.getEmojiSubGroupsList();

    std::cout << tomarklib::emojitools.getEmojiGroup("Smileys & Emotion") << std::endl;
    std::cout << tomarklib::emojitools.getEmojiGroup("Component") << std::endl;
    std::cout << tomarklib::emojitools.getEmojiSubGroup("warning") << std::endl;
    std::cout << tomarklib::emojitools.getEmojiSubGroup("game") << std::endl;
    

    return 0;
}
