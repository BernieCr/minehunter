// MineHunterDlg.h : Header-Datei
//

#if !defined(AFX_MINEHUNTERDLG_H__F3E8CDB2_1343_41E9_B6AD_7DB4D8BB7DAE__INCLUDED_)
#define AFX_MINEHUNTERDLG_H__F3E8CDB2_1343_41E9_B6AD_7DB4D8BB7DAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMineHunterDlg Dialogfeld

#include "item.h"
#include "field.h"

#include "ximage.h"

class CMineHunterDlg : public CDialog
{
// Konstruktion
public:
	void EndGame();
	void DrawFieldInt(HDC dc, int j, int i);
	static void DrawField(int x, int y, void* data);
	void ClickField(CPoint point, bool left);
	void PaintIt();
	CMineHunterDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CMineHunterDlg)
	enum { IDD = IDD_MINEHUNTER_DIALOG };
	int		m_newm;
	int		m_newh;
	int		m_neww;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMineHunterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;

	CField m_field;

	bool m_started;

	CxImage* m_picitem[7];
	CxImage* m_picnumber[8]; // -1!!!
	int m_item_w, m_item_h;

	void SizeControl(CWnd* w, int width, int height);
	void MoveControl(CWnd* w, int x, int y);
	void Resize();

	CTime m_start;

	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CMineHunterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnShowtip();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MINEHUNTERDLG_H__F3E8CDB2_1343_41E9_B6AD_7DB4D8BB7DAE__INCLUDED_)
