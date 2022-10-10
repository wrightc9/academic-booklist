# A Simple Linked List of Books

## Introduction
This lab will require you to code a simple linked list where each of the elements of the list are going to be Books. An interesting twist of this linked list is that the `data` part of the `Node` is a pointer to a `Book`. This is so because the class `Book` doesn't have a default constructor!

## Learning Goals
* Practice programming with multiple files
* Practice programming using dynamic memory
* Create a module of a linked list with object elements

## The Target
You are to develop two classes: `Book` and `BookList`. The class `Book` is a simple class that stores the name, isbn and publishing date of a book. Class `BookList` represents a single-linked list where you can insert, remove, retrieve, etc. books.

## Classes Description

### Book

| Member                       | Description                                                                                                                                                                                                                                                                                                                                                                                                  |
|------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `_name`                      | Represents the name of the book. Store it with spaces                                                                                                                                                                                                                                                                                                                                                        |
| `_isbn`                      | Represents a valid ISBN. Never stores an invalid ISBN, instead it would store empty string                                                                                                                                                                                                                                                                                                                   |
| `_year`                      | Represents the publishing year                                                                                                                                                                                                                                                                                                                                                                               |
| Book Constructor 1           | Constructor with `name` and `year`. Sets the ISBN to empty string                                                                                                                                                                                                                                                                                                                                            |
| Book Constructor 2           | Constructor with `name`, `year` and `isbn`. Needs to check if the ISBN is a valid one, if the provided isbn is not valid, it should set `_isbn` to empty string                                                                                                                                                                                                                                              |
| Copy Constructor             | Copy Constructor.                                                                                                                                                                                                                                                                                                                                                                                            |
| `ToString()` method          | Returns a string representation of the book. It will concatenate all three fields and separate them by period. Example: `"The Book of the Jungle.1111111111.1900"`, in the case the entered ISBN is invalid (or not provided) then it would look: `"My Book..2021"`                                                                                                                                          |
| `ToJSON()` method            | Returns a JSON string representation of the book. It will use the field names: `name`, `isbn`, `year`. Note that `year` is a number so it doesn't need quotation marks for the value. Example: `"{"name":"The Book of the Jungle", "isbn":"1111111111", "year":1900}"`                                                                                                                                       |
| ISBN getter/accessor method  | Accessor method, returns the ISBN                                                                                                                                                                                                                                                                                                                                                                            |
| Name  getter/accessor method | Accessor method, returns the name                                                                                                                                                                                                                                                                                                                                                                            |
| Year  getter/accessor method | Accessor method, returns the year                                                                                                                                                                                                                                                                                                                                                                            |
| `Read` from `istream` method | Reads a book from the input stream `input`. The book in the input should be stored in a single line (At the end of the book there should be a `\n` character). The format of the book being read is the same as the format of the string representation created by the `ToString` method. Remember to validate the ISBN before setting it.  Assume that the input is always going to be correctly formatted. |
| `Write` to `ostream` method` | Writes a book to the output stream `output`. The format of the output book is the same as the string created by the `ToString` method                                                                                                                                                                                                                                                                        |                                          

There is non-member function declared in your `book.h` file that needs to be implemented in the `book.cpp` file. The function is `bool IsValidISBN(const string& isbn);` this function takes in a string holding an ISBN, the function will check if the ISBN is valid or not, and will return true or false accordingly.
> Note: **You** will need to research on how to check if an ISBN is valid and create the algorithm based on your research. A good _starting_ point is: [Wikipedia: ISBN](https://en.wikipedia.org/wiki/International_Standard_Book_Number)


### Node
Class node looks like this:
```cpp
class Node{
public:
    Book* book;
    Node* next;
    Node(const Book& book);
    Node();
};
```

The implementation of both constructors is provided to you. Note that this class is declared as `private` inside class `BookList`.

### BookList

| Member | Description                                                                                                                                                                                                        |
|------- |--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|`Node* _head` | Pointer to the first node of the linked list                                                                                                                                                                       |
|`size_t _size` | Keeps track of how many elements there are in the list                                                                                                                                                             |
|`BookList(const BookList& other)` | Copy constructor, set to private, no need to implement                                                                                                                                                             |
|`BookList& operator=(const BookList& rhs)` | Copy assignment operator, set to private, just return `*this`                                                                                                                                                      |
|`BookList()` | Default constructor, initialize `_head` and `_size`                                                                                                                                                                |
|`~BookList()` | Destructor, takes care of deallocating the memory used by the nodes and their books. Remember, the books on each one of the nodes were also dynamically allocated!                                                 |
|`bool AddBook(const Book& book)` | Adds a book at the beginning of the list. The parameter is a book already created by the user, you'll need to dynamically allocate a copy of the parameter.                                                        |
|`bool AddBook(const string& name, const string& isbn, unsigned int year)` | Creates a book using the parameters, then adds the book at the beginning of the list.                                                                                                                              |
|`bool AddBook(const string& name, unsigned int year)` | Creates a book using the parameters, then adds the book at the beginning of the list.                                                                                                                              |
|`int IndexOf(const string& isbn)const` | Searches the list using a linear search (traversing the list) to find a book with the given `isbn`, if the book is found the method returns the position where it was found, if it wasn't found then it returns -1 |
|`const Book* Get(unsigned int position)const` | Returns the pointer to the book that is located at the given `position`. If the `position` is not valid it returns `nullptr`                                                                                       |
|`bool Remove(unsigned int position)` | Removes the book located in the given `position`. If the `position` is not valid returns false.                                                                                                                    |
|`string ToString()const` | Returns a string representation of the list. See below for examples.                                                                                                                                               |
|`string ToJSON()const` | Returns a string in JSON format that represents the list. See below for examples.                                                                                                                                  |
|`istream& Read(istream& input)` | Reads a list of books from the given input stream `input`. Each one of the books will be separated by `\n`. Assume that the input is always going to be correctly formatted.                                       |
|`ostream& Write(ostream& output)const` | Writes the books to the given output stream `output`. Each book will be in their own line, that is the books will be separated by `\n`.                                                                            |
|`void Clear()` | Clears the whole list. It frees all the allocated memory for the elements of the list, sets `_head` to `nullptr` and `_size` to zero.                                                                              |
|`unsigned int Size()const` | Returns the number of elements of the list.                                                                                                                                                                        |

### Example of `ToString` returned string
The elements of the list are enclosed by `[]`, each element is separated by comma and space.
```txt
[The Bible.9780825432286.2004, How to Read the Bible Book by Book.9780310211181.2002, The New American Bible.9780382007354.1970, Revelation.9780857861016.2010, Holy Bible.9780340979655.2010]
```

### Example of `ToJSON` returned string
The elements are represented in JSON format, just like `ToString` the list is enclosed in `[]`, and each one of the elements are separated by comma and space.
```json
[{"name":"Book #4", "isbn":"", "year":1994}, {"name":"Book #2", "isbn":"", "year":1993}, {"name":"Book #1", "isbn":"", "year":1990}]
```

## What you are given

* `Book` class, the declaration of the class is found in `book.h` and the definition of the methods in `book.cpp`. You are expected to write the declaration of all the "listed" methods in the header file. Then you will need to implement all those methods in the cpp file. Additionally, you will need to implement the function (note this is not a method): `bool IsValidISBN(const string& isbn);` that is declared in the header file. Remember to implement the function in the cpp file.
* `BookList` class, the declaration of the class is found in `book_list.h` and the definition of the methods in `book_list.cpp`. You are expected to implement all of its methods.
* The `main` function is located in `main.cpp`. You should **not** change this file in any way.

## A Possible Worklist

One possible way to solve this lab is to do the following activities:

1. Implement `IsValidISBN`. 
   1. Build and run your program to pass the tests related to this function.
   2. You should pass Tests 1-17
2. Implement all the `Book` class methods. 
   1. Build and run your program and make sure all the `Book` method tests are passed.
   2. You should pass Tests 18-30
3. Implement the methods of the `BookList` class incrementally:
   1. Constructor and Destructor
   2. Implement `ToJSON`, `ToString`, `Add` and `Size`.
   3. Build and run your program to make sure the tests related to the methods above (31-37, 57-58).
   4. Implement `Write`
   5. Build and run your program to make sure the test related to the `Write` method (38-40, 59).
   6. Implement `IndexOf`
   7. Build and run to make sure you pass the tests related to the `IndexOf` method (41-44).
   8. Implement `Get` 
   9. Build and run to make sure you pass the tests related to the `Get` method (45-48).
   10. Implement `Remove` 
   11. Build and run to make sure you pass the tests related to the `Remove` method (49-56).
   12. Implement `Clear`
   13. Build and run to make sure you pass the tests related to the `Clear` method (60-62).
   14. Implement `Read`
   15. Build and run to make sure you pass the tests related to the `Read` method (63-70).

## Testing your Code
Below you can see the expected output of your program:
```
- * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * 
- * - * - *     ISBN TESTS      - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * 

