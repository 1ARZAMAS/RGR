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
    } // � ������� ������ ��������� ������ ����� � ����� �� 256 ���� ������ ���������� � ��������� �������� ASCII
    return encoded;
}

string decode(const string& text, const string& key) {
    string decoded;
    for (int i = 0; i < text.length(); i++)
    {
        decoded += (((int)(text[i]) - (int)(key[i % key.length()]) + 256) % 256);
    } // �������� �� ������ ������ ���� + 256 ���� ������ ���� ������������� �������� � ����� �� 256 ���� ���������� � ���������
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
            cout << "���� ��������" << endl;
            cout << "�������� ��������: " << endl;
            cout << "1. ����������" << endl;
            cout << "2. ������������" << endl;
            cout << "3. �����" << endl;
            cout << "������� ����� ��������: ";

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
                }
                else if (getAction != 1 && getAction != 2) {
                    throw logic_error("����� �������� ��� � ������!");
                }
                cin.ignore(256, '\n');
                if (getAction == 1) {
                    cout << "������� �����: ";
                    getline(cin, text);
                    writeToFile("plaintext.txt", text);

                    cout << "������� ����: ";
                    getline(cin, key);
                    for (auto& i : key) {
                        if (i >= 48 && i <= 57) {
                            throw logic_error("���� ������ �������� �� ����!");
                        }
                    }
                    string encodedText = readFromFile("plaintext.txt");
                    string encoded = code(encodedText, key);

                    writeToFile("VIGencrypted.txt", encoded);

                    cout << "������������� ����� ������� � ���� VIGencrypted.txt "<< endl;
                    Sleep(2000);
                }
                else if (getAction == 2) {
                    cout << "������� ��� �����: ";
                    cin >> fname;
                    cin.ignore(256, '\n');
                    string encodedText = readFromFile(fname);

                    cout << "������� ����: ";
                    getline(cin, key);
                    for (auto& i : key) {
                        if (i >= 48 && i <= 57) {
                            throw logic_error("���� ������ �������� �� ����!");
                        }
                    }
                    string encoded = code(encodedText, key);
                    writeToFile("VIGencrypted.txt", encoded);

                    cout << "������������� ����� ������� � ���� VIGencrypted.txt " << endl;
                    Sleep(2000);
                }
                else if (cin.peek() != '\n' || cin.fail()) {
                    throw logic_error("�� ����� ������");
                }
            }
            else if (getChoice == 2) {
                cin.ignore(256, '\n');
                cout << "������� ������: ";
                cin >> userPass;
                if (userPass != password) {
                    throw logic_error("�������� ������");
                }
                cout << "������� ����: ";
                cin.ignore(256, '\n');
                getline(cin, key);
                for (auto& i : key) {
                    if (i >= 48 && i <= 57) {
                        throw logic_error("���� ������ �������� �� ����!");
                    }
                }
                string encodedText = readFromFile("VIGencrypted.txt");
                string decoded = decode(encodedText, key);

                writeToFile("VIGdecrypted.txt", decoded);

                cout << "�������������� ����� ������� � ���� VIGdecrypted.txt" << endl;
                Sleep(2000);
            }
        }
        catch (const exception& e) {
            cerr << "������: " << e.what() << endl;
            cin.clear();
            cin.ignore(256, '\n');
        }
    }
}