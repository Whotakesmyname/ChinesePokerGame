# 「斗地主」残局解算器  
Chinese Poker Game Solver  
(中文文档 | [English version](./README.md))

这是一个可能是目前最快的斗地主残局解算器。使用C++实现，采用MinMax算法思想，并进行了对象复用、多线程等一系列的优化，使得它与目前能找到的其他相似程序相比占用内存少，
解算速度快数倍甚至若干量级。

关于实现的细节请参考该篇博文：[《“斗地主”残局的对抗搜索算法》](https://blog.darkray.cn/tech/algorithm/adversarial-search-on-chinese-poker-game/)

## 环境要求

### 测试环境
- CPU: Intel(R) Core(TM) i7-4710MQ CPU @ 2.50GHz
- RAM: DDR3L 24G(8+8+4+4)

一般情况下占用**1G内存**，于**2秒**内得出结果；少于10%的高复杂度问题(场上手牌总数>20张)需要约**10G内存**，于**1分钟**左右得到结果。  

## 使用方法

- 提供Windows平台下x64版本已编译完成的[可执行文件下载](https://github.com/Whotakesmyname/ChinesePokerGame/releases)
- 自行编译

运行可执行文件`ChinesePokerGame.exe`即可

## 编译方法
**本项目要求C++20**  
*推动编译Toolchain版本升级人人有责*

在项目根目录下新建build目录，在build目录内使用cmake构建编译。或者使用IDE（如VS Code）安装cmake插件，自动读取并配置编译环境。项目无外部第三方依赖，但**依赖C++20标准库**。
