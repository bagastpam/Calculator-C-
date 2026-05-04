/*
================================================================
PROGRAM: CALCULATOR PRO++ (FULL SCIENTIFIC CALCULATOR)
AUTHOR: [Your Name]
DESCRIPTION: Kalkulator ilmiah lengkap dengan berbagai fungsi
             matematika, history, dan export file
================================================================
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cstdlib>

using namespace std;

// ================== STRUCTURE ==================
/*
STRUKTUR HISTORY
Fungsi: Menyimpan struktur data untuk riwayat perhitungan
*/
struct History {
    string deskripsi; // Menyimpan deskripsi perhitungan
};

// ================== FUNGSI OPERASI DASAR ==================
/*
FUNGSI: calculate
INPUT: a,b (angka), op (operator), valid (referensi bool)
OUTPUT: hasil perhitungan
DESKRIPSI: Melakukan operasi matematika dasar (+, -, *, /, ^)
*/
double calculate(double a, double b, string op, bool &valid) {
    valid = true; // Asumsikan operasi valid
    
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    
    if (op == "/") {
        if (b == 0) {
            cout << "Error: Tidak bisa bagi dengan 0!" << endl;
            valid = false;
            return 0;
        }
        return a / b;
    }
    
    if (op == "^") return pow(a, b);
    
    valid = false; // Operator tidak dikenal
    return 0;
}

// ================== FUNGSI VALIDASI INPUT ==================
/*
FUNGSI: getValidNumber
INPUT: prompt (string pertanyaan)
OUTPUT: angka yang valid (double)
DESKRIPSI: Memastikan user memasukkan angka, bukan huruf
*/
double getValidNumber(string prompt) {
    double value;
    cout << prompt;
    
    while (!(cin >> value)) {
        cin.clear(); // Hapus error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Buang input salah
        cout << "Input tidak valid! Masukkan angka: ";
    }
    
    return value;
}

/*
FUNGSI: getValidString
INPUT: prompt (string pertanyaan)
OUTPUT: string input user
DESKRIPSI: Mengambil input string dari user
*/
string getValidString(string prompt) {
    string value;
    cout << prompt;
    cin >> value;
    return value;
}

