#include <iostream>
#include "MenuUI.h"
using namespace std;

void MenuUI::tampilMenu() {
    cout << "\n=== MENU INVENTORY ===\n";
    cout << "1. Tampilkan Data\n";
    cout << "2. Tambah Barang\n";
    cout << "3. Barang Keluar\n";
    cout << "4. Ubah Barang\n";
    cout << "5. Hapus Barang\n";
    cout << "6. Save Data\n";
    cout << "7. Import Data\n";
    cout << "8. Exit\n";
    cout << "Pilih: ";
}

void MenuUI::jalankan() {
    int pilih;
    filemgr.loadData("data/inventory.txt", manager.getData());

    while (true) {
        tampilMenu();
        cin >> pilih;
        cin.ignore();  // Clear newline from input buffer

        switch (pilih) {
        case 1: manager.tampilData(); break;
        case 2: manager.tambahBarang(); break;
        case 3: manager.keluarkanBarang(); break;
        case 4: manager.ubahBarang(); break;
        case 5: manager.hapusBarang(); break;
        case 6: filemgr.saveData("data/inventory.txt", manager.getData()); break;
        case 7: filemgr.importData("data/import.txt", manager.getData()); break;
        case 8: return;
        }
    }
}
