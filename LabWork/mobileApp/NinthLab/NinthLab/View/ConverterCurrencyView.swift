//
//  ConverterCurrency.swift
//  NinthLab
//
//  Created by Андрiй on 04.11.2023.
//

import SwiftUI

struct ConverterCurrencyView: View
{
    @Binding var closeStatus: Bool
    @Binding var buyDollar: Double
    @Binding var buyEuro: Double

    @State private var writeMoney: String = "0"
    @State private var isInvalidInputVisible = false
    
    var body: some View
    {
        NavigationView
        {
            VStack
            {
                Spacer()
                
                VStack(spacing: 12)
                {
                    Text("\((Double(writeMoney) ?? 0)/buyDollar) доларів")
                        .padding(.top)
                    
                    Text("\((Double(writeMoney) ?? 0)/buyEuro) євро")
                        .padding(.bottom)
                }//with info about currency convert
                .frame(maxWidth: .infinity)
                .background(Color.accentColor)
                .foregroundColor(Color.white)
                .cornerRadius(12)
                .padding(.horizontal, 12)
                .padding(.vertical, 12)
                .font(.body.bold())

                Spacer()
                
                VStack
                {
                    Text("Кількість гривень")
                    
                    HStack
                    {
                        TextField("0", text: $writeMoney)
                            .multilineTextAlignment(.trailing)
                            .keyboardType(.numberPad)
                            .onChange(of: writeMoney)
                            { newValue, _ in
                                withAnimation(Animation.easeIn(duration: 0.5))
                                {
                                    if Double(writeMoney) == nil && !writeMoney.isEmpty
                                    {
                                        isInvalidInputVisible = true
                                    }
                                    else
                                    {
                                        isInvalidInputVisible = false
                                    }
                                }
                            }
                        
                        Text("грн")
                    }//Text field with write money
                    .font(.body.bold())
                    .padding(.horizontal, 128)
                    
                    if isInvalidInputVisible
                    {
                        Text("Конвертер не може містити символів")
                            .foregroundColor(.red)
                    }
                }//VStack with converter
                .padding(.bottom)
 
            }//MainVStack with all
            .navigationBarTitle("Конвертер", displayMode: .inline)
            .toolbar
            {
                ToolbarItem(placement: .navigationBarTrailing)
                {
                    Button
                    {
                        closeStatus = false
                    }
                    label:
                    {
                       Text("Закрити")
                            .foregroundColor(Color.blue)
                    }
                }
            }
        }//NavigationView
    }// body
}

struct ConverterCurrency_Previews: PreviewProvider
{
    @State static var closeStatus = false
    @State static var buyDollar = 2.2
    @State static var buyEuro = 2.2
    
    static var previews: some View
    {
        ConverterCurrencyView(closeStatus: $closeStatus, buyDollar: $buyDollar, buyEuro: $buyEuro)
    }
    
}
