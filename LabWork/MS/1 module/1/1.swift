//
//  ContentView.swift
//  MS1
//
//  Created by Андрiй on 02.11.2024.
//

import SwiftUI
import Charts

struct ContentView: View
{
    @State private var initialValue: String = ""
    @State private var endValue: String = ""
    @State private var stepValue: String = ""
    @State private var dataPoints: [(Double, Double)] = []

    var body: some View
    {
        VStack
        {
            TextField("Initial Value", text: $initialValue)
                .textFieldStyle(RoundedBorderTextFieldStyle())
                .padding()
            
            TextField("End Value", text: $endValue)
                .textFieldStyle(RoundedBorderTextFieldStyle())
                .padding()
            
            TextField("Step", text: $stepValue)
                .textFieldStyle(RoundedBorderTextFieldStyle())
                .padding()
            
            Button(action: calculateValues)
            {
                Text("Calculate")
                    .padding()
                    .background(Color.blue)
                    .foregroundColor(.white)
                    .cornerRadius(8)
            }
            .buttonStyle(PlainButtonStyle())
            .padding()
            
            if !dataPoints.isEmpty {
                Chart
                {
                    ForEach(dataPoints, id: \.0)
                    { point in
                        LineMark(
                            x: .value("X", point.0),
                            y: .value("Y", point.1)
                        )
                    }
                }
                .frame(height: 300)
                .padding()
            }
        }
        .padding()
    }
    
    private func calculateValues()
    {
        guard let a = Double(initialValue),
              let b = Double(endValue),
              let h = Double(stepValue), h > 0 else {
            return
        }
        
        dataPoints.removeAll()
        var x = a
        
        while x <= b
        {
            let y1 = -sin(x)
            let y2 = sin(x) - 2 * sin(x + h) + sin(x + 2 * h)
            dataPoints.append((x, y1))
            dataPoints.append((x, y2))
            x += h
        }
    }
}
