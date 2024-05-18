#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

// Function to find the position of a character in a string
int findInString(string str, char c)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == c)
        {
            return i;
        }
    }
    return -1;
}

// Function to get the key matrix from the key string
void getKeyMatrix(string key, int keyMatrix[3][3])
{
    int k = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            keyMatrix[i][j] = (key[k]) % 65;
            k++;
        }
    }
}

// Function to perform matrix multiplication
void matrixMultiply(int a[3][3], int b[3][1], int result[3][1])
{
    for (int i = 0; i < 3; i++)
    {
        result[i][0] = 0;
        for (int j = 0; j < 3; j++)
        {
            result[i][0] += a[i][j] * b[j][0];
        }
        result[i][0] %= 26;
    }
}

// Function to find the determinant of a 3x3 matrix
int determinant(int A[3][3])
{
    return A[0][0] * (A[1][1] * A[2][2] - A[1][2] * A[2][1]) -
           A[0][1] * (A[1][0] * A[2][2] - A[1][2] * A[2][0]) +
           A[0][2] * (A[1][0] * A[2][1] - A[1][1] * A[2][0]);
}

// Function to find the modular inverse of a number
int modInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
    {
        if ((a * x) % m == 1)
        {
            return x;
        }
    }
    return 1;
}

// Function to find the cofactor matrix
void cofactorMatrix(int A[3][3], int cofactor[3][3])
{
    cofactor[0][0] = (A[1][1] * A[2][2] - A[1][2] * A[2][1]);
    cofactor[0][1] = -(A[1][0] * A[2][2] - A[1][2] * A[2][0]);
    cofactor[0][2] = (A[1][0] * A[2][1] - A[1][1] * A[2][0]);
    cofactor[1][0] = -(A[0][1] * A[2][2] - A[0][2] * A[2][1]);
    cofactor[1][1] = (A[0][0] * A[2][2] - A[0][2] * A[2][0]);
    cofactor[1][2] = -(A[0][0] * A[2][1] - A[0][1] * A[2][0]);
    cofactor[2][0] = (A[0][1] * A[1][2] - A[0][2] * A[1][1]);
    cofactor[2][1] = -(A[0][0] * A[1][2] - A[0][2] * A[1][0]);
    cofactor[2][2] = (A[0][0] * A[1][1] - A[0][1] * A[1][0]);
}

// Function to find the inverse of the key matrix
void inverseKeyMatrix(int keyMatrix[3][3], int inverse[3][3])
{
    int det = determinant(keyMatrix);
    int detInv = modInverse(det, 26);

    // Finding the cofactor matrix
    int cofactor[3][3];
    cofactorMatrix(keyMatrix, cofactor);

    // Transposing the cofactor matrix to get the adjugate
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            inverse[i][j] = (cofactor[j][i] * detInv) % 26;
            if (inverse[i][j] < 0)
            {
                inverse[i][j] += 26;
            }
        }
    }
}

// Function to perform encryption
string encryptMessage(string message, int keyMatrix[3][3])
{
    string paddedMessage = message;

    // Add padding if necessary
    while (paddedMessage.length() % 3 != 0)
    {
        paddedMessage += 'X';
    }

    string CipherText = "";

    // Encrypt the message in blocks of 3
    for (size_t i = 0; i < paddedMessage.length(); i += 3)
    {
        int messageVector[3][1];
        for (int j = 0; j < 3; j++)
        {
            messageVector[j][0] = (paddedMessage[i + j]) % 65;
        }

        int cipherMatrix[3][1];
        matrixMultiply(keyMatrix, messageVector, cipherMatrix);

        for (int j = 0; j < 3; j++)
        {
            CipherText += cipherMatrix[j][0] + 65;
        }
    }

    return CipherText;
}

// Function to perform decryption
string decryptMessage(string cipherText, int keyMatrix[3][3])
{
    string DecryptedText = "";

    // Decrypt the message in blocks of 3
    for (size_t i = 0; i < cipherText.length(); i += 3)
    {
        int cipherMatrix[3][1];
        for (int j = 0; j < 3; j++)
        {
            cipherMatrix[j][0] = (cipherText[i + j]) % 65;
        }

        int inverseKey[3][3];
        inverseKeyMatrix(keyMatrix, inverseKey);
        int decryptedMessageVector[3][1];
        matrixMultiply(inverseKey, cipherMatrix, decryptedMessageVector);

        for (int j = 0; j < 3; j++)
        {
            DecryptedText += decryptedMessageVector[j][0] + 65;
        }
    }

    // Remove padding
    while (!DecryptedText.empty() && DecryptedText.back() == 'X')
    {
        DecryptedText.pop_back();
    }

    return DecryptedText;
}

// Driver function for above code
int main()
{
    int keymatrix[3][3], choice;
    getKeyMatrix("GYBNQKURP", keymatrix);
    string message;
    cout << "Enter the message: ";
    cin >> message;
    // conver the message to uppercase
    for (char &c : message)
    {
        c = toupper(c);
    }
    // Get the key
    string key = "GYBNQKURP";

    // Get the choice
    cout << "========================" << endl;
    cout << "1. Encrypt" << endl
         << "2. Decrypt" << endl;
    cout << "========================" << endl;

    cin >> choice;
    if (choice != 1 && choice != 2)
    {
        cout << "Invalid choice" << endl;
        return 0;
    }
    if (choice == 1)
    {
        cout << encryptMessage(message, keymatrix) << endl;
    }
    else
    {
        cout << decryptMessage(message, keymatrix) << endl;
    }

    return 0;
}
