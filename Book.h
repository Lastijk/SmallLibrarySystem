#pragma once
#include <string>

class Book{
public:
    Book() = default;
    Book(std::string title, std::string author, std::string isbn, std::string genre);

    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    const std::string& getIsbn() const;
    const std::string& getGenre() const;

    bool isAvailable() const;
    void setAvailable(bool available);

private:
    std::string title_;
    std::string author_;
    std::string isbn_;
    std::string genre_;
    bool available_ {true};
}; 