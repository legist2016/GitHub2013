#pragma once
class CChessUI
{
public:
	CChessUI(COLORREF transparentColor);
	~CChessUI();
	void paint(HDC dst);
	void paintBoard(HDC hdc);
	void paintChess(HDC hdc, int pos, int chess);


private:
	HDC m_dcBoard;
	HDC m_dcChess;
	HBITMAP m_bmpBoard;
	HBITMAP m_bmpChess;
	
	BITMAP m_biBoard;
	BITMAP m_biChess;
};

