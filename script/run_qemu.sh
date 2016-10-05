#!/bin/sh

if ! command -v qemu-system-i386 >/dev/null 2>&1;
then
	echo "could not find qemu-system-i386, please install"
	exit 1
fi

qemu-system-i386 -cpu 486 -kernel kernel/racoon -m 1024
