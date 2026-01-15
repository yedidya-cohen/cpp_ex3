set -e

cd "/cygdrive/c/C++/Advance C++/ex3/cmake-build-debug"
/AppData/Local/JetBrains/CLion2023.2/cygwin_cmake/bin/cmake.exe --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
