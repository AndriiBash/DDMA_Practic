//
//  CustomGridView.swift
//  sixthLab
//
//  Created by Андрiй on 09.10.2023.
//

import SwiftUI

struct WeatherInfoGrid: View
{
    var image: String
    var title: String
    var information: String
    
    var body: some View
    {
        VStack
        {
            Text(title)
                .padding(.vertical, 12)
                .padding(.horizontal, 4)
            
            Spacer()
            
            HStack
            {
                Image(systemName: image)
                    .resizable()
                    .aspectRatio(contentMode: .fit)
                    .frame(maxWidth: 35, maxHeight: 35)
                
                Text(information)
                    .bold()
            }
            
            Spacer()
        }
        .frame(width: screen.width * 0.35, height: screen.height * 0.17)
        .background(Color.black.opacity(0.2))
        .cornerRadius(16)
        .shadow(radius: 12)
    }
}

#Preview
{
    WeatherInfoGrid(image: "", title: "",  information: "")
}
