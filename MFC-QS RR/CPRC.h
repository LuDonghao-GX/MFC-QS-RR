#pragma once

#include"CPCB.h"
#include <fstream>


// ���н��̶���
queue<PCB*> allPCBQu;
// �����ȴ�����
queue<PCB*> readyQu;
// ����ȴ�����
queue<PCB*> outputQu;
// ����ȴ�����
queue<PCB*> inputQu;
// �����ȴ�����
queue<PCB*> otherQu;

// ���ö���
queue<PCB*> standbyQu;

// ��ǰ���е�PCB
PCB* currentPCB;
// �����־�ļ�ָ��
ofstream outfile;

// CString => string
string c2s(CString str) {
	return CT2A(str.GetString());
}

// ������־�ļ�
void createLogFile() {
	CString logFilePath = _T("log\\");
	CString logFileName = _T("log ");

	// ʹ��CTime��ȡ��ǰʱ��
	CTime time = CTime::GetCurrentTime();
	CString timeT = time.Format(_T("%Y-%m-%d %H-%M-%S"));
	logFileName += timeT;

	// ����ļ���չ��
	logFileName += _T(".txt");

	// �����ļ�
	outfile.open((LPCTSTR)logFilePath + logFileName, ios::out | ios::app);
	if (outfile.is_open()) {
		// �ļ������ɹ�������д������
		outfile << c2s(timeT) << "\t��־�ļ������ɹ���" << endl;
	}
	else {
		// �ļ�����ʧ�ܣ�����������Ϣ
		AfxMessageBox(_T("�޷�������־�ļ���"), MB_ICONERROR);
		return;
	}
}


// ��������PCB����Ľ�����д��ָ��ID�Ŀؼ�
void q2e(queue<PCB*> qu, int nID) {
	// ���������ڶԻ�����ʹ�ã���ȡ�Ի����ָ��
	CWnd* pDlg = AfxGetApp()->GetMainWnd();

	// ���ݿؼ�ID��ȡ�ؼ�ָ��
	CEdit* pEditCtrl = (CEdit*)pDlg->GetDlgItem(nID);
	if (pEditCtrl != nullptr) {
		// ׼��Ҫд����ı�
		CString strText;

		// �������У���ȡÿ��PCB����Ľ�����
		queue<PCB*> temp = qu;
		while (!temp.empty()) {
			strText += CString(temp.front()->getPName().c_str()); // ��stringת��ΪCString
			strText += _T("\r\n"); // ��ӻ��з�
			temp.pop(); // �Ƴ�����ͷ����Ԫ��

		}

		// ���ı����õ��ؼ���
		pEditCtrl->SetWindowText(strText);
	}
}

// �������־�ļ�
void outLog(queue<PCB*>qu, string quName) {
	queue<PCB*> temp = qu;
	string strText;
	outfile << quName << "��";
	while (!temp.empty()) {
		outfile << temp.front()->getPName()/* <<"("<<temp.front()->getNextI()->getCName() << ")"*/<<"  ";
		temp.pop(); // �Ƴ�����ͷ����Ԫ��
	}
	outfile << endl;
}

// ��ն���
void clear(queue<PCB*>& q) {
	queue<PCB*> empty;
	swap(empty, q);
}

// �뱸�ö��н���
void exchange(queue<PCB*>& qu) {
	swap(qu, standbyQu);
	clear(standbyQu);
}

void test(queue<PCB*>qu, string quName) {
	queue<PCB*> temp = qu;
	string strText;
	cout << quName << "��";
	while (!temp.empty()) {
		cout << temp.front()->getPName() << "(" << temp.front()->getNextI()->getCName() << ")  ";
		temp.pop(); // �Ƴ�����ͷ����Ԫ��
	}
	cout << endl;
}
