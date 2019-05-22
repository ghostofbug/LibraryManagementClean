#include "FormAndCharge.h"

void DisplayBorrowBookInfo(BorrowForm Borrowbook)
{
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|      ISBN       |            Ten sach            |          Tac gia          |     NXB      |   Ngay XB  |          The loai         |    Gia    | Muon |" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < Borrowbook.BookBorrowed; i++)
	{
		cout << "| " << setw(15) << left << Borrowbook.Bookname[i].ISBN;
		cout << " | ";
		cout << setw(30) << Borrowbook.Bookname[i].Name;
		cout << " | " << setw(25) << Borrowbook.Bookname[i].Author;
		cout << " | " << setw(12) << Borrowbook.Bookname[i].Publisher;
		cout << " | "; DisplayDay(Borrowbook.Bookname[i].Mfg);
		cout << " | " << setw(25) << Borrowbook.Bookname[i].Category;
		cout << " | " << setw(9) << Borrowbook.Bookname[i].Price;
		cout << " | " << setw(4) << Borrowbook.Bookname[i].Borrowed << " |" << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	}
}
void DisplayBorrowForm(BorrowForm form)
{
	cout << " | " << setw(12) << left << form.FormID;
	cout << " | " << setw(30) << form.Person.Info.Name;
	cout << " | "; DisplayDay(form.Borrowday);
	cout << " ";   DisplayTime(form.TimeCreate);
	cout << " | "; DisplayDay(form.Expectreturnday);
	cout << " ";   DisplayTime(form.ExpectTime);
	for (int j = 0; j < form.BookBorrowed; j++)
	{
		cout << " | " << setw(30) << left << form.Bookname[j].Name;
		cout << " | " << setw(15) << form.Bookname[j].ISBN;
		cout << " | " << setw(4) << form.Bookname[j].Borrowed << " | " << endl;
		if (j < form.BookBorrowed)
		{
			cout << " |              |                                |                     |                    ";
		}
	}
	int y = wherey();
	gotoxy(0, y);
	cout << " -------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}
void DisplayListBorrow(list<BorrowForm>bf)
{
	system("cls");
	list<BorrowForm>::iterator i;
	cout << "   ---------------------------------" << endl;
	cout << "   |      DANH SACH PHIEU MUON      |" << endl;
	cout << "   ---------------------------------" << endl;
	cout << " -------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << " |   Ma phieu   |           Ten doc gia          |      Ngay muon      |  Ngay tra du kien   |            Ten sach            |      ISBN       |  SL  |" << endl;
	cout << " -------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (i = bf.begin(); i != bf.end(); i++)
	{
		DisplayBorrowForm(*i);
	}
}
void PrintForm(BorrowForm &Borrowbook)
{
	system("cls");
	cout << endl;
	cout << "THU VIEN TRUONG DAI HOC KHOA HOC TU NHIEN" << endl;
	cout << "   -----------------------------------" << endl;
	cout << "   |         PHIEU MUON SACH         |" << endl;
	cout << "   -----------------------------------" << endl << endl;
	cout << "Ma phieu     : " << Borrowbook.FormID << endl;
	cout << "Ma doc gia   : " << Borrowbook.Person.ID << endl;
	cout << "Ten doc gia  : " << Borrowbook.Person.Info.Name << endl;
	DisplayBorrowBookInfo(Borrowbook);
	time_t now;
	time(&now);
	tm borrowdate;
	localtime_s(&borrowdate, &now);
	Borrowbook.Borrowday.d = borrowdate.tm_mday;
	Borrowbook.Borrowday.m = borrowdate.tm_mon + 1;

	Borrowbook.Borrowday.y = borrowdate.tm_year + 1900;
	Borrowbook.TimeCreate.Hrs = borrowdate.tm_hour;
	Borrowbook.TimeCreate.Mins = borrowdate.tm_min;
	Borrowbook.TimeCreate.Secs = borrowdate.tm_sec;
	cout << "Ngay muon                : ";
	DisplayTime(Borrowbook.TimeCreate); cout << " ";
	DisplayDay(Borrowbook.Borrowday);
	cout << endl;
	time_t future = now + 604800;
	tm exreturndate;
	localtime_s(&exreturndate, &future);
	Borrowbook.Expectreturnday.d = exreturndate.tm_mday;
	Borrowbook.Expectreturnday.m = exreturndate.tm_mon + 1;
	Borrowbook.Expectreturnday.y = exreturndate.tm_year + 1900;
	Borrowbook.ExpectTime.Hrs = exreturndate.tm_hour;
	Borrowbook.ExpectTime.Mins = exreturndate.tm_min;
	Borrowbook.ExpectTime.Secs = exreturndate.tm_sec;
	cout << "Ngay tra du kien         : ";
	DisplayTime(Borrowbook.ExpectTime); cout << " ";
	DisplayDay(Borrowbook.Expectreturnday);
	cout << endl;
}

bool CheckNullForm(BorrowForm form)
{
	int count = 0;
	for (int j = 0; j < form.BookBorrowed; j++) {
		count = count + form.Bookname[j].Borrowed;
	}
	if (count == 0)
	{
		return true;
	}
	return false;
}
bool CheckIDForm(string ID)
{

	list<BorrowForm>temp;
	BorrowFormToList(temp);
	list<BorrowForm>::iterator i;
	list<BorrowForm>::iterator j = temp.begin();
	list<BorrowForm>::iterator k = temp.end();
	for (i = temp.begin(); i != temp.end(); i++)
	{
		if (ID.compare(i->FormID) == 0)
		{
			temp.erase(j, k);
			return true;
		}
	}
	temp.erase(j, k);
	return false;
}
bool CheckSameIDreader(string getIDreader)
{
	list<BorrowForm>bf;
	BorrowFormToList(bf);
	list<BorrowForm>::iterator i;
	list<BorrowForm>::iterator j = bf.begin();
	list<BorrowForm>::iterator k = bf.end();
	for (i = bf.begin(); i != bf.end(); i++)
	{
		if (getIDreader.compare(i->Person.ID) == 0)
		{
			bf.erase(j, k);
			return false;
		}
	}
	bf.erase(j, k);
	return true;
}
bool CheckSameISBN(BorrowForm temp, string ISBN)
{
	for (int i = 0; i < temp.BookBorrowed; i++)
	{
		if (ISBN.compare(temp.Bookname[i].ISBN) == 0)
		{
			return false;
		}
	}
	return true;
}
int CheckISBNInBorrowForm(string ISBN, BorrowForm form)
{

	bool check = false;
	for (int i = 0; i < 5; i++)
	{
		if (ISBN.compare(form.Bookname[i].ISBN) == 0)
		{
			return i;
		}
	}
	return -1;
}
int CheckNumBer(int num, string ISBN, BorrowForm form)
{
	for (int i = 0; i < form.BookBorrowed; i++)
	{
		if (ISBN.compare(form.Bookname[i].ISBN) == 0 && num <= form.Bookname[i].Borrowed && num != 0)
		{
			return num;
		}
	}
	return -1;
}
bool CheckExpDay(string IDreader)
{
	time_t check;
	time_t now;
	time(&now);
	tm timecheck;
	list<Reader>rd;
	UpdateReaderList(rd);
	list<Reader>::iterator i;
	for (i = rd.begin(); i != rd.end(); i++)
	{
		if (IDreader.compare(i->ID) == 0)
		{
			timecheck.tm_mday = i->Exp.d;
			timecheck.tm_mon = i->Exp.m - 1;
			timecheck.tm_year = i->Exp.y - 1900;
			check = mktime(&timecheck);
			if (check >= now)
			{
				return true;
			}
		}
	}
	return false;
}
int GetQuanTiTy(string ISBN)
{
	int quantity;
	list<Book>rd;
	UpdateBookList(rd);
	list<Book>::iterator i;
	for (i = rd.begin(); i != rd.end(); i++)
	{
		if (ISBN.compare(i->ISBN) == 0)
		{
			quantity = i->Quantity - i->Borrowed;
		}
	}
	return quantity;
}

string FindName(string ISBN, list<Book>b)
{
	UpdateBookList(b);
	list<Book>::iterator i;
	for (i = b.begin(); i != b.end(); i++)
	{
		if (ISBN.compare(i->ISBN) == 0)
		{
			break;
		}
	}
	return i->Name;
}
void CreateBorrowForm(list <BorrowForm> &bf)
{
	system("cls");
	list<Book>b;
	int count = 0;
	string confirm;
	string getIDreader;
	BorrowForm Borrowbook;
	cout << "   -------------------------------------" << endl;
	cout << "   |        LAP PHIEU MUON SACH        |" << endl;
	cout << "   -------------------------------------" << endl;
	cout << "Nhap Ma ID doc gia       : ";
	cin.ignore();
	getline(cin, getIDreader);
	if (CheckCreateReader(getIDreader) == true)
	{
		cout << "Ma doc gia khong ton tai, vui long tao the de muon sach" << endl;
	}
	else if (CheckSameIDreader(getIDreader) == false)
	{
		cout << "Doc gia da muon sach " << endl;
	}
	else if (CheckExpDay(getIDreader) == true)
	{
		cout << "The doc gia da het han" << endl;
	}
	else
	{
		Borrowbook.Person.ID = getIDreader;
		string validate;
		string temp;
		int n = 0;
		FindBorrowInfo(Borrowbook);
		cout << "Ten doc gia              : " << Borrowbook.Person.Info.Name << endl;
		cout << "--------------------------------------------------------------" << endl;
		cout << "LUU Y: Muon toi da 5 dau sach, moi dau sach muon toi da 3 cuon" << endl;
		int y = wherey();
		string text = "Nhap ISBN sach muon   : ";
		int x = static_cast<int>(text.size());
		int i = 0;
		for (;;)
		{
			Borrowbook.BookBorrowed = n;
			cout << "Nhan bat ky de chon sach, nhan 'Y' de hoan tat  :";
			string text1 = "Nhan bat ky de chon sach, nhan 'Y' de hoan tat  :";
			int cor = wherey();
			getline(cin, validate);
			if (n > 5)
			{
				cout << "Vuot qua so dau sach co the muon" << endl;
				break;
			}
			if (validate.compare("Y") == 0 || validate.compare("y") == 0)
			{
				break;
			}
			gotoxy(0, cor);
			for (int z = 0; z < (text1.size() + validate.size()); z++)
			{
				cout << " ";
			}
			gotoxy(0, cor);
			cout << "Nhap ISBN sach muon " << i + 1 << "    : ";
			getline(cin, temp);
			if (CheckISBN(temp) == false && CheckSameISBN(Borrowbook, temp) == true)
			{
				gotoxy(static_cast<int>(text.size() + 3), static_cast<int>(wherey() - 1));
				cout << setw(11) << left << temp << " ";
				cout << setw(15) << "Nhap sach thanh cong" << endl;

				string name = FindName(temp, b);
				cout << "Ten sach                 : " << name << endl;
				cout << "So luong muon (1->3 cuon): ";
				string text2 = "So luong muon (1->3 cuon): ";
				int y = wherey();
				string temp1;
				do
				{
					getline(cin, temp1);
					int x = static_cast<int>(text2.size());
					y = static_cast<int>(y);
					gotoxy(x, y);
				} while (temp1.compare("1") != 0 && temp1.compare("2") != 0 && temp1.compare("3") != 0);
				if (temp1.compare("1") == 0)
				{
					Borrowbook.Bookname[n].Borrowed = 1;
				}
				if (temp1.compare("2") == 0)
				{
					Borrowbook.Bookname[n].Borrowed = 2;
				}
				if (temp1.compare("3") == 0)
				{
					Borrowbook.Bookname[n].Borrowed = 3;
				}
				if (Borrowbook.Bookname[n].Borrowed <= GetQuanTiTy(temp))
				{
					UpDateQuanTiTy(temp, Borrowbook.Bookname[n].Borrowed);
					Borrowbook.Bookname[n].ISBN = temp;
					cout << endl;
					count++;
					n++;
					i++;
				}
				else
				{
					cout << endl;
					cout << "Kho khong du sach!" << endl;
				}
			}
			else
			{
				gotoxy(static_cast<int>(text.size() + 3), static_cast<int>(wherey() - 1));
				cout << setw(11) << left << temp << " ";
				cout << setw(15) << "Ma sach khong ton tai hoac da duoc nhap" << endl;
			}
		}
		Borrowbook.BookBorrowed = n;
		FindBookInfo(Borrowbook, b);
		list<Book>::iterator i1;
		list<Book>::iterator i2;
		i1 = b.begin();
		i2 = b.end();
		b.erase(i1, i2);
		cout << "--------------------------------------------------------------" << endl;
		if (count == 0)
		{
			cout << "Chua co sach nao duoc nhap, khong the lap phieu" << endl;
		}
		else
		{
			do
			{
				Borrowbook.FormID = printRandomString();
			} while (CheckIDForm(Borrowbook.FormID) == false);
			LoadingDot("Dang tai du lieu, xin hay doi trong giay lat");
			PrintForm(Borrowbook);
			cout << "Nhan 'Y' de xac nhan lap phieu muon sach, nhan phim khac de huy bo: ";
			int keypressed = _getch();
			if (keypressed == (int)'Y' || keypressed == (int)'y')
			{
				bf.push_back(Borrowbook);
				BorrowFormToFile(bf);
				cout << "Muon sach thanh cong" << endl;
			}
			else
			{
				cout << endl;
				cout << "Phieu da bi huy" << endl;
			}
		}
	}
	Pause();
}
void FindBookInfo(BorrowForm &Borrowbook, list<Book>b)
{
	UpdateBookList(b);
	list<Book>::iterator i;
	for (i = b.begin(); i != b.end(); i++)
	{
		for (int j = 0; j < Borrowbook.BookBorrowed; j++)
		{
			if (Borrowbook.Bookname[j].ISBN.compare(i->ISBN) == 0)
			{
				unsigned int temp = Borrowbook.Bookname[j].Borrowed;
				Borrowbook.Bookname[j] = *i;
				Borrowbook.Bookname[j].Borrowed = temp;
				Borrowbook.Bookname[j].Quantity = 0;
			}
		}
	}
}
void FindBorrowInfo(BorrowForm &Borrowbook)
{
	list<Reader>l;
	UpdateReaderList(l);
	list<Reader> ::iterator i;
	for (i = l.begin(); i != l.end(); i++)
	{
		if (Borrowbook.Person.ID.compare(i->ID) == 0)
		{
			Borrowbook.Person.Info = i->Info;
			Borrowbook.Person.Exp = i->Exp;
			Borrowbook.Person.Mfg = i->Mfg;
		}
	}
	list<Reader> ::iterator i2;
	i = l.begin();
	i2 = l.end();
	l.erase(i, i2);
}


void BorrowFormToList(list<BorrowForm>&bf)
{
	ifstream fread;
	int size = FileSize("BorrowForm.txt");
	list<Book>b;
	fread.open("BorrowForm.txt");
	for (int i = 0; i < size; i++)
	{
		BorrowForm temp;
		getline(fread, temp.Person.ID, ',');
		fread >> temp.BookBorrowed;
		fread.seekg(1, 1);
		for (int j = 0; j < temp.BookBorrowed; j++)
		{
			getline(fread, temp.Bookname[j].ISBN, ',');
			fread >> temp.Bookname[j].Borrowed;
			fread.seekg(1, 1);
		}
		fread >> temp.TimeCreate.Hrs;
		fread.seekg(1, 1);
		fread >> temp.TimeCreate.Mins;
		fread.seekg(1, 1);
		fread >> temp.TimeCreate.Secs;
		fread.seekg(1, 1);
		fread >> temp.Borrowday.d;
		fread.seekg(1, 1);
		fread >> temp.Borrowday.m;
		fread.seekg(1, 1);
		fread >> temp.Borrowday.y;
		fread.seekg(1, 1);
		fread >> temp.ExpectTime.Hrs;
		fread.seekg(1, 1);
		fread >> temp.ExpectTime.Mins;
		fread.seekg(1, 1);
		fread >> temp.ExpectTime.Secs;
		fread.seekg(1, 1);
		fread >> temp.Expectreturnday.d;
		fread.seekg(1, 1);
		fread >> temp.Expectreturnday.m;
		fread.seekg(1, 1);
		fread >> temp.Expectreturnday.y;
		fread.seekg(1, 1);
		getline(fread, temp.FormID);
		FindBookInfo(temp, b);
		FindBorrowInfo(temp);
		bf.push_back(temp);
	}
	list<Book>::iterator i1;
	list<Book>::iterator i2;
	i1 = b.begin();
	i2 = b.end();
	b.erase(i1, i2);
	fread.close();
}
void BorrowFormToFile(list<BorrowForm>bf)
{
	ofstream fwrite;
	fwrite.open("BorrowForm.txt");
	list<BorrowForm>::iterator i;
	for (i = bf.begin(); i != bf.end(); i++)
	{
		fwrite << i->Person.ID << ",";
		fwrite << i->BookBorrowed << ",";
		for (int j = 0; j < i->BookBorrowed; j++)
		{
			fwrite << i->Bookname[j].ISBN << ",";
			fwrite << i->Bookname[j].Borrowed << ",";
		}
		fwrite << i->TimeCreate.Hrs << "," << i->TimeCreate.Mins << "," << i->TimeCreate.Secs << ",";
		fwrite << i->Borrowday.d << "," << i->Borrowday.m << "," << i->Borrowday.y << ",";
		fwrite << i->ExpectTime.Hrs << "," << i->ExpectTime.Mins << "," << i->ExpectTime.Secs << ",";
		fwrite << i->Expectreturnday.d << "," << i->Expectreturnday.m << "," << i->Expectreturnday.y << ",";
		fwrite << i->FormID;
		fwrite << endl;
	}
	fwrite.close();
}
void BillToList(list<Bill>&BILL)
{
	ifstream fread;
	fread.open("chargebill.txt");
	int size = FileSize("chargebill.txt");
	for (int i = 0; i < size; i++)
	{
		Bill temp;
		getline(fread, temp.BillID, ',');
		getline(fread, temp.Charge.Person.ID, ',');
		fread >> temp.Charge.BookBorrowed;
		fread.seekg(1, 1);
		for (int j = 0; j < temp.Charge.BookBorrowed; j++)
		{
			getline(fread, temp.Charge.Bookname[j].ISBN, ',');
			fread >> temp.Charge.Bookname[j].Borrowed;
			fread.seekg(1, 1);
		}
		fread >> temp.charge;
		fread.seekg(1, 1);
		getline(fread, temp.reason);
		FindBorrowInfo(temp.Charge);
		BILL.push_back(temp);
	}
	fread.close();
}
void BillToFile(list<Bill>BILL)
{
	list<Bill>::iterator i;
	ofstream fwrite;
	fwrite.open("chargebill.txt");
	for (i = BILL.begin(); i != BILL.end(); i++)
	{
		Bill temp = *i;
		fwrite << temp.BillID << ",";
		fwrite << temp.Charge.Person.ID << ",";
		fwrite << temp.Charge.BookBorrowed << ",";
		for (int j = 0; j < temp.Charge.BookBorrowed; j++)
		{
			fwrite << temp.Charge.Bookname[j].ISBN << ",";
			fwrite << temp.Charge.Bookname[j].Borrowed << ",";
		}
		fwrite << temp.charge << ",";
		fwrite << temp.reason << endl;
	}
	fwrite.close();
}
void UpDateQuanTiTy(string ISBN, int n)
{
	list<Book> rd;
	UpdateBookList(rd);
	list<Book>::iterator i;
	list<Book>::iterator j;
	for (i = rd.begin(); i != rd.end(); i++)
	{
		if (ISBN.compare(i->ISBN) == 0)
		{
			i->Borrowed = i->Borrowed + n;
		}
	}
	UpdateBookFile(rd);
	i = rd.begin();
	j = rd.end();
	rd.erase(i, j);
}

void ReturnBook(list<BorrowForm>&bf, list<Bill>BILL)
{
	BorrowForm rb;
	DisplayListBorrow(bf);
	string ID;
	string temp;
	Date returndate;
	Bill bill;
	cin.ignore();
	cout << "Nhap ma phieu muon:  ";
	getline(cin, ID);
	list<BorrowForm>::iterator i;
	i = bf.begin();
	while (i != bf.end())
	{
		if (ID.compare(i->FormID) == 0)
		{
			cout << "Nhap ngay tra      : ";
			int y = wherey();
			returndate = GetDay(static_cast<int>(StringSize("Nhap ngay tra      : ")), static_cast<int>(y));
			Time Return;
			tm Returnday;
			tm ExpectReturn;
			time_t now;
			time(&now);
			localtime_s(&Returnday, &now);
			Return.Hrs = Returnday.tm_hour;
			Return.Mins = Returnday.tm_min;
			Return.Secs = Returnday.tm_sec;
			Returnday.tm_mday = returndate.d;
			Returnday.tm_mon = returndate.m - 1;
			Returnday.tm_year = returndate.y - 1900;
			Returnday.tm_hour = Return.Hrs;
			Returnday.tm_min = Return.Mins;
			Returnday.tm_sec = Return.Secs;
			time_t get = mktime(&Returnday);
			localtime_s(&Returnday, &get);
			ExpectReturn.tm_mday = i->Expectreturnday.d;
			ExpectReturn.tm_mon = i->Expectreturnday.m - 1;
			ExpectReturn.tm_year = i->Expectreturnday.y - 1900;
			ExpectReturn.tm_hour = i->ExpectTime.Hrs;
			ExpectReturn.tm_min = i->ExpectTime.Mins;
			ExpectReturn.tm_sec = i->ExpectTime.Secs;
			time_t take = mktime(&ExpectReturn);
			localtime_s(&ExpectReturn, &take);
			int tong = (get - take) / 86400;
			if (tong >= 1)
			{
				int fee = FeeCharge(tong);
				cout << "Phieu da tre " << tong << endl;
				cout << "So tien phai dong phat: ";
				cout << fee << endl;
				cout << CountNumber(fee) << endl;
				bill.Charge = *i;
				bill.BillID = printRandomNumber();
				bill.charge = static_cast<unsigned long int>(fee + fee * 0.1);
				bill.reason = "Tre han tra sach";
				LoadingDot("Dang tien hanh tao bien lai phat, xin hay doi trong giay lat");
				ChargeBill(bill);
				BILL.push_back(bill);
				BillToFile(BILL);
			}
			else
			{
				cout << "Phieu tra thanh cong" << endl;
			}
			list <Book> b;
			UpdateBookList(b);
			list <Book> ::iterator j;
			for (j = b.begin(); j != b.end(); j++)
			{
				for (int k = 0; k < i->BookBorrowed; k++)
				{
					if (j->ISBN.compare(i->Bookname[k].ISBN) == 0)
					{
						j->Borrowed = j->Borrowed - i->Bookname[k].Borrowed;
					}
				}
			}
			i = bf.erase(i);
			UpdateBookFile(b);
			BorrowFormToFile(bf);
		}
		else
		{
			i++;
		}
	}
	Pause();
}
void LostBook(list<BorrowForm>&bf, list<Bill>BILL)
{
	system("cls");
	cout << "   ---------------------------------" << endl;
	cout << "   |          BAO MAT SACH         |" << endl;
	cout << "   ---------------------------------" << endl;
	int numlost = 0;
	string num;
	string ISBN;
	string FormID;
	Bill bill;
	cout << "Nhap ma phieu muon       : ";
	cin.ignore();
	getline(cin, FormID);
	if (CheckIDForm(FormID) == false)
	{
		cout << "Ma phieu khong ton tai" << endl;
	}
	else {
		cout << " -------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << " |   Ma phieu   |           Ten doc gia          |      Ngay muon      |  Ngay tra du kien   |            Ten sach            |      ISBN       |  SL  |" << endl;
		cout << " -------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		list <BorrowForm> ::iterator k;
		for (k = bf.begin(); k != bf.end(); k++)
		{
			if (CheckIDForm(FormID) == true)
			{
				DisplayBorrowForm(*k);
				break;
			}
		}
		cout << "Nhap ISBN sach mat       : ";
		getline(cin, ISBN);
		int pos = CheckISBNInBorrowForm(ISBN, *k);
		if (pos == -1)
		{
			cout << "Sach khong ton tai trong phieu" << endl;
		}
		else
		{
			for (;;)
			{
				cout << "Nhap so luong sach mat   : ";
				string text2 = "Nhap so luong sach mat   : ";
				int y = wherey();
				getline(cin, num);
				int x = static_cast<int>(text2.size());
				y = static_cast<int>(y);
				if (num.compare("1") == 0)
				{
					numlost = 1;
				}
				else if (num.compare("2") == 0)
				{
					numlost = 2;
				}
				else if (num.compare("3") == 0)
				{
					numlost = 3;
				}
				else
				{
					numlost = 4;
				}
				if (numlost > k->Bookname[pos].Borrowed)
				{
					gotoxy(0, y);
					for (int i = 0; i < text2.size() + num.size(); i++)
					{
						cout << " ";
					}
					gotoxy(0, y);
					cout << "Nhap sai so luong sach duoc muon cua dau sach ";
					_getch();
					gotoxy(0, y);
					for (int i = 0; i < StringSize("Nhap sai so luong sach duoc muon cua dau sach "); i++)
					{
						cout << " ";
					}
					gotoxy(0, y);
				}
				else
				{
					cout << "Nhan 'Y' de xac nhan     : ";
					int keypressed = _getch();
					if (keypressed == (int)'y' || keypressed == (int)'Y')
					{
						k->Bookname[pos].Borrowed = k->Bookname[pos].Borrowed - numlost;
						bill.BillID = printRandomNumber();
						bill.Charge = *k;
						bill.charge = (static_cast<unsigned long int>(numlost * 2 * k->Bookname[pos].Price))*11/10 ;
						bill.reason = "Mat " + num + " cuon " + k->Bookname[pos].Name;
						cout << endl;
						LoadingDot("Dang tai hoa don");
						ChargeBill(bill);
						BorrowFormToFile(bf);
						BILL.push_back(bill);
						BillToFile(BILL);
						list <Book> b;
						UpdateBookList(b);
						list <Book> ::iterator i;
						for (i = b.begin(); i != b.end(); i++)
						{
							if (ISBN.compare(i->ISBN) == 0)
							{
								i->Quantity = i->Quantity - numlost;
								i->Borrowed = i->Borrowed - numlost;
								UpdateBookFile(b);
								break;
							}
						}
					}
					else
					{
						cout << "Thao tac bi huy" << endl;
					}
					break;
				}
			}
		}
		if (CheckNullForm(*k) == true)
		{
			bf.erase(k);
		}
	}
}
void ChargeBill(Bill bill)
{
	system("cls");
	cout << "   ---------------------------------" << endl;
	cout << "   |         HOA DON PHAT          |" << endl;
	cout << "   ---------------------------------" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|  Ma Hoa Don  |          Ten doc gia           |           Li Do            |      Tien Phat      | Thanh Tien (VAT 10%) |" << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "| " << setw(12) << left << bill.BillID;
	cout << " | " << setw(30) << bill.Charge.Person.Info.Name;
	cout << " | " << setw(26) << bill.reason;
	cout << " | " << setw(19) << (bill.charge / 11) * 10;
	cout << " | " <<setw(20)<< bill.charge;
	cout << " | " << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------" << endl;
	_getch();

}
unsigned long int FeeCharge(int elapseday)
{
	unsigned long int fee = 5000;
	fee = fee * elapseday;
	return fee;
}






