#pragma once
#include "resource.h"

// CMANIPULATE 对话框
class CGravityDlg;
class CMANIPULATE : public CDialogEx
{
	DECLARE_DYNAMIC(CMANIPULATE)

public:
	CMANIPULATE(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMANIPULATE();
	CGravityDlg* Gdlg = NULL;
// 对话框数据
	enum { IDD = IDD_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	Particle SearchParticle(vector<Particle>& m);
	virtual BOOL OnInitDialog();
	afx_msg void OnSetfocusEdit4();
	double mass;
	double hspeed;
	double vspeed;
	vector<Particle> Masses;
	long rc;
	int mTime;
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	double dosage;
	UINT px;
	UINT py;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	CListBox mlist;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeEdit14();
	afx_msg void OnSetfocusButton14();
	afx_msg void OnSetfocusEdit14();
	double pMass;
	double phorizon;
	double pverticality;
	double phg;
	double pvg;
	long prc;
	DWORD pID = 0;
	afx_msg void OnClickedCheck1();
	afx_msg void OnEnChangeEdit9();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit11();
	afx_msg void OnEnChangeEdit12();
	afx_msg void OnEnChangeEdit13();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnLbnSelchangeList1();
	BOOL pdestroy;
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton20();
	afx_msg void OnBnClickedButton19();
	afx_msg void OnBnClickedButton21();
};
