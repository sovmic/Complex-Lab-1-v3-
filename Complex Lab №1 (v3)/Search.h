#pragma once

#include "Header.h"

void search() {
    cout << "Вы выбрали поиск записи по атрибуту или по диапазону.\n1) Поиск по атрибуту\n2) Поиск по диапазону\nВыберите какой поиск вы хотите использовать: ";
    int Op = -1;
    cin >> Op;
    vector<VideoCards> AllCards;
    ifstream outFile("File.bin", ios::binary | ios::in);
    if (outFile) {

        if (outFile.peek() == ifstream::traits_type::eof()) {
            cout << "Записей нет.\n";
        }
        else {
            while (true) {
                VideoCards SomeCard;

                size_t nameLength;
                if (!outFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength))) {
                    break;
                }
                char* nameBuffer = new char[nameLength + 1];
                outFile.read(nameBuffer, nameLength);
                nameBuffer[nameLength] = '\0';
                SomeCard.CardName = nameBuffer;
                delete[] nameBuffer;

                size_t coolingTypeLength;
                outFile.read(reinterpret_cast<char*>(&coolingTypeLength), sizeof(coolingTypeLength));
                char* coolingBuffer = new char[coolingTypeLength + 1];
                outFile.read(coolingBuffer, coolingTypeLength);
                coolingBuffer[coolingTypeLength] = '\0';
                SomeCard.CardCoolingType = coolingBuffer;
                delete[] coolingBuffer;

                outFile.read(reinterpret_cast<char*>(&SomeCard.CapacityVRAM), sizeof(SomeCard.CapacityVRAM));
                outFile.read(reinterpret_cast<char*>(&SomeCard.VideoMemoryFrequency), sizeof(SomeCard.VideoMemoryFrequency));
                outFile.read(reinterpret_cast<char*>(&SomeCard.DirectXVersion), sizeof(SomeCard.DirectXVersion));

                AllCards.push_back(SomeCard);
            }
            outFile.close();
            switch (Op) {
            case 1: {
                int card_count = 0;
                string attribute, value;
                cout << "Введите атрибут для поиска (model или cooling): ";
                cin >> attribute;
                cout << "Введите значение атрибута: ";
                cin.ignore();
                getline(cin, value);
                bool found = false;
                cout << "+-----+-----------------+------------------+-------------------+--------------------+---------------------+" << endl;
                cout << "|  N  |      Model      |   Cooling type   |   Capacity VRAM   |  Memory Frequency  |   DirectX Version   |" << endl;
                cout << "+-----+-----------------+------------------+-------------------+--------------------+---------------------+" << endl;

                for (const auto& card : AllCards) {
                    if ((attribute == "model" || attribute == "Model" || attribute == "m") && (card.CardName.find(value) != string::npos)) {
                        found = true;
                        card_count++;
                        cout << "|  " << setw(3) << left << card_count << "| " << setw(16) << card.CardName <<
                            "| " << setw(17) << card.CardCoolingType << "| " << setw(18) << card.CapacityVRAM << "| " << setw(19) <<
                            card.VideoMemoryFrequency << "| " << setw(20) << card.DirectXVersion << "|" << endl;
                        cout << Interface << endl;
                    }
                    else if ((attribute == "cooling" || attribute == "Cooling" || attribute == "c") && card.CardCoolingType.find(value) != string::npos) {
                        found = true;
                        card_count++;
                        cout << "|  " << setw(3) << left << card_count << "| " << setw(16) << card.CardName <<
                            "| " << setw(17) << card.CardCoolingType << "| " << setw(18) << card.CapacityVRAM << "| " << setw(19) <<
                            card.VideoMemoryFrequency << "| " << setw(20) << card.DirectXVersion << "|" << endl;
                        cout << Interface << endl;
                    }
                }
                if (!found) {
                    cout << "| " << setw(73) << "Записи не найдены в заданном диапазоне." << setw(33) << "| " << endl;
                    card_count = 0;
                }
                break;
            }
            case 2: {
                string attribute;
                int card_count = 0;
                int min, max;
                cout << "Введите атрибут для поиска (vram или frequency): ";
                cin >> attribute;
                cout << "Введите минимальное значение: ";
                cin >> min;
                cout << "Введите максимальное значение: ";
                cin >> max;
                bool found = false;
                for (const auto& card : AllCards) {
                    if ((attribute == "vram" || attribute == "Vram" || attribute == "v") && card.CapacityVRAM >= min && card.CapacityVRAM <= max) {
                        found = true;
                        card_count++;
                        cout << "|  " << setw(3) << left << card_count << "| " << setw(16) << card.CardName <<
                            "| " << setw(17) << card.CardCoolingType << "| " << setw(18) << card.CapacityVRAM << "| " << setw(19) <<
                            card.VideoMemoryFrequency << "| " << setw(20) << card.DirectXVersion << "|" << endl;
                        cout << Interface << endl;
                    }
                    else if ((attribute == "frequency" || attribute == "Frequency" || attribute == "f") && card.VideoMemoryFrequency >= min && card.VideoMemoryFrequency <= max) {
                        found = true;
                        card_count++;
                        cout << "|  " << setw(3) << left << card_count << "| " << setw(16) << card.CardName <<
                            "| " << setw(17) << card.CardCoolingType << "| " << setw(18) << card.CapacityVRAM << "| " << setw(19) <<
                            card.VideoMemoryFrequency << "| " << setw(20) << card.DirectXVersion << "|" << endl;
                        cout << Interface << endl;
                    }
                }
                if (!found) {
                    cout << "| " << setw(73) << "Записи не найдены в заданном диапазоне." << setw(33) << "| " << endl;
                    card_count = 0;
                }
                break;
            }
            default: {
                cout << "Неверный ввод.\n";
            }
            }
        }
    }
}