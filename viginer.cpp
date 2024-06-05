#include <iostream>
#include <string>
#include <fstream>
#include "windows.h"
#include "Header1.h"

using namespace std;

extern const char* SYSTEM_CLEAR;

string code(const string& text, const string& key) {
    string encoded;
    for (int i = 0; i < text.length(); i++) {
        encoded += (((int)(text[i]) + (int)(key[i % key.length()])) % 256);
    } // к символу текста добавляем символ ключа и делим на 256 чтоб всегда оставаться в диапазоне символов ASCII
    return encoded;
}

string decode(const string& text, const string& key) {
    string decoded;
    for (int i = 0; i < text.length(); i++)
    {
        decoded += (((int)(text[i]) - (int)(key[i % key.length()]) + 256) % 256);
    } // вычитаем из зашифр текста ключ + 256 чтоб всегда были положительные значения и делим на 256 чтоб оставаться в диапазоне
    decoded = decoded.substr(0, decoded.length() - 1);
    return decoded;
}

void viginer(string& password) {
    string text, key, userPass, fname;
    int getChoice, getAction;
    while (true) {
        try {
            system(SYSTEM_CLEAR);
            cout << "------------------MENU------------------" << endl;
            cout << "Шифр Виженера" << endl;
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
                cin >> userPass;
                if (userPass != password) {
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

                    cout << "Введите ключ: ";
                    getline(cin, key);
                    for (auto& i : key) {
                        if (i >= 48 && i <= 57) {
                            throw logic_error("Ключ должен состоять из букв!");
                        }
                    }
                    string encodedText = readFromFile("plaintext.txt");
                    string encoded = code(encodedText, key);

                    writeToFile("VIGencrypted.txt", encoded);

                    cout << "Зашифрованный текст записан в файл VIGencrypted.txt "<< endl;
                    Sleep(2000);
                }
                else if (getAction == 2) {
                    cout << "Введите имя файла: ";
                    cin >> fname;
                    cin.ignore(256, '\n');
                    string encodedText = readFromFile(fname);

                    cout << "Введите ключ: ";
                    getline(cin, key);
                    for (auto& i : key) {
                        if (i >= 48 && i <= 57) {
                            throw logic_error("Ключ должен состоять из букв!");
                        }
                    }
                    string encoded = code(encodedText, key);
                    writeToFile("VIGencrypted.txt", encoded);

                    cout << "Зашифрованный текст записан в файл VIGencrypted.txt " << endl;
                    Sleep(2000);
                }
                else if (cin.peek() != '\n' || cin.fail()) {
                    throw logic_error("Вы ввели строку");
                }
            }
            else if (getChoice == 2) {
                cin.ignore(256, '\n');
                cout << "Введите пароль: ";
                cin >> userPass;
                if (userPass != password) {
                    throw logic_error("Неверный пароль");
                }
                cout << "Введите ключ: ";
                cin.ignore(256, '\n');
                getline(cin, key);
                for (auto& i : key) {
                    if (i >= 48 && i <= 57) {
                        throw logic_error("Ключ должен состоять из букв!");
                    }
                }
                string encodedText = readFromFile("VIGencrypted.txt");
                string decoded = decode(encodedText, key);

                writeToFile("VIGdecrypted.txt", decoded);

                cout << "Расшифрованный текст записан в файл VIGdecrypted.txt" << endl;
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
