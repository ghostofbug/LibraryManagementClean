#ifndef _READERMANAGE_H__
#define _READERMANAGE_H__

#include <iostream>
#include <iomanip>
#include <list>
#include <iterator>
#include <stdio.h>
#include <conio.h>
#include <string>
#include "PublicFunc.h"
#include "UserManagement.h"

using namespace std;

struct Reader {
	string ID;
	PersonInfo Info;
	Date Mfg;
	Date Exp;
};
//Trình bày
void DisplayReader(Reader reader);
void DisplayReaderList(list <Reader> l);
void DisplayReaderInfo(Reader temp);

//Đồng bộ dữ liệu độc giả
void UpdateReaderList(list <Reader> &l);
void UpdateReaderFile(list <Reader> l);
void AddReaderToFile(Reader reader);


//Tạo độc giả mới
bool CheckCreateReader(string ID);
void CreateReader(list<Reader> &l);
void AddReaderToList(list<Reader> &l, Reader reader);

//Cập nhật thông tin độc giả
void UpdateReaderInfo(list <Reader> &l, string id);
Reader ChangReaderInfo(Reader reader);
void UpdateReader(list <Reader> &l);

//Xóa độc giả
void DelReader(list <Reader> &l, string id);
void DeleteReader(list <Reader> &l);

//Tìm độc giả theo CMND
int SearchCitizenID(list <Reader> l, string id);
void SearchReaderCitizenID(list <Reader> l);

//Tìm độc giả theo tên
int SearchName(list <Reader> l, string id);
void SearchReaderName(list <Reader> l);

#endif