+	TEST  1 PASSED (Test Valid ISBN = 9780306406157                        ) Total Passed: 1
+	TEST  2 PASSED (Test Valid ISBN = 007462542X                           ) Total Passed: 2
+	TEST  3 PASSED (Test Not-Valid ISBN = 0112112425                       ) Total Passed: 3
+	TEST  4 PASSED (Test Valid ISBN = 9386954214                           ) Total Passed: 4
+	TEST  5 PASSED (Test Valid ISBN = 9971502100                           ) Total Passed: 5
+	TEST  6 PASSED (Test Valid ISBN = 9780131103627                        ) Total Passed: 6
+	TEST  7 PASSED (Test Valid ISBN = 0131103628                           ) Total Passed: 7
+	TEST  8 PASSED (Test Not-Valid ISBN = 9780131103621                    ) Total Passed: 8
+	TEST  9 PASSED (Test Not-Valid ISBN = 0131103608                       ) Total Passed: 9
+	TEST 10 PASSED (Test Valid ISBN = 0857861018                           ) Total Passed: 10
+	TEST 11 PASSED (Test Valid ISBN = 9780382007354                        ) Total Passed: 11
+	TEST 12 PASSED (Test Valid ISBN = 0382007352                           ) Total Passed: 12
+	TEST 13 PASSED (Test Valid ISBN = 9780825432286                        ) Total Passed: 13
+	TEST 14 PASSED (Test Valid ISBN = 0825432286                           ) Total Passed: 14
+	TEST 15 PASSED (Test Valid ISBN = 080442957X                           ) Total Passed: 15
+	TEST 16 PASSED (Test Not-Valid ISBN = 080442157X                       ) Total Passed: 16
+	TEST 17 PASSED (Test Not-Valid ISBN = ""                               ) Total Passed: 17

- * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * 
- * - * - *     Book TESTS      - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * 

+	TEST 18 PASSED (Book::ToString()                                       ) Total Passed: 18
+	TEST 19 PASSED (Book::ToJSON                                           ) Total Passed: 19
+	TEST 20 PASSED (Book::GetISBN()                                        ) Total Passed: 20
+	TEST 21 PASSED (Book::GetName()                                        ) Total Passed: 21
+	TEST 22 PASSED (Book::GetYear()                                        ) Total Passed: 22
+	TEST 23 PASSED (Book::Write()                                          ) Total Passed: 23
+	TEST 24 PASSED (Book::Read()                                           ) Total Passed: 24
+	TEST 25 PASSED (Book::ToString()                                       ) Total Passed: 25
+	TEST 26 PASSED (Book::ToJSON                                           ) Total Passed: 26
+	TEST 27 PASSED (Book::GetISBN()                                        ) Total Passed: 27
+	TEST 28 PASSED (Book::GetName()                                        ) Total Passed: 28
+	TEST 29 PASSED (Book::GetYear()                                        ) Total Passed: 29
+	TEST 30 PASSED (Book::Write()                                          ) Total Passed: 30

- * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * - * 
- * - * - *     BookList TESTS      - * - * - * - * - * - * - * - * - * - * - * - * - * - * 

