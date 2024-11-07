#pragma once

#include "Header.h"

void read(VideoCards Card) {
    cout << "Вы выбрали просмотр всех записей.\n";

    //Чтение
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

                cout << endl << "Model: " << SomeCard.CardName << endl << "Card Cooling Type: " << SomeCard.CardCoolingType << endl << "Capacity VRAM: " << SomeCard.CapacityVRAM << " GB" << endl << "Video Memory Frequency: " << SomeCard.VideoMemoryFrequency << " MHz" << endl << "DirectX Version: " << SomeCard.DirectXVersion << endl;
            }
        }
        outFile.close();
    }
}