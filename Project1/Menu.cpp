#include "Menu.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Menu::Menu(){
	attempts = 3;
	exit = false;
}

vector<int> Menu::convertASCII(string s){
	vector<int> asciiVec;
	for (int i = 0; i < s.length(); i++) {
		asciiVec.push_back((int)s[i]);
	}
	return asciiVec;
}

int Menu::calcSteps(int x){
	int steps = 0;
	while (x != 1) {
		if (x % 2 == 0) {
			x = x / 2;
			steps++;
		}
		else {
			x = 3 * x + 1;
			steps++;
		}
	}
	return steps;
}

vector<int> Menu::encryptPassword(vector<int> v){
	int offset = 0;
	vector<int> encrypVec = v;
	vector<int> newVec;
	for (int i : encrypVec) {
		int steps = calcSteps(i + offset);
		offset = steps;
		newVec.push_back(steps);
	}


	return newVec;
}

string Menu::passwordToString(vector<int> v){
	string tempString;
	for (int i : v) {
		tempString = tempString + to_string(i);
	}
	return tempString;
}

string Menu::combineDetails(string username, string pass){
	string combined;
	combined = username + " " + pass;
	return combined;
}

void Menu::createUser(Menu m, FileManager f){
	bool user = false;
	bool pass = false;
	string userText;
	string passwordText;
	try {
		cout << "Create a username: ";
		getline(cin, userText);
		if (userText != "" && userText.find(" ") == string::npos) {
			cout << "Username accepted" << endl;
			user = true;
		}
		else {
			throw(userText);
		}
	}
	catch (string userText) {
		cout << "Username " << userText << " was not accepted, cannot be empty or contain spaces" << endl;
		return;
	}

	try {
		cout << "Create a password: ";
		getline(cin, passwordText);
		if (passwordText != "" && passwordText.find(" ") == string::npos) {
			cout << "Password accepted" << endl;
			pass = true;
		}
		else {
			throw(passwordText);
		}
	}
	catch (string passwordText) {
		cout << "Password was not accepted, cannot be empty or contain spaces" << endl;
		return;

	}

	if (user && pass) {
		vector<int> tempVec;
		tempVec = m.convertASCII(passwordText);
		tempVec = m.encryptPassword(tempVec);

		string passString;
		passString = m.passwordToString(tempVec);
		string toEnter;
		toEnter = m.combineDetails(userText, passString);
		f.enterUserDetails(toEnter);
		cout << "User details written to file" << endl;
	}
}

void Menu::checkUserDetails(Menu m, FileManager f){
	while (attempts != 0) {
		string userText;
		string passwordText;
		bool user;
		bool pass;
		
		try {
			cout << "Enter your existing username: ";
			getline(cin, userText);
			if (userText != "" && userText.find(" ") == string::npos) {
				user = true;
			}
			else {
				throw(userText);
			}
		}
		catch (string userText) {
			cout << "Username " << userText << " was not accepted, cannot be empty or contain spaces" << endl;
			return;
		}

		try {
			cout << "Enter the corresponding password: ";
			getline(cin, passwordText);
			if (passwordText != "" && passwordText.find(" ") == string::npos) {
				pass = true;
			}
			else {
				throw (passwordText);
			}
		}

		catch (string passwordText) {
			cout << "Password was not accepted, cannot be empty or contain spaces" << endl;
			return;
		}

		if (user && pass) {
			vector<int> tempVec;
			tempVec = m.convertASCII(passwordText);
			tempVec = m.encryptPassword(tempVec);

			string passString;
			passString = m.passwordToString(tempVec);

			string passCheck;
			passCheck = f.searchName(userText, passString);

			if (passCheck == passString) {
				cout << "Login successful" << endl;
				break;
			}
			else {
				cout << "Failure!" << endl;
				attempts--;
				cout << "Attempts remaining: " << attempts << endl;
			}
		}
	}
	if (attempts == 0) {
		cout << "Maximum attempts exceeded. " << endl;
	}
}

void Menu::displayOptions(Menu m, FileManager f){
	cout << endl;
	cout << " --------------------------------" << endl;
	cout << "Choose from list of options: " << endl;
	cout << "1. Create a new account" << endl;
	cout << "2. Log in to an account" << endl;
	cout << "3. Generate passwords" << endl;
	cout << "4. Analyse passwords" << endl;
	cout << "5. Exit" << endl;
	int choice;
	cin >> choice;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	string username;
	Generator g;
	switch (choice) {
	case 1:
		m.createUser(m, f);
		break;
	case 2:
		m.checkUserDetails(m, f);
		break;
	case 3:
		g.firstSet();
		break;
	case 4:
		g.analysis();
		break;
	case 5:
		exit = true;
		break;
	default:
		cout << "Invalid option, try again. " << endl;
	}
}

int main() {
	Menu m;
	FileManager f;
	while (m.exit == false) {
		m.displayOptions(m, f);
	}
	
}