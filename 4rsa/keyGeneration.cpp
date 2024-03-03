#include <bits/stdc++.h>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
using namespace std;

double d, n, e;
int findGCD(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return findGCD(b, a % b);
    }
}

// int randomE(int phiN)
// {
//     while (true)
//     {
//         int e1 = rand() % (phiN - 1) + 1;
//         // cout << e;
//         if (findGCD(e1, phiN) == 1)
//         {
//             return e1;
//         }
//     }
// }

int findInverse(int a, int b, int *x, int *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1; // To store results of recursive call
    int gcd = findInverse(b % a, a, &x1, &y1);

    // Update x and y using results of
    // recursive call
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

int modulo(int a, int n, int m)
{
    if (n == 0)
    {
        return 1;
    }
    else if (n == 1)
    {
        return a % m;
    }
    else
    {
        if (n % 2 == 0)
        {
            return ((modulo(a, n / 2, m) % m) * (modulo(a, n / 2, m) % m)) % m;
        }
        else
        {
            return ((modulo(a, n / 2, m) % m) * (modulo(a, n / 2, m) % m) * a) % m;
        }
    }
}

void keyGenerate(double p, double q)
{
    int phiN = (p - 1) * (q - 1);
    // cout <<  phiN << endl;
    srand(time(NULL));
    // e = randomE(phiN);
    e  = 2;
    while (e < phiN)
    {
        if (findGCD(e, phiN) == 1)
            break;
        else
            e++;
    }

    // int x, y;
    // d = findInverse(e, phiN, &x, &y);
    int k = 2; // A constant value
	double d = (1 + (k * phiN)) / e;

    vector<double> publicKey = {e, n};
    vector<double> privateKey = {d, p, q};

    cout << "Public key : "
         << "e = " << publicKey[0] << " & n = " << publicKey[1] << endl;
    cout << "Private key : "
         << "d = " << privateKey[0] << " & p = " << privateKey[1] << " & q = " << privateKey[2] << endl;
}
int encrypt(double m)
{
    int c = modulo(m, e, n);

    return c;
}

int decrypt(int c)
{
    // cout << c << " " << d << " " << n << endl;
    int dm = modulo(c, d, n);
    return dm;
}

int main()
{
    double p = 11;
    double q = 17;
    n = p*q;
    double m = 88;
    keyGenerate(p, q);
    double c = encrypt(m);
    double dm = decrypt(c);

    cout << "Original message : " << m << endl;
    cout << "Message before encryption: " << c << endl;
    cout << "Message after decryption : " << dm;

    return 0;
}