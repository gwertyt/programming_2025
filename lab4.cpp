#include <iostream>

using namespace std;
/*
int main(){

	const int sizemas = 6;
	int mas[sizemas];

	for (int i = 0; i < sizemas; i++) {
		cin >> mas[i];
	}

	int para = 0;
	for (int i = 0; i < sizemas - 1; i++) {			//пара одинаковых чисел подряд
		if (mas[i] == mas[i + 1]) {
			para = 1;
			break;
		}
	}

	if (para == 1) {
		for (int i = 0; i < sizemas - 1; i++) {			//сортировка
			for (int j = 0; j < sizemas - i - 1; j++) {
				if (mas[j] > mas[j + 1]) {
					swap(mas[j], mas[j + 1]);
				}
			}
		}

		for (int i = 0; i < sizemas; i++) {			//вывод если есть пара
			cout << mas[i] << " ";
		}
	}
	else {
		cout << "Нет пар чисел в массиве" << endl;		//вывод если нет пар
	}

	return 0;
}

*/


int main() {
	const int str = 3;
	const int stl = 4;

	int matrix[str][stl];
	for (int i = 0; i < str; i++) {
		for (int j = 0; j < stl; j++) {
			cin >> matrix[i][j];
		}
	}

	int maxsum = -1;
	int maxi = 0;

	for (int i = 0; i < str; i++) {			//наибольшая сумма модулей
		int sum = 0;
		for (int j = 0; j < stl; j++) {
			sum += abs(matrix[i][j]);
		}
		if (sum > maxsum) {
			maxsum = sum;
			maxi = i;
		}
	}

	for (int j = 0; j < stl; j++) {			//обнуление
		matrix[maxi][j] = 0;
	}

	for (int i = 0; i < str; i++) {
		for (int j = 0; j < stl; j++) {
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}

	return 0;
}