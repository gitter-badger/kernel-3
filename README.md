[![Build Status](https://travis-ci.org/racoon-os/kernel.svg?branch=master)](https://travis-ci.org/racoon-os/kernel)

# racoon
A small OS for x86, initially targeting 486. This is the kernel for the OS.

# Setting up the environment
First, build a toolchain for cross compilation by running

	$ toolchain/build.sh

This will take a while so get yourself a cup of well deserved :coffee:

# Building the kernel
First, create a folder to hold the build artefacts:

	$ mkdir build

then change directory to that folder

	$ cd build

Make sure to have cmake installed and reachable in your
`PATH` and then run

	$ cmake ../

or

	$ cmake -DCMAKE_BUILD_TYPE=Debug ../

for a debug build.

This will generate makefiles so that you can in the next step run:

	$ make

If all goes well, racoon should build and the resulting binary
should be in `src/racoon`, relative to the `build` folder
created above.

To run qemu with the kernel, make sure to have qemu
installed and run (once again in the `build` directory):

	$ qemu-system-i386 -cpu 486 -kernel src/racoon

This will start an emulated x86 system and the kernel should now
boot.
