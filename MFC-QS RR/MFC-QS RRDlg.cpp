
// MFC-QS RRDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC-QS RR.h"
#include "MFC-QS RRDlg.h"
#include "afxdialogex.h"

#include "CPRC.h"
#include "afxmt.h"

#define TIMERID 8

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCQSRRDlg 对话框



CMFCQSRRDlg::CMFCQSRRDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCQS_RR_DIALOG, pParent)
	, currentPCBnum(0)
	, totalPCBnum(0)
	, timeSlice(0)
	, schedulingTimes(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCQSRRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_current, currentPCBnum);
	DDX_Text(pDX, IDC_EDIT_total, totalPCBnum);
	DDX_Text(pDX, IDC_EDIT_this, thisPCB);
	DDX_Text(pDX, IDC_EDIT_slice, timeSlice);
}

BEGIN_MESSAGE_MAP(CMFCQSRRDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_open, &CMFCQSRRDlg::OnBnClickedButtonopen)
	ON_BN_CLICKED(IDC_BUTTON_start, &CMFCQSRRDlg::OnBnClickedButtonstart)
	ON_BN_CLICKED(IDC_BUTTON_suspend, &CMFCQSRRDlg::OnBnClickedButtonsuspend)
	ON_BN_CLICKED(IDC_BUTTON_reset, &CMFCQSRRDlg::OnBnClickedButtonreset)

	ON_WM_TIMER()

END_MESSAGE_MAP()


// CMFCQSRRDlg 消息处理程序

BOOL CMFCQSRRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetTimer(TIMERID, timeSlice, 0);	// 设置定时器，时间片大小为定时器调用时间间隔，1000为1秒，

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCQSRRDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCQSRRDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCQSRRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCQSRRDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (startF && currentPCBnum > 0) {

		//处理三个等待队列的PCB
		runInput();
		runOutput();
		runOther();


		// 处理当前运行进程
		if (currentPCB != NULL) {
			currentPCB->runInstruction();
			InstructionType type = currentPCB->getNextI()->getType();  //获取当前pcb的第一条指令的类型

			switch (type)
			{
			default:
				break;
			case COMPUTE:
				readyQu.push(currentPCB);
				break;
			case INPUT1:
				inputQu.push(currentPCB);
				break;
			case OUTPUT:
				outputQu.push(currentPCB);
				break;
			case WAIT:
				otherQu.push(currentPCB);
				break;
			case HALT:
				delete currentPCB;
				currentPCBnum--;
				break;
			}

		}

		// 处理就绪队列
		runReady();


		if (currentPCB == NULL) {
			thisPCB = _T("NONE");
		}
		else {
			thisPCB = currentPCB->getPName().c_str();
		}

		// 输出至控件
		q2e(readyQu, IDC_EDIT_CONTENT);
		q2e(inputQu, IDC_EDIT_CONTENT2);
		q2e(outputQu, IDC_EDIT_CONTENT3);
		q2e(otherQu, IDC_EDIT_CONTENT4);
		GetDlgItem(IDC_EDIT_this)->SetWindowText(thisPCB);

		CString str;
		str.Format(_T("%d"), currentPCBnum);
		GetDlgItem(IDC_EDIT_current)->SetWindowText(str);


		// 输出至日志
		outfile << "============================ " << schedulingTimes++ << " ============================" << endl;
		outfile << "当前进程数量：" << currentPCBnum << endl;
		outfile << "当前运行进程：" << c2s(thisPCB) << endl;
		outLog(readyQu, "就绪队列");
		outLog(inputQu, "输入等待队列");
		outLog(outputQu, "输出等待队列");
		outLog(otherQu, "其他等待队列");


		if (currentPCBnum <= 0) {
			outfile << endl << "============================ 调度完成 ============================" << endl;

			AfxMessageBox(_T("调度完成！"), MB_OK | MB_ICONINFORMATION);

			
		}
	}
	
}




