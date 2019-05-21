#include "ReaderManage.h"

void DisplayReader(Reader reader)
{
	cout << "| " << setw(8) << left << reader.ID;
	cout << " | " << setw(30) << reader.Info.Name << "| ";
	DisplayDay(reader.Info.Birthday);
	cout << " | ";
	DisplaySex(reader.Info.Sex);
	cout << " | " << setw(12) << reader.Info.CitizenId;
	cout << " | " << setw(25) << reader.Info.Address;
	cout << " | " << setw(25) << reader.Info.Email;
	cout << " | ";
	DisplayDay(reader.Mfg);
	cout << " | ";
	DisplayDay(reader.Exp);
	cout << " |" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}
void DisplayReaderList(list <Reader> l)
{
	system("cls");
	cout << "   ---------------------------------" << endl;
	cout << "   |       DANH SACH DOC GIA       |" << endl;
	cout << "   ---------------------------------" << endl;
	if (l.empty() == true)
	{
		cout << "Danh sach doc gia rong!" << endl;
	}
	else
	{
		cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|  Ma so   |       Ho va ten doc gia       |  Ngay sinh | Gioi |     CMND     |         Dia chi           |           Email           |    Ngay    |    Ngay    |" << endl;
		cout << "|          |                               |            | tinh |              |                           |                           |   lap the  |   het han  |" << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

		list<Reader> ::iterator i;
		for (i = l.begin(); i != l.end(); i++)
		{
			DisplayReader(*i);
		}
	}
}
void DisplayReaderInfo(Reader temp)
{
	cout << "Ma doc gia               : " << temp.ID << endl;
	cout << "Ho va ten doc gia        : " << temp.Info.Name << endl;
	cout << "Ngay sinh                : "; DisplayDay(temp.Info.Birthday); cout << endl;
	cout << "Gioi tinh                : "; DisplaySex(temp.Info.Sex); cout << endl;
	cout << "CMND                     : " << temp.Info.CitizenId << endl;
	cout << "Dia chi                  : " << temp.Info.Address << endl;
	cout << "Email                    : " << temp.Info.Email << endl;
	cout << "===========================================================================" << endl;
}

void UpdateReaderList(list <Reader> &l)
{
	int size = FileSize("reader.txt");
	ifstream fin;
	fin.open("reader.txt");
	for (int i = 0; i < size; i++)
	{
		Reader temp;
		getline(fin, temp.ID, ',');
		getline(fin, temp.Info.Name, ',');
		fin >> temp.Info.Birthday.d;
		fin.seekg(1, 1);
		fin >> temp.Info.Birthday.m;
		fin.seekg(1, 1);
		fin >> temp.Info.Birthday.y;
		fin.seekg(1, 1);
		fin >> temp.Info.Sex;
		fin.seekg(1, 1);
		getline(fin, temp.Info.CitizenId, ',');
		getline(fin, temp.Info.Email, ',');
		getline(fin, temp.Info.Address, ',');
		fin >> temp.Mfg.d;
		fin.seekg(1, 1);
		fin >> temp.Mfg.m;
		fin.seekg(1, 1);
		fin >> temp.Mfg.y;
		fin.seekg(1, 1);
		fin >> temp.Exp.d;
		fin.seekg(1, 1);
		fin >> temp.Exp.m;
		fin.seekg(1, 1);
		fin >> temp.Exp.y;
		string x;
		getline(fin, x, '\n');
		l.push_back(temp);
	}
}
void UpdateReaderFile(list <Reader> l)
{
	list<Reader> ::iterator i;
	for (i = l.begin(); i != l.end(); i++)
	{
		AddReaderToFile(*i);
	}
	remove("reader.txt");
	rename("readernew.txt", "reader.txt");
}
void AddReaderToFile(Reader reader)
{
	ofstream fout;
	fout.open("readernew.txt", ios::app);
	fout << reader.ID << "," << reader.Info.Name << ",";
	fout << reader.Info.Birthday.d << "," << reader.Info.Birthday.m << "," << reader.Info.Birthday.y << ",";
	fout << reader.Info.Sex << "," << reader.Info.CitizenId << "," << reader.Info.Email << "," << reader.Info.Address << ",";
	fout << reader.Mfg.d << "," << reader.Mfg.m << "," << reader.Mfg.y << ",";
	fout << reader.Exp.d << "," << reader.Exp.m << "," << reader.Exp.y << endl;
	fout.close();
}

