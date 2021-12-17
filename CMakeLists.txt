cmake_minimum_required(VERSION 3.13.0...3.22.0)
project(TNG033-Lab-3 VERSION 1.0.0 DESCRIPTION "TNG033 Lab 3" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(enable_warnings target)
target_compile_options(${target} PUBLIC 
$<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall -Wextra>
)
endfunction()

add_executable(Exercise1 exerc1.cpp uppgift1_kort.txt out_uppgift1_kort.txt uppgift1.txt out_uppgift1.txt)
add_executable(Exercise2 exerc2.cpp uppgift2_kort.txt anagrams_uppgift2_kort.txt out_uppgift2_kort.txt uppgift2.txt anagrams_uppgift2.txt out_uppgift2.txt)

enable_warnings(Exercise1)
enable_warnings(Exercise2)