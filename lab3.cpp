#include <iostream>
#include <limits>
#include <cmath>

int main() {

    int n;
    std::cout << "Count of numbers " << std::endl;
    std::cin >> n; //кол-во чисел в послед-ти

    if (n <= 0) {
        std::cout << "не верно" << std::endl;
        return 0;
    }

    double summa = 0.0;
    double maxn = -std::numeric_limits<double>::max();
    int maxi = -1;

    for (int i = 1; i <= n; i++) {
        double number;
        std::cin >> number;

        if (number <= -0.36 || number > 10.1) {
            continue;
        }

        summa += number;

        if (number > maxn) {
            maxn = number;
            maxi = i;
        }
    }

    if (maxi == -1) {
        std::cout << "Нет чисел из промежутка" << std::endl;
    }
    else {
        std::cout << "Summa " << summa << std::endl; //вывод сумма
        std::cout << "Max number " << maxn << std::endl; //вывод максимальное число
        std::cout << "Index max number " << maxi << std::endl; //вывод индекс максимального числа
    }

    return 0;
}


/*
int main() {

    int a;
    std::cin >> a;

    if (a >= 1000 || a <= -1000) {
        std::cout << "Неверное число" << std::endl;
        return 1;
    }

    int number1 = abs(a);
    int result = 1;

    if (number1 == 0) {
        result = 0;
    }
    else {
        while (number1 > 0) {
            int digit = number1 % 10;
            result *= digit;
            number1 /= 10;
        }
    }

    std::cout << result << std::endl;

    return 0;

}

*/
