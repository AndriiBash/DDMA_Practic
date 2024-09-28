import SwiftUI

struct ContentView: View {
    @State private var a: Double = 140 // Міжосьова відстань в мм
    @State private var m: Double = 2.75 // Модуль
    @State private var psi_ba: Double = 0.3 // Коефіцієнт ширини зубчастого вінця
    @State private var n1: Double = 289 // Швидкість обертання, об/хв
    @State private var d1: Double = 47 // Діаметр колеса в мм
    @State private var U_12: Double = 5 // Передавальне число
    
    @State private var Z_sum: Double = 0.0
    @State private var Z1: Double = 0.0
    @State private var Z2: Double = 0.0
    @State private var U_12_actual: Double = 0.0
    @State private var delta_U: Double = 0.0
    @State private var V: Double = 0.0
    @State private var b: Double = 0.0
    @State private var b1: Double = 0.0

    var body: some View {
        VStack {
            Text("Розрахунок зубчастої передачі")
                .font(.largeTitle)
                .padding()
            
            HStack {
                Text("Міжосьова відстань (a)")
                TextField("Введіть a", value: $a, formatter: NumberFormatter())
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .padding()
            }
            
            HStack {
                Text("Модуль (m)")
                TextField("Введіть m", value: $m, formatter: NumberFormatter())
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .padding()
            }
            
            HStack {
                Text("Коефіцієнт ширини вінця (ψba)")
                TextField("Введіть ψba", value: $psi_ba, formatter: NumberFormatter())
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .padding()
            }
            
            HStack {
                Text("Швидкість обертання (n1)")
                TextField("Введіть n1", value: $n1, formatter: NumberFormatter())
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .padding()
            }
            
            HStack {
                Text("Діаметр колеса (d1)")
                TextField("Введіть d1", value: $d1, formatter: NumberFormatter())
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .padding()
            }
            
            HStack {
                Text("Передавальне число (U12)")
                TextField("Введіть U12", value: $U_12, formatter: NumberFormatter())
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .padding()
            }
            
            Button("Обчислити") {
                calculate()
            }
            .padding()
            
            // Виведення результатів
            Text("Сума зубців Z1 + Z2: \(Z_sum, specifier: "%.2f")")
            Text("Z1: \(Z1, specifier: "%.0f")")
            Text("Z2: \(Z2, specifier: "%.0f")")
            Text("Фактичне передавальне число: \(U_12_actual, specifier: "%.2f")")
            Text("Похибка ΔU: \(delta_U, specifier: "%.2f")%")
            Text("Окружна швидкість V: \(V, specifier: "%.2f") м/с")
            Text("Ширина колеса b: \(b, specifier: "%.0f") мм")
            Text("Ширина шестерні b1: \(b1, specifier: "%.0f") мм")
        }
        .padding()
    }
    
    // Функція для розрахунків
    func calculate() {
        Z_sum = (2 * a) / m
        Z1 = Z_sum / (U_12 + 1)
        Z2 = Z_sum - Z1
        U_12_actual = Z2 / Z1
        delta_U = abs((U_12 - U_12_actual) / U_12) * 100
        V = (Double.pi * d1 * n1) / 60000
        b = psi_ba * a
        b1 = b + 5 // Додаємо 5 мм для компенсації
    }
}
