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
            cout << "���� RSA" << endl;
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
                cin >> userpass;
                if (userpass != password) {
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

                    string encodedText = readFromFile("plaintext.txt");
                    string encoded = code(encodedText, randE_open, N);

                    writeToFile("RSAencrypted.txt", encoded);
                    cout << "������������� ����� ������� � ���� RSAencrypted.txt" << endl;
                    Sleep(2000);
                }
                else if (getAction == 2) {
                    cout << "������� ��� �����: ";
                    cin >> fname;
                    cin.ignore(256, '\n');

                    string encodedText = readFromFile(fname);

                    string encoded = code(encodedText, randE_open, N);
                    writeToFile("RSAencrypted.txt", encoded);

                    cout << "������������� ����� ������� � ���� RSAencrypted.txt" << endl;
                    Sleep(2000);
                }
                else if (cin.peek() != '\n' || cin.fail()) {
                    throw logic_error("�� ����� ������");
                }
            }
            else if (getChoice == 2) {
                cin.ignore(256, '\n');
                cout << "������� ������: ";
                cin >> userpass;
                if (userpass != password) {
                    throw logic_error("�������� ������");
                }
                string encodedText = readFromFile("RSAencrypted.txt");
                string decoded = decode(encodedText, inversedD_closed, N);

                writeToFile("RSAdecrypted.txt", decoded);
                cout << "�������������� ����� ������� � ���� RSAdecrypted.txt" << endl;
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
