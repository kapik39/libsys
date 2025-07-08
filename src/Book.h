#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <mutex>

using namespace std;

class Book
{
private:
    string title;
    string author;
    string isbn;
    int numberOfBook;
    int numberOfBorrwed;
    bool isBorrowed;
    bool isEmpty;
    mutable mutex bookMutex;

public:
    Book(string title, string author, string isbn, int numberOfBook);

    string getTitle() const;
    string getAuthor() const;
    string getIsbn() const;
    int getNumberOfBook() const;

    bool isAvailable() const;

    bool borrowBook();
    bool returnBook();
};

#endif