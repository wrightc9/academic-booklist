/**
 * Title:   Lab 4 - Book class implementation
 *
 * Purpose: Create Book objects that store the name, isbn number, and year of the book
 * Class:   CSC 2430 Winter 2022
 * Author:  Christian Case Wright
 */
#include "book.h"

#include <string>
#include <iostream>


using std::string;
using std::ostream;
using std::istream;
using std::stringstream;
using std::to_string;
using std::getline;

// Implementation of Constructor that takes in name and year
Book::Book(const string& name, unsigned int year)
{
    _name = name;
    _year = year;
}
// Implementation of Constructor that takes in name, isbn and year
// Remember to validate the ISBN
Book::Book(const string& name, const string& isbn, unsigned int year)
{
    _name = name;

    if(IsValidISBN(isbn))
    {
        _isbn = isbn;
    }
    else
    {
        _isbn = "";
    }

    _year = year;
}

// Implementation of Copy constructor
Book::Book(const Book& book)
{
    _name = book.GetName();
    _year = book.GetYear();
    _isbn = book.GetISBN();

}

// Implementation of ToString method
// Format: Name of Book.ISBN.Year (Period separated values)
string Book::ToString() const
{
    return _name + "." + _isbn + "." + to_string(_year);
}
// Implementation of ToJSON method
// Format: {"name":"Algorithm Design", "isbn":"0321295358", "year":2015}
string Book::ToJSON() const
{
    return R"({"name":")" + _name + R"(", "isbn":")" + _isbn + R"(", "year":)" + to_string(_year) + "}";
}

// Implementation of ISBN getter/accessor method
string Book::GetISBN() const
{
    return _isbn;
}
// Implementation of Name getter/accessor method
string Book::GetName() const
{
    return _name;
}
// Implementation of Year getter/accessor method
int Book::GetYear() const
{
    return _year;
}
// Implementation of Read from istream method
// Remember that each book is in a single line, and that the fields are separated by period
void Book::Read(istream& input)
{
    string bookLine;
    int position = 0;
    int position2;

    // stores the line into a string
    getline(input, bookLine);

    //gets the position of the first period and takes everything before it and stores it into name
    position = bookLine.find('.', position);
    _name = bookLine.substr(0, position);

    // finds the position of the second period
    position2 = bookLine.find('.', position + 1);

    // checks to see if the isbn (everything in between the first and second period) is valid then stores it in isbn if it is
    if(IsValidISBN(bookLine.substr(position + 1, position2 - (position + 1))))
    {
        _isbn = bookLine.substr(position + 1, position2 - (position + 1));
    }
    else
    {
        _isbn = "";
    }

    // takes everything after the second period and stores it into year
    _year = stoi(bookLine.substr(position2 + 1, bookLine.length() - position2));

}
// Implementation of Write to ostream method
// This output *does not* include an end-line
void Book::Write(ostream& output)
{
    output << _name << "." << _isbn + "." << to_string(_year);
}

/**
 * This function checks if the string passed as parameter, isbn, represents a valid
 * isbn. To implement this function you will need to do research on how to validate ISBN.
 * Both ISBN10 and ISBN13 are expected to work with this function.
 * @param isbn the isbn that is going to be checked
 * @return true if the isbn given is a valid isbn, false otherwise
 */
bool IsValidISBN(const string& isbn){

    int countdown = isbn.length();
    int isbnTotal = 0;
    int isbnInt;

    // switch to determine the type of isbn
    switch(isbn.length())
    {
        // if isbn is 13 digits long
        case 13:
        {
            for(int i = 0; i < isbn.length()-1; i++)
            {
                if(isdigit(isbn[i]))
                {
                    isbnInt = isbn[i] - 48;

                    if(i % 2 == 0)
                    {
                        isbnTotal += isbnInt;
                    }
                    else
                    {
                        isbnTotal += isbnInt * 3;
                    }
                }
                else
                {
                    return false;
                }
            }
            if(isbnTotal % 10 == (10-(isbn[12] - 48)))
            {
                return true;
            }
            else
            {
                return false;
            }

        }
        // if isbn is 10 digits long
        case 10:
        {
            for(size_t i = 0; i < isbn.length(); i++)
            {
                if(std::isdigit(isbn[i]))
                {
                    isbnInt = isbn[i] - 48;
                    isbnTotal += (countdown * isbnInt);
                }
                else if(isbn[i] == 'X' || isbn[i] == 'x')
                {
                    isbnTotal += 10;
                }
                else
                {
                    return false;
                }

                countdown--;
            }
            if(isbnTotal%11 == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        // any other case
        default:
        {
            return false;
        }
    }
}
