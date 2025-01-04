#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <ctime>


struct Transaction
{
	std::string type; // тип транзакции либо spend либо deposit
	double value; // сумма сделки
	std::string category; // категория в которую были потрачены деньги
	time_t date; // сохранение времени, что бы можно было сделать отчет за определенное время 
};


class Card {
private:
	std::string name; // Название карты
	std::string type; // Тип карты (дебитовая/кредитная)
	double balance; // баланс на карте
	std::vector<Transaction> transactions; // Транзакции, нужны что бы генерировать отчеты
    // std::vector выбрал потому-что это очень удобный динамический массив 
    // гораздо удобней использовать готовую структуру данных чем создавать свою динамическую коллекцию
public:
    Card() : name(""), type(""), balance(0.0) {} // конструктор по умолчанию
    Card(const std::string& name, const std::string& type) : name(name), type(type), balance(0.0) {} // конструктор
    void deposit(double value) {
        balance += value; // пополняем баланс
        transactions.push_back({ "deposit", value, "", std::time(nullptr) }); // вношу пополнение баланса в массив транзакций
    }

    void spend(double value, const std::string& category) {
        if (value > balance) {
            throw std::runtime_error("Insufficient balance"); // Выкидываю исключение, если средств на балансе недостаточно
        }
        balance -= value; // Отнимаю баланс
        transactions.push_back({ "spend", value, category, std::time(nullptr) }); // вношу перевод средств в массив транзацкий, для формирования отчетов в дальнейшем
    }

    const std::vector<Transaction>& getTransactions() const {
        return transactions; // getter метод для получения вектора транзакций для генерации отчетов
    }
};


class Customer {
private:
    std::map<std::string, Card> cards; // словарь карт (ключ: значение), карты клиента
    time_t calculateDate(const std::string& period) {
        time_t now = std::time(nullptr); // Создаю объект time_t с значением акутального времени
        if (period == "day") {
            return now - 24 * 60 * 60;
        }
        else if (period == "week") {
            return now - 7 * 24 * 60 * 60;
        }
        else if (period == "month") {
            return now - 30 * 24 * 60 * 60;
        }
        else {
            throw std::invalid_argument("Invalid period"); // Кидаю исключения, о нправильно переданном аргументе
        }
    }

public:
    void addCard(const std::string& name, const std::string& cardType) {
        if (cards.find(name) != cards.end()) { // Проверка, если карта с таким именем есть, то выкидываем исключение
            throw std::runtime_error("Card already exists"); // Кидаю исключение, что карта с таким именем уже есть
        }
        cards[name] = Card(name, cardType); // Добавляю в словарь карт, карту с именем name
    }

    void depositToCard(const std::string& name, double value) {
        if (cards.find(name) == cards.end()) { // Проверка, если карты с таким именем нету выкидываю исключение
            throw std::runtime_error("Card does not exist"); // Кидаю исключение, карты с таким именем нету
        }
        cards[name].deposit(value); // Вношу депозит на карту
    }

    void spendFromCard(const std::string& name, double value, const std::string& category) {
        if (cards.find(name) == cards.end()) { // Проверка, если карты с таким именем нету выкидываю исключение
            throw std::runtime_error("Card does not exist"); // Кидаю исключение, карты с таким именем нету
        }
        cards[name].spend(value, category); // Перевожу с карты
    }

    std::map<std::string, double> generateReport(const std::string& period) {
        std::time_t startDate = calculateDate(period); // Беру дату за которую нужно сгенерировать отчет
        std::time_t now = std::time(nullptr); // Беру актуальное время
        std::map<std::string, double> report; // Создаю словарь отчета
        for (const auto& card : cards) { // Прохожусь по всем картам клиента
            const auto& transactions = card.second.getTransactions(); // Получаю список транзакций конркретной карты
            for (const auto& transaction : transactions) { // Прохожусь по транзакциям конркретной карты клиента
                if (transaction.type == "spend" && transaction.date >= startDate && transaction.date <= now) { // Проверяю транзакцию
                    report[transaction.category] += transaction.value; // Добавляю сколько денег было потраченно на категорию
                }
            }
        }
        return report; // Возврщаю отчет
    }

    std::vector<Transaction> generateTop(const std::string& period) {
        std::time_t startDate = calculateDate(period); // Беру дату за которую нужно сгенерировать отчет
        std::time_t now = std::time(nullptr); // Беру актуальное время
        std::vector<Transaction> top; // Создаю словарь топа
        for (const auto& card : cards) { // Прохожусь по всем картам клиента
            const auto& transactions = card.second.getTransactions(); // Получаю список транзакций конркретной карты
            for (const auto& transaction : transactions) { // Прохожусь по транзакциям конркретной карты клиента
                if (transaction.type == "spend" && transaction.date >= startDate && transaction.date <= now) { // Проверяю транзакцию
                    top.push_back(transaction); // Добавляю транзакцию в топ
                }
            }
        }
        std::sort(top.begin(), top.end(), [](const Transaction& a, const Transaction& b) { // сортирую вектор top по лямбда-функции
            // Использую лямбда функцию, для сортировки, сравниваю значения сум транзакций
            return a.value > b.value;
            }
        );

        if (top.size() > 3) { // Проверяю больше ли записей в топе чем 3 штуки
            top.resize(3); // Если да, то изменяю размер вектора, что бы было только 3
        }
        return top; // Возвращаю вектор топа
    }

    void saveReportToFile(const std::map<std::string, double>& report, const std::string& filename) {
        std::ofstream file(filename); // Создаю объект записи а файл
        if (!file.is_open()) { // Проверяю открыт ли файл
            throw std::runtime_error("Failed to open file"); // Кидаю исключение, если файл не открыт
        }
        for (const auto& pair : report) { // Прохожусь по отчету
            file << pair.first << ": " << pair.second << "\n"; // Добавляю записи в файл
        }
        file.close(); // Закрываю файл
    }
};
