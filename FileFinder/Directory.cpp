#include "Directory.h"
#include <iostream>

using std::string;
using std::vector;

Directory::Directory() { std::cout << "Default Directory c-tor\n"; }

Directory::Directory(const string& name) : Component(name) { /*std::cout << "Directory c-tor\n";*/ }

Directory::~Directory() { /*components_.clear();*/ /*std::cout << "Directory " + getName() + " d-tor\n";*/ }

bool Directory::isDirectory()
{
	return true;
}

void Directory::add(Component* component)
{
	components_.push_back(component);
}

vector<Component*> Directory::getComponents()
{
	return components_;
}