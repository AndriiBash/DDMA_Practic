//
//  PhotoView.swift
//  fifthLab
//
//  Created by Андрiй on 04.10.2023.
//

import SwiftUI

struct PhotoView: View
{
    @State private var image = UIImage(systemName: "photo")!
    @State private var isPickerShow = false

    var body: some View
    {
        ScrollView
        {
            Text("Обери фото")
                .frame(maxWidth: .infinity, maxHeight: .infinity)
            
            ZStack(alignment: Alignment(horizontal: .trailing, vertical: .bottom))
            {
                Image(uiImage: image)
                    .resizable()
                    .aspectRatio(contentMode: .fill)
                    .frame(width: 100, height: 100)
                    .clipped()
                    .cornerRadius(16)
                
                ZStack
                {
                    Button
                    {
                        isPickerShow.toggle()
                    }
                    label:
                    {
                        ZStack
                        {
                            Circle()
                                .frame(width: 50, height: 50)
                                .foregroundColor(.blue)
                                .overlay(
                                    RoundedRectangle(cornerRadius: 25)
                                        .stroke(Color.white, lineWidth: 3))
                            Image(systemName: "camera.fill")
                                .foregroundColor(.white)
                        }
                    }
                    .offset(x: 20, y: 20)
                    .sheet(isPresented: $isPickerShow)
                    {
                        ImagePicker(image: $image)
                    }

                } // In ZStack ZStack
            } //ZStack
            
        }
        .frame(maxWidth: .infinity, maxHeight: .infinity)
        .navigationBarTitle("Перегляд фото", displayMode: .inline)

    }
}

#Preview
{
    PhotoView()
}
