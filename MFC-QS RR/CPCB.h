#pragma once

#include"CInstruction.h"
#include <queue>



class PCB
{
public:
    PCB(); // 构造函数
    ~PCB(); // 析构函数

    // 设置函数（Setters）
    void setPID(int id) { pID = id; }
    void setPName(string name) { pName = name; }
    void setRunTime(int time) { runTime = time; }
    void setNextI(instruction* insn) { runTime = insn->getRunTime(); nextI = insn; }
    void setEndI(instruction* insn) { endI = insn; }

    void runInstruction();
    void deleteInstruction();

    // 获取函数（Getters）
    int getPID() const { return pID; } // 获取进程标识符
    string getPName()const { return pName; }
    int getRunTime() const { return runTime; } // 获取当前运行指令还需要的时间
    instruction* getNextI() const { return nextI; } // 获取指向第一条指令的指针
    instruction* getEndI() const { return endI; } // 获取指向最后一条指令的指针

private:
    int pID; // 进程标识符
    string pName;// 进程名
    int runTime; // 当前运行指令运行还需要的时间
    instruction* nextI; // 指向本进程的指令序列（线性表）的第一条指令
    instruction* endI; // 指向本进程的指令序列（线性表）的最后一条指令
};

PCB::PCB()
{
    // 构造函数的实现，可以初始化成员变量
    pID = 0; // 默认进程标识符为0
    pName = "";
    runTime = 0; // 默认运行时间为0
    nextI = nullptr; // 初始化时没有第一条指令
    endI = nullptr; // 初始化时没有最后一条指令
}

PCB::~PCB()
{
    // 析构函数的实现，可以释放资源
    // 如果nextI和endI指向的指令是在堆上分配的，则需要在这里释放
    // 但在这个例子中，nextI和endI只是一个指针，不需要释放
}

void PCB::runInstruction() {
    runTime--;
    if (runTime == 0) {
        deleteInstruction();
    }
}

void PCB::deleteInstruction() {
    if (nextI != NULL) {
        setNextI(nextI->getNext());
    }
}