#include <iostream>
#include <vector>
#include <algorithm>

void printVector(const std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i != vec.size() - 1) std::cout << " ";
    }
}

void viewArray(const std::vector<int>& vec) {
    if (vec.empty()) {
        return;
    }
    printVector(vec);
}

void addToBeginning(std::vector<int>& vec) {
    int value;
    std::cin >> value;
    vec.insert(vec.begin(), value);
}

void addToEnd(std::vector<int>& vec) {
    int value;
    std::cin >> value;
    vec.push_back(value);
}

void searchElement(const std::vector<int>& vec) {
    int value;
    std::cin >> value;

    std::vector<int> indices;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == value) indices.push_back(i);
    }

    if (indices.empty()) {
        std::cout << "элемента нет" << std::endl;
    }
    else {
        for (size_t i = 0; i < indices.size(); ++i) {
            std::cout << indices[i];
            if (i != indices.size() - 1) std::cout << ",";
        }
    }
}

void variantTask(std::vector<int>& vec) {
    if (vec.empty()) {
        std::cout << "массив пуст" << std::endl;
        return;
    }

    std::cout << "до: ";
    printVector(vec);
    std::cout << std::endl;

    int maxElement = *std::max_element(vec.begin(), vec.end());

    int count = std::count(vec.begin(), vec.end(), maxElement);

    vec.erase(std::remove(vec.begin(), vec.end(), maxElement), vec.end());

    if (count == 1) {
        vec.insert(vec.begin(), maxElement);
    }
    else {
        vec.push_back(maxElement);
    }

    std::cout << "После: ";
    printVector(vec);
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec;
    int choice;

    do {
        std::cout << "\n выберите действие:" << std::endl;
        std::cout << "0. выход" << std::endl;
        std::cout << "1. просмотр массива" << std::endl;
        std::cout << "2. добавить элемент в начало" << std::endl;
        std::cout << "3. добавить элемент в конец" << std::endl;
        std::cout << "4. очистка всего массива" << std::endl;
        std::cout << "5. поиск элемента в массиве" << std::endl;
        std::cout << "6. задание варианта" << std::endl;
        std::cout << "выберите действие: ";
        std::cin >> choice;

        switch (choice) {
        case 1: viewArray(vec); break;
        case 2: addToBeginning(vec); break;
        case 3: addToEnd(vec); break;
        case 4: vec.clear(); std::cout << "массив очищен" << std::endl; break;
        case 5: searchElement(vec); break;
        case 6: variantTask(vec); break;
        case 0: std::cout << "ыыход из программы" << std::endl; break;
        default: std::cout << "неверный выбор" << std::endl;
        }
    } while (choice != 0);

    return 0;
}

/*
#include <iostream>
#include <array>
#include <algorithm>

void print(const std::array<int, 10>& arr, const char* text) {
    std::cout << text;
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;
}

// по значению, с копией
void sortValue(std::array<int, 10> arr) {
    std::sort(arr.begin(), arr.end());
    print(arr, "Sorting by value (asc): ");

    std::reverse(arr.begin(), arr.end());
    print(arr, "Sorting by value (desk): ");
}

// по ссылке, оригинал
void sortRef(std::array<int, 10>& arr) {
    std::sort(arr.begin(), arr.end());
    print(arr, "Sorting by link (asc): ");

    std::reverse(arr.begin(), arr.end());
    print(arr, "Sorting by link (desk): ");
}

// по указателю, оригинал
void sortPtr(std::array<int, 10>* arr) {
    std::sort(arr->begin(), arr->end());
    print(*arr, "Sorting by index (asc): ");

    std::reverse(arr->begin(), arr->end());
    print(*arr, "Sorting by index (desk): ");
}

int main() {
    std::array<int, 10> arr;

    for (int i = 0; i < 10; i++) {
        arr[i] = std::rand() % 21 - 10;
    }

    print(arr, "Starting array: ");

    sortValue(arr);
    print(arr, "After sortValue: ");

    sortRef(arr);
    print(arr, "After sortRef: ");

    sortPtr(&arr);
    print(arr, "After sortPtr: ");

    return 0;
}*/

/*
пункт 3
п1 использую vector, потому что нужно было добавлять и удалять элементы, 
а размер массива менялся. vector умеет сам менять свой размер.
п2 использую array, потому что размер фиксированный (10 элементов) и не меняется. 
также array хорошо подходит, чтобы показать разницу между передачей по значению (копия) 
и по ссылке/указателю (работа с оригиналом).
для динамических операций нужен vector, а для фиксированного
размера и демонстрации передачи параметров нужен array.
vector и array одинаково работают, только когда размер массива известен
заранее и не меняется. Но тогда array немного быстрее.
*/
