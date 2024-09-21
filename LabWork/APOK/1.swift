import SwiftUI

struct ContentView: View
{
    @State private var calculations: [Calculation] = []
    
    var body: some View
    {
        VStack
        {
            ZStack
            {
                Color.blue
                    .frame(height: 80)
                    .edgesIgnoringSafeArea(.top)
                
                Text("Калькулятор параметрів")
                    .font(.system(size: 24, weight: .bold))
                    .foregroundColor(.white)
            }
            
            // Таблиця для результатів
            List
            {
                ForEach(calculations)
                { calculation in
                    HStack {
                        Text(calculation.parameter)
                        Spacer()
                        Text(calculation.value)
                    }
                }
            }
            .frame(height: 200)
            
            // Кнопка для обчислень
            Button(action: calculateResults)
            {
                Text("Зробити обчислення")
                    .buttonStyle(PlainButtonStyle())
                    .font(.system(size: 18, weight: .bold))
                    .foregroundColor(.white)
                    .padding()
                    .background(Color.blue)
                    .cornerRadius(8)
            }
            .padding(.top, 20)
        }
        .padding()
    }
    
    // Функція для обчислень
    func calculateResults()
    {
        let T = 161.0
        let n = 285.0
        let nc = 750.0
        let kd1 = 0.99
        let kd2 = 0.97
        let u = 2.5

        
        let P_vyhod = trimToThreeDecimalPlaces(T * n / 9550)
        let P_potr = trimToThreeDecimalPlaces(P_vyhod / 0.95)
        let upriv = trimToThreeDecimalPlaces(nc / n)
        let P_z1 = trimToThreeDecimalPlaces(P_potr * kd1)
        let P_z2 = trimToThreeDecimalPlaces(P_z1 * kd2)
        let n_z2 = trimToThreeDecimalPlaces(720 / u)
        let T_z2 = trimToThreeDecimalPlaces((9550 * P_z2) / n_z2)
        let U_z2 = trimToThreeDecimalPlaces(u * 17)
        
        calculations = [
            Calculation(parameter: "Pz1, кВт", value: String(format: "%.3f", P_z1)),
            Calculation(parameter: "Pz2, кВт", value: String(format: "%.3f", P_z2)),
            Calculation(parameter: "nz2, об/хв", value: String(format: "%.0f", n_z2)),
            Calculation(parameter: "Tz2, Нм", value: String(format: "%.3f", T_z2)),
            Calculation(parameter: "Uz2", value: String(format: "%.3f", U_z2))
        ]
    }
    
    // Допоміжна функція для округлення
    func trimToThreeDecimalPlaces(_ value: Double) -> Double
    {
        return (value * 1000).rounded() / 1000
    }
}

// Модель для результатів обчислень
struct Calculation: Identifiable
{
    let id = UUID()
    let parameter: String
    let value: String
}

struct ContentView_Previews: PreviewProvider
{
    static var previews: some View
    {
        ContentView()
    }
}


