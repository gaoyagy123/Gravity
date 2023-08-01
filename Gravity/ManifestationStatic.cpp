#include "pch.h"
#include "ManifestationStatic.h"
#include "GravityDlg.h"
//确定坐标图四周预留的空白大小
double Pixel= 637139.3; //米*10   地球地壳半径  637139.3

BEGIN_MESSAGE_MAP(CManifestationStatic, CStatic)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

CManifestationStatic::CManifestationStatic()
{
	InitializeCriticalSection(&cs);
	Init();
}

CManifestationStatic::~CManifestationStatic()
{
	if (Mem_BitMap != 0)
	{
		Mem_BitMap->DeleteObject();
		delete Mem_BitMap;
	}
	DeleteCriticalSection(&cs);
}
void CManifestationStatic::SetMyParent(CWnd* pParent)
{
	CRect Re;
	GetClientRect(&Re);
	void (CManifestationStatic:: * fuc)() = &CManifestationStatic::thread_function;
	ThreadT.push_back(thread(fuc, this));
	void (CManifestationStatic:: * fuc2)() = &CManifestationStatic::Pic_function;
	ThreadT.push_back(thread(fuc2, this));
	Par = (CGravityDlg*)pParent;
}

void CManifestationStatic::OnPaint()
{
	CPaintDC dc(this);

	CRect mRe;
	GetClientRect(&mRe);
	COLORREF blackColor = RGB(0, 0, 0);
	CBrush brush(blackColor);
	dc.FillRect(&mRe, &brush);


	if (RefreshMem)
	{
		if (Mem_BitMap != 0)
		{
			Mem_BitMap->DeleteObject();
			delete Mem_BitMap;
		}
		Mem_BitMap = new CBitmap;

		//CDC pDC;
		//pDC.CreateCompatibleDC(&dc);
		//Mem_BitMap->CreateCompatibleBitmap(&dc, memRe.Width(), memRe.Height());
		//CBitmap *oldBitMap = pDC.SelectObject(Mem_BitMap);
		//pDC.BitBlt(0, 0, memRe.Width(), memRe.Height(), &dc, memRe.left, memRe.top, SRCCOPY);
		//pDC.SelectObject(oldBitMap);
		//pDC.DeleteDC();
		Mem_BitMap->CreateCompatibleBitmap(&dc, memRe.Width(), memRe.Height());
		SaveMemBitMap(&dc, memRe);
		RefreshMem = false;
	}
}
void CManifestationStatic::SaveMemBitMap(CDC* dc, CRect& Re)
{
	CDC pDC;
	pDC.CreateCompatibleDC(dc);
//	Mem_BitMap->CreateCompatibleBitmap(dc, memRe.Width(), memRe.Height());
	CBitmap* oldBitMap = pDC.SelectObject(Mem_BitMap);
	pDC.BitBlt(0, 0, memRe.Width(), memRe.Height(), dc, memRe.left, memRe.top, SRCCOPY);
	pDC.SelectObject(oldBitMap);
	pDC.DeleteDC();
}

double DoubleRetained(double p)
{
	CString str;
	str.Format("%.2f", p);
	return atof(str);
}
void CManifestationStatic::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);

	GetClientRect(&memRe);
	RefreshMem = true;
}


void CManifestationStatic::LoadMemBitMap(CDC *dc, CRect &Re)
{
	//刷新背景
	CDC pDc;
	pDc.CreateCompatibleDC(dc);
	CBitmap *oldMap = pDc.SelectObject(Mem_BitMap);
	dc->BitBlt(Re.left, Re.top, Re.Width(), Re.Height(), &pDc, 0, 0, SRCCOPY); //因为线的粗度是2，所以为防止在极端情况下线超界的话所以多刷新2个像素高度
	pDc.SelectObject(oldMap);
	pDc.DeleteDC();
}

