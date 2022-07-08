#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class FileManager {
public:
	FileManager();
	void enterUserDetails(string details);
	string searchName(string n, string p);
};