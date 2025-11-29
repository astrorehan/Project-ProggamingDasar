#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <iostream>
#include <vector>
#include "Barang.h"
using namespace std;

class FileManager {
public:
    void loadData(string file, vector<Barang>& data);
    void saveData(string file, vector<Barang>& data);
    void importData(string fileEksternal, vector<Barang>& data);
};

#endif
