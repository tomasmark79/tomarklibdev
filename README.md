# ToMarkLibrary

Useful C++ library with some of features 

# Library Features

## Unicode emoji tools

```cpp
    // some useful functions
    std::cout << tomarklib::emojitools.getEmojiGroupsDelimitered(';') << std::endl;
    std::cout << tomarklib::emojitools.getEmojiGroupsDelimitered('\n') << std::endl;
    std::vector<std::string> vecEmojiGroups = tomarklib::emojitools.getEmojiGroupsList();

    std::cout << tomarklib::emojitools.getEmojiSubGroupsDelimitered(';') << std::endl;
    std::cout << tomarklib::emojitools.getEmojiSubGroupsDelimitered('\n') << std::endl;
    std::vector<std::string> vecEmojiSubGroups = tomarklib::emojitools.getEmojiSubGroupsList();
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
