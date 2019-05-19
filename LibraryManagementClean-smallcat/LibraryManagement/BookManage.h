#ifndef __BookManage_H__
#define __BookManage_H__
#include <iostream>
#include <string>
#include <conio.h>
#include <list>
#include <iterator>
#include <string>

#include "PublicFunc.h"

using namespace std;

struct Book {
	string ISBN;
	string Name;
	string Author;
	string Publisher;
	Date Mfg;
	string Category;
	float Price;
	int Quantity;
	int Borrowed;
};
//Trình bày
void DisplayBook(Book book);
void DisplayBookList(list <Book> l);
void DisplayBookInfo(Book temp);

//Đồng bộ dữ liệu sách
void UpdateBookList(list <Book> &l);
void UpdateBookFile(list <Book> l);
void AddBookToFile(Book book);

//Thêm sách mới
bool CheckISBN(string ISBN);
void CreateBook(list <Book> &l);
void AddBookToList(list<Book> &l, Book book);

//Cập nhật thông tin sách
void UpdateBookInfo(list <Book> &l, string ISBN);
Book ChangBookInfo(Book book);
void UpdateBook(list <Book> &l);

//Xóa sách
void DelBook(list <Book> &l, string ISBN);
void DeleteBook(list <Book> &l);

//Tìm theo ISBN
int BookISBN(list <Book> l, string ISBN);
void SearchBookISBN(list <Book> l);

//Tìm theo tên
int BookName(list <Book> l, string name);
void SearchBookName(list <Book> l);
#endif