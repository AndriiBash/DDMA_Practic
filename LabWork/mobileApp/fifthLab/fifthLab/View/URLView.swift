//
//  URLView.swift
//  fifthLab
//
//  Created by Андрiй on 04.10.2023.
//

import SwiftUI

struct URLView: View
{
    @Environment(\.openURL) var openURL
    @State private var url: String = "https://www.apple.com"
    
    var body: some View
    {
        ScrollView
        {
            VStack
            {
                VStack
                {
                    TextField("Введіть лінк вебсайта", text: $url)
                        .background(Color.white)
                                    .cornerRadius(10)
                                    .padding(12)
                                    .foregroundColor(.black)
                                    .font(.title2)
                                    .overlay(
                                        RoundedRectangle(cornerRadius: 10)
                                            .stroke(Color.gray, lineWidth: 1))
                } //VStack
                .padding(.horizontal, 12)
                
                Button
                {
                    openURL(URL(string: url)!)
                }
                label:
                {
                    Text("Шукати")
                        .padding(.horizontal, 26)
                        .padding(.vertical, 8)
                        .foregroundColor(.white)
                        .background(Color.blue)
                        .cornerRadius(10)
                        .font(.title3.bold())
                } //Button
            } //VStack
            .padding(.top, 300)
        } //ScrollView
        .frame(maxWidth: .infinity, maxHeight: .infinity)
        .navigationBarTitle("URL-open", displayMode: .inline)
    }
}

#Preview
{
    URLView()
}
