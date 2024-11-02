import SwiftUI
import Charts

struct ContentView: View {
    @State private var q: String = ""
    @State private var L: String = ""
    @State private var results: [(Double, Double, Double)] = []
    
    var body: some View {
        VStack {
            HStack {
                TextField("Enter q", text: $q)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .padding()
                TextField("Enter L", text: $L)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .padding()
            }
            
            Button("Calculate") {
                calculate()
            }
            .padding()
            
            if !results.isEmpty {
                Chart {
                    ForEach(results, id: \.0) { (x, Q, M) in
                        LineMark(x: .value("x", x), y: .value("Q", Q))
                            .foregroundStyle(Color.red)
                        LineMark(x: .value("x", x), y: .value("M", M))
                            .foregroundStyle(Color.blue)
                    }
                }
                .frame(height: 300)
                
                List(results, id: \.0) { (x, Q, M) in
                    HStack {
                        Text("x: \(x, specifier: "%.2f")")
                        Spacer()
                        Text("Q: \(Q, specifier: "%.2f")")
                        Spacer()
                        Text("M: \(M, specifier: "%.2f")")
                    }
                }
            }
        }
        .padding()
    }
    
    private func calculate() {
        guard let qValue = Double(q), let LValue = Double(L) else { return }
        
        results = []
        let h = LValue / 100
        for i in 0...100 {
            let x = Double(i) * h
            let Q = calculateQ(q: qValue, L: LValue, x: x)
            let M = calculateM(q: qValue, L: LValue, x: x)
            results.append((x, Q, M))
        }
    }
    
    private func calculateQ(q: Double, L: Double, x: Double) -> Double {
        return q * (L / 2 - x)
    }
    
    private func calculateM(q: Double, L: Double, x: Double) -> Double {
        return q * x / 2 * (L - x)
    }
}
