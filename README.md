
![CEX Logo](/img/cex.jpg)

# CEX
The C-Extended Standard Library.

## Purpose
To satisfy the need for a central collection of high-quality C-language extensions.

## Goals
1. To be POSIX and ANSI C compliant.
2. To be freely distributed across popular package repositories.
3. To add new and adapted extensions to the C standard library in a libc-like fashion.

## Building
```
$ cmake -B build .
$ cmake --build build
```
For more information on building see [Build Flags](#build-flags) and [Cross-Compiling](#cross-compiling).

## Installing
Once built, `libcex.a` and its header `cex.h` can be installed on the host system by running
```
$ cmake --install build
```

## Usage
To use CEX in your project, include the `cex.h` header and link `libcex.a` to your binary at compile-time:
```c
#include <cex.h>

int main(void) {
    ...
    return 0;
}
```

```
$ gcc my_source.c -lcex
```

## FAQ
### Hasn't this been tried before?
Spurious attempts have been made to provide custom string support to C or even collect community-made C libraries in one place with CLI tooling.

But...

1. There is no uniformity in convention or quality whatsoever – some are excellent and well-documented, others are broken and even memory leak hells. Even if they were somehow all made to be top-notch in quality and stability, I still wouldn’t have confidence that libraries will resemble each other or work cohesively. This issue seems intrinsic to the fact that they are developed by disjoint developers, all with different needs, goals, visions and standards for their code.

2. The lack of consistency and predictability among the libraries offers no opportunity for an intuition to be built around higher-level constructs like strings. Different naming conventions, different memory allocation schemes and custom error handling methods all need to be learned and applied separately to components of the same code. 

3. Even if (1) and (2) can be overcome or tolerated, this does not prevent the pollution of the C code’s namespace. Up to 3-4 different developers may have come up with their own ‘str’ method or type, and the confusion of the similarities aside it may just straight up collide in the symbol table. Few to none of the efforts dare try to use short and catchy representations of types and methods since if they are not already taken they are certain to cause a collision sooner or later.

## Appendix
### Build Flags
The build process can be modified with the following build flags:

#### Debug Build Flag
Enabling the debug build flag will compile `libcex.a` with the `-g` flag for use when debugging dependent programs.
```
$ cmake -B build -DDEBUG=1 .
```

#### CEX Namespace Flag
Although experimental, an attempt at C-namespace encapsulation is included (for now) which makes use of a struct of function pointers to the library functions in `libcex.a`. See [cex.h](/cex.h) for what this is about.
```
$ cmake -B build -DCEX_USE_NAMESPACE=1 .
```

This is not recommended for small embedded systems that are limited in memory as initializing the struct of function pointers required a good amount of stack space.

### Cross-compiling
#### Method 1: Adding `libcex.a` to your toolchain
See [cmake-toolchains](https://cmake.org/cmake/help/latest/manual/cmake-toolchains.7.html) on how to cross-compile CMake for your target system.
```
$ cmake -B build -DCMAKE_TOOLCHAIN_FILE=cross.cmake .
```
Where `cross.cmake` is a CMake toolchain descriptor file you'll need to setup and adapt according to your needs.

Once cross-compiled, `libcex.a` can be added to the embedded system toolchain you depend on (like the ARM GNU toolchain distribution). The toolchain 'home' directory will have a `/lib` or `/usr/lib` directory of its own where `libcex.a` can be added. 

You will need to manage the include directories visible to your IDE to ensure `cex.h` is visible for inclusion. When in doubt, you can drop `cex.h` into the include directory of your project.

#### Method 2: Adding `cex.c` and `cex.h` as sources to your project
Alternatively, `cex.c` and `cex.h` can directly be added to your embedded development project as local source files. They can be obtained from the source distribution of this repo and manually inserted.
