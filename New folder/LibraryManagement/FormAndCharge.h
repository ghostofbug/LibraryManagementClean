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
void CreateBorrowForm(list <BorrowForm> &bf, list<Reader> reader);
void FindReaderInfo(BorrowForm &Borrowbook, list<Reader>l);
#endif

