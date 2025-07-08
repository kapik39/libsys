#ifndef LIBRARY_H
#define LIBRARY_H

#include <Book.h>
#include <User.h>
#include <map>
#include <vector>
#include <memory>

class Library
{
private:
    map<string, shared_ptr<Book>> books;
    map<string, shared_ptr<User>> users;

    vector<string> logEntries;
    mutable mutex libraryMutex;

public:
    Library();

    void addBook(const string &title, const string &author, const string &isbn, const int &numberOfBook);

    shared_ptr<Book> findBook(const string &isbn) const;

    void printAllBooks() const;

    void addUser(const string &userId, const string &username);

    shared_ptr<User> findUser(const string &userId) const;

    void printAllUser() const;

    void printUserBorrowedBooks(const string &userId) const;

    void performBorrow(const string &userId, const string &isbn);

    void performReturn(const string &userId, const string &isbn);

    void printLog() const;
};

#endif