//
//  main.cpp
//  C++Console
//
//  Created by Андрiй on 27.01.2025.
//

#include <iostream>

using namespace std;

double f(double x, double y) {
    return sin(x) + cos(y);
}



int main(int argc, const char * argv[]) {
    // Введення меж і кроку
    double x_min, x_max, y_min, y_max, step;
    cout << "Введіть межі для x (min max): ";
    cin >> x_min >> x_max;
    cout << "Введіть межі для y (min max): ";
    cin >> y_min >> y_max;
    cout << "Введіть крок сканування: ";
    cin >> step;

    // Ініціалізація
    double max_value = numeric_limits<double>::lowest();
    double best_x = 0.0, best_y = 0.0;

    // Пошук максимального значення
    for (double x = x_min; x <= x_max; x += step) {
        for (double y = y_min; y <= y_max; y += step) {
            double value = f(x, y);
            if (value > max_value) {
                max_value = value;
                best_x = x;
                best_y = y;
            }
        }
    }

    // Виведення результатів
    cout << "Максимальне значення: " << max_value << endl;
    cout << "Координати: x = " << best_x << ", y = " << best_y << endl;

    return 0;
}
