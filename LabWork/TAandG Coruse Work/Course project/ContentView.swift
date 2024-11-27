//
//  ContentView.swift
//  Course project
//
//  Created by Андрiй on 08.10.2024.
//

import SwiftUI

struct HeapsortView: View
{
    @State private var array: [Int] = Array(1...20).shuffled()  // Ініціалізація масиву з 20 випадкових елементів
    @State private var sortedIndices: Set<Int> = []             // Множина індексів відсортованих елементів
    @State private var currentIndex: Int? = nil                 // Індекс поточного елемента, що змінюється
    @State private var delay: Double = 0.5                      // Затримка для анімації (в секундах)

    @State private var isSorting: Bool = false                  // Статус виконання сортування
    @State private var isSorted: Bool = false                   // Відсортований масив чи ні
    

    var body: some View
    {
        VStack
        {
            Text("Made by Andrii Izbash")
                .bold()
            
            Spacer()
            // Відображення масиву з індексами
            HStack
            {
                ForEach(array.indices, id: \.self)
                { index in
                    withAnimation(Animation.easeInOut(duration: delay))
                    {
                        Text("\(array[index])")
                            .font(.system(size: 24)) // Шрифт для відображення 20 елементів
                            .frame(width: 30, height: 30) // Розмір для 20 елементів
                            // Зміна фону відповідно до статусу елемента
                            .background(self.sortedIndices.contains(index) ? Color.green : (self.currentIndex == index ? Color.red : Color.blue))
                            .cornerRadius(8)
                    }
                }
            }
            Spacer()
            
            // Кнопка для запуску сортування
            Button
            {
                Task
                {
                    isSorting = true // Встановлюємо статус сортування
                    await heapsort()
                    isSorting = false // Після завершення сортування
                    isSorted = true // Позначаємо масив як відсортований
                }
            }
            label:
            {
                Text("Запустити пірамідальне сортування")
            }
            .buttonStyle(.borderedProminent)
            .disabled(isSorting || isSorted) // Забороняємо натискати під час сортування або якщо масив вже відсортований

            // Кнопка для скидання масиву
            Button
            {
                resetArray() // Перемішуємо масив заново
            }
            label:
            {
                Text("Скинути масив")
            }
            .buttonStyle(.bordered)
            .disabled(isSorting || !isSorted) // Доступна тільки після завершення сортування
        }
        .padding()
    }

    
    // Функція для скидання масиву
    func resetArray()
    {
        withAnimation(Animation.easeInOut(duration: delay))
        {
            array = Array(1...20).shuffled() // Перемішуємо масив заново
            sortedIndices = []               // Очищаємо індекси відсортованих елементів
            currentIndex = nil               // Скидаємо поточний індекс
            isSorted = false                 // Масив більше не відсортований
        }
    }// func resetArray()
    
    
    // Функція, що виконує пірамідальне сортування
    func heapsort() async
    {
        let n = array.count
        
        // Побудова купи (максимальної купи)
        for i in stride(from: n / 2 - 1, through: 0, by: -1)
        {
            await heapify(n: n, i: i)
        }
        
        // Витягування елементів один за одним з купи
        for i in stride(from: n - 1, through: 0, by: -1)
        {
            array.swapAt(0, i) // Заміна кореня з останнім елементом
            sortedIndices.insert(i) // Позначаємо цей елемент як відсортований
            currentIndex = 0 // Оновлюємо поточний індекс для анімації
            try? await Task.sleep(nanoseconds: UInt64(delay * 1_000_000_000)) // Затримка для візуалізації
            await heapify(n: i, i: 0) // Перебудова купи
        }
    }// func heapsort() async
    

    // Функція для перебудови купи з коренем в i
    func heapify(n: Int, i: Int) async
    {
        var largest = i // Найбільший елемент початково — корінь
        let left = 2 * i + 1 // Лівий дочірній елемент
        let right = 2 * i + 2 // Правий дочірній елемент
        
        // Якщо лівий дочірній елемент більше кореня
        if left < n && array[left] > array[largest]
        {
            largest = left
        }
        
        // Якщо правий дочірній елемент більше найбільшого
        if right < n && array[right] > array[largest]
        {
            largest = right
        }
        
        // Якщо найбільший не корінь, міняємо їх місцями
        if largest != i
        {
            array.swapAt(i, largest) // Заміна місцями
            currentIndex = largest // Оновлення індексу для анімації
            try? await Task.sleep(nanoseconds: UInt64(delay * 1_000_000_000)) // Затримка для візуалізації
            await heapify(n: n, i: largest) // Рекурсивно перебудовуємо
        }
    }// func heapify(n: Int, i: Int) async
}


struct ContentView: View
{
    var body: some View
    {
        HeapsortView()
    }
}
