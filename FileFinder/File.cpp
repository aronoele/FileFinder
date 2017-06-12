#include "File.h"
#include <iostream>


using std::string;

File::File(const string& name) : Component(name) { /*std::cout << "File c-tor\n";*/ }

File::~File() { /*std::cout << "File d-tor\n";*/ }