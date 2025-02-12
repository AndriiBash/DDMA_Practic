#include <iostream>     // Для вводу/виводу даних
#include <thread>       // Для роботи з потоками
#include <vector>       // Для використання контейнера vector
#include <cmath>        // Для математичних функцій (sin, cos)
#include <limits>       // Для отримання граничних значень типів даних
#include <mutex>

using namespace std;

mutex results_mutex;    // mutex

// Структура для збереження результатів
struct Result {
    double value;  // Значення функції
    double x;      // Координата x
    double y;      // Координата y
};

// Функція, яка обчислює значення цільової функції
double f(double x, double y)
{
    return sin(x) + cos(y);
}

// Функція для пошуку локального максимуму в заданому проміжку
void find_max(int thread_id,               // Ідентифікатор потоку (для відображення інформації)
              double x_min, double x_max,  // Межі діапазону для змінної x, який обробляє потік
              double y_min, double y_max,  // Межі діапазону для змінної y
              double step,                 // Крок ітерацій
              vector<Result>& results)     // Массив для зберігання результатів
{
    // Ініціалізація локальних змінних для зберігання максимуму в межах поточного потоку
    double local_max = numeric_limits<double>::lowest(); // Початкове значення - найменше можливе
    double local_best_x = 0.0, local_best_y = 0.0;       // Координати локального максимуму

    string thread_info_string = "Потік №" + to_string(thread_id) +
                                " обробляє проміжок x: [" +
                                to_string(x_min) + ", " +
                                to_string(x_max) + "]"  + "\n";

    cout << thread_info_string;

    // Двоцикловий перебір усіх значень у заданих межах
    for (double x = x_min; x <= x_max; x += step)
    {
        for (double y = y_min; y <= y_max; y += step)
        {
            double value = f(x, y); // Обчислення значення функції в точці (x, y)
            if (value > local_max)  // Перевірка, чи нове значення більше поточного максимуму
            {
                local_max = value;   // Оновлення локального максимуму
                local_best_x = x;    // Збереження координат нового максимуму
                local_best_y = y;
            }
        }
    }

    string thread_answer_string = "Потік №" + to_string(thread_id) +
                                  " знайшов локальне максимальне значення: " +
                                  to_string(local_max) +  " при координатах x = " +
                                  to_string(local_best_x) + ", y = " +
                                  to_string(local_best_y) + "\n";
    
    cout << thread_answer_string;

    // Зберігання результату потоку в загальний масив результатів
    {
        lock_guard<mutex> lock(results_mutex);
        results.push_back({local_max, local_best_x, local_best_y});
    }
}

int main()
{
    double x_min;
    double x_max;
    double y_min;
    double y_max;
    double step;
    unsigned int num_threads;                // Змінна для кількості потоків

    // Введення меж діапазонів для змінних x і y
    cout << "Введіть межі для x (min max): ";
    cin >> x_min >> x_max;
    cout << "Введіть межі для y (min max): ";
    cin >> y_min >> y_max;
    cout << "Введіть крок сканування: ";
    cin >> step;
    cout << "Введіть кількість потоків: ";
    cin >> num_threads;

    // Перевірка коректності введення кількості потоків
    if (num_threads == 0)
    {
        cout << "Кількість потоків має бути більше 0. Встановлено 1 потік за замовчуванням." << endl;
        num_threads = 1;
    }

    // Ініціалізація змінних для зберігання результатів
    vector<Result> results;                             // Массив для зберігання результатів
    double x_range = (x_max - x_min) / num_threads;     // Розрахунок діапазону для кожного потоку

    // Створення і запуск потоків
    vector<thread> threads;
    for (unsigned int i = 0; i < num_threads; ++i)
    {
        double thread_x_min = x_min + i * x_range;               // Початок діапазону для потоку
        double thread_x_max = (i == num_threads - 1) ? x_max     // Кінець діапазону (останній потік)
                                                    : thread_x_min + x_range;

        // Додавання нового потоку до вектора потоків
        threads.emplace_back(find_max, i + 1, thread_x_min, thread_x_max, y_min, y_max, step, ref(results));
    }

    // Очікування завершення всіх потоків
    for (auto& t : threads)
    {
        t.join(); // Метод join() очікує завершення потоку перед переходом до наступного
    }

    // Виведення фінальних результатів (глобального максимуму і координат)
    double max_value = numeric_limits<double>::lowest();
    double best_x = 0.0;
    double best_y = 0.0;

    // Пошук глобального максимуму серед усіх результатів
    for (const auto& result : results)
    {
        if (result.value > max_value)
        {
            max_value = result.value;
            best_x = result.x;
            best_y = result.y;
        }
    }

    cout << "\nГлобальне максимальне значення: " << max_value << endl;
    cout << "Координати: x = " << best_x << ", y = " << best_y << endl;

    return 0; // Завершення програми
}
