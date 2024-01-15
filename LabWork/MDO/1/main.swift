//
//  main.swift
//  FastSwiftProj
//
//  Created by Андрiй on 15.01.2024.
//

import Foundation
import Cocoa
import SwiftUI
import Charts

struct DataPoint: Identifiable
{
    let id = UUID()
    let x: Double
    let y: Double
}// struct DataPoint

struct Chartview: View
{
    var dataPoints = [DataPoint]()
    
    var body: some View
    {
        VStack
        {
            Chart
            {
                ForEach(dataPoints) { dataPoint in
                    LineMark(x: .value("x", dataPoint.x),
                             y: .value("y", dataPoint.y))
                }
            }
            .chartXAxisLabel("x")
            .chartYAxisLabel("y")
        }// VStack with main chart
        .padding()
        .frame(maxWidth: .infinity, maxHeight: .infinity)
    }
    
}// struct Chartview: View



func findMaximumValue(a: Double, b: Double, c: Double, d: Double, epsilon: Double) -> (maximumValue: Double, argument: Double)
{
    var max = Double.leastNormalMagnitude
    var argMax = 0.0
    
    for x in stride(from: -3.0, to: 2.0, by: epsilon)
    {
        let y = a * pow(x, 3) + b * pow(x, 2) + c * x + d
        
        if y > max
        {
            max = y
            argMax = x
        }
    }
    
    // rounded value to 4 number after ,
    max = round(max * pow(10, 4)) / pow(10, 4)
    argMax = round(argMax * pow(10, 4)) / pow(10, 4)
    
    return (maximumValue: max, argument: argMax)
} // func findMaximumValue -> (Double, double)

func main()
{
    let a = 1.6
    let b = 0.2
    let c = -4.8
    let d = 16.6
    let epsilon = 0.0001
    
    let result = findMaximumValue(a: a, b: b, c: c, d: d, epsilon: epsilon)
    print("Максимальне значення: \(result.maximumValue) досягається при x = \(result.argument)")
    
    var points = [DataPoint]()
    
    for x in stride(from: -3.0, to: 2.0, by: 0.01)
    {
        let y = a * pow(x, 3) + b * pow(x, 2) + c * x + d
        points.append(DataPoint(x: x, y: y))
    }

    let window = NSWindow(contentRect: NSRect(x: 0, y: 0, width: 400, height: 200),
                          styleMask: [.titled, .closable, .resizable],
                          backing: .buffered,
                          defer: false)

    let hostingView = NSHostingView(rootView: Chartview(dataPoints: points))
    window.contentView = hostingView

    //window.contentView = graphView
    window.makeKeyAndOrderFront(nil)

    NSApplication.shared.run()
} // func main

main()
