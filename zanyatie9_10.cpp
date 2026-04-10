#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream> 
#include <cstring>

using namespace std;

const int SIZE = 20;

enum Comfort { LUXE, JUNIOR, STANDARD, ECONOMY };

struct Amenities {
    bool hasWiFi;
    bool hasTV;
    bool hasFridge;
};


struct HotelRoom {
    char hotelName[80];
    int number;
    Comfort comfortType;
    int capacity;
    double price;
    Amenities options;
};


void updatePriceFromTextFile(HotelRoom* arr, int n, string filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Ошибка: Файл " << filename << " не найден!" << endl;
        return;
    }

    char nameInFile[80];
    double newPrice;

  
    while (fin >> nameInFile >> newPrice) {
        for (int i = 0; i < n; i++) {
            if (strcmp(arr[i].hotelName, nameInFile) == 0) {
                arr[i].price = newPrice;
            }
        }
    }
    fin.close();
}

//Запись массива в бинар
void saveToBinary(HotelRoom* arr, int n, string filename) {
    ofstream out(filename, ios::binary | ios::out);
    if (out.is_open()) {
        for (int i = 0; i < n; i++) {
            out.write((char*)&arr[i], sizeof(HotelRoom)); 
        }
        out.close();
        cout << "Данные сохранены в бинарный файл." << endl;
    }
}

//Чтение массива из бинар
void loadFromBinary(HotelRoom* target, int n, string filename) {
    ifstream in(filename, ios::binary | ios::in);
    if (in.is_open()) {
        for (int i = 0; i < n; i++) {
            in.read((char*)&target[i], sizeof(HotelRoom)); // [cite: 10]
        }
        in.close();
        cout << "Данные загружены из бинарного файла." << endl;
    }
}

void printRow(HotelRoom& r) {
    const char* cTypes[] = { "LUXE", "JUNIOR", "STANDARD", "ECONOMY" };

    cout << setw(15) << left << r.hotelName
        << " | №" << setw(4) << r.number
        << " | " << setw(9) << cTypes[r.comfortType]
        << " | Мест: " << r.capacity
        << " | Цена: " << setw(8) << r.price
        << " | Холод: " << (r.options.hasFridge ? "+" : "-") << endl;
}

HotelRoom* init() {
    HotelRoom* rooms = new HotelRoom[SIZE];
    strcpy_s(rooms[0].hotelName, "Grand_Plaza");
    rooms[0].number = 101; rooms[0].comfortType = LUXE; rooms[0].capacity = 2;
    rooms[0].price = 8500.0; rooms[0].options = { true, true, true };

    strcpy_s(rooms[1].hotelName, "Ocean_Plaza");
    rooms[1].number = 202; rooms[1].comfortType = STANDARD; rooms[1].capacity = 3;
    rooms[1].price = 4500.0; rooms[1].options = { true, false, true };

    for (int i = 2; i < SIZE; i++) {
        strcpy_s(rooms[i].hotelName, "Other_Hotel");
        rooms[i].number = 100 + i;
        rooms[i].comfortType = ECONOMY;
        rooms[i].capacity = 1;
        rooms[i].price = 2000.0;
        rooms[i].options = { false, false, false };
    }
    return rooms;
}

int main() {
    setlocale(LC_ALL, "Russian"); 

    HotelRoom* catalog = init();

    cout << "--- 1. Данные ДО обновления ---" << endl;
    printRow(catalog[0]);
    printRow(catalog[1]);

    // Текст (Задание 1)
    updatePriceFromTextFile(catalog, SIZE, "prices.txt");

    cout << "\n--- 2. Данные ПОСЛЕ обновления из prices.txt ---" << endl;
    printRow(catalog[0]);
    printRow(catalog[1]);

    // Бинар (Задание 2)
    cout << "\n--- 3. Работа с бинарным файлом ---" << endl;
    saveToBinary(catalog, SIZE, "hotel_data.bin");

    HotelRoom* loadedCatalog = new HotelRoom[SIZE];
    loadFromBinary(loadedCatalog, SIZE, "hotel_data.bin");

    cout << "Проверка первой записи из бинарника:" << endl;
    printRow(loadedCatalog[0]);

    delete[] catalog;
    delete[] loadedCatalog;

    return 0;
}
