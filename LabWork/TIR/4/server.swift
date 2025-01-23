import Foundation
import Network

// Порт для сервера
let port: NWEndpoint.Port = 42345

// Створення слухача для TCP-з'єднань
let listener = try! NWListener(using: .tcp, on: port)

print("Сервер запущено на порту \(port)")

// Обробник нових підключень
listener.newConnectionHandler = { connection in
    print("Нове підключення від \(connection.endpoint)")
    connection.start(queue: .global())
    
    func receiveNextMessage() {
        connection.receive(minimumIncompleteLength: 2, maximumLength: 1024) { data, _, isComplete, error in
            if let error = error {
                print("Помилка з'єднання: \(error)")
                return
            }
            
            guard let data = data else {
                print("З'єднання завершено.")
                return
            }
            
            var offset = 0
            
            // Зчитування довжини даних (UInt16)
            guard data.count >= 2 else {
                print("Отримано недостатньо даних для довжини.")
                return
            }
            let dataLength = data.withUnsafeBytes { $0.load(fromByteOffset: offset, as: UInt16.self) }
            offset += MemoryLayout<UInt16>.size
            
            guard data.count >= offset + Int(dataLength) else {
                print("Отримано недостатньо даних для JSON.")
                return
            }
            
            // Зчитування JSON-даних
            let jsonData = data[offset..<offset + Int(dataLength)]
            if let jsonString = String(data: jsonData, encoding: .utf8),
               let jsonObject = try? JSONSerialization.jsonObject(with: jsonData) as? [String: Any] {
                print("Отримано JSON:")
                print(jsonString)
                
                // Збереження JSON у файл
                if let packetNumber = jsonObject["packet"] as? Int {
                    let fileName = "packet\(packetNumber).json"
                    let fileURL = FileManager.default.temporaryDirectory.appendingPathComponent(fileName)
                    try? jsonString.write(to: fileURL, atomically: true, encoding: .utf8)
                    print("Дані збережено у файл: \(fileURL.path)")
                }
            } else {
                print("Невірний формат JSON.")
            }
            
            if isComplete {
                print("З'єднання завершено клієнтом.")
            } else {
                receiveNextMessage()
            }
        }
    }
    
    receiveNextMessage()
}

listener.start(queue: .main)
dispatchMain()