/*
FUNGSI: getValidMenu
INPUT: min, max (batasan menu)
OUTPUT: pilihan menu yang valid
DESKRIPSI: Memastikan user memilih menu dalam range yang benar
*/
int getValidMenu(int min, int max) {
    int pilihan;
    while (true) {
        cout << "Pilih (" << min << "-" << max << "): ";
        if (cin >> pilihan && pilihan >= min && pilihan <= max) {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid! Masukkan angka " << min << " sampai " << max << endl;
    }
    return pilihan;
}

// ================== FUNGSI FAKTORIAL ==================
/*
FUNGSI: faktorial
INPUT: n (double)
OUTPUT: hasil faktorial (long long)
DESKRIPSI: Menghitung n! (faktorial) untuk bilangan bulat positif
*/
long long faktorial(double n) {
    if (n < 0 || n != (int)n) {
        cout << "Error: Faktorial hanya untuk bilangan bulat positif!" << endl;
        return -1;
    }
    
    int num = (int)n;
    long long hasil = 1;
    
    for (int i = 1; i <= num; i++) {
        hasil *= i;
    }
    
    return hasil;
}

// ================== FUNGSI KONVERSI ANGKA ==================
/*
FUNGSI: konversiDerajatKeRadian
INPUT: derajat (double)
OUTPUT: radian (double)
DESKRIPSI: Mengubah derajat ke radian
*/
double konversiDerajatKeRadian(double derajat) {
    return derajat * M_PI / 180.0;
}

/*
FUNGSI: konversiRadianKeDerajat
INPUT: radian (double)
OUTPUT: derajat (double)
DESKRIPSI: Mengubah radian ke derajat
*/
double konversiRadianKeDerajat(double radian) {
    return radian * 180.0 / M_PI;
}

// ================== FUNGSI TRIGONOMETRI LENGKAP ==================
/*
FUNGSI: prosesTrigonometriDasar
INPUT: menu (sin/cos/tan), angka (double)
OUTPUT: -
DESKRIPSI: Menghitung sin, cos, tan dengan output degree dan radian
*/
void prosesTrigonometriDasar(string menu, double angka) {
    double hasilDegree, hasilRadian;
    bool valid = true;
    
    if (menu == "sin") {
        hasilDegree = sin(konversiDerajatKeRadian(angka));
        hasilRadian = sin(angka);
        cout << "Hasil sin(" << angka << "°) = " << hasilDegree << endl;
        cout << "Hasil sin(" << angka << " rad) = " << hasilRadian << endl;
    }
    else if (menu == "cos") {
        hasilDegree = cos(konversiDerajatKeRadian(angka));
        hasilRadian = cos(angka);
        cout << "Hasil cos(" << angka << "°) = " << hasilDegree << endl;
        cout << "Hasil cos(" << angka << " rad) = " << hasilRadian << endl;
    }
    else if (menu == "tan") {
        hasilDegree = tan(konversiDerajatKeRadian(angka));
        hasilRadian = tan(angka);
        cout << "Hasil tan(" << angka << "°) = " << hasilDegree << endl;
        cout << "Hasil tan(" << angka << " rad) = " << hasilRadian << endl;
    }
    else {
        valid = false;
    }
}

/*
FUNGSI: prosesTrigonometriInvers
INPUT: menu (asin/acos/atan), angka (double)
OUTPUT: -
DESKRIPSI: Menghitung arcsin, arccos, arctan
*/
void prosesTrigonometriInvers(string menu, double angka) {
    if (menu == "asin") {
        if (angka < -1 || angka > 1) {
            cout << "Error: asin hanya untuk nilai -1 sampai 1!" << endl;
            return;
        }
        double hasilRad = asin(angka);
        double hasilDeg = konversiRadianKeDerajat(hasilRad);
        cout << "Hasil asin(" << angka << ") = " << hasilDeg << "° atau " << hasilRad << " rad" << endl;
    }
    else if (menu == "acos") {
        if (angka < -1 || angka > 1) {
            cout << "Error: acos hanya untuk nilai -1 sampai 1!" << endl;
            return;
        }
        double hasilRad = acos(angka);
        double hasilDeg = konversiRadianKeDerajat(hasilRad);
        cout << "Hasil acos(" << angka << ") = " << hasilDeg << "° atau " << hasilRad << " rad" << endl;
    }
    else if (menu == "atan") {
        double hasilRad = atan(angka);
        double hasilDeg = konversiRadianKeDerajat(hasilRad);
        cout << "Hasil atan(" << angka << ") = " << hasilDeg << "° atau " << hasilRad << " rad" << endl;
    }
}

/*
FUNGSI: prosesHiperbolik
INPUT: menu (sinh/cosh/tanh), angka (double)
OUTPUT: -
DESKRIPSI: Menghitung sinh, cosh, tanh (hiperbolik)
*/
void prosesHiperbolik(string menu, double angka) {
    if (menu == "sinh") {
        double hasil = sinh(angka);
        cout << "Hasil sinh(" << angka << ") = " << hasil << endl;
    }
    else if (menu == "cosh") {
        double hasil = cosh(angka);
        cout << "Hasil cosh(" << angka << ") = " << hasil << endl;
    }
    else if (menu == "tanh") {
        double hasil = tanh(angka);
        cout << "Hasil tanh(" << angka << ") = " << hasil << endl;
    }
}

// ================== FUNGSI LOGARITMA ==================
/*
FUNGSI: prosesLogaritma
INPUT: menu (log/ln), angka (double)
OUTPUT: -
DESKRIPSI: Menghitung log10 (basis 10) dan ln (basis e)
*/
void prosesLogaritma(string menu, double angka) {
    if (angka <= 0) {
        cout << "Error: Logaritma hanya untuk angka > 0!" << endl;
        return;
    }
    
    if (menu == "log") {
        double hasil = log10(angka);
        cout << "Hasil log10(" << angka << ") = " << hasil << endl;
    }
    else if (menu == "ln") {
        double hasil = log(angka);
        cout << "Hasil ln(" << angka << ") = " << hasil << endl;
    }
}

// ================== FUNGSI AKAR & PANGKAT ==================
/*
FUNGSI: prosesAkarPangkat
INPUT: menu (sqrt/cbrt/pangkat2/pangkat3), angka (double)
OUTPUT: -
DESKRIPSI: Menghitung akar kuadrat, akar pangkat 3, kuadrat, pangkat 3
*/
void prosesAkarPangkat(string menu, double angka) {
    if (menu == "sqrt") {
        if (angka < 0) {
            cout << "Error: Akar kuadrat tidak untuk angka negatif!" << endl;
            return;
        }
        double hasil = sqrt(angka);
        cout << "Hasil sqrt(" << angka << ") = " << hasil << endl;
        cout << "atau v" << angka << " = " << hasil << endl;
    }
    else if (menu == "cbrt") {
        double hasil = cbrt(angka);
        cout << "Hasil cbrt(" << angka << ") = " << hasil << endl;
        cout << "atau ?" << angka << " = " << hasil << endl;
    }
    else if (menu == "pangkat2" || menu == "^2") {
        double hasil = angka * angka;
        cout << "Hasil " << angka << "^2 = " << hasil << endl;
        cout << "atau " << angka << "² = " << hasil << endl;
    }
    else if (menu == "pangkat3" || menu == "^3") {
        double hasil = angka * angka * angka;
        cout << "Hasil " << angka << "^3 = " << hasil << endl;
        cout << "atau " << angka << "³ = " << hasil << endl;
    }
}

// ================== FUNGSI PEMBULATAN ==================
/*
FUNGSI: prosesPembulatan
INPUT: menu (ceil/floor/round), angka (double)
OUTPUT: -
DESKRIPSI: Membulatkan angka ke atas (ceil), bawah (floor), atau terdekat (round)
*/
void prosesPembulatan(string menu, double angka) {
    if (menu == "ceil") {
        double hasil = ceil(angka);
        cout << "Hasil ceil(" << angka << ") = " << hasil << endl;
    }
    else if (menu == "floor") {
        double hasil = floor(angka);
        cout << "Hasil floor(" << angka << ") = " << hasil << endl;
    }
    else if (menu == "round") {
        double hasil = round(angka);
        cout << "Hasil round(" << angka << ") = " << hasil << endl;
    }
}

// ================== FUNGSI LAINNYA ==================
/*
FUNGSI: prosesFungsiLain
INPUT: menu (abs/exp/persen), angka (double)
OUTPUT: -
DESKRIPSI: Nilai mutlak, eksponensial, persentase
*/
void prosesFungsiLain(string menu, double angka) {
    if (menu == "abs") {
        double hasil = fabs(angka);
        cout << "Hasil |" << angka << "| = " << hasil << endl;
    }
    else if (menu == "exp") {
        double hasil = exp(angka);
        cout << "Hasil e^" << angka << " = " << hasil << endl;
    }
    else if (menu == "persen") {
        cout << "Hasil " << angka << "% = " << angka / 100.0 << endl;
    }
}

// ================== FUNGSI KONSTANTA ==================
/*
FUNGSI: tampilkanKonstanta
INPUT: menu (pi/e)
OUTPUT: -
DESKRIPSI: Menampilkan nilai konstanta matematika
*/
void tampilkanKonstanta(string menu) {
    cout << fixed << setprecision(15);
    
    if (menu == "pi" || menu == "p") {
        cout << "Nilai p (PI) = " << M_PI << endl;
    }
    else if (menu == "e") {
        cout << "Nilai e (Euler) = " << M_E << endl;
    }
    else {
        cout << "Konstanta tidak dikenal! Gunakan: pi, p, atau e" << endl;
    }
}

// ================== FUNGSI HISTORY ==================
/*
FUNGSI: saveHistory
INPUT: histories (vector reference)
OUTPUT: -
DESKRIPSI: Menyimpan history ke file history.txt
*/
void saveHistory(const vector<History> &histories) {
    ofstream file("history.txt");
    
    if (!file) {
        cout << "Peringatan: Tidak dapat menyimpan file history!" << endl;
        return;
    }
    
    for (size_t i = 0; i < histories.size(); i++) {
        file << histories[i].deskripsi << endl;
    }
    
    file.close();
}

/*
FUNGSI: loadHistory
INPUT: histories (vector reference)
OUTPUT: -
DESKRIPSI: Memuat history dari file history.txt
*/
void loadHistory(vector<History> &histories) {
    ifstream file("history.txt");
    
    if (!file) return;
    
    string line;
    while (getline(file, line)) {
        histories.push_back({line});
    }
    
    file.close();
}

/*
FUNGSI: exportHistoryToFile
INPUT: histories (vector reference)
OUTPUT: -
DESKRIPSI: Mengekspor history ke file yang ditentukan user (backup)
*/
void exportHistoryToFile(const vector<History> &histories) {
    string filename;
    cout << "Masukkan nama file backup (contoh: backup.txt): ";
    cin >> filename;
    
    ofstream file(filename.c_str());
    
    if (!file) {
        cout << "Error: Tidak dapat membuat file backup!" << endl;
        return;
    }
    
    // Header file backup
    file << "========================================" << endl;
    file << "   BACKUP HISTORY CALCULATOR PRO++" << endl;
    file << "   Tanggal: " << __DATE__ << " " << __TIME__ << endl;
    file << "========================================" << endl;
    file << endl;
    
    // Isi history
    for (size_t i = 0; i < histories.size(); i++) {
        file << i + 1 << ". " << histories[i].deskripsi << endl;
    }
    
    file << endl;
    file << "Total: " << histories.size() << " riwayat perhitungan" << endl;
    file << "========================================" << endl;
    
    file.close();
    cout << "? History berhasil diekspor ke " << filename << endl;
}

/*
FUNGSI: hapusHistory
INPUT: histories (vector reference)
OUTPUT: -
DESKRIPSI: Menghapus semua history dengan konfirmasi
*/
void hapusHistory(vector<History> &histories) {
    char confirm;
    cout << "??  Apakah Anda yakin ingin menghapus SEMUA history? (y/n): ";
    cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        histories.clear();
        saveHistory(histories);
        cout << "? History berhasil dihapus!" << endl;
    } else {
        cout << "? Penghapusan dibatalkan." << endl;
    }
}

