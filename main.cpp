// main.cpp
// Program utama - hanya memanggil tampil_menu()
// 
// Cara compile:
// g++ main.cpp inventory.cpp -o inventory.exe
//
// Cara run:
// ./inventory.exe

#include "inventory.h"
#include <iostream>

using namespace std;

int main(){
    cout << "========================================\n";
    cout << "   SISTEM MANAJEMEN INVENTORY BARANG   \n";
    cout << "========================================\n";
    
    inventory inv;
    inv.tampil_menu();
    
    return 0;
}