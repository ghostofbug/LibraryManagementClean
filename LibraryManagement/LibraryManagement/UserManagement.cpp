#include "UserManagement.h"

User Admin()
{
	User admin;
	admin.UserId = "useradmin";
	admin.PassWord = "4638";
	admin.Pos = 1;
	admin.Info.Birthday.d = 1;
	admin.Info.Birthday.m = 1;
	admin.Info.Birthday.y = 1;
	admin.Info.Address = "ThuVienKHTN";
	admin.Info.Email = "ThuVien@gmail";
	admin.Info.CitizenId = "000000000";
	admin.Info.Sex = -1;
	admin.Info.Name = "DoAnKTLT";
	admin.Stats = 0;
	return admin;
}
void CreateAdmin(UserList &list, User ADmin, NodeUser *NodeAdmin)
{
	if (FileSize("systemadmin.txt") == 0)
	{
		ADmin = Admin();
		NodeAdmin = AddUser(ADmin);
		AddTail(list, NodeAdmin);
		ofstream addadmin;
		addadmin.open("systemadmin.txt");
		addadmin << NodeAdmin->node.UserId << "," << EncryptPassWord(NodeAdmin->node.PassWord) << "," << NodeAdmin->node.Info.Name << ",";
		addadmin << NodeAdmin->node.Info.Email << "," << NodeAdmin->node.Info.Address << "," << NodeAdmin->node.Info.CitizenId << ",";
		addadmin << NodeAdmin->node.Info.Birthday.d << "," << NodeAdmin->node.Info.Birthday.m << "," << NodeAdmin->node.Info.Birthday.y << "," << NodeAdmin->node.Info.Sex << ",";
		addadmin << NodeAdmin->node.Pos << "," << NodeAdmin->node.Stats << endl;
		addadmin.close();
	}
	else
	{
		ifstream addamin;
		User admin;
		addamin.open("systemadmin.txt");
		getline(addamin, admin.UserId, ',');
		getline(addamin, admin.PassWord, ',');
		admin.PassWord = EncryptPassWord(admin.PassWord);
		getline(addamin, admin.Info.Name, ',');
		getline(addamin, admin.Info.Email, ',');
		getline(addamin, admin.Info.Address, ',');
		admin.Info.Address = EncryptPassWord(admin.Info.Address);
		getline(addamin, admin.Info.CitizenId, ',');
		addamin >> admin.Info.Birthday.d;
		addamin.seekg(1, 1);
		addamin >> admin.Info.Birthday.m;
		addamin.seekg(1, 1);
		addamin >> admin.Info.Birthday.y;
		addamin.seekg(1, 1);
		addamin >> admin.Info.Sex;
		addamin.seekg(1, 1);
		addamin >> admin.Pos;
		addamin.seekg(1, 1);
		addamin >> admin.Stats;
		NodeAdmin = AddUser(admin);
		AddTail(list, NodeAdmin);
		addamin.close();
	}
}
void InitializeUserList(UserList &list)
{
	list.listhead = list.listtail = NULL;
}
void AddTail(UserList &list, NodeUser *user)
{
	if (list.listhead == NULL)
	{
		list.listhead = list.listtail = user;
	}
	else
	{
		list.listtail->next = user;
		list.listtail = user;
	}
}
NodeUser *AddUser(User user)
{
	NodeUser *nodeuser = new NodeUser;
	if (nodeuser == NULL)
	{
		cout << "dang ky that bai" << endl;
		return NULL;
	}
	else
	{
		nodeuser->node = user;
		nodeuser->next = NULL;
	}
	return nodeuser;
}
User Register(UserList list)
{
	User user;
	cout << "LUU Y: Cac thong tin (*) la bat buoc, cac thong tin khac co the bo qua " << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << "(*) Ten nguoi dung       : ";
	getline(cin, user.Info.Name);
	cout << "(*) Ten dang nhap        : ";
	getline(cin, user.UserId);
	NodeUser *temp = new NodeUser;
	if (CheckCreateAccount(list, user.UserId, temp) == false)
	{
		cout << "Ten dang nhap da ton tai, moi dang ky lai" << endl;

	}
	else
	{
		cout << "(*) Mat khau             : ";
		int y = wherey();
		user.PassWord = HidePassword(wherex(), y);
		cout << "" << endl;
		if (CheckSame(user.UserId, user.PassWord) == false)
		{
			cout << "Mat khau trung ten dang nhap, moi dang ky lai!" << endl;
		}
		else
		{
			string text = "(*) Ngay sinh(dd/mm/yyyy): ";
			cout << text;
			int y = wherey();
			y = static_cast<int>(y);
			int x = static_cast<int>(text.size());
			user.Info.Birthday = GetDay(x, y);
			cout << "Gioi tinh (0:nu /1:nam)  : ";
			string text1 = "Gioi tinh (0:nu /1:nam)  : ";
			string sex;
			y = wherey();
			y = static_cast<int>(y);
			x = static_cast<int>(text1.size());
			while (sex.compare("1") != 0 && sex.compare("0") != 0 && sex.compare("-1") != 0)
			{
				gotoxy(x, y);
				getline(cin, sex);
			}

			if (sex.compare("1") == 0)
			{
				user.Info.Sex = 1;
			}
			else if (sex.compare("0") == 0)
			{
				user.Info.Sex = 0;
			}
			else
			{
				user.Info.Sex = -1;
			}
			cout << "(*) CMND (9 hoac 12 so)  : ";
			y = wherey();
			do {
				getline(cin, user.Info.CitizenId);
				if (CheckIDCard(user.Info.CitizenId) == false)
				{
					gotoxy(StringSize("(*) CMND (9 hoac 12 so)  : "), y);
				}
			} while (CheckIDCard(user.Info.CitizenId) == false);
			cout << "Dia chi                  : ";
			getline(cin, user.Info.Address);
			cout << "Email                    : ";
			getline(cin, user.Info.Email);
			user.Stats = 1;
			cout << "Dang ky thanh cong!" << endl << "Tai khoan dang bi khoa!" << endl;
		}
	}
	delete temp;
	return user;
}
void GrantPermission(UserList &list, NodeUser * temp, NodeUser *temp1)
{

	system("cls");
	int runtime = 0;
	for (;;)
	{
		bool check = false;
		system("cls");
		cout << "   ---------------------------------" << endl;
		cout << "   |      DANH SACH NGUOI DUNG     |" << endl;
		cout << "   ---------------------------------" << endl;
		cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|     UserID      |    Password     |     CMND     |       Dia chi        |        Email         |  Chuc vu  | Tinh trang |" << endl;
		cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
		for (temp = list.listhead; temp != NULL; temp = temp->next)
		{
			cout << "| ";
			cout << setw(15) << left << temp->node.UserId;
			cout << " | ";
			cout << setw(15) << HidePassWordV2(temp->node.PassWord);
			cout << " | ";
			cout << setw(12) << temp->node.Info.CitizenId;
			cout << " | ";
			cout << setw(20) << temp->node.Info.Address;
			cout << " | ";
			cout << setw(20) << temp->node.Info.Email;
			cout << " | ";
			if (temp->node.Stats == 0)
			{
				if (temp->node.Pos == 1)
				{
					cout << setw(9) << "Admin";
				}
				else if (temp->node.Pos == 0)
				{
					cout << setw(9) << "Quan ly";
				}
				else
				{
					cout << setw(9) << "Nhan vien";
				}
				cout << " | ";
				cout << setw(10) << "Activated";
			}
			else
			{
				cout << setw(9) << " ";
				cout << " | ";
				cout << setw(10) << "Blocked";
			}
			cout << " |" << endl;
			cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
		}
		string text;
		string validate;
		int y = wherey();
		
		cout << "Nhan Y de phan quyen,nhan bat ky de thoat: ";
		if (runtime == 0)
		{
			cin.ignore();
		}
		getline(cin, validate);
		if (validate.compare("y") == 0 || validate.compare("Y") == 0)
		{
			gotoxy(0, y);
			for (int i = 0; i < (StringSize("Nhan Y de phan quyen,nhan bat ky de thoat: ") + StringSize(validate)); i++)
			{
				cout << " ";
			}
			gotoxy(0, y);
			cout << "Nhap UserId can phan quyen: ";
			getline(cin, text);
			for (temp1 = list.listhead; temp1 != NULL; temp1 = temp1->next)
			{
				NodeUser* temp2 = new NodeUser;
				if (text.compare(temp1->node.UserId) == 0 && CheckAdmin(temp1->node.UserId, list, temp2) == false)
				{
					cout << "Phan quyen (0: Quan ly /-1: Nhan vien /so khac: khoa tai khoan): ";
					string text = "Phan quyen (0: Quan ly /-1: Nhan vien /so khac: khoa tai khoan): ";
					COORD coord;
					coord.X = wherex();
					coord.Y = wherey();
					while (!(cin >> temp1->node.Pos))
					{
						gotoxy(coord.X, coord.Y);
						cin.clear();
						cin.ignore();
					}
					if (temp1->node.Pos != 0 && temp1->node.Pos != -1)
					{
						temp1->node.Stats = 1;
						temp1->node.Pos = -2;
					}
					else
					{
						temp1->node.Stats = 0;
					}
					ListToFile(list);
					check = true;
					cin.ignore();
				}
			}
			if (check == false)
			{
				cout << "Khong the thuc hien! Nguoi dung la Admin/khong ton tai!" << endl;
				system("pause");
			}
			runtime++;
		}
		else
		{
			break;
		}
	}
}
void DeleteList(UserList &list)
{
	NodeUser *temp1 = list.listhead;
	NodeUser *temp2 = NULL;
	while (temp1 != NULL)
	{
		temp2 = temp1->next;
		delete temp1;
		temp1 = temp2;
	}
	delete temp2;
	list.listhead = NULL;
}

