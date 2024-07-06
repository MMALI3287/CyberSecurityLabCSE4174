#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long int ul;
typedef bitset<64> b64;
typedef bitset<48> b48;
typedef bitset<32> b32;
typedef bitset<56> b56;
typedef bitset<28> b28;
typedef bitset<8> b8;

b64 asciiTo64BitBinary(const string &asciiString)
{
    b64 binaryRepresentation;

    for (char c : asciiString)
    {
        int asciiValue = static_cast<int>(c);

        binaryRepresentation <<= 8;

        binaryRepresentation |= b64(asciiValue);
    }

    return binaryRepresentation;
}

vector<b64> textToInputBlocks(string plainText)
{
    vector<b64> output;
    int i = 0;
    b64 block;
    int padding = 128;
    int padLength = 8 - (plainText.length() % 8);
    for (char c : plainText)
    {
        b64 temp((int)c);
        block <<= 8;
        block |= temp;
        i++;
        if (i == 8)
        {
            output.push_back(block);
            i = 0;
            block.reset();
        }
    }
    // for (int i = 0; i < padLength; i++)
    // {
    //     b64 temp(padding);
    //     block <<= 8;
    //     block |= temp;
    // }
    return output;
}

string bitToCharacters(b64 input)
{
    string output = "";
    b8 temp;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            temp[7 - j] = input[63 - j];
        }
        char c = (int)(temp.to_ulong());
        output.push_back(c);
        input <<= 8;
    }
    return output;
}

b64 initialPermutation(b64 input)
{
    b64 output;
    int IP[] =
        {
            58, 50, 42, 34, 26, 18, 10, 2,
            60, 52, 44, 36, 28, 20, 12, 4,
            62, 54, 46, 38, 30, 22, 14, 6,
            64, 56, 48, 40, 32, 24, 16, 8,
            57, 49, 41, 33, 25, 17, 9, 1,
            59, 51, 43, 35, 27, 19, 11, 3,
            61, 53, 45, 37, 29, 21, 13, 5,
            63, 55, 47, 39, 31, 23, 15, 7};
    for (int i = 0; i < 64; i++)
    {
        output[63 - i] = input[64 - IP[i]];
    }
    return output;
}

b56 permutedChoice1(b64 key)
{
    b56 output;
    int PC1[] =
        {
            57, 49, 41, 33, 25, 17, 9,
            1, 58, 50, 42, 34, 26, 18,
            10, 2, 59, 51, 43, 35, 27,
            19, 11, 3, 60, 52, 44, 36,
            63, 55, 47, 39, 31, 23, 15,
            7, 62, 54, 46, 38, 30, 22,
            14, 6, 61, 53, 45, 37, 29,
            21, 13, 5, 28, 20, 12, 4};
    b56 permuted_key;
    for (int i = 0; i < 56; i++)
    {
        output[55 - i] = key[64 - PC1[i]];
    }
    return output;
}

b48 permutedChoice2(b56 input)
{
    b48 output;
    int PC2[] = {14, 17, 11, 24, 1, 5,
                 3, 28, 15, 6, 21, 10,
                 23, 19, 12, 4, 26, 8,
                 16, 7, 27, 20, 13, 2,
                 41, 52, 31, 37, 47, 55,
                 30, 40, 51, 45, 33, 48,
                 44, 49, 39, 56, 34, 53,
                 46, 42, 50, 36, 29, 32};
    for (int i = 0; i < 48; i++)
    {
        output[47 - i] = input[56 - PC2[i]];
    }
    return output;
}

vector<b48> generateSubkeys(b64 input64BitKey)
{
    b56 permuted_key = permutedChoice1(input64BitKey);

    int SHIFTS[] = {1, 1, 2, 2, 2, 2, 2, 2,
                    1, 2, 2, 2, 2, 2, 2, 1};

    b56 divider(0b00000000000000000000000000001111111111111111111111111111);
    b28 right((permuted_key & divider).to_ulong());
    b28 left(((permuted_key >> 28) & divider).to_ulong());

    vector<b48> subkeys(16);
    for (int round = 0; round < 16; round++)
    {
        left = (left << SHIFTS[round]) | (left >> (28 - SHIFTS[round]));
        right = (right << SHIFTS[round]) | (right >> (28 - SHIFTS[round]));

        b56 combined_key;
        for (int i = 0; i < 28; i++)
        {
            combined_key[i] = right[i];
            combined_key[i + 28] = left[i];
        }
        subkeys[round] = permutedChoice2(combined_key);
    }
    return subkeys;
}

b48 expand(b32 input)
{
    int E[] =
        {
            32, 1, 2, 3, 4, 5, 4, 5,
            6, 7, 8, 9, 8, 9, 10, 11,
            12, 13, 12, 13, 14, 15, 16, 17,
            16, 17, 18, 19, 20, 21, 20, 21,
            22, 23, 24, 25, 24, 25, 26, 27,
            28, 29, 28, 29, 30, 31, 32, 1};
    b48 output;
    for (int i = 0; i < 48; i++)
    {
        output[47 - i] = input[32 - E[i]];
    }
    return output;
}

b32 sBoxSubstitution(b48 input)
{
    b32 output;
    int S_BOX[8][4][16] =
        {
            {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
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
             {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}},
        };
    int bits = 0;
    for (int i = 0; i < 8; i++)
    {
        int row = (input[47 - (i * 6)] << 1) | input[47 - (i * 6 + 5)];
        int col = (input[47 - (i * 6 + 1)] << 3) |
                  (input[47 - (i * 6 + 2)] << 2) |
                  (input[47 - (i * 6 + 3)] << 1) |
                  input[47 - (i * 6 + 4)];
        int sbox_value = S_BOX[i][row][col];
        bitset<4> sbox_bits(sbox_value);
        for (int j = 0; j < 4; j++)
        {
            output[31 - bits] = sbox_bits[3 - j];
            bits++;
        }
    }
    return output;
}

