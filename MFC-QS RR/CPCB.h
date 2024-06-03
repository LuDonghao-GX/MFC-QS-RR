#pragma once

#include"CInstruction.h"
#include <queue>



class PCB
{
public:
    PCB(); // ���캯��
    ~PCB(); // ��������

    // ���ú�����Setters��
    void setPID(int id) { pID = id; }
    void setPName(string name) { pName = name; }
    void setRunTime(int time) { runTime = time; }
    void setNextI(instruction* insn) { runTime = insn->getRunTime(); nextI = insn; }
    void setEndI(instruction* insn) { endI = insn; }

    void runInstruction();
    void deleteInstruction();

    // ��ȡ������Getters��
    int getPID() const { return pID; } // ��ȡ���̱�ʶ��
    string getPName()const { return pName; }
    int getRunTime() const { return runTime; } // ��ȡ��ǰ����ָ���Ҫ��ʱ��
    instruction* getNextI() const { return nextI; } // ��ȡָ���һ��ָ���ָ��
    instruction* getEndI() const { return endI; } // ��ȡָ�����һ��ָ���ָ��

private:
    int pID; // ���̱�ʶ��
    string pName;// ������
    int runTime; // ��ǰ����ָ�����л���Ҫ��ʱ��
    instruction* nextI; // ָ�򱾽��̵�ָ�����У����Ա��ĵ�һ��ָ��
    instruction* endI; // ָ�򱾽��̵�ָ�����У����Ա������һ��ָ��
};

PCB::PCB()
{
    // ���캯����ʵ�֣����Գ�ʼ����Ա����
    pID = 0; // Ĭ�Ͻ��̱�ʶ��Ϊ0
    pName = "";
    runTime = 0; // Ĭ������ʱ��Ϊ0
    nextI = nullptr; // ��ʼ��ʱû�е�һ��ָ��
    endI = nullptr; // ��ʼ��ʱû�����һ��ָ��
}

PCB::~PCB()
{
    // ����������ʵ�֣������ͷ���Դ
    // ���nextI��endIָ���ָ�����ڶ��Ϸ���ģ�����Ҫ�������ͷ�
    // ������������У�nextI��endIֻ��һ��ָ�룬����Ҫ�ͷ�
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