#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "FileManager.h"
#include "Generator.h"

using namespace std;

class Menu {
public:
	Menu();
	vector<int> convertASCII(string s);
	int calcSteps(int x);
	vector<int> encryptPassword(vector<int> v);
	string passwordToString(vector<int> v);
	string combineDetails(string username, string pass);
	void createUser(Menu m, FileManager f);
	void displayOptions(Menu m, FileManager f);
	void checkUserDetails(Menu m, FileManager f);
	int attempts;
	bool exit;
};