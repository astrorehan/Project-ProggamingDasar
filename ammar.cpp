#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

class inventory {
private:
    int id;
    char kodeBarang[50];
    char namaBarang[50];
    char kategori[50];
    int stok;

public:

    void Cekfile(fstream &data){
        data.open("inventory.bin", ios::in | ios::out | ios::binary);
        if (!data.is_open()) {
            data.open("inventory.bin", ios::trunc | ios::in | ios::out | ios::binary);
        }
    }

    int ukuranData(fstream &data){
        int akhir, total;
        data.seekg(0, ios::end);
        akhir = data.tellg();
        total = akhir / sizeof(inventory);
        return total;
    }

    void MenulisFile(fstream &data, inventory &item, int posisi){
        data.seekp((posisi - 1) * sizeof(inventory));
        data.write(reinterpret_cast<char*>(&item), sizeof(inventory));
    }

    void tambahdata(fstream &data){
        inventory itemBaru, itemLama;
        
        cout << "Kode Barang  : "; cin.getline(itemBaru.kodeBarang, 50);
        cout << "Nama Barang  : "; cin.getline(itemBaru.namaBarang, 50);
        cout << "Kategori     : "; cin.getline(itemBaru.kategori, 50);
        cout << "Stok Masuk   : "; cin >> itemBaru.stok;
        cin.ignore();

        int size = ukuranData(data);

        for (int i = 1; i <= size; i++){
            itemLama = BacaData(data, i);

            if (strcmp(itemLama.kodeBarang, itemBaru.kodeBarang) == 0 ||
                strcmp(itemLama.namaBarang, itemBaru.namaBarang) == 0)
            {
                cout << "\nBarang sudah ada. Menambahkan stok...\n";
                itemLama.stok += itemBaru.stok;  
                MenulisFile(data, itemLama, i);    
                return;
            }
        }
        int posisi = size + 1;
        itemBaru.id = posisi;

        MenulisFile(data, itemBaru, posisi);

        cout << "\nBarang baru berhasil ditambahkan!\n";
    }

    void keluarbarang(fstream &data){
        inventory itemBaru, itemLama;
        
        cout << "Kode Barang  : "; cin.getline(itemBaru.kodeBarang, 50);
        cout << "Nama Barang  : "; cin.getline(itemBaru.namaBarang, 50);
        cout << "Kategori     : "; cin.getline(itemBaru.kategori, 50);
        cout << "Stok Keluar   : "; cin >> itemBaru.stok;
        cin.ignore();

        int size = ukuranData(data);
        for (int i = 1; i <= size; i++){
            itemLama = BacaData(data, i);

            if (strcmp(itemLama.kodeBarang, itemBaru.kodeBarang) == 0 ||
                strcmp(itemLama.namaBarang, itemBaru.namaBarang) == 0)
            {
                if (itemLama.stok < itemBaru.stok){
                    cout<<"Stok kurang dari barang yang diminta";
                }
                else {
                itemLama.stok -= itemBaru.stok;
                MenulisFile(data, itemLama, i);    
                return;}
            }
        }

        int posisi = size + 1;
        itemBaru.id = posisi;

        MenulisFile(data, itemBaru, posisi);

        cout << "\nBarang baru berhasil ditambahkan!\n";
    }

    void TampilData(fstream &data){
        inventory item;
        int size = ukuranData(data);


        cout<<left<<setw(5)<<"NO"
            <<setw(5)<<"ID"
            <<setw(8)<<"KODE"
            <<setw(15)<<"NAMA"
            <<setw(15)<<"KATEGORI"
            <<setw(5)<<"STOK"<<right<<"\n";

        for (int i = 0; i < size; i++){
            data.seekg(i * sizeof(inventory));
            data.read(reinterpret_cast<char*>(&item), sizeof(inventory));
            cout<<left<<setw(5)<<i + 1
                <<setw(5)<<item.id
                <<setw(8)<<item.kodeBarang
                <<setw(15)<<item.namaBarang
                <<setw(15)<<item.kategori
                <<setw(5)<<item.stok<<right<<"\n";
        }
    }

    void UbahData(fstream &data){
        inventory item;
        int posisi;

        cout << "Ubah data nomor : ";
        cin >> posisi;
        cin.ignore();

        cout << "Kode Barang  : "; cin.getline(item.kodeBarang, 50);
        cout << "Nama Barang  : "; cin.getline(item.namaBarang, 50);
        cout << "Kategori     : "; cin.getline(item.kategori, 50);
        cout << "Stok         : "; cin >> item.stok;
        cin.ignore();

        item.id = posisi;

        MenulisFile(data, item, posisi);
    }

    inventory BacaData(fstream &data, int posisi){
        inventory item;
        data.seekg((posisi - 1) * sizeof(inventory), ios::beg);
        data.read(reinterpret_cast<char*>(&item), sizeof(inventory));
        return item;
    }

    void HapusData(fstream &data){
        fstream datatemp;
        inventory kosong{}, item;

        int hapusIndex;
        int offset = 0;

        datatemp.open("tempinv.bin", ios::in | ios::out | ios::trunc | ios::binary);

        cout << "Pilih data yang dihapus : ";
        cin >> hapusIndex;

        MenulisFile(data, kosong, hapusIndex);

        int size = ukuranData(data);

        for (int i = 1; i <= size; i++){
            item = BacaData(data, i);

            if (strlen(item.namaBarang) == 0) {
                offset++;
            } else {
                MenulisFile(datatemp, item, i - offset);
            }
        }

        int ukuranTemp = ukuranData(datatemp);

        data.close();
        data.open("inventory.bin", ios::trunc | ios::in | ios::out | ios::binary);

        for (int i = 1; i <= ukuranTemp; i++){
            item = BacaData(datatemp, i);
            MenulisFile(data, item, i);
        }
    }

    int menu(){
        int input;
        cout << "\n===== MENU INVENTORY =====\n";
        cout << "1. Barang Masuk\n";
        cout << "2. Barang Keluar\n";
        cout << "3. Tampilkan Barang\n";
        cout << "4. Ubah Barang\n";
        cout << "5. Hapus Barang\n";
        cout << "6. Selesai\n";
        cout << "Pilih menu : ";
        cin >> input;
        cin.ignore();
        return input;
    }

    void tampil_menu(){
        inventory inv;
        fstream data;
        inv.Cekfile(data);

        while (true){
            int pilih = inv.menu();
            if (pilih == 5) break;

            switch (pilih){
                case 1:
                    inv.tambahdata(data);
                    inv.TampilData(data);
                    break;
                case 2:
                    inv.keluarbarang(data);
                    inv.TampilData(data);
                    break;
                case 3:
                    inv.TampilData(data);
                    break;
                case 4:
                    inv.TampilData(data);
                    inv.UbahData(data);
                    inv.TampilData(data);
                    break;
                case 5:
                    inv.TampilData(data);
                    inv.HapusData(data);
                    inv.TampilData(data);
                    break;
                default:
                    cout << "Pilihan tidak valid!\n";
            }

            char lanjut;
            cout << "Lanjutkan? (y/n): ";
            cin >> lanjut;
            cin.ignore();

            if (lanjut == 'n' || lanjut == 'N')
                break;
        }

        cout << "Program selesai.\n";
    }
};


int main() {
    inventory inv;
    inv.tampil_menu();
    return 0;
}
