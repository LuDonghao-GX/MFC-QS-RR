
// MFC-QS RRDlg.h: 头文件
//

#pragma once



// CMFCQSRRDlg 对话框
class CMFCQSRRDlg : public CDialogEx
{
	// 构造
public:
	CMFCQSRRDlg(CWnd* pParent = nullptr);	// 标准构造函数

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCQS_RR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//	CButton t;
	afx_msg void OnBnClickedButtonopen();
	afx_msg void OnBnClickedButtonstart();
	afx_msg void OnBnClickedButtonsuspend();
	afx_msg void OnBnClickedButtonreset();

	// 定时器调用函数
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	// 就绪队列执行
	void runReady();
	// 输入队列执行
	void runInput();
	// 输出队列执行
	void runOutput();
	// 其他队列执行
	void runOther();

	// 当前PCB数
	int currentPCBnum;
	// PCB总数
	int totalPCBnum;
	// 当前运行进程
	CString thisPCB;
	// 时间片大小
	int timeSlice;
	// 开始标识符
	bool startF = false;
	// 调度次数
	int schedulingTimes;



};

