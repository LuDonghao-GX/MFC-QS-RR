#pragma once

#include <iostream>
#include <string>
using namespace std;



// �����������ö��
enum InstructionType {
    COMPUTE = 'C', // C��CPU����
    INPUT1 = 'I',    // I������
    OUTPUT = 'O',   // O�����
    WAIT = 'W',     // W���ȴ�
    HALT = 'H',      // H�����̽���
    INIT = 'T'		//T: ��ʼ��
};


class instruction
{
    friend class PCB; // ����pcb��Ϊ��Ԫ�࣬����pcb�����instruction���˽�г�Ա
public:
    instruction(); // ���캯��
    ~instruction(); // ��������

    // ���ú�����Setters��
    
    // ����ָ����
    void setCName(const string& name) { cName = name; } 
    // ���ò�������
    void setType(char t) { type = static_cast<InstructionType>(t); } 
    // ��������ʱ��
    void setRuntime(int time) { runtime = time; } 
    // ������һ��ָ��
    void setNext(instruction* insn) { next = insn; } 
   
    // ��ȡ������Getters��

    // ��ȡ���̱�ʶ��
    string getCName() const { return cName; } 
    // ��ȡ��ǰָ�������
    InstructionType getType() const { return type; };
    // ��ȡ��ǰ����ָ���Ҫ��ʱ��
    int getRunTime() const { return runtime; } 
    // ��ȡ��һ��ָ��
    instruction* getNext() const { return next; } 
  

private:
    string cName; // ָ����
    InstructionType type; // ��������
    int runtime; // ����ʱ�䣨ʱ��Ƭ����
    instruction* next; // ��һ��ָ��
};

instruction::instruction()
{
    // ���캯����ʵ�֣����Գ�ʼ����Ա����
    cName = "";
    type = INIT; // Ĭ��Ϊ��ʼ��ָ��
    runtime = 0;
    next = nullptr; // ��ʼ��ʱû����һ��ָ��
}

instruction::~instruction()
{
    // ����������ʵ�֣������ͷ���Դ
    // ���nextָ���ָ�����ڶ��Ϸ���ģ�����Ҫ�������ͷ�
    // ������������У�nextֻ��һ��ָ�룬����Ҫ�ͷ�
}
