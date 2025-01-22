import Foundation
import Network

// Вказуємо порт, на якому працюватиме сервер
let port: NWEndpoint.Port = 42345

// Створюємо слухач (listener) для UDP-з'єднань на заданому порту
let listener = try! NWListener(using: .udp, on: port)

print("Сервер запущено на порту \(port)")

// Обробник для нових підключень
listener.newConnectionHandler = { connection in
    // Запускаємо підключення в окремому потоці
    connection.start(queue: .global())
    
    // Функція для отримання наступного повідомлення
    func receiveNextMessage() {
        connection.receiveMessage { data, _, _, _ in
            // Якщо дані відсутні, підключення завершено
            guard let data = data else {
                print("Підключення завершено.")
                return
            }
            
            var offset = 0
            
            // Зчитуємо номер пакета (UInt32)
            let packetNumber = data.withUnsafeBytes { $0.load(fromByteOffset: offset, as: UInt32.self) }
            offset += MemoryLayout<UInt32>.size
            
            // Зчитуємо timestamp (Int32)
            let timestamp = data.withUnsafeBytes { $0.load(fromByteOffset: offset, as: Int32.self) }
            offset += MemoryLayout<Int32>.size
            
            // Зчитуємо довжину тексту (UInt8)
            let textLength = data.withUnsafeBytes { $0.load(fromByteOffset: offset, as: UInt8.self) }
            offset += MemoryLayout<UInt8>.size
            
            // Зчитуємо текстові дані
            let textData = data[offset..<offset + Int(textLength)]
            let text = String(data: textData, encoding: .utf8) ?? "Invalid text"
            
            // Конвертуємо timestamp у зручний формат дати
            let date = Date(timeIntervalSince1970: TimeInterval(timestamp))
            let formatter = DateFormatter()
            formatter.dateFormat = "yyyy-MM-dd HH:mm:ss"
            let formattedDate = formatter.string(from: date)
            
            // Виводимо інформацію про отриманий пакет
            print("=============================")
            print("Отримано пакет:")
            print("Номер пакета: \(packetNumber)")
            print("Час відправлення: \(formattedDate)")
            print("Довжина тексту: \(textLength) байт")
            print("Текст: \(text)")
            
            // Очікуємо наступне повідомлення
            receiveNextMessage()
        }
    }
    
    // Запуск отримання першого повідомлення
    receiveNextMessage()
}

// Запускаємо слухач у головному потоці
listener.start(queue: .main)
dispatchMain()

