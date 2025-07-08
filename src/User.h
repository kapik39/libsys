#ifndef USER_H
#define USER_H

#include <iostream>
#include <mutex>
#include <vector>
#include <memory>

using namespace std;

class Book;
class User
{
private:
    string userId;
    string username;
    vector<shared_ptr<Book>> borrowedBooks;
    mutable mutex userMutex;

public:
    User(string userId, string username);

    string getUserId() const;
    string getUsername() const;

    bool hasBorrowedBook(const string &isbn) const;
    bool addBorrowedBook(shared_ptr<Book> book);
    bool removeBorrowedBook(const string &isbn);
    void printBorrowedBooks() const;
};

#endif