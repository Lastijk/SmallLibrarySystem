#include "Users.h"
#include "Rules.h"
#include <utility>
#include <algorithm>

UserInterface::UserInterface(std::string name, std::string id, std::string mail) : name_(std::move(name)), id_(std::move(id)), mail_(std::move(mail)){
}

bool UserInterface::removeBorrowed(const std::string& isbn){
    auto it = std::find(borrowed_books.begin(), borrowed_books.end(), isbn);
    if(it == borrowed_books.end()) return false;
    borrowed_books.erase(it);
    return true;
}

User::User(std::string name, std::string id, std::string mail) : UserInterface(std::move(name), std::move(id), std::move(mail)){
}

int User::GetMaxBooks() const{
    return restrictions.at("MaxBooks");
}

int User::GetBorrowDays() const{
    return restrictions.at("MaxDays");
}

Student::Student(std::string name, std::string id, std::string mail) : User(std::move(name), std::move(id), std::move(mail)){
    restrictions = Rules["Student"];
}

Faculty::Faculty(std::string name, std::string id, std::string mail) : User(std::move(name), std::move(id), std::move(mail)){
    restrictions = Rules["Faculty"];
}

Guest::Guest(std::string name, std::string id, std::string mail) : User(std::move(name), std::move(id), std::move(mail)){
    restrictions = Rules["Guest"];
}