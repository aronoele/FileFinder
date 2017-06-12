#include "FileFinder.h"
#include <iostream>

FileFinder::FileFinder(const string& path)
{
	std::cout << "FileFinder c-tor\n";
	node_ = new Directory(path.substr(path.find_last_of('\\') + 1));
	root_ = node_;
	parent_ = nullptr;
	path_ = path;
}

FileFinder::~FileFinder()
{
	std::cout << "FileFinder d-tor\n";
	node_ = root_;
	clear(node_);
	//delete node_;
}

void FileFinder::clear(Directory* node)
{
	node_ = node;
	vector<Component*> components = node_->getComponents();

	for (int i = 0; i < components.size(); i++)
	{
		if (components[i]->isDirectory()) {
			parent_ = node_;
			node_ = static_cast<Directory*>(components[i]);
			clear(node_);
		}
		else {
			cout << "delete file " << components[i]->getName() << endl;
			delete components[i];
		}
	}

	if (node_ != root_) {
		cout << "delete directory " << node_->getName() << endl;
		delete node_;
		node_ = parent_;
		cout << "node = parent : " << node_->getName() << endl;
	}
}

void FileFinder::scan(const string& path)
{
	_finddata_t fd;

	string currentPath = path + "\\*.*";
	int hFile = _findfirst(currentPath.c_str(), &fd);
	int result = hFile;

	while (result != -1) {
		if (strcmp(fd.name, ".") == 0 || strcmp(fd.name, "..") == 0) {
			result = _findnext(hFile, &fd);
			continue;
		}
		currentPath = path + "\\";
		currentPath.append(fd.name);
		if (!(fd.attrib & _A_SUBDIR)) {
			//std::cout << "new File " <<fd.name << std::endl;
			File* file = new File(fd.name);
			node_->add(file);
		}
		else {
			//std::cout << "new Directory " << fd.name << std::endl;
			Directory* directory = new Directory(fd.name);
			node_->add(directory);
			parent_ = node_;
			node_ = directory;
			scan(currentPath);
		}

		result = _findnext(hFile, &fd);
	}

	if (node_ != root_) {
		node_ = parent_;
	}

	_findclose(hFile);
}

void FileFinder::scan()
{
	node_ = root_;
	scan(path_);
	node_ = root_;
	cout << "Specified folder were scanned\n";
}

void FileFinder::search()
{
	cout << "Enter a search template: ";
	string str;
	cin >> str;
	node_ = root_;
	find(str);
	node_ = root_;
}

void FileFinder::find(const string& str)
{
	vector<Component*> components = node_->getComponents();

	for (int i = 0; i < components.size(); i++)
	{
		if (strstr((components[i]->getName()).c_str(), str.c_str())) {
			cout << components[i]->getName() << endl;
		}
		if (components[i]->isDirectory()) {
			parent_ = node_;
			node_ = static_cast<Directory*>(components[i]);
			find(str);
		}
	}

	if (node_ != root_) {
		node_ = parent_;
	}
}

void FileFinder::saveToXml(ostream& os, int& tab)
{
	vector<Component*> components = node_->getComponents();

	for (int i = 0; i < components.size(); i++)
	{
		for (int i = 0; i < tab; i++)
		{
			os << "\t";
		}
		if (components[i]->isDirectory()) {
			os << "<directory name =\"" << components[i]->getName() << "\">";
			if (node_->getComponents().size() != 0) { os << endl; }
			tab++;
			parent_ = node_;
			node_ = static_cast<Directory*>(components[i]);
			saveToXml(os, tab);
		}
		else {
			os << "<file name =\"" << components[i]->getName() << "\">" << "</file>\n";
		}
	}

	if (node_ != root_ && tab > 1) {
		for (int i = 0; i < tab - 1; i++)
		{
			os << "\t";
		}
		os << "</directory>\n";
		tab--;
		node_ = parent_;
	}
}


void FileFinder::saveToXml()
{
	node_ = root_;
	ofstream out("filefinder.xml", ios::out);
	if (!out.is_open())
	{
		cout << "Writting error\n";
	}
	out << "<?xml version=\"1.0\"?>\n";
	//out << "<filesystem>\n";
	out << "<directory name =\"" << node_->getName() << "\">";
	int tab = 1;
	saveToXml(out, tab);
	//out << "</filesystem>\n";
	out << "</directory>\n"; 
	out.close();
	node_ = root_;
	cout << "Data was saved to file filefinder.xml\n";
}