b32 permutation(b32 input)
{
    b32 output;
    int P[] = {16, 7, 20, 21, 29, 12, 28, 17,
               1, 15, 23, 26, 5, 18, 31, 10,
               2, 8, 24, 14, 32, 27, 3, 9,
               19, 13, 30, 6, 22, 11, 4, 25};
    for (int i = 0; i < 32; i++)
    {
        output[31 - i] = input[32 - P[i]];
    }
    return output;
}

b64 inverseInitialPermutation(b64 input)
{
    b64 output;
    int FP[] = {40, 8, 48, 16, 56, 24, 64, 32,
                39, 7, 47, 15, 55, 23, 63, 31,
                38, 6, 46, 14, 54, 22, 62, 30,
                37, 5, 45, 13, 53, 21, 61, 29,
                36, 4, 44, 12, 52, 20, 60, 28,
                35, 3, 43, 11, 51, 19, 59, 27,
                34, 2, 42, 10, 50, 18, 58, 26,
                33, 1, 41, 9, 49, 17, 57, 25};
    for (int i = 0; i < 64; i++)
    {
        output[63 - i] = input[64 - FP[i]];
    }
    return output;
}

b32 feistelFunction(b32 half_block, b48 subkey)
{
    b48 expanded_half = expand(half_block);
    expanded_half ^= subkey;
    b32 sbox_result = sBoxSubstitution(expanded_half);
    return permutation(sbox_result);
}

b64 desEncryptBlock(b64 block, vector<b48> subkeys)
{
    block = initialPermutation(block);
    b64 divider(0b0000000000000000000000000000000011111111111111111111111111111111);
    b32 right((block & divider).to_ulong());
    b32 left(((block >> 32) & divider).to_ulong());

    for (int round = 0; round < 16; round++)
    {
        b32 temp = right;
        right = left ^ feistelFunction(right, subkeys[round]);
        left = temp;
    }

    b64 combined_block;
    for (int i = 0; i < 32; i++)
    {
        combined_block[i] = right[i];
        combined_block[i + 32] = left[i];
    }
    return inverseInitialPermutation(combined_block);
}

b64 desDecryptBlock(b64 block, vector<b48> subkeys)
{
    block = initialPermutation(block);
    b64 divider(0b0000000000000000000000000000000011111111111111111111111111111111);
    b32 right((block & divider).to_ulong());
    b32 left(((block >> 32) & divider).to_ulong());

    for (int round = 15; round >= 0; round--)
    {
        b32 temp = left;
        left = right ^ feistelFunction(left, subkeys[round]);
        right = temp;
    }
    b64 combined_block;
    for (int i = 0; i < 32; i++)
    {
        combined_block[i] = right[i];
        combined_block[i + 32] = left[i];
    }
    return inverseInitialPermutation(combined_block);
}

vector<b64> cbcDesEncrypt(vector<b64> inputBlocks, vector<b48> subkeys, b64 initial64BitVector)
{
    vector<b64> ciphertext;
    b64 prevBlock = initial64BitVector;
    for (b64 block : inputBlocks)
    {
        b64 xorBlock = block ^ prevBlock;
        b64 encryptedBlock = desEncryptBlock(xorBlock, subkeys);
        ciphertext.push_back(encryptedBlock);
        prevBlock = encryptedBlock;
    }
    return ciphertext;
}

vector<b64> cbcDesDecrypt(vector<b64> ciphertext, vector<b48> subkeys, b64 initial64BitVector)
{
    vector<b64> plaintext;
    b64 prevBlock = initial64BitVector;
    for (b64 block : ciphertext)
    {
        b64 decryptedBlock = desDecryptBlock(block, subkeys);
        b64 xorBlock = decryptedBlock ^ prevBlock;
        plaintext.push_back(xorBlock);
        prevBlock = block;
    }
    return plaintext;
}

int main()
{
    string plainText, keyString, inputVectorString;

    cout << "Enter the plain text: ";
    getline(cin, plainText);

    int padLength = 8 - (plainText.length() % 8);
    for (int i = 0; i < padLength; i++)
    {
        plainText += ' ';
    }

    vector<b64> inputBlocks = textToInputBlocks(plainText);

    while (keyString.length() != 8 && inputVectorString.length() != 8)
    {
        cout << "Encryption key and input vector must be of length 8 in ASCII" << endl;
        cout << "Enter the encryption key: ";
        cin >> keyString;

        cout << "Enter the input vector: ";
        cin >> inputVectorString;
    }

    cout << "Plain text: " << plainText << endl;
    cout << "Encryption Key: " << keyString << endl;
    cout << "Initial Vector: " << inputVectorString << endl;

    b64 input64BitKey = asciiTo64BitBinary(keyString);
    b64 initial64BitVector = asciiTo64BitBinary(inputVectorString);
    vector<b48> subkeys = generateSubkeys(input64BitKey);

    vector<b64> ciphertext = cbcDesEncrypt(inputBlocks, subkeys, initial64BitVector);
    cout << "Cipher Text After Encryption: ";
    for (b64 cipherBlocks : ciphertext)
    {
        cout << bitToCharacters(cipherBlocks);
    }
    cout << endl;

    vector<b64> plaintext = cbcDesDecrypt(ciphertext, subkeys, initial64BitVector);
    cout << "Plain Text After Decryption: ";
    for (b64 plainBlocks : plaintext)
    {
        cout << bitToCharacters(plainBlocks);
    }
    cout << endl;

    return 0;
}
