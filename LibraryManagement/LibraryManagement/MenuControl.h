#ifndef __MenuControl_H__
#define __MenuControl_H__
#include "HeaderManagement.h"
#include "UserManagement.h"

int GetDirect();
string GetInput();

//THAY ĐỔI THÔNG TIN NGƯỜI DÙNG
void ChangePassword(UserList &list, string signinuser); // hàm thay đổi password
void ChangeName(string signinuser, UserList &list);//Đổi tên
void ChangeSex(string signinuser, UserList &list);//Đổi giới tính
void ChangeEmail(string signinuser, UserList &list);//Đổi email
void ChangeAddress(string signinuser, UserList &list);//Đổi địa chỉ
void ChangeDateOfBirth(string signinuser, UserList &list);//Đổi ngày sinh
//MENU
bool SignIn(string ID, string Pass, UserList list, NodeUser *temp); // hàm kt đăng nhập
void MenuSignIn();
void RunMenuSignIn(UserList &list); // hàm chạy menu đăng nhập
void MenuFunc();
void RunMenuFunc(string SignInUserID, UserList &List); // hàm chạy menu tính năng
void MenuUserManage();
void RunMenuUserManage(string SignInUserID, UserList &list); // hàm chạy menu quản lý người dùng
void MenuReader();
void RunMenuReader(string SignInUserID, UserList userlist);
void MenuBookManage();
void RunMenuBookManage(string SignInUserID, UserList userlist);
void MenuStatistic();
void RunMenuStatistic(string SignInUserID, UserList userlist);
void MenuUpdatePersonalInfo();
void RunMenuUpdatePersonalInfo(string UserSignIn, UserList &list);
#endif

