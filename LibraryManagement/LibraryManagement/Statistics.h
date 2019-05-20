#include <iostream>
#include <list>
#include <iterator>
#include <fstream>

#include "PublicFunc.h"
#include "BookManage.h"
#include "ReaderManage.h"

using namespace std;

void ReaderCount();
void BookCount();
void CountBookByCategory();
bool CheckCategory(list <string> catlist, string category);
void CreateCategoryList(list <Book> l, list <string> &CatList);
bool CheckCategory(list <string> catlist, string category);
void CountEachCategory(list <Book> l, list <string> &CatList);
void CountReaderByGender();
void CountBookBorrowed();
