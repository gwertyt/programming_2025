#include <iostream>

using namespace std;

int twonumber(int a, int b) {
	cout << "использована функция для 2х чисел" << endl;
	
    if (a % b == 0) {
        return a / b;
    }
    else if (b % a == 0) {
        return b / a;
    }
    else {
        return a * b;
    }
}

int threenumber(int a, int b, int c) {
    cout << "использована функция для 3х чисел" << endl;

    if (a == b && b == c) {
        return 1;
    }
    else {
        return -1;
    }
}

void calculations(int a, int b) {
    cout << "использована функция операций для чисел" << endl;
    cout << a + b << endl;      
    cout << a - b << endl;      
    cout << b - a << endl;      
    cout << a * b << endl;
    if (b != 0) {
        cout << (double(a) / b) << endl;
    }
    else {
        cout << "невозможно деление на 0" << endl;
    }

    if (a != 0) {
        cout << (double(b) / a) << endl;
    }
    else {
        cout << "невозможно деление на 0" << endl;
    }
}

int main() {
    int choice;
    int n1, n2, n3;

    cin >> choice;

    if (choice == 1) {
        cin >> n1 >> n2 >> n3;

        int ct = 0;
        if (n1 != 0) ct++;
        if (n2 != 0) ct++;
        if (n3 != 0) ct++;

        int res;



        if (ct == 1) {
            int one;
            if (n1 != 0) one = n1;
            else if (n2 != 0) one = n2;
            else one = n3;

            cout << "только одно число: " << one << endl;
        }


        else if (ct == 2) {
            int a, b;
            if (n1 != 0 && n2 != 0) {
                a = n1, b = n2;
            }
            else if (n1 != 0 && n3 != 0) {
                a = n1, b = n3;
            }
            else {
                a = n2, b = n3;
            }

            res = twonumber(a, b);
            cout << res << endl;
        }


        else if (ct==3) {
            res = threenumber(n1, n2, n3);
            cout << res << endl;
        }


        else {
            cout << "все числа 0" << endl;
        }
    }

    else if (choice == 2) {

        cin >> n1 >> n2;

        if (n1 < 0 || n2 < 0) {
            cout << "есть отрицательное число" << endl;
        }
        else {
            calculations(n1, n2);
        }
       
    }

    else {
        cout << "это не 1 или 2" << endl;
    }

    return 0;
}


