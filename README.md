# Chinese Poker Game Solver  
([中文文档](./README_zh-cn.md) | English version)

It is an Chinese Poker Game solver using MinMax algorithm, and maybe also the fastest one.  
The Chinese Poker Game is also known as 斗地主(Dou Di Zhu).

For more details of the realization, please refer to my blog [Adversarial Search on Chinese Poker Game](https://blog.darkray.cn/tech/algorithm/adversarial-search-on-chinese-poker-game/)

## Environment Requirements

### Test Environment

- CPU: Intel(R) Core(TM) i7-4710MQ CPU @ 2.50GHz
- RAM: DDR3L 24G(8+8+4+4)

Most problems will be solved within 2 secs taking less than 1G RAM; problems with high complexity(odds < 10%, total cards > 20) will take about 10G RAM and be solved within 1 min.

## How to use

Download the [release for Windows_x64](https://github.com/Whotakesmyname/ChinesePokerGame/releases) or build your own.

## How to compile
**C++20 standard is required**  

- Create a new build folder under project root and use cmake to build
- Or use an IDE(like VS Code) and install cmake plugin which will configure your environment automatically for you
