//
//  ContentView.swift
//  NinthLab
//
//  Created by Андрiй on 04.11.2023.
//

import SwiftUI

struct ContentView: View
{
    @State var dollar = Currency(nameCurrency: "Грн/Доллар", sellCurrency: 1, buyCurrence: 1, urlImage: "dollarsign.circle.fill", colorImage: .green)
    @State var euro = Currency(nameCurrency: "Грн/Євро", sellCurrency: 2, buyCurrence: 2, urlImage: "eurosign.circle.fill", colorImage: .orange)
    @State private var isConverterPresent: Bool = false

    var body: some View
    {
        NavigationView
        {
            VStack
            {
                ScrollView
                {
                    VStack(spacing: 24)
                    {
                        MoneyCardView(imageDir: dollar.urlImage, nameMoney: dollar.nameCurrency, sellMoney: dollar.sellCurrency, buyMoney: dollar.buyCurrence, colorImage: dollar.colorImage)
                        MoneyCardView(imageDir: euro.urlImage, nameMoney: euro.nameCurrency, sellMoney: euro.sellCurrency, buyMoney: euro.buyCurrence, colorImage: euro.colorImage)
                    }//VStack with info course
                    .padding(.horizontal, 16)
                    .frame(maxWidth: .infinity, maxHeight: .infinity)
                    
                    
                }//ScrollView
                
                VStack
                {
                    Button
                    {
                        isConverterPresent.toggle()
                    }
                    label:
                    {
                        Image(systemName: "coloncurrencysign.square.fill")
                            .foregroundColor(Color.white)
                        Text("Конвертувати в валюту")
                            .foregroundColor(Color.white)
                            .padding(.vertical)
                    }
                    .frame(maxWidth: .infinity)
                    .background(Color.blue)
                    .cornerRadius(12)
                    .shadow(radius: 12)
                    .padding()
                }// VStack with button
              
            }// Main VStack
            .background(
                   LinearGradient(gradient: Gradient(colors: [Color("1MainGradient"), Color("2MainGradient"), Color("3MainGradient"), Color("4MainGradient")]), startPoint: .top, endPoint: .bottom)
               )
            .navigationBarTitle("Курс від PrivatBank", displayMode: .inline)
            .sheet(isPresented: $isConverterPresent)
            {
                ConverterCurrency(closeStatus: $isConverterPresent, buyDollar: $dollar.buyCurrence, buyEuro: $euro.buyCurrence)
            }


        }// NavigationView
        .onAppear
        {
            setCurrentExchange()
        }
        
    }
    
    func setCurrentExchange()
    {
        let request = URLRequest(url: URL(string: "https://api.privatbank.ua/p24api/pubinfo?exchange&coursid=5")!)
        
        let task = URLSession.shared.dataTask(with: request)
        { data ,response,error in
            
            do
            {
                let jsonArray = try JSONSerialization.jsonObject(with: data!, options: []) as! [[String: Any]]

                for item in jsonArray
                {
                    if let ccy = item["ccy"] as? String
                    {
                        if ccy == "EUR"
                        {
                            if let buy = item["buy"] as? String,
                                let sale = item["sale"] as? String
                            {
                                // need fix this
                                euro.buyCurrence = Double(buy)!
                                euro.sellCurrency = Double(sale)!
                            }
                        }
                        else if ccy == "USD"
                        {
                            if let buy = item["buy"] as? String,
                                let sale = item["sale"] as? String
                            {
                                // also need fix
                                dollar.buyCurrence = Double(buy)!
                                dollar.sellCurrency = Double(sale)!
                            }
                        }
                        
                    }
                }// end for, for parse data
                                             
            }
            catch
            {
                print("Can't parse response")
            }
        }
        task.resume()
    }
    
}

#Preview
{
    ContentView()
}
