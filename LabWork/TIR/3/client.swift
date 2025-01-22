import Foundation
import Network

// Вказуємо хост і порт сервера
let host = NWEndpoint.Host("127.0.0.1")
let port: NWEndpoint.Port = 42345

// Створюємо підключення до сервера через UDP
let connection = NWConnection(host: host, port: port, using: .udp)
connection.start(queue: .global())

// Функція для надсилання пакета
func sendPacket(packetNumber: UInt32, text: String) {
    // Генеруємо поточний timestamp
    let timestamp = Int32(Date().timeIntervalSince1970)
    
    // Конвертуємо текст у Data
    let textData = text.data(using: .utf8) ?? Data()
    let textLength = UInt8(min(textData.count, 256)) // Максимальна довжина тексту - 256 байт
    
    // Формуємо пакет
    var packet = Data()
    packet.append(contentsOf: withUnsafeBytes(of: packetNumber) { Data($0) }) // Номер пакета
    packet.append(contentsOf: withUnsafeBytes(of: timestamp) { Data($0) })   // Час відправлення
    packet.append(textLength)                                               // Довжина тексту
    packet.append(textData.prefix(Int(textLength)))                         // Текст
    
    // Надсилаємо пакет
    connection.send(content: packet, completion: .contentProcessed { error in
        if let error = error {
            print("Помилка надсилання: \(error)")
        } else {
            print("Пакет надіслано: \(packetNumber)")
        }
    })
}

// Лічильник номерів пакетів
var packetNumber: UInt32 = 1

// Цикл для введення тексту
while true {
    print("Введення:", terminator: " ") // Запитуємо текст у користувача
    if let input = readLine(), !input.isEmpty {
        if input.lowercased() == "exit" { // Якщо введено "exit", завершуємо роботу
            print("Завершення роботи клієнта.")
            break
        }
        sendPacket(packetNumber: packetNumber, text: input) // Надсилаємо пакет
        packetNumber += 1
    } else {
        print("Текст не може бути порожнім. Спробуйте ще раз.") // Повідомлення про помилку
    }
}
