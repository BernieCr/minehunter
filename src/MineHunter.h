// MineHunter.h : Haupt-Header-Datei f�r die Anwendung MINEHUNTER
//

#if !defined(AFX_MINEHUNTER_H__7E4AE7AB_DA9A_4EEC_BA14_C3F78855495B__INCLUDED_)
#define AFX_MINEHUNTER_H__7E4AE7AB_DA9A_4EEC_BA14_C3F78855495B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CMineHunterApp:
// Siehe MineHunter.cpp f�r die Implementierung dieser Klasse
//

class CMineHunterApp : public CWinApp
{
public:
	CMineHunterApp();

// �berladungen
	// Vom Klassenassistenten generierte �berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMineHunterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CMineHunterApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // !defined(AFX_MINEHUNTER_H__7E4AE7AB_DA9A_4EEC_BA14_C3F78855495B__INCLUDED_)
