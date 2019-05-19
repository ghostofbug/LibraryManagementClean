#ifndef __UserManagement_H__
#define __UserManagement_H__
#include <iostream>
#include <fstream>
using namespace std;
#include "PublicFunc.h"
#include <string>
#include <conio.h>
#include <stdio.h>
#define Sex_Male 1;
#define Sex_Female 0;
#define Sex_Optional - 1;
#define Status_Blocked 1;
#define Status_Activated 0;
#define Pos_Ad 1;
#define Pos_Manage 0;
#define Pos_Employ -1;
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
	int Stats; // defined above
	int Pos; //defined above
};

struct NodeUser {
	User node;
	NodeUser *next;
};
struct UserList {
	NodeUser *listhead;
	NodeUser *listtail;
};
void InitializeUserList(UserList &list); // hàm tạo danh sách người dùng
void AddTail(UserList &list, NodeUser *user); // hàm thêm người dùng đăng ký vào cuối list
NodeUser *AddUser(User user); // hàm khởi tạo một nút kiểu người dùng
User Register(UserList list); // hàm cho admin add tài khoản mới vao
void AddUserToList(UserList &list, User user, NodeUser *User); // hàm đưa tài khoản đã đăng ký thành công vào list
void RunMenuSignIn(UserList &list); // hàm chạy menu đăng nhập
bool SignIn(string ID, string Pass, UserList list, NodeUser *temp); // hàm kt đăng nhập
bool CheckCreateAccount(UserList list, string registeruser, NodeUser *temp); // hàm kt tài khoản đã tồn tại chưa
void ChangePassword(UserList &list, string signinuser); // hàm thay đổi password
void RunMenuFunc(string SignInUserID, UserList &list); // hàm chạy menu tính năng
void RunMenuUserManage(string SignInUserID, UserList &list); // hàm chạy menu quản lý người dùng
bool CheckSame(string username, string password); // hàm kiểm tra ID và mật khẩu có trùng không
bool CheckIDCard(string ID); // Hàm kiểm tra CMND 
int CountIDCard(string ID); // Hàm đếm chữ số CMND
User Admin(); // hàm khởi tạo admin hệ thống
void CreateAdmin(UserList &list, User ADmin, NodeUser *NodeAdmin); // hàm tạo addmin hệ thống
string EncryptPassWord(string pass); // hàm mã hóa mật khẩu vào file
void ListToFile(UserList list); //hàm đưa ds vào file
void AddFileTolist(UserList &list, NodeUser *user); // hàm đưa data từ file vao list
bool CheckAdmin(string signinuser, UserList list, NodeUser *temp); //hàm kt nguoi dang nhap la admin 
void GrantPermission(UserList &list,NodeUser *temp,NodeUser *temp1);// hàm cấp quyền người dùng
bool CheckManager(string signinuser, UserList list, NodeUser *temp); // hàm kt người đăng nhập là quản lý
bool CheckBlocked(string signinuser, UserList list, NodeUser *temp); // hàm kt tài khoản có bị khóa hay không
void DeleteList(UserList &list);
void DisplayUserInfo(UserList list, string signinuser);
#endif // !__UserManagement_H__

