//
//  DefaultChart.swift
//  thirdLab
//
//  Created by Андрiй on 23.09.2023.
//

import SwiftUI
import Charts
import Foundation

struct DefaultChartView: View
{
    @State private var alertIsShow = false
    @State private var avarageIsShow = false
    @State private var averageValueY: Double = 0.0
    
    @State var dataChart: [FormulaChartData] = []

    @State var startValue = "0"
    @State var endValue   = "50"
    @State var stepValue  = "0.1"
    
    private let userSettings = UserDefaults.standard
    
    var body: some View
    {
        ScrollView
        {
            VStack
            {
                Chart(dataChart)
                { d in
                    LineMark(x: .value("x", d.x), y: .value("y", d.y))
                                        
                    // показати або сховати середнє значення на графіку
                    if avarageIsShow
                    {
                        RuleMark(y: .value("Середнє значення", averageValueY))
                            .foregroundStyle(.green)
                            .annotation(position: .bottom, alignment: .bottomLeading)
                            {
                                Text("  Середнє значення [\(averageValueY)]  ")
                                    .foregroundColor(.white)
                                    .background(.black.opacity(0.35))
                                    .cornerRadius(12)
                                    .padding(6)
                                    .padding(.horizontal, 12)
                            }
                    }
                    
                }
                .aspectRatio(1, contentMode: .fit)
                
                Toggle(avarageIsShow ? "Сховати середнє значення у" : "Показати середнє значення у", isOn: $avarageIsShow)
                    .padding(.top, 6)
            }
            .padding()
            
            VStack(spacing: 12)
            {
                TextField("Введіть початок інтервалу", text: $startValue)
                    .padding()
                    .background(RoundedRectangle(cornerRadius: 18).stroke(Color.gray, lineWidth: 1))
                    .keyboardType(.numberPad)
                
                TextField("Введіть кінець інтервалу", text: $endValue)
                    .padding()
                    .background(RoundedRectangle(cornerRadius: 18).stroke(Color.gray, lineWidth: 1))
                    .keyboardType(.numberPad)
                
                TextField("Введіть кроки розрахування", text: $stepValue)
                    .padding()
                    .background(RoundedRectangle(cornerRadius: 18).stroke(Color.gray, lineWidth: 1))
                    .keyboardType(.numberPad)
            }
            .padding(.horizontal, 16)

            
            HStack
            {
                VStack(spacing: 15)
                {
                    
                    Button
                    {
                        setNewValues()
                    }
                    label:
                    {
                        Text("Зобразити")
                            .padding(.vertical, 8)
                            .padding(.horizontal, 16)

                    }
                    .frame(maxWidth: .infinity)
                    .background(.black)
                    .foregroundColor(.white)
                    .cornerRadius(12)
                    .shadow(radius: 12)
                    
                    
                    Button
                    {
                        saveSetting()
                    }
                    label:
                    {
                        Text("Зберегти налаштування")
                            .padding(.vertical, 8)
                            .padding(.horizontal, 16)
                    }
                    .frame(maxWidth: .infinity)
                    .background(.black)
                    .foregroundColor(.white)
                    .cornerRadius(12)
                    .shadow(radius: 12)
                    
                    
                    Button
                    {
                        loadSetting()
                    }
                    label:
                    {
                        Text("Завантажити налаштування")
                            .padding(.vertical, 8)
                            .padding(.horizontal, 16)
                    }
                    .frame(maxWidth: .infinity)
                    .background(.black)
                    .foregroundColor(.white)
                    .cornerRadius(12)
                    .shadow(radius: 12)
                    
                    
                    Button
                    {
                        clearSetting()
                    }
                    label:
                    {
                        Text("Скинути налаштування")
                            .padding(.vertical, 8)
                            .padding(.horizontal, 16)
                    }
                    .frame(maxWidth: .infinity)
                    .background(.black)
                    .foregroundColor(.white)
                    .cornerRadius(12)
                    .shadow(radius: 12)
                    
                }
            }
            .padding(.horizontal, 18)
            .padding(.top, 26)
            
        }
        .navigationTitle(Text("Формула y = 6 ∙ sin (x) ∙ x "))
        .navigationBarTitleDisplayMode(.inline)
        .onAppear
        {
            setNewValues()
        }
        
        .alert(isPresented: $alertIsShow)
        {
        Alert(
            title: Text("Помилка"),
            message: Text("Потрібно ввести тільки цілі значення у поля"),
            dismissButton: .default(Text("OK"))
            )
        }
    }
    
    
    func setNewValues()
    {
        dataChart = [] // для очистку списку значень координат
        
        if let startValueInt = Int.Stride(startValue), let endValueInt = Int(endValue), let stepValueDouble = Double(stepValue)
        {
            // Додати дані для функції y = 6 ∙ sin(x) ∙ x на інтервалі [0..50] з кроком 0.1
            for x in stride(from: Double(startValueInt), through: Double(endValueInt), by: stepValueDouble)
            {
                let y = 6 * sin(x) * x
                dataChart.append(FormulaChartData(x: Double(x), y: y))
            }
            
            // Задаємо нове середнє значення
            let sum = dataChart.reduce(0) { $0 + $1.y }
            let count = Double(dataChart.count)
            
            if count > 0
            {
                let average = sum / count
                averageValueY = average // Зберігаємо середнє значення у @State властивості
            }
        }
        else
        {
            alertIsShow = true
        }
    }
    
    
    func saveSetting()
    {
        userSettings.set(startValue, forKey: "startValueSet")
        userSettings.set(endValue,   forKey: "endValueSet")
        userSettings.set(stepValue,  forKey: "stepValueSet")
    }
    
    
    func loadSetting()
    {
        startValue = UserDefaults.standard.string(forKey: "startValueSet") ?? "0"
        endValue = UserDefaults.standard.string(forKey: "endValueSet") ?? "20"
        stepValue = UserDefaults.standard.string(forKey: "stepValueSet") ?? "0.1"
    }
    
    
    func clearSetting()
    {
        startValue = "0"
        endValue   = "20"
        stepValue  = "0.1"
        
        saveSetting()
    }
}

// Структурм для значень у графік
struct FormulaChartData: Identifiable
{
    let id = UUID()
    var x: Double
    var y: Double
}

#Preview
{
    DefaultChartView()
}
