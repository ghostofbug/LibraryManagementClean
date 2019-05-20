#ifndef __MenuControl_H__
#define __MenuControl_H__
#include "HeaderManagement.h"
#include "UserManagement.h"

int GetDirect();
string GetInput();
void MenuSignIn();
void MenuFunc();
void MenuUserManage();
void MenuReader();
void RunMenuReader(string SignInUserID, UserList userlist);
void MenuBookManage();
void RunMenuBookManage(string SignInUserID, UserList userlist);
void MenuStatistic();
void RunMenuStatistic(string SignInUserID, UserList userlist);
void MenuUpdatePersonalInfo();
void RunMenuUpdatePersonalInfo(string UserSignIn, UserList &list);
void ChangeName(string signinuser, UserList &list);
void ChangeSex(string signinuser, UserList &list);
void ChangeEmail(string signinuser, UserList &list);
void ChangeAddress(string signinuser, UserList &list);
void ChangeDateOfBirth(string signinuser, UserList &list);
#endif

