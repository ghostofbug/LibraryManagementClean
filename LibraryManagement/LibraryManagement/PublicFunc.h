#ifndef __PublicFunc_H__
#define __PublicFunc_H__
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <chrono>
using namespace std;

struct Time
{
	int Hrs;
	int Mins;
	int Secs;
};
struct Date
{
	int d;
	int m;
	int y;
};
void DisplayTime(Time time);
string HidePassWordV2(string password); // hàm ẩn 1 phần password 
int FileSize(string file); // hàm lấy kích thước file
Date GetDay(int x,int y); // hàm lấy ngày tháng năm
bool CheckDay(Date date); // hàm kt ngày tháng năm
Date PlusDay(Date date, int d, int m, int y);
string HidePassword(int x, int y); // hàm thay password bằng *
void gotoxy(int x, int y); // hàm di chuyển cursor tới vị trí x,y http://www.cplusplus.com/
void DisplayAfterError(int x, int y, string &text, bool Check); //hàm thể hiện lỗi sai 
void DisplaySex(int x);// hàm hiện giới tính
void DisplayDay(Date date);// hàm hiện thỉ ngày
Date PlusDay(Date date, int d, int m, int y);
void DisplayIntAfterError(int x, int y);// hàm hiện thị lỗi sai kiểu int
int StringSize(string text); // hàm lấy kich thước chuỗi 
int wherey(); // hàm lấy tọa độ y trên màn console nguồn http://www.cplusplus.com/
int wherex();// hàm lấy tọa độ x trên màn console http://www.cplusplus.com/
void LoadingDot(string text);
string EncryptPassWord(string pass);
int CountNumber(int n);
string printRandomString();
string printRandomNumber();
void Pause();
#endif