bool CheckCreateAccount(UserList list, string registeruser, NodeUser *temp)
{
	if (list.listhead == NULL)
	{
		return true;
	}
	else
	{
		for (temp = list.listhead; temp != NULL; temp = temp->next)
		{
			if (temp->node.UserId.compare(registeruser) == 0)
			{

				return false;
			}
		}
	}
	return true;
}
bool CheckSame(string username, string password)
{
	if (username.compare(password) == 0)
	{
		return false;
	}
	return true;
}
bool CheckIDCard(string ID)
{
	int check = CountIDCard(ID);
	if (check == 12 || check == 9)
	{
		if (check == ID.length())
		{
			return true;
		}
	}
	return false;
}
int CountIDCard(string ID)
{

	int count = 0;
	for (int i = 0; i < ID.length(); i++)
	{
		if (ID[i] >= '0' && ID[i] <= '9')
		{
			count++;
		}
	}
	return count;
}
bool CheckAdmin(string signinuser, UserList list, NodeUser *temp)
{
	for (temp = list.listhead; temp != NULL; temp = temp->next)
	{
		if (signinuser.compare(temp->node.UserId) == 0 && temp->node.Pos == 1)
		{
			return true;
		}
	}
	return false;
}
bool CheckManager(string signinuser, UserList list, NodeUser *temp)
{
	for (temp = list.listhead; temp != NULL; temp = temp->next)
	{
		if (signinuser.compare(temp->node.UserId) == 0 && temp->node.Pos == 0)
		{
			return true;
		}
	}
	return false;
}
bool CheckBlocked(string signinuser, UserList list, NodeUser *temp)
{
	for (temp = list.listhead; temp != NULL; temp = temp->next)
	{
		if ((signinuser.compare(temp->node.UserId) == 0 && temp->node.Stats == 0))
		{
			return true;
		}
	}
	return false;
}

