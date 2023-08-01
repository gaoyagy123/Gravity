
// GravityDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Gravity.h"
#include "GravityDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGravityDlg 对话框



CGravityDlg::CGravityDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRAVITY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGravityDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_pic);
}

BEGIN_MESSAGE_MAP(CGravityDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_MOVE()
END_MESSAGE_MAP()


// CGravityDlg 消息处理程序

BOOL CGravityDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_control = new CMANIPULATE(this);
	m_control->Create(CMANIPULATE::IDD);

	InitInterFace();

	m_pic.SetMyParent(this);
	m_pic.ModifyStyle(0xF, SS_NOTIFY);






	ULONG64 idistance = 6371393;
	double distance = idistance;
	double v = 7902;
	double ddv = v;

	int t =30;
	double g0 = (double)39786550 * 10000000 / (idistance * idistance);  //重力加速度
	double hmetre0 = t * v + (g0 * t * t / 2);
	double v0 = v + g0 * t;

	
	double dt = 0.000001;     //时间分成3000000分
	ULONG64 k = t / dt;

	double hmetre3 = 0;
	double gd = 0;
	double hmetre1 = 0;
	ULONG64 i = 0;
	for (i = 0; i < k; ++i)
	{ 
		gd = (double)39786550 * 10000000 / (distance * distance);  //重力加速度
		hmetre1 = dt * ddv + (gd * dt * dt / 2);
		ddv += gd * dt;
		distance -= hmetre1;
		hmetre3 += hmetre1;
	}


	double dv = (ddv - v) / t;
	double dv0 = (v0 - v) / t;

	double dh = hmetre3 - hmetre0;
	double mm = dv / idistance;
	double nn = dh / idistance;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CGravityDlg::InitInterFace()
{
	CRect cRe;
	m_control->GetClientRect(&cRe);
	MoveWindow(0, 0, m_pic.px + cRe.Width(), m_pic.py);
	CRect Re;
	GetClientRect(&Re);
	int px = m_pic.px + cRe.Width() - Re.Width();
	int py = m_pic.py - Re.Height();
	MoveWindow(0, 0, m_pic.px + cRe.Width() + px, m_pic.py + py);
	CenterWindow();
}

void CGravityDlg::OnPaint()
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
HCURSOR CGravityDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGravityDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (m_pic.m_hWnd == NULL)
		return;
	CRect Re;
	GetClientRect(&Re);
	m_pic.MoveWindow(0, 0, m_pic.px, m_pic.py);
	m_pic.InvalidateRect(NULL);
	if (m_control == NULL)
		return;
	if (m_control->m_hWnd == NULL)
		return;
	m_control->GetClientRect(&Re);
	CRect sRe(m_pic.px, 0, m_pic.px + Re.Width(), m_pic.py);
	ClientToScreen(&sRe);
	m_control->MoveWindow(&sRe);
}


void CGravityDlg::OnClose()
{
	m_pic.Working = false;
	for (UINT i = 0; i < m_pic.ThreadT.size(); ++i)
		m_pic.ThreadT[i].join();
	if (m_control)
		delete m_control;
	CDialogEx::OnClose();
}


void CGravityDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	if (m_control == NULL)
		return;
	if (m_control->m_hWnd == NULL)
		return;
	CRect Re;
	m_control->GetClientRect(&Re);
	CRect sRe(m_pic.px, 0, m_pic.px + Re.Width(), m_pic.py);
	ClientToScreen(&sRe);
	m_control->MoveWindow(&sRe);
}
