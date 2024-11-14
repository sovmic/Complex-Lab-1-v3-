#include "Read.h"
#include "Search.h"
#include "Input.h"

int main() {
    setlocale(LC_ALL, "RUSSIAN");

    VideoCards Card;

    int UserInput = -1;
    int Status = 1;
    
    cout << Interface << endl << "Приветствуем! Перед вами каталог видеокарт. Вы можете:\n1) Добавить запись;\n2) Просмотреть все записи;\n3) Поиск записи по атрибуту;\n4) Выход;\n";

    while (Status == 1) {
        cout << Interface << endl << "Введите номер операции которую хотите совершить: ";
        cin >> UserInput;
        switch (UserInput) {
        case 1: {
            input(Card);
            UserInput = -1;
            break;
        }
        case 2: {
            read(Card);
            UserInput = -1;
            break;
        }
        case 3: {
            search();
            UserInput = -1;
            break;
        }
        case 4: {
            cout << "Выход из программы.\n";
            Status = 0;
            break;
        }
        default: {
            cout << "Неверный ввод.\n";
            UserInput = -1;
        }
        }
    }
}