#!/bin/sh

find_clang() {

if [ -f "/usr/bin/clang" ]
then
	clang_path="/usr/bin/clang"
elif [ -f "/usr/local/bin/clang" ]
then
	clang_path="/usr/local/bin/clang"
fi

if [ ! -z "$clang_path" ]
then
	echo "found clang at $clang_path"
	export CC=$clang_path
	return 0
else
	echo "could not find clang"
	return 1
fi

}

find_asm() {

if [ -f "/usr/bin/nasm" ]
then
	asm_path="/usr/bin/nasm"
elif [ -f "/usr/local/bin/nasm" ]
then
	asm_path="/usr/local/bin/nasm"
fi

if [ ! -z "$asm_path" ]
then
	echo "found netwide assembler at $asm_path"
	export ASM=$asm_path
	return 0
else
	echo "could not find netwide assembler."
	return 1
fi
}

find_clang
find_asm

