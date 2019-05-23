﻿#ifndef __UserManagement_H__
#define __UserManagement_H__
#include <iostream>
#include <fstream>
using namespace std;
#include "PublicFunc.h"
#include <string>
#include <conio.h>
#include <stdio.h>

struct PersonInfo {
	string Name;
	Date Birthday; // D/M/Y
	int Sex; // 0 for female, 1 for male;
	string CitizenId;
	string Email;
	string Address; // address,street,ward,city
};
struct User {
	string UserId;
	string PassWord;
	PersonInfo Info;
	int Stats; //
	int Pos; //defined above
	bool success;
};

struct NodeUser {
	User node;
	NodeUser *next;
};
struct UserList {
	NodeUser *listhead;
	NodeUser *listtail;
};
// ADMIN/NGƯỜI DÙNG
User Admin(); //Khởi tạo admin hệ thống
void CreateAdmin(UserList &list, User ADmin, NodeUser *NodeAdmin); // hàm tạo addmin hệ thống
void InitializeUserList(UserList &list); // hàm tạo danh sách người dùng
void AddTail(UserList &list, NodeUser *user); // hàm thêm người dùng đăng ký vào cuối list
NodeUser *AddUser(User user); // hàm khởi tạo một nút kiểu người dùng
User Register(UserList list); // Tạo người dùng mới
void GrantPermission(UserList &list, NodeUser *temp, NodeUser *temp1);// hàm cấp quyền người dùng
void DeleteList(UserList &list);//Xóa danh sách

//KIỂM TRA
bool CheckCreateAccount(UserList list, string registeruser, NodeUser *temp); // hàm kt tài khoản đã tồn tại chưa
bool CheckSame(string username, string password); // hàm kiểm tra ID và mật khẩu có trùng không
bool CheckIDCard(string ID); // Hàm kiểm tra CMND 
int CountIDCard(string ID); // Hàm đếm chữ số CMND
bool CheckAdmin(string signinuser, UserList list, NodeUser *temp); //hàm kt nguoi dang nhap la admin 
bool CheckManager(string signinuser, UserList list, NodeUser *temp); // hàm kt người đăng nhập là quản lý
bool CheckBlocked(string signinuser, UserList list, NodeUser *temp); // hàm kt tài khoản có bị khóa hay không

//ĐỒNG BỘ DỮ LIỆU
void AddUserToList(UserList &list, User user, NodeUser *User); // hàm đưa tài khoản đã đăng ký thành công vào list
void ListToFile(UserList list); //Ghi dữ liệu vào file
void AddFileTolist(UserList &list, NodeUser *user); //Lấy dữ liệu từ file

//HIỂN THỊ
void DisplayUserInfo(UserList list, string signinuser);
#endif // !__UserManagement_H__