void CManifestationStatic::GetSpeed(Particle& p, int index1, const Particle& Target, int index2)  //target里面的值在这个函数里只读，不改变内容
{
	double horizon = Target.hmetre - p.hmetre;
	double verticality = Target.vmetre - p.vmetre;
	double idistance2 = horizon * horizon + verticality * verticality;
	double idistance = sqrt(idistance2);
	LONG r1 = p.GM / EarthMass;
	if (r1 > 5)
		r1 = 5;
	if (r1 > 0)
		--r1;
	LONG r2 = Target.GM / EarthMass;
	if (r2 > 5)
		r2 = 5;
	if (r2 > 0)
		--r2;
	LONG r = r1 + r2;
	if (r == 0)
		r = 1;
	if (idistance < Pixel * r)
	{
		bool has1 = (clashed.find(index1) != clashed.end());
		Particle& p1 = clashed[index1];
		if (p1.destroy)
			return;

		bool has2 = (clashed.find(index2) != clashed.end());
		Particle& p2 = clashed[index2];
		if (p2.destroy)
			return;

		if (!has1)
			p1 = p;
		if (!has2)
			p2 = Target;

		double clashHorizon = Target.GM * Target.Horizon + p.GM * p.Horizon;
		double clashVerticality = Target.GM * Target.Verticality + p.GM * p.Verticality;
		if (Target.GM >= p.GM)
		{
			p2.GM += p.GM;
			p2.Horizon = ((double)clashHorizon) / p2.GM;
			p2.Verticality = ((double)clashVerticality) / p2.GM;
			p1.destroy = true;
		}
		else
		{
			p1.GM += Target.GM;
			p1.Horizon = ((double)clashHorizon) / p1.GM;
			p1.Verticality = ((double)clashVerticality) / p1.GM;
			p2.destroy = true;
		}
		return;
	}

	double g = (double)Target.GM * 10000000 / idistance2;  //重力加速度
	p.hg += (double)(horizon * Target.GM * 10000000) / (idistance2 * idistance);
	p.vg += (double)(verticality * Target.GM * 10000000) / (idistance2 * idistance);
}


