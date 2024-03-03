#include<bits/stdc++.h>
#include<iostream>
#include<vector>
using namespace std;

string encryption(string text, int shift)
{
    string res = "";
    
    for (int i = 0; i < text.size(); i++)
    {
        if(text[i] == ' ')
        {
            res+= " ";
        }
        else if(isupper(text[i]))
        {

            res += char(int(text[i] + shift - 65 ) % 26 + 65);
        }
        else
        {
            res += char(int(text[i] + shift - 97) % 26 + 97);
        }
    }

    return res;
    

}


string decryption(string text, int shift)
{
    string res = "";
    for (int i = 0; i < text.size(); i++)
    {
        if(text[i] == ' ')
        {
            res += " ";
        }
        else if(isupper(text[i]))
        {
            res += char(int(text[i] - shift - 65) % 26  + 65);
        }
        else
        {
            res += char(int(text[i] - shift - 97 ) % 26 + 97);
        }
    }
    return res;
}

int main()
{
    int shift;
    string text;
    cout << "Enter the text : "<< endl;
    // cin >> text;
    getline(cin, text);
    cout << "Enter the no of shifts : ";
    cin >> shift;
    string encryptKey =  encryption(text, shift); 
    cout <<  "Encrypted key : " <<  encryptKey << endl;
    cout << "Decrypted key : " << decryption(encryptKey, shift);

    

    return 0;
}