import SwiftUI
import Foundation

// Модель для зберігання даних JSON
struct PacketData: Identifiable, Codable {
    let id = UUID()
    let packet: Int
    let timestamp: Int
    let image: String
}

struct ContentView: View {
    @State private var packets: [PacketData] = []

    var body: some View {
        VStack {
            List(packets) { packet in
                VStack(alignment: .leading) {
                    Text("Пакет: \(packet.packet)")
                        .font(.headline)
                    Text("Часова мітка: \(packet.timestamp)")
                        .font(.subheadline)
                    if let imageData = Data(base64Encoded: packet.image),
                       let nsImage = NSImage(data: imageData) {
                        Image(nsImage: nsImage)
                            .resizable()
                            .scaledToFit()
                            .frame(height: 100)
                    } else {
                        Text("Некоректні дані зображення")
                            .foregroundColor(.red)
                    }
                }
                .padding()
            }
            .navigationTitle("Пакети")
            .toolbar {
                ToolbarItem(placement: .primaryAction) {
                    Button(action: loadPackets) {
                        Label("Оновити", systemImage: "arrow.clockwise")
                    }
                }
            }
        }
    }

    // Завантаження даних з файлів JSON
    func loadPackets() {
        packets = [] // Очищаємо поточні дані
        let fileManager = FileManager.default
        let tempDirectory = fileManager.temporaryDirectory

        do {
            let files = try fileManager.contentsOfDirectory(at: tempDirectory, includingPropertiesForKeys: nil)
                        
            for file in files where file.pathExtension == "json" {
                if let data = try? Data(contentsOf: file),
                   let packet = try? JSONDecoder().decode(PacketData.self, from: data) {
                    packets.append(packet)
                    print("Шлях до файлу: \(file.path)")
                }
            }
        } catch {
            print("Помилка завантаження файлів: \(error)")
        }
    }
}
