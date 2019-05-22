#include "Statistics.h"


void BookCount()
{
	int count = 0;
	list <Book> l;
	UpdateBookList(l);
	list<Book> ::iterator i;
	for (i = l.begin(); i != l.end(); i++)
	{
		count += i->Quantity;
	}
	cout << "-----------------------------------------" << endl;
	cout << "So luong dau sach: " << FileSize("book.txt") << endl;
	cout << "So luong sach    : " << count << endl;
}
void ReaderCount()
{
	cout << "-----------------------------------------" << endl;
	cout << "So luong doc gia: " << FileSize("reader.txt") << endl;
}
void CountBookByCategory()
{
	list <Book> l;
	UpdateBookList(l);
	list <string> CatList;
	list<Book> ::iterator i;
	int n = 0;
	if (l.empty() == false)
	{
		CreateCategoryList(l, CatList);
		cout << "-----------------------------------------------------------------------------" << endl;
		cout << "|              The loai               | So luong dau sach |  So luong sach  |" << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
		CountEachCategory(l, CatList);
	}
	else {
		cout << "Danh sach sach rong!" << endl;
	}
}
void CreateCategoryList(list <Book> l, list <string> &CatList)
{
	list<Book> ::iterator i;
	for (i = l.begin(); i != l.end(); i++)
	{
		string category = i->Category;
		if (CheckCategory(CatList, category) == true)
		{
			CatList.push_back(category);
		}
	}
}
bool CheckCategory(list <string> catlist, string category)
{
	list<string> ::iterator k;
	for (k = catlist.begin(); k != catlist.end(); k++)
	{
		if (category.compare(*k) == 0)
		{
			return false;
		}
	}
	return true;
}
void CountEachCategory(list <Book> l, list <string> &CatList)
{
	list<Book> ::iterator i;
	while (CatList.empty() != true)
	{
		int count = 0;
		int count1 = 0;
		string temp = CatList.front();
		for (i = l.begin(); i != l.end(); i++)
		{
			Book temp1;
			temp1.Category = i->Category;
			if (temp.compare(temp1.Category) == 0)
			{
				temp1.Quantity = i->Quantity;
				count1 = count1 + temp1.Quantity;
				count++;
			}
		}
		cout << "| " << setw(35) << left << temp << " | " << setw(17) << count << " | " << setw(15) << count1 << " |" << endl;
		cout << "---------------------------------------------------------" << endl;
		CatList.pop_front();
	}
}
void CountReaderByGender()
{
	int male = 0; int female = 0;
	list <Reader> l;
	UpdateReaderList(l);
	list<Reader> ::iterator i;
	for (i = l.begin(); i != l.end(); i++)
	{
		int gender;
		gender = i->Info.Sex;
		if (gender == 0)
		{
			female++;
		}
		else if (gender == 1)
		{
			male++;
		}
	}
	cout << "-----------------------------------------" << endl;
	cout << "So luong doc gia nu  : " << female << endl;
	cout << "So luong doc gia nam : " << male << endl;
}
void CountBookBorrowed()
{
	list <Book> l;
	UpdateBookList(l);
	list<Book> ::iterator i;
	int count = 0;
	for (i = l.begin(); i != l.end(); i++)
	{
		int temp;
		temp = i->Borrowed;
		count = count + temp;
	}
	cout << "-----------------------------------------" << endl;
	cout << "So luong sach dang muon: " << count << endl;
}
void CountReaderByBorrow()
{
	list <BorrowForm> bf;
	list <BorrowForm> ::iterator i;
	BorrowFormToList(bf);
	time_t now;
	time(&now);
	tm ExpectReturn;
	int count = 0;
	cout << " -------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << " |   Ma phieu   |           Ten doc gia          |      Ngay muon      |  Ngay tra du kien   |            Ten sach            |      ISBN       |  SL  |" << endl;
	cout << " -------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (i = bf.begin(); i != bf.end(); i++)
	{
		Time temptime = i->ExpectTime;
		Date tempday = i->Expectreturnday;
		ExpectReturn.tm_mday = i->Expectreturnday.d;
		ExpectReturn.tm_mon = i->Expectreturnday.m - 1;
		ExpectReturn.tm_year = i->Expectreturnday.y - 1900;
		ExpectReturn.tm_hour = i->ExpectTime.Hrs;
		ExpectReturn.tm_min = i->ExpectTime.Mins;
		ExpectReturn.tm_sec = i->ExpectTime.Secs;
		time_t temp = mktime(&ExpectReturn);
		if (temp < now)
		{
			DisplayBorrowForm(*i);
			count ++;
		}
	}	
	cout << "So luong doc gia tre han: " << count << endl;
}