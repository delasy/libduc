# libduc
Delasy Utilities Collection - collection of missing utilities developed by Aaron Delasy for The C Programming Language. \
Project code is fully covered with tests.

**Utilities**
- `array` - [Documentation](include/duc/array.h), [Example](examples/array.c)
- `binary` - [Documentation](include/duc/binary.h), [Example](examples/binary.c)
- `filesystem` - [Documentation](include/duc/fs.h), [File Example](examples/fs-file.c), [Path Example](examples/fs-path.c)
- `helpers` - [Documentation](include/duc/helpers.h)
- `map` - [Documentation](include/duc/map.h), [Example](examples/map.c)
- `testing` - [Documentation](include/duc/testing.h), [Example](examples/testing.c)
- `time` - [Documentation](include/duc/time.h)

## Building and installing
To build with [CMake](https://cmake.org):
```bash
$ mkdir -p build
$ (cd build && cmake .. -DCMAKE_BUILD_TYPE=Debug)
$ cmake --build build
```

To install with [CMake](https://cmake.org):
```bash
$ cmake --install build
```

To build and install with [Docker](https://www.docker.com):
```bash
$ docker build -t libduc .
```

## Usage
Preferred - you can import specific utility with:
```c
#import <duc/array.h>
```

Not efficient - you can import all utilities at once with:
```c
#import <duc.h>
```

With [CMake](https://cmake.org):
```cmake
cmake_minimum_required(VERSION 3.4)

find_path(LIBDUC_INCLUDE_DIR duc.h)
find_library(LIBDUC_LIBRARY duc)

# ...

target_include_directories(TARGET PRIVATE "${LIBDUC_INCLUDE_DIR}")
target_link_libraries(TARGET PRIVATE "${LIBDUC_LIBRARY}")
```

With [CMake's FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html):
```cmake
cmake_minimum_required(VERSION 3.14)
include(FetchContent)

FetchContent_Declare(libduc GIT_REPOSITORY https://github.com/delasy/libduc.git GIT_TAG v4.7.1)
FetchContent_MakeAvailable(libduc)

# ...

target_include_directories(TARGET PRIVATE "${libduc_SOURCE_DIR}/include")
target_link_libraries(TARGET PRIVATE duc)
```

## Testing
To test your build with [CMake](https://cmake.org):
```bash
$ (cd build && cmake .. -DCMAKE_BUILD_TYPE=Debug -DLIBDUC_BUILD_EXAMPLES=ON -DLIBDUC_BUILD_TESTS=ON)
$ cmake --build build
$ (cd build && ctest -T memcheck --output-on-failure)
```

To test your build with [Docker](https://www.docker.com):
```bash
$ docker run libduc
```

## Contributing
See the [guidelines for contributing](CONTRIBUTING.md).

## Version
Starting from version 1.0.0 libduc follows [Semantic Versioning](https://semver.org) rules.

## License
libduc is distributed under the terms of MIT License, see [LICENSE file](LICENSE) for details.
