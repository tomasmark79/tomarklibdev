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
    // Smileys & Emotion;People & Body;Component;Animals & Nature;Food & Drink;Travel & Places;Activities;Objects;Symbols;Flags

    std::cout << tomarklib::emojitools.getEmojiGroupsDelimitered('\n') << std::endl; // new line delimiter
    std::vector<std::string> vecEmojiGroups = tomarklib::emojitools.getEmojiGroupsList(); // get the list of emoji groups

    std::cout << tomarklib::emojitools.getEmojiSubGroupsDelimitered(';') << std::endl;
    // face-smiling;face-affection;face-tongue;face-hand;face-neutral-skeptical;face-sleepy;face-unwell;face-hat;face-glasses;
    // ace-concerned;face-negative;face-costume;cat-face;monkey-face;heart;emotion;hand-fingers-open;hand-fingers-partial;
    // hand-single-finger;hand-fingers-closed;hands;hand-prop;body-parts;person;person-gesture;person-role;person-fantasy;
    // person-activity;person-sport;person-resting;family;person-symbol;skin-tone;hair-style;animal-mammal;animal-bird;
    // animal-amphibian;animal-reptile;animal-marine;animal-bug;plant-flower;plant-other;food-fruit;food-vegetable;food-prepared;
    // ood-asian;food-marine;food-sweet;drink;dishware;place-map;place-geographic;place-building;place-religious;place-other;
    // transport-ground;transport-water;transport-air;hotel;time;sky & weather;event;award-medal;sport;game;arts & crafts;
    // clothing;sound;music;musical-instrument;phone;computer;light & video;book-paper;money;mail;writing;office;lock;tool;
    // science;medical;household;other-object;transport-sign;warning;arrow;religion;zodiac;av-symbol;gender;math;punctuation;
    // currency;other-symbol;keycap;alphanum;geometric;flag;country-flag;subdivision-flagmm

    std::cout << tomarklib::emojitools.getEmojiSubGroupsDelimitered('\n') << std::endl; // new line delimiter
    std::vector<std::string> vecEmojiSubGroups = tomarklib::emojitools.getEmojiSubGroupsList(); // get the list of emoji sub groups

    std::cout << tomarklib::emojitools.getEmojiGroup("Smileys & Emotion") << std::endl;
    // 😀😃😄😁😆😅🤣😂🙂🙃🫠😉😊😇🥰😍🤩😘😗 ...

    std::cout << tomarklib::emojitools.getEmojiSubGroup("warning") << std::endl;
    // ⚠️⚠🚸⛔🚫🚳🚭🚯🚱🚷📵🔞☢️☢☣️☣

    std::cout << tomarklib::emojitools.getEmojiSubGroup("game") << std::endl;
    // 🎯🪀🪁🔫🎱🔮🪄🎮🕹️🕹🎰🎲🧩🧸🪅🪩🪆♠️♠♥️♥♦️♦♣️♣♟️♟🃏🀄🎴

    std::cout << tomarklib::emojitools.getEmojiSubGroup("drink") << std::endl;
    // 🍼🥛☕🫖🍵🍶🍾🍷🍸🍹🍺🍻🥂🥃🫗🥤🧋🧃🧉🧊

    

    return 0;
}
