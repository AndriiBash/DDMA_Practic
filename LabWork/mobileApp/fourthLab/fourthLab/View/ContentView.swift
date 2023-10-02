//
//  ContentView.swift
//  fourthLab
//
//  Created by Андрiй on 01.10.2023.
//

import SwiftUI

struct ContentView: View
{
    var body: some View
    {
        TabView
        {
            
            NavigationView
            {
                MoveCirvleView()
            }
            .tabItem
            {
                Text("Фігура")
                Image(systemName: "circle")
            }
            
            NavigationView
            {
                FlashView()
            }
            .tabItem
            {
                Text("Спалах")
                Image(systemName: "flashlight.on.fill")
            }
            
            NavigationView
            {
                AccelerometerView()
            }
            .tabItem
            {
                Text("Акселерометр")
                Image(systemName: "externaldrive.connected.to.line.below")
            }
            
            NavigationView
            {
                VibrationView()
            }
            .tabItem
            {
                Text("Вібрація")
                Image(systemName: "iphone.radiowaves.left.and.right")
            }
            
        }// TabView
    }
}

#Preview
{
    ContentView()
}
