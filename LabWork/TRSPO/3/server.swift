import Foundation
import Network

// Функція для обчислення f(x, y)
func f(x: Double, y: Double) -> Double {
    return sin(x) + cos(y)
}

// Створюємо сервер
let listener = try! NWListener(using: .tcp, on: 12345)
print("Сервер запущений і чекає на з'єднання...")

listener.newConnectionHandler = { connection in
    connection.start(queue: .global())

    // Отримання даних від клієнта
    connection.receive(minimumIncompleteLength: 1, maximumLength: 1024) { (data, context, isComplete, error) in
        if let data = data, let message = String(data: data, encoding: .utf8) {
            print("Отримано дані від клієнта: ")
            
            // Розбір отриманих даних
            let components = message.split(separator: " ")
            let xMin = Double(components[0])!
            let xMax = Double(components[1])!
            let yMin = Double(components[2])!
            let yMax = Double(components[3])!
            let step = Double(components[4])!

            // Виведення отриманих меж
            print("Задані межі для x (min max): \(xMin) \(xMax)")
            print("Задані межі для y (min max): \(yMin) \(yMax)")
            print("Заданий крок сканування: \(step)")

            var maxValue = -Double.greatestFiniteMagnitude // Використовуємо максимально можливе негативне значення для початку
            var bestX = 0.0
            var bestY = 0.0

            // Пошук максимального значення
            for x in stride(from: xMin, to: xMax, by: step) {
                for y in stride(from: yMin, to: yMax, by: step) {
                    let value = f(x: x, y: y)
                    if value > maxValue {
                        maxValue = value
                        bestX = x
                        bestY = y
                    }
                }
            }
            
            // Перевірка чи було знайдено максимальне значення
            if maxValue == -Double.greatestFiniteMagnitude {
                print("Не вдалося знайти значення у вказаному діапазоні.")
            } else {
                maxValue = round(maxValue * 1000) / 1000        // округлюємо до 3 цифр після коми
                print("Максимальне значення: \(maxValue), координати: x = \(bestX), y = \(bestY)")
            }

            // Відправка результату клієнту
            let response = "Максимальне значення: \(maxValue), координати: x = \(bestX), y = \(bestY)"
            if let responseData = response.data(using: .utf8) {
                connection.send(content: responseData, completion: .contentProcessed({ _ in
                    connection.cancel()
                }))
            }
        }
    }
}

listener.start(queue: .global())
RunLoop.main.run()
