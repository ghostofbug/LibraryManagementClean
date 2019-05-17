#include "BookManage.h"
#include "PublicFunc.h"
void DisplayBook(Book book)
{
	cout << "| " << setw(15) << left << book.ISBN;
	cout << " | ";
	cout << setw(30) << book.Name;
	cout << " | " << setw(25) << book.Author;
	cout << " | " << setw(12) << book.Publisher;
	cout << " | "; DisplayDay(book.Mfg);
	cout << " | " << setw(25) << book.Category;
	cout << " | " << setw(9) << book.Price;
	cout << " | " << setw(4) << book.Quantity;
	cout << " | " << setw(4) << book.Borrowed << " |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}
void DisplayBookList(list <Book> l)
{
	system("cls");
	cout << "   ---------------------------------" << endl;
	cout << "   |         DANH SACH SACH        |" << endl;
	cout << "   ---------------------------------" << endl;
	if (l.empty() == true)
	{
		cout << "Danh sach sach rong!" << endl;
	}
	else
	{
		cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "|      ISBN       |            Ten sach            |          Tac gia          |     NXB      |   Ngay XB  |          The loai         |    Gia    |  SL  | Muon |" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

		list<Book> ::iterator i;
		for (i = l.begin(); i != l.end(); i++)
		{
			Book temp;
			temp.ISBN = i->ISBN;
			temp.Name = i->Name;
			temp.Author = i->Author;
			temp.Publisher = i->Publisher;
			temp.Mfg = i->Mfg;
			temp.Category = i->Category;
			temp.Price = i->Price;
			temp.Quantity = i->Quantity;
			temp.Borrowed = i->Borrowed;
			DisplayBook(temp);
		}
	}
}
void DisplayBookInfo(Book temp)
{
	cout << "ISBN        : " << temp.ISBN << endl;
	cout << "Ten sach    : " << temp.Name << endl;
	cout << "Tac gia     : " << temp.Author << endl;
	cout << "NXB         : " << temp.Publisher << endl;
	cout << "Ngay XB     : "; DisplayDay(temp.Mfg); cout << endl;
	cout << "The loai    : " << temp.Category << endl;
	cout << "Gia         : " << temp.Price << endl;
	cout << "So luong    : " << temp.Quantity << endl;
	cout << "Dang muon   : " << temp.Borrowed << endl;
	cout << "===========================================================================" << endl;
}
void UpdateBookList(list <Book> &l)
{
	int size = FileSize("book.txt");
	ifstream fin;
	fin.open("book.txt");
	l.clear();
	for (int i = 0; i < size; i++)
	{
		Book temp;
		getline(fin, temp.ISBN, ',');
		getline(fin, temp.Name, ',');
		getline(fin, temp.Author, ',');
		getline(fin, temp.Publisher, ',');
		fin >> temp.Mfg.d;
		fin.seekg(1, 1);
		fin >> temp.Mfg.m;
		fin.seekg(1, 1);
		fin >> temp.Mfg.y;
		fin.seekg(1, 1);
		getline(fin, temp.Category, ',');
		fin >> temp.Price;
		fin.seekg(1, 1);
		fin >> temp.Quantity;
		fin.seekg(1, 1);
		fin >> temp.Borrowed;
		string x;
		getline(fin, x, '\n');
		l.push_back(temp);
	}
}
void UpdateBookFile(list <Book> l)
{
	list<Book> ::iterator i;
	for (i = l.begin(); i != l.end(); i++)
	{
		Book temp;
		temp.ISBN = i->ISBN;
		temp.Name = i->Name;
		temp.Author = i->Author;
		temp.Publisher = i->Publisher;
		temp.Mfg = i->Mfg;
		temp.Category = i->Category;
		temp.Price = i->Price;
		temp.Quantity = i->Quantity;
		temp.Borrowed = i->Borrowed;
		AddBookToFile(temp);
	}
	remove("book.txt");
	rename("booknew.txt", "book.txt");
}
void AddBookToFile(Book book)
{
	ofstream fout;
	fout.open("booknew.txt", ios::app);
	fout << book.ISBN << "," << book.Name << "," << book.Author << "," << book.Publisher << ",";
	fout << book.Mfg.d << "," << book.Mfg.m << "," << book.Mfg.y << ",";
	fout << book.Category << "," << book.Price << "," << book.Quantity << "," << book.Borrowed << endl;;
	fout.close();
}
bool CheckISBN(string ISBN)
{
	ifstream fin;
	fin.open("book.txt");
	string x;
	while (getline(fin, x, ','))
	{
		if (ISBN.compare(x) == 0)
		{
			return false;
		}
		getline(fin, x, '\n');
	}
	return true;
}
void CreateBook(list <Book> &l)
{
	Book temp;
	system("cls");
	cout << "   ---------------------------------" << endl;
	cout << "   |           THEM SACH           |" << endl;
	cout << "   ---------------------------------" << endl;

	cout << "Nhap ISBN              : ";
	cin >> temp.ISBN;
	if (CheckISBN(temp.ISBN) == false)
	{
		cout << "Sach da co, thay doi thong tin sach o muc chinh sua!" << endl;
		temp.ISBN = "0";
	}
	else
	{
		cout << "Ten sach               : ";
		cin.ignore();
		getline(cin, temp.Name);
		cout << "Tac gia                : ";
		getline(cin, temp.Author);
		cout << "NXB                    : ";
		getline(cin, temp.Publisher);
		cout << "Ngay XB (dd/mm/yyyy)   : ";
		int y = wherey();
		temp.Mfg = GetDay(StringSize("Ngay XB (dd/mm/yyyy)   : "),y);
		cout << "The loai               : ";
		cin.ignore();
		getline(cin, temp.Category);
		cout << "Gia                    : ";
		cin >> temp.Price;
		cout << "So luong               : ";
		cin >> temp.Quantity;
		temp.Borrowed = 0;
		AddBookToList(l, temp);
		cout << endl << "Them sach thanh cong!" << endl;
	}
}
void AddBookToList(list<Book> &l, Book book)
{
	l.push_back(book);
	UpdateBookFile(l);
}
void UpdateBookInfo(list <Book> &l, string ISBN)
{
	list<Book> ::iterator i;
	for (i = l.begin(); i != l.end(); i++)
	{
		Book temp;
		temp.ISBN = i->ISBN;

		if (temp.ISBN.compare(ISBN) == 0)
		{
			temp.Name = i->Name;
			temp.Author = i->Author;
			temp.Publisher = i->Publisher;
			temp.Mfg = i->Mfg;
			temp.Category = i->Category;
			temp.Price = i->Price;
			temp.Quantity = i->Quantity;
			temp.Borrowed = i->Borrowed;

			DisplayBookInfo(temp);
			temp = ChangBookInfo(temp);

			i->Name = temp.Name;
			i->Author = temp.Author;
			i->Publisher = temp.Publisher;
			i->Mfg = temp.Mfg;
			i->Category = temp.Category;
			i->Price = temp.Price;
			i->Quantity = temp.Quantity;
			i->Borrowed = temp.Borrowed;
			UpdateBookFile(l);
		}
	}
}
Book ChangBookInfo(Book book)
{
	Book temp = book;
	cout << "Nhan 'y' de cap nhat thong tin, nhan bat ky de bo qua: " << endl;
	int check = _getch();
	if (check == (int)'y')
	{
		cout << "Ten sach                 - " << temp.Name << endl;
		int check;
		check = _getch();
		if (check == (int)'y')
		{
			cout << "Cap nhat ten sach       : ";
			getline(cin, temp.Name);
		}

		cout << "Tac gia                  - " << temp.Author << endl;
		check = _getch();
		if (check == (int)'y')
		{
			cout << "Cap nhat tac gia        : ";
			getline(cin, temp.Author);
		}
		cout << "Nha xuat ban             - " << temp.Publisher << endl;
		check = _getch();
		if (check == (int)'y')
		{
			cout << "Cap nhat nha xuat ban   : ";
			getline(cin, temp.Publisher);
		}
		cout << "Ngay xuat ban            - "; DisplayDay(temp.Mfg); cout << endl;
		check = _getch();
		if (check == (int)'y')
		{
			cout << "Cap nhat ngay xuat ban  : ";
			int y = wherey();
			temp.Mfg = GetDay(StringSize("Cap nhat ngay xuat ban  : "), y);
		}
		cout << "The loai                 - " << temp.Category << endl;
		check = _getch();
		if (check == (int)'y')
		{
			cout << "Cap nhat the loai       : ";
			getline(cin, temp.Category);
		}
		cout << "Gia                      - " << temp.Price << endl;
		check = _getch();
		if (check == (int)'y')
		{
			cout << "Cap nhat gia            : ";
			cin >> temp.Price;
		}
		cout << "So luong sach            - " << temp.Quantity << endl;
		check = _getch();
		if (check == (int)'y')
		{
			cout << "Cap nhat so luong sach   : ";
			cin >> temp.Quantity;
		}
		cout << "Dang muon                - " << temp.Borrowed << endl;
		check = _getch();
		if (check == (int)'y')
		{
			cout << "Cap nhat so luong muon   : ";
			cin >> temp.Borrowed;
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
	else
	{
		cout << "Thao tac da bi huy!" << endl;
	}
	return book;
}
void UpdateBook(list <Book> &l)
{
	system("cls");
	cout << "   ---------------------------------" << endl;
	cout << "   |    CAP NHAT THONG TIN SACH    |" << endl;
	cout << "   ---------------------------------" << endl;
	if (l.empty() == true)
	{
		cout << "Danh sach sach rong!" << endl;
	}
	else
	{
		cout << "Nhap ma ISBN        : ";
		string s;
		cin.ignore();
		getline(cin, s);
		UpdateBookInfo(l, s);
	}
}
void DelBook(list <Book> &l, string ISBN)
{
	list<Book> ::iterator i;
	for (i = l.begin(); i != l.end(); i++)
	{
		Book temp;
		temp.ISBN = i->ISBN;
		if (ISBN.compare(temp.ISBN) == 0)
		{
			temp.Name = i->Name;
			temp.Author = i->Author;
			temp.Publisher = i->Publisher;
			temp.Mfg = i->Mfg;
			temp.Category = i->Category;
			temp.Price = i->Price;
			temp.Quantity = i->Quantity;
			temp.Borrowed = i->Borrowed;
			DisplayBookInfo(temp);
			cout << "Nhan 'y' de xoa thong tin, nhan bat ky de huy thao tac : ";
			int check;
			check = _getch();
			{
				if (check == 'y')
				{
					l.erase(i);
					UpdateBookFile(l);
					cout << "Sach da bi xoa!" << endl;
				}
				else {
					cout << "Thao tac da bi huy!" << endl;
				}
			}
			break;
		}
	}
}
void DeleteBook(list <Book> &l)
{
	system("cls");
	cout << "   ---------------------------------" << endl;
	cout << "   |            XOA SACH           |" << endl;
	cout << "   ---------------------------------" << endl;
	if (l.empty() == true)
	{
		cout << "Danh sach sach rong!" << endl;
	}
	else
	{
		cout << "Nhap ma ISBN: ";
		string s;
		cin.ignore();
		getline(cin, s);
		DelBook(l, s);
	}
}
int BookISBN(list <Book> l, string ISBN)
{
	int check = 1;
	list<Book> ::iterator i;
	for (i = l.begin(); i != l.end(); i++)
	{
		Book temp;
		temp.ISBN = i->ISBN;
		if (ISBN.compare(temp.ISBN) == 0)
		{
			temp.Name = i->Name;
			temp.Author = i->Author;
			temp.Publisher = i->Publisher;
			temp.Mfg = i->Mfg;
			temp.Category = i->Category;
			temp.Price = i->Price;
			temp.Quantity = i->Quantity;
			temp.Borrowed = i->Borrowed;
			DisplayBookInfo(temp);
			check = 0;
		}
	}
	return check;
}
void SearchBookISBN(list <Book> l)
{
	system("cls");
	cout << "   ---------------------------------" << endl;
	cout << "   |       TIM SACH THEO ISBN      |" << endl;
	cout << "   ---------------------------------" << endl;
	if (l.empty() == true)
	{
		cout << "Danh sach sach rong!" << endl;
	}
	else
	{
		cout << "Nhap ma ISBN: ";
		string s;
		cin.ignore();
		getline(cin, s);
		if (BookISBN(l, s) != 0)
		{
			cout << "Khong tim thay sach!" << endl;
		}
	}
}
int BookName(list <Book> l, string name)
{
	int check = 1;
	list<Book> ::iterator i;
	for (i = l.begin(); i != l.end(); i++)
	{
		Book temp;
		temp.Name = i->Name;
		if (temp.Name.find(name, 0) != string::npos)
		{
			temp.ISBN = i->ISBN;
			temp.Author = i->Author;
			temp.Publisher = i->Publisher;
			temp.Mfg = i->Mfg;
			temp.Category = i->Category;
			temp.Price = i->Price;
			temp.Quantity = i->Quantity;
			temp.Borrowed = i->Borrowed;
			DisplayBookInfo(temp);
			check = 0;
		}
	}
	return check;
}
void SearchBookName(list <Book> l)
{
	system("cls");
	cout << "   ---------------------------------" << endl;
	cout << "   |       TIM SACH THEO TEN       |" << endl;
	cout << "   ---------------------------------" << endl;
	if (l.empty() == true)
	{
		cout << "Danh sach sach rong!" << endl;
	}
	else
	{
		cout << "Nhap ten sach: ";
		string s;
		cin.ignore();
		getline(cin, s);
		if (BookName(l, s) != 0)
		{
			cout << "Khong tim thay sach!" << endl;
		}
	}
}

