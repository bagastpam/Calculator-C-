#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

struct History {
    string deskripsi;
};

// ================== FUNCTION ==================
double calculate(double a, double b, string op, bool &valid) {
    valid = true;
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
    
    valid = false;
    return 0;
}

// Fungsi validasi input angka
double getValidNumber(string prompt) {
    double value;
    cout << prompt;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid! Masukkan angka: ";
    }
    return value;
}

// Fungsi validasi input string
string getValidString(string prompt) {
    string value;
    cout << prompt;
    cin >> value;
    return value;
}

// ================== SAVE & LOAD ==================
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

void loadHistory(vector<History> &histories) {
    ifstream file("history.txt");
    if (!file) return;
    string line;
    while (getline(file, line)) {
        histories.push_back({line});
    }
    file.close();
}

void exportHistoryToFile(const vector<History> &histories) {
    string filename;
    cout << "Masukkan nama file (contoh: backup.txt): ";
    cin >> filename;
    
    ofstream file(filename.c_str()); // Gunakan .c_str() untuk C++ lama
    if (!file) {
        cout << "Error: Tidak dapat membuat file!" << endl;
        return;
    }
    
    for (size_t i = 0; i < histories.size(); i++) {
        file << i + 1 << ". " << histories[i].deskripsi << endl;
    }
    file.close();
    cout << "History berhasil diekspor ke " << filename << endl;
}

