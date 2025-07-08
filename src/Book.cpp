#include <Book.h>
#include <iostream>

using namespace std;

Book::Book(string title, string author, string isbn, int numberOfBook)
    : title(move(title)), author(move(author)), isbn(move(isbn)), numberOfBook(move(numberOfBook)), numberOfBorrwed(0), isBorrowed(false), isEmpty(false) {}

string Book::getTitle() const
{
    return title;
}

string Book::getAuthor() const
{
    return author;
}

string Book::getIsbn() const
{
    return isbn;
}

int Book::getNumberOfBook() const
{
    return numberOfBook;
}

bool Book::isAvailable() const
{
    lock_guard<mutex> bookLock(bookMutex);
    return !isEmpty;
}

bool Book::borrowBook()
{
    lock_guard<mutex> bookLock(bookMutex);
    if (!isEmpty)
    {
        numberOfBorrwed += 1;
        if (numberOfBorrwed == numberOfBook)
        {
            isEmpty = true;
        }
        isBorrowed = true;
        return true;
    }
    return false;
}

bool Book::returnBook()
{
    lock_guard<mutex> bookLock(bookMutex);
    if (isBorrowed)
    {
        numberOfBorrwed -= 1;
        if (numberOfBorrwed == 0)
        {
            isBorrowed = false;
        }
        isEmpty = false;
        return true;
    }
    return false;
}