+	TEST 31 PASSED (BookList::ToJSON()                                     ) Total Passed: 31
+	TEST 32 PASSED (BookList::ToString()                                   ) Total Passed: 32
+	TEST 33 PASSED (BookList::Size()                                       ) Total Passed: 33
+	TEST 34 PASSED (BookList::Add(...) returned true                       ) Total Passed: 34
+	TEST 35 PASSED (Size increment to 1                                    ) Total Passed: 35
+	TEST 36 PASSED (BookList::Add(...) returned true                       ) Total Passed: 36
+	TEST 37 PASSED (Size increment to 2                                    ) Total Passed: 37
+	TEST 38 PASSED (BookList::Write()                                      ) Total Passed: 38
+	TEST 39 PASSED (BookList::Add(...) returned true                       ) Total Passed: 39
+	TEST 40 PASSED (Size increment to 3                                    ) Total Passed: 40
+	TEST 41 PASSED (BookList::IndexOf() test 1                             ) Total Passed: 41
+	TEST 42 PASSED (BookList::IndexOf() test 2                             ) Total Passed: 42
+	TEST 43 PASSED (BookList::IndexOf() test 3                             ) Total Passed: 43
+	TEST 44 PASSED (BookList::IndexOf() test 4                             ) Total Passed: 44
+	TEST 45 PASSED (BookList::Get() test 1                                 ) Total Passed: 45
+	TEST 46 PASSED (BookList::Get() test 2                                 ) Total Passed: 46
+	TEST 47 PASSED (BookList::Get() test 3                                 ) Total Passed: 47
+	TEST 48 PASSED (BookList::Get() test 4                                 ) Total Passed: 48
+	TEST 49 PASSED (BookList::Remove() Invalid Position                    ) Total Passed: 49
+	TEST 50 PASSED (BookList::Size() = 3, did not remove                   ) Total Passed: 50
+	TEST 51 PASSED (BookList::Remove() Middle                              ) Total Passed: 51
+	TEST 52 PASSED (BookList::Size() = 2, did remove                       ) Total Passed: 52
+	TEST 53 PASSED (BookList::Remove() First                               ) Total Passed: 53
+	TEST 54 PASSED (BookList::Size() = 1, did remove                       ) Total Passed: 54
+	TEST 55 PASSED (BookList::Remove() Last and Only                       ) Total Passed: 55
+	TEST 56 PASSED (BookList::Size() = 0, did remove                       ) Total Passed: 56
+	TEST 57 PASSED (BookList::ToString()                                   ) Total Passed: 57
+	TEST 58 PASSED (BookList::ToJSON()                                     ) Total Passed: 58
+	TEST 59 PASSED (BookList::Write()                                      ) Total Passed: 59
+	TEST 60 PASSED (Empty list (size == 0) after BookList::Clear()         ) Total Passed: 60
+	TEST 61 PASSED (Empty list (ToString() == []) after BookList::Clear()  ) Total Passed: 61
+	TEST 62 PASSED (Empty list (Get(0) == nullptr) after BookList::Clear() ) Total Passed: 62
+	TEST 63 PASSED (After reading from istream BookList::Read()            ) Total Passed: 63
+	TEST 64 PASSED (ToString after reading from stream BookList::Read()    ) Total Passed: 64
+	TEST 65 PASSED (Check after reading from istream, element 0            ) Total Passed: 65
+	TEST 66 PASSED (Check after reading from istream, element 1            ) Total Passed: 66
+	TEST 67 PASSED (Check after reading from istream, element 2            ) Total Passed: 67
+	TEST 68 PASSED (Check after reading from istream, element 3            ) Total Passed: 68
+	TEST 69 PASSED (Check after reading from istream, element 4            ) Total Passed: 69
+	TEST 70 PASSED (No sixth element on list of 5 elements                 ) Total Passed: 70

