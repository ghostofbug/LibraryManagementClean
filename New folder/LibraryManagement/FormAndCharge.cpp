#include "FormAndCharge.h"
void BorrowFormToFile(list<BorrowForm>bf)
{
	ofstream fwrite;
	fwrite.open("BorrowForm");
	list<BorrowForm>::iterator i;
	for (i = bf.begin(); i != bf.end(); i++)
	{
		BorrowForm temp;
		temp.Person.ID = i->Person.ID;
		temp.BookBorrowed = i->BookBorrowed;
		fwrite << temp.Person.ID << ",";
		for (int j = 0; j < temp.BookBorrowed; j++)
		{
			temp.Bookname[j].ISBN = i->Bookname[j].ISBN;
			temp.Bookname[j].Borrowed = i->Bookname[j].Borrowed;
			fwrite << temp.Bookname[j].ISBN << ",";
			fwrite << temp.Bookname[j].Borrowed << ",";
		}
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
void PrintForm(BorrowForm Borrowbook)
{
	system("cls");
	cout << "Thu vien truong Dai Hoc Khoa Hoc Tu Nhien" << endl;
	cout << endl;
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
	Borrowbook.TimeCreate.Hrs = exreturndate.tm_hour;
	Borrowbook.TimeCreate.Mins = exreturndate.tm_min;
	Borrowbook.TimeCreate.Secs = exreturndate.tm_sec;
	cout << "Ngay tra du kien         : ";
	DisplayTime(Borrowbook.TimeCreate);
	DisplayDay(Borrowbook.Expectreturnday);
	cout << endl;

}
void CreateBorrowForm(list <BorrowForm> &bf)
{
	system("cls");
	list<Book>b;
	int count = 0;
	string confirm;
	BorrowForm Borrowbook;
	cout << "   ************************************" << endl;
	cout << "   |        Lap phieu muon sach        |" << endl;
	cout << "   ************************************" << endl;
	cout << "Nhap Ma ID doc gia       : ";
	cin.ignore();
	getline(cin, Borrowbook.Person.ID);
	if (CheckCreateReader(Borrowbook.Person.ID) == true)
	{
		cout << "Ma doc gia khong ton tai vui long tao the de muon sach" << endl;
	}
	else
	{
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
			cout << "nhan bat ky de chon sach,nhan Y de hoan tat  :";
			string text1 = "nhan bat ky de chon sach,nhan Y de hoan tat  :";
			int cor = wherey();
			getline(cin, validate);
			if (n > 50)
			{
				cout << "Vuot qua so sach co the muon" << endl;
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
			if (CheckISBN(temp) == false)
			{
				gotoxy(text.size() + 3, wherey() - 1);
				cout << setw(11) << left << temp << " ";
				cout << setw(15) << "Nhap sach thanh cong" << endl;
				Borrowbook.Bookname[n].ISBN = temp;
				string name = FindName(temp, b);
				cout << "ten sach                 : " << name << endl;
				cout << "Nhap so luong sach muon  : ";
				string text2= "Nhap so luong sach muon  : ";
				int y = wherey();
				do
				{
					cin >> Borrowbook.Bookname[n].Borrowed;
					gotoxy(text2.size(), y);
				} while (Borrowbook.Bookname[n].Borrowed < 0);
				cout << endl;
				cin.ignore();
				count++;
				n++;
				i++;
			}
			else
			{
				i++;
				gotoxy(text.size() + 3, wherey() - 1);
				cout << setw(11) << left << temp << " ";
				cout << setw(15) << "Ma sach khong ton tai" << endl;
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
			LoadingDot();
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

			}
		}
	}

}

