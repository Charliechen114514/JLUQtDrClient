# JLUQtDrClient

## 开始之前...

​	这是一个使用Qt6框架的，是由Dessera大爹开发的cygnus-rs的一个简单的UI包装器，cygnus-rs的项目地址在：[Dessera/cygnus-rs: Rust Implementation of JLU Drcom client (github.com)](https://github.com/Dessera/cygnus-rs)。

​	具体的使用方法参考下文 :)

​	Dessera's github :https://github.com/Dessera

## Stylesheet

​	本项目使用的Stylesheet是著名MIT开源的QSS

​	[ColinDuquesnoy/QDarkStyleSheet: A dark style sheet for QtWidgets application (github.com)](https://github.com/ColinDuquesnoy/QDarkStyleSheet?tab=License-1-ov-file) 

​	如有侵犯，请立即告知本人删除。

## 方法1 直接使用发行

​	Release地址：[Release v1.0 · Charliechen114514/JLUQtDrClient (github.com)](https://github.com/Charliechen114514/JLUQtDrClient/releases/tag/v1.0)

​	下载后前往[Dessera/cygnus-rs: Rust Implementation of JLU Drcom client (github.com)](https://github.com/Dessera/cygnus-rs)下载核心驱动，放到可执行文件目录下的core文件夹下，即可按照软件内帮助文档依次注册用户与启动文件！

## 方法2 构建自定义版本

​	要构建软件，应该拥有版本可能高于5.15的Qt框架，以及基本的Qt模块和Qt网络（如果你没有QtNetwork，请通过MaintainTools.exe下载：）

​	编译完成后，在可执行目录中创建一个名为“core”的目录，并将cygnus可执行文件复制到其中，然后你就可以连上JLU.PC了！

​	任何人都可以自由修改源代码并构建自己的版本。

## Before Start

​	This is a software aims to wrapping the cygnus implemented by Dessera using rust, with Qt6 C++. The Core Driver is cygnus-rs, implemented by Dessera, whose github url is: https://github.com/Dessera

​	The Core Driver Execuatble is supposed to be fetched at His cygnus-rs repository, with url giving here [Dessera/cygnus-rs: Rust Implementation of JLU Drcom client (github.com)](https://github.com/Dessera/cygnus-rs). Anyone who gonna use the core file with this Qt GUI Wrapper is supposed to follow the instructions under below :)。If there is any infringement, please post an issue to me for deleting it as soon as possible:)

## StyleSheet

​	The Default Stylesheet is provided by [ColinDuquesnoy/QDarkStyleSheet: A dark style sheet for QtWidgets application (github.com)](https://github.com/ColinDuquesnoy/QDarkStyleSheet?tab=License-1-ov-file), Whose license is MIT. 

## Use Releases Directly

One shall use the sources directly for the releases at

> [Release v1.0 · Charliechen114514/JLUQtDrClient (github.com)](https://github.com/Charliechen114514/JLUQtDrClient/releases/tag/v1.0)

or see the building manuals below :)

​	After downloading the executable files, put the cygnus-file under the dirent /core/, then executate the file :)

## Build Reference

​	To Build the software, one should owns Qt Framework with version possible above 5.15, with base Qt Modules and Qt Network(If u don't have QtNetwork, download by MaintainTools.exe then :) 

​	After compilings, create a dirent at the executable direct called "core" and copy the cygnus execuatble into it, then u shell enjoy's it!

​	Anyone has free access to modify the source code and build up they own versions.
