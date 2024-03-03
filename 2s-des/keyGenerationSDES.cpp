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

void keyGeneration(vector<int> arrBit, vector<int> p10, vector<int> p8)
{
    vector<int> key(10, -1);

    key = permutate10(arrBit, p10);

    // cout << "Key: ";
    // for (int i = 0; i < key.size(); i++)
    // {
    //     cout << key[i] << " ";
    // }

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
    cout << endl;
    cout << "Key 1: ";
    for (int i = 0; i < key1.size(); i++)
    {
        cout << key1[i] << " ";
    }

    vector<int> ls2 = leftShift(left, 2);
    vector<int> rs2 = leftShift(right, 2);

    for (int i = 0; i < left.size(); i++)
    {
        key[i] = ls2[i];
        key[i + 5] = rs2[i];
    }

    vector<int> key2 = permutate8(key, p8);
    cout << endl;
    cout << "Key 2: ";
    for (int i = 0; i < key2.size(); i++)
    {
        cout << key2[i] << " ";
    }
}

int main()
{
    vector<int> key = {1, 0, 1, 0, 0, 0, 0, 0, 1, 0};

    vector<int> p10 = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    vector<int> p8 = {6, 3, 7, 4, 8, 5, 10, 9};

    keyGeneration(key, p10, p8);

    return 0;
}