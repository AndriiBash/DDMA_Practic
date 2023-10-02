//
//  MoveCirvleView.swift
//  fourthLab
//
//  Created by Андрiй on 01.10.2023.
//

import SwiftUI
import Foundation

struct MoveCirvleView: View
{
    @State private var circleOffset = CGSize.zero
    @State private var showInfo = false
    @State private var secTime = 10
    @State private var timer: Timer?
    
    var body: some View
    {
        VStack
        {
            VStack
            {
                Text("Рухай фігуру, це весело!")
                    .bold()
                
                Circle()
                    .frame(width: 100, height: 100)
                    .foregroundColor(.pink)
                    .opacity(0.65)
                    .offset(circleOffset)
                    .gesture(
                        DragGesture()
                            .onChanged
                        { value in
                            circleOffset = value.translation
                        }
                            .onEnded
                        { _ in
                            withAnimation(Animation.easeInOut(duration: 0.25))
                            {
                                circleOffset = CGSize.zero
                            }
                        }
                    ) // gesture
                } // top stack
           
                Spacer()
            
                VStack
                {
                    Text("Таймер: [\(secTime) секунд]")
                        .bold()
                        .padding(.top, 26)
                    
                    Button
                    {
                        startTimerAndMoveCircle()
                    }
                    label:
                    {
                        Text("Рухати фігуру за таймером")
                            .padding(.horizontal, 12)
                            .padding(.vertical, 16)
                    } // button mover circle with timer
                    .background(.black)
                    .foregroundColor(.white)
                    .cornerRadius(16)
                    .padding(.bottom, 16)
                    
                } // bottom stack
                .frame(maxWidth: .infinity)
                .background(.black.opacity(0.2))
                .padding(.bottom, 14)
            
              
            }// MainVStack
            .frame(maxWidth: .infinity, maxHeight: .infinity)
            .navigationBarTitle("Фігура", displayMode: .inline)
                            .toolbar {
                                ToolbarItem(placement: .navigationBarTrailing) {
                                    Button(action: 
                                        {
                                            showInfo = true
                                        }) {
                                        Image(systemName: "info.circle")
                                    }
                                } //ToolBaritEM
                            }//.toolbar
            .alert(isPresented: $showInfo)
            {
                Alert(
                    title: Text("Інформація"),
                    message: Text("Тут ви можете рухати фігуру самостійно або по таймеру, у разі закінчення її руху фігура повертається на попереднє місце"))
            }//.alert
    }
    
    
    func startTimerAndMoveCircle()
    {
        secTime = 0
        
        timer = Timer.scheduledTimer(withTimeInterval: 1.0, repeats: true)
        { _ in
            
            if secTime >= Int(TimeInterval(10))
            {
                timer?.invalidate()
                withAnimation(Animation.easeOut(duration: 0.5))
                {
                    circleOffset = CGSize.zero
                }
            }
            else
            {
                withAnimation(Animation.easeOut(duration: 0.5))
                {
                    circleOffset =  CGSize(width: circleOffset.width, height: circleOffset.height + 15)
                }

                secTime += 1
            }
        }
    }// func startTimerAndMoveCircle
}

#Preview
{
    MoveCirvleView()
}
