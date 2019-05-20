#include "HeaderManagement.h"
int main()
{
	UserList list;
	User admin;
	NodeUser *ADmin = new NodeUser;
	NodeUser *User = new NodeUser;
	ofstream systemadmin;
	systemadmin.open("useraccount.txt", ios_base::out | ios_base::app);
	InitializeUserList(list);
	CreateAdmin(list, admin,ADmin);
	delete ADmin;
	AddFileTolist(list,User);
	RunMenuSignIn(list);
	DeleteList(list);
	systemadmin.close();
}