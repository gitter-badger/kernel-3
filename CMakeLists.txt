cmake_minimum_required(VERSION 3.0)
SET(CMAKE_SYSTEM_NAME Generic)

enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf)

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

project(racoon C ASM_NASM)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

#configure_file(src/config.h.in ${CMAKE_BINARY_DIR}/config.h)
#configure_file(script/run.sh.in ${CMAKE_BINARY_DIR}/run.sh)

include_directories(${CMAKE_BINARY_DIR} "kernel/include")

set(CMAKE_C_FLAGS "-Werror -std=gnu99 -ffreestanding -Wall -target i686-pc-none-elf")

set(CMAKE_EXE_LINKER_FLAGS "-T ${PROJECT_SOURCE_DIR}/script/link.ld -ffreestanding -nostdlib")

add_subdirectory(kernel)
