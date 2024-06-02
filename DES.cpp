#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

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

vector<int> concatenate(vector<int> C, vector<int> D)
{
    vector<int> concatenated;
    concatenated.reserve(C.size() + D.size());

    concatenated.insert(concatenated.end(), C.begin(), C.end());
    concatenated.insert(concatenated.end(), D.begin(), D.end());

    return concatenated;
}

vector<int> leftCircularShift(vector<int> C, vector<int> D, int l)
{
    vector<int> shiftedC(28);
    vector<int> shiftedD(28);

    if (l == 0 || l == 1 || l == 8 || l == 15)
    {
        for (int i = 0; i < 28; i++)
        {
            if (i == 27)
            {
                shiftedC[i] = C[0];
                shiftedD[i] = D[0];
            }
            else
            {
                shiftedC[i] = C[i + 1];
                shiftedD[i] = D[i + 1];
            }
        }
    }
    else
    {
        for (int i = 0; i < 28; i++)
        {
            if (i == 26)
            {
                shiftedC[i] = C[0];
                shiftedD[i] = D[0];
            }
            else if (i == 27)
            {
                shiftedC[i] = C[1];
                shiftedD[i] = D[1];
            }
            else
            {
                shiftedC[i] = C[i + 2];
                shiftedD[i] = D[i + 2];
            }
        }
    }

    vector<int> shifted = concatenate(shiftedC, shiftedD);

    return shifted;
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

vector<vector<int>> generateSubkeys(vector<int> key)
{
    vector<int> pc1 = permutedChoice1(key);
    vector<int> C = getC(pc1);
    vector<int> D = getD(pc1);

    vector<vector<int>> subkeys;
    for (int i = 0; i < 16; i++)
    {
        vector<int> shifted = leftCircularShift(C, D, i);
        vector<int> subkey = permutedChoice2(shifted);
        subkeys.push_back(subkey);
        C = getC(shifted);
        D = getD(shifted);
    }

    return subkeys;
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

vector<int> expand(vector<int> R0)
{
    vector<int> eTable = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};
    vector<int> expanded(48);

    for (int i = 0; i < 48; i++)
    {
        expanded[i] = R0[eTable[i] - 1];
    }

    return expanded;
}

vector<int> get48bitXOR(vector<int> R0, vector<int> K)
{
    vector<int> result(48);
    for (int i = 0; i < 48; i++)
    {
        result[i] = R0[i] ^ K[i];
    }
    return result;
}

vector<int> sBox(vector<int> R0, int sBoxNumber)
{
    const vector<vector<vector<int>>> sBoxes = {{{{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
                                                  {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
                                                  {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
                                                  {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
                                                 {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
                                                  {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
                                                  {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
                                                  {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
                                                 {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
                                                  {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
                                                  {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
                                                  {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
                                                 {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
                                                  {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
                                                  {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
                                                  {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
                                                 {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
                                                  {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
                                                  {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
                                                  {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
                                                 {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
                                                  {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
                                                  {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
                                                  {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
                                                 {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
                                                  {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
                                                  {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
                                                  {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
                                                 {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
                                                  {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
                                                  {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
                                                  {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}}};

    int row = 2 * R0[0] + R0[5];
    int column = 8 * R0[1] + 4 * R0[2] + 2 * R0[3] + R0[4];

    int sBoxOutput = sBoxes[sBoxNumber][row][column];

    vector<int> sBoxOutputBits(4);
    for (int i = 0; i < 4; i++)
    {
        sBoxOutputBits[3 - i] = sBoxOutput % 2;
        sBoxOutput /= 2;
    }

    return sBoxOutputBits;
}

vector<int> permutation(vector<int> R0)
{
    vector<int> pTable = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};
    vector<int> permuted(32);

    for (int i = 0; i < 32; i++)
    {
        permuted[i] = R0[pTable[i] - 1];
    }

    return permuted;
}

vector<int> get32bitXOR(vector<int> L0, vector<int> P)
{
    vector<int> result(32);
    for (int i = 0; i < 32; i++)
    {
        result[i] = L0[i] ^ P[i];
    }
    return result;
}

vector<int> swap32bit(vector<int> L0, vector<int> R0)
{
    vector<int> swapped(64);
    for (int i = 0; i < 32; i++)
    {
        swapped[i] = R0[i];
    }
    for (int i = 32; i < 64; i++)
    {
        swapped[i] = L0[i - 32];
    }
    return swapped;
}

vector<int> inverseInitialPermutation(vector<int> swapped)
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

vector<int> desEncrypt(vector<int> plainText, vector<int> key)
{
    vector<int> permutedPlainText = initialPermutation(plainText);
    vector<vector<int>> subkeys = generateSubkeys(key);

    vector<int> L0 = getL(permutedPlainText);
    vector<int> R0 = getR(permutedPlainText);

    for (int i = 0; i < 16; i++)
    {
        vector<int> expanded = expand(R0);
        vector<int> R0XORk = get48bitXOR(expanded, subkeys[i]);
        vector<int> sBoxOutput;
        vector<int> sBoxOutputBits;
        for (int j = 0; j < 8; j++)
        {
            sBoxOutput = sBox(R0XORk, j);
            sBoxOutputBits.insert(sBoxOutputBits.end(), sBoxOutput.begin(), sBoxOutput.end());
        }
        vector<int> permuted = permutation(sBoxOutputBits);
        vector<int> L1 = R0;
        vector<int> R1 = get32bitXOR(L0, permuted);
        L0 = L1;
        R0 = R1;
    }

    vector<int> swapped = swap32bit(L0, R0);
    vector<int> cipherText = inverseInitialPermutation(swapped);

    return cipherText;
}

vector<int> desDecrypt(vector<int> cipherText, vector<vector<int>> subkeys)
{
    vector<int> initialPermutation = inverseInitialPermutation(cipherText);
    vector<int> L0(initialPermutation.begin(), initialPermutation.begin() + 32);
    vector<int> R0(initialPermutation.begin() + 32, initialPermutation.end());

    for (int i = 15; i >= 0; i--)
    {
        vector<int> expanded = expand(R0);
        vector<int> R0XORk = get48bitXOR(expanded, subkeys[i]);
        vector<int> sBoxOutput;
        vector<int> sBoxOutputBits;
        for (int j = 0; j < 8; j++)
        {
            sBoxOutput = sBox(R0XORk, j);
            sBoxOutputBits.insert(sBoxOutputBits.end(), sBoxOutput.begin(), sBoxOutput.end());
        }
        vector<int> permuted = permutation(sBoxOutputBits);
        vector<int> L1 = R0;
        vector<int> R1 = get32bitXOR(L0, permuted);
        L0 = L1;
        R0 = R1;
    }

    vector<int> swapped = swap32bit(L0, R0);
    vector<int> plainText = inverseInitialPermutation(swapped);

    return plainText;
}

int main()
{
    string plainText;
    // vector<int> key = {0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
    vector<int> key;
    cout << "Enter key in ASCII: ";
    getline(cin, plainText);

    for (int i = 0; i < plainText.length(); i++)
    {
        bitset<8> binary(plainText[i]);
        for (int j = 7; j >= 0; j--)
        {
            key.push_back(static_cast<int>(binary[j]));
        }
    }

    cout << "Key: ";
    for (auto bit : key)
    {
        cout << bit << " ";
    }
    cout << endl;
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

    cout << "Plain text: ";
    for (auto byte : plainTextVector)
    {
        for (auto bit : byte)
        {
            cout << bit << " ";
        }
    }
    cout << endl;

    vector<vector<int>> chunks;
    vector<int> chunk;
    int chunkCounter = 1;
    for (int i = 0; i < plainTextVector.size(); i++)
    {
        chunk.push_back(plainTextVector[i][0]);
        if (chunk.size() == 64)
        {
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

    for (int i = 0; i < chunks.size(); i++)
    {
        cout << "Chunk " << i + 1 << ": ";
        for (auto bit : chunks[i])
        {
            cout << bit << " ";
        }
        cout << endl;
    }

    vector<vector<int>> cipherText;
    for (auto chunk : chunks)
    {
        cipherText.push_back(desEncrypt(chunk, key));
    }

    cout << "Cipher text: ";
    for (auto byte : cipherText)
    {
        for (auto bit : byte)
        {
            cout << bit << " ";
        }
    }

    cout << endl;

    vector<vector<int>> decryptedText;
    for (auto chunk : cipherText)
    {
        decryptedText.push_back(desDecrypt(chunk, generateSubkeys(key)));
    }

    cout << "Decrypted text: ";
    for (auto byte : decryptedText)
    {
        for (auto bit : byte)
        {
            cout << bit << " ";
        }
    }

    cout << endl;

    return 0;
}