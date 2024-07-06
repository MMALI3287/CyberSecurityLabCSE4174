#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long int ul;

typedef bitset<64> b64;

using namespace std;

int main()
{
    string asciiString = "H!";
    b64 binaryRepresentation(stoull(asciiString, nullptr, 16));

    cout << "ASCII string: " << asciiString << endl;
    cout << "Binary representation: " << binaryRepresentation << endl;

    return 0;
}
