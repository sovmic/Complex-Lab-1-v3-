#pragma once

#include "Header.h"

void search() {
    cout << "�� ������� ����� ������ �� �������� ��� �� ���������.\n1) ����� �� ��������\n2) ����� �� ���������\n�������� ����� ����� �� ������ ������������: ";
    int Op = -1;
    cin >> Op;
    vector<VideoCards> AllCards;
    ifstream outFile("File.bin", ios::binary | ios::in);
    if (outFile) {

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
                string attribute, value;
                cout << "������� ������� ��� ������ (model ��� cooling): ";
                cin >> attribute;
                cout << "������� �������� ��������: ";
                cin.ignore();
                getline(cin, value);
                bool found = false;
                for (const auto& card : AllCards) {
                    if ((attribute == "model" || attribute == "Model") && (card.CardName.find(value) != string::npos)) {
                        found = true;
                        cout << endl << "������� ������:" << endl << "Model: " << card.CardName << endl << "Card Cooling Type: " << card.CardCoolingType << endl << "Capacity VRAM: " << card.CapacityVRAM << endl << "Video Memory Frequency: " << card.VideoMemoryFrequency << endl << "DirectX Version: " << card.DirectXVersion << endl;
                    }
                    else if (attribute == "cooling" || attribute == "Cooling" && card.CardCoolingType.find(value) != string::npos) {
                        found = true;
                        cout << endl << "������� ������:" << endl << "Model: " << card.CardName << endl << "Card Cooling Type: " << card.CardCoolingType << endl << "Capacity VRAM: " << card.CapacityVRAM << endl << "Video Memory Frequency: " << card.VideoMemoryFrequency << endl << "DirectX Version: " << card.DirectXVersion << endl;
                    }
                }
                if (!found) {
                    cout << "������� �� �������." << endl;
                }
                break;
            }
            case 2: {
                string attribute;
                int min, max;
                cout << "������� ������� ��� ������ (vram ��� frequency): ";
                cin >> attribute;
                cout << "������� ����������� ��������: ";
                cin >> min;
                cout << "������� ������������ ��������: ";
                cin >> max;
                bool found = false;
                for (const auto& card : AllCards) {
                    if ((attribute == "vram" || attribute == "Vram") && card.CapacityVRAM >= min && card.CapacityVRAM <= max) {
                        found = true;
                        cout << endl << "������� �����: " << card.CardName << " � VRAM: " << card.CapacityVRAM << " GB" << endl;
                    }
                    else if ((attribute == "frequency" || attribute == "Frequency") && card.VideoMemoryFrequency >= min && card.VideoMemoryFrequency <= max) {
                        found = true;
                        cout << endl << "������� �����: " << card.CardName << " � �������� �����������: " << card.VideoMemoryFrequency << " MHz" << endl;
                    }
                }
                if (!found) {
                    cout << "������ �� ������� � �������� ���������." << endl;
                }
                break;
            }
            default: {
                cout << "�������� ����.\n";
            }
            }
        }
    }
}