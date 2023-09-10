//
//  ContentView.swift
//  firstLab
//
//  Created by Андрiй on 09.09.2023.
//

import SwiftUI


struct ContentView: View
{
    @ObservedObject var geterStyledText = TextViewModel()
    
    var body: some View
    {
        TabView
        {
            NavigationView
            {
                SettingView(textViewModel: geterStyledText) // get obj textViewModel
            }
            .tabItem()
            {
                Image(systemName: "square.and.pencil")
                Text("Налаштування")
            }
                        
            NavigationView
            {
                TextView(mainTextViewModel: geterStyledText)    // send obj textViewModel
            }
            
            .tabItem()
            {
                Image(systemName: "text.viewfinder")
                Text("Вихідний текст")
            }
        }
        
        //.animation(Animation.easeOut, value: 0.2)
        
    }
    
}

struct ContentView_Previews: PreviewProvider
{
    static var previews: some View
    {
        ContentView()
    }
}
