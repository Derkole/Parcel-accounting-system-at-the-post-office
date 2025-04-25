#include <iostream>                                                                        //
#include <vector>                                                                          //
#include <string>                                                                          //
#include <iomanip>                                                                         //
#include <limits>                                                                          //

struct package                                                                             // Структура для хранения информации о посылке
{
    int recipient_ID;
    std::string recipient_name;
    bool recipient_delivery;
};

std::vector<package> packages;                                                             // Глобальный вектор для хранения всех посылок

void menu()                                                                                // Функция меню
{
    std::cout << "=============================\n";
    std::cout << "       МЕНЮ ПОСЫЛОК       \n";
    std::cout << "=============================\n";

    std::cout << "1️⃣  Добавить посылку\n";                                // Пункт меню 1
    std::cout << "2️⃣  Найти посылку по ID посылки\n";                     // Пункт меню 2
    std::cout << "3️⃣  Изменить статус посылки\n";                  // Пункт меню 3
    std::cout << "4️⃣  Показать все посылки\n";                 // Пункт меню 4
    std::cout << "5️⃣  Выход\n";// Пункт меню 6
}

void add_a_parcel()                                                                        // Функция добавления посылки
{
    package new_package;

    std::cout << "Введите ID посылки: ";
    while (!(std::cin >> new_package.recipient_ID))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "----Ошибка статуса----" << '\n';
        std::cout << "Пожалуйста, введите числовой ID: " << '\n';
    }

    std::cout << "Введите имя пользователя: ";
    std::cin.ignore();
    std::getline(std::cin, new_package.recipient_name);

    int delivery_status;
    std::cout << "Утвердите статус доставки до пользователя(1 - да, 0 - нет): ";
    while (!(std::cin >> delivery_status) || (delivery_status != 0 && delivery_status != 1))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "----Ошибка статуса----" << '\n';
        std::cout << "Пожалуйста, введите 1, если посылка доставлена, или 0, если она ещё не доставлена: " << '\n';
    }

    new_package.recipient_delivery = (delivery_status == 1);

    packages.push_back(new_package);
    std::cout << "Посылка с ID" << new_package.recipient_ID << " успешно добавлена!\n";
}

void find_a_parcel()                                                                       // Функция поиска посылки
{
    if (packages.empty()) 
    {
        std::cout << "----Информация----\n";
        std::cout << "Список посылок пуст!\n\n";
        return;
    }

    std::cout << "Введите ID посылки для изменения статуса: ";
    int search_ID{};
    while (!(std::cin >> search_ID))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "----Ошибка статуса----" << '\n';
        std::cout << "Пожалуйста, введите числовой ID: " << '\n';
    }

    bool found{false};
    for (const auto& parcel : packages)
    {
        if (parcel.recipient_ID == search_ID)
        {
            std::cout << "\nНайдена посылка:\n"
            << "ID: " << parcel.recipient_ID << "\n"
            << "Получатель: " << parcel.recipient_name << "\n"
            << "Статус: " << (parcel.recipient_delivery ? "Доставлена" : "Не доставлена") << "\n\n";
            found = true;
            break;
        }
    }

    if (!found) 
    {
        std::cout << "Посылка с ID " << search_ID << " не найдена.\n\n";
    }
}

void mark_a_parcel()                                                                       // Функция отметки доставки
{
    if (packages.empty()) 
    {
        std::cout << "----Информация----\n";
        std::cout << "Список посылок пуст!\n\n";
        return;
    }

    std::cout << "Для изменения статуса Введите ID посылки: ";
    int search_ID;
    while (!(std::cin >> search_ID))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "----Ошибка ввода----\n";
        std::cout << "Пожалуйста, введите числовой ID: ";
    }

    bool found = false;
    for (auto& parcel : packages)
    {
        if (parcel.recipient_ID == search_ID) 
        {
            found = true;
            std::cout << "\nТекущий статус посылки:\n"
                      << "ID: " << parcel.recipient_ID << "\n"
                      << "Получатель: " << parcel.recipient_name << "\n"
                      << "Статус: " << (parcel.recipient_delivery ? "Доставлена" : "Не доставлена") << "\n\n";

            std::cout << "Изменить статус доставки? (1 - да, 0 - нет): ";
            int change_choice;
            while (!(std::cin >> change_choice) || (change_choice != 0 && change_choice != 1))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "----Ошибка ввода----\n";
                std::cout << "Пожалуйста, введите 1 или 0: ";
            }

            if (change_choice == 1) 
            {
                parcel.recipient_delivery = !parcel.recipient_delivery;  // Инвертируем статус
                std::cout << "Новый статус: " << (parcel.recipient_delivery ? "Доставлена" : "Не доставлена") << "\n\n";
            }
            else 
            {
                std::cout << "Статус не изменён.\n\n";
            }
            break;
        }
    }

    if (!found) 
    {
        std::cout << "----Ошибка----\n";
        std::cout << "Посылка с ID " << search_ID << " не найдена.\n\n";
    }
}

void show_packages()                                                                       // Функция показа всех посылок
{
    if (packages.empty()) 
    {
        std::cout << "----Информация----\n";
        std::cout << "Список посылок пуст!\n\n";
        return;
    }

    std::cout << "===================================\n";
    std::cout << "        СПИСОК ВСЕХ ПОСЫЛОК        \n";
    std::cout << "===================================\n";

    // Заголовок таблицы
    std::cout << std::left 
              << std::setw(10) << "ID" 
              << std::setw(25) << "Получатель" 
              << std::setw(15) << "Статус" 
              << "\n";
    std::cout << "-----------------------------------\n";

    // Вывод всех посылок
    for (const auto& parcel : packages) 
    {
        std::cout << std::left 
                  << std::setw(10) << parcel.recipient_ID 
                  << std::setw(25) << parcel.recipient_name 
                  << std::setw(15) << (parcel.recipient_delivery ? "Доставлена" : "Не доставлена") 
                  << "\n";
    }

    std::cout << "===================================\n\n";
}
                                                          // Функция показа недославленных посылок
void exiting_the_program()                                                                 // Функция выхода из программы
{
    std::cout << "=============================\n";
    std::cout << "  Благодарим за использование!\n";
    std::cout << "=============================\n";
}

int main()                                                                                 // Основная функция
{
    int choice{0};                                                                                 // Переменная для выбора пункта меню

    while (choice != 5)                                                                       // Главный цикл программы
    {
        menu();                                                                                    // Вывод меню
        
        if (!(std::cin >> choice))                                                            // Проверка корректности ввода
        {
            std::cin.clear();                                                                      // Сброс флагов ошибок
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');                    // Очистка буфера
            std::cout << "Ошибка ввода. Пожалуйста, введите число.\n";                             // Сообщение об ошибке
            continue;                                                                              // Переход к следующей итерации
        }

        switch (choice)                                                                      // Обработка выбора пользователя
        {
            case 1: add_a_parcel(); break;                                                         // Вызов функции добавления
            case 2: find_a_parcel(); break;                                                        // Вызов функции поиска
            case 3: mark_a_parcel(); break;                                                        // Вызов функции отметки
            case 4: show_packages(); break;                                                        // Вызов функции показа всех
            case 5: exiting_the_program(); break;                                            // Вызов функции показа недосланных                                                 // Вызов функции выхода
            default: std::cout << "Неверный выбор. Попробуйте снова.\n";                           // Неверный ввод
        }
    }
    return 0;                                                                                 // Завершение программы
}