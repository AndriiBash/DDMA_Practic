//
//  GestureView.swift
//  secondLab
//
//  Created by Андрiй on 17.09.2023.
//

import SwiftUI

struct GestureView: View
{
    @State private var offset: CGSize = .zero
    @State private var isAnimation: Bool = true
    @State private var circleInsideRectangle = false

    var body: some View
    {
        VStack
        {
            Rectangle()
                .frame(height: 100)
                .foregroundColor(.blue)
                .cornerRadius(24)
                .shadow(radius: 12)
                .ignoresSafeArea()
            
            Spacer()
            
            Text("Перетягніть круг догори щоб закрити додаток")
                .font(.headline)
            
            Circle()
                .frame(width: 150, height: 150)
                .foregroundColor(.blue)
                .shadow(radius: 12)
                .offset(offset)
                .gesture(
                    DragGesture()
                        .onChanged
                    { value in
                        offset = value.translation
                        isAnimation = true
                        
                        if value.location.y <= -500
                        {
                            circleInsideRectangle = true
                        }
                        else
                        {
                            circleInsideRectangle = false
                        }
                    }
                        .onEnded
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
                .opacity(circleInsideRectangle ? 0.75 : 1)
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
