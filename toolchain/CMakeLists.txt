cmake_minimum_required(VERSION 2.6)
project(prism_deps)

set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/usr)

find_program(MAKE_PRG NAMES gmake make)
if(MAKE_PRG)
	execute_process(
		COMMAND "${MAKE_PRG}" --version
		OUTPUT_VARIABLE MAKE_VERSION_INFO)
	if(NOT "${OUTPUT_VARIABLE}" MATCHES ".*GNU.*")
		unset(MAKE_PRG)
	endif()
endif()
if(NOT MAKE_PRG)
	message(FATAL_ERROR "GNU Make is required to build the dependencies.")
else()
	message(STATUS "Found GNU Make at ${MAKE_PRG}")
endif()

include(ExternalProject)

ExternalProject_Add(
	binutils
	URL ftp://ftp.gnu.org/gnu/binutils/binutils-2.27.tar.bz2
	CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR> --target i686-elf --with-sysroot
)

ExternalProject_Add(
	gcc
	URL ftp://ftp.gnu.org/gnu/gcc/gcc-6.2.0/gcc-6.2.0.tar.bz2
	CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR> --target i686-elf
	--disable-nls --enable-languages=c --without-headers --disable-libssp --disable-libquadmath
	DEPENDS binutils
)
