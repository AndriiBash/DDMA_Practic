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
    @Published var styledText = StyledText(text: "Null",
                                           sizeText: 24,
                                           weightText: "Light",
                                           textColor: Color.black)
    
    private let userSettings = UserDefaults.standard

        
    struct StyledText: Equatable
    {
        var text: String
        var sizeText: Int
        var weightText: String
        var textColor: Color
    }

    init(textInit: StyledText = StyledText(text: "Default Text",
                                           sizeText: 24,
                                           weightText: "Light",
                                           textColor: Color.black))
    {
            
        loadSettings()

        //self.styledText = textInit
        
    }
    
    
    public func loadSettings()
    {
        self.styledText.text = UserDefaults.standard.string(forKey: "text") ?? "Default Text"
        self.styledText.sizeText = UserDefaults.standard.integer(forKey: "sizeText")
        self.styledText.weightText = UserDefaults.standard.string(forKey: "weightText") ?? "light"

        let readColor: String = UserDefaults.standard.string(forKey: "textColor") ?? "black"
        
        switch readColor
        {
        case "black":
            self.styledText.textColor = Color.black
        case "red":
            self.styledText.textColor = Color.red
        case "green":
            self.styledText.textColor = Color.green
        case "blue":
            self.styledText.textColor = Color.blue
        case "yellow":
            self.styledText.textColor = Color.yellow
        default:
            self.styledText.textColor = Color.black
        }
                        
    }
    
    
    public func saveSettings()
    {
        userSettings.set(self.styledText.text, forKey: "text")
        userSettings.set(self.styledText.sizeText, forKey: "sizeText")
        userSettings.set(self.styledText.weightText, forKey: "weightText")

        switch self.styledText.textColor
        {
        case Color.black:
            userSettings.set("black", forKey: "textColor")
        case Color.red:
            userSettings.set("red", forKey: "textColor")
        case Color.green:
            userSettings.set("green", forKey: "textColor")
        case Color.blue:
            userSettings.set("blue", forKey: "textColor")
        case Color.yellow:
            userSettings.set("yellow", forKey: "textColor")
        default:
            userSettings.set("black", forKey: "textColor")
        }
        
        
        
        
    }
    
    
    
    public func printers()
    {
        print("\(String(describing: UserDefaults.standard.string(forKey: "text")))")
        print("\(String(describing: UserDefaults.standard.string(forKey: "sizeText")))")
        print("\(String(describing: UserDefaults.standard.string(forKey: "textColor")))")
        print("\(String(describing: UserDefaults.standard.string(forKey: "weightText")))")


        
        //print("\(String(describing: UserDefaults.standard.string(forKey: "font")))")
    }
    
    
    public func getText() -> String
    {
        return self.styledText.text
    }
    
    
}
