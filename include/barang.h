#ifndef BARANG_H
#define BARANG_H

#include <string>
using namespace std;

// Model data untuk item inventory
class Barang {
private:
    int id;
    string kode;
    string nama;
    string kategori;
    int stok;

public:
    // Konstruktor default
    Barang() : id(0), stok(0) {}
    
    // Konstruktor dengan parameter
    Barang(int id, string kode, string nama, string kategori, int stok)
        : id(id), kode(kode), nama(nama), kategori(kategori), stok(stok) {}

    // Getter methods
    int getId() const { return id; }
    string getKode() const { return kode; }
    string getNama() const { return nama; }
    string getKategori() const { return kategori; }
    int getStok() const { return stok; }

    // Setter methods
    void setId(int i) { id = i; }
    void setStok(int s) { stok = s; }
    void setKode(string k) { kode = k; }
    void setNama(string n) { nama = n; }
    void setKategori(string k) { kategori = k; }
};

#endif
