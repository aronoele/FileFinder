#pragma once

#include <iostream>
#include <string>

#include "Component.h"

using std::string;

class File : public Component
{
public:
	File(const string& name);
	~File();
};
