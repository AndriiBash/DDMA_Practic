//
//  ContentView.swift
//  firstLab
//
//  Created by Андрiй on 09.09.2023.
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
                SettingView()
            }
            .tabItem()
            {
                Image(systemName: "square.and.pencil")
                Text("Налаштування")
            }
            
            
            VStack
            {
                Text("hello!")
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




/*
 
 /
 import SwiftUI

 struct ContentView: View
 {
     
     @State var goAnimated: Bool = false
     @State var showAlertText: Bool = false
     @State var showAlertMessage: Bool = false
     
     @ObservedObject var mainToggleViewModel = ToggleViewModel()
     
     var body: some View
     {
         TabView
         {
             NavigationView
             {
                 ItemGridView()
             }
             .tabItem()
             {
                 Image(systemName: "airtag")
                 Text("item")
             }
             
             
             VStack
             {
                 VStack
                 {
                     Image(systemName: "globe")
                         .imageScale(.large)
                         .foregroundColor(Color.purple)
                         .padding(.top, 20)
                         .padding(.bottom, 5)
                     
                     Text(goAnimated ? "Poka" : "Privet")
                         .padding(.top, 1)
                         .padding([.horizontal], goAnimated ? 45 : 55)
                         .font(.title)
                     
                     if goAnimated
                     {
                         Text("Ya animation")
                             .font(.title2)
                             .padding(.horizontal, 45)
                     }
                     
                     Button
                     {
                         goAnimated.toggle()
                     }
                     label:
                     {
                         Text("Click me!")
                             .padding(.vertical, 6)
                             .padding(.horizontal, 12)
                             .foregroundColor(Color.black)
                     }.background(Color.white)
                         .cornerRadius(12)
                         .padding(.bottom, 12)
                     
                 }.background(Color("TestColor").opacity(0.2))
                     .cornerRadius(12)
                     .shadow(radius: 24)
                 
                 HStack
                 {
                     Text("hello!")
                     Text("Hello2!")
                     
                 }.padding(.top, 25)
                 
                 if showAlertText
                 {
                     VStack
                     {
                         Text("Error authorization!")
                             .font(.title2.bold())
                             .foregroundColor(Color.red)
                             .opacity(showAlertText ? 2 : 0)
                             .padding(.top, 1)
                     }
                 }
                 
                 
                 Button
                 {
                     showAlertText.toggle()
                 }
                 label:
                 {
                     Text("ShowAlertText")
                 }
                 .padding(1)
                 
                 Button
                 {
                     showAlertMessage = true
                 }
                 label:
                 {
                     Text("ShowAlertMessage")
                 }
                 .padding(1)

                 
                 .alert(isPresented: $showAlertMessage)
                 {
                     Alert(
                         title: Text("TitleName"),
                         message: Text("YourMessage"),
                         primaryButton: .default(Text("ОK")) {
                             // Действия при нажатии кнопки "ОК"
                         },
                         secondaryButton: .cancel(Text("NotOkay")) {
                             // Действия при нажатии кнопки "Отмена"
                         }
                     )
                 }
                 
             }.tabItem()
             {

                 Image(systemName: "macpro.gen3.fill")
                 Text("hello!")
             }
             
             VStack
             {
                 TogleView(viewModel: mainToggleViewModel)
             }
             .tabItem()
             {
                 Image(systemName: "togglepower")
                 Text("ExampleToogle")
             }

             if mainToggleViewModel.isToogler
             {
                 VStack
                 {
                     EmptyView()
                 }
                 .tabItem()
                 {
                     Image(systemName: "40.square")
                     Text("Bool tab")
                 }
             }
             
             
         }.frame(maxWidth: .infinity, maxHeight: .infinity)
             .background(Color.white)
             .animation(Animation.easeInOut(duration: 0.25), value: goAnimated)
             .animation(Animation.easeInOut(duration: 0.4), value: showAlertText)
         
             //.padding(5) // have padding all sides
     }
     
 }

 struct ContentView_Previews: PreviewProvider
 {
     static var previews: some View
     {
         ContentView()
     }
 }

 */
