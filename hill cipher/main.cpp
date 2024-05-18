
// Hill cipher- uses 3x3 key matrix and blocks of 1x3

#include <iostream>
#include <string.h>
using namespace std;

// Initialize the key matrix
int keyMatrix[3][3];

// Charachers
string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Function to find the position of character in a string
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

// Function to generate the key matrix
void generateKeyMatrix(string input)
{
    int stringIndex = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            keyMatrix[i][j] = findInString(characters, input[stringIndex]);
            stringIndex++;
        }
    }
}

// Function to format the input string
struct formattedMessage
{
    int formatedCount;
    string message;
};

formattedMessage formatString(string inputString)
{
    formattedMessage m;
    if (inputString.length() % 3 != 0)
    {
        if (inputString.length() % 3 == 1)
        {
            m.message = inputString + "XX";
            m.formatedCount = 2;
        }
        else
        {
            m.message = inputString + "X";
            m.formatedCount = 1;
        }
        return m;
    }
    else
    {
        m.message = inputString;
        m.formatedCount = 0;
        return m;
    }
}

// Encryption function
string encrypt(string inputString)
{
    // Format the input string
    formattedMessage formattedMessage = formatString(inputString);

    string resultString = "";
    for (int i = 0; i < formattedMessage.message.length(); i += 3)
    {

        // Initialize the block of 3 and populate it
        int block[3];
        block[0] = findInString(characters, formattedMessage.message[i]);
        block[1] = findInString(characters, formattedMessage.message[i + 1]);
        block[2] = findInString(characters, formattedMessage.message[i + 2]);

        // Multiply the block with the key matrix
        int result[3];
        for (int j = 0; j < 3; j++)
        {
            result[j] = 0;
            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    result[i] += keyMatrix[i][j] * block[j];
                }
            }
        }

        // Convert the result to string
        for (int i = 0; i < 3; i++)
        {
            resultString += characters[result[i] % 26];
        }

        // Remove the padding if addded
        if (formattedMessage.formatedCount)
        {
            if (formattedMessage.formatedCount == 1)
            {
                resultString[resultString.length() - 1] = ' ';
            }
            else
            {
                resultString[resultString.length() - 1] = ' ';
                resultString[resultString.length() - 2] = ' ';
            }
        }
    }
    return resultString;
}

// Main function
int main()
{
    string inputKey;
    // Take the key string as input
    // cout << "Enter the key string, string must be of lenght 9" << endl;
    // cin >> inputKey;
    generateKeyMatrix("HILLAJTSR");

    cout << encrypt("BBB") << endl;
    // cout << formatString("HELL") << endl;
    return 0;
}
