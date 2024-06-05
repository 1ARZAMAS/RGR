#pragma once
void writeToFile(const std::string& filename, const std::string& content);
std::string readFromFile(const std::string& filename);
bool isPrime(int num);
int getRandomNumber(int min, int max);
int NOD(int firstNum, int secondNum);
int EilerFunc(int p);
int extendedEuclid(int firstNum, int secondNum, int& firstCoef, int& secondCoef);
int modInverse(int randE_open, int phi_N);
long long modPower(long long base, long long exp, long long mod);
