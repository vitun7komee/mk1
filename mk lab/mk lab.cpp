#include <iostream>
#include <fstream>
#include <string>

class FiniteStateMachine
{
private:
    static int D[7][4]; 

   
    static int sclass(char c)
    {
        if (c == 'a') return 0;
        if (c == 'b') return 1;
        if (c == 'c') return 2;
        if (c == '-') return 3;
        return -1; // если символ не подходит
    }

    // Проверка строки
    static void checkString(const std::string& s)
    {
        int st = 0; // начальное состояние (q0)
        int i = 0;  // начальный индекс

        while (i < s.length())
        {
            int myClass = sclass(s[i]);
            if (myClass == -1)
            {
                std::cout << "Неверный символ: " << s[i] << std::endl;
                return;
            }

            std::cout << s[i] << " [" << st << " -> ";

            st = D[st][myClass];  // переход в новое состояние
            std::cout << st << "]" << std::endl;

            if (st == -1)
            {
                std::cout << "Ошибка: недопустимый переход." << std::endl;
                return;
            }

            ++i;
        }

        if (st == 1 || st == 2 || st == 3) {
            std::cout << "Строка принята." << std::endl;
        }
        else {
            std::cout << "Строка отклонена." << std::endl;
        }
    }

public:
    // Чтение строк из файла и проверка
    static void readFromFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                checkString(line);
            }
            file.close();
        }
        else
        {
            std::cout << "Не удалось открыть файл." << std::endl;
        }
    }
};

// Матрица переходов состояний для автомата (из схемы)
int FiniteStateMachine::D[7][4] = {
    // Переходы для состояний q0 - q6, символы: a, b, c, -
    {1, 2, 3, -1},  // q0
    {1, 2, 3, 5},   // q1
    {1, 2, 3, 4},   // q2
    {1, 2, 3, 6},   // q3
    {-1, -1, -1, -1}, // q4
    {1, -1, -1, -1},  // q5
    {-1, -1, -1, -1}  // q6 
};

int main()
{
    
    setlocale(LC_ALL, "Russian");

    
    FiniteStateMachine::readFromFile("input.txt");

    return 0;
}
