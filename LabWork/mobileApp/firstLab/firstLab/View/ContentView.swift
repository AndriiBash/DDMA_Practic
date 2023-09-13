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
    @ObservedObject var tabSelection  = TabSelectionViewModel()
    
    var body: some View
    {
        TabView(selection: $tabSelection.selectedTab)
        {
            NavigationView
            {
                SettingView(textViewModel: geterStyledText,
                            tabSelection: tabSelection) // get obj textViewModel
            }
            .tabItem()
            {
                Image(systemName: "square.and.pencil")
                Text("Налаштування")
            }
            .tag(0)
                        
            
            NavigationView
            {
                TextView(mainTextViewModel: geterStyledText)    // send obj textViewModel
            }
            .tabItem()
            {
                Image(systemName: "text.viewfinder")
                Text("Вихідний текст")
            }
            .tag(1)
            
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
