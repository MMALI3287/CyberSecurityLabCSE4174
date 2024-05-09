#include <math.h>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <unistd.h>
using namespace std;

bool isPrime(unsigned long long n)
{
    unsigned long long j = sqrt(n);

    if (n >= 2)
    {
        for (unsigned long long i = 2; i <= j; i++)
        {
            if (n % i == 0)
                return false;
        }

        return true;
    }

    return false;
}

unsigned long long modPow(unsigned long long base, unsigned long long exponent, unsigned long long modulus)
{
    if (modulus == 1)
        return 0;

    unsigned long long result = 1;
    base = base % modulus;

    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;

        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }

    return result;
}

bool isCardinal(long double num)
{
    long double intPart;
    long double fracPart = modf(num, &intPart);

    return fracPart == 0 && num >= 0;
}

vector<string> RSAencrypt(string message, unsigned long long e, unsigned long long n)
{
    unsigned long long siz = 127;
    unsigned long long asiz = 0;
    vector<string> encryptedMessage;
    vector<string> mess;
    vector<unsigned long long> asciiMess;

    while (siz < n)
    {
        siz = (siz * 1000) + 127;
        asiz++;
    }

    unsigned long long vsize = (strlen(message.c_str()) + asiz - 1) / asiz;

    for (unsigned long long i = 0; i < vsize; i++)
    {
        string part = message.substr(i * asiz, asiz);
        part.resize(asiz, ' ');
        mess.push_back(part);
    }

    for (auto i : mess)
    {
        string temp = i;
        unsigned long long tempNum = 0;

        for (char &c : temp)
        {
            tempNum = (tempNum * 1000) + (unsigned long long)c;
        }

        asciiMess.push_back(tempNum);
    }

    for (auto i : asciiMess)
    {
        encryptedMessage.push_back(to_string(modPow(i, e, n)));
    }

    return encryptedMessage;
}

vector<string> RSAdecrypt(vector<string> encryptedMessage, unsigned long long d, unsigned long long n)
{
    vector<string> decryptedMessage;

    for (auto i : encryptedMessage)
    {
        decryptedMessage.push_back(to_string(modPow(stoll(i), d, n)));
    }

    return decryptedMessage;
}

int main()
{
    unsigned long long p = 0;
    unsigned long long q = 0;
    unsigned long long n;
    unsigned long long phi;
    unsigned long long e;
    long double d;
    unsigned long long k = 1;

    cout << "Generating prime numbers..." << endl;
    sleep(1);
    srand(time(NULL));

    while (!isPrime(p))
    {
        p = 6666 + (rand() % 99999);
    }
    while (!isPrime(q))
    {
        q = 6666 + (rand() % 99999);
    }

    cout << "Prime numbers: (" << p << ", " << q << ")" << endl
         << endl;

    cout << "Generating public and private keys..." << endl;
    sleep(1);

    n = p * q;
    phi = (p - 1) * (q - 1);
    e = 3;
    while (!(phi % e != 0 && isPrime(e)))
    {
        e++;
    }
    d = -1.1;
    while (!isCardinal(d))
    {
        d = (1 + double(phi) * double(k)) / double(e);
        k++;
    }

    cout << "Public key: (" << e << ", " << n << ")" << endl;
    cout << "Private key: (" << d << ", " << n << ")" << endl
         << endl;

    string message;
    cout << "Enter the message: ";
    getline(cin, message);

    cout << "Message: " << message << endl
         << endl;
    message.erase(remove(message.begin(), message.end(), '\0'), message.end());

    cout << "Encrypting message...  -->  " << message << endl;
    sleep(1);
    vector<string> encrypted = RSAencrypt(message, e, n);

    cout << "Encrypted message: ";
    for (auto i : encrypted)
    {
        cout << i;
    }
    cout << "  -->  ";
    for (auto i : encrypted)
    {
        long int sti = stoll(i);
        string temp = "";
        while (sti)
        {
            char ch = char(sti % 1000);
            temp = ch + temp;
            sti /= 1000;
        }
        cout << temp;
    }
    cout << endl;

    cout << endl
         << "Decrypting message...  -->  ";
    for (auto i : encrypted)
    {
        cout << i;
    }
    cout << endl;
    sleep(1);

    vector<string> decrypted = RSAdecrypt(encrypted, d, n);
    cout << "Decrypted message: ";
    for (auto i : decrypted)
    {
        cout << i;
    }

    cout << "  -->  ";
    for (auto i : decrypted)
    {
        long int sti = stoll(i);
        string temp = "";
        while (sti)
        {
            char ch = char(sti % 1000);
            temp = ch + temp;
            sti /= 1000;
        }
        cout << temp;
    }

    cout << endl
         << endl;

    return 0;
}