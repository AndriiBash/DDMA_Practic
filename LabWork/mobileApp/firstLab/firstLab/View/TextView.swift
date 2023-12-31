//
//  TextView.swift
//  firstLab
//
//  Created by Андрiй on 10.09.2023.
//

import SwiftUI
import UserNotificationsUI

struct TextView: View
{
    @ObservedObject var mainTextViewModel: TextViewModel      // From main ContentView
    @State private var isContextMenuVisible = false
    
    var fontWeight: Font.Weight {
        switch mainTextViewModel.styledText.weightText
        {
        case "light":
            return .light
        case "medium":
            return .medium
        case "heavy":
            return .heavy
        default:
            return .light
        }
    }
    
    var body: some View
    {
        ScrollView
        {
            Spacer()
        
            Text(mainTextViewModel.styledText.text)
                .padding(.horizontal, 8)
                .foregroundColor(mainTextViewModel.styledText.textColor)
            
                .font(Font.system(size: CGFloat(mainTextViewModel.styledText.sizeText)))
    
                .fontWeight(fontWeight)
            
                .animation(Animation.easeInOut(duration: 0.3), value: mainTextViewModel.styledText)
            
        }
        .navigationTitle("Твій текст")
    }
}

struct TextView_Previews: PreviewProvider
{
    static var previews: some View
    {
        TextView(mainTextViewModel: TextViewModel())
    }
}
