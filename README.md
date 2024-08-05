# ToMarkLib

My own C++ library with useful stuff

## Library Features


# Unicode emoji tools
- Print/Get Unicode Emoji by Code Point
```cpp
 char32_t emojiCodePoint[1] = {0x1F600}; // 😀
    printEmojiCodePoint(emojiCodePoint, 1);
    std::string EmojiTools::getEmojiCodePoint(char32_t *emojiCodePoints, size_t length)
```

- Print/Get Unicode Emoji by multiple Code Points with variable count of modifiers
 ```cpp
 char32_t emojiCodePointWSelector7[7] = {0x1F9D1, 0x1F3FF, 0x200D, 0x1F9AF, 0x200D, 0x27A1, 0xFE0F}; // 🧑🏿‍🦯‍➡️
    printEmojiCodePoint(emojiCodePointWSelector7, 7);
    std::string EmojiTools::getEmojiCodePoint(char32_t *emojiCodePoints, size_t length)
```

- Print/Get Count of Unicode Emoji by Group 💀☠️☠💩🤡👹👺👻👽👾 ...
```cpp
    printEmojiGroup("Smileys & Emotion");    
```

- Print/Get Count of Unicode Emoji by Sub Group 😌😔😪🤤😴
```cpp
    printEmojiSubGroup("face-sleepy");
```

## ToDo

a lot of operations over handling emoticons

## Requirements

- CMake 3.10 or higher
- Compiler supporting C++17

## Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/tomasmark79/tomarklibdev
    cd project
    ```

2. Create a build directory and navigate into it:
    ```sh
    mkdir build
    cd build
    ```

3. Run CMake and compile the project:
    ```sh
    cmake ..
    make
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


## License

