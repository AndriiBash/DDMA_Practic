import Foundation
import Network

// Функція для обчислення математичної функції f(x, y)
func f(x: Double, y: Double) -> Double {
    return sin(x) + cos(y)
}

// Клас Server відповідає за створення серверу, який слухає підключення на заданому порту
class Server {
    let port: NWEndpoint.Port  // Порт, на якому працює сервер
    let listener: NWListener   // NWListener для прослуховування вхідних підключень

    // Ініціалізуємо сервер з заданим портом
    init(port: NWEndpoint.Port) throws {
        self.port = port
        self.listener = try NWListener(using: .tcp, on: port)  // Ініціалізація TCP слухача
    }

    // Метод для запуску серверу
    func start() {
        print("Сервер на порту \(port.rawValue) запущений...")

        // Обробник для нових підключень клієнтів
        listener.newConnectionHandler = { connection in
            connection.start(queue: .global())  // Запускаємо з'єднання в глобальній черзі

            // Приймаємо дані від клієнта
            connection.receive(minimumIncompleteLength: 1, maximumLength: 1024) { (data, _, _, _) in
                if let data = data, let message = String(data: data, encoding: .utf8) {
                    // Розділяємо отримані дані на числові значення
                    let components = message.split(separator: " ").map { Double($0)! }
                    let xMin = components[0]  // Мінімальна межа для x
                    let xMax = components[1]  // Максимальна межа для x
                    let yMin = components[2]  // Мінімальна межа для y
                    let yMax = components[3]  // Максимальна межа для y
                    let step = components[4]  // Крок для обчислень

                    // Ініціалізація змінних для пошуку максимального значення функції
                    var maxValue = -Double.greatestFiniteMagnitude  // Початкове значення максимально мінімальне
                    var bestX = 0.0, bestY = 0.0  // Координати, де знайдено максимум

                    // Перебір всіх можливих комбінацій (x, y) у заданому діапазоні
                    for x in stride(from: xMin, through: xMax, by: step) {
                        for y in stride(from: yMin, through: yMax, by: step) {
                            let value = f(x: x, y: y)  // Обчислення значення функції
                            if value > maxValue {  // Якщо нове значення більше попереднього максимуму
                                maxValue = value
                                bestX = x
                                bestY = y
                            }
                        }
                    }

                    // Вивід знайденого максимуму на цьому сервері
                    print("Сервер на порту \(self.port.rawValue) знайшов максимум: \(maxValue) при x = \(bestX), y = \(bestY)")

                    // Відправка знайденого максимуму назад клієнту
                    let response = "\(maxValue) \(bestX) \(bestY)"
                    if let responseData = response.data(using: .utf8) {
                        connection.send(content: responseData, completion: .contentProcessed({ _ in
                            connection.cancel()  // Закриваємо з'єднання після відправки
                        }))
                    }
                }
            }
        }

        listener.start(queue: .global())  // Запуск прослуховування на сервері
    }
}

// Клієнтська функція для розподілу обчислень між серверами
func startClient(servers: [NWEndpoint.Port], xMin: Double, xMax: Double, yMin: Double, yMax: Double, step: Double) {
    let xRangePerServer = (xMax - xMin) / Double(servers.count)  // Розподіл діапазону x між серверами
    var maxResult: (value: Double, x: Double, y: Double) = (-Double.greatestFiniteMagnitude, 0.0, 0.0)  // Глобальний максимум
    let group = DispatchGroup()  // Використовуємо для синхронізації завершення обчислень усіх серверів

    // Перебір всіх серверів
    for (index, port) in servers.enumerated() {
        let xStart = xMin + Double(index) * xRangePerServer  // Початок діапазону для поточного серверу
        let xEnd = (index == servers.count - 1) ? xMax : xStart + xRangePerServer  // Кінець діапазону

        let connection = NWConnection(host: "localhost", port: port, using: .tcp)  // Створення TCP-з'єднання
        connection.start(queue: .global())  // Запуск з'єднання у глобальній черзі

        // Формуємо повідомлення для серверу: межі для x, y та крок
        let message = "\(xStart) \(xEnd) \(yMin) \(yMax) \(step)"
        if let messageData = message.data(using: .utf8) {
            group.enter()  // Відзначаємо, що задача для цього серверу активна
            connection.send(content: messageData, completion: .contentProcessed({ _ in
                // Приймаємо відповідь від серверу
                connection.receive(minimumIncompleteLength: 1, maximumLength: 1024) { (data, _, _, _) in
                    if let data = data, let response = String(data: data, encoding: .utf8) {
                        let parts = response.split(separator: " ").map { Double($0)! }  // Розділяємо отримані дані
                        let value = parts[0]  // Максимальне значення функції
                        let x = parts[1]  // Координата x, де знайдено максимум
                        let y = parts[2]  // Координата y, де знайдено максимум

                        // Вивід результату від кожного серверу
                        print("Сервер на порту \(port.rawValue) обчислив максимум: \(value) при x = \(x), y = \(y)")

                        // Перевірка, чи знайдене значення є новим глобальним максимумом
                        if value > maxResult.value {
                            maxResult = (value, x, y)
                        }
                    }
                    connection.cancel()  // Закриваємо з'єднання після отримання відповіді
                    group.leave()  // Відзначаємо завершення задачі для цього серверу
                }
            }))
        }
    }

    // Очікуємо завершення всіх обчислень на серверах
    group.wait()
    
    // Вивід глобального максимуму серед усіх серверів
    print("\nГлобальний максимум серед усіх серверів: \(maxResult.value), координати: x = \(maxResult.x), y = \(maxResult.y)")
}

// Основна програма, де користувач вводить параметри
print("Введіть кількість серверів:")
let numServers = Int(readLine()!)!  // Отримуємо кількість серверів від користувача
var servers: [Server] = []  // Масив для збереження серверів
var ports: [NWEndpoint.Port] = []  // Масив для збереження портів серверів

// Створюємо та запускаємо сервери на різних портах
for i in 0..<numServers {
    let port = NWEndpoint.Port(rawValue: UInt16(12345 + i))!  // Визначаємо порт для кожного серверу
    ports.append(port)
    let server = try! Server(port: port)  // Створення серверу
    server.start()  // Запуск серверу
    servers.append(server)  // Додаємо сервер до масиву
}

// Отримання діапазонів для обчислень від користувача
print("Введіть межі для x (min max): ", terminator: "")
let xRange = readLine()!.split(separator: " ").map { Double($0)! }  // Межі для x
print("Введіть межі для y (min max): ", terminator: "")
let yRange = readLine()!.split(separator: " ").map { Double($0)! }  // Межі для y
print("Введіть крок сканування: ", terminator: "")
let step = Double(readLine()!)!  // Крок для сканування

// Запускаємо клієнта для розподілу задачі між серверами
startClient(servers: ports, xMin: xRange[0], xMax: xRange[1], yMin: yRange[0], yMax: yRange[1], step: step)

RunLoop.main.run()  // Запускаємо основний цикл для підтримки роботи серверів
