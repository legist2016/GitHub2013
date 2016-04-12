#include "stdafx.h"
#include "wcppchess.h"
#include "ChessUI.h"


CChessUI::CChessUI(COLORREF transparentColor)
{
	m_bmpBoard = LoadBitmap(GetModuleHandle(0), (LPCSTR)IDB_BOARD);
	m_dcBoard = CreateCompatibleDC(0);
	if (m_bmpBoard && m_dcBoard)
	{
		SelectObject(m_dcBoard, m_bmpBoard);
		GetObject(m_bmpBoard, sizeof(m_biBoard), &m_biBoard);
	}

	HBITMAP tmpBmp = LoadBitmap(GetModuleHandle(0), (LPCSTR)IDB_CHESS);
	m_dcChess = CreateCompatibleDC(0);

	HDC tmpDc = CreateCompatibleDC(0);
	GetObject(tmpBmp, sizeof(m_biChess), &m_biChess);
	SelectObject(tmpDc, tmpBmp);

	//创建双倍高度的棋子图片，下半部作为掩码图
	m_bmpChess = CreateBitmap(m_biChess.bmWidth, m_biChess.bmHeight * 2, m_biChess.bmPlanes, m_biChess.bmBitsPixel, NULL);
	SelectObject(m_dcChess, m_bmpChess);

	//将读取的资源位图画入棋子图上半部分
	BitBlt(m_dcChess, 0, 0, m_biChess.bmWidth, m_biChess.bmHeight, tmpDc, 0, 0, SRCCOPY);

	DeleteObject(tmpBmp);
	//创建掩码临时图
	tmpBmp = CreateBitmap(m_biChess.bmWidth, m_biChess.bmHeight , 1, 1, NULL);
	SelectObject(tmpDc, tmpBmp);

	SetBkColor(m_dcChess, transparentColor);
	BitBlt(tmpDc, 0, 0, m_biChess.bmWidth, m_biChess.bmHeight, m_dcChess, 0, 0, SRCCOPY);


	BitBlt(m_dcChess, 0, 0, m_biChess.bmWidth, m_biChess.bmHeight, tmpDc, 0, 0, SRCINVERT);
	SetBkColor(m_dcChess, RGB(255, 255, 255));
	BitBlt(m_dcChess, 0, m_biChess.bmHeight, m_biChess.bmWidth, m_biChess.bmHeight, tmpDc, 0, 0, SRCCOPY);

	DeleteDC(tmpDc);
	DeleteObject(tmpBmp);

	//SelectObject(m_dcBoard, m_bmpChess);
}

void CChessUI::paint(HDC dst)
{
	BitBlt(dst, 0, 300, m_biChess.bmWidth, m_biChess.bmHeight, m_dcChess, 0, m_biChess.bmHeight, SRCAND);
	BitBlt(dst, 0, 300, m_biChess.bmWidth, m_biChess.bmHeight, m_dcChess, 0, 0, SRCPAINT);
}

void CChessUI::paintBoard(HDC hdc)
{
	BitBlt(hdc, 0, 0, m_biBoard.bmWidth, m_biBoard.bmHeight, m_dcBoard, 0, 0, SRCCOPY);
}

void CChessUI::paintChess(HDC hdc, int pos, int chess)
{
	BitBlt(hdc, 10 + (pos % 9) * 47 , 10 + (pos / 9)* 47, 41, m_biChess.bmHeight, m_dcChess, 41 * chess, m_biChess.bmHeight, SRCAND);
	BitBlt(hdc, 10 + (pos % 9) * 47, 10 + (pos / 9) * 47, 41, m_biChess.bmHeight, m_dcChess, 41 * chess, 0, SRCPAINT);
}


CChessUI::~CChessUI()
{
	DeleteDC(m_dcBoard);
	DeleteDC(m_dcChess);
	DeleteObject(m_bmpBoard);
	DeleteObject(m_bmpChess);
}
