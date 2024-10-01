import SwiftUI

struct ContentView: View {
    @State private var sigmaHlim_shester: Double = 670
    @State private var sigmaHlim_koleso: Double = 590
    @State private var SH: Double = 1.1
    @State private var KHL_shester: Double = 2.05
    @State private var KHL_koleso: Double = 1.66
    @State private var ZR: Double = 0.95
    @State private var ZV: Double = 1.04
    @State private var KL: Double = 1.0
    @State private var KXH: Double = 1.0
    @State private var result: [String: String] = [:]

    var body: some View {
        VStack {
            Text("Gear Transmission Calculator")
                .font(.title)
                .padding()

            Form {
                Section(header: Text("Input Parameters")) {
                    TextField("SigmaHlim for Gear", value: $sigmaHlim_shester, formatter: NumberFormatter())
                    TextField("SigmaHlim for Wheel", value: $sigmaHlim_koleso, formatter: NumberFormatter())
                    TextField("SH", value: $SH, formatter: NumberFormatter())
                    TextField("KHL for Gear", value: $KHL_shester, formatter: NumberFormatter())
                    TextField("KHL for Wheel", value: $KHL_koleso, formatter: NumberFormatter())
                    TextField("ZR", value: $ZR, formatter: NumberFormatter())
                    TextField("ZV", value: $ZV, formatter: NumberFormatter())
                    TextField("KL", value: $KL, formatter: NumberFormatter())
                    TextField("KXH", value: $KXH, formatter: NumberFormatter())
                }
                
                Button("Calculate") {
                    calculate()
                }
                .padding()

                Section(header: Text("Results")) {
                    ForEach(result.keys.sorted(), id: \.self) { key in
                        HStack {
                            Text(key)
                            Spacer()
                            Text(result[key] ?? "")
                        }
                    }
                }
            }
            .padding()
        }
    }

    func calculate() {
        let sigmaH_shester = (sigmaHlim_shester / SH) * KHL_shester * ZR * ZV * KL * KXH
        let sigmaH_koleso = (sigmaHlim_koleso / SH) * KHL_koleso * ZR * ZV * KL * KXH

        result["Allowable Stress for Gear"] = String(format: "%.3f MPa", sigmaH_shester)
        result["Allowable Stress for Wheel"] = String(format: "%.3f MPa", sigmaH_koleso)

        let Kap = 8847.0
        let U12 = 5.0
        let Pi = 3.1415
        let n1 = 289.0
        let psi_ba = 0.3
        let sigmaHraschet = 880.0

        let numerator = Pi * 1.0 * 1.04 * 1.0
        let denominator = n1 * psi_ba * U12 * pow(sigmaHraschet, 2.0)
        let cubicRootValue = pow(numerator / denominator, 1.0 / 3.0)
        let a = Kap * (U12 + 1) * cubicRootValue

        let standardValues: [Double] = [40, 50, 63, 80, 100, 125, 160, 200]
        let a_standard = standardValues.first { $0 >= a } ?? a

        let m = 2.75
        let Z1_plus_Z2 = (2 * a_standard) / m
        let Z1 = round(Z1_plus_Z2 / (U12 + 1))
        let Z2 = round(Z1_plus_Z2 - Z1)

        let b = psi_ba * a_standard
        let d1 = m * Z1
        let d2 = m * Z2
        let da1 = d1 + 2 * m
        let da2 = d2 + 2 * m

        result["Minimum Center Distance"] = String(format: "%.3f mm", a)
        result["Standard Center Distance"] = String(format: "%.3f mm", a_standard)
        result["Module"] = String(format: "%.3f mm", m)
        result["Gear Teeth Count (Z1)"] = String(format: "%.0f", Z1)
        result["Wheel Teeth Count (Z2)"] = String(format: "%.0f", Z2)
        result["Width of Gear Wheels"] = String(format: "%.3f mm", b)
        result["Pitch Diameter (d1)"] = String(format: "%.3f mm", d1)
        result["Pitch Diameter (d2)"] = String(format: "%.3f mm", d2)
        result["Tip Diameter (da1)"] = String(format: "%.3f mm", da1)
        result["Tip Diameter (da2)"] = String(format: "%.3f mm", da2)
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