/*
FUNGSI: tampilkanHistory
INPUT: histories (vector reference)
OUTPUT: -
DESKRIPSI: Menampilkan semua riwayat perhitungan
*/
void tampilkanHistory(const vector<History> &histories) {
    cout << "\n=== HISTORY PERHITUNGAN ===" << endl;
    
    if (histories.empty()) {
        cout << "?? History kosong. Belum ada perhitungan." << endl;
        return;
    }
    
    cout << "?? Total " << histories.size() << " riwayat perhitungan:" << endl;
    cout << "----------------------------------------" << endl;
    
    for (size_t i = 0; i < histories.size(); i++) {
        cout << i + 1 << ". " << histories[i].deskripsi << endl;
    }
    
    cout << "----------------------------------------" << endl;
}

// ================== FUNGSI TAMPILAN MENU ==================
/*
FUNGSI: tampilkanMenuUtama
INPUT: -
OUTPUT: -
DESKRIPSI: Menampilkan menu utama kalkulator
*/
void tampilkanMenuUtama() {
    cout << "\n========================================" << endl;
    cout << "     CALCULATOR PRO++ (SCIENTIFIC)     " << endl;
    cout << "========================================" << endl;
    cout << " 1. Operasi Dasar (+, -, *, /, ^)      " << endl;
    cout << " 2. Trigonometri (sin, cos, tan)       " << endl;
    cout << " 3. Trigonometri Invers (asin, acos)   " << endl;
    cout << " 4. Hiperbolik (sinh, cosh, tanh)      " << endl;
    cout << " 5. Logaritma (log10, ln)              " << endl;
    cout << " 6. Akar & Pangkat (sqrt, cbrt, ^2, ^3)" << endl;
    cout << " 7. Pembulatan (ceil, floor, round)    " << endl;
    cout << " 8. Fungsi Lain (abs, exp, faktorial)  " << endl;
    cout << " 9. Konstanta (pi, e)                  " << endl;
    cout << "10. Lihat History                      " << endl;
    cout << "11. Hapus History                      " << endl;
    cout << "12. Export History ke File             " << endl;
    cout << "13. Keluar                             " << endl;
    cout << "========================================" << endl;
}

