#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "windows.h"
#include "Header2.h"

using namespace std;
extern const char* SYSTEM_CLEAR;

string code(const string& text, int randE_open, int N) {
    string encoded;
    for (char c : text) {
        long long M = static_cast<long long>(c);
        long long C = modPower(M, randE_open, N);
        encoded = encoded + to_string(C) + ' ';
    }
    return encoded;
}

string decode(const string& text, int inversedD_closed, int N) {
    string decoded;
    istringstream iss(text);
    long long num;
    while (iss >> num) {
        long long decSymb = modPower(num, inversedD_closed, N);
        decoded += static_cast<char>(decSymb);
    }
    return decoded;
}

void rsa(string& password) {
    string text, userpass, fname;
    int getChoice, getAction;
    int min = 5000, max = 10000;
    int randP = getRandomNumber(min, max), randQ = getRandomNumber(min, max);
    int N = randP * randQ;
    int phi_N = EilerFunc(randP) * EilerFunc(randQ);
    int randE_open = getRandomNumber(min, phi_N);
    while (NOD(phi_N, randE_open) != 1) {
        randE_open = getRandomNumber(min, phi_N);
    }
    int inversedD_closed = modInverse(randE_open, phi_N);

    while (true) {
        try {
            system(SYSTEM_CLEAR);
            cout << "------------------MENU------------------" << endl;
            cout << "Шифр RSA" << endl;
            cout << "Выберите операцию: " << endl;
            cout << "1. Шифрование" << endl;
            cout << "2. Дешифрование" << endl;
            cout << "3. Выход" << endl;
            cout << "Введите номер операции: ";

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
                cin >> userpass;
                if (userpass != password) {
                    throw logic_error("Неверный пароль");
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
                }
                else if (getAction != 1 && getAction != 2) {
                    throw logic_error("Такой операции нет в списке!");
                }
                cin.ignore(256, '\n');

                if (getAction == 1) {
                    cout << "Введите текст: ";
                    getline(cin, text);
                    writeToFile("plaintext.txt", text);

                    string encodedText = readFromFile("plaintext.txt");
                    string encoded = code(encodedText, randE_open, N);

                    writeToFile("RSAencrypted.txt", encoded);
                    cout << "Зашифрованный текст записан в файл RSAencrypted.txt" << endl;
                    Sleep(2000);
                }
                else if (getAction == 2) {
                    cout << "Введите имя файла: ";
                    cin >> fname;
                    cin.ignore(256, '\n');

                    string encodedText = readFromFile(fname);

                    string encoded = code(encodedText, randE_open, N);
                    writeToFile("RSAencrypted.txt", encoded);

                    cout << "Зашифрованный текст записан в файл RSAencrypted.txt" << endl;
                    Sleep(2000);
                }
                else if (cin.peek() != '\n' || cin.fail()) {
                    throw logic_error("Вы ввели строку");
                }
            }
            else if (getChoice == 2) {
                cin.ignore(256, '\n');
                cout << "Введите пароль: ";
                cin >> userpass;
                if (userpass != password) {
                    throw logic_error("Неверный пароль");
                }
                string encodedText = readFromFile("RSAencrypted.txt");
                string decoded = decode(encodedText, inversedD_closed, N);

                writeToFile("RSAdecrypted.txt", decoded);
                cout << "Расшифрованный текст записан в файл RSAdecrypted.txt" << endl;
                Sleep(2000);
            }
        }
        catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
            cin.clear();
            cin.ignore(256, '\n');
        }
    }
}
