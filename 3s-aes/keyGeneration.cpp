#include <bits/stdc++.h>
#include <vector>
using namespace std;
vector<vector<int>> S = {{9, 4, 10, 11},
                             {13, 1, 8, 5},
                             {6, 2, 0, 3},
                             {12, 14, 15, 7}};

vector<vector<int>> Me = {{1,4}, {4,1}};

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

vector<int> RotNib(vector<int> x)
{
    vector<int> res(x.size(), -1);
    vector<int> left(4, -1);
    vector<int> right(4, -1);

    for (int i = 0; i < 4; i++)
    {
        left[i] = x[i];
        right[i] = x[i + 4];
    }
    for (int i = 0; i < 4; i++)
    {
        res[i] = right[i];
    }
    for (int i = 0; i < 4; i++)
    {
        res[i + 4] = left[i];
    }
    return res;
}
vector<int> substitution(vector<vector<int>> S, vector<int> x)
{

    int r = x[0] * 2 + x[1];
    int c = x[2] * 2 + x[3];

    int val1 = S[r][c];

    vector<int> temp(4, 0);
    int i = 0;
    while (val1 > 0)
    {
        temp[i] = val1 % 2;
        val1 = val1 / 2;
        i++;
    }
    vector<int> binaryNum(4, 0);
    i = 0;
    for (int j = temp.size() - 1; j >= 0; j--)
    {
        binaryNum[i] = temp[j];
        i++;
    }
    return binaryNum;
}

vector<int> SubNib(vector<int> w, vector<vector<int>> S)
{

    vector<int> RotNible = RotNib(w);
  
    vector<int> left(4, -1);
    vector<int> right(4, -1);
    for (int i = 0; i < 4; i++)
    {
        left[i] = RotNible[i];
        right[i] = RotNible[i + 4];
    }

    vector<int> leftBin = substitution(S, left);
    vector<int> rightBin = substitution(S, right);

    vector<int> SubNible(8, -1);
    for (int i = 0; i < leftBin.size(); i++)
    {
        SubNible[i] = leftBin[i];
        SubNible[i + 4] = rightBin[i];
    }
    return SubNible;
}
vector<vector<int>> keyGeneration(vector<int> key, vector<vector<int>> S, vector<int> Rcon1, vector<int> Rcon2)
{
    vector<int> key1(16, -1);
    vector<int> key2(16, -1);
    vector<int> key3(16, -1);
    vector<int> w0(8, -1);
    vector<int> w1(8, -1);
    vector<int> w2(8, -1);
    vector<int> w3(8, -1);
    vector<int> w4(8, -1);
    vector<int> w5(8, -1);

    for (int i = 0; i < 8; i++)
    {
        w0[i] = key[i];
        w1[i] = key[i + 8];
    }

    vector<int> tempw2 = performXOR(w0, Rcon1);
    vector<int> subw2 = SubNib(w1, S);
   
    w2 = performXOR(tempw2, subw2);
 
    w3 = performXOR(w1, w2);

    vector<int> tempw4 = performXOR(w2, Rcon2);
    vector<int> subw4 = SubNib(w3, S);
    
    w4 = performXOR(tempw4, subw4);

    w5 = performXOR(w3, w4);

    for (int i = 0; i < w0.size(); i++)
    {
        key1[i] = w0[i];
        key1[i + 8] = w1[i];
    }

    for (int i = 0; i < w2.size(); i++)
    {
        key2[i] = w2[i];
        key2[i + 8] = w3[i];
    }

    for (int i = 0; i < w3.size(); i++)
    {
        key3[i] = w4[i];
        key3[i + 8] = w5[i];
    }

    return {key1, key2, key3};
}

vector<int> ARK(vector<int> x1, vector<int> x2)
{
    vector<int> ans(x1.size(), -1);
    for (int i = 0; i < x1.size(); i++)
    {
        if (x1[i] == x2[i])
        {
            ans[i] = 0;
        }
        else
        {
            ans[i] = 1;
        }
    }
    return ans;
}

vector<int> SubNibE(vector<int> w)
{
  
    vector<int> left(4, -1);
    vector<int> right(4, -1);
    for (int i = 0; i < 4; i++)
    {
        left[i] = w[i];
        right[i] = w[i + 4];
    }

    vector<int> leftBin = substitution(S, left);

    vector<int> rightBin = substitution(S, right);

    vector<int> SubNible(8, -1);
    for (int i = 0; i < leftBin.size(); i++)
    {
        SubNible[i] = leftBin[i];
        SubNible[i + 4] = rightBin[i];
    }
    return SubNible;
}
vector<int>shiftRow(vector<int>x)
{
    vector<int>ans = x;
    for (int i = 4; i < 8; i++)
    {
        ans[i] = x[i+8];
    }
    for (int i = 12; i < 16; i++)
    {
        ans[i] = x[i-8];
    }
    return ans;
    
}
int binaryToDecimal(const vector<int>& binaryVector) {
    int decimalNumber = 0;
    int power = binaryVector.size() - 1; // Start from the most significant bit
    for (int i = 0; i < binaryVector.size(); ++i) {
        decimalNumber += binaryVector[i] * pow(2, power);
        --power;
    }
    return decimalNumber;
}


vector<int>mixedCol(vector<int> x)
{
    vector<int>a1(4,-1);
    vector<int>a2(4,-1);
    vector<int>a3(4,-1);
    vector<int>a4(4,-1);
    for (int i = 0; i < 4; i++)
    {
        a1[i] = x[i];
        a2[i] = x[i+4];
        a3[i] = x[i+8];
        a4[i] = x[i+12];
    }
    int s1 = binaryToDecimal(a1);
    int s2 = binaryToDecimal(a2);
    int s3 = binaryToDecimal(a3);
    int s4 = binaryToDecimal(a4);

    vector<int>matrix = {{s1,s3}, {s2,s4}};

    
    vector<int>matrix = {}

}
void encryption(vector<int> P,  vector<int> key1,  vector<int> key2,  vector<int> key3 )
{
    vector<int> ark = ARK(P,key1);

    vector<int>a1(8,-1);
    vector<int>a2(8,-1);

    for(int i = 0; i< 8;i++)
    {
        a1[i] = ark[i];
        a2[i] = ark[i+8];
    }

    vector<int>subA1 =  SubNibE(a1);
    vector<int>subA2=  SubNibE(a2);
    vector<int> sub (16,-1);
    for (int i = 0; i < 8; i++)
    {
        sub[i] = subA1[i];
        sub[i+8] = subA2[i];
    }

    vector<int>shiftrow = shiftRow(sub);
    for (int i = 0; i < shiftrow.size(); i++)
    {
        cout << shiftrow[i] << " ";
    }

}

int main()
{
    vector<int> key = {0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1};
    vector<int> P = {1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0};
    
    vector<int> Rcon1 = {1, 0, 0, 0, 0, 0, 0, 0};
    vector<int> Rcon2 = {0, 0, 1, 1, 0, 0, 0, 0};

    vector<vector<int>> keys = keyGeneration(key, S, Rcon1, Rcon2);
    vector<int> key1 = keys[0];
    vector<int> key2 = keys[1];
    vector<int> key3 = keys[2];
    encryption(P,key1,key2,key3);

    return 0;
}