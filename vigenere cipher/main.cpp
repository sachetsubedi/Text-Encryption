#include <iostream>
#include <string>

using namespace std;

// Function to encrypt the message using Vigenere Cipher
string encryptVigenere(string plaintext, string key)
{
    string ciphertext;
    int keyLength = key.length();

    for (int i = 0; i < plaintext.length(); ++i)
    {
        char plainChar = plaintext[i];
        char keyChar = key[i % keyLength];

        if (isalpha(plainChar))
        {
            char base = isupper(plainChar) ? 'A' : 'a';
            char encryptedChar = ((plainChar - base) + (keyChar - 'A')) % 26 + base;
            ciphertext += encryptedChar;
        }
        else
        {
            ciphertext += plainChar; // Keep non-alphabetic characters unchanged
        }
    }

    return ciphertext;
}

// Function to decrypt the message using Vigenere Cipher
string decryptVigenere(string ciphertext, string key)
{
    string plaintext;
    int keyLength = key.length();

    for (int i = 0; i < ciphertext.length(); ++i)
    {
        char cipherChar = ciphertext[i];
        char keyChar = key[i % keyLength];

        if (isalpha(cipherChar))
        {
            char base = isupper(cipherChar) ? 'A' : 'a';
            char decryptedChar = ((cipherChar - base) - (keyChar - 'A') + 26) % 26 + base;
            plaintext += decryptedChar;
        }
        else
        {
            plaintext += cipherChar; // Keep non-alphabetic characters unchanged
        }
    }

    return plaintext;
}

int main()
{
    string plaintext, key, ciphertext;
    int choice;

    cout << "Enter the plaintext: ";
    getline(cin, plaintext);

    cout << "Enter the key: ";
    cin >> key;

    cout << "========================" << endl;
    cout << "1. Encrypt" << endl
         << "2. Decrypt" << endl;
    cout << "========================" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        ciphertext = encryptVigenere(plaintext, key);
        cout << "Encrypted Text: " << ciphertext << endl;
        break;
    case 2:
        plaintext = decryptVigenere(plaintext, key);
        cout << "Decrypted Text: " << plaintext << endl;
        break;
    default:
        cout << "Invalid choice" << endl;
    }

    return 0;
}
