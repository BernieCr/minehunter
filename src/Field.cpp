// Field.cpp: Implementierung der Klasse CField.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Field.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CField::CField()
{
	m_created = false;
	srand( (unsigned)time( NULL ) );
}

CField::~CField()
{

}

void CField::Create(int w, int h, int mines)
{
	if (m_created)
	{
		Delete();
	}
	m_w = w;
	m_h = h;


	// Feld aufbauen
	CItem t;
	t.number = 0;
	t.type = TYPE_EMPTY;
	t.vistype = TYPE_EMPTY;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			m_field[i][j] = t;
		}
	}


	int x,y;

	// Minen setzen
	m_mines = min(w*h, mines);
	for (int k = 0; k < m_mines; k++)
	{
		do
		{
			x = (int)(((float)rand() / RAND_MAX) * w);
			y = (int)(((float)rand() / RAND_MAX) * h);
		}
		while (Get(x,y) != TYPE_EMPTY);
		Set(x,y,TYPE_MINE);
	}


	// Zahlen berechnen
	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			if (Get(x,y) != TYPE_MINE)
			{
				int c = 0;
				if (Get(x-1, y-1) == TYPE_MINE) c++;
				if (Get(x  , y-1) == TYPE_MINE) c++;
				if (Get(x+1, y-1) == TYPE_MINE) c++;
				if (Get(x-1, y  ) == TYPE_MINE) c++;
				if (Get(x+1, y  ) == TYPE_MINE) c++;
				if (Get(x-1, y+1) == TYPE_MINE) c++;
				if (Get(x  , y+1) == TYPE_MINE) c++;
				if (Get(x+1, y+1) == TYPE_MINE) c++;

				if (c) SetNumber(x,y,c);
			}
		}
	}
	

}

void CField::Delete()
{

}

int CField::Get(int x, int y)
{
	int ret = -1;
	if ((x >= 0) && (x < m_w) && (y >= 0) && (y < m_h))
	{
		ret = m_field[y][x].type;
	}
	return ret;
}

int CField::GetVis(int x, int y)
{
	int ret = -1;
	if ((x >= 0) && (x < m_w) && (y >= 0) && (y < m_h))
	{
		ret = m_field[y][x].vistype;
	}
	return ret;
}


void CField::Set(int x, int y, int type)
{
	if ((x >= 0) && (x < m_w) && (y >= 0) && (y < m_h))
	{
		m_field[y][x].type = type;
	}
}

void CField::SetVis(int x, int y, int type)
{
	if ((x >= 0) && (x < m_w) && (y >= 0) && (y < m_h))
	{
		m_field[y][x].vistype = type;
		m_drawfunc(x,y,m_funcdata);
	}
}


void CField::SetNumber(int x, int y, int number)
{
	if ((x >= 0) && (x < m_w) && (y >= 0) && (y < m_h))
	{
		m_field[y][x].type = TYPE_NUMBER;
		m_field[y][x].number = number;
	}
}

int CField::GetNumber(int x, int y)
{
	int ret = 0;
	if ((x >= 0) && (x < m_w) && (y >= 0) && (y < m_h))
	{
		if (m_field[y][x].type == TYPE_NUMBER)
		{
			ret = m_field[y][x].number;
		}
	}

	return ret;
}

int CField::GetWidth()
{
	return m_w;
}

int CField::GetHeight()
{
	return m_h;
}


int CField::Click(int x, int y, int type)
{
	// Return: 0=OK, 1=Mine(verloren), 2=Gewonnen


	int ft = Get(x,y);
	int vt = GetVis(x,y);

	int ret = 0;

	if (type == 0) // aufdecken
	{
		if (vt != TYPE_MARK)
		{
			switch (ft)
			{
				case TYPE_EMPTY:
					SetVis(x,y,TYPE_FREE);
					OpenFreeFields(x,y);
					break;
				case TYPE_NUMBER:
					SetVis(x,y,TYPE_NUMBER);
					break;
				case TYPE_MINE:
					SetVis(x,y,TYPE_MINE);
					ret = 1;
					break;
			}
		}
	}
	else if (type == 1) // markieren
	{
		if (vt == TYPE_MARK)
		{
			SetVis(x,y,TYPE_EMPTY);
		}
		if (vt == TYPE_EMPTY)
		{
			SetVis(x,y,TYPE_MARK);
		}
	}

	if (GetTotalMines() == GetMarks())
	{
		if (GetFoundMines() == GetMarks())
		{
			if (GetEmptyFields() == 0) ret = 2;
		}
	}

	return ret;
}




void CField::OpenFreeFields(int x, int y)
{
	Free9(x,y);
}

void CField::Free9(int x, int y)
{
	Check1(x-1, y-1);
	Check1(x  , y-1);
	Check1(x+1, y-1);
	Check1(x-1, y  );
	Check1(x+1, y  );
	Check1(x-1, y+1);
	Check1(x  , y+1);
	Check1(x+1, y+1);
}

void CField::Check1(int x, int y)
{
	int t = Get(x,y);
	if (GetVis(x,y) == TYPE_EMPTY)
	{
		if (t == TYPE_EMPTY) 
		{
			SetVis(x,y,TYPE_FREE);
			Free9(x,y);
		}
		if (t == TYPE_NUMBER)
		{
			SetVis(x,y,TYPE_NUMBER);
		}
	}
}

void CField::Lose(int x, int y)
{
	for (int i = 0; i < m_h; i++)
	{
		for (int j = 0; j < m_w; j++)
		{
			int ft = Get(j,i);
			int vt = GetVis(j,i);

		//	if (ft == TYPE_EMPTY) SetVis(j,i,TYPE_FREE);
		//	if (ft == TYPE_NUMBER) SetVis(j,i,TYPE_NUMBER);
			if (vt == TYPE_MARK) 
			{
				if (ft != TYPE_MINE) SetVis(j,i,TYPE_WRONG);
			}
			if (ft == TYPE_MINE)
			{
				if (vt != TYPE_MARK) SetVis(j,i,TYPE_MINE);
			}


		}
	}

	SetVis(x,y,TYPE_MINEUP);
}

int CField::GetTotalMines()
{
	return m_mines;
}

int CField::GetFoundMines()
{
	int c = 0;

	for (int i = 0; i < m_h; i++)
	{
		for (int j = 0; j < m_w; j++)
		{
			int ft = Get(j,i);
			int vt = GetVis(j,i);

			if ((ft == TYPE_MINE) && (vt == TYPE_MARK)) c++;
		}
	}

	return c;
}

int CField::GetMarks()
{
	int c = 0;

	for (int i = 0; i < m_h; i++)
	{
		for (int j = 0; j < m_w; j++)
		{
			int vt = GetVis(j,i);

			if (vt == TYPE_MARK) c++;
		}
	}

	return c;
}

int CField::GetEmptyFields()
{
	int c = 0;

	for (int i = 0; i < m_h; i++)
	{
		for (int j = 0; j < m_w; j++)
		{
			int vt = GetVis(j,i);
			if (vt == TYPE_EMPTY) c++;
		}
	}

	return c;
}


void CField::Tip()
{
	int x,y,c=0;
	do
	{
		c++;
		if (c > 10000) return;
		x = (int)(((float)rand() / RAND_MAX) * GetWidth());
		y = (int)(((float)rand() / RAND_MAX) * GetHeight());
	}
	while ((Get(x,y) == TYPE_MINE) || (GetVis(x,y) != TYPE_EMPTY));
	Click(x,y,0);
}

void CField::SetDrawFunc(DrawFunc *func, void* funcdata)
{
	m_funcdata = funcdata;
	m_drawfunc = func;
}



