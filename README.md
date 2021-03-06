# libGearBox
C++ library used for interacting with a remote [Transmission](https://transmissionbt.com/) server.

## Building
### Dependencies
The following combination of operating system and compiler are officially supported:
 * Windows (MinGW 4.9+, Microsoft Visual Studio 2015+)
 * Linux (GCC 4.9+, clang 3.8.1+) + cURL development libraries (libcurl4-openssl-dev on Ubuntu)
 * macOS (GCC 4.9+, clang 3.8.1+)

The project comes with all required (unless otherwise noted) dependencies as [git submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules). In adition to these [CMake](https://cmake.org/) is required to perform the actual build. Make sure that the cmake binary is in your `PATH`.

### Extra dependencies
Tests:
 * Python (min v3.4) libraries

Code coverage:
 * gcov
 * lcov
 * GCC/Clang/MinGW compiler
 
Documentation:
 * Doxygen

### Build steps
Clone the repository:
```bash
git clone https://github.com/kicsyromy/libGearBox.git
git submodule update --init
```
**Note:** Since CMake supports several Makefile formats, based on the target platform, I am not going to cover all of them here. Feel free to use the Visual Studio generator on Windows, or XCode generator on macOS. If a specific generator doesn't work for you please file a bug report.

**All platforms**
```
cd libGearBox
mkdir build
cd build
```

**Windows**
```
cmake .. -G "NMake Makefiles"
nmake
```

**Linux**
```
cmake .. -G "Unix Makefiles"
make -j $(grep -c ^processor /proc/cpuinfo)
```

**macOS**
```
cmake .. -G "Unix Makefiles"
make
```

The output of the build should be a static library called `libgearbox` with the appropriate extension (.lib on Windows, .a on Linux and macOS).

### Build options
libGearBox supports some [CMake options](https://cmake.org/cmake/help/v3.7/command/option.html) for a customized build. These are as follows:

`LIBGEARBOX_STATIC_LIB` Build static library if set to ON otherwise build shared library. Defaults to ON.

`LIBGEARBOX_DEBUG_LOGS` Build with additional debug logs. CAUTION: Do not use in production. Defaults to OFF.

`LIBGEARBOX_ENABLE_TESTS` Build tests. Defaults to OFF.

`LIBGEARBOX_TESTS_ENABLE_CODE_COVERAGE` Only available when building with tests. Enables code coverage generation using gcov/lcov.

`LIBGEARBOX_GENERATE_DOCUMENTATION` Generate HTML documentation, also builds manpages when building under Linux. Defaults to OFF.

### Using as a build dependency for a bigger project
The easiest way to use the library for a bigger project is to add this repository as a git submodule and including the CMakeLists.txt file of this project as a subdirectory in your own CMakeLists.txt and adding a dependency to your own target to `libgearbox`.
```
...
add_subdirectory(libgearbox)
add_executable (myapp main.cpp src1.cpp src2.cpp)
target_link_libraries (myapp libgearbox)
...
```
Please be aware that while some effort was put into not polluting the global CMake namespace with all sorts of intermediary variables the following are still present in the global namespace:
 - The options mentined above
 - `LIBGEARBOX_VERSION_MAJOR`, `LIBGEARBOX_VERSION_MINOR`, `LIBGEARBOX_VERSION_PATCH`
 - `LIBGEARBOX_PRIVATE_HEADERS`, `LIBGEARBOX_PUBLIC_HEADERS`, `LIBGEARBOX_SOURCES`

## Roadmap
TBD

## Contributing
Contributions are welcome, documentation, tests, code fixes etc. For a guideline on how contributions work on GitHub visit https://help.github.com/articles/working-with-forks/ and https://help.github.com/articles/proposing-changes-to-your-work-with-pull-requests/
