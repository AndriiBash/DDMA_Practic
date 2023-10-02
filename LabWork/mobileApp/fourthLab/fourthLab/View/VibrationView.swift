//
//  VibrationView.swift
//  fourthLab
//
//  Created by Андрiй on 01.10.2023.
//

import SwiftUI

struct VibrationView: View
{
    @State private var showInfo = false

    var body: some View
    {
        ScrollView
        {
            VStack
            {
                Button
                {
                    let generator = UIImpactFeedbackGenerator(style: .heavy)
                    generator.impactOccurred()
                }
                label:
                {
                    Text("Включити вібрацію")
                        .padding(.horizontal, 12)
                        .padding(.vertical, 16)
                }// Button vibro
                .background(.black)
                .foregroundColor(.white)
                .cornerRadius(16)
                .padding(.top, 16)
            }
        } //ScrollView
        .frame(maxWidth: .infinity, maxHeight: .infinity)
        .navigationBarTitle("Вібрація", displayMode: .inline)
                        .toolbar {
                            ToolbarItem(placement: .navigationBarTrailing) {
                                Button(action:
                                    {
                                        showInfo = true
                                    }) {
                                    Image(systemName: "info.circle")
                                }
                            } //ToolBaritEM
                        }//.toolbar
        .alert(isPresented: $showInfo)
        {
            Alert(
                title: Text("Інформація"),
                message: Text("Тут ви можете включити перевірку вібрації"))
        }//.alert
    }
}

#Preview
{
    VibrationView()
}
