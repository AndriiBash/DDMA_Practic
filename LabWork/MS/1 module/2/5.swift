import SwiftUI
import Charts

struct Result: Hashable {
    let time: Double
    let exact: Double
    let approx2: Double
    let approx4: Double
    let approx6: Double
}

struct ContentView: View {
    @State private var x0: String = ""
    @State private var v0: String = ""
    @State private var k: String = ""
    @State private var tk: String = ""
    @State private var m: String = ""
    
    @State private var results: [Result] = []
    
    var body: some View {
        ScrollView {
            TextField("Initial Position (x0)", text: $x0)
                .textFieldStyle(RoundedBorderTextFieldStyle())
                .padding()
            
            TextField("Initial Velocity (v0)", text: $v0)
                .textFieldStyle(RoundedBorderTextFieldStyle())
                .padding()
            
            TextField("Constant (k)", text: $k)
                .textFieldStyle(RoundedBorderTextFieldStyle())
                .padding()
            
            TextField("Time (tk)", text: $tk)
                .textFieldStyle(RoundedBorderTextFieldStyle())
                .padding()
            
            TextField("Mass (m)", text: $m)
                .textFieldStyle(RoundedBorderTextFieldStyle())
                .padding()
            
            Button("Calculate") {
                calculate()
            }
            .padding()
            
            if !results.isEmpty {
                List(results, id: \.self) { result in
                    HStack {
                        Text("t: \(String(format: "%.1f", result.time))")
                        Spacer()
                        Text("Exact: \(String(format: "%.4f", result.exact))")
                        Spacer()
                        Text("Approx 2: \(String(format: "%.4f", result.approx2))")
                        Spacer()
                        Text("Approx 4: \(String(format: "%.4f", result.approx4))")
                        Spacer()
                        Text("Approx 6: \(String(format: "%.4f", result.approx6))")
                    }
                }
                .padding()
                
                Chart {
                    ForEach(results, id: \.self) { result in
                        LineMark(
                            x: .value("Time (t)", result.time),
                            y: .value("Exact Value", result.exact)
                        )
                        .foregroundStyle(Color.blue)
                        LineMark(
                            x: .value("Time (t)", result.time),
                            y: .value("Approx 2", result.approx2)
                        )
                        .foregroundStyle(Color.red)
                        LineMark(
                            x: .value("Time (t)", result.time),
                            y: .value("Approx 4", result.approx4)
                        )
                        .foregroundStyle(Color.green)
                        LineMark(
                            x: .value("Time (t)", result.time),
                            y: .value("Approx 6", result.approx6)
                        )
                        .foregroundStyle(Color.orange)
                    }
                }
                .frame(height: 300)
                .padding()
                
                // Textual Output
                VStack(alignment: .leading) {
                    Text("Results Summary:")
                        .font(.headline)
                        .padding(.top)
                    
                    ForEach(results, id: \.self) { result in
                        Text("At time \(String(format: "%.1f", result.time)): Exact = \(String(format: "%.4f", result.exact)), Approx 2 = \(String(format: "%.4f", result.approx2)), Approx 4 = \(String(format: "%.4f", result.approx4)), Approx 6 = \(String(format: "%.4f", result.approx6))")
                    }
                }
                .padding()
            }
        }
        .padding()
    }
    
    private func calculate() {
        guard let x0 = Double(self.x0),
              let v0 = Double(self.v0),
              let k = Double(self.k),
              let tk = Double(self.tk),
              let m = Double(self.m) else { return }
        
        var resultRows: [Result] = []
        
        let c2 = (x0 * k - v0) / (2 * k)
        let c1 = x0 - c2
        var t = 0.0
        
        while t <= tk {
            let exactX = x_tocnoe(t: t, c1: c1, c2: c2, k: k)
            let approx2 = x2(t: t, k0: x0, k1: v0)
            let approx4 = x4(t: t, k0: x0, k1: v0, k2: k * k * x0, k3: k * k * v0)
            let approx6 = x6(t: t, k0: x0, k1: v0, k2: k * k * x0, k3: k * k * v0)
            
            resultRows.append(Result(time: t, exact: exactX, approx2: approx2, approx4: approx4, approx6: approx6))
            
            t += 0.1
        }
        
        results = resultRows
    }
    
    private func x_tocnoe(t: Double, c1: Double, c2: Double, k: Double) -> Double {
        return c1 * exp(k * t) + c2 * exp(-k * t)
    }
    
    private func x2(t: Double, k0: Double, k1: Double) -> Double {
        return k0 + k1 * t
    }
    
    private func x4(t: Double, k0: Double, k1: Double, k2: Double, k3: Double) -> Double {
        return k0 + k1 * t + (k2 * t * t) / fact(n: 2) + (k3 * t * t * t) / fact(n: 3)
    }
    
    private func x6(t: Double, k0: Double, k1: Double, k2: Double, k3: Double) -> Double {
        return k0 + k1 * t + (k2 * t * t) / fact(n: 2) + (k3 * t * t * t) / fact(n: 3)
    }
    
    private func fact(n: Int) -> Double {
        return (1...n).reduce(1, { $0 * Double($1) })
    }
}
