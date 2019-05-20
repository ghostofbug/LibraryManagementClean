#include "PublicFunc.h"
int CountNumber(int n)
{
	int count = 1;
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return count;
}
string EncryptPassWord(string pass)
{
	char key[14] = { 'A','B','C','D','E','F','G','J','Y','X','Z','W','I','S' };
	string encrypt = pass;
	for (int i = 0; i < encrypt.size(); i++)
	{
		encrypt[i] = pass[i] ^ key[i % (sizeof(key) / sizeof(char))];
	}
	return encrypt;
}
string HidePassWordV2(string password)
{
	string hidepassword = password;
	for (int i = 0; i < hidepassword.size(); i++)
	{
		if (i >= 2)
		{
			hidepassword[i] = '*';
		}
	}
	return hidepassword;
}
int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&csbi
	))
		return -1;
	return csbi.dwCursorPosition.X;
}

int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&csbi
	))
		return -1;
	return csbi.dwCursorPosition.Y;
}
int StringSize(string text)
{
	return text.size();
}
void DisplayIntAfterError(int x, int y)
{
	gotoxy(x, y);
}
void DisplayAfterError(int x, int y,string &text,bool Check)
{
	string text_temp = text;
	text = "";
	gotoxy(x, y);
	if (Check == false)
	{
		cout << text_temp;
		gotoxy(x + text_temp.size(), y);
	}
	else
	{
		cout << text;
	}
}
void LoadingDot(string text)
{
	cout << text;
	for (int i = 0; i <3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << ".";
			cout.flush();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		gotoxy(StringSize(text), wherey());
		for (int k = 0;k < 6; k++)
		{
			cout << " ";
		}
		gotoxy(StringSize(text),wherey());
		
	}
}
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
string HidePassword(int x,int y)
{
	string password;
	char keypressed;
	for (;;) 
	{
		keypressed = NULL;
		keypressed = _getch();
		if (password.size()<16 && (keypressed >= 60 && keypressed <= 90) || (keypressed >= 97 && keypressed <= 122) || (keypressed >= 48 && keypressed <= 57) || keypressed == 32 || keypressed ==(int)',')
		{
			password += keypressed;
			cout << "*";
		}
		else if (password.size() >0 && keypressed == 8)
		{
			password.resize(password.size() - 1);
			gotoxy(x, y);
			for (int l = 0; l < password.size(); l++)
			{
				cout << "*";
			}
			cout << " ";
			int n = static_cast<int>(password.length());
			gotoxy(x + n, y);
		}
		else if (keypressed == 13)
		{
			break;
		}
	}
	return password;
}
int FileSize(string file)
{
	ifstream fin;
	fin.open(file,ios::in);
	int dem = 0;
	string x;
	while (getline(fin, x))
	{
		dem++;
	}
	fin.close();
	return dem;
}

bool CheckDay(Date date) {
	int MaxDay[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (date.y % 400 == 0 || date.y % 4 == 0 && date.y % 100 != 0) {
		MaxDay[2] = 29;
	}
	if (date.y < 1)
	{
		return false;
	}
	if (date.m < 1 || date.m >12)
	{
		return false;
	}
	if (date.d < 1 || date.d>MaxDay[date.m])
	{
		return false;
	}
	return true;
}
Date GetDay(int x, int y)
{
	Date date;
	do {
		scanf_s("%d/%d/%d", &date.d, &date.m, &date.y);
		if (CheckDay(date) == false)
		{
			gotoxy(x, y);
			cin.clear();
			cin.ignore();
		}
	} while (CheckDay(date) == false);
	return date;
}

Date PlusDay(Date date, int d, int m, int y) {

	int MaxDay[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	date.d = date.d + d;
	date.m = date.m + m;
	date.y = date.y + y;
	if (date.y % 400 == 0 || date.y % 4 == 0 && date.y % 100 != 0) {
		MaxDay[2] = 29;
	}
	while (date.m > 12)
	{
		date.m = date.m - 12;
		date.y++;
		if (date.y % 400 == 0 || date.y % 4 == 0 && date.y % 100 != 0) {
			MaxDay[2] = 29;
		}
	}
	while (date.d > MaxDay[date.m])
	{
		date.d = date.d - MaxDay[date.m];
		date.m++;
		if (date.m > 12)
		{
			date.m = 1;
			date.y++;
			if (date.y % 400 == 0 || date.y % 4 == 0 && date.y % 100 != 0) {
				MaxDay[2] = 29;
			}
		}
	}
	if (date.d > MaxDay[date.m])
	{
		date.d = MaxDay[date.m];
	}
	return date;
}
void DisplayDay(Date date)
{
	if (date.d < 10) {
		cout << "0";
	}
	cout << date.d << "/";
	if (date.m < 10) {
		cout << "0";
	}
	cout << date.m << "/";
	if (date.y < 1000) {
		if (date.y < 100) {
			if (date.y < 10) {
				cout << "0";
			}
			cout << "0";
		}
		cout << "0";
	}
	cout << date.y;
}
void DisplaySex(int x)
{
	if (x == 1)
	{
		cout << setw(4) << "Nam";
	}
	else if (x == 0)
	{
		cout << setw(4) << "Nu";
	}
	else
	{
		cout << "Khac";
	}
}
void DisplayTime(Time time)
{
	if (time.Hrs < 10) {
		cout << "0";
	}
	cout << time.Hrs << ":";
	if (time.Mins < 10) {
		cout << "0";
	}
	cout << time.Mins << ":";
	if (time.Secs < 10) {
		cout << "0";
	}
	cout << time.Secs;
}
string printRandomNumber()
{
	char num[10] = { '1','2','3','4','5','6','7','8','9','0' };
	string text = "";
	for (int i = 0; i < 10; i++)
	{
		text = text + num[rand() % 10];
	}
	return text;
}
string printRandomString()
{
	char alphabet[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G',
						  'H', 'I', 'J', 'K', 'L', 'M', 'N',
						  'O', 'P', 'Q', 'R', 'S', 'T', 'U',
						  'V', 'W', 'X', 'Y', 'Z' };

	string text = "";
	for (int i = 0; i < 5; i++)
	{
		text = text + alphabet[rand() % 26];
	}
	return text;
}
void Pause()
{
	cout << "Nhan bat ky de tiep tuc.";
	_getch();
}