#ifndef __FormAndCharge_H__
#define __FormAndCharge_H__
#include "ReaderManage.h"
#include "BookManage.h"
#include "PublicFunc.h"
#include <ctime>


struct BorrowForm
{
	Reader Person;
	Book Bookname[50];
	Date Borrowday;
	Date Expectreturnday;
	Time TimeCreate;
	int BookBorrowed;
};
string FindName(string ISBN, list<Book>b);
void CreateBorrowForm(list <BorrowForm> &bf);
void FindBorrowInfo(BorrowForm &Borrowbook);
void FindBookInfo(BorrowForm &Borrowbook, list<Book>b);
void DisplayBorrowBookInfo(BorrowForm Borrowbook);
void PrintForm(BorrowForm Borrowbook);
void BorrowFormToFile(list<BorrowForm>bf);
#endif

