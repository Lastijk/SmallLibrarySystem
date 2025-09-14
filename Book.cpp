#include "Book.h"
#include <utility>

Book::Book(std::string title, std::string author, std::string isbn, std::string genre)
    : title_(std::move(title)), author_(std::move(author)), isbn_(std::move(isbn)), genre_(std::move(genre)), available_(true){}

const std::string& Book::getTitle() const { return title_; }
const std::string& Book::getAuthor() const { return author_; }
const std::string& Book::getIsbn() const { return isbn_; }
const std::string& Book::getGenre() const { return genre_; }

bool Book::isAvailable() const { return available_; }
void Book::setAvailable(bool available) { available_ = available; } 