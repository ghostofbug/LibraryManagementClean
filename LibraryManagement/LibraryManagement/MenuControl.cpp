#include "HeaderManagement.h"
void MenuUpdatePersonalInfo()
{
	cout << endl;
	cout << "   ************************************" << endl;
	cout << "   |   CAP NHAT THONG TIN NGUOI DUNG  |" << endl;
	cout << "   ************************************" << endl;
	cout << "   * 1. Thay doi ten                  *" << endl;
	cout << "   * 2. Thay doi gioi tinh            *" << endl;
	cout << "   * 3. Thay doi email                *" << endl;
	cout << "   * 4. Thay doi dia chi              *" << endl;
	cout << "   * 5. Thay doi ngay sinh            *" << endl;
	cout << "   * 0. Quay lai                      *" << endl;
	cout << "   ************************************" << endl;
	cout << endl << "Chon chuc nang: ";
}
void ChangeDateOfBirth(string signinuser, UserList &list)
{
	NodeUser *temp = new NodeUser;
	for (temp = list.listhead; temp != NULL; temp = temp->next)
	{
		if (temp->node.UserId.compare(signinuser) == 0)
		{
			cout << "Nhap ngay sinh moi: ";
			int y = wherey();
			y = static_cast<int>(y);
			string text = "Nhap ngay sinh moi: ";
			int x = static_cast<int>(text.size());
			temp->node.Info.Birthday = GetDay(x, y);
		}
	}
	delete temp;
}
void ChangeAddress(string signinuser, UserList &list)
{
	NodeUser *temp = new NodeUser;
	for (temp = list.listhead; temp != NULL; temp = temp->next)
	{
		if (temp->node.UserId.compare(signinuser) == 0)
		{
			cout << "Nhap dia chi moi: ";
			getline(cin, temp->node.Info.Address);
		}
	}
	delete temp;
}
void ChangeEmail(string signinuser, UserList &list)
{
	NodeUser *temp = new NodeUser;
	for (temp = list.listhead; temp != NULL; temp = temp->next)
	{
		if (temp->node.UserId.compare(signinuser) == 0)
		{
			cout << "Nhap dia chi mail dien tu moi: ";
			getline(cin, temp->node.Info.Email);
		}
	}
	delete temp;
}
void ChangeSex(string signinuser, UserList &list)
{
	NodeUser *temp = new NodeUser;
	for (temp = list.listhead; temp != NULL; temp = temp->next)
	{
		if (temp->node.UserId.compare(signinuser) == 0)
		{
			cout << "Nhap gioi tinh (0:nu / 1:nam) : ";
			string text1 = "Nhap gioi tinh (0:nu / 1:nam) : ";
			string sex;
			int y = wherey();
			y = static_cast<int>(y);
			int x = static_cast<int>(text1.size());
			while (sex.compare("1") != 0 && sex.compare("0") != 0)
			{
				gotoxy(x, y);
				getline(cin, sex);
			}
			if (sex.compare("1") == 0)
			{
				temp->node.Info.Sex = 1;
			}
			else if (sex.compare("0") == 0)
			{
				temp->node.Info.Sex = 0;
			}
			else
			{
				temp->node.Info.Sex = -1;
			}
		}
	}
	delete temp;
}
void ChangeName(string signinuser, UserList &list)
{
	NodeUser *temp = new NodeUser;
	for (temp = list.listhead; temp != NULL; temp = temp->next)
	{
		if (temp->node.UserId.compare(signinuser) == 0)
		{
			cout << "Nhap ten moi: " << endl;
			getline(cin, temp->node.Info.Name);
		}
	}
	delete temp;
}
void RunMenuUpdatePersonalInfo(string signinuser, UserList &list)
{
	int Direct;
	do
	{
		system("cls");
		DisplayUserInfo(list, signinuser);
		MenuUpdatePersonalInfo();
		Direct = GetDirect();
		if (Direct == 1)
		{
			cin.ignore();
			ChangeName(signinuser, list);
			ListToFile(list);
		}
		else if (Direct == 2)
		{
			ChangeSex(signinuser, list);
			ListToFile(list);
		}
		else if (Direct == 3)
		{
			cin.ignore();
			ChangeEmail(signinuser, list);
			ListToFile(list);
		}
		else if (Direct == 4)
		{
			cin.ignore();
			ChangeAddress(signinuser, list);
			ListToFile(list);
		}
		else if (Direct == 5)
		{
			ChangeDateOfBirth(signinuser, list);
			ListToFile(list);
		}
	} while (Direct != 0);
}
int GetDirect()
{
	int direct;
	cin >> direct;
	return direct;
}
string GetInput()
{
	string Input;
	getline(cin, Input);
	return Input;
}
void RunMenuSignIn(UserList &list)
{
	User user;
	NodeUser *temp = new NodeUser;
	string getUserId;
	string getPass;
	int direct;
	do
	{
		MenuSignIn();
		direct = GetDirect();
		if (direct == 1)
		{
			cin.ignore();
			cout << "Ten dang nhap : ";
			getUserId = GetInput();
			cout << "Mat khau      : ";
			string text = "Mat khau      : ";
			int x = static_cast<int>(text.size());
			int y = wherey();
			y = static_cast<int>(y);
			getPass = HidePassword(x, y);
			NodeUser *temp = new NodeUser;
			if (SignIn(getUserId, getPass, list, temp) == true && CheckBlocked(getUserId, list, temp) == true)
			{
				delete temp;
				RunMenuFunc(getUserId, list);
			}
			else
			{
				delete temp;
				cout << "" << endl;
				cout << "Dang nhap that bai!" << endl;
			}
		}
		Pause();
	} while (direct != 0);
}
void MenuSignIn()
{
	system("cls");
	cout << endl;
	cout << "   ***************************************************" << endl;
	cout << "   |      CHAO MUNG BAN DEN VOI THU VIEN DH KHTN!    |" << endl;
	cout << "   ***************************************************" << endl;
	cout << "   |  1. Dang nhap                0. Thoat           |" << endl;
	cout << "   ***************************************************" << endl;
	cout << endl << "Chon chuc nang: ";
}
void MenuFunc()
{
	system("cls");
	cout << endl;
	cout << "   ************************************" << endl;
	cout << "   |             CHUC NANG            |" << endl;
	cout << "   ************************************" << endl;
	cout << "   | 1. Quan ly nguoi dung            |" << endl;
	cout << "   | 2. Quan ly doc gia               |" << endl;
	cout << "   | 3. Quan ly sach                  |" << endl;
	cout << "   | 4. Lap phieu muon sach           |" << endl;
	cout << "   | 5. Lap phieu tra sach            |" << endl;
	cout << "   | 6. Thong ke                      |" << endl;
	cout << "   | 7. Bao mat sach                  |" << endl;
	cout << "   | 0. Dang xuat                     |" << endl;
	cout << "   ************************************" << endl;
	cout << endl << "Chon chuc nang: ";
}
void RunMenuFunc(string SignInUserID, UserList &List)
{
	list <BorrowForm> bf;
	list <Bill>BILL;
	BorrowFormToList(bf);
	BillToList(BILL);
	int direct1;
	do
	{
		MenuFunc();
		direct1 = GetDirect();
		if (direct1 == 1)
		{
			RunMenuUserManage(SignInUserID, List);
		}
		else if (direct1 == 2)
		{
			RunMenuReader(SignInUserID, List);
		}
		else if (direct1 == 3)
		{
			RunMenuBookManage(SignInUserID, List);
		}
		else if (direct1 == 4)
		{
			CreateBorrowForm(bf);
		}
		else if (direct1 == 5)
		{
			ReturnBook(bf,BILL);
		}
		else if (direct1 == 6)
		{
			RunMenuStatistic(SignInUserID, List);
		}
		else if (direct1 == 7)
		{
			LostBook(bf,BILL);
		}
	} while (direct1 != 0);
}

