#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <sstream>
#include "Header2.h"

using namespace std;

bool isPrime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

int getRandomNumber(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(min, max);

    while (true) {
        int num = dist(gen);
        if (isPrime(num)) return num;
    }
}

int NOD(int firstNum, int secondNum) {
    if (firstNum % secondNum == 0) return secondNum;
    if (secondNum % firstNum == 0) return firstNum;
    if (firstNum > secondNum) return NOD(firstNum % secondNum, secondNum);
    return NOD(firstNum, secondNum % firstNum);
}

int EilerFunc(int p) {
    int result = p;
    for (int i = 2; i * i <= p; i++) {
        if (p % i == 0) {
            while (p % i == 0) p /= i;
            result -= result / i;
        }
    }
    if (p > 1) result -= result / p;
    return result;
}

int extendedEuclid(int firstNum, int secondNum, int& firstCoef, int& secondCoef) {
    if (secondNum == 0) {
        firstCoef = 1;
        secondCoef = 0;
        return firstNum;
    }

    int firstCoef1, secondCoef1;
    int gcd = extendedEuclid(secondNum, firstNum % secondNum, firstCoef1, secondCoef1);

    firstCoef = secondCoef1;
    secondCoef = firstCoef1 - (firstNum / secondNum) * secondCoef1;

    return gcd;
}

int modInverse(int randE_open, int phi_N) {
    int firstCoef, secondCoef;
    int gcd = extendedEuclid(randE_open, phi_N, firstCoef, secondCoef);

    if (gcd != 1) {
        cout << "Обратный элемент не существует, так как randE_open и phi_N не взаимно просты." << endl;
        return -1;
    }
    else {
        return (firstCoef % phi_N + phi_N) % phi_N;
    }
}

// Функция для возведения в степень по модулю
long long modPower(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}
