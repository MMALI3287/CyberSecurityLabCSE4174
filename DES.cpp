#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

vector<vector<int>> manglerFunction(vector<int> S, vector<int> F)
{
    vector<vector<int>> sBox = {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}};

    vector<int> pBox = {
        16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
        2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};
    vector<vector<int>> result;
    vector<int> temp;
    for (int i = 0; i < S.size(); i++)
    {
        temp.push_back(S[i] ^ F[i]);
    }
    for (int i = 0; i < temp.size(); i++)
    {
        temp[i] = sBox[i / 4][temp[i]];
    }
    for (int i = 0; i < temp.size(); i++)
    {
        temp[i] = temp[i] << 1 | temp[i] >> 31;
    }
    for (int i = 0; i < temp.size(); i++)
    {
        result.push_back({temp[pBox[i] - 1]});
    }
    return result;
}
vector<int> initialPermutation(vector<int> plainText)
{
    vector<int> ipTable = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};
    vector<int> permutedPlainText(64);

    for (int i = 0; i < 64; i++)
    {
        permutedPlainText[i] = plainText[ipTable[i] - 1];
    }

    return permutedPlainText;
}

vector<int> getL(vector<int> ip)
{
    vector<int> l(32);
    for (int i = 0; i < 32; i++)
    {
        l[i] = ip[i];
    }
    return l;
}

vector<int> getR(vector<int> ip)
{
    vector<int> r(32);
    for (int i = 32; i < 64; i++)
    {
        r[i - 32] = ip[i];
    }
    return r;
}

vector<int> permutedChoice1(vector<int> key)
{
    vector<int> pc1Table = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};
    vector<int> permutedKey(56);

    for (int i = 0; i < 56; i++)
    {
        permutedKey[i] = key[pc1Table[i] - 1];
    }

    return permutedKey;
}

vector<int> getC(vector<int> pc1)
{
    vector<int> c(28);
    for (int i = 0; i < 28; i++)
    {
        c[i] = pc1[i];
    }
    return c;
}

vector<int> getD(vector<int> pc1)
{
    vector<int> d(28);
    for (int i = 28; i < 56; i++)
    {
        d[i - 28] = pc1[i];
    }
    return d;
}

vector<int> permutedChoice2(vector<int> key)
{
    vector<int> pc2Table = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};
    vector<int> permutedKey(48);
    for (int i = 0; i < 48; i++)
    {
        permutedKey[i] = key[pc2Table[i] - 1];
    }
    return permutedKey;
}

vector<int> swap32bit(vector<int> round16out)
{
    vector<int> swapped(64);
    for (int i = 0; i < 32; i++)
    {
        swapped[i] = round16out[i + 32];
    }
    for (int i = 32; i < 64; i++)
    {
        swapped[i] = round16out[i - 32];
    }
    return swapped;
}

vector<int> reverseInitialPermutation(vector<int> swapped)
{
    vector<int> ipTable = {40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31, 38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29, 36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27, 34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};
    vector<int> result;
    vector<int> temp;
    for (int i = 0; i < swapped.size(); i++)
    {
        temp.push_back(swapped[ipTable[i] - 1]);
    }
    for (int i = 0; i < temp.size(); i++)
    {
        result.push_back({temp[i]});
    }
    return result;
}

vector<int> DESencrypt(vector<int> plainText, vector<int> key)
{
    vector<int> ip = initialPermutation(plainText);
    vector<int> pc1 = permutedChoice1(key);
    vector<int> L0 = getL(ip);
    vector<int> R0 = getR(ip);
    vector<int> C = getC(pc1);
    vector<int> D = getD(pc1);

    for (int i = 0; i < 16; i++)
    {
        vector<int> L1 = R0;
        vector<int> E = expand(R0);                      // You need to implement the expand function
        vector<int> K = permutedChoice2(shift(C, D, i)); // You need to implement the shift function
        vector<int> S = manglerFunction(E, K);
        vector<int> P = permute(S);         // You need to implement the permute function
        vector<int> R1 = xorVectors(L0, P); // You need to implement the xorVectors function

        L0 = L1;
        R0 = R1;
    }

    vector<int> final = concatenate(L0, R0); // You need to implement the concatenate function
    vector<int> swapped = swap32bit(final);
    vector<int> result = reverseInitialPermutation(swapped);

    return result;
}
int main()
{
    string plainText;
    vector<int> key = {0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
    cout << "Enter plain text in ASCII: ";
    getline(cin, plainText);

    vector<vector<int>> plainTextVector;

    for (int i = 0; i < plainText.length(); i++)
    {
        bitset<8> binary(plainText[i]);
        for (int j = 7; j >= 0; j--)
        {
            plainTextVector.push_back({static_cast<int>(binary[j])});
        }
    }

    vector<vector<int>> chunks;
    vector<int> chunk;
    int chunkCounter = 1;
    for (int i = 0; i < plainTextVector.size(); i++)
    {
        chunk.push_back(plainTextVector[i][0]);
        if (chunk.size() == 64)
        {
            cout << "Chunk " << chunkCounter << ": ";
            for (auto bit : chunk)
            {
                cout << bit << " ";
            }
            cout << endl;
            chunks.push_back(chunk);
            chunk.clear();
            chunkCounter++;
        }
    }

    while (chunk.size() < 64)
    {
        chunk.push_back(1);
        for (int i = 0; i < 7; i++)
        {
            chunk.push_back(0);
        }
    }
    chunks.push_back(chunk);

    vector<vector<int>> cipherText;
    for (auto chunk : chunks)
    {
        cipherText.push_back(DESencrypt(chunk, key));
    }

    return 0;
}