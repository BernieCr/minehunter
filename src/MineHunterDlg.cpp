// MineHunterDlg.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "MineHunter.h"
#include "MineHunterDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMineHunterDlg Dialogfeld

CMineHunterDlg::CMineHunterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMineHunterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMineHunterDlg)
	m_newm = 90;
	m_newh = 24;
	m_neww = 36;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMineHunterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMineHunterDlg)
	DDX_Text(pDX, IDC_MINES, m_newm);
	DDV_MinMaxInt(pDX, m_newm, 0, 10000);
	DDX_Text(pDX, IDC_HEIGHT, m_newh);
	DDV_MinMaxInt(pDX, m_newh, 1, 99);
	DDX_Text(pDX, IDC_WIDTH, m_neww);
	DDV_MinMaxInt(pDX, m_neww, 1, 99);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMineHunterDlg, CDialog)
	//{{AFX_MSG_MAP(CMineHunterDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(IDC_SHOWTIP, OnShowtip)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMineHunterDlg Nachrichten-Handler

BOOL CMineHunterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	m_started = false;

	CString dir;
	::GetModuleFileName(AfxGetApp()->m_hInstance, dir.GetBuffer(MAX_PATH), MAX_PATH);
	dir.ReleaseBuffer();
	dir = dir.Left(dir.ReverseFind('\\')+1);

	for (int i = 0; i <= TYPE_LAST; i++)
	{
		CString s;
		itoa(i, s.GetBuffer(10), 10);
		s.ReleaseBuffer();
		s = dir+"item"+s+".jpg";
		m_picitem[i] = new CxImage(s, CXIMAGE_FORMAT_JPG);

		if (i == 0)
		{
			m_item_w = m_picitem[0]->GetWidth();
			m_item_h = m_picitem[0]->GetHeight();
		}
	}
	
	for (i = 0; i < 8; i++)
	{
		CString s;
		itoa(i+1, s.GetBuffer(10), 10);
		s.ReleaseBuffer();
		s = dir+"item2"+s+".jpg";
		m_picnumber[i] = new CxImage(s, CXIMAGE_FORMAT_JPG);
	}

	m_field.SetDrawFunc(DrawField, (void*)this);

	OnOK();
	
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CMineHunterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // device context for painting		
		
		for (int i = 0; i < m_field.GetHeight(); i++)
		{
			for (int j = 0; j < m_field.GetWidth(); j++)
			{
				DrawFieldInt(dc.m_hDC, j, i);
			}
		}

		CDialog::OnPaint();
	}

}

HCURSOR CMineHunterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CMineHunterDlg::PaintIt()
{
	CRect rect;
	GetDlgItem(IDC_FIELD)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	InvalidateRect(&rect);
	UpdateWindow();
}

void CMineHunterDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	for (int i = 0; i <= TYPE_LAST; i++)
	{
		delete m_picitem[i];
	}
	
	for (i = 0; i < 8; i++)
	{
		delete m_picnumber[i];
	}	
}


void CMineHunterDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ClickField(point, true);
	CDialog::OnLButtonUp(nFlags, point);
}

void CMineHunterDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	ClickField(point, false);
	CDialog::OnRButtonDown(nFlags, point);
}

void CMineHunterDlg::ClickField(CPoint point, bool left)
{
	if (!m_started) return;
	CRect rect;
	GetDlgItem(IDC_FIELD)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	if (rect.PtInRect(point))
	{
		int px = point.x - rect.left;
		int py = point.y - rect.top;
		int x = px / m_item_w;
		int y = py / m_item_h;
		
		int res = m_field.Click(x,y,left?0:1);

		CString s;
		s.Format("Minen: %i von %i markiert", m_field.GetMarks(), m_field.GetTotalMines());
		SetDlgItemText(IDC_MINEINFO, s);

		if (res == 1)
		{
			m_field.Lose(x,y);
			//PaintIt();
			EndGame();
			MessageBox("Das war's wohl!");
		}
		else if (res == 2)
		{
			//PaintIt();
			EndGame();
			MessageBox("Supi!!! Du hast gewonnen!");
		}

		//PaintIt();
	}
}

void CMineHunterDlg::OnOK() 
{
	EndGame();
	m_field.Create(1,1,1);
	PaintIt();

	UpdateData();
	m_field.Create(m_neww, m_newh, m_newm);
	m_start = CTime::GetCurrentTime();
	OnTimer(1);
	SetTimer(1, 300, NULL);
	m_started = true;

	CString s;
	s.Format("Minen: %i von %i markiert", m_field.GetMarks(), m_field.GetTotalMines());
	SetDlgItemText(IDC_MINEINFO, s);

	int winw = max(500,((m_neww) * m_item_w) + 15);
	int winh = ((m_newh) * m_item_h) + 90;

	SetWindowPos(NULL,NULL,NULL,winw,winh,SWP_NOZORDER | SWP_NOREPOSITION | SWP_NOMOVE);
	SizeControl(GetDlgItem(IDC_FIELD), (m_neww * m_item_w), (m_newh * m_item_h));

	PaintIt();
}


void CMineHunterDlg::OnShowtip() 
{
	m_field.Tip();
	//PaintIt();
}

void CMineHunterDlg::DrawField(int x, int y, void* data)
{
	CMineHunterDlg* dlg = (CMineHunterDlg*)data;
	CClientDC dc(dlg);
	dlg->DrawFieldInt(dc.m_hDC, x, y);

}

void CMineHunterDlg::DrawFieldInt(HDC dc, int j, int i)
{
	CRect rect;
	GetDlgItem(IDC_FIELD)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	int x = rect.left, y = rect.top;

	int type = m_field.GetVis(j,i);

	int xofs = x + (j*m_item_w);
	int yofs = y + (i*m_item_h);

	if (type != TYPE_NUMBER)
	{
		if (type <= TYPE_LAST)
			m_picitem[type]->Draw(dc,xofs,yofs);
	}
	else
	{
		int num = m_field.GetNumber(j,i);
		if (num)
			m_picnumber[num-1]->Draw(dc,xofs,yofs);
	}
}




void CMineHunterDlg::Resize()
{
	CRect r;
	GetWindowRect(&r);
	ScreenToClient(&r);
	int w = r.Width();
	int h = r.Height();

//	SizeControl(GetDlgItem(IDC_LIST), (w), (h));
//	MoveControl(GetDlgItem(IDC_ST_TEXT), 15, (h-18));

	InvalidateRect(&r);
	UpdateWindow();
}

void CMineHunterDlg::MoveControl(CWnd* w, int x, int y)
{
	if ((!w) || (!IsWindow(w->m_hWnd))) return;
	CRect r;
	w->GetWindowRect(&r);
	ScreenToClient(&r);
	int width = r.Width();
	int height = r.Height();

	w->MoveWindow(x, y, width, height);

}

void CMineHunterDlg::SizeControl(CWnd* w, int width, int height)
{
	CRect r;
	w->GetWindowRect(&r);
	ScreenToClient(&r);
	int x = r.left;
	int y = r.top;

	w->MoveWindow(x, y, width, height);
}

void CMineHunterDlg::OnTimer(UINT id) 
{
	if (id == 1)
	{
		CTime curt = CTime::GetCurrentTime();	
		curt -= CTimeSpan(m_start.GetTime());
		SetDlgItemText(IDC_TIMEINFO, curt.Format("Zeit: %M:%S"));
	}
	else CDialog::OnTimer(id);
}

void CMineHunterDlg::EndGame()
{
	m_started = false;
	KillTimer(1);
}
