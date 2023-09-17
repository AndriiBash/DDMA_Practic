//
//  ContentView.swift
//  secondLab
//
//  Created by Андрiй on 17.09.2023.
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
                CharTabView()
            }
            .tabItem()
            {
                Image(systemName: "e.circle")
                Text("Символ Е")
            }
            
            GestureView()
            .tabItem
            {
                Image(systemName: "hand.draw")
                Text("Жести")
            }
            
            
            
            
            
            
            
        }
        
      
    }
}

struct ContentView_Previews: PreviewProvider
{
    static var previews: some View
    {
        ContentView()
    }
}
