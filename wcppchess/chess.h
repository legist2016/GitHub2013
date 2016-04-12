#pragma once
#include <string>
using std::string;

struct CHESSSTEP
{
	int from;
	int to;
	int win;
	CHESSSTEP* pNextStep;
	CHESSSTEP* pNebrStep;
};

class Chess
{
public:
	Chess();
	~Chess();

	void test();
	void loadini();
private:
	char m_board[91];
	CHESSSTEP m_firstStep;
};



class IniFile{
public:
	IniFile(string lpFileName);
	~IniFile();

	string	IniReadValue(string section, string key);

private:
	string m_lpFileName;
};