void MenuUserManage()
{
	system("cls");
	cout << endl;
	cout << "   ************************************" << endl;
	cout << "   |         QUAN LY NGUOI DUNG       |" << endl;
	cout << "   ************************************" << endl;
	cout << "   * 1. Thay doi mat khau             *" << endl;
	cout << "   * 2. Cap nhat thong tin ca nhan    *" << endl;
	cout << "   * 3. Tao nguoi dung                *" << endl;
	cout << "   * 4. Phan quyen nguoi dung         *" << endl;
	cout << "   * 0. Quay lai                      *" << endl;
	cout << "   ************************************" << endl;
	cout << endl << "Chon chuc nang: ";
}
void RunMenuUserManage(string SignInUserID, UserList &list)
{
	int direct1;

	do
	{
		MenuUserManage();
		direct1 = GetDirect();
		if (direct1 == 1)
		{
			system("cls");
			cin.ignore();
			ChangePassword(list, SignInUserID);
			ListToFile(list);
		}
		else if (direct1 == 2)
		{
			RunMenuUpdatePersonalInfo(SignInUserID, list);
		}
		else if (direct1 == 3)
		{
			NodeUser *nodeuser = new NodeUser;
			NodeUser *temp = new NodeUser;
			if (CheckAdmin(SignInUserID, list, temp) == true)
			{
				system("cls");
				User user;
				cin.ignore();
				user = Register(list);
				AddUserToList(list, user, nodeuser);
			}
			else
			{
				cout << "Gioi han quyen he thong" << endl;
			}
			delete nodeuser;
			delete temp;
		}
		else if (direct1 == 4)
		{
			NodeUser *temp = new NodeUser;
			if (CheckAdmin(SignInUserID, list, temp) == true)
			{
				NodeUser *temp = new NodeUser;
				NodeUser *temp1 = new NodeUser;
				GrantPermission(list,temp,temp1);
				delete temp;
				delete temp1;
			}
			else
			{
				cout << "Gioi han quyen he thong" << endl;
			}
			delete temp;
		}
		Pause();
	} while (direct1 != 0);
}
void MenuReader()
{
	system("cls");
	cout << endl;
	cout << "   ************************************" << endl;
	cout << "   |          QUAN LY DOC GIA         |" << endl;
	cout << "   ************************************" << endl;
	cout << "   * 1. Xem danh sach doc gia         *" << endl;
	cout << "   * 2. Them doc gia                  *" << endl;
	cout << "   * 3. Cap nhat thong tin doc gia    *" << endl;
	cout << "   * 4. Xoa doc gia                   *" << endl;
	cout << "   * 5. Tim kiem doc gia theo CMND    *" << endl;
	cout << "   * 6. Tim kiem doc gia theo ten     *" << endl;
	cout << "   * 0. Quay lai                      *" << endl;
	cout << "   ************************************" << endl;
	cout << endl << "Chon chuc nang: ";
}
void RunMenuReader(string SignInUserID, UserList userlist)
{
	int direct1;
	list <Reader> l;

	UpdateReaderList(l);
	do
	{
		MenuReader();
		direct1 = GetDirect();
		if (direct1 == 1)
		{
			DisplayReaderList(l);

		}
		if (direct1 == 2)
		{
			CreateReader(l);
		}
		if (direct1 == 3)
		{
			UpdateReader(l);
		}
		if (direct1 == 4)
		{
			NodeUser *temp = new NodeUser;
			if (CheckManager(SignInUserID, userlist, temp) == true || CheckAdmin(SignInUserID, userlist, temp) == true)
			{
				DeleteReader(l);
			}
			else
			{
				cout << "Gioi han quyen he thong" << endl;
			}
			delete temp;
		}
		if (direct1 == 5)
		{
			SearchReaderCitizenID(l);
		}
		if (direct1 == 6)
		{
			SearchReaderName(l);
		}
		Pause();
	} while (direct1 != 0);

}
void MenuBookManage()
{
	system("cls");
	cout << endl;
	cout << "   ************************************" << endl;
	cout << "   |            QUAN LY SACH          |" << endl;
	cout << "   ************************************" << endl;
	cout << "   * 1. Xem danh sach cac sach        *" << endl;
	cout << "   * 2. Them sach                     *" << endl;
	cout << "   * 3. Cap nhat thong tin sach       *" << endl;
	cout << "   * 4. Xoa sach                      *" << endl;
	cout << "   * 5. Tim kiem sach theo ISBN       *" << endl;
	cout << "   * 6. Tim kiem sach theo ten        *" << endl;
	cout << "   * 0. Quay lai                      *" << endl;
	cout << "   ************************************" << endl;
	cout << endl << "Chon chuc nang: ";
}

