//
//  PhoneView.swift
//  fifthLab
//
//  Created by Андрiй on 04.10.2023.
//

import SwiftUI

struct PhoneView: View
{
    @State var numString = "+380660242367"
    var body: some View
    {
        ScrollView
        {
            VStack
            {
                VStack
                {
                    TextField("Введіть номер телефону", text: $numString)
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
                    let formattedString = "tel://" + numString
                    guard let url = URL(string: formattedString) else { return }
                    UIApplication.shared.open(url)
                }
                label:
                {
                    Image(systemName: "phone.arrow.up.right.fill")
                    Text("Подзвонити!")
                }// call button
            } //VStack
            .padding(.top, 300)
        } //ScrollView
        .frame(maxWidth: .infinity, maxHeight: .infinity)
        .navigationBarTitle("URL-open", displayMode: .inline)
    }
}

#Preview
{
    PhoneView()
}
