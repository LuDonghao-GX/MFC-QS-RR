#pragma once

#include <iostream>
#include <string>
using namespace std;



// 定义操作命令枚举
enum InstructionType {
    COMPUTE = 'C', // C：CPU计算
    INPUT1 = 'I',    // I：输入
    OUTPUT = 'O',   // O：输出
    WAIT = 'W',     // W：等待
    HALT = 'H',      // H：进程结束
    INIT = 'T'		//T: 初始化
};


class instruction
{
    friend class PCB; // 声明pcb类为友元类，允许pcb类访问instruction类的私有成员
public:
    instruction(); // 构造函数
    ~instruction(); // 析构函数

    // 设置函数（Setters）
    
    // 设置指令名
    void setCName(const string& name) { cName = name; } 
    // 设置操作类型
    void setType(char t) { type = static_cast<InstructionType>(t); } 
    // 设置运行时间
    void setRuntime(int time) { runtime = time; } 
    // 设置下一条指令
    void setNext(instruction* insn) { next = insn; } 
   
    // 获取函数（Getters）

    // 获取进程标识符
    string getCName() const { return cName; } 
    // 获取当前指令的类型
    InstructionType getType() const { return type; };
    // 获取当前运行指令还需要的时间
    int getRunTime() const { return runtime; } 
    // 获取下一条指令
    instruction* getNext() const { return next; } 
  

private:
    string cName; // 指令名
    InstructionType type; // 操作类型
    int runtime; // 运行时间（时间片数）
    instruction* next; // 下一条指令
};

instruction::instruction()
{
    // 构造函数的实现，可以初始化成员变量
    cName = "";
    type = INIT; // 默认为初始化指令
    runtime = 0;
    next = nullptr; // 初始化时没有下一条指令
}

instruction::~instruction()
{
    // 析构函数的实现，可以释放资源
    // 如果next指向的指令是在堆上分配的，则需要在这里释放
    // 但在这个例子中，next只是一个指针，不需要释放
}
