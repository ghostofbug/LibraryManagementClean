#include "FormAndCharge.h"
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
void UpDateQuanTiTy(string ISBN,int n)
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
bool CheckNumBer(int num,string ISBN,string ID)
{
	
	list<BorrowForm>temp;
	list<BorrowForm>::iterator i;
	BorrowFormToList(temp);
	for (i = temp.begin(); i != temp.end(); i++)
	{
		if (ID.compare(i->FormID)==0)
		{
			for (int j = 0; j < i->BookBorrowed; j++)
			{
				if (ISBN.compare(i->Bookname[j].ISBN) == 0 && num <= i->Bookname[j].Borrowed && num!=0)
				{
					return true;
				}
			}
		}
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
bool CheckISBNInBorrowForm(string ISBN,string ID)
{
	bool check = false;
	list<BorrowForm>temp;
	BorrowFormToList(temp);
	list<BorrowForm>::iterator i;
	list<BorrowForm>::iterator j = temp.begin();
	list<BorrowForm>::iterator k = temp.end();
	for (i = temp.begin(); i != temp.end(); i++)
	{
		if (ID.compare(i->FormID) == 0)
		{
			for (int j = 0; j < i->BookBorrowed; j++)
			{
				if (ISBN.compare(i->Bookname[j].ISBN) == 0)
				{
					check = true;
				}
			}
		}
		if (check == true)
		{
			temp.erase(j, k);
			return true;
		}
	}
	temp.erase(j, k);
	return false;
}
void LostBook(list<BorrowForm>&bf,list<Bill>BILL)
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
	else
	{
		cout << "Nhap ISBN sach mat       : ";
		getline(cin, ISBN);
		if (CheckISBNInBorrowForm(ISBN,FormID) == false)
		{
			cout << "Sach khong ton tai trong phieu" << endl;
		}
		else
		{
			for (;;)
			{
				cout << "Nhap so luong sach mat   :  ";
				string text2 = "Nhap so luong sach mat   :  ";
				int y = wherey();
				//do
				//{
					getline(cin, num);
					int x = static_cast<int>(text2.size());
					y = static_cast<int>(y);
					//gotoxy(x, y);
				//} while ((num.compare("1") != 0 && num.compare("2") != 0 && num.compare("3") != 0));
				if (num.compare("1") == 0)
				{
					numlost = 1;
				}
				if (num.compare("2") == 0)
				{
					numlost = 2;
				}
				if (num.compare("3") == 0)
				{
					numlost = 3;
				}
				else if (num.compare("1") != 0 && num.compare("2") != 0 && num.compare("3") != 0)
				{
					numlost = 10;
				}
				if (CheckNumBer(numlost, ISBN, FormID) == false)
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
				else if (CheckNumBer(numlost, ISBN, FormID) == true)
				{
					break;
				}
			}
			cout << "nhap Y de xac nhan: ";
			int keypressed = _getch();
			if (keypressed == (int)'y' || keypressed == (int)'Y')
			{
				list<BorrowForm>::iterator i;
				for (i = bf.begin(); i != bf.end(); i++)
				{
					if (FormID.compare(i->FormID) == 0)
					{
						for (int j = 0; j < i->BookBorrowed; j++)
						{
							if (ISBN.compare(i->Bookname[j].ISBN) == 0)
							{
								i->Bookname[j].Borrowed = i->Bookname[j].Borrowed - numlost;
								bill.BillID = printRandomNumber();
								bill.Charge = *i;
								bill.charge = (static_cast<unsigned long int>(numlost * 2 * i->Bookname[j].Price)) + (static_cast<unsigned long int>(numlost * 2 * i->Bookname[j].Price))*0.1;
								bill.reason = "Mat " + num + "cuon " + i->Bookname[j].Name;
							}
						}
					}
				}
				LoadingDot("Dang tai hoa don");
				ChargeBill(bill);
				BorrowFormToFile(bf);
				BILL.push_back(bill);
				BillToFile(BILL);
			}
			else
			{
				cout << "Thao tac bi huy" << endl;
			}
		}
	}

	
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
		BorrowForm temp = *i;
		if (getIDreader.compare(temp.Person.ID) == 0)
		{
			bf.erase(j, k);
			return false;
		}
	}
	bf.erase(j, k);
	return true;
}
bool CheckSameISBN(BorrowForm temp,string ISBN)
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
void ChargeBill(Bill bill)
{
	system("cls");
	cout << "   ---------------------------------" << endl;
	cout << "   |         HOA DON PHAT          |" << endl;
	cout << "   ---------------------------------" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|  Ma Hoa Don  |          Ten doc gia           |           Li Do            |      Tien Phat      |   Thanh Tien (da VAT)  |" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "| " << setw(12) << left << bill.BillID;
	cout << " | ";
	cout << setw(30) << bill.Charge.Person.Info.Name;
	cout << " | " << setw(26) << bill.reason;
	cout << " | " << setw(19) << (bill.charge * 100) / 110;
	cout << " | " <<setw(20)<< bill.charge;
	cout << " | " << endl;
	_getch();
}
unsigned long int FeeCharge(int elapseday)
{
	unsigned long int fee = 5000;
	fee = fee * elapseday;
	return fee;
}
bool CheckID(string ID,list<BorrowForm>bf)
{
	list<BorrowForm>::iterator i;
	for (i = bf.begin(); i!= bf.end(); i++)
	{
		BorrowForm temp;
		temp.FormID = i->FormID;
		if (ID.compare(temp.FormID) == 0)
		{
			return true;
		}
	}
	return false;
}
bool CheckSameID(string ID)
{
	list<BorrowForm>bf;
	BorrowFormToList(bf);
	list<BorrowForm>::iterator i;
	BorrowForm temp;
	for (i = bf.begin(); i != bf.end(); i++)
	{
		temp.FormID = i->FormID;
		if (ID.compare(temp.FormID) == 0)
		{
			return false;
		}
	}
	return true;
}
void ReturnBook(list<BorrowForm>&bf,list<Bill>BILL)
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
	
	//for (i = bf.begin(); i != bf.end(); i++)
	while (i!=bf.end())
	{
		BorrowForm temp = *i;
		temp.FormID = i->FormID;
		if (ID.compare(temp.FormID) == 0)
		{
			cout << "Nhap ngay tra: ";
			int y = wherey();
			returndate = GetDay(static_cast<int>(StringSize("Nhap ngay tra : ")), static_cast<int>(y));
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
			ExpectReturn.tm_mday = temp.Expectreturnday.d;
			ExpectReturn.tm_mon = temp.Expectreturnday.m-1;
			ExpectReturn.tm_year = temp.Expectreturnday.y-1900;
			ExpectReturn.tm_hour = temp.ExpectTime.Hrs;
			ExpectReturn.tm_min = temp.ExpectTime.Mins;
			ExpectReturn.tm_sec = temp.ExpectTime.Secs;
			time_t take = mktime(&ExpectReturn);
			localtime_s(&ExpectReturn, &take);
			int tong = (get - take)/86400;
			if (tong >= 1)
			{
				int fee = FeeCharge(tong);
				cout << "Phieu da tre " << tong << endl;
				cout << "so tien phai dong phat: ";
				cout << fee << endl;
				cout << CountNumber(fee) << endl;
				bill.Charge = temp;
				bill.BillID = printRandomNumber();
				bill.charge =static_cast<unsigned long int>(fee + fee * 0.1);
				bill.reason = "Tre han tra sach";
				LoadingDot("Dang tien hanh tao bien lai phat, xin hay doi trong giay lat");
				ChargeBill(bill);
				i = bf.erase(i);
				BorrowFormToFile(bf);
				BILL.push_back(bill);
				BillToFile(BILL);
			}
			else
			{
				cout << "Phieu tra thanh cong" << endl;
				i = bf.erase(i);
				BorrowFormToFile(bf);
			}
		}
		else
		{
			i++;
		}
	}
	
}
void DisplayListBorrow(list<BorrowForm>bf)
{
	system("cls");
	list<BorrowForm>::iterator i;
	cout << "   ---------------------------------" << endl;
	cout << "   |      DANH SACH PHIEU MUON      |" << endl;
	cout << "   ---------------------------------" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|    FormID   |            Ten doc gia        |            Ngay muon            |        Ngay tra du kien           |         Ten sach        |     ISBN     |  SL  |" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (i = bf.begin(); i != bf.end(); i++)
	{
		BorrowForm temp;
		temp.Borrowday = i->Borrowday;
		temp.Person.ID = i->Person.ID;
		temp.Expectreturnday = i->Expectreturnday;
		temp.Person.Info.Name = i->Person.Info.Name;
		temp.TimeCreate = i->TimeCreate;
		temp.ExpectTime = i->ExpectTime;
		temp.FormID = i->FormID;
		cout << "| " << setw(12) << left << temp.FormID;
		cout << "|";
		cout << setw(31) << temp.Person.Info.Name;
		temp.BookBorrowed = i->BookBorrowed;
		cout << "|" << temp.Borrowday.d << "/" << temp.Borrowday.m << "/" << temp.Borrowday.y << " ";
		DisplayTime(temp.TimeCreate);
		cout << setw(15) << right << " | " << temp.Expectreturnday.d << "/" << temp.Expectreturnday.m << "/" << temp.Expectreturnday.y << " ";
		DisplayTime(temp.ExpectTime);
		//cout << setw(-6) << left;
		cout << setw(15)<<"|" << right;
		for (int j = 0; j <temp.BookBorrowed ; j++)
		{
			temp.Bookname[j].Name = i->Bookname[j].Name;
			temp.Bookname[j].ISBN = i->Bookname[j].ISBN;
			temp.Bookname[j].Borrowed = i->Bookname[j].Borrowed;
			cout <<setw(25)<<left<<temp.Bookname[j].Name;
			cout << "|" << temp.Bookname[j].ISBN;
			int space = static_cast<int>(15 - temp.Bookname[j].ISBN.size());
			space = static_cast<int>(space);
			for (int i=0;i<space;i++)
			{
				cout << " ";
			}
			cout<<temp.Bookname[j].Borrowed << "|" << endl;
			cout << "                                                                                                                     ";
			 
			
		}
	
		int y = wherey();
		gotoxy(0, y);
		cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	}
}
void BorrowFormToList(list<BorrowForm>&bf)
{
	ifstream fread;
	int size = FileSize("BorrowForm.txt");
	list<Book>b;
	fread.open("BorrowForm.txt");
	for (int i = 0; i <size; i++)
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
		BorrowForm temp;
		temp.Person.ID = i->Person.ID;
		temp.BookBorrowed = i->BookBorrowed;
		fwrite << temp.Person.ID << ",";
		fwrite << temp.BookBorrowed << ",";
		for (int j = 0; j < temp.BookBorrowed; j++)
		{
			temp.Bookname[j].ISBN = i->Bookname[j].ISBN;
			temp.Bookname[j].Borrowed = i->Bookname[j].Borrowed;
			fwrite << temp.Bookname[j].ISBN << ",";
			fwrite << temp.Bookname[j].Borrowed << ",";
		}
		temp.Borrowday = i->Borrowday;
		temp.Expectreturnday = i->Expectreturnday;
		temp.TimeCreate = i->ExpectTime;
		temp.ExpectTime = i->ExpectTime;
		temp.FormID = i->FormID;
		fwrite << temp.TimeCreate.Hrs << "," << temp.TimeCreate.Mins << "," << temp.TimeCreate.Secs << ",";
		fwrite << temp.Borrowday.d << "," << temp.Borrowday.m << "," << temp.Borrowday.y << ",";
		fwrite << temp.ExpectTime.Hrs << "," << temp.ExpectTime.Mins << "," << temp.ExpectTime.Secs << ",";
		fwrite << temp.Expectreturnday.d << "," << temp.Expectreturnday.m << "," << temp.Expectreturnday.y << ",";
		fwrite << temp.FormID;
		fwrite << endl;
	}
	fwrite.close();
}
void DisplayBorrowBookInfo(BorrowForm Borrowbook)
{
	cout << "   ---------------------------------" << endl;
	cout << "   |         DANH SACH SACH        |" << endl;
	cout << "   ---------------------------------" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|      ISBN       |            Ten sach            |          Tac gia          |     NXB      |   Ngay XB  |          The loai         |    Gia    | Muon |" << endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (int i=0;i<Borrowbook.BookBorrowed;i++)
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
		cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	}
}
string FindName(string ISBN, list<Book>b)
{
	string name;
	UpdateBookList(b);
	list<Book>::iterator i;
	for (i = b.begin(); i != b.end(); i++)
	{
		if (ISBN.compare(i->ISBN) == 0)
		{
			name = i->Name;
		}
	}
	return name;
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
				Borrowbook.Bookname[j].Author = i->Author;
				Borrowbook.Bookname[j].Category = i->Category;
				Borrowbook.Bookname[j].Name = i->Name;
				Borrowbook.Bookname[j].Publisher = i->Publisher;
				Borrowbook.Bookname[j].Mfg = i->Mfg;
				Borrowbook.Bookname[j].Price = i->Price;
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
	l.erase(i,i2);
}
void PrintForm(BorrowForm &Borrowbook)
{
	system("cls");
	cout << "Thu vien truong Dai Hoc Khoa Hoc Tu Nhien" << endl;
	cout << endl;
	cout << "Ma phieu: " << Borrowbook.FormID << endl;
	cout << "   ************************************" << endl;
	cout << "   |         Phieu muon sach          |" << endl;
	cout << "   ************************************" << endl;
	cout << "Ma doc gia   : " << Borrowbook.Person.ID << endl;
	cout << "Ten doc gia  : " << Borrowbook.Person.Info.Name << endl;
	cout << "---------------------------------------" << endl;
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
	DisplayTime(Borrowbook.TimeCreate);
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
	DisplayTime(Borrowbook.ExpectTime);
	DisplayDay(Borrowbook.Expectreturnday);
	cout << endl;

}
void CreateBorrowForm(list <BorrowForm> &bf)
{
	system("cls");
	list<Book>b;
	int count = 0;
	string confirm;
	string getIDreader;
	BorrowForm Borrowbook;
	cout << "   ************************************" << endl;
	cout << "   |        Lap phieu muon sach        |" << endl;
	cout << "   ************************************" << endl;
	cout << "Nhap Ma ID doc gia       : ";
	cin.ignore();
	getline(cin, getIDreader);
	if (CheckCreateReader(getIDreader) == true)
	{
		cout << "Ma doc gia khong ton tai vui long tao the de muon sach" << endl;
	}
	else if (CheckSameIDreader(getIDreader) == false)
	{
		cout << "Doc gia da muon sach " << endl;
	}
	else
	{
		Borrowbook.Person.ID = getIDreader;
		string validate;
		string temp;
		int n = 0;
		FindBorrowInfo(Borrowbook);
		cout << "Ten doc gia              : "<< Borrowbook.Person.Info.Name << endl;
		cout << "------------------------------------------------------" << endl;
		int y = wherey();
		string text = "nhap ISBN sach muon   : ";
		int x = static_cast<int>(text.size());
		int i = 0;
		for (;;)
		{
			Borrowbook.BookBorrowed = n;
			cout << "nhan bat ky de chon sach,nhan Y de hoan tat  :";
			string text1 = "nhan bat ky de chon sach,nhan Y de hoan tat  :";
			int cor = wherey();
			getline(cin, validate);
			if (n >5)
			{
				cout << "Vuot qua so dau sach co the muon" << endl;
				break;
			}
			if (validate.compare("Y") == 0 || validate.compare("y") == 0)
			{
				break;
			}
			gotoxy(0, cor);
			for (int z = 0; z < (text1.size()+validate.size()); z++)
			{
				cout << " ";
			}
			gotoxy(0, cor);
			cout << "nhap ISBN sach muon " << i + 1 << "    : ";
			getline(cin, temp);
			if (CheckISBN(temp) == false && CheckSameISBN(Borrowbook,temp)==true)
			{
				gotoxy(static_cast<int>(text.size() + 3),static_cast<int>( wherey() - 1));
				cout << setw(11) << left << temp << " ";
				cout << setw(15) << "Nhap sach thanh cong" << endl;
				
				string name = FindName(temp, b);
				cout << "ten sach                 : " << name << endl;
				cout << "Nhap so luong sach muon (toi da 3 cuon)  : ";
				string text2 = "Nhap so luong sach muon (toi da 3 cuon)  : ";
				int y = wherey();
				string temp1;
				do
				{
					getline(cin, temp1);
					//cin >> Borrowbook.Bookname[n].Borrowed;
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
					//cin.ignore();
					count++;
					n++;
					i++;
				}
				else
				{
					cout << endl;
					cout << "nhap du sach voi kho" << endl;
				}
			}
			else
			{
				gotoxy(static_cast<int>(text.size() + 3),static_cast<int>( wherey() - 1));
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
		cout << "------------------------------------------------------" << endl;
		if (count == 0)
		{
			cout << "Chua co sach nao duoc nhap, khong the lap phieu" << endl;
		}
		else
		{
			do
			{
				Borrowbook.FormID = printRandomString();
			} while (CheckSameID(Borrowbook.FormID) == false);
			LoadingDot("Dang tai du lieu, xin hay doi trong giay lat");
			PrintForm(Borrowbook);
			cout << "bam Y de xac nhan lap phieu muon sach,bam cac ky tu khac de huy bo: ";
			int keypressed = _getch();
			if (keypressed == (int)'Y' || keypressed == (int)'y')
			{
				bf.push_back(Borrowbook);
				BorrowFormToFile(bf);
			}
			else
			{
				cout << endl;
				cout << "Phieu da bi huy" << endl;
			}
		}
	}

}

