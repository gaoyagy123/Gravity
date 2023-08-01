// MANIPULATE.cpp: 实现文件
//

#include "pch.h"
#include "Gravity.h"
#include "GravityDlg.h"
#include "MANIPULATE.h"


// CMANIPULATE 对话框

IMPLEMENT_DYNAMIC(CMANIPULATE, CDialogEx)

CMANIPULATE::CMANIPULATE(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONTROL, pParent)
	, mass(5965)
	, hspeed(0)
	, vspeed(0)
	, rc((long)RGB(255, 255, 255))
	, mTime(1000)
	, dosage(5)
	, px(1600)
	, py(900)
	, pMass(0)
	, phorizon(0)
	, pverticality(0)
	, phg(0)
	, pvg(0)
	, prc(0)
	, pdestroy(FALSE)
{
	Gdlg = (CGravityDlg*)pParent;
}

CMANIPULATE::~CMANIPULATE()
{
}

void CMANIPULATE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mass);
	DDX_Text(pDX, IDC_EDIT2, hspeed);
	DDX_Text(pDX, IDC_EDIT3, vspeed);
	DDX_Text(pDX, IDC_EDIT4, rc);
	DDX_Text(pDX, IDC_EDIT5, mTime);
	DDX_Text(pDX, IDC_EDIT8, dosage);
	DDX_Text(pDX, IDC_EDIT6, px);
	DDX_Text(pDX, IDC_EDIT7, py);
	DDX_Control(pDX, IDC_LIST1, mlist);
	DDX_Text(pDX, IDC_EDIT9, pMass);
	DDX_Text(pDX, IDC_EDIT10, phorizon);
	DDX_Text(pDX, IDC_EDIT11, pverticality);
	DDX_Text(pDX, IDC_EDIT12, phg);
	DDX_Text(pDX, IDC_EDIT13, pvg);
	DDX_Text(pDX, IDC_EDIT14, prc);
	DDX_Check(pDX, IDC_CHECK1, pdestroy);
}


BEGIN_MESSAGE_MAP(CMANIPULATE, CDialogEx)
	ON_EN_SETFOCUS(IDC_EDIT4, &CMANIPULATE::OnSetfocusEdit4)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, &CMANIPULATE::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMANIPULATE::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CMANIPULATE::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CMANIPULATE::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_EDIT2, &CMANIPULATE::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CMANIPULATE::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT5, &CMANIPULATE::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT1, &CMANIPULATE::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT4, &CMANIPULATE::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_BUTTON6, &CMANIPULATE::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMANIPULATE::OnBnClickedButton7)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT14, &CMANIPULATE::OnEnChangeEdit14)
	ON_BN_SETFOCUS(IDC_BUTTON14, &CMANIPULATE::OnSetfocusButton14)
	ON_EN_SETFOCUS(IDC_EDIT14, &CMANIPULATE::OnSetfocusEdit14)
	ON_BN_CLICKED(IDC_CHECK1, &CMANIPULATE::OnClickedCheck1)
	ON_EN_CHANGE(IDC_EDIT9, &CMANIPULATE::OnEnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT10, &CMANIPULATE::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT11, &CMANIPULATE::OnEnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT12, &CMANIPULATE::OnEnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT13, &CMANIPULATE::OnEnChangeEdit13)
	ON_BN_CLICKED(IDC_BUTTON9, &CMANIPULATE::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON8, &CMANIPULATE::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON10, &CMANIPULATE::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CMANIPULATE::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CMANIPULATE::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CMANIPULATE::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CMANIPULATE::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CMANIPULATE::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CMANIPULATE::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &CMANIPULATE::OnBnClickedButton17)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMANIPULATE::OnLbnSelchangeList1)
	ON_EN_CHANGE(IDC_EDIT8, &CMANIPULATE::OnEnChangeEdit8)
	ON_BN_CLICKED(IDC_BUTTON18, &CMANIPULATE::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON20, &CMANIPULATE::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON19, &CMANIPULATE::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON21, &CMANIPULATE::OnBnClickedButton21)
END_MESSAGE_MAP()


// CMANIPULATE 消息处理程序


BOOL CMANIPULATE::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetTimer(1, 300, 0);

	return TRUE;
}


void CMANIPULATE::OnSetfocusEdit4()
{
	SetFocus();
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		rc = (long)dlg.GetColor();
		UpdateData(FALSE);
	}
}


void CMANIPULATE::OnPaint()
{
	CPaintDC dc(this);
}


