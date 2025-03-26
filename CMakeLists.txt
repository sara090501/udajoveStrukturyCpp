cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)

project(cv2C)
add_executable(cv2C
        main.cpp
        needleman_wunsch.cpp
        trie.cpp
        utils.cpp
)
