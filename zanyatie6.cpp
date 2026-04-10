#include <iostream>
using namespace std;

// Сортировка пузырьком
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // меняем местами
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Бинарный поиск
int binarySearch(int arr[], int n, int key) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (arr[mid] == key)
            return mid; // найден
        else if (arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1; // не найден
}

int main() {
    system("chcp 1251");
    system("cls");
    int n;

    cout << "Введите количество элементов: ";
    cin >> n;

    int arr[100];

    cout << "Введите элементы массива:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Сортировка
    bubbleSort(arr, n);

    cout << "Отсортированный массив:\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    int key;
    cout << "Поиск числа: ";
    cin >> key;

    int result = binarySearch(arr, n, key);

    if (result != -1)
        cout << "Элемент найден с индексом: " << result << endl;
    else
        cout << "Не найден\n";

    return 0;
}
