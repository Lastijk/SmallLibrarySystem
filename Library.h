#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <optional>
#include <set>
#include <memory>
#include <chrono>
#include "Book.h"
#include "Users.h"
#include "BorrowingRecord.h"

class Library{
public:
    Library() = default;

    void addBook(const std::string& title, const std::string& author, const std::string& isbn, const std::string& genre);
    bool removeBook(const std::string& isbn);
    Book* findBook(const std::string& isbn);
    std::vector<Book> searchBooks(const std::string& query) const;

    void registerUser(const std::string& name, const std::string& userId, const std::string& email, const std::string& type);
    UserInterface* findUser(const std::string& userId);

    bool borrowBook(const std::string& userId, const std::string& isbn);
    bool returnBook(const std::string& userId, const std::string& isbn);
    std::vector<BorrowingRecord> getOverdueBooks() const;

private:
    std::unordered_map<std::string, Book> isbnToBook_;
    std::unordered_map<std::string, std::unique_ptr<UserInterface>> userIdToUser_;
    std::vector<BorrowingRecord> history_;
    std::set<std::string> genres_;
}; 