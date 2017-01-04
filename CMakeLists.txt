cmake_minimum_required(VERSION 3.6)

set(CMAKE_SYSTEM_NAME Generic)

enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/toolchain/usr/bin/i686-elf-gcc)
	message(FATAL_ERROR "No cross compiler could be found. Run toolchain/build.sh to build it")
endif()

set(CMAKE_C_COMPILER ${CMAKE_CURRENT_SOURCE_DIR}/toolchain/usr/bin/i686-elf-gcc)

project(racoon C ASM_NASM)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#configure_file(src/config.h.in ${CMAKE_BINARY_DIR}/config.h)
#configure_file(script/run.sh.in ${CMAKE_BINARY_DIR}/run.sh)

include_directories(${CMAKE_BINARY_DIR} "src/include")

set(CMAKE_C_FLAGS "-Werror -std=gnu99 -ffreestanding -Wall")
set(CMAKE_EXE_LINKER_FLAGS "-T ${PROJECT_SOURCE_DIR}/script/link.ld -ffreestanding -nostdlib")

add_subdirectory(src)
