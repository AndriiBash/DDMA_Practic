//
//  PainterView.swift
//  eighthLab
//
//  Created by Андрiй on 22.10.2023.
//

import SwiftUI

struct PainterView: View
{
    @State private var SelectedColor: Color = Color.green
    @State private var WidthValue: Double = 25.0
    @State private var lines: [Line] = []
    
    var body: some View
    {
        VStack
        {
            Canvas
            { context, size in
                for line in lines
                {
                    var path = Path()
                    path.addLines(line.points)
                    
                    context.stroke(path, with: .color(line.color),
                                   style: StrokeStyle(lineWidth: line.lineWidth, lineCap: .round, lineJoin: .round))
                }
            }//Canvas
            .gesture(DragGesture(minimumDistance: 0, coordinateSpace: .local)
                .onChanged(
                    { value in
                        
                        let position = value.location
                        
                        if value.translation == .zero
                        {
                            lines.append(Line(points: [position], color: SelectedColor, lineWidth: WidthValue))
                        }
                        else
                        {
                            guard let lastIndex = lines.indices.last else
                            {
                                return
                            }
                            
                            lines[lastIndex].points.append(position)
                        }
                    })//onChanged
            )// gesture
                        
            HStack(spacing: 10)
            {
                Text("Товщина")
                    .padding()
                
                Slider(value: $WidthValue, in: 5.0...100.0, step: 1.0)
                
                ColorPicker("Колір", selection: $SelectedColor)
                    .padding()
            }//HStack setting line's
            .background(Color.black.opacity(0.2))
        }//mainVStack
        .toolbar
        {
            ToolbarItem(placement: .navigationBarTrailing) {
                Button(action:
                {
                    lines = []
                })
                {
                    Image(systemName: "trash.fill")
                }
            } //ToolBarItem
        }//.toolbar
    }// body view
}

#Preview
{
    PainterView()
}
