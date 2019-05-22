#include <iostream>
#include <list>
#include <iterator>
#include <fstream>

#include "PublicFunc.h"
#include "BookManage.h"
#include "ReaderManage.h"
#include "FormAndCharge.h"

using namespace std;

void ReaderCount();//Sl độc giả
void BookCount();//Sl sách
void CountBookByCategory();//SL sách theo thể loại
bool CheckCategory(list <string> catlist, string category);//Kiểm tra thể loại
void CreateCategoryList(list <Book> l, list <string> &CatList);//Tạo danh sách thể loại
void CountEachCategory(list <Book> l, list <string> &CatList);//Đếm sách mỗi thể loại
void CountReaderByGender();//SL độc giả theo giới tính
void CountBookBorrowed();//SL sách đang mượn
void CountReaderByBorrow();//Thống kê độc giả trễ hạn
