#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

// ======================
// KELAS TOKO ELEKTRONIK
// ======================
class TokoElektronik {
private:
    array<string, 3> etalase;

public:
    // Constructor
    TokoElektronik() {
        etalase[0] = "Laptop Asus";
        etalase[1] = "Smartphone Samsung";
        etalase[2] = "Printer Epson";
    }

    // Method mengambil produk
    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range&) {
            throw string(
                "Gagal Mengambil Barang : Rak nomor " +
                to_string(nomorRak) +
                " kosong atau tidak tersedia!"
            );
        }
    }
};

// ======================
// STRUCT BARANG GUDANG
// ======================
struct Barang {
    string nama;
    int stok;
    double harga;
};

const string FILE_GUDANG = "gudang.txt";

// ======================
// LOAD DATA DARI FILE
// ======================
vector<Barang> loadData() {
    vector<Barang> daftarBarang;

    ifstream file(FILE_GUDANG);

    Barang b;
    while (file >> b.nama >> b.stok >> b.harga) {
        daftarBarang.push_back(b);
    }

    file.close();
    return daftarBarang;
}

// ======================
// SIMPAN KE FILE
// ======================
void saveData(const vector<Barang>& daftarBarang) {
    ofstream file(FILE_GUDANG);

    for (const auto& b : daftarBarang) {
        file << b.nama << " "
             << b.stok << " "
             << b.harga << endl;
    }

    file.close();
}

// ======================
// READ
// ======================
void tampilkanBarang() {
    vector<Barang> daftarBarang = loadData();

    cout << "\n===== DATA GUDANG =====\n";

    if (daftarBarang.empty()) {
        cout << "Gudang masih kosong.\n";
        return;
    }

    for (size_t i = 0; i < daftarBarang.size(); i++) {
        cout << i + 1 << ". "
             << "Nama : " << daftarBarang[i].nama
             << " | Stok : " << daftarBarang[i].stok
             << " | Harga : Rp" << daftarBarang[i].harga
             << endl;
    }
}

// ======================
// CREATE
// ======================
void tambahBarang() {
    vector<Barang> daftarBarang = loadData();

    Barang b;

    cout << "\nNama Barang : ";
    cin >> b.nama;

    cout << "Stok : ";
    cin >> b.stok;

    cout << "Harga : ";
    cin >> b.harga;

    daftarBarang.push_back(b);

    saveData(daftarBarang);

    cout << "Data berhasil ditambahkan!\n";
}

// ======================
// UPDATE
// ======================
void updateBarang() {
    vector<Barang> daftarBarang = loadData();

    if (daftarBarang.empty()) {
        cout << "Data kosong.\n";
        return;
    }

    tampilkanBarang();

    int nomor;
    cout << "\nPilih nomor barang yang ingin diubah : ";
    cin >> nomor;

    if (nomor < 1 || nomor > daftarBarang.size()) {
        cout << "Nomor tidak valid!\n";
        return;
    }

    cout << "Nama Baru : ";
    cin >> daftarBarang[nomor - 1].nama;

    cout << "Stok Baru : ";
    cin >> daftarBarang[nomor - 1].stok;

    cout << "Harga Baru : ";
    cin >> daftarBarang[nomor - 1].harga;

    saveData(daftarBarang);

    cout << "Data berhasil diperbarui!\n";
}

// ======================
// DELETE
// ======================
void hapusBarang() {
    vector<Barang> daftarBarang = loadData();

    if (daftarBarang.empty()) {
        cout << "Data kosong.\n";
        return;
    }

    tampilkanBarang();

    int nomor;
    cout << "\nPilih nomor barang yang ingin dihapus : ";
    cin >> nomor;

    if (nomor < 1 || nomor > daftarBarang.size()) {
        cout << "Nomor tidak valid!\n";
        return;
    }

    daftarBarang.erase(daftarBarang.begin() + nomor - 1);

    saveData(daftarBarang);

    cout << "Data berhasil dihapus!\n";
}

// ======================
// SIMULASI ETALASE
// ======================
void simulasiEtalase() {
    TokoElektronik toko;

    cout << "\n===== SIMULASI ETALASE =====\n";

    // Skenario 1
    try {
        cout << "\nSkenario 1 (Rak 1)\n";
        cout << "Barang : "
             << toko.ambilProduk(1)
             << endl;
    }
    catch (string pesan) {
        cout << pesan << endl;
    }

    // Skenario 2
    try {
        cout << "\nSkenario 2 (Rak 5)\n";
        cout << "Barang : "
             << toko.ambilProduk(5)
             << endl;
    }
    catch (string pesan) {
        cout << pesan << endl;
    }
}

// ======================
// MAIN
// ======================
int main() {
    int pilihan;

    do {
        cout << "\n================================";
        cout << "\n SISTEM TOKO ELEKTRONIK";
        cout << "\n================================";

        // Read otomatis saat menu dibuka
        tampilkanBarang();

        cout << "\n\nMENU";
        cout << "\n1. Tambah Barang (Create)";
        cout << "\n2. Tampilkan Barang (Read)";
        cout << "\n3. Update Barang";
        cout << "\n4. Hapus Barang (Delete)";
        cout << "\n5. Simulasi Etalase";
        cout << "\n0. Keluar";
        cout << "\nPilihan : ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tambahBarang();
            break;

        case 2:
            tampilkanBarang();
            break;

        case 3:
            updateBarang();
            break;

        case 4:
            hapusBarang();
            break;

        case 5:
            simulasiEtalase();
            break;

        case 0:
            cout << "\nTerima kasih.\n";
            break;

        default:
            cout << "\nPilihan tidak tersedia!\n";
        }

    } while (pilihan != 0);

    return 0;
}