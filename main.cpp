// main.cpp
// Program utama - entry point aplikasi
//
// Cara compile:
// g++ main.cpp fileOperations.cpp crudOperations.cpp menuInterface.cpp -o inventory.exe
//
// Cara run:
// ./inventory.exe

#include "inventory.h"
#include <iostream>

using namespace std;

int main(){
    cout << "========================================\n";
    cout << "   SISTEM MANAJEMEN INVENTORY BARANG   \n";
    cout << "          (TEXT FILE VERSION)          \n";
    cout << "========================================\n";
    
    inventory inv;
    inv.tampil_menu();
    
    return 0;
}