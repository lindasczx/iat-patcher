## IAT补丁工具 for Windows XP+2003

该补丁工具可使得不支持Windows XP/2003的32位程序运行于Windows XP/2003上。

## 简史

随着Windows XP和2003结束官方支持，越来越多的程序开始不支持Windows XP和2003。但由于众所周知的原因，服务器市场上对Windows Server 2003的需求依然非常旺盛，其中当属PHP为最大需求。然而，PHP从5.5开始就不支持2003了，因此本工具诞生了。

## 适用程序

以下程序经过测试可用：
* PHP 5.5 - 7.1 官网版（CGI确定可用，CLI好像有BUG）（海量三方扩展也需要处理）
* FileZilla Server 0.9.43 - 0.9.57

理论上所有包含重定位信息的PE文件都可以经过处理变得可用。本工程仅针对PHP和FileZilla处理了少数XP/2003不存在的新API，若有别的新API，欢迎提交模拟实现代码。

## 使用方法

下载dist目录中所有文件，放入需要补丁的程序根目录中，运行bat即可。

可能需要安装VC运行时库。目前所有VC运行时库（2003-2017）均支持Windows XP/2003。

## 贡献者

nonxp使用了WineHQ项目的代码。

## 报告BUG

请在issues里面报告。

## 许可证

本代码由两部分组成，其中iatpatcher使用两句版BSD许可证，nonxp使用WineHQ所用的LGPL许可证。

