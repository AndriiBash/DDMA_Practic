//
//  GestureView.swift
//  secondLab
//
//  Created by Андрiй on 17.09.2023.
//

import SwiftUI

struct GestureView: View
{
    @State private var offset: CGSize = .zero   // координати фігури для перетаскання
    @State private var circleInsideRectangle = false // стан попадання фігури до верхнього синього прямокутника

    var body: some View
    {
        VStack
        {
            // Верхній синій прямокутний
            Rectangle()
                .frame(height: 100)
                .foregroundColor(.blue)
                .cornerRadius(24)
                .shadow(radius: 12)
                .ignoresSafeArea()
            
            Spacer()
            
            Text("Перетягніть круг догори щоб закрити додаток")
                .font(.headline)
            
            // Фігура для перетаскання
            Circle()
                .frame(width: 150, height: 150)
                .foregroundColor(.blue)
                .shadow(radius: 12)
                .offset(offset)
                .gesture(
                    DragGesture()
                        .onChanged // Початок виконання жесту
                    { value in
                        offset = value.translation

                        // Умова попадання фігури до синього прямокутника
                        if value.location.y <= -500
                        {
                            circleInsideRectangle = true
                        }
                        else //
                        {
                            circleInsideRectangle = false
                        }
                    }
                        .onEnded // Кінець виконання жесту
                    { value in
                        withAnimation(Animation.easeOut(duration: 0.5))
                        {
                            offset = .zero
                            circleInsideRectangle = false
                            
                            if value.location.y <= -500
                            {
                                exit(0)
                            }
                        }
                    }
                )
                .opacity(circleInsideRectangle ? 0.75 : 1) // прозорість перетаскємої фігури у разі якщо вона потрапила до синього прямокутнику
                .padding(.bottom, 15)
        }
    }
}
      

struct GestureView_Previews: PreviewProvider
{
    static var previews: some View
    {
        GestureView()
    }
}
