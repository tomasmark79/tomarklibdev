# ToMarkLibrary

Useful C++ library with some of features 

# Library Features

## Unicode emoji tools

**This library feature is very useful to work with Emojis**.

- You may to get **Emoji** by **codepoints**, by group name, by sub group name.
- You may to get Emoji group or sub group list in vector.
- It's very easy to work with the library.
The source definiction for Emojis is using official document by Unicode organisation which define used Unicode version defined within resource file located in assets folder.

```cpp
    // some useful functions

    std::cout << tomarklib::emojitools.getEmojiGroupsDelimitered(';') << std::endl;
    // Smileys & Emotion;People & Body;Component;Animals & Nature;Food & Drink;Travel & Places;Activities;Objects;Symbols;Flags

    std::cout << tomarklib::emojitools.getEmojiGroupsDelimitered('\n') << std::endl; // new line delimiter
    std::vector<std::string> vecEmojiGroups = tomarklib::emojitools.getEmojiGroupsList(); // get the list of emoji groups

    std::cout << tomarklib::emojitools.getEmojiSubGroupsDelimitered(';') << std::endl;
    // face-smiling;face-affection;face-tongue;face-hand;face-neutral-skeptical;face-sleepy;face-unwell;face-hat;face-glasses ...

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

```    




## ToDo

a lot of operations over handling emoticons
planned soon

## Requirements

- CMake 3.10 or higher
- Compiler supporting C++17 and earlier (C++20/23 is on the way)

## Installation

Developed under Linux with VSCode and CMake Extension.
MS Windows via MSYS2 tested too, but Win cmd console isn't supporting printing emojis.


1. Clone the repository:
    ```sh
    git clone https://github.com/tomasmark79/tomarklibdev
    cd tomarklibdev
    ```

2. Create a build directory and navigate into it:
    ```sh
    mkdir build
    cd build
    ```

3. Linux - Run CMake configuration and compile the project
    ```sh
    cmake -G Ninja .. -DCMAKE_BUILD_TYPE=Debug 
    cmake --build .
    ```
3. Windows - Run CMake configuration and compile the project
     ```sh
    cmake -G "MSYS Makefiles" .. -DCMAKE_BUILD_TYPE=Debug #
    cmake --build .
    ```

## Source files of library
`src/`

## Header files of library
`include/`

## Assets files of library
`assets/`
`LibToMarkLibrary.a` is dependent on **Unicode Organisation file** `emoji-tests.txt` which is included.

## Caller.cpp in root folder
is a `./caller` of compiled library `LibToMarkLibrary.a`. It is here only for fast start. It may show you how to link the library in your project very simply.
