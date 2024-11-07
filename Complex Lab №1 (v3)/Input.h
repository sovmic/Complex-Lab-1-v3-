#pragma once

#include "Header.h"

void input(VideoCards Card) {
    cout << "Вы выбрали добавление.\nВведите модель видеокарты, тип её охлаждения, количество гигабайт видеопамяти, частоту графического процессора (в мегагерцах), поддерживаемую версию DirectX\n(Пример: GTX 2060; Active; 6; 1300; 12)\n";

    ofstream inFile("File.bin", ios::binary | ios::app);
    if (inFile) {

        //Обработка ввода пользователем
        string NewCard, temp;
        cin.ignore();
        getline(cin, NewCard);
        int count = 0;
        NewCard += ";";

        for (int i = 0; i < NewCard.size(); i++) {

            if (NewCard[i] != ';') {
                temp += NewCard[i];
            }
            else {
                if (count == 0) {
                    Card.CardName = temp;
                    count++;
                    temp = "";
                }
                else if (count == 1) {
                    Card.CardCoolingType = temp;
                    count++;
                    temp = "";
                }
                else if (count == 2) {
                    Card.CapacityVRAM = stoi(temp);
                    count++;
                    temp = "";
                }
                else if (count == 3) {
                    Card.VideoMemoryFrequency = stoi(temp);
                    count++;
                    temp = "";
                }
                else if (count == 4) {
                    Card.DirectXVersion = stoi(temp);
                    count++;
                    temp = "";
                }
            }
        }

        //Запись
        size_t nameLength = Card.CardName.size();
        inFile.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        inFile.write(Card.CardName.c_str(), nameLength);

        size_t coolingTypeLength = Card.CardCoolingType.size();
        inFile.write(reinterpret_cast<char*>(&coolingTypeLength), sizeof(coolingTypeLength));
        inFile.write(Card.CardCoolingType.c_str(), coolingTypeLength);

        inFile.write(reinterpret_cast<char*>(&Card.CapacityVRAM), sizeof(Card.CapacityVRAM));
        inFile.write(reinterpret_cast<char*>(&Card.VideoMemoryFrequency), sizeof(Card.VideoMemoryFrequency));
        inFile.write(reinterpret_cast<char*>(&Card.DirectXVersion), sizeof(Card.DirectXVersion));
        inFile.close();
    }
}