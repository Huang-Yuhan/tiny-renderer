# Tiny Renderer

这个项目是关于ssloy/tiny-renderer的实现，以及在过程中的一些学习

之前是在Windows环境下用Visual Studio 和easyx进行编写。

现在装了双系统以及学习了一些新知识，准备在Ubuntu下用CMake和C++重新写一遍

## 直线

src/line-drawing 是画直线

## 三角形

src/triangle-drawing 是画三角形

## 一些编码规范

- 代码中自己写的指针，用`std::unique_ptr`管理
- 代码中自己写的数组，用`std::vector`管理
- 代码中自己写的字符串，用`std::string`管理
