import Foundation
import Network

// Створюємо з'єднання з сервером
let connection = NWConnection(host: "localhost", port: 12345, using: .tcp)
connection.start(queue: .global())

// Запит даних від користувача
print("Введіть межі для x (min max): ", terminator: "")
let xRange = readLine()!.split(separator: " ").map { Double($0)! }
print("Введіть межі для y (min max): ", terminator: "")
let yRange = readLine()!.split(separator: " ").map { Double($0)! }
print("Введіть крок сканування: ", terminator: "")
let step = Double(readLine()!)!

let xMin = xRange[0]
let xMax = xRange[1]
let yMin = yRange[0]
let yMax = yRange[1]

// Формуємо повідомлення для сервера
let message = "\(xMin) \(xMax) \(yMin) \(yMax) \(step)"
if let messageData = message.data(using: .utf8) {
    connection.send(content: messageData, completion: .contentProcessed({ _ in
        // Отримуємо відповідь від сервера
        connection.receive(minimumIncompleteLength: 1, maximumLength: 1024) { (data, context, isComplete, error) in
            if let data = data, let response = String(data: data, encoding: .utf8) {
                print("Відповідь від сервера: \(response)")
            }
            connection.cancel()
        }
    }))
}

// Дозволяємо часу на виконання
RunLoop.main.run()
