#include <bits/stdc++.h>
using namespace std;

int main()
{
    string message;
    string key;

    //* Getting the message and key from the user

    cout << "Enter the message to encrypt: ";
    getline(cin, message);

    cout << "Enter the key: ";
    getline(cin, key);

    //* Removing the space from the key and message and transfroming them to capital letter

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

    int order[keyLen];
    for (int i = 0; i < keyLen; i++)
        order[i] = key[i] - 'A';

    int indexOrder[keyLen];
    for (int i = 0; i < keyLen; i++)
    {
        indexOrder[i] = i;
    }

    for (int i = 0; i < keyLen - 1; i++)
    {
        for (int j = i + 1; j < keyLen; j++)
        {
            if (order[i] > order[j])
            {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
                temp = indexOrder[i];
                indexOrder[i] = indexOrder[j];
                indexOrder[j] = temp;
            }
        }
    }

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
            cout << block[j][indexOrder[i]] << " ";
        }
    }

    return 0;
}
