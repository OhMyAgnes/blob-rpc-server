# blob-rpc-server
# 项目信息
这是一个实践项目，面向工业交付场景，实现了一个图像处理SDK和RPC服务。

# 项目需求
我们希望模拟一个项目的完整开发和迭代过程，故初期需求和功能都比较简单（但也不要忘记考虑扩展性）。
## 使用场景
用户通过RPC协议发起调用，输入图片等数据，server处理请求并调用计算节点（一个节点是一个sdk实例，目前只考虑一个节点的情况），计算节点处理输入并输出结果。
## 输入
一个RPC请求包含一张任意图片、一个float类型的阈值。
## 输出
灰度值超过阈值的所有区域轮廓。

# 开发流程
从零开始的项目交付。
## 开发环境搭建
- 操作系统：Linux/Windows均可（推荐Ubuntu18.04）
- IDE：VS Code（需要C++相关插件）
- 构建工具：CMake
- 编译器：gcc7.4/msvc150（至少需要支持C++11）
- 版本管理：Git

以上环境都搭建完成之后，还需要为我们的项目安装grpc环境。grpc是Google的一个开源框架。
Linux可以很方便的用源码编译安装。
```shell
# ubuntu
git clone --depth=1 -b v1.41.1 https://github.com/grpc/grpc.git && \
    cd grpc && git submodule update --init && mkdir build && cd build && cmake -DgRPC_INSTALL=ON -DCMAKE_BUILD_TYPE=Release -DgRPC_BUILD_TESTS=OFF -DgRPC_SSL_PROVIDER=module .. && make -j4 && make install
```

Windows推荐用vcpkg安装 [参考这里](https://github.com/grpc/grpc/blob/master/src/cpp/README.md#install-using-vcpkg-package)
```shell
# windows powershell
# install vcpkg package manager on your system using the official instructions
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg

# Bootstrap on Linux:
./bootstrap-vcpkg.sh
# Bootstrap on Windows instead:
# ./bootstrap-vcpkg.bat

./vcpkg integrate install

# install gRPC using vcpkg package manager
./vcpkg install grpc
```

## 需求分析、接口设计

## 协同开发
