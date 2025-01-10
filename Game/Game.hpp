#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


class Game { // Создаю класс игры
private: // Приватные поля
	time_t start_game_date; // Дата начала игры
	int attempts_count; // Кол-во попыток потраченых в игре
	std::string word; // 
    std::vector<char> user_guess; // Вектор символов, здесь сохраняться буквы, которые пользователь ввел
    bool active; // Активна ли игра
	std::string getWord() // Метод для взятия случайного слова из спика слов
    {
        srand(time(nullptr)); // Задаю seed рандому в актуальное время
        std::ifstream file; // Создаю объект чтения из файла
        file.open("words.txt"); // Открываю файл
        std::vector<std::string> lines; // Создаю вектор, для хранение строк из файла
        std::string line; // Создаю переменную в которой будет храниться строка из файла
        while (std::getline(file, line)) // Перебираю каждую строку из файла, записываю в переменную line
        {
            lines.push_back(line); // Добавляю переменную line в вектор lines, для того, что бы выбрать рандомную строку из файла
        }
        std::string chosen_line = lines[rand() % lines.size()]; // Выбираю рандомную строку из вектора, записываю в переменную chosen_line
        return decode_word(chosen_line); // Декодирую слово и возвращаю его (слово которое пользователь должен угадать)
	}

    bool checkWin() { // Метод для проверки победы
        for (char ch : word) { // Прохожусь по символам слова
            if (std::find(user_guess.begin(), user_guess.end(), ch) == user_guess.end()) // делаю поиск кокнретной буквы из слова в векторе символов пользователя 
            {
                return false; // Если в векторе символов пользователя нету хотя бы одной буквы из слова вовзращаю false
            }
        }
        return true; // Все буквы есть в векторе символов пользователя возвращаю trye
    }

    static std::string decode_word(const std::string& word) // Статический метод декодирования слова из файла
    {
        std::string result = ""; // Слово после декодировки
        for (char ch : word) // Прохожусь по символам
        {
            result += ch - 1; // Отнимаю от Ascii кода еденицу, что бы получить другую букву
        }
        return result; // Возвращаю слово
    }

    void endGame(const std::string& result) // метод конца игры
    {
        if (result == "win") // Если пользователь выиграл
        {
            std::cout << "Congratulations, you win the game!" << std::endl;
        }
        else // Если пользователь проиграл
        {
            std::cout << "You lost the game ;(" << std::endl;
        }
        // Вывожу информацию о игре
        std::cout << "Game info:\n";
        std::cout << "Game time: " << time(nullptr) - start_game_date << " seconds\n";
        std::cout << "Attempts count: " << attempts_count << "\n";
        std::cout << "Word: " << word << "\n";
        std::cout << "Used letters: ";
        for (char ch : user_guess) // Прохожусь по символам из вектора
        {
            std::cout << ch << " "; // Пишу каждый символ, которы был в символьном векторе пользователя
        }
        std::cout << std::endl;
        active = false; // Делаю игру неактивной
    }
public:
    Game() : start_game_date(0), attempts_count(0), word(""), active(0) {} // Констурктор по умолчанию
    ~Game() {} // Деструктор
    void startGame() // Метод начала игры
    {
        this->word = getWord(); // Получаю слово, присваива в переменную word
        this->attempts_count = 0; // Обнуляю кол-во попыток
        this->start_game_date = time(nullptr); // Обнуляю время начала игры
        this->active = 1; // Активирую игру
    }
    bool isGameActive() // getter метод, который дает доступ к закрытому полю и показывает статус игры
    {
        return this->active;
    }

    void showGuessProgress() const // Показываю на каком пользователь шаге
    {
        std::cout << "\nYour guess progress:\n";
        for (char ch : word) // прохожусь по символам загаданного слова
        {
            if (std::find(user_guess.begin(), user_guess.end(), ch) != user_guess.end()) // Проверка на то есть ли символ в символьном векторе пользователя
            {
                std::cout << ch << " "; // Если да, то показывает его
            }
            else 
            {
                std::cout << "_ "; // Если нет, то ставит пропуск
            }
        }
        std::cout << std::endl;
    }
    void guess(char guess_char) // Метод для угадывания слова
    {
        int max_attempts = word.length() + 6; // Вычисляю кол-во попыток, кол-во попыток зависит от длины слова

        if (std::find(user_guess.begin(), user_guess.end(), guess_char) != user_guess.end()) // Проверка, на то есть ли символ в символьном векторе пользователя
        {
            std::cout << "You already guessed this letter.\n"; // Если есть, то пишем, что это дубликат
            return;
        }

        user_guess.push_back(guess_char); // Если нет, то заносим этот символ в символьный вектор пользователя
        ++attempts_count; // Записываем, что попытка была потрачена

        if (word.find(guess_char) != std::string::npos)  // Проверка, если в слове есть символ, который ввел пользователь
        {
            std::cout << "Good guess! Attempts left: " << max_attempts - attempts_count << std::endl; // Если да, то показываем, что пользователь угада и показываем сколько попыток у него осталось
            if (checkWin())  // Проверяем победил ли пользователь
            {
                endGame("win"); // Если да то заканчиваем игру с аргументом win
            }
        }
        else 
        {
            std::cout << "Wrong guess. Attempts left: " << max_attempts - attempts_count << std::endl; // Если такой буквы нету в слове, говорим об этом пользователю и показывем сколько у него осталось попыток
            if (attempts_count >= max_attempts) // Проверка, не истратил ли пользователь все попытки
            {
                endGame("lose"); // Если да, то заканчиваем игру с аргументом lose
            }
        }
    }
};