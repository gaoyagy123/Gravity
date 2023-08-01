#pragma once
#include "ManifestationStatic.h"
#include "MANIPULATE.h"
// CGravityDlg 对话框
class CGravityDlg : public CDialogEx
{
// 构造
public:
	CGravityDlg(CWnd* pParent = nullptr);	// 标准构造函数
	CMANIPULATE* m_control = NULL;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRAVITY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;


	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void InitInterFace();
	CManifestationStatic m_pic;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnMove(int x, int y);
};
