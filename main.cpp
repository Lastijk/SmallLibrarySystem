#include <iostream>
#include <string>
#include <vector>
#include "Users.h"
#include "Rules.h"
#include "Library.h"

static void printMenu(){
    std::cout << "\n=== Library Management ===\n";
    std::cout << "1. Add Book\n";
    std::cout << "2. Remove Book\n";
    std::cout << "3. Register User\n";
    std::cout << "4. Borrow Book\n";
    std::cout << "5. Return Book\n";
    std::cout << "6. Search Books\n";
    std::cout << "7. Overdue List\n";
    std::cout << "0. Exit\n";
}

int main(){
    Library lib;

    while(true){
        printMenu();
        std::cout << "Enter choice: ";
        int choice;
        if(!(std::cin >> choice)) return 0;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if(choice == 0) return 0;
        if(choice == 1){
            std::string t,a,i,g;
            std::cout << "Title: "; std::getline(std::cin, t);
            std::cout << "Author: "; std::getline(std::cin, a);
            std::cout << "ISBN: "; std::getline(std::cin, i);
            std::cout << "Genre: "; std::getline(std::cin, g);
            lib.addBook(t,a,i,g);
            std::cout << "Added.\n";
        }else if(choice == 2){
            std::string i;
            std::cout << "ISBN: "; std::getline(std::cin, i);
            std::cout << (lib.removeBook(i) ? "Removed" : "Not found") << "\n";
        }else if(choice == 3){
            std::string n,id,e,tp;
            std::cout << "Name: "; std::getline(std::cin, n);
            std::cout << "UserId: "; std::getline(std::cin, id);
            std::cout << "Email: "; std::getline(std::cin, e);
            std::cout << "Type (Student/Faculty/Guest): "; std::getline(std::cin, tp);
            lib.registerUser(n,id,e,tp);
            std::cout << "Registered.\n";
        }else if(choice == 4){
            std::string id,i;
            std::cout << "UserId: "; std::getline(std::cin, id);
            std::cout << "ISBN: "; std::getline(std::cin, i);
            std::cout << (lib.borrowBook(id,i) ? "Borrowed" : "Failed") << "\n";
        }else if(choice == 5){
            std::string id,i;
            std::cout << "UserId: "; std::getline(std::cin, id);
            std::cout << "ISBN: "; std::getline(std::cin, i);
            std::cout << (lib.returnBook(id,i) ? "Returned" : "Failed") << "\n";
        }else if(choice == 6){
            std::string q;
            std::cout << "Query: "; std::getline(std::cin, q);
            auto res = lib.searchBooks(q);
            std::cout << "Found " << res.size() << " book(s):\n";
            for(const auto& b : res){
                std::cout << b.getTitle() << " by " << b.getAuthor() << " (" << b.getIsbn() << ")" << (b.isAvailable()?"":" [BORROWED]") << "\n";
            }
        }else if(choice == 7){
            auto overdue = lib.getOverdueBooks();
            if(overdue.empty()){
                std::cout << "No overdue.\n";
            }else{
                for(const auto& r : overdue){
                    auto now = std::chrono::system_clock::now();
                    auto due = r.borrowedAt + std::chrono::hours(24 * r.allowedDays);
                    auto overdue_days = std::chrono::duration_cast<std::chrono::hours>(now - due).count() / 24;
                    std::cout << "User " << r.userId << " overdue book " << r.isbn << " by " << overdue_days << " days+\n";
                }
            }
        }else{
            std::cout << "Invalid choice\n";
        }
    }
}
