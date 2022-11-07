# 生成Linux 平台 可以通过html 展示覆盖度，通过率的gtest gmock c++单元测试框架
要在 HTML 格式中展示覆盖度和通过率的 GoogleTest 和 GoogleMock，我们可以使用 LCOV 和 genhtml 工具。这是一个简单的演示：

首先，确保已安装所有依赖项：

1. 安装 LCOV：
   ```
   sudo apt-get install lcov
   ```

2. 根据上一个示例中的说明安装 GoogleTest 框架。

现在，使用此文件结构扩展前面的示例：

```
gtest_coverage_example/
|-- CMakeLists.txt
|-- include/
|   |-- Calculator.h
|-- src/
|   |-- Calculator.cpp
|-- test/
|   |-- CalculatorTest.cpp
|-- gmock/
```

在 gmock 目录中，执行以下命令下载和编译 GoogleMock：

```sh
git clone https://github.com/google/googletest.git gmock-source
cd gmock-source/googletest
cmake -S . -B build
cmake --build build
```

接下来，编辑 `CMakeLists.txt` 并添加 GoogleMock：

```cmake
cmake_minimum_required(VERSION 3.14)
project(gtest_coverage_example)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")

include_directories(include)
add_executable(main src/Calculator.cpp)

enable_testing()

# Add googlemock
add_subdirectory(gmock/gmock-source)
include_directories(SYSTEM ${GTEST_INCLUDE_DIRS})
include_directories(${GMOCK_INCLUDE_DIRS})

# Link google test and google mock
add_executable(calculator_tests test/CalculatorTest.cpp)
target_link_libraries(calculator_tests ${GTEST_BOTH_LIBRARIES} pthread)
target_link_libraries(calculator_tests gmock)
target_compile_features(calculator_tests PRIVATE cxx_std_14)

gtest_discover_tests(calculator_tests)
```

现在，编译并运行测试：

```sh
mkdir build
cd build
cmake ..
make
make test
```

生成覆盖率报告：

```sh
lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info '*/test/*' '/usr/*' '*/gmock/*' --output-file coverage-filtered.info
```

生成覆盖率的 HTML 报告：

```sh
genhtml coverage-filtered.info --output-directory coverage-html
```

最后，使用浏览器打开 `coverage-html/index.html` 查看覆盖率报告。

# 生成windows 平台 可以通过html 展示覆盖度，通过率的gtest gmock c++单元测试框架
要在 Windows 平台上构建此方案并生成 HTML 格式的覆盖率和通过率报告，我们将使用以下工具：

* MSYS2：运行集成环境和代码编译器
* CMake：构建生成器和管理
* Google Test and Google Mock：单元测试框架
* OpenCppCoverage：Windows 平台的代码覆盖率工具
* ReportGenerator：生成 HTML 报告

安装和设置：

1. 下载并安装 [MSYS2](https://www.msys2.org/)。

2. 打开 MSYS2 64-bit 终端。

3. 输入以下命令安装 CMake、GCC、make 和 git 依赖项：
   ```
   pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-gcc make git
   ```

4. 安装 GoogleTest。
   ```
   git clone https://github.com/google/googletest.git
   cd googletest
   cmake -S . -B build
   cmake --build ./build
   cmake --install ./build --prefix /mingw64
   ```

现在，使用与前面的示例相同的文件结构扩展该示例。请注意，您无需使用 GMock 的下载步骤，因为我们已经安装了 GoogleTest 和 GoogleMock。

**CMakeLists.txt**

```cmake
cmake_minimum_required(VERSION 3.14)
project(gtest_coverage_example)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
add_executable(main src/Calculator.cpp)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(calculator_tests test/CalculatorTest.cpp)
target_link_libraries(calculator_tests ${GTEST_BOTH_LIBRARIES})

gtest_discover_tests(calculator_tests)
```

编译并运行测试：

```sh
mkdir build
cd build
cmake -G"MSYS Makefiles" ..
make
make test
```

安装覆盖率工具：

1. 下载并安装 [OpenCppCoverage](https://github.com/OpenCppCoverage/OpenCppCoverage/releases)。

2. 下载并解压 [ReportGenerator](https://github.com/danielpalme/ReportGenerator/releases) 的最新版本。

3. 将安装目录下的 "bin" 文件夹（OpenCppCoverage 和 ReportGenerator 的 "bin" 文件夹）添加到系统的 PATH 环境变量中。

生成覆盖率报告：

在 MSYS2 兼容的 CMD 或 PowerShell 窗口中执行以下命令。请注意，使用 MSYS2 终端可能导致路径问题。

```sh
OpenCppCoverage --sources "path\to\gtest_coverage_example\include" --sources "path\to\gtest_coverage_example\src" --export_type binary:cov_output.coverage "path\to\gtest_coverage_example\build\calculator_tests.exe"
```

生成 HTML 报告：

```sh
ReportGenerator -reports:cov_output.coverage -targetdir:coverage_html -reporttypes:Html
```

打开生成的 `coverage_html/index.htm` 文件，以 HTML 格式查看覆盖率和通过率报告。
