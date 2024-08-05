cmake_minimum_required(VERSION 3.10)
project(ToMarkLibrary VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Debug)

# Copy assets to build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/assets/emoji-test.txt ${CMAKE_CURRENT_BINARY_DIR}/assets/emoji-test.txt COPYONLY)

# Library source files
set(LIBRARY_SOURCES
    src/ToMarkLibrary.cpp    
    src/Utf8Tools.cpp
    src/EmojiTools.cpp
)

# Library target
add_library(ToMarkLibrary STATIC ${LIBRARY_SOURCES})
# Library Header files
target_include_directories(ToMarkLibrary PUBLIC ${PROJECT_SOURCE_DIR}/include)
# Output library to a specific directory
set_target_properties(ToMarkLibrary PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Caller target
add_executable(Caller Caller.cpp)
target_include_directories(Caller PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(Caller PRIVATE ToMarkLibrary)

# Ensure Caller looks in the right directory for the library
target_link_directories(Caller PRIVATE ${CMAKE_BINARY_DIR}/lib)


