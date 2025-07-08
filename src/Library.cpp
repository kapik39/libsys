#include <iostream>
#include <Library.h>
#include <string>

using namespace std;

Library::Library() {};

void Library::addBook(const string &title, const string &author, const string &isbn, const int &numberOfBook)
{
    lock_guard<mutex> libraryLock(libraryMutex);
    if (books.find(isbn) == books.end())
    {
        books[isbn] = make_shared<Book>(title, author, isbn, numberOfBook);
        int tempNumber = books[isbn]->getNumberOfBook();
        logEntries.push_back("Added: \"" + title + "\" by " + author + "(ISBN: " + isbn + ") quantity: " + to_string(tempNumber));
        cout << "Added: \"" + title + "\" by " + author + "(ISBN: " + isbn + ") quantity: " << numberOfBook << endl;
    }
    else
    {
        logEntries.push_back("Failed to add book, book already exists with ISBN: " + isbn);
        cout << "Failed to add book, book already exists with ISBN: " + isbn << endl;
    }
}

shared_ptr<Book> Library::findBook(const string &isbn) const
{
    lock_guard<mutex> libraryLock(libraryMutex);
    auto isFindable = books.find(isbn);
    if (isFindable != books.end())
    {
        return isFindable->second;
    }
    return nullptr;
}

void Library::printAllBooks() const
{
    lock_guard<mutex> libraryLock(libraryMutex);
    cout << "\n Current Books in Library \n";
    if (books.empty())
    {
        cout << "No book in the library. \n";
        return;
    }
    for (const auto &i : books)
    {
        const auto &book = i.second;
        cout << "Title: \"" << book->getTitle()
             << "\", Author: " << book->getAuthor()
             << ", ISBN: " << book->getIsbn()
             << ", Status: " << (book->isAvailable() ? "Avaiale" : "Borrowed")
             << endl;
    }
}

void Library::addUser(const string &userId, const string &username)
{
    lock_guard<mutex> libraryLock(libraryMutex);
    if (users.find(userId) == users.end())
    {
        users[userId] = make_shared<User>(userId, username);
        logEntries.push_back("Added: " + username + " with user ID: " + userId);
        cout << "Added: " + username + " with user ID: " + userId << endl;
    }
    else
    {
        logEntries.push_back("Failed to add user, user already exists with user ID: " + userId);
        cout << "Failed to add user, user already exists with user ID: " + userId << endl;
    }
}

shared_ptr<User> Library::findUser(const string &userId) const
{
    lock_guard<mutex> libraryLock(libraryMutex);
    auto isFindable = users.find(userId);
    if (isFindable != users.end())
    {
        return isFindable->second;
    }
    return nullptr;
}

void Library::printAllUser() const
{
    lock_guard<mutex> libraryLock(libraryMutex);
    cout << "\n All registered Users \n";
    if (users.empty())
    {
        cout << "No registered Users. \n";
        return;
    }
    for (const auto &i : users)
    {
        const auto &user = i.second;
        cout << "Username: " << user->getUsername()
             << "User ID: " << user->getUserId()
             << endl;
    }
}

void Library::printUserBorrowedBooks(const string &userId) const
{
    shared_ptr<User> user = findUser(userId);
    if (user)
    {
        user->printBorrowedBooks();
    }
    else
    {
        cout << "User not found\n";
    }
}

void Library::performBorrow(const string &userId, const string &isbn)
{
    shared_ptr<Book> book = findBook(isbn);
    shared_ptr<User> user = findUser(userId);
    string logMessage;

    if (!user)
    {
        logMessage = "User not found";
        cout << "User not found\n";
    }
    else if (!book)
    {
        logMessage = "Book not found";
        cout << "Book not found\n";
    }
    else
    {
        if (book->borrowBook())
        {
            if (user->addBorrowedBook(book))
            {
                logMessage = "User: " + user->getUsername() + "(ID: " + user->getUserId() + ") borrowed \"" + book->getTitle() + "\" SUCCESS";
                cout << "User: " + user->getUsername() + "(ID: " + user->getUserId() + ") borrowed \"" + book->getTitle() + "\" SUCCESS\n";
            }
            else
            {
                logMessage = "FAILED: User: " + user->getUsername() + "(ID: " + user->getUserId() + ") already has this book";
                cout << "FAILED: User: " + user->getUsername() + "(ID: " + user->getUserId() + ") already has this book\n";
                book->returnBook();
            }
        }
        else
        {
            logMessage = "FAILED: All books already borrowed";
            cout << "FAILED: All books already borrowed\n";
        }
    }

    lock_guard<mutex> libraryLock(libraryMutex);
    logEntries.push_back(logMessage);
}

void Library::performReturn(const string &userId, const string &isbn)
{
    shared_ptr<Book> book = findBook(isbn);
    shared_ptr<User> user = findUser(userId);
    string logMessage;

    if (!user)
    {
        logMessage = "User not found";
        cout << "User not found\n";
    }
    else if (!book)
    {
        logMessage = "Book not found";
        cout << "Book not found\n";
    }
    else
    {
        if (book->returnBook())
        {
            if (user->removeBorrowedBook(isbn))
            {
                logMessage = "User: " + user->getUsername() + "(ID: " + user->getUserId() + ") returned \"" + book->getTitle() + "\" SUCCESS";
                cout << "User: " + user->getUsername() + "(ID: " + user->getUserId() + ") returned \"" + book->getTitle() + "\" SUCCESS\n";
            }
            else
            {
                logMessage = "FAILED: User: " + user->getUsername() + "(ID: " + user->getUserId() + ") not borrowed this book";
                cout << "FAILED: User: " + user->getUsername() + "(ID: " + user->getUserId() + ") not borrowed this book\n";
                book->borrowBook();
            }
        }
        else
        {
            logMessage = "FAILED: This book was not borrowed by anyone";
            cout << "FAILED: This book was not borrowed by anyone\n";
        }
    }

    lock_guard<mutex> libraryLock(libraryMutex);
    logEntries.push_back(logMessage);
}

void Library::printLog() const
{
    lock_guard<mutex> libraryLock(libraryMutex);
    cout << "\n Library Activity Log \n";
    if (logEntries.empty())
    {
        cout << "No activities logged in library. \n";
        return;
    }
    for (const auto &i : logEntries)
    {
        cout << i << endl;
    }
}