// ================== FUNGSI UTAMA ==================
/*
FUNGSI: main
INPUT: -
OUTPUT: int (status program)
DESKRIPSI: Fungsi utama program kalkulator
*/
int main() {
    vector<History> histories;  // Menyimpan riwayat perhitungan
    int pilihan;                // Menyimpan pilihan menu
    
    // Load history dari file saat program dimulai
    loadHistory(histories);
    
    // Setting format output
    cout << fixed << setprecision(8);
    
    // Tampilan selamat datang
    cout << "\n==========================================" << endl;
    cout << "   SELAMAT DATANG DI CALCULATOR PRO++   " << endl;
    cout << "   Kalkulator Ilmiah Lengkap            " << endl;
    cout << "==========================================" << endl;
    
    // Loop utama program
    do {
        tampilkanMenuUtama();
        pilihan = getValidMenu(1, 13);
        
        // ========== MENU 1: OPERASI DASAR ==========
        if (pilihan == 1) {
            double a, b, hasil;
            string op;
            bool valid;
            
            cout << "\n--- OPERASI DASAR ---" << endl;
            a = getValidNumber("Angka pertama : ");
            op = getValidString("Operator (+, -, *, /, ^): ");
            b = getValidNumber("Angka kedua   : ");
            
            hasil = calculate(a, b, op, valid);
            
            if (valid) {
                string record = to_string(a) + " " + op + " " + to_string(b) + " = " + to_string(hasil);
                cout << "\n? Hasil: " << hasil << endl;
                histories.push_back({record});
                saveHistory(histories);
            }
        }
        
        // ========== MENU 2: TRIGONOMETRI DASAR ==========
        else if (pilihan == 2) {
            string menu;
            double angka;
            
            cout << "\n--- FUNGSI TRIGONOMETRI ---" << endl;
            cout << "Fungsi: sin, cos, tan" << endl;
            menu = getValidString("Pilih fungsi: ");
            
            if (menu == "sin" || menu == "cos" || menu == "tan") {
                angka = getValidNumber("Masukkan angka (dalam derajat): ");
                prosesTrigonometriDasar(menu, angka);
                
                string record = menu + "(" + to_string(angka) + "°) = " + 
                               to_string(sin(konversiDerajatKeRadian(angka)));
                histories.push_back({record});
                saveHistory(histories);
            } else {
                cout << "? Fungsi tidak dikenal!" << endl;
            }
        }
        
        // ========== MENU 3: TRIGONOMETRI INVERS ==========
        else if (pilihan == 3) {
            string menu;
            double angka;
            
            cout << "\n--- FUNGSI TRIGONOMETRI INVERS ---" << endl;
            cout << "Fungsi: asin, acos, atan" << endl;
            menu = getValidString("Pilih fungsi: ");
            
            if (menu == "asin" || menu == "acos" || menu == "atan") {
                angka = getValidNumber("Masukkan angka: ");
                prosesTrigonometriInvers(menu, angka);
                
                string record = menu + "(" + to_string(angka) + ") = " + 
                               to_string(konversiRadianKeDerajat(asin(angka))) + "°";
                histories.push_back({record});
                saveHistory(histories);
            } else {
                cout << "? Fungsi tidak dikenal!" << endl;
            }
        }
        
        // ========== MENU 4: FUNGSI HIPERBOLIK ==========
        else if (pilihan == 4) {
            string menu;
            double angka;
            
            cout << "\n--- FUNGSI HIPERBOLIK ---" << endl;
            cout << "Fungsi: sinh, cosh, tanh" << endl;
            menu = getValidString("Pilih fungsi: ");
            
            if (menu == "sinh" || menu == "cosh" || menu == "tanh") {
                angka = getValidNumber("Masukkan angka: ");
                prosesHiperbolik(menu, angka);
                
                string record = menu + "(" + to_string(angka) + ") = " + 
                               to_string(sinh(angka));
                histories.push_back({record});
                saveHistory(histories);
            } else {
                cout << "? Fungsi tidak dikenal!" << endl;
            }
        }
        
        // ========== MENU 5: LOGARITMA ==========
        else if (pilihan == 5) {
            string menu;
            double angka;
            
            cout << "\n--- FUNGSI LOGARITMA ---" << endl;
            cout << "Fungsi: log (log10), ln (log natural)" << endl;
            menu = getValidString("Pilih fungsi: ");
            
            if (menu == "log" || menu == "ln") {
                angka = getValidNumber("Masukkan angka (>0): ");
                prosesLogaritma(menu, angka);
                
                string record = menu + "(" + to_string(angka) + ") = " + 
                               to_string(log10(angka));
                histories.push_back({record});
                saveHistory(histories);
            } else {
                cout << "? Fungsi tidak dikenal!" << endl;
            }
        }
        
        // ========== MENU 6: AKAR & PANGKAT ==========
        else if (pilihan == 6) {
            string menu;
            double angka;
            
            cout << "\n--- AKAR & PANGKAT ---" << endl;
            cout << "Fungsi: sqrt (v), cbrt (?), pangkat2 (^2), pangkat3 (^2)" << endl;
            menu = getValidString("Pilih fungsi: ");
            
            if (menu == "sqrt" || menu == "cbrt" || menu == "pangkat2" || menu == "pangkat3") {
                angka = getValidNumber("Masukkan angka: ");
                prosesAkarPangkat(menu, angka);
                
                string record = menu + "(" + to_string(angka) + ") = " + 
                               to_string(sqrt(angka));
                histories.push_back({record});
                saveHistory(histories);
            } else {
                cout << "? Fungsi tidak dikenal!" << endl;
            }
        }
        
        // ========== MENU 7: PEMBULATAN ==========
        else if (pilihan == 7) {
            string menu;
            double angka;
            
            cout << "\n--- FUNGSI PEMBULATAN ---" << endl;
            cout << "Fungsi: ceil, floor, round" << endl;
            menu = getValidString("Pilih fungsi: ");
            
            if (menu == "ceil" || menu == "floor" || menu == "round") {
                angka = getValidNumber("Masukkan angka: ");
                prosesPembulatan(menu, angka);
                
                string record = menu + "(" + to_string(angka) + ") = " + 
                               to_string(ceil(angka));
                histories.push_back({record});
                saveHistory(histories);
            } else {
                cout << "? Fungsi tidak dikenal!" << endl;
            }
        }
        
        // ========== MENU 8: FUNGSI LAIN ==========
        else if (pilihan == 8) {
            string menu;
            double angka;
            
            cout << "\n--- FUNGSI LAINNYA ---" << endl;
            cout << "Fungsi: abs, exp, faktorial" << endl;
            menu = getValidString("Pilih fungsi: ");
            
            if (menu == "abs" || menu == "exp") {
                angka = getValidNumber("Masukkan angka: ");
                prosesFungsiLain(menu, angka);
                
                string record = menu + "(" + to_string(angka) + ") = " + 
                               to_string(fabs(angka));
                histories.push_back({record});
                saveHistory(histories);
            }
            else if (menu == "faktorial" || menu == "fact") {
                angka = getValidNumber("Masukkan bilangan bulat positif: ");
                long long hasil = faktorial(angka);
                
                if (hasil != -1) {
                    cout << "Hasil " << angka << "! = " << hasil << endl;
                    string record = "faktorial(" + to_string(angka) + ") = " + to_string(hasil);
                    histories.push_back({record});
                    saveHistory(histories);
                }
            }
            else {
                cout << "? Fungsi tidak dikenal!" << endl;
            }
        }
        
        // ========== MENU 9: KONSTANTA ==========
        else if (pilihan == 9) {
            string menu;
            
            cout << "\n--- KONSTANTA MATEMATIKA ---" << endl;
            cout << "Konstanta: pi, p, e" << endl;
            menu = getValidString("Pilih konstanta: ");
            
            tampilkanKonstanta(menu);
            
            string record = menu + " = " + to_string(M_PI);
            histories.push_back({record});
            saveHistory(histories);
        }
        
        // ========== MENU 10: LIHAT HISTORY ==========
        else if (pilihan == 10) {
            tampilkanHistory(histories);
        }
        
        // ========== MENU 11: HAPUS HISTORY ==========
        else if (pilihan == 11) {
            hapusHistory(histories);
        }
        
        // ========== MENU 12: EXPORT HISTORY ==========
        else if (pilihan == 12) {
            if (histories.empty()) {
                cout << "?? Tidak ada history untuk diekspor!" << endl;
            } else {
                exportHistoryToFile(histories);
            }
        }
        
        // ========== MENU 13: KELUAR ==========
        else if (pilihan == 13) {
            cout << "\n==========================================" << endl;
            cout << "   Terima kasih telah menggunakan" << endl;
            cout << "   CALCULATOR PRO++!" << endl;
            cout << "   Sampai jumpa lagi! ??" << endl;
            cout << "==========================================" << endl;
            break;
        }
        
    } while (true);
    
    return 0;
}
