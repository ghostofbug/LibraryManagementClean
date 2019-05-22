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
void DisplayBorrowBookInfo(BorrowForm Borrowbook);// hiển thị thông tin sách mượn
void DisplayBorrowForm(BorrowForm form);//hiển thị phiếu mượn sách
void DisplayListBorrow(list<BorrowForm>bf);// hiển thị danh sách phiếu mượn sách đang có
void PrintForm(BorrowForm &Borrowbook);// tạo phiếu dựng sách từ các thông tin sách mượn đã nhập
//KIỂM TRA
bool CheckNullForm(BorrowForm form);// kt phiếu độc giả có tất cả đầu sách có số lượng bằng 0 hay không
bool CheckIDForm(string ID); // kt mã phiếu được nhập có trùng với dữ liệu phiếu 
bool CheckSameISBN(BorrowForm temp, string ISBN); // kt trùng mã ISBN trả về đúng sai
bool CheckSameIDreader(string getIDreader); // Kt độc giả đã mượn sách hay chưa
int CheckISBNInBorrowForm(string ISBN, BorrowForm form);// kt trùng mã ISB trả về vị trí
int CheckNumBer(int num, string ISBN, BorrowForm form);// kt số lượng nhập khi mất sách có đúng như trong phiếu mượn
bool CheckExpDay(string IDreader);// kt ngày hết hạn của thẻ
int GetQuanTiTy(string ISBN);// lấy tổng số lượng 1 đầu sách 

//MƯỢN SÁCH
string FindName(string ISBN, list<Book>b); // Tìm tên sách
void CreateBorrowForm(list <BorrowForm> &bf);// tạo phiếu mượn
void FindBorrowInfo(BorrowForm &Borrowbook);//tìm thông tin độc giả mượn sách
void FindBookInfo(BorrowForm &Borrowbook, list<Book>b);// tìm thông tin quyển sách được mượn

//ĐỒNG BỘ DỮ LIỆU
void BorrowFormToList(list<BorrowForm>&bf);// thêm các phiếu vào danh sách
void BorrowFormToFile(list<BorrowForm>bf);// thêm phiếu vào dữ liệu file
void BillToList(list<Bill>&BILL);// thêm dữ liệu hóa đơn vào list
void BillToFile(list<Bill>BILL);// thêm dữ liệu hóa đơn vào file lưu trữ
void UpDateQuanTiTy(string ISBN, int n);// cập nhật lại số lượng sách khi mượn/trả

//TRẢ SÁCH
void ReturnBook(list<BorrowForm>&bf, list<Bill>BILL);// hàm trả sách
unsigned long int FeeCharge(int elapseday);// hàm tính phí phạt trễ hạn
void LostBook(list<BorrowForm>&bf, list<Bill>BILL);// hàm báo mất sách
void ChargeBill(Bill bill);// hàm hiển thị hóa đơn phạt

#endif