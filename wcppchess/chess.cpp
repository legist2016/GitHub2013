#include "stdafx.h"
#include "chess.h"
#include <vector>
#include <string>

using namespace std;

Chess::Chess()
{
}


Chess::~Chess()
{
}

void Chess::test()
{
}

void Chess::loadini()
{
	IniFile ini("..\\s1.ini");
	string msg = ini.IniReadValue("info", "start");
	if (msg == "red")
	{
		MessageBox(NULL, "is red", "", MB_OK);
	}
	else
	{
		MessageBox(NULL, "is black", "", MB_OK);
	}
	msg = ini.IniReadValue("info", "chesses");
	int chesses = _ttoi(msg.c_str());
	for (int i = 0; i < chesses; ++i)
	{
		int chess, x, y;
		string  section("chess");
		
	}

	/*IniFile ini = new IniFile("..\\s1.ini");
	string s = ini.IniReadValue("info", "start");
	if (s == "black")
		rootstep.side = 1;
	else
		rootstep.side = 0;

	s = ini.IniReadValue("info", "chesses");
	chesses = int.Parse(s);
	for (int i = 0; i < chesses; ++i)
	{
		int chess, x, y;
		string section = "chess" + (i + 1);
		chess = int.Parse(ini.IniReadValue(section, "chess"));
		x = int.Parse(ini.IniReadValue(section, "posx"));
		y = int.Parse(ini.IniReadValue(section, "posy"));
		if (chess > 0 && chess <= 14 && x >= 0 && x < 9 && y >= 0 && y < 10)
		{
			m_board[y * 9 + x] = (byte)chess;
		}
	}
	*/
}

string IniFile::IniReadValue(string section, string key)
{
	std::vector<char> buff(255);
	GetPrivateProfileString(section.c_str(), key.c_str(), "", &buff[0], 255, m_lpFileName.c_str());
	return string(buff.begin(), buff.end());
}

IniFile::IniFile(string lpFileName)
{
	m_lpFileName = lpFileName;
}

IniFile::~IniFile()
{
}
