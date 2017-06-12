#pragma once

#include <iostream>
#include <io.h>
#include <string>
#include <Windows.h>
#include <fstream>

#include "Component.h"
#pragma once

#include "File.h"
#include "Directory.h"

using namespace std;

class FileFinder
{
public:
	FileFinder(const string& path);
	~FileFinder();
	void clear(Directory* node);
	void scan();
	void search();
	void find(const string& str);
	void saveToXml();
private:
	string path_;
	Directory* root_;
	Directory* node_;
	Directory* parent_;
	void scan(const string& path);
	void saveToXml(ostream &os, int& tab);
};
