#include "Generator.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

Generator::Generator(){
}

void Generator::firstSet(){
	cout << "Start first set " << endl;
	ofstream gfile;
	gfile.open("passwordtest.txt");
	int count = 100;
	vector<int> letters(26);
	for (int i = 0; i < letters.size(); i++) {
		letters[i] = i;
	}

	random_device ran;
	mt19937 prng(ran());
	shuffle(letters.begin(), letters.end(), prng);
	
	vector<int> asciiLetters;
	for (int y = 0; y < 10; y++) {
		asciiLetters.push_back(letters[y] + 97);
	}

	Menu m;

	while (count < 10100) {
		double l = count / 100;
		double rounded = ceil(l);
		int passlength = (int)rounded;
		vector<int> password;
		for (int z = 0; z < passlength; z++) {
			int rselection = (rand() % 10);
			password.push_back(asciiLetters[rselection]);
		}
		password = m.encryptPassword(password);
		string passString;
		passString = m.passwordToString(password);
		gfile << passString << endl;

		count++;
	}

	cout << "First set complete. " << endl;
	gfile.close();
	secondSet();
}

void Generator::secondSet() {
	cout << "Start second set " << endl;
	ofstream gfile;
	gfile.open("passwordtest.txt", ios::app);
	int passwordlength = 1;
	Menu m;


	for (int a = 0; a < 100; a++) {
		for (int b = 0; b < 100; b++) {
			vector<int> newpass;
			int previous = 256;
			for (int c = 0; c < passwordlength; c++) {
				int current;
				do {
					random_device rd;
					mt19937 rng(rd());
					uniform_int_distribution<int> uni(1, 256);
					current = uni(rng);
				} while (current == previous);
				previous = current;
				newpass.push_back(current);
			}
			newpass = m.encryptPassword(newpass);
			string passString;
			passString = m.passwordToString(newpass);
			gfile << passString << endl;
		}
		passwordlength++;
	}
	gfile.close();
	cout << "Second set complete " << endl;
}

void Generator::analysis() {
	cout << "Beginning analysis " << endl;
	Menu m;
	fstream afile;
	afile.open("passwordtest.txt");
	string password;
	int linecount = 0;
	double correct = 0;
	double correct2 = 0;
	double timer1 = 0;
	double timer2 = 0;
	while (afile >> password) {
		auto start = chrono::high_resolution_clock::now();
		int offset = 0;
		int stringindex = 0;
		string comparepass;
		vector<int> checkVec;
		while (stringindex < password.length()) {
			bool nomatch = false;
			int len1 = stoi(password.substr(stringindex, 1));
			int len2 = stoi(password.substr(stringindex, 2));
			int len3 = stoi(password.substr(stringindex, 3));
			for (int lcase = 1; lcase < 256; lcase++) {
				int testnum = m.calcSteps(lcase + offset);
				if (testnum == len1) {
					offset = testnum;
					stringindex = stringindex + 1;
					nomatch = false;
					checkVec.push_back(lcase);
					break;
				}
				else if (testnum == len2) {
					offset = testnum;
					stringindex = stringindex + 2;
					nomatch = false;
					checkVec.push_back(lcase);
					break;
				}
				else if (testnum == len3) {
					offset = testnum;
					stringindex = stringindex + 3;
					nomatch = false;
					checkVec.push_back(lcase);
					break;
				} else {
					nomatch = true;
				}
			}
			comparepass = comparepass + to_string(offset);
			auto stop = chrono::high_resolution_clock::now();
			if (comparepass == password) {
				if (linecount <= 10000) {
					auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
					timer1 += duration.count();
					correct++;
				}
				if (linecount > 10000) {
					auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
					timer2 += duration.count();
					correct2++;
				}
			}

			if (nomatch) {
				break;
			}
		}
		linecount++;
	}

	double pcent1 = ((correct / 10000) * 100);
	double pcent2 = ((correct2 / 10000) * 100);
	cout << "Number of passwords correct in set 1 = " << correct << " Percentage correct = " << pcent1 << "%" << endl;
	cout << "Number of passwords correct in set 2 = " << correct2 << " Percentage correct = " << pcent2 << "%" << endl;
	double avg1 = ((timer1/1000) / correct);
	double avg2 = ((timer2/1000) / correct2);
	cout << "Average time to crack password for set 1: " << avg1 << "ms" << endl;
	cout << "Average time to crack password for set 2: " << avg2 << "ms" << endl;
	afile.close();

}



