// Item.h: Schnittstelle für die Klasse CItem.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEM_H__320F2F23_8CC1_49ED_BE95_AAE5A696AEA2__INCLUDED_)
#define AFX_ITEM_H__320F2F23_8CC1_49ED_BE95_AAE5A696AEA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TYPE_EMPTY	0
#define TYPE_MINE	1
#define TYPE_NUMBER	2
#define TYPE_MARK	3
#define TYPE_FREE	4
#define TYPE_WRONG	5
#define TYPE_MINEUP	6

#define TYPE_LAST	6

class CItem  
{
public:
	CItem();
	virtual ~CItem();

	int	type;
	int vistype;
	int number;
};

#endif // !defined(AFX_ITEM_H__320F2F23_8CC1_49ED_BE95_AAE5A696AEA2__INCLUDED_)
