#pragma once
#include <string>
#include <chrono>

struct BorrowingRecord {
    std::string userId;
    std::string isbn;
    std::chrono::system_clock::time_point borrowedAt;
    int allowedDays = 0;

    BorrowingRecord() = default;

    BorrowingRecord(const std::string& userId, const std::string& isbn,
                    const std::chrono::system_clock::time_point& borrowedAt,
                    int allowedDays)
            : userId(userId), isbn(isbn), borrowedAt(borrowedAt), allowedDays(allowedDays) {}
};