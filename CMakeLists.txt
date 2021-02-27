#
# Copyright (c) Aaron Delasy
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
#

cmake_minimum_required(VERSION 3.4)
project(libduc VERSION 4.7.1 LANGUAGES C)

include(GNUInstallDirs)

option(LIBDUC_BUILD_EXAMPLES "Build example programs" OFF)
option(LIBDUC_BUILD_TESTS "Build test programs" OFF)

set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wconversion -Werror -Wextra -Wshadow -Wundef -Wunreachable-code -pedantic-errors")

set(sources src/array.c src/array.h src/binary.c src/binary.h src/common.c src/fs.c src/fs.h src/map.c src/map.h src/time.c)

include_directories(include)

add_library(duc SHARED ${sources})
add_library(duc_a STATIC ${sources})

if (MINGW OR UNIX)
  set(includedir "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
  set(libdir "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
  set(prefix "${CMAKE_INSTALL_PREFIX}")

  configure_file(libduc.pc.in libduc.pc @ONLY)
  configure_file(libduc-static.pc.in libduc-static.pc @ONLY)

  install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
  install(FILES LICENSE DESTINATION "${CMAKE_INSTALL_DOCDIR}")
  install(FILES "${PROJECT_BINARY_DIR}/libduc.pc" "${PROJECT_BINARY_DIR}/libduc-static.pc" DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
  install(TARGETS duc duc_a LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
endif ()

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND LIBDUC_BUILD_EXAMPLES)
  set(examples array binary fs-file fs-path map testing)

  foreach (example ${examples})
    add_executable(${PROJECT_NAME}-example-${example} examples/${example}.c)
    target_link_libraries(${PROJECT_NAME}-example-${example} PRIVATE duc)
  endforeach ()
endif ()

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND LIBDUC_BUILD_TESTS)
  set(CTEST_MEMORYCHECK_COMMAND valgrind)
  set(MEMORYCHECK_COMMAND_OPTIONS "--error-exitcode=1 --leak-check=full --show-leak-kinds=all --tool=memcheck --track-origins=yes")

  include(CTest)
  set(tests array binary common fs map time)

  foreach (test ${tests})
    add_executable(${PROJECT_NAME}-test-${test} tests/${test}-test.c)
    target_link_libraries(${PROJECT_NAME}-test-${test} PRIVATE duc)
    add_test(${test} ${PROJECT_NAME}-test-${test})
  endforeach ()
endif ()
