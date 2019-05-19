#ifndef __FormAndCharge_H__
#define __FormAndCharge_H__
#include "ReaderManage.h"
#include "BookManage.h"
#include "PublicFunc.h"
#include <ctime>


struct BorrowForm
{
	string FormID;
	Reader Person;
	Book Bookname[50];
	Date Borrowday;
	Date Expectreturnday;
	Time TimeCreate;
	Time ExpectTime;
	int BookBorrowed;
};
struct Bill
{
	string BillID;
	BorrowForm Charge;
	double charge;
	string reason;
};
void BorrowFormToList(list<BorrowForm>&bf);
string FindName(string ISBN, list<Book>b);
void CreateBorrowForm(list <BorrowForm> &bf);
void FindBorrowInfo(BorrowForm &Borrowbook);
void FindBookInfo(BorrowForm &Borrowbook, list<Book>b);
void DisplayBorrowBookInfo(BorrowForm Borrowbook);
void PrintForm(BorrowForm &Borrowbook);
void BorrowFormToFile(list<BorrowForm>bf);
void DisplayListBorrow(list<BorrowForm>bf);
bool CheckSameID(string ID);
bool CheckID(string ID, list<BorrowForm>bf);
void ReturnBook(list<BorrowForm>&bf, list<Bill>BILL);
bool CheckSameISBN(BorrowForm temp, string ISBN);
void BillToFile(list<Bill>BILL);
int FeeCharge(int elapseday);
void BillToList(list<Bill>&BILL);
bool CheckSameIDreader(string getIDreader);
void ChargeBill(Bill bill);
#endif