```

## Grading Rubric
There are 70 tests that your code needs to pass. If a test is failed, then the message will appear there and that test will not be counted towards the total test passed. Your "gross" grade will be the number of tests you passed divided by 70 times 100.

<img src="https://render.githubusercontent.com/render/math?math=grade=\frac{Tests Passed}{70}*100">

Remember that you are expected to follow the good programming practices and course coding conventions. See the [Deductions](Deductions) section for details on the issues that may reduce your gross grade.


### Deductions
* For each infraction on good programming practices there will be a deduction of 5 points. See Canvas page about Expected Good Programming Practices.
* If the program has a runtime error (the program crashes) there will be a deduction of 10 points
* If the program does not have comment headers there will be a deduction of 10 points
* If the program does not have comments on functions and appropriate additional comments there will be a deduction of 5 points
* If the program does not follow instructions, for instance if you did not implement any of the requested functions, there will be a deduction of 5 points per ignored instruction
* If the program does not run (compilation or linking errors), the grade will be zero.
* If you modify the file `main.cpp` in any way, the grade will be zero.


### Grading yourself
It is possible, and encouraged that you grade your own assignment. The steps to grade your assignment:
1. Make sure your code run, if it doesn't you will not receive credit for this assignment.
3. Calculate your gross grade using the formula provided above
4. Check that your code follows the programming guidelines
   1. Is your code following the identifier naming conventions?
   2. Is your code appropriately indented?
   3. Does your code avoid using global variables?
   4. Does your code use a consistent style of {}?
   5. Are all your identifiers using meaningful names?
   6. Are all non-primitive type parameters passed by reference and const when needed?
   7. Is your code clean?
   8. Does your code avoid using `cout` or `cin` inside functions or methods that are not supposed to have console input or output?
   9. Does your program run smoothly? (Your code doesn't crash)
   10. Does your code have all the header comments?
   11. If your answer to all the above questions is yes, then you are unlikely to lose any points and your assignment final grade should be very close to the gross grade.

A warning: hard-coding your output will result in a zero grade!

## Academic Integrity

This programming assignment is to be done on an individual basis. At the same time, it is understood that learning from your peers is valid, and you are encouraged to talk among yourselves about programming in general and current assignments in particular. Keep in mind, however, that each individual student must do the work in order to learn.

Hence, the following guidelines are established:

* Feel free to discuss any and all programming assignments but do not allow other students to look at or copy your code. Do not give any student an electronic or printed copy of any program you write for this class.
* Gaining the ability to properly analyze common programming errors is an important experience. Do not deprive a fellow student of his/her opportunity to practice problem solving: control the urge to show them what to do by writing the code for them.
* If you’ve given the assignment a fair effort and still need help, see the instructor or a lab assistant.
* If there is any evidence that a program or other written assignment was copied from another student (or from any source), neither student will receive any credit for it. This rule will be enforced.
* Protect yourself: Handle throw-away program listings carefully.
* Remember to read the Academic Integrity guidelines provided in the class syllabus.


## Extra Credit

Using the Menu class, create an application for a Book Store, the menu should have the following options:
```
1. Add a Book
2. Find a Book
3. Get a Book
4. List all Books
5. Remove one Book
6. Remove all Books
99. Exit
```

To be able to get the extra credit you will need to:
* Copy the working files `menu_element.h`, `menu_element.cpp`, `menu.h` and `menu.cpp` into your project. Remember to add them when you commit using GitHub desktop.
* Create a new main, call it `extracredit.cpp`, in that main you will code your extra credit.
* When you want to run your `extracredit.cpp` change `main.cpp` to `extracredit.cpp` in the `CMakeLists.txt` file. This way your program will know that it needs to use the `main` function of `extracredit.cpp` instead of the `main` function that has the tests script. **REMEMBER** in your `CMakeLists.txt` file there cannot be two files that have main!

### BRIEF description of each of the options

1. Add a Book. Request name, isbn and publishing date from the user. Adds a book with the input information to the list.
2. Find a Book. Requests an isbn from the user, if the isbn is found, the program displays the rest of the book's information.
3. Get a Book. Requests a number from the user, if that number is a valid position on the list the program displays the book's information.
4. List all Books. Shows all the books on the list. Nicely formatted!
5. Remove one Book. Given the isbn of a book this option will check if that there is a book with that isbn, if that's the case, the program will remove that book from the list.
6. Remove all Books. Clears all the books from the list.

You are not given a sample of the output for the extra credit, so you will have more space for creativity. However, make sure that all the operations mentioned above work at least according to the description.

### Grading the Extra Credit
* The program adds and lists books. 10
* The program finds an added book, and reports when it is not found. 10
* The program gets a book, and reports when the position is not found. 10
* The program removes and lists books. 10
* The program clears the list. 10



