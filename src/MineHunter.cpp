// MineHunter.cpp : Legt das Klassenverhalten für die Anwendung fest.
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
// CMineHunterApp

BEGIN_MESSAGE_MAP(CMineHunterApp, CWinApp)
	//{{AFX_MSG_MAP(CMineHunterApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMineHunterApp Konstruktion

CMineHunterApp::CMineHunterApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CMineHunterApp-Objekt

CMineHunterApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMineHunterApp Initialisierung

BOOL CMineHunterApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standardinitialisierung

#ifdef _AFXDLL
	Enable3dControls();			// Diese Funktion bei Verwendung von MFC in gemeinsam genutzten DLLs aufrufen
#else
	Enable3dControlsStatic();	// Diese Funktion bei statischen MFC-Anbindungen aufrufen
#endif

	CMineHunterDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Da das Dialogfeld geschlossen wurde, FALSE zurückliefern, so dass wir die
	//  Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.
	return FALSE;
}
