#include <iostream>
#include <string>

using namespace std;

// Function to encrypt the message using Rail Fence Cipher
string encryptRailFence(string plaintext, int rails)
{
    string ciphertext;
    int n = plaintext.length();
    int cycle = 2 * rails - 2;

    for (int i = 0; i < rails; ++i)
    {
        for (int j = 0; j + i < n; j += cycle)
        {
            ciphertext += plaintext[j + i];
            if (i != 0 && i != rails - 1 && j + cycle - i < n)
            {
                ciphertext += plaintext[j + cycle - i];
            }
        }
    }

    return ciphertext;
}

// Function to decrypt the message using Rail Fence Cipher
string decryptRailFence(string ciphertext, int rails)
{
    string plaintext;
    int n = ciphertext.length();
    int cycle = 2 * rails - 2;
    int railLength = cycle;
    int index = 0;

    for (int i = 0; i < rails; ++i)
    {
        int j = i;
        int k = railLength - i;

        while (j < n)
        {
            plaintext += ciphertext[j];
            if (i != 0 && i != rails - 1 && k < n)
            {
                plaintext += ciphertext[k];
            }
            j += cycle;
            k += cycle;
        }

        index += 1;
        railLength -= 2;
    }

    return plaintext;
}

int main()
{
    string plaintext, ciphertext;
    int rails, choice;

    cout << "Enter the plaintext: ";
    getline(cin, plaintext);

    cout << "Enter the number of rails: ";
    cin >> rails;

    cout << "========================" << endl;
    cout << "1. Encrypt" << endl
         << "2. Decrypt" << endl;
    cout << "========================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        ciphertext = encryptRailFence(plaintext, rails);
        cout << "Encrypted Text: " << ciphertext << endl;
        break;
    case 2:
        ciphertext = encryptRailFence(plaintext, rails);
        plaintext = decryptRailFence(ciphertext, rails);
        cout << "Decrypted Text: " << plaintext << endl;
        break;
    default:
        cout << "Invalid choice" << endl;
    }

    return 0;
}
