#include "Component.h"
#include <iostream>

using std::string;

Component::Component() : name_("") { /*std::cout << "Default Component c-tor\n";*/ }

Component::Component(const string& name) : name_(name) { /*std::cout << "Component c-tor\n";*/ }

string Component::getName() const
{
	return name_;
}

void Component::setName(const string& name)
{
	name_ = name;
}

bool Component::isDirectory()
{
	return false;
}

Component::~Component() { /*std::cout << "Component d-tor\n";*/ }