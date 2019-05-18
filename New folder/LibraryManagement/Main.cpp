#include "HeaderManagement.h"
int main()
{
	UserList List;
	
	User admin;
	NodeUser *ADmin = new NodeUser;
	NodeUser *User = new NodeUser;
	ofstream systemadmin;
	systemadmin.open("useraccount.txt", ios_base::out | ios_base::app);
	InitializeUserList(List);
	CreateAdmin(List, admin,ADmin);
	delete ADmin;
	AddFileTolist(List,User);
	RunMenuSignIn(List);
	DeleteList(List);
	systemadmin.close();
	system("pause");

}