// 打开文件按钮
void CMFCQSRRDlg::OnBnClickedButtonopen()
{
	// TODO: 在此添加控件通知处理程序代码

	// 创建文件对话框
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, _T("文本文件 (*.txt)|*.txt|所有文件 (*.*)|*.*||"), this);

	// 显示文件对话框
	if (fileDlg.DoModal() == IDOK)
	{

		// 获取用户选择的文件路径
		CString FilePath = fileDlg.GetPathName();

		// 创建日志
		createLogFile();

		outfile << "开始读取模拟进程文件：" << c2s(FilePath) << endl;

		// 打开文件并读取内容
		CStdioFile file(FilePath, CFile::modeRead);
		CString cstrContent;
		string data;

		PCB* currentPCB = nullptr;// 当前进程
		instruction* currentInstruction = nullptr;// 当前指令
		instruction* lastInstruction = nullptr;// 最后一条指令

		// 处理文件内容
		while (file.ReadString(cstrContent))
		{
			data = c2s(cstrContent);// CString => string

			if (data[0] == 'P') {
				// 创建新的PCB
				PCB* newPCB = new PCB();
				newPCB->setPName(data);
				newPCB->setPID(stoi(data.substr(1)));
				currentPCB = newPCB;

				totalPCBnum++;// 计算PCB总数
				currentPCBnum++;// 计算当前PCB数

				allPCBQu.push(currentPCB);// 将pcb装入队列中

				currentInstruction = nullptr;
				lastInstruction = nullptr;
			}
			else {
				// 创建新的instruction
				instruction* newInstruction = new instruction();
				newInstruction->setCName(data);
				newInstruction->setType(data[0]);
				newInstruction->setRuntime(stoi(data.substr(1)));

				// 当前指令指针为空，说明进程指针未指向指令
				if (currentInstruction == nullptr) {
					currentPCB->setNextI(newInstruction);
					currentInstruction = newInstruction;
				}
				else {
					lastInstruction->setNext(newInstruction);
				}

				lastInstruction = newInstruction;
				currentPCB->setEndI(lastInstruction);
			}
		}
		file.Close();

		outLog(allPCBQu, "所有进程队列");
		outfile << "进程总数：" << totalPCBnum << endl
			<< "初始化完成！" << endl
			<< "===========================================================" << endl;

	}
}



// 开始调度按钮
void CMFCQSRRDlg::OnBnClickedButtonstart()
{
	// TODO: 在此添加控件通知处理程序代码

	// 检查是否打开文件
	if (allPCBQu.empty()) {
		// 弹出警告对话框
		AfxMessageBox(_T("请打开模拟进程文件!"), MB_ICONWARNING);
		CMFCQSRRDlg::OnBnClickedButtonopen();
	}

	// 获取时间片大小
	CString timeText;
	GetDlgItem(IDC_EDIT_slice)->GetWindowText(timeText);
	timeSlice = _ttoi(timeText);// CString => int
	if (timeSlice == 0) {
		// 弹出警告对话框
		AfxMessageBox(_T("时间片不能为零!"), MB_ICONWARNING);
		return;
	}
	else {
		GetDlgItem(IDC_EDIT_slice)->EnableWindow(false);
	}

	GetDlgItem(IDC_BUTTON_start)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_open)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_suspend)->EnableWindow(true);

	outfile << endl << "设定时间片大小：" << timeSlice << endl
		<< endl << "开始进行调度！" << endl;

	startF = true;// 设置开始标识符


	// 检索所有PCB的第一条指令的类型，
	// 并将指令装入对应的等待队列，
	// 直至检索到 COMPUTE 类型
	queue<PCB*>temp = allPCBQu;
	while (!temp.empty())
	{
		PCB* tempPCB = temp.front();
		int type = tempPCB->getNextI()->getType();  //获取当前PCB的第一条指令的类型
		if (type == COMPUTE) {
			currentPCB = tempPCB;
			temp.pop();
			break;
		}

		switch (type)
		{
		default:
			break;
		case INPUT1:
			inputQu.push(tempPCB);
			temp.pop();
			break;
		case OUTPUT:
			outputQu.push(tempPCB);
			temp.pop();
			break;
		case WAIT:
			otherQu.push(tempPCB);
			temp.pop();
			break;
		case HALT:

			break;
		}

	}

	// 将剩余的PCB装入就绪队列
	while (!temp.empty()) {
		PCB* tempPCB = temp.front();
		readyQu.push(tempPCB);
		temp.pop();
	}

	if (currentPCB == NULL) {
		thisPCB = _T("NONE");
	}
	else {
		thisPCB = currentPCB->getPName().c_str();
	}

	// 输出至控件
	q2e(readyQu, IDC_EDIT_CONTENT);
	q2e(inputQu, IDC_EDIT_CONTENT2);
	q2e(outputQu, IDC_EDIT_CONTENT3);
	q2e(otherQu, IDC_EDIT_CONTENT4);
	GetDlgItem(IDC_EDIT_this)->SetWindowText(thisPCB);

	CString str;
	str.Format(_T("%d"), currentPCBnum);
	GetDlgItem(IDC_EDIT_current)->SetWindowText(str);
	str.Format(_T("%d"), totalPCBnum);
	GetDlgItem(IDC_EDIT_total)->SetWindowText(str);


	// 输出至日志
	outfile << "============================ " << schedulingTimes++ << " ============================" << endl;
	outfile << "当前进程数量：" << currentPCBnum << endl;
	outfile << "当前运行进程：" << c2s(thisPCB) << endl;
	outLog(readyQu, "就绪队列");
	outLog(inputQu, "输入等待队列");
	outLog(outputQu, "输出等待队列");
	outLog(otherQu, "其他等待队列");

}


void CMFCQSRRDlg::OnBnClickedButtonsuspend()
{
	// TODO: 在此添加控件通知处理程序代码

	GetDlgItem(IDC_BUTTON_start)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_suspend)->EnableWindow(false);

	startF = false;
	outfile << endl
		<< "========================= 暂停调度 =========================" << endl
		<< endl;

}


