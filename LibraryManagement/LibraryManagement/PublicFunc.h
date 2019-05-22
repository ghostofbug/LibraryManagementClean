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
//CÁC HÀM TRÌNH BÀY
void DisplayTime(Time time);//Hiển thị giờ
void DisplaySex(int x);// Hiển thị giới tính
void DisplayDay(Date date);// Hiển thị ngày

//DI CHUYỂN CON TRỎ MÀN HÌNH
void gotoxy(int x, int y); // hàm di chuyển cursor tới vị trí x,y http://www.cplusplus.com/
int wherey(); // hàm lấy tọa độ y trên màn console nguồn http://www.cplusplus.com/
int wherex();// hàm lấy tọa độ x trên màn console http://www.cplusplus.com/

//HỖ TRỢ GIAO DIỆN
string HidePassWordV2(string password); // hàm ẩn 1 phần password 
string HidePassword(int x, int y); // Ẩn mật khẩu bằng '*'
void LoadingDot(string text);//Thông báo đang thực hiện thao tác
void Pause();//Dừng màn hình

//DỮ LIỆU
string EncryptPassWord(string pass);//mã hóa mật khẩu đơn giản
int FileSize(string file); // hàm lấy kích thước file
int StringSize(string text); // hàm lấy kich thước chuỗi 
int CountNumber(int n); //Đếm số trong chuỗi
Date GetDay(int x,int y); // hàm lấy ngày tháng năm
bool CheckDay(Date date); // hàm kt ngày tháng năm

//TẠO CHUỐI NGẪU NHIÊN
string printRandomString();//Tạo chuỗi ký tự
string printRandomNumber();//Tạo chuỗi số

#endif

