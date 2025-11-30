#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <iostream>
#include <vector>
#include "Barang.h"
using namespace std;

// Kelas untuk mengelola operasi file I/O inventory
class FileManager {
public:
    // Muat data dari file teks
    void loadData(string file, vector<Barang>& data);
    
    // Simpan data ke file teks
    void saveData(string file, vector<Barang>& data);
    
    // Import data dari file eksternal (merge by kode)
    void importData(string fileEksternal, vector<Barang>& data);
    
    // Muat lastId dari file penyimpanan
    int loadLastId();
    
    // Simpan lastId ke file penyimpanan
    void saveLastId(int lastId);
};

#endif
