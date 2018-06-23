cmake_minimum_required(VERSION 2.8)
project(CardSimulator CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O1 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# サブディレクトリ登録
add_subdirectory(include)

add_executable(CardSimulator.out main.cpp)

# ライブラリのリンク
target_include_directories(CardSimulator.out PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(CardSimulator.out cards)

