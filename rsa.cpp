#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "windows.h"
#include "Header1.h"
using namespace std;
const char* SYSTEM_CLEAR = "cls";

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string userpass, userpasssys, password = "nstu1", passForSys = "nstu", joke = "пирожковый колледж";
	char getChoice;
	cout << "Введите пароль для входа в систему: ";
	getline(cin, userpasssys);
	while (userpasssys != passForSys) {
		if (userpasssys == joke) {
			cout << "Какой пирожковый колледж, чел?\nОтчислен\n";
			cout << "       _______\n";
			cout << "      /       \\\n";
			cout << "     /  НКТП   \\\n";
			cout << "    /___________\\\n";
			cout << "    |  _    _   |\n";
			cout << "    | | |  | |  |\n";
			cout << "    | | |  | |  |\n";
			cout << "    |_|_|__|_|__|\n";
			cout << "Вот на что ты променял НГТУ";
			return -10;
		}
		cout << "Неверный пароль!" << endl;
		cout << "Введите пароль для входа в систему: ";
		getline(cin, userpasssys);
	}
	system(SYSTEM_CLEAR);
	while (true) {
		try {
			system(SYSTEM_CLEAR);
			cout << "------------------MENU------------------" << endl;
			cout << "1. Шифр Виженера" << endl;
			cout << "2. Шифр Скитала" << endl;
			cout << "3. Шифр RSA" << endl;
			cout << "4. Выход" << endl;
			cout << "Введите номер операции: ";
			cin >> getChoice;
			if (getChoice != '1' && getChoice != '2' && getChoice != '3' && getChoice != '4') {
				throw logic_error("Такой операции нет в списке");
			}
			else if (getChoice == '4') {
				cout << " ______________\n";
				cout << "|    _         |\n";
				cout << "|   / \\        |     НГТУ НЭТИ\n";
				cout << "|  /   \\       |\n";
				cout << "|       \\   /  |       АВТФ\n";
				cout << "|        \\_/   |\n";
				cout << "|              |\n";
				cout << "----------------\n";
				return 0;
			}
			switch (getChoice) {
			case '1':
			{
				system(SYSTEM_CLEAR);
				viginer(password);
				break;
			}
			case '2':
			{
				system(SYSTEM_CLEAR);
				scytale(password);
				break;
			}
			case '3':
			{
				system(SYSTEM_CLEAR);
				rsa(password);
				break;
			}
			}
		}
		catch (const exception& e) {
			cerr << "Ошибка: " << e.what() << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
	}
}
