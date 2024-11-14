#pragma once

#include "Header.h"

void read(VideoCards Card) {
    cout << "�� ������� �������� ���� �������.\n";

    //������
    ifstream outFile("File.bin", ios::binary | ios::in);
    if (outFile) {

        int card_count = 0;
        if (outFile.peek() == ifstream::traits_type::eof()) {
            cout << "������� ���.\n";
        }
        else {
            while (true) {
                VideoCards SomeCard;

                size_t nameLength;
                if (!outFile.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength))) {
                    break;
                }
                cout << "+-----+-----------------+------------------+-------------------+--------------------+---------------------+" << endl;
                cout << "|  N  |      Model      |   Cooling type   |   Capacity VRAM   |  Memory Frequency  |   DirectX Version   |" << endl;
                cout << "+-----+-----------------+------------------+-------------------+--------------------+---------------------+" << endl;

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

                card_count++;
                cout << "|  " << setw(3) << left << card_count << "| " << setw(16) << SomeCard.CardName <<
                    "| " << setw(17) << SomeCard.CardCoolingType << "| " << setw(18) << SomeCard.CapacityVRAM << "| " << setw(19) <<
                    SomeCard.VideoMemoryFrequency << "| " << setw(20) << SomeCard.DirectXVersion << "|" << endl;
                cout << Interface << endl;
            }
        }
        outFile.close();
    }
}