import Foundation
import Network

// Адреса сервера
let serverHost = "127.0.0.1"
let serverPort: NWEndpoint.Port = 42345

// Створення з'єднання
let connection = NWConnection(host: NWEndpoint.Host(serverHost), port: serverPort, using: .tcp)
connection.start(queue: .global())

print("Клієнт підключився до сервера \(serverHost):\(serverPort)")

var packetNumber = 1

func sendPacket() {
    let json: [String: Any] = [
        "packet": packetNumber,
        "timestamp": Int(Date().timeIntervalSince1970),
        "image": "MTIzNDU2NzY3ODkw\n" // Base64 закодоване зображення
    ]
    let jsonData = try! JSONSerialization.data(withJSONObject: json)
    var dataLength = UInt16(jsonData.count)
    
    var packet = Data()
    packet.append(Data(bytes: &dataLength, count: MemoryLayout<UInt16>.size))
    packet.append(jsonData)
    
    connection.send(content: packet, completion: .contentProcessed { error in
        if let error = error {
            print("Помилка відправлення: \(error)")
        } else {
            print("Пакет \(packetNumber) надіслано.")
        }
    })
}

// Відправка пакетів кожні 10 секунд
Timer.scheduledTimer(withTimeInterval: 10.0, repeats: true) { _ in
    sendPacket()
    packetNumber += 1
}

RunLoop.main.run()
