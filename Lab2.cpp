// Lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <bitset>

int main(){

    short A;
    int i;

    std::cin >> A >> i;
    std::bitset<8> binA(A);
    std::cout << A << " = " << binA << std::endl; //вывод первые 8 бит
    int val = (A >> i) & 1;
    std::cout << val << std::endl; //i бит

    if (val != 0) {
        int number1, number2;
        std::cin >> number1 >> number2;

        if number2 != 0 {
            if (number1 % number2 == 0) || (number1 == 0) {
                std::cout << number1 / number2 << std::endl; //вывод 1/2
            }    
        }
        else if number1 != 0 {
            if (number2 % number1 == 0) || (number2 == 0) {
                std::cout << number2 / number1 << std::endl; //вывод 2/1
            }
        }
        else {
            std::cout << number1 * number2 << std::endl; //произведение
        }
    }
    else {
        short res = A;
        if (i + 1 <= 7) {
            res = res ^ (1 << (i + 1));
        }
        if (i - 1 >= 0) {
            res = res ^ (1 << (i - 1));
        }
       
        std::bitset<8> bin_res(res);
        std::cout << res << "=" << bin_res << std::endl;
    }

    return 0;
}



/*int main() {

    int number_of_error;
    std::cin >> number_of_error;
    switch(number_of_error){

        case 1: std::cout << "Неисправность ЭБУ впрыска" << std::endl; break;
        case 2: std::cout << "Неисправность ДУТ" << std::endl; break;
        case 4: std::cout << "Повышенное напряжение" << std::endl; break;
        case 8: std::cout << "Пониженное напряжение" << std::endl; break;
        case 13: std::cout << "Отсутсвует сигнал датчика кислорода" << std::endl; break;
        case 51: std::cout << "Неисправность работы ПЗУ" << std::endl; break;
        case 52: std::cout << "Неисправность работу ОЗУ" << std::endl; break;
        case 55: std::cout << "Слишком бедная смесь" << std::endl; break;
        case 61: std::cout << "Проблемы в работе датчика кислорода" << std::endl; break;
        default: std::cout << "Неизвестная ошибка" << std::endl; break;

    }

    return 0;
}
*/



