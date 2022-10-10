/**
 * Title:   Lab 4 - BookList class implementation.
 *
 * Purpose: Used to create and edit linked list of book objects
 * Class:   CSC 2430 Winter 2022
 * Author:  Christian Case Wright
 */
#include "book_list.h"

#include <string>
#include <iostream>
using std::string;
using std::stringstream;
using std::ostream;
using std::istream;
using std::endl;

/**
 * Copy Constructor of the Book List
 * You don't need to implement this method.
 * @param other the original BookList that is going to be copied.
 */
BookList::BookList(const BookList &other){
}
/**
 * Copy Assignment operator of the Book List
 * You don't need to implement this method.
 * @param rhs The right hand side operand of the assignment.
 * @return a reference to the caller object
 */
BookList &BookList::operator=(const BookList &rhs){
    return *this;
}
/**
 * Default constructor
 * Initializes _head and _size
 */
BookList::BookList()
{
    _head = nullptr;
    _size = 0;
}
/**
 * Destructor
 * Empties the linked list and clears up memory
 */
BookList::~BookList()
{
    while (_head != nullptr)
    {
        Node* nodeToDelete = _head;
        _head = _head->next;
        delete nodeToDelete->book;
        delete nodeToDelete;
    }
}
/**
 * Dynamically allocates memory for and creates a copy of book object.
 * Creates new node with the book object and adds to the beginning of the list
 * @param book to be added
 * @return always returns true
 */
bool BookList::AddBook(const Book &book)
{
    Book* newBook = new Book(book);

    Node* newNode = new Node;
    newNode->book = newBook;
    newNode->next = _head;
    _head = newNode;

    _size++;

    return true;
}
/**
 * Creates new book object with parameters given.
 * Creates new node with the book object and adds to the beginning of the list
 * @param name
 * @param isbn
 * @param year
 * @return always returns true
 */
bool BookList::AddBook(const string &name, const string &isbn, unsigned int year)
{
    Book* newBook = new Book(name, isbn, year);

    Node* newNode = new Node;
    newNode->book = newBook;
    newNode->next = _head;
    _head = newNode;

    _size++;

    return true;
}
/**
 * Creates new book object with parameters given.
 * Creates new node with the book object and adds to the beginning of the list
 * @param name
 * @param year
 * @return always returns true
 */
bool BookList::AddBook(const string &name, unsigned int year)
{
    Book* newBook = new Book(name, year);

    Node* newNode = new Node;
    newNode->book = newBook;
    newNode->next = _head;
    _head = newNode;

    _size++;

    return true;
}
/**
 * Searches the linked list for an isbn and returns the position it is held.
 * if isbn is not in the list, returns -1
 * @param isbn the isbn of the book the user is searching for
 * @return position of the book in the list if found, -1 otherwise
 */
int BookList::IndexOf(const string &isbn) const
{
    int cur = 0;
    for (Node* ptr = _head; ptr != nullptr; ptr = ptr->next)
    {
        if (isbn == ptr->book->GetISBN())
        {
            return cur;
        }
        cur++;
    }
    return -1;
}
/**
 * returns pointer to the book at requested position, if not found, returns nullptr
 * @param position
 * @return pointer to book or nullptr
 */
const Book *BookList::Get(unsigned int position) const
{
    size_t cur = 0;
    for (Node* ptr = _head; ptr != nullptr; ptr = ptr->next)
    {
        if (cur == position)
        {
            return ptr->book;
        }
        cur++;
    }
    return nullptr;
}
/**
 * removes node from the list at a given position
 * @param position
 * @return true or false
 */
bool BookList::Remove(unsigned int position)
{
    Node* nodeToDelete;
    Node* nodeBefore;
    // if node is first item in the list
    if (0 == position)
    {
        nodeToDelete = _head;
        _head = _head->next;
    }
    // anywhere else in the list
    else
    {
        int cur = 0;
        // iterates through the list to find the position before the position to be removed and sets nodeBefore to it.
        for (Node* ptr = _head; ptr != nullptr; ptr = ptr->next)
        {
            if(cur == position - 1)
            {
                nodeBefore = ptr;
            }
            cur++;
        }
        // if the position is invalid, it returns false.
        if(nodeBefore == nullptr || nodeBefore->next == nullptr)
        {
            return false;
        }
        nodeToDelete = nodeBefore->next;
        nodeBefore->next = nodeToDelete->next;
    }

    delete nodeToDelete->book;
    delete nodeToDelete;
    _size--;
    return true;

}
/**
 * formats book objects in string format and returns it
 * Format for string to be returned:
 * [Book1Name.Book1ISBN.Book1Year, Book2Name.Book2ISBN, Book2Year, ...]
 * @return string list
 */
string BookList::ToString() const
{
    string list = "[";
    for (Node* ptr = _head; ptr != nullptr; ptr = ptr->next)
    {
        if (ptr != _head)
        {
            list += ", ";
        }
        list += ptr->book->ToString();
    }
    list += "]";

    return list;
}
/**
 * Reads from an input stream, each book will be stored in the stream in a single line.
 * @param input stream to read from
 * @return input to allow stream chaining
 */
istream &BookList::Read(istream &input)
{
    string bookLine;
    string name, isbn;
    int year;
    // looks through each line in the istream and creates a new book object for them, then adds it to the linked list
    while(getline(input, bookLine))
    {
        int position = 0;
        int position2;

        position = bookLine.find('.', position);
        name = bookLine.substr(0, position);

        position2 = bookLine.find('.', position + 1);
        isbn = bookLine.substr(position + 1, position2 - (position + 1));


        year = stoi(bookLine.substr(position2 + 1, bookLine.length() - position2));

        AddBook(name, isbn, year);

    }
    return input;
}
/**
 * Writes to the output stream, each book should be stored in a single line.
 * @param output
 * @return output to allow stream chaining
 */
ostream &BookList::Write(ostream &output) const
{
    for (Node* ptr = _head; ptr != nullptr; ptr = ptr->next)
    {
        output << ptr->book->ToString() << endl;
    }

    return output;
}
/**
 * going from start to end, deletes all nodes in the linked list and sets _head to nullptr and _size to 0
 */
void BookList::Clear()
{
    while (_head != nullptr)
    {
        Node* nodeToDelete = _head;
        _head = _head->next;
        delete nodeToDelete->book;
        delete nodeToDelete;
    }
    _size = 0;
}
/**
 * Takes each book in the linked list and returns them as a string in JSON format
 * Example:
 * [{"name":"book one", "isbn":"1234567890", "year":1900}, {"name":"book two", "isbn":"0987654321", "year":1901}]
 * @return string list
 */
string BookList::ToJSON() const
{
    string list = "[";
    for (Node* ptr = _head; ptr != nullptr; ptr = ptr->next)
    {
        if (ptr != _head)
        {
            list += ", ";
        }
        list += ptr->book->ToJSON();
    }
    list += "]";

    return list;
}
/**
 * returns the amount of nodes in the linked list
 * @return _size
 */
unsigned int BookList::Size() const
{
    return _size;
}
/**
 * constructor for node
 * sets book in node to parameter and next to nullptr
 * @param book
 */
BookList::Node::Node(const Book &book)
{
    this->book = new Book(book);
    next = nullptr;
}

/**
 * default constructor for node
 * sets book and next in the node to nullptr
 */
BookList::Node::Node()
{
    book = nullptr;
    next = nullptr;
}
