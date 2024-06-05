#pragma once

#include"CPCB.h"
#include <fstream>


// 所有进程队列
queue<PCB*> allPCBQu;
// 就绪等待队列
queue<PCB*> readyQu;
// 输出等待队列
queue<PCB*> outputQu;
// 输入等待队列
queue<PCB*> inputQu;
// 其他等待队列
queue<PCB*> otherQu;

// 备用队列
queue<PCB*> standbyQu;

// 当前运行的PCB
PCB* currentPCB;
// 输出日志文件指针
ofstream outfile;

// CString => string
string c2s(CString str) {
	return CT2A(str.GetString());
}

// 创建日志文件
void createLogFile() {
	CString logFilePath = _T("log\\");
	CString logFileName = _T("log ");

	// 使用CTime获取当前时间
	CTime time = CTime::GetCurrentTime();
	CString timeT = time.Format(_T("%Y-%m-%d %H-%M-%S"));
	logFileName += timeT;

	// 添加文件扩展名
	logFileName += _T(".txt");

	// 创建文件
	outfile.open((LPCTSTR)logFilePath + logFileName, ios::out | ios::app);
	if (outfile.is_open()) {
		// 文件创建成功，可以写入内容
		outfile << c2s(timeT) << "\t日志文件创建成功！" << endl;
	}
	else {
		// 文件创建失败，弹出错误消息
		AfxMessageBox(_T("无法创建日志文件！"), MB_ICONERROR);
		return;
	}
}


// 将队列中PCB对象的进程名写入指定ID的控件
void q2e(queue<PCB*> qu, int nID) {
	// 假设这是在对话框中使用，获取对话框的指针
	CWnd* pDlg = AfxGetApp()->GetMainWnd();

	// 根据控件ID获取控件指针
	CEdit* pEditCtrl = (CEdit*)pDlg->GetDlgItem(nID);
	if (pEditCtrl != nullptr) {
		// 准备要写入的文本
		CString strText;

		// 遍历队列，获取每个PCB对象的进程名
		queue<PCB*> temp = qu;
		while (!temp.empty()) {
			strText += CString(temp.front()->getPName().c_str()); // 将string转换为CString
			strText += _T("\r\n"); // 添加换行符
			temp.pop(); // 移除队列头部的元素

		}

		// 将文本设置到控件中
		pEditCtrl->SetWindowText(strText);
	}
}

// 输出至日志文件
void outLog(queue<PCB*>qu, string quName) {
	queue<PCB*> temp = qu;
	string strText;
	outfile << quName << "：";
	while (!temp.empty()) {
		outfile << temp.front()->getPName()/* <<"("<<temp.front()->getNextI()->getCName() << ")"*/<<"  ";
		temp.pop(); // 移除队列头部的元素
	}
	outfile << endl;
}

// 清空队列
void clear(queue<PCB*>& q) {
	queue<PCB*> empty;
	swap(empty, q);
}

// 与备用队列交换
void exchange(queue<PCB*>& qu) {
	swap(qu, standbyQu);
	clear(standbyQu);
}

void test(queue<PCB*>qu, string quName) {
	queue<PCB*> temp = qu;
	string strText;
	cout << quName << "：";
	while (!temp.empty()) {
		cout << temp.front()->getPName() << "(" << temp.front()->getNextI()->getCName() << ")  ";
		temp.pop(); // 移除队列头部的元素
	}
	cout << endl;
}
