//
//  SettingView.swift
//  firstLab
//
//  Created by Андрiй on 09.09.2023.
//

import SwiftUI

struct SettingView: View
{
    @State private var isShowingAuthor: Bool = false
    @State private var selectedColor: Color = Color.black
    @State private var valueSizeText: Int = 6
    @State private var currentText: String = ""
    
    @ObservedObject var textViewModel = TextViewModel()
    
    var body: some View
    {
        ScrollView()
        {
            VStack
            {
                Spacer()
                
                HStack
                {
                    Text("Оберіть колір: ")
                        .padding(.leading, 16)
                    
                    Spacer()

                    Picker(selection: $selectedColor, label: Text(""))
                    {
                        Text("Чорний").tag(Color.black)
                        Text("Червоний").tag(Color.red)
                        Text("Зелений").tag(Color.green)
                        Text("Блакитний").tag(Color.blue)
                        Text("Жовтий").tag(Color.yellow)
                    }
                    .pickerStyle(MenuPickerStyle())
                }
                
                HStack
                {
                    Stepper("Розмір тексту: \(valueSizeText)", value: $valueSizeText, in: 6...40, step: 1)
                        .padding(.leading, 16)
                        .padding(.trailing, 12)
                }
                                
                HStack
                {
                    TextField("Введіть текст", text: $currentText)
                        .padding(6)
                        .background(RoundedRectangle(cornerRadius: 13).stroke(Color.gray, lineWidth: 1)) // Задаємо рамку та скруглення
                        .shadow(radius: 12)
                }
                .padding(.horizontal, 15)
                .padding(.bottom, 12)
                .padding(.top, 12)
                
               
                Button
                {
                    // set right info in styled text obj
                    textViewModel.styledText.text = currentText
                    textViewModel.styledText.textSize = valueSizeText
                    textViewModel.styledText.textColor = selectedColor
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
        SettingView(textViewModel: TextViewModel())
    }
}
