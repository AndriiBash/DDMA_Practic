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
    
    @State private var isOption1Selected = false
    @State private var isOption2Selected = false
    @State private var isOption3Selected = false
    // и так далее для каждого элемента списка

    

    var body: some View
    {
        ScrollView()
        {
            VStack
            {
                //norm
                Spacer()
                
                HStack
                {
                    TextField("Введіть текст", text: $currentText)
                        .padding(6)
                        .background(RoundedRectangle(cornerRadius: 13).stroke(Color.gray, lineWidth: 1)) // Задаємо рамку та скруглення
                        .shadow(radius: 12)
                }
                .padding(.horizontal, 15)
                .padding(.bottom, 12)
                
               
                Button
                {
                    // send in right tab info text
                    print(currentText)
                }
                label:
                {
                    Text("Вивести текст")
                        .padding(.vertical, 12)
                        .padding(.horizontal, 45)
                        .font(Font.callout.bold())
                }
                .background(Color("MainButtonBG"))
                .foregroundColor(Color.white)
                .cornerRadius(16)
                
                
                    Toggle("Опция 1", isOn: $isOption1Selected)
                    Toggle("Опция 2", isOn: $isOption2Selected)
                    Toggle("Опция 3", isOn: $isOption3Selected)
                    // Добавьте другие флажки по аналогии
                
                
                
                
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
        .navigationTitle(Text("Лабораторна Робота №1"))
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
        
    }
}

struct SettingView_Previews: PreviewProvider
{
    static var previews: some View
    {
        SettingView()
    }
}
