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
	Book Bookname[5];
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
	unsigned long int charge;
	string reason;
};
//TRÌNH BÀY
void DisplayBorrowBookInfo(BorrowForm Borrowbook);
void DisplayBorrowForm(BorrowForm form);
void DisplayListBorrow(list<BorrowForm>bf);
void PrintForm(BorrowForm &Borrowbook);
//KIỂM TRA
bool CheckNullForm(BorrowForm form);
bool CheckIDForm(string ID);
bool CheckSameID(string ID);
bool CheckID(string ID, list<BorrowForm>bf);
bool CheckSameISBN(BorrowForm temp, string ISBN);
bool CheckSameIDreader(string getIDreader);
int CheckISBNInBorrowForm(string ISBN, BorrowForm form);
int CheckNumBer(int num, string ISBN, BorrowForm form);
bool CheckExpDay(string IDreader);
int GetQuanTiTy(string ISBN);

//MƯỢN SÁCH
string FindName(string ISBN, list<Book>b);
void CreateBorrowForm(list <BorrowForm> &bf);
void FindBorrowInfo(BorrowForm &Borrowbook);
void FindBookInfo(BorrowForm &Borrowbook, list<Book>b);

//ĐỒNG BỘ DỮ LIỆU
void BorrowFormToList(list<BorrowForm>&bf);
void BorrowFormToFile(list<BorrowForm>bf);
void BillToList(list<Bill>&BILL);
void BillToFile(list<Bill>BILL);
void UpDateQuanTiTy(string ISBN, int n);

//TRẢ SÁCH
void ReturnBook(list<BorrowForm>&bf, list<Bill>BILL);
unsigned long int FeeCharge(int elapseday);
void LostBook(list<BorrowForm>&bf, list<Bill>BILL);
void ChargeBill(Bill bill);

#endif