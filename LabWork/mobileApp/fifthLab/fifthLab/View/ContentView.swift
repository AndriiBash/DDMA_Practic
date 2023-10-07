//
//  ContentView.swift
//  fifthLab
//
//  Created by Андрiй on 04.10.2023.
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
                PhotoView()
            }
            .tabItem
            {
                Text("Галерея")
                Image(systemName: "photo.circle")
            }
            
            NavigationView
            {
                URLView()
            }
            .tabItem
            {
                Text("URL")
                Image(systemName: "ellipsis.curlybraces")
            }
            
            NavigationView
            {
                PhoneView()
            }
            .tabItem
            {
                Text("Дзвінок")
                Image(systemName: "phone.circle")
            }
        } //TabView
    } // body
}

#Preview
{
    ContentView()
}
