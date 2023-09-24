//
//  ContentView.swift
//  thirdLab
//
//  Created by Андрiй on 24.09.2023.
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
                DefaultChartView()
            }
            .tabItem
            {
                Text("Стандартний")
                Image(systemName: "chart.xyaxis.line")
            }
        }
    }
}

#Preview {
    ContentView()
}
