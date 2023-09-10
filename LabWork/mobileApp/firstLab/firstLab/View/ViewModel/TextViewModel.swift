//
//  TextViewModel.swift
//  firstLab
//
//  Created by Андрiй on 10.09.2023.
//

import Foundation
import SwiftUI

class TextViewModel: ObservableObject
{
    @Published var styledText = StyledText(text: "Custom Text",
                                           font: Font.system(size: 14),
                                           textColor: Color.black)

    struct StyledText: Equatable
    {
        var text: String
        var font: Font
        var textColor: Color
    }

    init(textInit: StyledText = StyledText(text: "Default Text",
                                           font: Font.system(size: 16),
                                           textColor: Color.black))
    {
            self.styledText = textInit
    }
}
