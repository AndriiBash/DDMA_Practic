//
//  CharTabView.swift
//  secondLab
//
//  Created by Андрiй on 17.09.2023.
//

import SwiftUI
import AVKit

struct CharTabView: View
{
    // Зміна для отримання значення гучності
    @State private var currentVolume: Float = AVAudioSession.sharedInstance().outputVolume
    
    @State private var selectedOption: String? = nil

    
    var body: some View
    {
        ScrollView
        {
            Text("Для збільшення жирності символу збільшіть або зменшіть гучність")
                .padding(10)
                .font(.title3)
            
            //Drawing char "E"
            Path
            {
                path in
                
                path.move(to: CGPoint(x: 42, y: 0))
                path.addLine(to: CGPoint(x: 175, y: 0))
                
                path.move(to: CGPoint(x: 42, y: 0))
                path.addLine(to: CGPoint(x: 42, y :300))
                
                path.move(to: CGPoint(x: 42, y: 150))
                path.addLine(to: CGPoint(x: 175, y: 150))
                
                path.move(to: CGPoint(x: 42, y: 300))
                path.addLine(to: CGPoint(x: 175, y: 300))
                
            }
            .stroke(Color.black,
                style: StrokeStyle(lineWidth: CGFloat(currentVolume * 25),
                                   dash: selectedOption == "Непреривна" ? [] : [5]))

            //style: StrokeStyle(lineWidth: 2, dash: [5])
            .padding(.top, 45)
            .onAppear
            {
                // Таймер для оновлення значення кожної секунди
                Timer.scheduledTimer(withTimeInterval: 0.5, repeats: true)
                { timer in
                    currentVolume = AVAudioSession.sharedInstance().outputVolume
                }
            }
            
            VStack(spacing: 5)
            {
                HStack
                {
                    Text("Тип ліній")
                        .font(.title2)
                    
                    Spacer()
                }
                .padding(.horizontal, 14)
                 
                // Стек з radioButton
                HStack
                {
                    RadioButton(optionText: "Пукнтир", selectedOption: $selectedOption)
                        
                    RadioButton(optionText: "Непреривна", selectedOption: $selectedOption)
                    
                    Spacer()
                }
                .padding(.horizontal, 14)
            }
            .padding(.top, 340)
        }
        .navigationTitle("Виведенна буква «E» за допомогою ліній")
    }
}

// своя реалізація классу RadioButton
struct RadioButton: View
{
    var optionText: String
    
    @Binding var selectedOption: String?
    
    var body: some View
    {
        // Кнопка яка включае в себе текст та картинку, та виконує дію передачу аргумента текста кнопки
        Button(action: { selectedOption = optionText })
        {
            HStack
            {
                Image(systemName: selectedOption == optionText ? "largecircle.fill.circle" : "circle")
                Text(optionText)
            }
        }
        .foregroundColor(Color.blue)
        .font(.title3)
        .onAppear
        {
            selectedOption = "Непреривна"
        }
    }
}

struct CharTabView_Previews: PreviewProvider
{
    static var previews: some View
    {
        CharTabView()
    }
}