void CMANIPULATE::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (mlist.m_hWnd == NULL)
		return;
	CRect Re;
	mlist.GetWindowRect(&Re);
	CRect sRe;
	GetClientRect(&sRe);
	ScreenToClient(&Re);
	Re.bottom = sRe.bottom;
	mlist.MoveWindow(&Re);
}


void CMANIPULATE::OnBnClickedButton1()
{
	mass = 5965;
	hspeed = 0;
	vspeed = 0;
	rc = 16776960;
	UpdateData(FALSE);
	CManifestationStatic& mStatic = Gdlg->m_pic;
	mStatic.PlanetMass = mass;
	mStatic.Horizon = hspeed;
	mStatic.Verticality = vspeed;
	mStatic.rc = rc;
}


void CMANIPULATE::OnBnClickedButton2()
{
	mass = 73.49;
	hspeed = 0;
	vspeed = 0;
	rc = 4227327;
	UpdateData(FALSE);
	CManifestationStatic& mStatic = Gdlg->m_pic;

	mStatic.PlanetMass = mass;
	mStatic.Horizon = hspeed;
	mStatic.Verticality = vspeed;
	mStatic.rc = rc;
}
void CMANIPULATE::OnBnClickedButton5()
{
	UpdateData();

	CManifestationStatic& mStatic = Gdlg->m_pic;
	mStatic.Clear = true;
	mStatic.threadClear = true;
	mStatic.Dosage = dosage;
	mStatic.px = px;
	mStatic.py = py;
	mStatic.Init();
	Gdlg->InitInterFace();
}


void CMANIPULATE::OnBnClickedButton4()
{
	CManifestationStatic& mStatic = Gdlg->m_pic;
	mStatic.Clear = true;
	mStatic.threadClear = true;
}


void CMANIPULATE::OnEnChangeEdit2()
{
	CString str;
	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	if (str.IsEmpty())
	{
		hspeed = 0;
		UpdateData(FALSE);
	}
	UpdateData();
	CManifestationStatic& mStatic = Gdlg->m_pic;

	mStatic.Horizon = hspeed;

}


void CMANIPULATE::OnEnChangeEdit3()
{
	CString str;
	GetDlgItem(IDC_EDIT3)->GetWindowText(str);
	if (str.IsEmpty())
	{
		vspeed = 0;
		UpdateData(FALSE);
	}
	UpdateData();
	CManifestationStatic& mStatic = Gdlg->m_pic;

	mStatic.Verticality = vspeed;

}


void CMANIPULATE::OnEnChangeEdit5()
{
	CString str;
	GetDlgItem(IDC_EDIT5)->GetWindowText(str);
	if (str.IsEmpty())
	{
		mTime = 1000;
		UpdateData(FALSE);
	}
	UpdateData();
	if (mTime < 1)
		mTime = 1;
	CManifestationStatic& mStatic = Gdlg->m_pic;

	mStatic.ControlTime = mTime;
}


void CMANIPULATE::OnEnChangeEdit1()
{
	UpdateData();
	CManifestationStatic& mStatic = Gdlg->m_pic;

	mStatic.PlanetMass = mass;
}


void CMANIPULATE::OnEnChangeEdit4()
{
	UpdateData();
	CManifestationStatic& mStatic = Gdlg->m_pic;

	mStatic.rc = rc;
}


void CMANIPULATE::OnBnClickedButton6()
{
	UpdateData();
	int d = mTime / 10;
	if (d == 0)
		d = 1;
	mTime -= d;
	if (mTime <= 0)
		mTime = 1;
	UpdateData(FALSE);
	CManifestationStatic& mStatic = Gdlg->m_pic;

	mStatic.ControlTime = mTime;
}

Particle CMANIPULATE::SearchParticle(vector<Particle>& m)
{
	UINT iSize = m.size();
	for (UINT i = 0; i < iSize; ++i)
	{
		Particle& p = m[i];
		if (p.ID == pID)
			return p;
	}
	pID = 0;
	Particle e;
	return e;
}
void CMANIPULATE::OnBnClickedButton7()
{
	UpdateData();
	mTime += 100;
	UpdateData(FALSE);
	CManifestationStatic& mStatic = Gdlg->m_pic;
	mStatic.ControlTime = mTime;
}


