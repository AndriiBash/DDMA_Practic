//
//  AccelerometerView.swift
//  fourthLab
//
//  Created by Андрiй on 01.10.2023.
//

import SwiftUI

struct AccelerometerView: View
{
    @ObservedObject var accelerometerViewModel = AccelerometerViewModel()
    @State private var showInfo = false

    var body: some View
    {
        ScrollView
        {
            VStack
            {
                Text("Значення акселерометру")
                Text("X : \(accelerometerViewModel.xAcceleration)")
                Text("Y : \(accelerometerViewModel.yAcceleration)")
                Text("Z : \(accelerometerViewModel.zAcceleration)")
            }
            .frame(maxWidth: .infinity, maxHeight: .infinity)

        } //ScrollView
        .navigationBarTitle("Акселерометр", displayMode: .inline)
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
                message: Text("Тут ви можете побачити значення акселерометру"))
        }//.alert
    }
}

#Preview {
    AccelerometerView()
}