bool CheckCreateReader(string ID)
{
	ifstream fin;
	fin.open("reader.txt");
	string x;
	while (getline(fin, x, ','))
	{
		if (ID.compare(x) == 0)
		{
			return false;
		}
		getline(fin, x, '\n');
	}
	return true;
}
void CreateReader(list <Reader> &l)
{
	Reader temp;
	system("cls");
	cout << "   ---------------------------------" << endl;
	cout << "   |          THEM DOC GIA         |" << endl;
	cout << "   ---------------------------------" << endl;

	cout << "Nhap ma doc gia: ";
	cin >> temp.ID;
	if (CheckCreateReader(temp.ID) == false)
	{
		cout << "Ma doc gia da ton tai!" << endl;
		temp.ID = "0";
	}
	else
	{
		cin.ignore();
		cout << "Ho va ten                : ";
		getline(cin, temp.Info.Name);
		cout << "Ngay sinh (dd/mm/yyyy)   : ";
		int y = wherey();
		temp.Info.Birthday = GetDay(StringSize("Ngay sinh (dd/mm/yyyy)   : "), y);
		cout << "Gioi tinh (Nam-1 / Nu-0) : ";
		cin >> temp.Info.Sex;
		if (temp.Info.Sex != 1 && temp.Info.Sex != 0)
		{
			temp.Info.Sex = -1;
		}
		cout << "CMND                     : ";
		do {
			cin.ignore();
			getline(cin, temp.Info.CitizenId);
			if (CheckIDCard(temp.Info.CitizenId) == false)
			{
				cout << "CMND nhap sai" << endl;
				cout << "Moi nhap lai" << endl;
			}
		} while (CheckIDCard(temp.Info.CitizenId) == false);
		cout << "Dia chi                  : ";
		getline(cin, temp.Info.Address);
		cout << "Email                    : ";
		getline(cin, temp.Info.Email);
		cout << "Ngay lap the (dd/mm/yyyy): ";
		y = wherey();
		temp.Mfg = GetDay(StringSize("Ngay lap the (dd/mm/yyyy): "), y);
		temp.Exp = PlusDay(temp.Mfg, 0, 48, 0);
		cout << endl << "Nhan 'y' de xac nhan them doc gia, nhan bat ky de huy thao tac: ";
		int check = _getch();
		if (check == (int) 'y')
		{
			AddReaderToList(l, temp);
			cout << endl << "Tao doc gia thanh cong! " << endl;
		}
		else {
			cout << "Thao tac da bi huy!" << endl;
		}
	}
}
void AddReaderToList(list<Reader> &l, Reader reader)
{
	l.push_back(reader);
	UpdateReaderFile(l);
}

void UpdateReaderInfo(list <Reader> &l, string id)
{
	int check = 0;
	list<Reader> ::iterator i;
	for (i = l.begin(); i != l.end(); i++)
	{
		if (id.compare(i->ID) == 0)
		{
			DisplayReaderInfo(*i);
			*i = ChangReaderInfo(*i);
			UpdateReaderFile(l);
			check = 1;
			break;
		}
	}
	if (check == 0) {
		cout << "Doc gia khong ton tai!" << endl;
	}
}
Reader ChangReaderInfo(Reader reader)
{
	cout << "Nhan 'y' de cap nhat thong tin, nhan bat ky de bo qua: ";
	int check;
	check = _getch();
	if (check == (int) 'y')
	{
		Reader temp = reader;
		cout << endl;
		cout << "Ho va ten doc gia        - " << temp.Info.Name << endl;
		check = _getch();
		if (check == (int)'y')
		{
			cout << "Cap nhat ho va ten   : ";
			getline(cin, temp.Info.Name);
		}

		cout << "Ngay sinh                - "; DisplayDay(temp.Info.Birthday); cout << endl;
		check = _getch();
		if (check == (int)'y')
		{
			cout << "Cap nhat ngay sinh   : ";
			int y = wherey();
			temp.Info.Birthday = GetDay(StringSize("Cap nhat ngay sinh   : "), y);
		}
		cout << "Gioi tinh (Nam-1 / Nu-0) - "; DisplaySex(temp.Info.Sex); cout << endl;
		check = _getch();
		if (check == (int)'y')
		{
			cout << "Cap nhat gioi tinh   : ";
			cin >> temp.Info.Sex;
		}
		cout << "CMND                     - " << temp.Info.CitizenId << endl;
		check = _getch();
		if (check == (int)'y')
		{
			cout << "Cap nhat CMND        : ";
			do {
				getline(cin, temp.Info.CitizenId);
				if (CheckIDCard(temp.Info.CitizenId) == false)
				{
					cout << "CMND nhap sai" << endl;
					cout << "Moi nhap lai: ";
				}
			} while (CheckIDCard(temp.Info.CitizenId) == false);
		}
		cout << "Dia chi                  - " << temp.Info.Address << endl;
		check = _getch();
		if (check == (int)'y')
		{
			cout << "Cap nhat dia chi     : ";
			getline(cin, temp.Info.Address);
			cout << endl;
		}
		cout << "Email                    - " << temp.Info.Email << endl;
		check = _getch();
		if (check == (int)'y')
		{
			cout << "Cap nhat email       : ";
			getline(cin, temp.Info.Email);
		}
		cout << "Nhan 'y' de xac nhan thay doi, nhan bat ky de huy thao tac: ";
		check = _getch();
		if (check == (int) 'y')
		{
			cout << "Thong tin da cap nhat!" << endl;
			return temp;
		}
		cout << "Thao tac da bi huy!" << endl;
	}
	else {
		cout << "Thao tac da bi huy!" << endl;
	}
	return reader;
}
void UpdateReader(list <Reader> &l)
{
	system("cls");
	cout << "   ---------------------------------" << endl;
	cout << "   |   CAP NHAT THONG TIN DOC GIA  |" << endl;
	cout << "   ---------------------------------" << endl;
	if (l.empty() == true)
	{
		cout << "Danh sach doc gia rong!" << endl;
	}
	else
	{
		cout << "Nhap ma doc gia: ";
		string s;
		cin.ignore();
		getline(cin, s);
		UpdateReaderInfo(l, s);
	}
}

