#include "FileManager.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

FileManager::FileManager(){
	
}

void FileManager::enterUserDetails(string details){
	fstream pfile;
	pfile.open("password.txt", ios::app);
	pfile << details << endl;
}

string FileManager::searchName(string n, string p){
	fstream pfile;
	pfile.open("password.txt");
	string username;
	string password;
	bool match = false;
	while (pfile >> username >> password) {
		if (username == n) {
			match = true;
			return password;
		}
	}
	if (match == false) {
		cout << "User does not exist" << endl;
	}
	return ("");
}
