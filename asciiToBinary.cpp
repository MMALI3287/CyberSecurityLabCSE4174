#include <iostream>
#include <string>
#include <bitset>

using namespace std;

// Function to convert ASCII characters to binary
string asciiToBinary(const string &asciiString)
{
    string binaryString;

    for (char c : asciiString)
    {
        // Convert character 'c' to its ASCII integer value
        int asciiValue = static_cast<int>(c);

        // Convert ASCII integer value to binary string representation
        string binaryRepresentation = bitset<8>(asciiValue).to_string();

        // Append binary representation to the result string
        binaryString += binaryRepresentation;
    }

    return binaryString;
}

int main()
{
    string asciiString = "H!";
    string binaryRepresentation = asciiToBinary(asciiString);

    cout << "ASCII string: " << asciiString << endl;
    cout << "Binary representation: " << binaryRepresentation << endl;

    return 0;
}
