import SwiftUI

struct ContentView: View {
    @State private var Ft1: Double = 0.0
    @State private var Ft2: Double = 0.0
    @State private var Fr1: Double = 0.0
    @State private var Fr2: Double = 0.0
    @State private var FR1: Double = 0.0
    @State private var FR2: Double = 0.0
    @State private var Pr1: Double = 0.0
    @State private var Pr2: Double = 0.0
    @State private var VnutrD1: String = ""
    @State private var ZovnD1: String = ""
    @State private var Shir1: String = ""
    @State private var Vantazh1: String = ""
    @State private var ResursOb1: String = ""
    @State private var ResursGod1: String = ""
    @State private var VnutrD2: String = ""
    @State private var ZovnD2: String = ""
    @State private var Shir2: String = ""
    @State private var Vantazh2: String = ""
    @State private var ResursOb2: String = ""
    @State private var ResursGod2: String = ""

    // Функція для обчислення Pr
    func Pr(_ FR: Double) -> Double {
        let X: Double = 1.0
        let V: Double = 1.0
        let Kb: Double = 1.0
        let Kt: Double = 1.0
        return (X * FR * V) * Kb * Kt
    }

    var body: some View {
        VStack {
            // Виведення результатів
            Text("Ft1: \(Ft1)")
            Text("Ft2: \(Ft2)")
            Text("Fr1: \(Fr1)")
            Text("Fr2: \(Fr2)")
            Text("FR1: \(FR1)")
            Text("FR2: \(FR2)")
            Text("Pr1: \(Pr1)")
            Text("Pr2: \(Pr2)")

            Text("Внутрішній діаметр 1: \(VnutrD1)")
            Text("Зовнішній діаметр 1: \(ZovnD1)")
            Text("Ширина 1: \(Shir1)")
            Text("Вантажопідйомність 1: \(Vantazh1)")
            Text("Ресурс у оборотах 1: \(ResursOb1)")
            Text("Ресурс у годинах 1: \(ResursGod1)")

            Text("Внутрішній діаметр 2: \(VnutrD2)")
            Text("Зовнішній діаметр 2: \(ZovnD2)")
            Text("Ширина 2: \(Shir2)")
            Text("Вантажопідйомність 2: \(Vantazh2)")
            Text("Ресурс у оборотах 2: \(ResursOb2)")
            Text("Ресурс у годинах 2: \(ResursGod2)")

            // Кнопка для запуску розрахунків
            Button(action: {
                // Нові дані з таблиці
                let P_okr: Double = 161
                let Tz2: Double = 217.9
                let d2: Double = 101.82

                Ft1 = P_okr
                Ft2 = (2 * Tz2 * 1000) / ceil(d2)
                Fr1 = Ft1 * 0.36397
                Fr2 = Ft2 * 0.36397
                FR1 = sqrt(pow(Fr1, 2) + pow(Ft1, 2))
                FR2 = sqrt(pow(Fr2, 2) + pow(Ft2, 2))
                Pr1 = Pr(FR1)
                Pr2 = Pr(FR2)

                // Імітація отримання даних з JSON (при наявності локального файлу JSON)
                // Тут можна додати логіку роботи з JSON-файлом і даними про підшипники
                
                // Оновлення даних підшипників (приклад)
                VnutrD1 = "59.5 мм"
                ZovnD1 = "148.3 мм"
                Shir1 = "15 мм"
                Vantazh1 = "30500 Н"
                ResursOb1 = "\(round(pow(30500 / Pr1, 3)))"
                ResursGod1 = "\(round((pow(30500 / Pr1, 3)) / (60 * 125)))"

                VnutrD2 = "148.3 мм"
                ZovnD2 = "59.5 мм"
                Shir2 = "18 мм"
                Vantazh2 = "35500 Н"
                ResursOb2 = "\(round(pow(35500 / Pr2, 3)))"
                ResursGod2 = "\(round((pow(35500 / Pr2, 3)) / (60 * 125)))"
            }) {
                Text("Розрахувати")
            }
            .padding()
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
