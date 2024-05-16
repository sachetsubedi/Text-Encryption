#include <iostream>
#include <string>
using namespace std;
// Key matrix for playfair cipher
char keyMatrix[5][5];
// Characters for playfair cipher
string characters = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
// struct for refactored message
struct RefactoredMessage
{
    bool isRedundent;
    string message;
};
// Function to add redundent character
RefactoredMessage addRedundedChar(string message)
{
    RefactoredMessage m;
    if (message.length() % 2 != 0)
    {
        m.message = message + message[message.length() - 1];
        m.isRedundent = true;
    }
    else
    {
        m.message = message;
        m.isRedundent = false;
    }
    return m;
}
struct Position
{
    int x;
    int y;
};

// Function to find the position of the character in the key matrix
Position findPosition(char c)
{
    Position p;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (keyMatrix[i][j] == c)
            {
                p.x = i;
                p.y = j;
                return p;
            }
        }
    }
    return p;
}

// Function to check if the character exists in the matrix
bool existsInMatrix(char c)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (keyMatrix[i][j] == c)
            {
                return true;
            }
        }
    }
    return false;
}

// Function to generate key matrix
void generateKeyMatrix(string message)
{
    bool messageVisited = false;
    int index = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (!messageVisited)
            {
                // If already exists in matrix then skip the character and check for next character
                while (existsInMatrix(message[index]))
                {
                    index++;
                    if (index >= message.length())
                    {
                        messageVisited = true;
                        break;
                    }
                }
                if (messageVisited)
                    break;

                // If the character is 'J' then replace it with 'I'
                if (message[index] == 'J')
                    message[index] = 'I';

                // Set the character in the matrix
                keyMatrix[i][j] = message[index];
                index++;
                if (index == message.length())
                    messageVisited = true;
            }
            // If the message is visited then add the remaining characters in the matrix
            else
            {
                for (int k = 0; k < characters.length(); k++)
                {
                    if (!existsInMatrix(characters[k])) // If the character does not exist in the matrix then add it
                    {
                        keyMatrix[i][j] = characters[k];
                        break;
                    }
                }
            }
        }
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << keyMatrix[i][j];
        }
        cout << endl;
    }
}

// Struct for position

string encrypt(string messageInput)
{
    // refactor the message by added a redundent character if the length is odd
    RefactoredMessage refactoredMessage = addRedundedChar(messageInput);
    string message = refactoredMessage.message;

    generateKeyMatrix("SACHETSUBEDI");
    for (char &c : message)
    {
        c = toupper(c);
    }
    string encryptedMessage = "";
    for (int i = 0; i < message.length(); i += 2)
    {
        char first = message[i];
        char second = message[i + 1];
        Position firstPosition = findPosition(first);
        Position secondPosition = findPosition(second);
        if (firstPosition.x == secondPosition.x)
        {
            encryptedMessage += keyMatrix[firstPosition.x][(firstPosition.y + 1) % 5];
            encryptedMessage += keyMatrix[secondPosition.x][(secondPosition.y + 1) % 5];
        }
        else if (firstPosition.y == secondPosition.y)
        {
            encryptedMessage += keyMatrix[(firstPosition.x + 1) % 5][firstPosition.y];
            encryptedMessage += keyMatrix[(secondPosition.x + 1) % 5][secondPosition.y];
        }
        else
        {
            encryptedMessage += keyMatrix[firstPosition.x][secondPosition.y];
            encryptedMessage += keyMatrix[secondPosition.x][firstPosition.y];
        }
    }
    if (refactoredMessage.isRedundent)
    {
        encryptedMessage[encryptedMessage.length() - 1] = ' ';
    }
    return encryptedMessage;
}

string decrypt(string message)
{
    // refactor the message by added a redundent character if the length is odd
    RefactoredMessage refactoredMessage = addRedundedChar(message);
    message = refactoredMessage.message;

    generateKeyMatrix("SACHETSUBEDI");
    // change to upper case
    for (char &c : message)
    {
        c = toupper(c);
    }
    string decryptedMessage = "";
    for (int i = 0; i < message.length(); i += 2)
    {
        char first = message[i];
        char second = message[i + 1];
        Position firstPosition = findPosition(first);
        Position secondPosition = findPosition(second);
        if (firstPosition.x == secondPosition.x)
        {
            decryptedMessage += keyMatrix[firstPosition.x][(firstPosition.y - 1 + 5) % 5];
            decryptedMessage += keyMatrix[secondPosition.x][(secondPosition.y - 1 + 5) % 5];
        }
        else if (firstPosition.y == secondPosition.y)
        {
            decryptedMessage += keyMatrix[(firstPosition.x - 1 + 5) % 5][firstPosition.y];
            decryptedMessage += keyMatrix[(secondPosition.x - 1 + 5) % 5][secondPosition.y];
        }
        else
        {
            decryptedMessage += keyMatrix[firstPosition.x][secondPosition.y];
            decryptedMessage += keyMatrix[secondPosition.x][firstPosition.y];
        }
    }
    // Remove the redundent character
    if (refactoredMessage.isRedundent)
    {
        decryptedMessage[decryptedMessage.length() - 1] = ' ';
    }
    return decryptedMessage;
}

int main()
{
    int choice;
    string message;
    cout << "Enter the message: ";
    cin >> message;

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
        string encryptedText = encrypt(message);
        cout << "Encrypted Text: " << encryptedText << endl;
    }

    else if (choice == 2)
    {
        // Decrypting the message
        string decryptedText = decrypt(message);
        cout << "Decrypted Text: " << decryptedText << endl;
    }

    return 0;
}
