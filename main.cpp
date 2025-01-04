#include "Finance.hpp"

void printMenu() {
    std::cout << "\nMenu" << std::endl;
    std::cout << "1. Add Card" << std::endl;
    std::cout << "2. Deposit to Card" << std::endl;
    std::cout << "3. Spend from Card" << std::endl;
    std::cout << "4. Generate Report" << std::endl;
    std::cout << "5. Generate Top" << std::endl;
    std::cout << "6. Save Report to File" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "Select an option: ";
}

int main() {
    Customer user;
    int choice;

    while (true) {
        printMenu();
        std::cin >> choice;
        switch (choice) {
        case 1: {
            std::string name, type;
            std::cout << "Enter card name: ";
            std::cin >> name;
            std::cout << "Enter card type (debit/credit): ";
            std::cin >> type;
            user.addCard(name, type);
            std::cout << "Card added successfully" << std::endl;
            break;
        }
        case 2: {
            std::string name;
            double value;
            std::cout << "Enter card name: ";
            std::cin >> name;
            std::cout << "Enter amount to deposit: ";
            std::cin >> value;
            user.depositToCard(name, value);
            std::cout << "Deposit successful" << std::endl;
            break;
        }
        case 3: {
            std::string name, category;
            double value;
            std::cout << "Enter card name: ";
            std::cin >> name;
            std::cout << "Enter amount to spend: ";
            std::cin >> value;
            std::cout << "Enter category: ";
            std::cin >> category;
            user.spendFromCard(name, value, category);
            std::cout << "Transaction successful" << std::endl;
            break;
        }
        case 4: {
            std::string period;
            std::cout << "Enter report period (day/week/month): ";
            std::cin >> period;
            auto report = user.generateReport(period);
            std::cout << "\nReport:\n";
            for (const auto& pair : report) {
                std::cout << pair.first << ": " << pair.second << std::endl;
            }
            break;
        }
        case 5: {
            std::string period;
            std::cout << "Enter period for top (day/week/month): ";
            std::cin >> period;
            auto top = user.generateTop(period);
            std::cout << "\nTop Expenses:\n";
            for (const auto& transaction : top) {
                std::cout << "Category: " << transaction.category << ", Value: " << transaction.value << std::endl;
            }
            break;
        }
        case 6: {
            std::string period, filename;
            std::cout << "Enter report period (day/week/month): ";
            std::cin >> period;
            std::cout << "Enter filename: ";
            std::cin >> filename;
            auto report = user.generateReport(period);
            user.saveReportToFile(report, filename);
            std::cout << "Report saved to file successfully" << std::endl;
            break;
        }
        case 7: {
            std::cout << "Exiting program" << std::endl;
            return 0;
        }
        default: {
            std::cout << "Invalid option. Please try again" << std::endl;
            break;
        }
     }
}

    return 0;
}
