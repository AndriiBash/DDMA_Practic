//
//  MoneyCardView.swift
//  NinthLab
//
//  Created by Андрiй on 04.11.2023.
//

import SwiftUI

struct MoneyCardView: View
{
    var imageDir: String
    var nameMoney: String
    var sellMoney: Double
    var buyMoney: Double
    var colorImage: Color
    
    var body: some View
    {
        VStack
        {
            HStack
            {
                Spacer()
                
                Image(systemName: imageDir)
                    .resizable()
                    .aspectRatio(contentMode: .fit)
                    .frame(width: 45, height: 45, alignment: .center)
                    .foregroundColor(colorImage)
                
                Spacer()
                
                VStack
                {
                    Text(nameMoney)
                        .font(.title3.bold())
                    
                    Text("Продаж : \(String(format: "%.3f", sellMoney)) грн.")
                    Text("Купівля : \(String(format: "%.3f", buyMoney)) грн.")

                }//VStack info sell and buy
                .font(.body.bold())
                
                Spacer()
                
            }//HStack with info
            .padding(.vertical)
        }// mainVStack
        .background(.ultraThinMaterial)
        .cornerRadius(12)
        .shadow(radius: 8)
    }
}

#Preview
{
    MoneyCardView(imageDir: "externaldrive.fill.badge.questionmark", nameMoney: "test", sellMoney: 22.22, buyMoney: 33.33, colorImage: .white)
}
