#include <User.h>
#include <Book.h>
#include <iostream>
#include <algorithm>

using namespace std;

User::User(string userId, string username)
    : userId(move(userId)), username(move(username)) {}

string User::getUserId() const
{
    return userId;
}

string User::getUsername() const
{
    return username;
}

bool User::hasBorrowedBook(const string &isbn) const
{
    lock_guard<mutex> userLock(userMutex);
    for (const auto &book : borrowedBooks)
    {
        if (book->getIsbn() == isbn)
        {
            return true;
        }
    }
    return false;
}

bool User::addBorrowedBook(shared_ptr<Book> book)
{
    lock_guard<mutex> userLock(userMutex);
    if (!hasBorrowedBook(book->getIsbn()))
    {
        borrowedBooks.push_back(book);
        return true;
    }
    return false;
}

bool User::removeBorrowedBook(const string &isbn)
{
    lock_guard<mutex> userLock(userMutex);
    auto remove = remove_if(borrowedBooks.begin(), borrowedBooks.end(), [&isbn](const shared_ptr<Book> &r)
                            { return r->getIsbn() == isbn; });
    if (remove != borrowedBooks.end())
    {
        borrowedBooks.erase(remove, borrowedBooks.end());
        return true;
    }
    return false;
}

void User::printBorrowedBooks() const
{
    lock_guard<mutex> userLock(userMutex);
    if (borrowedBooks.empty())
    {
        cout << "User: " << username << ", ID: " << userId << " not has book borrowed!" << endl;
        return;
    }
    cout << "User: " << username << ", ID: " << userId << " List of book borrowed:" << endl;
    for (const auto &i : borrowedBooks)
    {
        cout << "- \"" << i->getTitle() << "\" ISBN: " << i->getIsbn() << endl;
    }
}