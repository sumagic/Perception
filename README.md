# Perception

#### Description
* 本代码仓主要实现感知部署基础框架代码
* 使用Eigen::Tensor作为基础的数据结构
* 支持NCNN

#### Software Architecture
* ai_engine: 提供简化、通用、灵活的感知部署框架
* operator: 实现常用的预处理和后处理算子
* utils: 实现工具类等

### 编译
* 修改ecarx_engine位置:
```bash
set(ECARX_ENGINE_PATH "/home/geely/kx/ecarx-ai-sdk/ecarx/ecarxengine")
```

#### 依赖库编译
* ubuntu20.04
* cmake 3.16.3
* gcc 9.3.0
* aarch64-linux-gnu-gcc 7.5.0


1.  googletest编译
```bash
cmake .. -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=googletest-dev
```

2. yaml-cpp编译
```
cmake .. -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=yaml-cpp-dev

```

3、opencv-x86编译
```
cmake -DCMAKE_INSTALL_PREFIX=opencv-dev -DWITH_OPENCL=ON -DENABLE_PRECOMPILED_HEADERS=OFF  -DBUILD_SHARED_LIBS=ON -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules/ ..

```

4、eigen编译
```bash
cmake .. -DCMAKE_INSTALL_PREFIX=Eigen

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
cmake -DCMAKE_INSTALL_PREFIX=opencv-dev -DWITH_OPENCL=ON -DENABLE_PRECOMPILED_HEADERS=OFF -DCMAKE_TOOLCHAIN_FILE=../platforms/linux/aarch64-gnu.toolchain.cmake  -DBUILD_SHARED_LIBS=ON -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules/ ..
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
cmake .. -DCMAKE_TOOLCHAIN_FILE=../arm-linux-gnueabi.toolchain.cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=yaml-cpp-dev
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