void RunMenuBookManage(string SignInUserID, UserList userlist)
{
	int direct1;
	list <Book> b;
	UpdateBookList(b);
	do
	{
		MenuBookManage();
		direct1 = GetDirect();
		if (direct1 == 1)
		{
			NodeUser *temp = new NodeUser;
			if (CheckManager(SignInUserID, userlist, temp) == true || CheckAdmin(SignInUserID, userlist, temp) == true)
			{
				DisplayBookList(b);
			}
			else
			{
				cout << "Gioi han quyen he thong" << endl;
			}
			delete temp;
		}
		if (direct1 == 2)
		{
			NodeUser *temp = new NodeUser;
			if (CheckManager(SignInUserID, userlist, temp) == true || CheckAdmin(SignInUserID, userlist, temp) == true)
			{
				CreateBook(b);
			}
			else
			{
				cout << "Gioi han quyen he thong" << endl;
			}
			delete temp;
		}
		if (direct1 == 3)
		{
			NodeUser *temp = new NodeUser;
			if (CheckManager(SignInUserID, userlist, temp) == true || CheckAdmin(SignInUserID, userlist, temp) == true)
			{
				UpdateBook(b);
			}
			else
			{
				cout << "Gioi han quyen he thong" << endl;
			}
			delete temp;
		}
		if (direct1 == 4)
		{
			NodeUser *temp = new NodeUser;
			if (CheckManager(SignInUserID, userlist, temp) == true || CheckAdmin(SignInUserID, userlist, temp) == true)
			{
				DeleteBook(b);
			}
			else
			{
				cout << "Gioi han quyen he thong" << endl;
			}
			delete temp;
		}
		if (direct1 == 5)
		{
			SearchBookISBN(b);
		}
		if (direct1 == 6)
		{
			SearchBookName(b);
		}
		Pause();
	} while (direct1 != 0);
}
void MenuStatistic()
{
	system("cls");
	cout << endl;
	cout << "   **************************************************" << endl;
	cout << "   |                     THONG KE                   |" << endl;
	cout << "   **************************************************" << endl;
	cout << "   * 1. Thong ke so luong sach                      *" << endl;
	cout << "   * 2. Thong ke so luong sach theo the loai        *" << endl;
	cout << "   * 3. Thong ke so luong doc gia                   *" << endl;
	cout << "   * 4. Thong ke so luong doc gia theo gioi tinh    *" << endl;
	cout << "   * 5. Thong ke so luong sach dang muon            *" << endl;
	cout << "   * 6. Thong ke danh sach doc gia tre han          *" << endl;
	cout << "   * 0. Quay lai                                    *" << endl;
	cout << "   **************************************************" << endl;
	cout << endl << "Chon chuc nang: ";
}
void RunMenuStatistic(string SignInUserID, UserList userlist)
{
	int direct1;
	do
	{
		MenuStatistic();
		direct1 = GetDirect();
		if (direct1 == 1)
		{			
			NodeUser *temp = new NodeUser;
			if (CheckManager(SignInUserID, userlist, temp) == true || CheckAdmin(SignInUserID, userlist, temp) == true)
			{
				BookCount();
			}
			else
			{
				cout << "Gioi han quyen he thong" << endl;
			}
			delete temp; 
		}
		else if (direct1 == 2)
		{
			NodeUser *temp = new NodeUser;
			if (CheckManager(SignInUserID, userlist, temp) == true || CheckAdmin(SignInUserID, userlist, temp) == true)
			{
				CountBookByCategory();
			}
			else
			{
				cout << "Gioi han quyen he thong" << endl;
			}
			delete temp;
		}
		else if (direct1 == 3)
		{
			NodeUser *temp = new NodeUser;
			if (CheckManager(SignInUserID, userlist, temp) == true || CheckAdmin(SignInUserID, userlist, temp) == true)
			{
				ReaderCount();
			}
			else
			{
				cout << "Gioi han quyen he thong" << endl;
			}
			delete temp;
		}
		if (direct1 == 4)
		{
			NodeUser *temp = new NodeUser;
			if (CheckManager(SignInUserID, userlist, temp) == true || CheckAdmin(SignInUserID, userlist, temp) == true)
			{
				CountReaderByGender();
			}
			else
			{
				cout << "Gioi han quyen he thong" << endl;
			}
			delete temp; 
		}
		if (direct1 == 5)
		{
			CountBookBorrowed();
		}
		if (direct1 == 6)
		{
			CountReaderByBorrow();
		}
		Pause();
	} while (direct1 != 0);
}