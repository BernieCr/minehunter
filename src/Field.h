// Field.h: Schnittstelle für die Klasse CField.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIELD_H__BB41FCA2_672D_45C0_98AD_858874EE4087__INCLUDED_)
#define AFX_FIELD_H__BB41FCA2_672D_45C0_98AD_858874EE4087__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "item.h"
#include "afxtempl.h"

typedef CArray<CItem, CItem> iarray;
typedef void DrawFunc(int x, int y, void* data);

class CField  
{
public:
	int GetEmptyFields();
	int GetMarks();
	void SetDrawFunc(DrawFunc* func, void* funcdata);
	void Tip();
	int GetTotalMines();
	int GetFoundMines();
	void Lose(int x, int y);
	void OpenFreeFields(int x, int y);
	void SetVis(int x, int y, int type);
	int Click(int x, int y, int type);
	int GetVis(int x, int y);
	int GetHeight();
	int GetWidth();
	void SetNumber(int x, int y, int number);
	int GetNumber(int x,int y);
	void Set(int x, int y, int type);
	int Get(int x, int y);
	void Delete();
	void Create(int w, int h, int mines);
	CField();
	virtual ~CField();

	bool m_created;
	CItem m_field[100][100];
	int m_w, m_h;
	int m_mines;
protected:
	void Check1(int x, int y);
	void Free9(int x, int y);

	DrawFunc* m_drawfunc;
	void* m_funcdata;
};

#endif // !defined(AFX_FIELD_H__BB41FCA2_672D_45C0_98AD_858874EE4087__INCLUDED_)
