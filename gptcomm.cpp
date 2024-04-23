#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <regex>
using namespace std;

bool validKey(string str)
{
    regex validPattern("[a-zA-Z]+");
    if (regex_match(str, validPattern))
    {
        unordered_map<char, int> mp;
        for (int i = 0; i < str.length(); i++)
        {
            if (mp.find(str[i]) != mp.end())
                return false;
            mp[str[i]] = 1;
        }
        return true;
    }
    return false;
}

int main()
{
    string message;
    string key;
    regex validMessage("[a-zA-Z]+");
    //* Getting the message and key from the user
    while (message.empty() || !regex_match(message, validMessage))
    {
        std::cout << "Enter the message to encrypt: ";
        getline(cin, message);
    }

    while (key.empty() || !validKey(key))
    {
        std::cout << "Enter the key: ";
        getline(cin, key);
    }

    //* Removing the space from the key and message and transforming them to capital letter

    key.erase(remove(key.begin(), key.end(), ' '), key.end());
    message.erase(remove(message.begin(), message.end(), ' '), message.end());

    transform(key.begin(), key.end(), key.begin(), ::toupper);
    transform(message.begin(), message.end(), message.begin(), ::toupper);

    //* Making 2D vector to store the message

    int keyLen = key.length();
    int msgLen = message.length();
    int rowNumber = (msgLen + keyLen - 1) / keyLen;

    vector<vector<char>> block(rowNumber, vector<char>(keyLen, 'X'));

    int k = 0;
    for (int i = 0; i < rowNumber; i++)
    {
        for (int j = 0; j < keyLen; j++)
        {
            if (k < msgLen)
                block[i][j] = message[k++];
        }
    }

    //* Finding the order in the Key
    vector<pair<char, int>> order;
    for (int i = 0; i < keyLen; i++)
        order.push_back({key[i], i});

    sort(order.begin(), order.end());

    //* Printing the 2D Vector

    cout << "\nBlock: " << endl;

    for (auto i : block)
    {
        for (auto j : i)
        {
            cout << j << " ";
        }
        cout << endl;
    }

    //* Iterating through the 2D vector using the Key order to get the Ciphertext

    cout << "\nEncrypted message: ";
    for (int i = 0; i < keyLen; i++)
    {
        for (int j = 0; j < rowNumber; j++)
        {
            cout << block[j][order[i].second] << " ";
        }
    }

    return 0;
}