void CMFCQSRRDlg::OnBnClickedButtonreset()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_BUTTON_start)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_open)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_suspend)->EnableWindow(false);

	CString str;

	timeSlice = 0;
	str.Format(_T("%d"), timeSlice);
	GetDlgItem(IDC_EDIT_slice)->SetWindowText(str);
	GetDlgItem(IDC_EDIT_slice)->EnableWindow(true);


	currentPCBnum = 0;
	str.Format(_T("%d"), currentPCBnum);
	GetDlgItem(IDC_EDIT_current)->SetWindowText(str);

	totalPCBnum = 0;
	str.Format(_T("%d"), totalPCBnum);
	GetDlgItem(IDC_EDIT_total)->SetWindowText(str);

	startF = false;

	CString cls = _T("");

	GetDlgItem(IDC_EDIT_this)->SetWindowText(cls);

	GetDlgItem(IDC_EDIT_CONTENT)->SetWindowText(cls);
	GetDlgItem(IDC_EDIT_CONTENT2)->SetWindowText(cls);
	GetDlgItem(IDC_EDIT_CONTENT3)->SetWindowText(cls);
	GetDlgItem(IDC_EDIT_CONTENT4)->SetWindowText(cls);

	clear(readyQu);
	clear(inputQu);
	clear(outputQu);
	clear(otherQu);
	clear(allPCBQu);

	outfile << endl
		<< "========================= 重置 =========================" << endl
		<< endl;

}


// 就绪队列执行
void CMFCQSRRDlg::runReady() {
	if (startF && currentPCBnum > 0) {
		while (!readyQu.empty()) {
			PCB* pCB = readyQu.front();
			InstructionType type = pCB->getNextI()->getType();
			if (type == COMPUTE) {
				currentPCB = pCB;
				readyQu.pop();
				break;
			}
			switch (type)
			{
			default:
				break;
			case INPUT1:
				inputQu.push(pCB);
				readyQu.pop();
				break;
			case OUTPUT:
				outputQu.push(pCB);
				readyQu.pop();
				break;
			case WAIT:
				otherQu.push(pCB);
				readyQu.pop();
				break;
			case HALT:
				pCB = NULL;
				currentPCBnum--;
				readyQu.pop();
				break;
			}
		}
	}
}
// 输入队列执行
void CMFCQSRRDlg::runInput() {

	int n = inputQu.size();
	for (int i = 0; i < n; i++) {
		PCB* pcb = inputQu.front();
		pcb->runInstruction();
		InstructionType type = pcb->getNextI()->getType();  //获取当前pcb的第一条指令的类型

		switch (type)
		{
		default:
			break;
		case COMPUTE:
			readyQu.push(pcb);
			break;
		case INPUT1:
			inputQu.push(pcb);
			break;
		case OUTPUT:
			outputQu.push(pcb);
			break;
		case WAIT:
			otherQu.push(pcb);
			break;
		case HALT:
			delete pcb;
			currentPCBnum--;
			break;
		}

		//outfile << endl << "===========test==============" << endl;
		//outfile << pcb->getPName() << " " << pcb->getRunTime() << endl;
		//outLog(readyQu, "就绪队列");
		//outLog(inputQu, "输入等待队列");
		//outLog(outputQu, "输出等待队列");
		//outLog(otherQu, "其他等待队列");
		//outfile << endl << "============test=============" << endl;

		inputQu.pop();

	}
	//exchange(inputQu);
}

// 输出队列执行
void CMFCQSRRDlg::runOutput() {

	int n = outputQu.size();
	for (int i = 0; i < n; i++) {
		PCB* pcb = outputQu.front();
		pcb->runInstruction();
		InstructionType type = pcb->getNextI()->getType();  //获取当前pcb的第一条指令的类型

		switch (type)
		{
		default:
			break;
		case COMPUTE:
			readyQu.push(pcb);
			break;
		case INPUT1:
			inputQu.push(pcb);
			break;
		case OUTPUT:
			outputQu.push(pcb);
			break;
		case WAIT:
			otherQu.push(pcb);
			break;
		case HALT:
			delete pcb;
			currentPCBnum--;
			break;
		}

		outputQu.pop();
	}

}

// 其他队列执行
void CMFCQSRRDlg::runOther() {

	int n = otherQu.size();
	for (int i = 0; i < n; i++) {
		PCB* pcb = otherQu.front();
		pcb->runInstruction();
		InstructionType type = pcb->getNextI()->getType();  //获取当前pcb的第一条指令的类型

		switch (type)
		{
		default:
			break;
		case COMPUTE:
			readyQu.push(pcb);
			break;
		case INPUT1:
			inputQu.push(pcb);
			break;
		case OUTPUT:
			outputQu.push(pcb);
			break;
		case WAIT:
			otherQu.push(pcb);
			break;
		case HALT:
			delete pcb;
			currentPCBnum--;
			break;
		}

		otherQu.pop();
	}
}