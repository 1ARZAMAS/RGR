#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "windows.h"
#include "Header1.h"

using namespace std;
extern const char* SYSTEM_CLEAR;

// Функция для удаления символов '_' из строки
string cleanOutput(const string& output) {
	string cleanedOutput = output;
	cleanedOutput.erase(remove(cleanedOutput.begin(), cleanedOutput.end(), '_'), cleanedOutput.end());
	return cleanedOutput;
}

string encodeScytale(string& message, int diameter) {
	int length = message.length();
	int height = (length + diameter - 1) / diameter;
	//высота - это необходимое число для шифровки всего сообщения

	// Создание таблицы для шифрования
	vector<vector<char>> grid(height, vector<char>(diameter, '_'));

	int index = 0;
	for (int j = 0; j < diameter; j++) { // заполняем по столбцам
		for (int i = 0; i < height; i++) {
			if (index < length) {
				if (message[index] == '\n') {
					grid[i][j] = '@'; // Замена символа новой строки на '@'
				}
				else {
					grid[i][j] = message[index];
				}
				index++;
			}
		}
	}

	string encodedMessage = ""; // читаем таблицу по строкам и готовченко
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < diameter; j++) {
			encodedMessage += grid[i][j];
		}
	}
	encodedMessage = encodedMessage.substr(0, encodedMessage.length() - 1); // Удаление последнего символа тк это _
	return encodedMessage;
}

string decodeScytale(string& encodedMessage, int diameter) {
	int length = encodedMessage.length();
	int height = (length + diameter - 1) / diameter;

	vector<vector<char>> grid(height, vector<char>(diameter, '_'));

	int index = 0; // заполняем таблицу по строкам
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < diameter; j++) {
			if (index < length) {
				grid[i][j] = encodedMessage[index++];
			}
		}
	}

	string decodedMessage = ""; // а читам - по столбцам
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
			cout << "Шифр Скитала" << endl;
			cout << "Выберите действие:" << endl;
			cout << "1. Шифрование" << endl;
			cout << "2. Дешифрование" << endl;
			cout << "3. Выход" << endl;
			cout << "Выберите номер операции: ";

			cin >> getChoice;
			if (cin.peek() != '\n' || cin.fail()) {
				throw logic_error("Вы ввели недопустимое значение!");
			}
			if (getChoice == 3) {
				break;
			}
			else if (getChoice != 1 && getChoice != 2) {
				throw logic_error("Такой операции нет в списке!");
			}
			else if (getChoice == 1) {
				cout << "Введите пароль: ";
				cin >> userPass;
				if (userPass != password) {
					throw logic_error("Неверный пароль");
					Sleep(2000);
				}
				system(SYSTEM_CLEAR);
				cout << "------------------MENU------------------" << endl;
				cout << "Выберите ввод: " << endl;
				cout << "1. С консоли" << endl;
				cout << "2. Из файла" << endl;
				cout << "Выберите номер операции: ";

				cin >> getAction;
				if (cin.peek() != '\n' || cin.fail()) {
					throw logic_error("Вы ввели строку");
					Sleep(2000);
				}
				else if (getChoice != 1 && getChoice != 2) {
					throw logic_error("Такой операции нет в списке!");
					Sleep(2000);
				}

				if (getAction == 1) {
					cout << "Введите текст: ";
					cin.ignore();
					getline(cin, message);
					writeToFile("plaintext.txt", message);

					cout << "Введите диаметр скитала: ";

					cin >> diametr1;

					if (cin.fail() || cin.peek() != '\n') {
						throw logic_error("Вы вводите не цифру!");
					}

					string encodedText2 = readFromFile("plaintext.txt");
					string encoded2 = encodeScytale(encodedText2, diametr1);
					string cleanedEncoded2 = cleanOutput(encoded2);

					writeToFile("SKITencrypted.txt", encoded2);
					cout << "Зашифрованный текст записан в файл SKITencrypted.txt " << endl;
					Sleep(2000);
				}
				if (getAction == 2) {
					cout << "Введите название файла с расширением:";
					cin >> filename;
					//if (exists(filename) == false){
					//	throw logic_error("Такого файла не существует или его невозможно открыть!");
					//}
					cin.ignore(256, '\n');
					string encodedText = readFromFile(filename);

					cout << "Введите диаметр скитала: ";
					cin >> diametr2;

					if (cin.fail() || cin.peek() != '\n') {
						throw logic_error("Вы вводите не цифру!");
						Sleep(2000);
					}

					string encoded1 = encodeScytale(encodedText, diametr2);
					string cleanedEncoded2 = cleanOutput(encoded1);

					writeToFile("SKITencrypted.txt", encoded1);
					cout << "Зашифрованный текст записан в файл SKITencrypted.txt" << endl;
					Sleep(2000);
				}
			}
			else if (getChoice == 2) {
				cout << "Введите пароль: ";
				cin >> userPass;
				if (userPass == password) {
					cout << "Введите диаметр скитала: ";
					cin >> diametr2;
					if (cin.fail() || cin.peek() != '\n') {
						throw logic_error("Вы вводите не цифру!");
					}
					string encodedText1 = readFromFile("SKITencrypted.txt");
					string decoded1 = decodeScytale(encodedText1, diametr2);
					string cleanedDecoded1 = cleanOutput(decoded1);
					writeToFile("SKITdecoded.txt", cleanedDecoded1);
					cout << "Расшифрованный текст записан в файл SKITdecoded.txt" << endl;
					Sleep(2000);
				}
				else {
					throw logic_error("Неверный пароль декодирования");
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
