// find a large prime number

#include <math.h>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
using namespace std;
bool isPrime(long long n)
{
    long long j = sqrt(n);
    if (n >= 2)
    {
        for (long long i = 2; i <= j; i++)
        {
            if (n % i == 0)
                return false;
        }
        return true;
    }
    return false;
}

bool isCardinal(double num)
{
    double intPart;
    double fracPart = modf(num, &intPart);
    return fracPart == 0 && num >= 0;
}

vector<string> RSAencrypt(string message, long long e, long long n)
{
    long long siz = 127;
    long long asiz = 1;

    while (siz < n)
    {
        siz = (siz * 1000) + 127;
        asiz++;
    }

    vector<string> mess(asiz);
    for (long long i = 0; i < asiz; i++)
    {
        mess.push_back(message.substr(i * asiz, asiz));
    }
    for (long long i = 0; i < asiz; i++)
    {
        cout << i << "->" << mess[i] << endl;
    }
    vector<string> encryptedMessage(asiz);
    for (long long i = 0; i < asiz; i++)
    {
        encryptedMessage[i] = "";
        for (long long j = 0; j < mess[i].length(); j++)
        {
            encryptedMessage[i] += to_string((long long)pow((long long)mess[i][j], e) % n);
        }
    }
    return encryptedMessage;
}

string RSAdecrypt(string encryptedMessage, long long d, long long n)
{
    string message = "";
    for (long long i = 0; i < encryptedMessage.length(); i++)
    {
        message += to_string((long long)pow((long long)encryptedMessage[i], d) % n);
    }
    return message;
}

int main()
{
    long long p;
    long long q;
    long long n;
    long long phi;
    long long e;
    long long d;
    long long k = 1;
    srand(time(NULL));
    while (!isPrime(p))
    {
        p = 999999 + (rand() % 999999999);
    }
    while (!isPrime(q))
    {
        q = 999999 + (rand() % 999999999);
    }
    n = p * q;
    phi = (p - 1) * (q - 1);
    e = 3;
    while (!(phi % e != 0 && isPrime(e)))
    {
        e++;
    }
    d = -1;
    while (!isCardinal(d))
    {
        d = (1 + phi * k) / e;
        k++;
        cout << d << endl;
    }
    cout << "Public key: (" << e << ", " << n << ")" << endl;
    cout << "Private key: (" << d << ", " << n << ")" << endl;

    string message;
    cout << "Enter the message: ";
    getline(cin, message);

    cout << "The message is " << message << endl;
    vector<string> encrypted = RSAencrypt(message, e, n);
    for (long long i = 0; i < encrypted.size(); i++)
    {
        cout << "The encrypted message is " << encrypted[i] << endl;
    }
    // cout << "The decrypted message is " << RSAdecrypt(RSAencrypt(message, e, n), d, n) << endl;
    return 0;
}