void CMANIPULATE::OnTimer(UINT_PTR nIDEvent)
{
	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle& p = SearchParticle(mStatic.Masses);
	if (p.ID > 0)
	{
		pMass = p.GM / G;
		phorizon = p.Horizon;
		pverticality = p.Verticality;
		phg = p.hg;
		pvg = p.vg;
		prc = p.rc;
		pID = p.ID;
		UpdateData(FALSE);
	}
	else
	{
		GetDlgItem(IDC_EDIT9)->SetWindowText("0");
		GetDlgItem(IDC_EDIT10)->SetWindowText("0");
		GetDlgItem(IDC_EDIT11)->SetWindowText("0");
		GetDlgItem(IDC_EDIT12)->SetWindowText("0");
		GetDlgItem(IDC_EDIT13)->SetWindowText("0");
		GetDlgItem(IDC_EDIT14)->SetWindowText("0");
		CheckDlgButton(IDC_CHECK1, 0);
	}

	if (Masses.size() == mStatic.Masses.size())
		return;
	mlist.ResetContent();
	Masses = mStatic.Masses;
	UINT iSize = Masses.size();
	for (UINT i = 0; i < iSize; ++i)
	{
		CString str;
		str.Format("%d", i);
		mlist.AddString(str);
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CMANIPULATE::OnClickedCheck1()
{
	UpdateData();
	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.destroy = pdestroy;
	mStatic.Modified[p.ID] = p;
}


void CMANIPULATE::OnEnChangeEdit9()
{
	CString str;
	GetDlgItem(IDC_EDIT9)->GetWindowText(str);
	if (str.IsEmpty())
	{
		pMass = 0;
		UpdateData(FALSE);
	}
	UpdateData();
	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.GM = pMass * G;
	mStatic.Modified[p.ID] = p;
}


void CMANIPULATE::OnEnChangeEdit10()
{
	CString str;
	GetDlgItem(IDC_EDIT10)->GetWindowText(str);
	if (str.IsEmpty())
	{
		phorizon = 0;
		UpdateData(FALSE);
	}
	UpdateData();
	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.Horizon = phorizon;
	mStatic.Modified[p.ID] = p;
}


void CMANIPULATE::OnEnChangeEdit11()
{
	CString str;
	GetDlgItem(IDC_EDIT11)->GetWindowText(str);
	if (str.IsEmpty())
	{
		pverticality = 0;
		UpdateData(FALSE);
	}
	UpdateData();
	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.Verticality = pverticality;
	mStatic.Modified[p.ID] = p;
}


void CMANIPULATE::OnEnChangeEdit12()
{
	CString str;
	GetDlgItem(IDC_EDIT12)->GetWindowText(str);
	if (str.IsEmpty())
	{
		phg = 0;
		UpdateData(FALSE);
	}
	UpdateData();
	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.hg = phg;
	mStatic.Modified[p.ID] = p;
}


void CMANIPULATE::OnEnChangeEdit13()
{
	CString str;
	GetDlgItem(IDC_EDIT13)->GetWindowText(str);
	if (str.IsEmpty())
	{
		pvg = 0;
		UpdateData(FALSE);
	}
	UpdateData();
	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.vg = pvg;
	mStatic.Modified[p.ID] = p;
}

void CMANIPULATE::OnEnChangeEdit14()
{

}


void CMANIPULATE::OnSetfocusButton14()
{

}


void CMANIPULATE::OnBnClickedButton8()
{
	if (pID == 0)
		return;
	UpdateData();
	double d = pMass / 10;
	if (d == 0)
		d = 1;
	pMass += d;

	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.GM = pMass * G;
	mStatic.Modified[p.ID] = p;
}


void CMANIPULATE::OnBnClickedButton9()
{
	if (pID == 0)
		return;
	UpdateData();
	double d = pMass / 10;
	if (d == 0)
		d = 1;
	pMass -= d;
	UpdateData(FALSE);
	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.GM = pMass * G;
	mStatic.Modified[p.ID] = p;
}


void CMANIPULATE::OnBnClickedButton10()
{
	if (pID == 0)
		return;
	UpdateData();
	double d = phorizon / 10;
	if (d == 0)
		d = 1;
	phorizon += d;

	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.Horizon = phorizon;
	mStatic.Modified[p.ID] = p;
}


void CMANIPULATE::OnBnClickedButton11()
{
	if (pID == 0)
		return;
	UpdateData();
	double d = phorizon / 10;
	if (d == 0)
		d = 1;
	phorizon -= d;

	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.Horizon = phorizon;
	mStatic.Modified[p.ID] = p;
}


void CMANIPULATE::OnBnClickedButton12()
{
	if (pID == 0)
		return;
	UpdateData();
	double d = pverticality / 10;
	if (d == 0)
		d = 1;
	pverticality += d;

	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.Verticality = pverticality;
	mStatic.Modified[p.ID] = p;
}


void CMANIPULATE::OnBnClickedButton13()
{
	if (pID == 0)
		return;
	UpdateData();
	double d = pverticality / 10;
	if (d == 0)
		d = 1;
	pverticality -= d;

	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.Verticality = pverticality;
	mStatic.Modified[p.ID] = p;
}


void CMANIPULATE::OnBnClickedButton14()
{
	if (pID == 0)
		return;
	UpdateData();
	double d = phg / 10;
	if (d == 0)
		d = 1;
	phg += d;

	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.hg = phg;
	mStatic.Modified[p.ID] = p;
}

void CMANIPULATE::OnBnClickedButton15()
{
	if (pID == 0)
		return;
	UpdateData();
	double d = phg / 10;
	if (d == 0)
		d = 1;
	phg -= d;

	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.hg = phg;
	mStatic.Modified[p.ID] = p;
}

void CMANIPULATE::OnBnClickedButton16()
{
	if (pID == 0)
		return;
	UpdateData();
	double d = pvg / 10;
	if (d == 0)
		d = 1;
	pvg += d;

	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.vg = pvg;
	mStatic.Modified[p.ID] = p;
}

void CMANIPULATE::OnBnClickedButton17()
{
	if (pID == 0)
		return;
	UpdateData();
	double d = pvg / 10;
	if (d == 0)
		d = 1;
	pvg -= d;

	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.vg = pvg;
	mStatic.Modified[p.ID] = p;
}


void CMANIPULATE::OnSetfocusEdit14()
{
	SetFocus();
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		prc = (long)dlg.GetColor();
		UpdateData(FALSE);
		UpdateData();
		CManifestationStatic& mStatic = Gdlg->m_pic;
		Particle &p = SearchParticle(mStatic.Masses);
		if (p.ID == 0)
			return;
		p.rc = prc;
		mStatic.Modified[p.ID] = p;
	}
}

void CMANIPULATE::OnLbnSelchangeList1()
{
	int sel = mlist.GetCurSel();
	if (sel < 0)
		return;
	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle& p = mStatic.Masses[sel];
	pMass = p.GM / G;
	phorizon = p.Horizon;
	pverticality = p.Verticality;
	phg = p.hg;
	pvg = p.vg;
	prc = p.rc;
	pID = p.ID;
	pdestroy = FALSE;
	UpdateData(FALSE);

	//UINT iSize = mStatic.Masses.size();
	//for (UINT i = 0; i < iSize; ++i)
	//{
	//	Particle& mp = mStatic.Masses[i];
	//	if (mp.Selected)
	//	{
	//		if (mp.ID == pID)
	//			continue;
	//		mp.Selected = false;
	//		mStatic.Modified[mp.ID] = mp;
	//		break;
	//	}
	//}
	p.Selected = true;
	mStatic.Modified[p.ID] = p;
}


void CMANIPULATE::OnEnChangeEdit8()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMANIPULATE::OnBnClickedButton18()
{
	if (pID == 0)
		return;
	UpdateData();
	double d = phorizon / 10;
	if (d == 0)
		d = 1;
	phorizon -= d;

	d = pverticality / 10;
	if (d == 0)
		d = 1;
	pverticality -= d;

	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.Horizon = phorizon;
	p.Verticality = pverticality;
	mStatic.Modified[p.ID] = p;
}


void CMANIPULATE::OnBnClickedButton20()
{
	if (pID == 0)
		return;
	UpdateData();
	double d = phorizon / 10;
	if (d == 0)
		d = 1;
	phorizon += d;

	d = pverticality / 10;
	if (d == 0)
		d = 1;
	pverticality += d;

	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.Horizon = phorizon;
	p.Verticality = pverticality;
	mStatic.Modified[p.ID] = p;
}


void CMANIPULATE::OnBnClickedButton19()
{
	if (pID == 0)
		return;
	UpdateData();
	double d = phg / 10;
	if (d == 0)
		d = 1;
	phg -= d;

	d = pvg / 10;
	if (d == 0)
		d = 1;
	pvg -= d;

	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.hg = phg;
	p.vg = pvg;
	mStatic.Modified[p.ID] = p;
}


void CMANIPULATE::OnBnClickedButton21()
{
	if (pID == 0)
		return;
	UpdateData();
	double d = phg / 10;
	if (d == 0)
		d = 1;
	phg += d;

	d = pvg / 10;
	if (d == 0)
		d = 1;
	pvg += d;

	CManifestationStatic& mStatic = Gdlg->m_pic;
	Particle &p = SearchParticle(mStatic.Masses);
	if (p.ID == 0)
		return;
	p.hg = phg;
	p.vg = pvg;
	mStatic.Modified[p.ID] = p;
}