void AddUserToList(UserList &list, User user, NodeUser *User)
{
	User = AddUser(user);
	AddTail(list, User);
	ListToFile(list);
}
void ListToFile(UserList list)
{
	ofstream addfile;
	NodeUser *temp = new NodeUser;
	addfile.open("useraccount.txt");
	for (temp = list.listhead; temp != NULL; temp = temp->next)
	{
		if (temp->node.Pos == 1 && temp->node.UserId.compare("useradmin") == 0)
		{
			ofstream addadmin;
			addadmin.open("systemadmin.txt");
			addadmin << temp->node.UserId << "," << EncryptPassWord(temp->node.PassWord) << "," << temp->node.Info.Name << ",";
			addadmin << temp->node.Info.Email << "," << EncryptPassWord(temp->node.Info.Address) << "," << temp->node.Info.CitizenId << ",";
			addadmin << temp->node.Info.Birthday.d << "," << temp->node.Info.Birthday.m << "," << temp->node.Info.Birthday.y << "," << temp->node.Info.Sex << "," << temp->node.Pos << "," << temp->node.Stats << endl;
			addadmin.close();
		}
		else
		{

			addfile << temp->node.UserId << "," << EncryptPassWord(temp->node.PassWord) << ",";
			addfile << temp->node.Info.CitizenId << ",";
			addfile << EncryptPassWord(temp->node.Info.Address) << ",";
			addfile << temp->node.Info.Email << ",";
			addfile << temp->node.Info.Name << ",";
			addfile << temp->node.Info.Birthday.d << "," << temp->node.Info.Birthday.m << "," << temp->node.Info.Birthday.y << ",";
			addfile << temp->node.Info.Sex << "," << temp->node.Pos << "," << temp->node.Stats << endl;
		}

	}
	addfile.close();
	delete temp;
}
void AddFileTolist(UserList &list, NodeUser *user)
{
	User temp;
	ifstream adddata;
	int n = FileSize("useraccount.txt");
	adddata.open("useraccount.txt");
	for (int i = 0; i < n; i++)
	{
		getline(adddata, temp.UserId, ',');
		getline(adddata, temp.PassWord, ',');
		temp.PassWord = EncryptPassWord(temp.PassWord);
		getline(adddata, temp.Info.CitizenId, ',');
		getline(adddata, temp.Info.Address, ',');
		temp.Info.Address = EncryptPassWord(temp.Info.Address);
		getline(adddata, temp.Info.Email, ',');
		getline(adddata, temp.Info.Name, ',');
		adddata >> temp.Info.Birthday.d;
		adddata.seekg(1, 1);
		adddata >> temp.Info.Birthday.m;
		adddata.seekg(1, 1);
		adddata >> temp.Info.Birthday.y;
		adddata.seekg(1, 1);
		adddata >> temp.Info.Sex;
		adddata.seekg(1, 1);
		adddata >> temp.Pos;
		adddata.seekg(1, 1);
		adddata >> temp.Stats;
		string x;
		getline(adddata, x, '\n');
		user = AddUser(temp);
		AddTail(list, user);
	}
	adddata.close();
}

void DisplayUserInfo(UserList list, string signinuser)
{
	NodeUser *temp = new NodeUser;
	for (temp = list.listhead; temp != NULL; temp = temp->next)
	{
		if (temp->node.UserId.compare(signinuser) == 0)
		{
			cout << "Ten nguoi dung		 : " << temp->node.Info.Name << endl;
			cout << "Gioi tinh                : ";
			DisplaySex(temp->node.Info.Sex);
			cout << endl;
			cout << "Email                    : " << temp->node.Info.Email << endl;
			cout << "Dia chi                  : " << temp->node.Info.Address << endl;
			cout << "Ngay sinh                : ";
			DisplayDay(temp->node.Info.Birthday);
			cout << endl;
			cout << "CMND(khong the sua)      : " << temp->node.Info.CitizenId << endl;
			cout << "===========================================================================" << endl;
		}
	}
}