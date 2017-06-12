#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Component.h"

class Directory : public Component
{
public:
	Directory();
	Directory(const string& name);
	~Directory();
	bool isDirectory() override;
	void add(Component* component);
	std::vector<Component*> getComponents();
private:
	std::vector<Component*> components_;
};
