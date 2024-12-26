#include <iostream>
#include "SearchHeader.h"

int main() {
    Queue emailQueue;
    readEmailsFromCSV("Emails.csv", emailQueue);

    int choice;
    std::string keyword;

    while (true) {
        std::cout
            << "\n---------------------------------\n"
            << "\nSearch Menu\n"
            << "\n1. Display All Emails\n"
            << "2. Search Email\n"
            << "3. Search by Month\n"
            << "5. Exit\n"
            << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Try again.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            displayAllEmails(emailQueue);
            break;
        case 2:
            std::cout << "Enter search keyword: ";
            std::getline(std::cin, keyword);
            searchEmail(emailQueue, keyword);
            break;
        case 3:
            std::cout << "Enter month (e.g., July): ";
            std::getline(std::cin, keyword);
            searchByMonth(emailQueue, keyword);
            break;
        case 5:
            std::cout << "Exiting...\n";
            return 0;
        default:
            std::cout << "Invalid choice. Try again.\n";
            break;
        }
    }

    return 0;
}
