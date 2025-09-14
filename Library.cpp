#include "Library.h"
#include "Rules.h"
#include <algorithm>
#include <memory>

void Library::addBook(const std::string& title, const std::string& author, const std::string& isbn, const std::string& genre){
    isbnToBook_.emplace(isbn, Book(title, author, isbn, genre));
    genres_.insert(genre);
}

bool Library::removeBook(const std::string& isbn){
    return isbnToBook_.erase(isbn) > 0;
}

Book* Library::findBook(const std::string& isbn){
    auto it = isbnToBook_.find(isbn);
    if(it == isbnToBook_.end()) return nullptr;
    return&it->second;
}

std::vector<Book> Library::searchBooks(const std::string& query) const{
    std::vector<Book> result;
    for(const auto& [isbn, book] : isbnToBook_){
        if(book.getIsbn().find(query) != std::string::npos
           || book.getTitle().find(query) != std::string::npos
           || book.getAuthor().find(query) != std::string::npos){
            result.push_back(book);
        }
    }
    return result;
}

void Library::registerUser(const std::string& name, const std::string& userId, const std::string& email, const std::string& type){
    if(type == "Student"){
        auto p = std::make_unique<Student>(name, userId, email);
        p->setRestrictions(Rules["Student"]);
        userIdToUser_[userId] = std::move(p);
        return;
    }
    if(type == "Faculty"){
        auto p = std::make_unique<Faculty>(name, userId, email);
        p->setRestrictions(Rules["Faculty"]);
        userIdToUser_[userId] = std::move(p);
        return;
    }
    auto p = std::make_unique<Guest>(name, userId, email);
    p->setRestrictions(Rules["Guest"]);
    userIdToUser_[userId] = std::move(p);
}

UserInterface* Library::findUser(const std::string& userId){
    auto it = userIdToUser_.find(userId);
    if(it == userIdToUser_.end()) return nullptr;
    return it->second.get();
}

bool Library::borrowBook(const std::string& userId, const std::string& isbn){
    UserInterface* user = findUser(userId);
    Book* book = findBook(isbn);
    if(!user || !book) return false;
    if(!book->isAvailable()) return false;
    if(!user->canBorrow()) return false;

    book->setAvailable(false);
    user->addBorrowed(isbn);

    BorrowingRecord rec{userId, isbn, std::chrono::system_clock::now(), user->GetBorrowDays()};
    history_.push_back(rec);
    return true;
}

bool Library::returnBook(const std::string& userId, const std::string& isbn){
    UserInterface* user = findUser(userId);
    Book* book = findBook(isbn);
    if(!user || !book) return false;

    if(!user->removeBorrowed(isbn)) return false;

    book->setAvailable(true);
    return true;
}

std::vector<BorrowingRecord> Library::getOverdueBooks() const{
    std::vector<BorrowingRecord> overdue;
    auto now = std::chrono::system_clock::now();
    for(const auto& rec : history_){
        auto due = rec.borrowedAt + std::chrono::hours(24* rec.allowedDays);
        if(now > due){
            overdue.push_back(rec);
        }
    }
    return overdue;
} 