void CManifestationStatic::Pic_function()
{
	CDC* dc = GetDC();
	while (Working)
	{
		if (Clear && !threadClear)
		{
			Clear = false;
			RefreshMem = true;
			Invalidate();
			LoadMemBitMap(dc, memRe);
			continue;
		}
	
		vector<Particle> cMasses;
		bool has_data = false;
		EnterCriticalSection(&cs);
		if (!queue_datas_.empty())
		{
			cMasses = queue_datas_.front();
			queue_datas_.clear();
			has_data = true;
		}
		LeaveCriticalSection(&cs);

		if (!has_data)
			continue;
		UINT iSize = cMasses.size();
		if (iSize > 0)
			LoadMemBitMap(dc, memRe);
		for (UINT i = 0; i < iSize; ++i)
		{
			Particle& p = cMasses[i];




			dc->SetPixel(p.Position.x, p.Position.y, p.rc);

			LONG num = p.GM / EarthMass;
			if (num > 5)
				num = 5;
			CPen pen(PS_SOLID, 1, p.rc);
			CPen* OldPen = dc->SelectObject(&pen);
			dc->MoveTo(p.Position);
			dc->AngleArc(p.Position.x, p.Position.y, num, 0, 360);  //这是画了一个360度的圆弧，也可以用Ellipse

			if (p.Selected)
			{
				CString str = "<-";
				CRect Re;
				Re.left = p.Position.x + 10;
				Re.right = Re.left + 15;
				Re.top = p.Position.y - 5;
				Re.bottom = Re.top + 10;
				dc->SetTextColor(RGB(0, 255, 0));
				dc->SetBkColor(RGB(0, 0, 0));
				dc->DrawText(str, &Re, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
			}
			dc->SelectObject(OldPen);
			pen.DeleteObject();

		//	SaveMemBitMap(dc, memRe);
		}
		if (iSize == 0)
			Sleep(1);
	}
}
void CManifestationStatic::thread_function()
{
	while (Working)
	{
		if (threadClear)
		{
			threadClear = false;
			Masses.clear();
			add.clear();
			continue;
		}
		UINT addiSize = add.size();
		for (UINT i = 0; i < addiSize; ++i)
		{
			Masses.push_back(add[i]);
		}
		add.clear();
		
		UINT iSize = Masses.size();
		if (iSize > 0)
		{
			double st = 20000 / ControlTime;
			UINT num = 20000 / iSize;
			double t = st / num;
			UINT index = 0;
			vector<Particle> cMasses = Masses;

			for (index = 0; index < num; ++index)
			{
				iSize = cMasses.size();
				if (iSize == 0)
					break;
				for (UINT i = 0; i < iSize; ++i)
				{
					Particle& p = cMasses[i];
					p.hg = 0;
					p.vg = 0;
					for (UINT k = 0; k < iSize; ++k)
					{
						if (k == i)
							continue;
						GetSpeed(p, i, Masses[k], k);
					}
					p.hmetre += t * p.Horizon + (p.hg * t * t / 2);
					p.vmetre += t * p.Verticality + (p.vg * t * t / 2);
					p.Horizon += p.hg * t;
					p.Verticality += p.vg * t;

					p.Position.x = p.hmetre / Pixel;
					p.Position.y = p.vmetre / Pixel;
				}
				for (map<int, Particle>::iterator it = clashed.begin(); it != clashed.end(); ++it)
				{
					cMasses[it->first] = it->second;
				}
				clashed.clear();
				for (vector<Particle>::iterator it_pos = cMasses.begin(); it_pos != cMasses.end(); )
				{
					Particle& p = *it_pos;
					if (p.destroy)
					{
						it_pos = cMasses.erase(it_pos);
						continue;
					}
					if (!memRe.PtInRect(p.Position))
					{
	/*					if (p.Position.x <= 0)
							p.Position.x = px;
						else if (p.Position.x >= px)
							p.Position.x = 0;

						if (p.Position.y <= 0)
							p.Position.y = py;
						else if (p.Position.y >= py)
							p.Position.y = 0;
						p.hmetre = p.Position.x * Pixel;
						p.vmetre = p.Position.y * Pixel;*/
						it_pos = cMasses.erase(it_pos);
						continue;
					}

					if (Modified.find(p.ID) != Modified.end())
					{
						Particle &mp = Modified[p.ID];
				
						if (mp.Selected)
						{
							for (vector<Particle>::iterator it = cMasses.begin(); it != cMasses.end(); ++it)
							{
								it->Selected = false;
							}
						}
						p = mp;
						Modified.erase(p.ID);

					}
					++it_pos;
				}
				Masses = cMasses;
			}
			EnterCriticalSection(&cs);
			queue_datas_.push_back(Masses);
			LeaveCriticalSection(&cs);
		}
		else
			Sleep(1);
	}
}
void CManifestationStatic::GetDif(double t, Particle& p, int index)
{
	double dt = 0.0001;
	ULONG64 num = t / dt;
	ULONG64 i = 0;
	double hmetre = 0;
	double vmetre = 0;
	for (i = 0; i < num; ++i)
	{
		p.hg = 0;
		p.vg = 0;
		UINT iSize = Masses.size();
		for (UINT k = 0; k < iSize; ++k)
		{
			if (k == index)
				continue;
			GetSpeed(p, index, Masses[k], k);
		}
		hmetre = dt * p.Horizon + (p.hg * dt * dt / 2);
		vmetre = dt * p.Verticality + (p.vg * dt * dt / 2);

		p.Horizon += p.hg * dt;
		p.Verticality += p.vg * dt;

		p.hmetre += hmetre;
		p.vmetre += vmetre;
	}
}
void CManifestationStatic::OnRButtonDown(UINT nFlags, CPoint point)
{
	//add.clear();
	//Particle p;
	//p.setPoint(point);
	//FILETIME ft;
	//LARGE_INTEGER li;
	//GetSystemTimeAsFileTime(&ft);
	//li.LowPart = ft.dwLowDateTime;
	//li.HighPart = ft.dwHighDateTime;
	//p.MoveTime = li.QuadPart;
	//p.GM = -G * PlanetMass * 500;
	//p.Horizon = 0;
	//p.Verticality = 0;
	//p.rc = 0;
	//p.destroy = true;
	//add.push_back(p);

	add.clear();
	Particle p;
	p.GM = EarthMass;
	//FILETIME ft;
	//LARGE_INTEGER li;
	//GetSystemTimeAsFileTime(&ft);
	//li.LowPart = ft.dwLowDateTime;
	//li.HighPart = ft.dwHighDateTime;
	//p.MoveTime = li.QuadPart;
	p.Horizon = 0;
	p.setPoint(point);
	p.rc = RGB(0, 255, 255);
	add.push_back(p);


	point.y += Dosage;
	p.setPoint(point);
	++p.ID;
	p.GM = 0.00000000;
	p.Horizon = EarthMass;
	p.Horizon *= 10000000;
	p.Horizon /= RealEarthR;
	p.Horizon = sqrt(p.Horizon);
	p.rc = RGB(255, 255, 255);
	add.push_back(p);
	CStatic::OnRButtonDown(nFlags, point);
}

void CManifestationStatic::OnLButtonDown(UINT nFlags, CPoint point)
{
	add.clear();
	Particle p;
	p.setPoint(point);
	//FILETIME ft;
	//LARGE_INTEGER li;
	//GetSystemTimeAsFileTime(&ft);
	//li.LowPart = ft.dwLowDateTime;
	//li.HighPart = ft.dwHighDateTime;
	//p.MoveTime = li.QuadPart;
	p.GM = G * PlanetMass;
	p.Horizon = Horizon;
	p.Verticality = Verticality;
	p.rc = rc;
	add.push_back(p);
	CStatic::OnLButtonDown(nFlags, point);
}
void CManifestationStatic::OnRButtonDblClk(UINT nFlags, CPoint point)
{

	CStatic::OnRButtonDblClk(nFlags, point);
}


void CManifestationStatic::OnLButtonDblClk(UINT nFlags, CPoint point)
{

	CStatic::OnLButtonDblClk(nFlags, point);
}
