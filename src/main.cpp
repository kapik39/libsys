#include "Library.h"
#include <iostream>
#include <vector>
#include <limits>
#include <string>

void displayMenu()
{
    cout << "\n LIBRARY MANAGEMENT SYSTEM \n";
    cout << "1. Add a new book \n";
    cout << "2. View all books in library \n";
    cout << "3. Add a new user \n";
    cout << "4. View all users \n";
    cout << "5. View user's borrowed books \n";
    cout << "6. Borrow book \n";
    cout << "7. Return book \n";
    cout << "8. View log history \n";
    cout << "0. Out system \n";
    cout << "-------------------------------------\n";
    cout << "Enter your selection: ";
}

string getLineInput(const string &prompt)
{
    string input;
    cout << prompt;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);
    return input;
}
bool checkValidInt()
{
    if (cin.fail())
    {
        cout << "Invalid number. Need a integer number!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter to continue.";
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

int getInt(const string &prompt)
{
    int input;
    while (true)
    {
        cout << prompt;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> input;
        if (checkValidInt())
        {
            break;
        }
    }

    return input;
}

int main()
{
    Library myLibrary;
    int choice;
    do
    {
        displayMenu();
        cin >> choice;
        checkValidInt();
        if (!checkValidInt())
        {
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            cout << "Add a new book \n";
            string title = getLineInput("Enter book's title: ");
            string author = getLineInput("Enter book's author: ");
            string isbn = getLineInput("Enter book's isbn: ");
            int numberOfBook = getInt("Enter number of book: ");
            myLibrary.addBook(title, author, isbn, numberOfBook);
            break;
        }
        case 2:
        {
            myLibrary.printAllBooks();
            break;
        }
        case 3:
        {
            cout << "Add a new user \n";
            string username = getLineInput("Enter your username: ");
            string userId = getLineInput("Enter youtr user ID: ");
            myLibrary.addUser(userId, username);
            break;
        }
        case 4:
        {
            myLibrary.printAllUser();
            break;
        }
        case 5:
        {
            cout << "List of user's borrowed books: \n";
            string userId = getLineInput("Enter youtr user ID: ");
            myLibrary.printUserBorrowedBooks(userId);
        }
        case 6:
        {
            cout << "Borrow book \n";
            string userId = getLineInput("Enter user ID: ");
            string isbn = getLineInput("Enter book's isbn want to borrow: ");
            myLibrary.performBorrow(userId, isbn);
            break;
        }
        case 7:
        {
            cout << "Return book \n";
            string userId = getLineInput("Enter user ID: ");
            string isbn = getLineInput("Enter book's isbn want to return: ");
            myLibrary.performBorrow(userId, isbn);
            break;
        }
        case 8:
        {
            myLibrary.printLog();
            break;
        }
        case 0:
        {
            cout << "Out of system!";
            break;
        }

        default:
        {
            cout << "Invalid selection. Please enter a valid number!\n";
            break;
        }
        }
    } while (choice != 0);

    return 0;
}