#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <vector>
#include "Barang.h"
using namespace std;

class InventoryManager {
private:
    vector<Barang> data;
    
    int getLastId() const;

public:
    vector<Barang>& getData() {
        return data;
    }

    void tampilData();

    void tambahBarang();
    void keluarkanBarang();
    void ubahBarang();
    void hapusBarang();
};

#endif
