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
            .stroke(Color.black, lineWidth: CGFloat(currentVolume * 25))
            .padding(.top, 45)
            .onAppear
            {
                // Таймер для оновлення значення кожної секунди
                Timer.scheduledTimer(withTimeInterval: 0.5, repeats: true)
                { timer in
                    currentVolume = AVAudioSession.sharedInstance().outputVolume
                }
            }
            
        }
        .navigationTitle("Виведенна буква «E» за допомогою ліній")
        
    }
}

struct CharTabView_Previews: PreviewProvider
{
    static var previews: some View
    {
        CharTabView()
    }
}
