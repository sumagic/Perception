# Perception

#### Description
{**When you're done, you can delete the content in this README and update the file with details for others getting started with your repository**}

#### Software Architecture
Software architecture description

#### 依赖库编译
1.  googletest编译
```bash
cmake .. -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=googletest-dev
```

2. yaml-cpp编译
```
cmake .. -DYAML_BUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=yaml-cpp

```

#### 依赖库交叉编译

* 导出环境变量
```bash
export PATH=/home/***-sdk/tools/gcc-linaro-7.5.0/bin
```

1. opencv编译过程
```bash
https://gitee.com/mirrors_trending/opencv.git
cd platforms/linux
# opencvX.X.X/platforms/linux目录下，选择aarch64-gnu.toolchain.cmake 工具链
# 在进行编译前，需要修改cmake文件，修改platform/linux/aarch64-gnu.toolchain.cmake，改为如下：
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(GCC_COMPILER_VERSION "" CACHE STRING "GCC Compiler version")
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
set(GNU_MACHINE "aarch64-linux-gnu" CACHE STRING "GNU compiler triple")
include("${CMAKE_CURRENT_LIST_DIR}/arm.toolchain.cmake")
```
* 编译
```bash
cd ${opencv_root}
git clone https://gitee.com/mirrors/opencv_contrib.git
cd build
cmake -DCMAKE_INSTALL_PREFIX=install -DWITH_OPENCL=ON -DENABLE_PRECOMPILED_HEADERS=OFF -DCMAKE_TOOLCHAIN_FILE=../platforms/linux/aarch64-gnu.toolchain.cmake  -DBUILD_SHARED_LIBS=ON -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules/ ..
make -j
make install
```

2.  ncnn编译
```bash
git clone https://gitee.com/Tencent/ncnn.git
cd <ncnn-root-dir>
mkdir -p build-aarch64-linux-gnu
cd build-aarch64-linux-gnu
cmake -DCMAKE_TOOLCHAIN_FILE=../toolchains/aarch64-linux-gnu.toolchain.cmake ..
make -j$(nproc)
```

3.  yaml-cpp编译
```bash
git clone https://gitee.com/mirrors/yaml-cpp.git
```
* 在yaml-cpp目录下创建一个名为arm-linux-gnueabi.toolchain.cmake的文件，内容如下：
```bash
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
```
* 编译
```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../arm-linux-gnueabi.toolchain.cmake -DYAML_BUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=install
make -j
make install
```

4.  googletest编译
* 在yaml-cpp目录下创建一个名为arm-linux-gnueabi.toolchain.cmake的文件，内容如下
```bash
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)
```
* 编译
```bash
cmake .. -DCMAKE_TOOLCHAIN_FILE=../arm-linux-gnueabi.toolchain.cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=install
make -j
make install
```

#### Instructions

1.  xxxx
2.  xxxx
3.  xxxx

#### Contribution

1.  Fork the repository
2.  Create Feat_xxx branch
3.  Commit your code
4.  Create Pull Request


#### Gitee Feature

1.  You can use Readme\_XXX.md to support different languages, such as Readme\_en.md, Readme\_zh.md
2.  Gitee blog [blog.gitee.com](https://blog.gitee.com)
3.  Explore open source project [https://gitee.com/explore](https://gitee.com/explore)
4.  The most valuable open source project [GVP](https://gitee.com/gvp)
5.  The manual of Gitee [https://gitee.com/help](https://gitee.com/help)
6.  The most popular members  [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
