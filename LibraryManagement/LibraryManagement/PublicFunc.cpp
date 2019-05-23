#include "PublicFunc.h"
bool AvoidAllSpace(string text)
{
	int count = 0;
	int n = StringSize(text);
	for (int i = 0; i < n; i++)
	{
		if (text[i] != ' ')
		{
			return false;
		}
	}
	return true;
}
string AvoidNullString(string text)
{
	int y = wherey();
	string returntext;
	do
	{
		getline(cin,returntext);
		if (returntext.empty() == true || (returntext.empty()==false && AvoidAllSpace(returntext)==true))
		{
			gotoxy(0, y);
			for (int i = 0; i < StringSize(text)+StringSize(returntext); i++)
			{
				cout << " ";
			}
			gotoxy(0, y);
			cout << text;
		}
	} while (returntext.empty() == true || (returntext.empty() == false && AvoidAllSpace(returntext) == true));
	return returntext;
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
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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
int StringSize(string text)
{
	int x = static_cast<int>(text.size());
	return x;
}
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
string HidePassword(int x, int y,int status)
{
	string password;
	char keypressed;
	int threshold;
	if (status == 1)
	{
		threshold = 0;
	}
	if (status == 0)
	{
		threshold = 6;
	}
	for (;;)
	{
		keypressed = NULL;
		keypressed = _getch();
		if (password.size() < 16 && (keypressed >= 60 && keypressed <= 90) || (keypressed >= 97 && keypressed <= 122) || (keypressed >= 48 && keypressed <= 57) || keypressed == 32 || keypressed == (int)',')
		{
			password += keypressed;
			cout << "*";
		}
		else if (password.size() > 0 && keypressed == 8)
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
		else if (keypressed == 13 && StringSize(password) >= threshold)
		{
				break;
		}
	}
	return password;
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
void LoadingDot(string text)
{
	cout << text;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << ".";
			cout.flush();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		gotoxy(StringSize(text), wherey());
		for (int k = 0; k < 6; k++)
		{
			cout << " ";
		}
		gotoxy(StringSize(text), wherey());

	}
}
void Pause()
{
	cout << "Nhan bat ky de tiep tuc.";
	_getch();
}

string printRandomNumber(int n)
{
	char num[10] = { '1','2','3','4','5','6','7','8','9','0' };
	string text = "";
	for (int i = 0; i < n; i++)
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
void stream2hex(const std::string str, std::string& hexstr)
{
	bool capital = false;
	hexstr.resize(str.size() * 2);
	const size_t a = capital ? 'A' - 1 : 'a' - 1;

	for (size_t i = 0, c = str[0] & 0xFF; i < hexstr.size(); c = str[i / 2] & 0xFF)
	{
		hexstr[i++] = c > 0x9F ? (c / 16 - 9) | a : c / 16 | '0';
		hexstr[i++] = (c & 0xF) > 9 ? (c % 16 - 9) | a : c % 16 | '0';
	}
}

void hex2stream(const std::string hexstr, std::string& str)
{
	str.resize((hexstr.size() + 1) / 2);

	for (size_t i = 0, j = 0; i < str.size(); i++, j++)
	{
		str[i] = (hexstr[j] & '@' ? hexstr[j] + 9 : hexstr[j]) << 4, j++;
		str[i] |= (hexstr[j] & '@' ? hexstr[j] + 9 : hexstr[j]) & 0xF;
	}
}

