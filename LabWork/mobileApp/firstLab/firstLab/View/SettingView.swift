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
    @State private var selectedTypeFont: String = "light"
    @State private var valueSizeText: Int = 24
    @State private var currentText: String = ""
    
    @ObservedObject var textViewModel = TextViewModel()
    @ObservedObject var tabSelection  = TabSelectionViewModel()
    
    
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
                    .onAppear
                    {
                        selectedColor = textViewModel.styledText.textColor
                    }
                }
                
                HStack
                {
                    Stepper("Розмір тексту: \(valueSizeText)", value: $valueSizeText, in: 24...60, step: 1)
                        .padding(.leading, 16)
                        .padding(.trailing, 12)
                }
                .padding(.bottom, 8)
                .onAppear
                {
                    valueSizeText = textViewModel.styledText.sizeText
                }
                
                HStack
                {
                    Text("Оберіть тип шрифту")
                        .padding(.leading, 16)
                    
                    Picker(selection: $selectedTypeFont, label: Text(""))
                    {
                        Text("Light").tag("light")
                        Text("Medium").tag("medium")
                        Text("Heavy").tag("heavy")
                    }
                    .pickerStyle(SegmentedPickerStyle())
                    .padding(.trailing, 12)
                    .onAppear
                    {
                        selectedTypeFont = textViewModel.styledText.weightText
                    }
                }
                                
                HStack
                {
                    TextField("Введіть текст", text: $currentText)
                        .padding(6)
                        .background(RoundedRectangle(cornerRadius: 13).stroke(Color.gray, lineWidth: 1)) // Задаємо рамку та скруглення
                        .shadow(radius: 12)
                        .onAppear
                        {
                            currentText = textViewModel.getText()
                        }
                }
                .padding(.horizontal, 15)
                .padding(.bottom, 12)
                .padding(.top, 12)
                
               
                Button
                {
                    //setSett
                    setSettingTextObj()
                    tabSelection.selectedTab = 1 // for go to second tab in ContentView
                }
                label:
                {
                    Text("Вивести текст")
                        .padding(.vertical, 12)
                        .padding(.horizontal, 83)
                        .font(Font.callout.bold())
                }
                .background(Color("MainButtonBG"))
                .foregroundColor(Color.white)
                .cornerRadius(16)
                
                
                Button
                {
                    // save
                    setSettingTextObj()
                    textViewModel.saveSettings()
                }
                label:
                {
                    Text("Зберегти налаштування")
                        .padding(.vertical, 12)
                        .padding(.horizontal, 45)
                        .font(Font.callout.bold())
                }
                .background(Color("MainButtonBG"))
                .foregroundColor(Color.white)
                .cornerRadius(16)
                
                
                Button
                {
                    // del
                    deletedSettingTextObj()
                    textViewModel.saveSettings()
                }
                label:
                {
                    Text("Скинути налаштування")
                        .padding(.vertical, 12)
                        .padding(.horizontal, 50)
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
    
    func setSettingTextObj()
    {
        textViewModel.styledText.text = currentText
        textViewModel.styledText.sizeText = valueSizeText
        textViewModel.styledText.textColor = selectedColor
        textViewModel.styledText.weightText = selectedTypeFont
    }
    
    func deletedSettingTextObj()
    {
        textViewModel.styledText.text = ""
        textViewModel.styledText.sizeText = 24
        textViewModel.styledText.textColor = .black
        textViewModel.styledText.weightText = "light"
    }
    
}

struct SettingView_Previews: PreviewProvider
{
    static var previews: some View
    {
        SettingView(textViewModel: TextViewModel(),
                    tabSelection: TabSelectionViewModel())
    }
}

