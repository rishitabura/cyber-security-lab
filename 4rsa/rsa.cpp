#include <bits/stdc++.h>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
using namespace std;

int findGCD(int a, int b)
{
    int t;
    while (true)
    {
        t = a % b;
        if (t == 0)
            return b;
        a = b;
        b = t;
    }
}


int findInverse(int A, int M)
{
    int i = 1;
    while (true)
    {
        if (A * i % M == 1)
            return i;
        else
            i++;
    }
}

int modulo(int base, int exponent, int mod)
{
    if (mod == 1)
    {
        return 0;
    }

    int result = 1;
    base = base % mod;

    while (exponent > 0)
    {
        result = (base * result) % mod;
        exponent--;
    }

    return result;
}

int main()
{
    double p = 11;
    double q = 17;
    double n = p * q;

    double phiN = (p - 1) * (q - 1);

    cout << "p: " << p << endl;
    cout << "q: " << q << endl;
    cout << "n: " << n << endl;
    cout << "phi: " << phiN << endl;
    srand(time(NULL));
    // e = randomE(phiN);
    double e = 2;
    while (e < phiN)
    {
        if (findGCD(e, phiN) == 1)
            break;
        else
            e++;
    }

    double d = findInverse((int)e, (int)phiN);

    double m = 77;

    double c = modulo((int)m, (int)e, (int)n);
    double dm = modulo((int)c, (int)d, (int)n);

    cout << "e: " << e<< endl;
    cout << "d: " << d << endl;
    cout << "Original message : " << m << endl;
    cout << "Message before encryption: " << c << endl;
    cout << "Message after decryption : " << dm;

    return 0;
}