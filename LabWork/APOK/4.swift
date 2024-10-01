import SwiftUI

struct ContentView: View {
    @State private var val1: Double = 0
    @State private var val2: Double = 0
    
    // Початкові параметри
    let Tz1: Double = 217.9
    let Tz2: Double = 55.03
    let d1: Double = 62
    let b: Double = 30
    
    var body: some View {
        VStack {
            Text("Результати обчислення:")
                .font(.title)
            
            Text("Діаметр першого валу: \(val1, specifier: "%.2f") мм")
            Text("Діаметр другого валу: \(val2, specifier: "%.2f") мм")
            
            Button(action: {
                calculate()
            }) {
                Text("Обчислити")
                    .padding()
                    .background(Color.blue)
                    .foregroundColor(.white)
                    .cornerRadius(10)
            }
            .padding()
        }
        .padding()
    }
    
    func calculate() {
        // Розрахунки для першого валу
        let Pokr1 = (2 * Tz1 * 1000) / ceil(d1)
        let Pr1 = Pokr1 * 0.36397 * 0.2125
        let Poc1 = Pokr1 * 0.2125
        let Rcx = Pokr1 / 2
        let Rax = Rcx
        let a1 = b + 2 * 10 + (20 / 2) * 2
        let a1half = a1 / 2
        let Mx1 = Rax * a1half
        let Ray = (Pr1 * a1half) / (2 * a1half)
        let My1 = Ray * a1half
        let Mizg = sqrt(pow(Mx1, 2) + pow(My1, 2))
        
        var val1Local = 5.0
        var gamma_ekv = 101.0
        var gamma_izg: Double = 0
        var tau1: Double = 0
        
        repeat {
            val1Local += 5
            gamma_izg = max(Mx1, My1) / (0.1 * pow(val1Local, 3))
            tau1 = (Tz1 * 1000) / (0.2 * pow(val1Local, 3))
            gamma_ekv = sqrt(pow(gamma_izg, 2) + 3 * pow(tau1, 2))
        } while gamma_ekv >= 100
        
        val1 = val1Local
        
        // Розрахунки для другого валу
        var val2Local = 5.0
        var gamma_ekv2 = 101.0
        var gamma_izg2: Double = 0
        var tau2: Double = 0
        
        repeat {
            val2Local += 5
            gamma_izg2 = max(Mx1, My1) / (0.1 * pow(val2Local, 3))
            tau2 = (Tz2 * 1000) / (0.2 * pow(val2Local, 3))
            gamma_ekv2 = sqrt(pow(gamma_izg2, 2) + 3 * pow(tau2, 2))
        } while gamma_ekv2 >= 100
        
        val2 = val2Local
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
