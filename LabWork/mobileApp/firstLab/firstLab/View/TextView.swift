//
//  TextView.swift
//  firstLab
//
//  Created by Андрiй on 10.09.2023.
//

import SwiftUI

struct TextView: View
{
    @ObservedObject var mainTextViewModel: TextViewModel            // From main ContentView

    var body: some View
    {
        ScrollView
        {

            Spacer()

            Text(mainTextViewModel.styledText.text)
                .padding(.horizontal, 10)

                
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