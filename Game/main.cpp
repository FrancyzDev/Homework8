#include "Game.hpp"


void printMenu() // Функция, которая выводит меню действий
{
    std::cout << "-----Menu-----" << std::endl;
    std::cout << "1. Start game" << std::endl;
    std::cout << "0. Exit" << std::endl;
}



int main() { 
    while (true) // Бесконечный цикл
    {
        printMenu(); // Выдаем меню пользователю
        int choice; // Создаем переменную для выбора поведения
        std::cin >> choice; // Запрашиваем ввод с клавиатуры
        switch (choice) // Проверяем выбор пользователя
        {
            case 1: // Если он выбрал 1 и хочет начать игру
            {
                Game game; // Создаем объект игры
                game.startGame(); // Запускаем игру
                while (game.isGameActive()) // Запускаем цикл "пока игра активна"
                {
                    game.showGuessProgress(); // Показываем прогресс игрока
                    std::cout << std::endl << "Enter letter you think issue in this word: "; // Запрашиваем символ
                    char guess_char; // создаем перемнную для хранения символа
                    std::cin >> guess_char; // Запрашиваем у пользователя ввести символ
                    game.guess(guess_char); // Проверяем есть ли такой символ в слове
                }
                break; // Что бы не перейти в другой case
            }
            case 0: // Если пользователь хочет выйти из программы
            {
                exit(0); // Выход из программы
            }
            default: // Если пользователь выбрал вариант, которого не было
            {
                std::cout << "Incorrect option" << std::endl; // Пишем пользователю, что такого варианта нету
                break;
            }
        }
    }
}