// ================== MAIN ==================
int main() {
    vector<History> histories;
    int pilihan;

    loadHistory(histories);
    
    cout << fixed << setprecision(8);
    cout << "==================================" << endl;
    cout << "   SELAMAT DATANG DI CALCULATOR   " << endl;
    cout << "==================================" << endl;

    do {
        cout << "\n=== CALCULATOR PRO++ (SCIENTIFIC) ===" << endl;
        cout << "1. Operasi Dasar (+, -, *, /, ^)" << endl;
        cout << "2. Fungsi Trigonometri (sin, cos, tan)" << endl;
        cout << "3. Fungsi Logaritma & Akar (log, ln, sqrt)" << endl;
        cout << "4. Fungsi Lainnya (abs, ceil, floor, exp)" << endl;
        cout << "5. Konstanta Matematika (pi, e)" << endl;
        cout << "6. Lihat History" << endl;
        cout << "7. Hapus History" << endl;
        cout << "8. Export History ke File" << endl;
        cout << "9. Keluar" << endl;
        cout << "Pilih (1-9): ";
        
        cin >> pilihan;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid! Masukkan angka 1-9." << endl;
            continue;
        }

        if (pilihan == 1) {
            double a, b, hasil;
            string op;
            bool valid;

            a = getValidNumber("Angka pertama: ");
            op = getValidString("Operator (+, -, *, /, ^): ");
            b = getValidNumber("Angka kedua: ");

            hasil = calculate(a, b, op, valid);
            if (valid) {
                string record = to_string(a) + " " + op + " " + to_string(b) + " = " + to_string(hasil);
                cout << "Hasil: " << hasil << endl;
                histories.push_back({record});
                saveHistory(histories);
            }
        } 
        else if (pilihan == 2) {
            string menu;
            double angka;
            
            cout << "Pilih fungsi (sin, cos, tan): ";
            cin >> menu;
            angka = getValidNumber("Masukkan angka (dalam derajat): ");
            
            if (menu == "sin") {
                double hasilDegree = sin(angka * M_PI / 180.0);
                
                cout << "Hasil sin(" << angka << "°) = " << hasilDegree << endl;
                cout << "Hasil sin(" << angka << " rad) = " << sin(angka) << endl;
                
                string record = "sin(" + to_string(angka) + "°) = " + to_string(hasilDegree);
                histories.push_back({record});
                saveHistory(histories);
            }
            else if (menu == "cos") {
                double hasilDegree = cos(angka * M_PI / 180.0);
                
                cout << "Hasil cos(" << angka << "°) = " << hasilDegree << endl;
                cout << "Hasil cos(" << angka << " rad) = " << cos(angka) << endl;
                
                string record = "cos(" + to_string(angka) + "°) = " + to_string(hasilDegree);
                histories.push_back({record});
                saveHistory(histories);
            }
            else if (menu == "tan") {
                double hasilDegree = tan(angka * M_PI / 180.0);
                
                cout << "Hasil tan(" << angka << "°) = " << hasilDegree << endl;
                cout << "Hasil tan(" << angka << " rad) = " << tan(angka) << endl;
                
                string record = "tan(" + to_string(angka) + "°) = " + to_string(hasilDegree);
                histories.push_back({record});
                saveHistory(histories);
            }
            else {
                cout << "Fungsi tidak dikenal!" << endl;
            }
        }
        else if (pilihan == 3) {
            string menu;
            double angka;
            
            cout << "Pilih fungsi (log, ln, sqrt): ";
            cin >> menu;
            angka = getValidNumber("Masukkan angka: ");
            
            if (menu == "log") {
                if (angka <= 0) {
                    cout << "Error: Logaritma basis 10 hanya untuk angka > 0!" << endl;
                } else {
                    double hasil = log10(angka);
                    cout << "Hasil log10(" << angka << ") = " << hasil << endl;
                    string record = "log10(" + to_string(angka) + ") = " + to_string(hasil);
                    histories.push_back({record});
                    saveHistory(histories);
                }
            }
            else if (menu == "ln") {
                if (angka <= 0) {
                    cout << "Error: Logaritma natural hanya untuk angka > 0!" << endl;
                } else {
                    double hasil = log(angka);
                    cout << "Hasil ln(" << angka << ") = " << hasil << endl;
                    string record = "ln(" + to_string(angka) + ") = " + to_string(hasil);
                    histories.push_back({record});
                    saveHistory(histories);
                }
            }
            else if (menu == "sqrt") {
                if (angka < 0) {
                    cout << "Error: Akar kuadrat tidak untuk angka negatif!" << endl;
                } else {
                    double hasil = sqrt(angka);
                    cout << "Hasil v" << angka << " = " << hasil << endl;
                    string record = "sqrt(" + to_string(angka) + ") = " + to_string(hasil);
                    histories.push_back({record});
                    saveHistory(histories);
                }
            }
            else {
                cout << "Fungsi tidak dikenal!" << endl;
            }
        }
        else if (pilihan == 4) {
            string menu;
            double angka;
            
            cout << "Pilih fungsi (abs, ceil, floor, exp): ";
            cin >> menu;
            angka = getValidNumber("Masukkan angka: ");
            
            if (menu == "abs") {
                double hasil = fabs(angka);
                cout << "Hasil |" << angka << "| = " << hasil << endl;
                string record = "abs(" + to_string(angka) + ") = " + to_string(hasil);
                histories.push_back({record});
                saveHistory(histories);
            }
            else if (menu == "ceil") {
                double hasil = ceil(angka);
                cout << "Hasil ceil(" << angka << ") = " << hasil << endl;
                string record = "ceil(" + to_string(angka) + ") = " + to_string(hasil);
                histories.push_back({record});
                saveHistory(histories);
            }
            else if (menu == "floor") {
                double hasil = floor(angka);
                cout << "Hasil floor(" << angka << ") = " << hasil << endl;
                string record = "floor(" + to_string(angka) + ") = " + to_string(hasil);
                histories.push_back({record});
                saveHistory(histories);
            }
            else if (menu == "exp") {
                double hasil = exp(angka);
                cout << "Hasil e^" << angka << " = " << hasil << endl;
                string record = "exp(" + to_string(angka) + ") = " + to_string(hasil);
                histories.push_back({record});
                saveHistory(histories);
            }
            else {
                cout << "Fungsi tidak dikenal!" << endl;
            }
        }
        else if (pilihan == 5) {
            string menu;
            cout << "Pilih konstanta (pi, e): ";
            cin >> menu;
            
            if (menu == "pi") {
                cout << "Nilai p (PI) = " << M_PI << endl;
                string record = "p = " + to_string(M_PI);
                histories.push_back({record});
                saveHistory(histories);
            }
            else if (menu == "e") {
                cout << "Nilai e = " << M_E << endl;
                string record = "e = " + to_string(M_E);
                histories.push_back({record});
                saveHistory(histories);
            }
            else {
                cout << "Konstanta tidak dikenal!" << endl;
            }
        }
        else if (pilihan == 6) {
            cout << "\n=== HISTORY PERHITUNGAN ===" << endl;
            if (histories.empty()) {
                cout << "History kosong. Belum ada perhitungan yang disimpan." << endl;
            } else {
                cout << "Total " << histories.size() << " riwayat perhitungan:" << endl;
                cout << "----------------------------------------" << endl;
                for (size_t i = 0; i < histories.size(); i++) {
                    cout << i + 1 << ". " << histories[i].deskripsi << endl;
                }
                cout << "----------------------------------------" << endl;
            }
        }
        else if (pilihan == 7) {
            char confirm;
            cout << "Apakah Anda yakin ingin menghapus semua history? (y/n): ";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                histories.clear();
                saveHistory(histories);
                cout << "History berhasil dihapus!" << endl;
            } else {
                cout << "Penghapusan dibatalkan." << endl;
            }
        }
        else if (pilihan == 8) {
            if (histories.empty()) {
                cout << "Tidak ada history untuk diekspor!" << endl;
            } else {
                exportHistoryToFile(histories); // <-- Ini sudah benar, fungsi sudah didefinisikan di atas
            }
        }
        else if (pilihan == 9) {
            cout << "\nTerima kasih telah menggunakan Calculator PRO++!" << endl;
            cout << "Sampai jumpa lagi!" << endl;
            break;
        }
        else {
            cout << "Pilihan tidak valid! Masukkan angka 1-9." << endl;
        }

    } while (pilihan != 9);

    return 0;
}
