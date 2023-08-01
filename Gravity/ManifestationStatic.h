
#include <afxwin.h>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define RealEarthMass 5965   //真实数5.965*10^24kg=5965000000000000000000000 除以10^21   如果加入另外的质量，则在kg单位下除以10^21就可以用了
#define RealEarthR 6371393     //米m
#define G 6672.59   //重力常数
#define EarthMass 39786550;  // 6670 * 5965=39786550‬ //*10^7  

extern double Pixel; //米*10   地球地壳半径  637139.3

struct Particle
{
	double GM = EarthMass;
	CPoint Position;
	double Horizon = 0;//  m/s
	double Verticality = 0;
	double hg = 0;
	double vg = 0;
	double hmetre = 0;
	double vmetre = 0;
	COLORREF rc = RGB(255, 255, 255);
	bool destroy = false;
	void setPoint(CPoint& p)
	{
		Position = p;
		hmetre = p.x * Pixel;
		vmetre = p.y * Pixel;
		ID = GetTickCount();
	}
	DWORD ID = 0;
	bool Selected = false;
};
class CGravityDlg;
class CManifestationStatic :public CStatic
{
public:
	CManifestationStatic();
	virtual ~CManifestationStatic();

	DECLARE_MESSAGE_MAP()
public:
	double Dosage = 5;  //设定地球半径的长度相当于多少像素点
	UINT ControlTime = 1000;
	double PlanetMass = RealEarthMass;
	double Horizon = 7900;//  m/s
	double Verticality = 0;
	COLORREF rc = RGB(255, 255, 255);
	void Init()
	{
		Pixel = (double)RealEarthR / Dosage;
	}
public:
	UINT px = 1600, py = 900;
	void SetMyParent(CWnd* pParent);
	void LoadMemBitMap(CDC* dc, CRect& Re);
	void SaveMemBitMap(CDC* dc, CRect& Re);
	bool RefreshMem = true;
	CBitmap* Mem_BitMap = NULL;
	CGravityDlg* Par = NULL;
	CRect memRe;
	vector<thread> ThreadT;
	bool Clear = false, threadClear = false;
	vector<Particle> Masses, add;
	map<int, Particle> clashed;
	map<DWORD, Particle> Modified;
	vector<vector<Particle>> queue_datas_;
	CRITICAL_SECTION cs;
	bool Working = true;
	void GetDif(double t, Particle& p, int index);
	void thread_function();
public:
	void Pic_function();
	void GetSpeed(Particle& p, int index1, const Particle& Target, int index2);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};
