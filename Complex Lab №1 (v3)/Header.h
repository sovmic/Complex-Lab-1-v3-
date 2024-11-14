#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

struct VideoCards {
    string CardName;
    string CardCoolingType;
    int CapacityVRAM;
    int VideoMemoryFrequency;
    int DirectXVersion;
};

string Interface(107, '-');