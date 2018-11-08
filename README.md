# 「斗地主」残局解算器  
Chinese Poker Game Solver  

It is an Chinese Poker Game solver using MinMax algorithm, and maybe also the fastest one.  
The Chinese Poker Game is also known as 斗地主(Dou Di Zhu).

For more details of the realization, please refer to my blog [Adversarial Search on Chinese Poker Game](https://blog.darkray.cn/tech/algorithm/adversarial-search-on-chinese-poker-game/)

这是一个可能是目前最快的斗地主残局解算器。使用C++实现，采用MinMax算法思想，并进行了对象复用、多线程等一系列的优化，使得它与目前能找到的其他相似程序相比占用内存少，
解算速度快数倍甚至若干量级。

关于实现的细节请参考该篇博文：[《“斗地主”残局的对抗搜索算法》](https://blog.darkray.cn/tech/algorithm/adversarial-search-on-chinese-poker-game/)

## 环境要求
Environment Requirements

### 测试环境
Test Environment

- CPU: Intel(R) Core(TM) i7-4710MQ CPU @ 2.50GHz
- RAM: DDR3L 24G(8+8+4+4)

一般情况下占用**1G内存**，于**2秒**内得出结果；少于10%的高复杂度问题(场上手牌总数>20张)需要约**10G内存**，于**1分钟**左右得到结果。  
Most problems will be solved within 2 secs taking less than 1G RAM; problems with high complexity(odds < 10%, total cards > 20) will take about 10G RAM and be solved within 1 min.

## 使用方法
How to use

1. 提供Windows平台下x64版本已编译完成的[可执行文件下载](https://github.com/Whotakesmyname/ChinesePokerGame/releases)
2. 自行编译，**引用boost库头文件**

运行可执行文件`ChinesePokerGame.exe`即可

Download the [release for Windows_x64](https://github.com/Whotakesmyname/ChinesePokerGame/releases) or build your own. **Note: Require BOOST Headers**
