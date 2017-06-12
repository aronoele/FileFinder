#pragma once

#include <string>

using std::string;

class Component
{
public:
	Component();
	Component(const string& name);
	virtual ~Component();
	virtual string getName() const;
	virtual void setName(const string& name);
	virtual bool isDirectory();
protected:
	string name_;
};