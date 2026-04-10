#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int SIZE = 20;

enum Comfort { LUXE, JUNIOR, STANDARD, ECONOMY };

struct Amenities {
    bool hasWiFi;
    bool hasTV;
    bool hasFridge;
};

struct HotelRoom {
    string hotelName;
    int number;
    Comfort comfortType;
    int capacity;
    double price;
    Amenities options;
};

void printRow(const HotelRoom& r) {
    string cTypes[] = { "LUXE", "JUNIOR", "STANDARD", "ECONOMY" };
    cout << setw(15) << left << r.hotelName
        << " | №" << setw(4) << r.number
        << " | " << setw(9) << cTypes[r.comfortType]
        << " | Мест: " << r.capacity
        << " | Цена: " << setw(7) << r.price
        << " | Холодильник: " << (r.options.hasFridge ? "+" : "-") << endl; // Fridge для примера
}

// 5. Функция изменения данных (Задание 5)
void changePrice(HotelRoom* arr, int n, int targetNum, double newPrice) {
    for (int i = 0; i < n; i++) {
        if (arr[i].number == targetNum) {
            arr[i].price = newPrice;
        }
    }
}

void bubbleSort(HotelRoom* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].price > arr[j + 1].price) {
                HotelRoom temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

HotelRoom* init() {
    HotelRoom* rooms = new HotelRoom[SIZE];
    rooms[0] = { "Grand Plaza", 101, LUXE, 2, 8500.0, {true, true, true} };
    rooms[1] = { "Ocean Plaza", 202, STANDARD, 3, 4500.0, {true, false, true} };
    rooms[2] = { "Sunset Hotel", 305, ECONOMY, 1, 2100.0, {false, true, false} };
    rooms[3] = { "Royal Plaza", 105, LUXE, 2, 9200.0, {true, true, true} };
    rooms[4] = { "City Plaza", 404, STANDARD, 2, 3500.0, {true, true, false} };
    rooms[5] = { "Cheap Rest", 10, ECONOMY, 2, 1200.0, {false, false, false} };
    rooms[6] = { "Marine Plaza", 108, JUNIOR, 2, 5200.0, {true, true, true} };
    rooms[7] = { "Elite Resort", 501, LUXE, 4, 15000.0, {true, true, true} };
    rooms[8] = { "Small Plaza", 12, ECONOMY, 1, 1800.0, {false, true, false} };
    rooms[9] = { "Skyline", 901, JUNIOR, 2, 6000.0, {true, true, false} };
    rooms[10] = { "Park Plaza", 110, STANDARD, 2, 3800.0, {true, true, false} };
    rooms[11] = { "Hostel One", 1, ECONOMY, 6, 950.0, {false, false, false} };
    rooms[12] = { "Luxury Plaza", 777, LUXE, 2, 25000.0, {true, true, true} };
    rooms[13] = { "Nordic Inn", 44, JUNIOR, 3, 5400.0, {true, true, false} };
    rooms[14] = { "Central Plaza", 102, STANDARD, 2, 4100.0, {true, true, true} };
    rooms[15] = { "Breeze Hotel", 215, STANDARD, 2, 3900.0, {true, false, true} };
    rooms[16] = { "East Plaza", 310, ECONOMY, 1, 1600.0, {false, true, false} };
    rooms[17] = { "Palm Resort", 505, LUXE, 3, 12500.0, {true, true, true} };
    rooms[18] = { "Winter Plaza", 112, JUNIOR, 2, 5800.0, {true, true, false} };
    rooms[19] = { "Gorky Plaza", 115, STANDARD, 2, 4300.0, {true, true, true} };
    return rooms;
}

int main() {
    system("chcp 1251");
    system("cls");

    HotelRoom* catalog = init();

   
    cout << "--- 1. Номера в отелях 'Plaza' ---" << endl;
    for (int i = 0; i < SIZE; i++) {
        if (catalog[i].hotelName.length() >= 5 && catalog[i].hotelName.substr(catalog[i].hotelName.length() - 5) == "Plaza") {
            printRow(catalog[i]);
        }
    }

    
    bubbleSort(catalog, SIZE);
    cout << "\n--- 2. Все номера (отсортированы по цене) ---" << endl;
    for (int i = 0; i < SIZE; i++) printRow(catalog[i]);

    
    cout << "\n--- 3. Поиск номера 777 ---" << endl;
    for (int i = 0; i < SIZE; i++) {
        if (catalog[i].number == 777) printRow(catalog[i]);
    }

    
    cout << "\n--- 4. Три самых дешевых номера ---" << endl;
    for (int i = 0; i < 3; i++) printRow(catalog[i]);

    
    cout << "\n--- 5. Изменение цены номера 101 на 7000 ---" << endl;
    changePrice(catalog, SIZE, 101, 7000.0);
    for (int i = 0; i < SIZE; i++) {
        if (catalog[i].number == 101) printRow(catalog[i]);
    }

   
    int count = 0;
    for (int i = 0; i < SIZE; i++) if (catalog[i].options.hasFridge) count++;

    HotelRoom* fridgeRooms = new HotelRoom[count];
    int index = 0;
    for (int i = 0; i < SIZE; i++) {
        if (catalog[i].options.hasFridge) {
            fridgeRooms[index++] = catalog[i];
        }
    }

    cout << "\n--- 6. Новый массив (номера с холодильником) ---" << endl;
    for (int i = 0; i < count; i++) printRow(fridgeRooms[i]);

    delete[] catalog;
    delete[] fridgeRooms;

    return 0;
}
