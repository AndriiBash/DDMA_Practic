//
//  SettingView.swift
//  firstLab
//
//  Created by Андрiй on 09.09.2023.
//

import SwiftUI

struct SettingView: View
{
    @State var secretMessage: Bool = false
    
    @State private var isShowingAuthor = false
    @State var currentText: String = ""
    

    var body: some View
    {
        ScrollView()
        {
            VStack
            {

                Image(systemName: "globe")
                    .imageScale(.large)
                    .foregroundColor(.accentColor)
                    .padding(.top, 30)
                    .padding(.bottom, 500)
                
                
                Text("Hello, world!")
                    .background(Color.red)
                
                if secretMessage
                {
                    Text("aga)")
                }
                
                Button
                {
                    secretMessage.toggle()
                }
                label:
                {
                    Text("hello!")
                        .padding(4)
                }
                .padding(4)
                .background(Color.gray)
                .cornerRadius(16)
                
                
                
                //norm
                
                HStack
                {
                    TextField("Введіть текст", text: $currentText)
                        .padding(6)
                        .background(RoundedRectangle(cornerRadius: 13).stroke(Color.gray, lineWidth: 1)) // Задаємо рамку та скруглення
                        .shadow(radius: 12)
                }
                .padding(.horizontal, 15)
                

                
                Button
                {
                    // send in right tab info text
                }
                label:
                {
                    Text("Вивести текст")
                }
                
            }
            .alert(isPresented: $isShowingAuthor)
            {
                Alert(
                    title: Text("Інформація"),
                    message: Text("Розробник програми студент групи КН-23-1Т Ізбаш Андрій"))
            }
            
            .frame(maxWidth: .infinity, maxHeight: .infinity)

        }
        .navigationBarHidden(false)
        .navigationTitle(Text("Лаб.Робота №1"))
        .navigationBarTitleDisplayMode(.inline)
        .toolbar
        {
            ToolbarItem(placement: .navigationBarTrailing)
            {
                Button(action:
                {
                    isShowingAuthor = true
                })
                {
                    Image(systemName: "info.circle")
                }
            }
        }
        
        /*
        .navigationBarHidden(false)
        .navigationTitle(Text("АйтемыНавигация"))
        .navigationBarTitleDisplayMode(.inline)
        .toolbar {
            ToolbarItem(placement: .navigationBarLeading) {
                Button(action: {
                    // действия КНОПКИ СЕЛВА
                }) {
                    Image(systemName: "arrow.backward")
                }
            }
            
            ToolbarItem(placement: .navigationBarTrailing) {
                Button(action: {
                    // действия для кнопки справа
                }) {
                    Text("ПрАЙТЕМ")
                    
                }
            }
        }
        */
    }
}

struct SettingView_Previews: PreviewProvider
{
    static var previews: some View
    {
        SettingView()
    }
}


/*

 struct ItemGridView: View
 {
     var body: some View
     {

             ScrollView(.vertical, showsIndicators: false)
             {
                 Section(header: Text("Айтемы").font(.title2.bold()).padding(.top, 4))
                 {
                     ForEach(1...15, id: \.self)
                     { index in
                         Text("Элемент \(index)")
                             .font(.title3)
                             .padding()
                             .padding(.horizontal, 35)
                             .background(Color.gray.opacity(0.2))
                             .cornerRadius(10)
                     }.padding(1.5)
                 }
                 Text("Как-же мы постарели, но остались детьми").padding(.top, 20)
             }
             .navigationBarHidden(false)
             .navigationTitle(Text("АйтемыНавигация"))
             .navigationBarTitleDisplayMode(.inline)
             .toolbar {
                 ToolbarItem(placement: .navigationBarLeading) {
                     Button(action: {
                         // действия КНОПКИ СЕЛВА
                     }) {
                         Image(systemName: "arrow.backward")
                     }
                 }
                 
                 ToolbarItem(placement: .navigationBarTrailing) {
                     Button(action: {
                         // действия для кнопки справа
                     }) {
                         Text("ПрАЙТЕМ")
                         
                     }
                 }
             }

         // navigationBarLeading - слева
         // navigationBarTrailing - справа
         // if need big navigation bar нужно всё обернуть в NavigationView
                 
     }
 }

 struct ItemGridView_Previews: PreviewProvider
 {
     static var previews: some View
     {
         ItemGridView()
     }
 }
*/
