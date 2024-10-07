//
//  ContentView.swift
//  aprk
//
//  Created by Андрiй on 07.10.2024.
//

import SwiftUI

struct ContentView: View {
    @State private var Q1: String = ""
    @State private var Si_etl: String = ""
    @State private var result: String = ""
    
    var body: some View {
        VStack(spacing: 20) {
            TextField("Q, кН", text: $Q1)
                .textFieldStyle(RoundedBorderTextFieldStyle())
            
            TextField("[G]", text: $Si_etl)
                .textFieldStyle(RoundedBorderTextFieldStyle())
            
            Button(action: calculateValue) {
                Text("Розрахувати значення")
                    .padding()
                    .background(Color.blue)
                    .foregroundColor(.white)
                    .cornerRadius(10)
            }
            
            Text("Внутрішній діаметр: \(result)")
        }
        .padding()
    }
    
    func calculateValue() {
        guard let Q1Double = Double(Q1), let Si_etlDouble = Double(Si_etl) else {
            result = "Некоректні дані"
            return
        }
        
        let Q = Q1Double * pow(10, 3)
        let T = 0.25 * Q
        let f = 0.4
        var dv = 1.0
        var Y = Q + T / f
        var Sig, t, Sig_ekv: Double
        
        while true {
            Sig = (4 * Q) / (Double.pi * pow(dv, 2))
            t = (4 * T) / (Double.pi * pow(dv, 2))
            Sig_ekv = sqrt(pow(Sig, 2) + 3 * pow(t, 2))
            
            if Sig_ekv <= Si_etlDouble {
                break
            } else {
                dv += 1
            }
        }
        
        result = String(format: "%.2f", dv)
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
