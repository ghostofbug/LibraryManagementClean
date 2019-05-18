#include "FormAndCharge.h"
void FindReaderInfo(BorrowForm &Borrowbook,list<Reader>l)
{
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
}
void PrintForm(BorrowForm Borrowbook)
{
	system("cls");
	cout << "Thu vien truong Dai Hoc Khoa Hoc Tu Nhien" << endl;
	cout << "				---------				  " << endl;
	cout << "   ************************************" << endl;
	cout << "   |         Phieu muon sach        |" << endl;
	cout << "   ************************************" << endl;
	cout << "Ma doc gia: "<< Borrowbook.Person.ID << endl;
}
void CreateBorrowForm(list <BorrowForm> &bf,list<Reader> reader)
{
	system("cls");
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
		FindReaderInfo(Borrowbook, reader);
		string temp;
		int n;
		cout << "Nhap so luong sach muon  : ";
		do
		{
			cin >> n;
		} while (n > 50);
		Borrowbook.BookBorrowed = n;
		cout << "------------------------------------------------------" << endl;
		int y = wherey();
		string text = "nhap ISBN sach muon   : ";
		int x = static_cast<int>(text.size());
		cin.ignore();
		for (int i=0;i<n;i++)
		{
			cout << "nhap ISBN sach muon "<<i+1<<"    : ";
			getline(cin, temp);
			if (CheckISBN(temp) == false)
			{
				gotoxy(text.size()+3, wherey()-1);
				cout << setw(11) << left << temp << " ";
				cout <<setw(15) << "Nhap sach thanh cong" << endl;
				Borrowbook.Bookname[i].ISBN = temp;
				count++;
				cin.clear();
			}
			else
			{
				gotoxy(text.size() + 3, wherey() - 1);
				cout << setw(11) << left << temp << " ";
				cout << setw(15) << "Ma sach khong ton tai" << endl;
				cin.clear();
			}
		}
		cout << "------------------------------------------------------" << endl;
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
		cout << "bam Y de xac nhan lap phieu muon sach,bam cac ky tu khac de huy bo: ";
		int keypressed = _getch();
		if (keypressed == (int)'Y' || keypressed == (int)'y')
		{
			bf.push_back(Borrowbook);
		}
	}

}