void DelReader(list <Reader> &l, string id)
{
	list<Reader> ::iterator i;
	for (i = l.begin(); i != l.end(); i++)
	{
		if (id.compare(i->ID) == 0)
		{
			DisplayReaderInfo(*i);
			cout << "Nhan 'y' de xoa thong tin, nhan bat ky de huy thao tac : ";
			int check;
			check = _getch();
			{
				if (check == 'y')
				{
					l.erase(i);
					UpdateReaderFile(l);
					cout << "Doc gia da bi xoa!" << endl;
				}
				else {
					cout << "Thao tac da bi huy!" << endl;
				}
			}
			break;
		}
	}
}
void DeleteReader(list <Reader> &l)
{
	system("cls");
	cout << "   ---------------------------------" << endl;
	cout << "   |          XOA DOC GIA          |" << endl;
	cout << "   ---------------------------------" << endl;
	if (l.empty() == true)
	{
		cout << "Danh sach doc gia rong!" << endl;
	}
	else
	{
		cout << "Nhap ma doc gia: ";
		string s;
		cin.ignore();
		getline(cin, s);
		DelReader(l, s);
	}
}

int SearchCitizenID(list <Reader> l, string id)
{
	int check = 1;
	list<Reader> ::iterator i;
	for (i = l.begin(); i != l.end(); i++)
	{
		if (id.compare(i->Info.CitizenId) == 0)
		{
			DisplayReaderInfo(*i);
			check = 0;
		}
	}
	return check;
}
void SearchReaderCitizenID(list <Reader> l)
{
	system("cls");
	cout << "   ---------------------------------" << endl;
	cout << "   |      TIM DOC GIA THEO CMND    |" << endl;
	cout << "   ---------------------------------" << endl;
	if (l.empty() == true)
	{
		cout << "Danh sach doc gia rong!" << endl;
	}
	else
	{
		cout << "Nhap CMND doc gia: ";
		string s;
		cin.ignore();
		getline(cin, s);
		if (SearchCitizenID(l, s) != 0)
		{
			cout << "Khong tim thay doc gia!" << endl;
		}
	}
}

int SearchName(list <Reader> l, string name)
{
	int check = 1;
	list<Reader> ::iterator i;
	for (i = l.begin(); i != l.end(); i++)
	{
		if (i->Info.Name.find(name, 0) != string::npos)
		{
			DisplayReaderInfo(*i);
			check = 0;
		}
	}
	return check;
}
void SearchReaderName(list <Reader> l)
{
	system("cls");
	cout << "   ---------------------------------" << endl;
	cout << "   |      TIM DOC GIA THEO TEN     |" << endl;
	cout << "   ---------------------------------" << endl;
	if (l.empty() == true)
	{
		cout << "Danh sach doc gia rong!" << endl;
	}
	else
	{
		cout << "Nhap ten doc gia: ";
		string s;
		cin.ignore();
		getline(cin, s);
		if (SearchName(l, s) != 0)
		{
			cout << "Khong tim thay doc gia!" << endl;
		}
	}
}
