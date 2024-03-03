#include <bits/stdc++.h>
#include <vector>
using namespace std;

vector<int> permutate10(vector<int> arrBit, vector<int> p10)
{
    vector<int> res(10, -1);
    for (int i = 0; i < p10.size(); i++)
    {
        res[i] = arrBit[p10[i] - 1];
    }
    return res;
}

vector<int> permutate8(vector<int> arrBit, vector<int> p8)
{
    vector<int> res(8, -1);
    for (int i = 0; i < p8.size(); i++)
    {
        res[i] = arrBit[p8[i] - 1];
    }
    return res;
}

vector<int> leftShift(vector<int> arr, int n)
{
    while (n > 0)
    {
        int temp = arr[0];
        for (int i = 0; i < arr.size() - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        arr[arr.size() - 1] = temp;
        n--;
    }
    return arr;
}

vector<vector<int>> keyGeneration(vector<int> arrBit, vector<int> p10, vector<int> p8)
{
    vector<int> key(10, -1);

    key = permutate10(arrBit, p10);

    vector<int> left(5, -1);
    vector<int> right(5, -1);

    for (int i = 0; i < left.size(); i++)
    {
        left[i] = key[i];
        right[i] = key[i + 5];
    }

    left = leftShift(left, 1);
    right = leftShift(right, 1);

    for (int i = 0; i < left.size(); i++)
    {
        key[i] = left[i];
        key[i + 5] = right[i];
    }

    vector<int> key1 = permutate8(key, p8);
    // cout << endl;

    vector<int> ls2 = leftShift(left, 2);
    vector<int> rs2 = leftShift(right, 2);

    for (int i = 0; i < left.size(); i++)
    {
        key[i] = ls2[i];
        key[i + 5] = rs2[i];
    }

    vector<int> key2 = permutate8(key, p8);
    return {key1, key2};
}

vector<vector<int>> generateIP(vector<int> p, vector<int> IP)
{
    vector<int> res(8, -1);
    for (int i = 0; i < p.size(); i++)
    {
        res[i] = p[IP[i] - 1];
    }

    vector<int> leftNible(4, -1);
    vector<int> rightNible(4, -1);

    for (int i = 0; i < leftNible.size(); i++)
    {
        leftNible[i] = res[i];
        rightNible[i] = res[i + 4];
    }

    return {leftNible, rightNible};
}

vector<int> performXOR(vector<int> x1, vector<int> x2)
{
    int i = 0;
    vector<int> res(x1.size(), -1);
    for (int i = 0; i < x1.size(); i++)
    {
        if (x1[i] == x2[i])
        {
            res[i] = 0;
        }
        else
        {
            res[i] = 1;
        }
    }
    return res;
}

vector<int> substitution(vector<vector<int>> s, vector<int> x)
{

    int r = x[0] * 2 + x[3];
    int c = x[1] * 2 + x[2];

    int val1 = s[r][c];

    vector<int> temp(2, 0);
    int i = 0;
    while (val1 > 0)
    {
        temp[i] = val1 % 2;
        val1 = val1 / 2;
        i++;
    }
    vector<int> binaryNum(2, 0);
    i = 0;
    for (int j = temp.size() - 1; j >= 0; j--)
    {
        binaryNum[i] = temp[j];
        i++;
    }
    return binaryNum;
}
vector<int> permutate4(vector<int> arrBit, vector<int> p4)
{
    vector<int> res(4, -1);
    for (int i = 0; i < p4.size(); i++)
    {
        res[i] = arrBit[p4[i] - 1];
    }
    return res;
}

vector<vector<int>> fk(vector<int> leftNible, vector<int> rightNible, vector<int> IP, vector<int> EP, vector<int> key2,
                       vector<vector<int>> s0, vector<vector<int>> s1, vector<int> p4)
{

    vector<int> expanded(8, -1);
    for (int i = 0; i < expanded.size(); i++)
    {
        expanded[i] = rightNible[EP[i] - 1];
    }

    vector<int> afterXOR = performXOR(expanded, key2);
    // cout << endl;

    vector<int> lx(4, -1);
    vector<int> rx(4, -1);

    for (int i = 0; i < lx.size(); i++)
    {
        lx[i] = afterXOR[i];
        rx[i] = afterXOR[i + 4];
    }

    vector<int> ls = substitution(s0, lx);

    vector<int> rs = substitution(s1, rx);

    vector<int> sub(4, -1);
    for (int i = 0; i < ls.size(); i++)
    {
        sub[i] = ls[i];
        sub[i + 2] = rs[i];
    }
    sub = permutate4(sub, p4);

    vector<int> sw = performXOR(sub, leftNible);

    return {sw, rightNible};
}

void decryption(vector<int> p, vector<int> IP, vector<int> IPI, vector<int> EP, vector<int> key1, vector<int> key2,
                vector<vector<int>> s0, vector<vector<int>> s1, vector<int> p4)
{
    vector<vector<int>> afterIP = generateIP(p, IP);
    vector<int> leftNible = afterIP[0];
    vector<int> rightNible = afterIP[1];

    vector<vector<int>> phisher = fk(leftNible, rightNible, IP, EP, key2, s0, s1, p4);

    vector<int> left = phisher[1];
    vector<int> right = phisher[0];

    vector<vector<int>> answer = fk(left, right, IP, EP, key1, s0, s1, p4);

    vector<int> leftans = answer[0];
    vector<int> rightans = answer[1];
    vector<int> ips(8, -1);
    for (int i = 0; i < leftans.size(); i++)
    {
        ips[i] = leftans[i];
        ips[i + 4] = rightans[i];
    }

    vector<vector<int>> result = generateIP(ips, IPI);
    cout << "Plain text : ";
    for (auto it : result)
    {
        for (auto m : it)
        {
            cout << m << " ";
        }
    }
}
int main()
{
    vector<int> key = {1, 0, 1, 0, 0, 0, 0, 0, 1, 0};
    vector<int> p10 = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    vector<int> p8 = {6, 3, 7, 4, 8, 5, 10, 9};

    vector<int> p4 = {2, 4, 3, 1};
    vector<int> EP = {4, 1, 2, 3, 2, 3, 4, 1};
    vector<int> IP = {2, 6, 3, 1, 4, 8, 5, 7};
    vector<int> IPI = {4, 1, 3, 5, 7, 2, 8, 6};
    vector<int> p = {0,0,0,1,0,1,0,1};

    vector<vector<int>> s0 = {{1, 0, 3, 2},
                              {3, 2, 1, 0},
                              {0, 2, 1, 3},
                              {3, 1, 3, 2}};

    vector<vector<int>> s1 = {{0, 1, 2, 3},
                              {2, 0, 1, 3},
                              {3, 0, 1, 0},
                              {2, 1, 0, 3}};

    vector<vector<int>> keys = keyGeneration(key, p10, p8);
    vector<int> key1 = keys[0];
    vector<int> key2 = keys[1];

    cout << "Cipher text : ";
    for (auto it: p)
    {
        cout << it << " ";
    }
    cout << endl;
    decryption(p, IP, IPI, EP, key1, key2, s0, s1, p4);
    return 0;
}