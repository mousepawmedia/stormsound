# Building Stormsound

## Building Basics

CMake is used to build Stormsound and Stormsound Tester. For your convenience,
we've included Makefiles to automate all common build scenarios on Linux.
Run `$ make` in the root of this repository for more information.

At this time, the Makefiles are only designed for Linux. If you are building
on another system, you can interact with CMake directly.

Currently, Stormsound is only designed to be built by GCC (5.3 or later) or
Clang (3.4 or later).

## Building and Linking Dependencies

Stormsound relies on CPGF, Opus, and PawLIB. The default behavior of the build
system is to look for MousePaw Media's `libdeps/` and `pawlib/` repositories,
cloned parallel to this repository's main folder. Simply run `$ make ready` in
each of those repositories (optionally, you can run `$ make cpgf && make opus`
in `libdeps/`) before building this one. (This is our default for company
development environments.)

You can specify custom paths for these libraries by creating a `.config` file
in the root of this repository. Make a copy of `build.config.txt` and save it
with the ending `.config`. See that file for more information.

## Ready-To-Use Build

If you just want to build Stormsound to use in your own project, the fastest way is
to run `$ make ready`. This will build Stormsound and place it in a folder called
`stormsound`, then point your compiler and linker to `stormsound/include` and
`stormsound/lib` respectively. Our other repositories point to this by default.

## Building HTML Docs

If you want the HTML documentation for Stormsound, run `$ make docs`. Then, grab the
`docs/build/html` folder, or just open `docs/build/html/index.html` in your
favorite web browser.

## Building Tester

If you want to test out Stormsound directly, run `make tester`. Then, look for the
`stormsound-tester` executable in `stormsound-tester/bin/[Debug/Release]`.
Alternatively, you may use the symbolic link `tester` or `tester_debug` in the
root of this repository.

## Code::Blocks

Stormsound was written and built in CodeBlocks. The projects (`*.cbp`) in this
repository are pre-configured to build directly in the repository.

## Source Directories

- The `/docs` folder contains the Sphinx documentation for Stormsound.
- The `/stormsound-source` folder contains the source code for the Stormsound
  library.
- The `/stormsound-tester` folder contains the console application for testing
  the Stormsound library.
