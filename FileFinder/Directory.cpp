#include "Directory.h"

using std::vector;

Directory::Directory() { std::cout << "Default Directory c-tor\n"; }

Directory::Directory(const string& name) : Component(name) {}

Directory::~Directory() { /*components_.clear();*/ }

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