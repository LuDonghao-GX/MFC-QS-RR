# 操作系统原理课程设计

#### 描述

题目：时间片轮转调度算法的模拟实现。

要求：充分理解时间片轮转调度算法原理的基础上，编写一个可视化的算法模拟程序。

#### 运行

1. 使用`vs`运行

- 在`MFC-OS RR\`目录下创建`log`文件夹
- 使用`VS`打开`MFC-QS RR.sln`文件，点击开始执行
- 模拟进程文件为`prc.txt`
- 时间片大小为定时器调用时间间隔，1000为1秒
- 运行后日志文件在`MFC-OS RR\log\`目录下



2. 使用`exe`文件运行

- `x64\Release\`目录下存在可直接使用的`.exe`文件
- 将该`exe`文件放在任意位置
- 在`exe`文件所在的目录下创建`log`文件夹
- 模拟进程文件为`prc.txt`
- 日志文件在`log\`目录下



#### 未知bug

当调度执行到4121次时，会出现卡死窗口重启现象，原因未知
