#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "windows.h"
#include "Header1.h"

using namespace std;
extern const char* SYSTEM_CLEAR;

// ������� ��� �������� �������� '_' �� ������
string cleanOutput(const string& output) {
	string cleanedOutput = output;
	cleanedOutput.erase(remove(cleanedOutput.begin(), cleanedOutput.end(), '_'), cleanedOutput.end());
	return cleanedOutput;
}

string encodeScytale(string& message, int diameter) {
	int length = message.length();
	int height = (length + diameter - 1) / diameter;
	//������ - ��� ����������� ����� ��� �������� ����� ���������

	// �������� ������� ��� ����������
	vector<vector<char>> grid(height, vector<char>(diameter, '_'));

	int index = 0;
	for (int j = 0; j < diameter; j++) { // ��������� �� ��������
		for (int i = 0; i < height; i++) {
			if (index < length) {
				if (message[index] == '\n') {
					grid[i][j] = '@'; // ������ ������� ����� ������ �� '@'
				}
				else {
					grid[i][j] = message[index];
				}
				index++;
			}
		}
	}

	string encodedMessage = ""; // ������ ������� �� ������� � ����������
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < diameter; j++) {
			encodedMessage += grid[i][j];
		}
	}
	encodedMessage = encodedMessage.substr(0, encodedMessage.length() - 1); // �������� ���������� ������� �� ��� _
	return encodedMessage;
}

string decodeScytale(string& encodedMessage, int diameter) {
	int length = encodedMessage.length();
	int height = (length + diameter - 1) / diameter;

	vector<vector<char>> grid(height, vector<char>(diameter, '_'));

	int index = 0; // ��������� ������� �� �������
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < diameter; j++) {
			if (index < length) {
				grid[i][j] = encodedMessage[index++];
			}
		}
	}

	string decodedMessage = ""; // � ����� - �� ��������
	for (int j = 0; j < diameter; j++) {
		for (int i = 0; i < height; i++) {
			if (grid[i][j] == '@') {
				decodedMessage += '\n';
			}
			else {
				decodedMessage += grid[i][j];
			}
		}
	}
	decodedMessage = decodedMessage.substr(0, decodedMessage.length() - 1);
	return decodedMessage;
}


void scytale(string& password) {
	int getChoice, diametr1, diametr2, getAction;
	string userPass, message, filename;
	while (true) {
		try {
			system(SYSTEM_CLEAR);
			cout << "------------------MENU------------------" << endl;
			cout << "���� �������" << endl;
			cout << "�������� ��������:" << endl;
			cout << "1. ����������" << endl;
			cout << "2. ������������" << endl;
			cout << "3. �����" << endl;
			cout << "�������� ����� ��������: ";

			cin >> getChoice;
			if (cin.peek() != '\n' || cin.fail()) {
				throw logic_error("�� ����� ������������ ��������!");
			}
			if (getChoice == 3) {
				break;
			}
			else if (getChoice != 1 && getChoice != 2) {
				throw logic_error("����� �������� ��� � ������!");
			}
			else if (getChoice == 1) {
				cout << "������� ������: ";
				cin >> userPass;
				if (userPass != password) {
					throw logic_error("�������� ������");
					Sleep(2000);
				}
				system(SYSTEM_CLEAR);
				cout << "------------------MENU------------------" << endl;
				cout << "�������� ����: " << endl;
				cout << "1. � �������" << endl;
				cout << "2. �� �����" << endl;
				cout << "�������� ����� ��������: ";

				cin >> getAction;
				if (cin.peek() != '\n' || cin.fail()) {
					throw logic_error("�� ����� ������");
					Sleep(2000);
				}
				else if (getChoice != 1 && getChoice != 2) {
					throw logic_error("����� �������� ��� � ������!");
					Sleep(2000);
				}

				if (getAction == 1) {
					cout << "������� �����: ";
					cin.ignore();
					getline(cin, message);
					writeToFile("plaintext.txt", message);

					cout << "������� ������� �������: ";

					cin >> diametr1;

					if (cin.fail() || cin.peek() != '\n') {
						throw logic_error("�� ������� �� �����!");
					}

					string encodedText2 = readFromFile("plaintext.txt");
					string encoded2 = encodeScytale(encodedText2, diametr1);
					string cleanedEncoded2 = cleanOutput(encoded2);

					writeToFile("SKITencrypted.txt", encoded2);
					cout << "������������� ����� ������� � ���� SKITencrypted.txt " << endl;
					Sleep(2000);
				}
				if (getAction == 2) {
					cout << "������� �������� ����� � �����������:";
					cin >> filename;
					//if (exists(filename) == false){
					//	throw logic_error("������ ����� �� ���������� ��� ��� ���������� �������!");
					//}
					cin.ignore(256, '\n');
					string encodedText = readFromFile(filename);

					cout << "������� ������� �������: ";
					cin >> diametr2;

					if (cin.fail() || cin.peek() != '\n') {
						throw logic_error("�� ������� �� �����!");
						Sleep(2000);
					}

					string encoded1 = encodeScytale(encodedText, diametr2);
					string cleanedEncoded2 = cleanOutput(encoded1);

					writeToFile("SKITencrypted.txt", encoded1);
					cout << "������������� ����� ������� � ���� SKITencrypted.txt" << endl;
					Sleep(2000);
				}
			}
			else if (getChoice == 2) {
				cout << "������� ������: ";
				cin >> userPass;
				if (userPass == password) {
					cout << "������� ������� �������: ";
					cin >> diametr2;
					if (cin.fail() || cin.peek() != '\n') {
						throw logic_error("�� ������� �� �����!");
					}
					string encodedText1 = readFromFile("SKITencrypted.txt");
					string decoded1 = decodeScytale(encodedText1, diametr2);
					string cleanedDecoded1 = cleanOutput(decoded1);
					writeToFile("SKITdecoded.txt", cleanedDecoded1);
					cout << "�������������� ����� ������� � ���� SKITdecoded.txt" << endl;
					Sleep(2000);
				}
				else {
					throw logic_error("�������� ������ �������������");
				}
			}
			else if (getChoice == 3) {
				system(SYSTEM_CLEAR);
				break;
			}
		}
		catch (const exception& e) {
			cerr << e.what() << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
	}
}