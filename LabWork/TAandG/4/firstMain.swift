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


struct DataPointF1: Identifiable
{
   let id = UUID()
   let n: Float
   let time: Float
}// struct DataPoint F1 n/time


struct DataPointF2: Identifiable
{
   let id = UUID()
   let n: Float
   let time: Float
}// struct DataPoint F1 n/time


func algo1(n: Float) -> Float
{
    return pow(n, 3)
}// func algo1(n: Float) -> Float


func algo2(n: Float) -> Float
{
    return pow(3, n)
}// func algo2(n: Float) -> Float


struct Chartview: View
{
    var dataPointsF1: [DataPointF1] = []
    var dataPointsF2: [DataPointF2] = []

    
   var body: some View
   {
       VStack
       {
           Chart
           {
               ForEach(dataPointsF1, id: \.id)
               { dataPoint in
                   // time for funcation F1
                   LineMark(x: PlottableValue.value("x", dataPoint.n),
                            y: PlottableValue.value("y", dataPoint.time),
                            series: .value("n-countF1", "timeF1"))
                            .foregroundStyle(Color.red)
                }
               
               ForEach(dataPointsF2, id: \.id)
               { dataPoint in
                   LineMark(x: PlottableValue.value("Week 3", dataPoint.n),
                            y: PlottableValue.value("Orders 3", dataPoint.time),
                            series: .value("n-countF2", "timeF2"))
                   .foregroundStyle(Color.blue)
               }
           }
           
           Text("Red -  f1")
           Text("Blue - f2")
       }// VStack with main chart
       .padding()
       .frame(maxWidth: .infinity, maxHeight: .infinity)
   }
}// struct Chartview: View


func measureTime(block: () -> Void) -> Double
{
    let startTime = DispatchTime.now().uptimeNanoseconds
    block()
    let endTime = DispatchTime.now().uptimeNanoseconds
    let elapsedTime = Double(endTime - startTime) / 1_000_000  // move to second
    return elapsedTime
}// func measureTime(block: () -> Void) -> Double


func main()
{
    let sizes = [10, 20, 30, 50, 100, 200] // size's input data
    var pointsF1: [DataPointF1] = []
    var pointsF2: [DataPointF2] = []

    print("n\tf1(n) time\tf2(n) time\tTotal time")

    for size in sizes
    {
        let time1 = measureTime
        {
            _ = algo1(n: Float(size))
        }
        
        let time2 = measureTime
        {
            _ = algo2(n: Float(size))
        }

        let totalTime = time1 + time2
        
        pointsF1.append(DataPointF1(n: Float(size), time: Float(time1)))
        pointsF2.append(DataPointF2(n: Float(size), time: Float(time2)))

        // Cout result
        print("\(size)\t\(String(format: "%.8f", time1))\t\(String(format: "%.8f", time2))\t\(String(format: "%.8f", totalTime))")
    }
    
    let window = NSWindow(contentRect: NSRect(x: 0, y: 0, width: 400, height: 200),
                          styleMask: [.titled, .closable, .resizable],
                          backing: .buffered,
                          defer: false)
  
    let hostingView = NSHostingView(rootView: Chartview(dataPointsF1: pointsF1, dataPointsF2: pointsF2))
    window.contentView = hostingView
  
    //window.contentView = graphView
    window.makeKeyAndOrderFront(nil)
  
    NSApplication.shared.run()
}// func main()

main()
