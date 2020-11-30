# DRender

基于OpenGL、Vulkan的渲染引擎，我们希望全平台支持，被迫不能选择DX12，选择Vulkan应该是最明智的选择

运行环境：

```
MacOS 11.0.1
Xcode 12.2 SDK
Clion 2020.3
```

安装以下依赖项（brew下载）：

```
glfw - Window creation, input handling
glm - Math operations
```

从WebSite下载：[glad](https://glad.dav1d.de/)

安装SOIL：

从GitHub[下载](https://github.com/kbranigan/Simple-OpenGL-Image-Library) ，然后进行make，得到一个静态链接库，再把`soil.h`拉入工程之中正常引用即可，编译时，Mac下如果出现bug，可以尝试将Cocoa framework加入其中即可解决

安装vulkan（未完成，TODO）:

```bash
brew install vulkan-header
brew cask install apenngrace/vulkan/vulkan-sdk
```

再从下载的里面查看版本号，在`CMakeList.txt`中修改成对应的目录即可