#include <bits/stdc++.h>
using namespace std;

int main()
{
    string message;
    string key;

    cout << "Enter the message to encrypt: ";
    getline(cin, message);

    cout << "Enter the key: ";
    getline(cin, key);

    key.erase(remove(key.begin(), key.end(), ' '), key.end());
    message.erase(remove(message.begin(), message.end(), ' '), message.end());

    transform(key.begin(), key.end(), key.begin(), ::toupper);
    transform(message.begin(), message.end(), message.begin(), ::toupper);

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

    cout << "\nBlock: " << endl;

    for (auto i : block)
    {
        for (auto j : i)
        {
            cout << j << " ";
        }
        cout << endl;
    }

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
