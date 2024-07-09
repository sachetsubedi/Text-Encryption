#include <iostream>
#include <string.h>

using namespace std;

string decryptMessage(string message, int shift)
{
    for (int i = 0; i < message.length(); i++)
    {
        message[i] = char((message[i] - shift) % 255);
    }
    return message;
}

int main()
{
    string message;
    int shift;

    cout << "Enter a message: ";
    getline(cin, message);
    cout << "Enter a shift: ";
    cin >> shift;
    cout << "Decrypted text:" << endl;
    cout << "=============================" << endl;
    cout << decryptMessage(message, shift) << endl;
    cout << "=============================" << endl;

    return 0;
}
