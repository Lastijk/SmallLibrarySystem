#pragma once
#include <utility>
#include <string>
#include <vector>
#include <unordered_map>

class UserInterface{
public:
    UserInterface(std::string  name, std::string id, std::string mail);

    virtual int GetMaxBooks() const = 0;

    virtual int GetBorrowDays() const = 0;

    bool canBorrow() const { return static_cast<int>(borrowed_books.size()) < GetMaxBooks(); }
    void addBorrowed(const std::string& isbn) { borrowed_books.push_back(isbn); }
    bool removeBorrowed(const std::string& isbn);

    void setRestrictions(const std::unordered_map<std::string,int>& r) { restrictions = r; }

protected:
    std::string name_, id_, mail_;
    std::vector<std::string> borrowed_books;
    std::unordered_map<std::string, int> restrictions;
};

class User : public UserInterface{
public:
    User(std::string name, std::string id, std::string mail);

    int GetMaxBooks() const override;

    int GetBorrowDays() const override;
};

class Student : public User{
public:
    Student(std::string name, std::string id, std::string mail);
};

class Faculty : public User{
public:
    Faculty(std::string name, std::string id, std::string mail);
};

class Guest : public User{
public:
    Guest(std::string name, std::string id, std::string mail);
};