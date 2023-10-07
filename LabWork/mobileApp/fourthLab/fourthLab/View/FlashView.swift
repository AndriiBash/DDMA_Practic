//
//  FlashView.swift
//  fourthLab
//
//  Created by Андрiй on 01.10.2023.
//

import SwiftUI
import AVFoundation

struct FlashView: View
{
    @State private var isOnFlashlight = false
    @State private var showInfo = false
    @State var avSession = AVCaptureSession()
    
    var body: some View
    {
        ScrollView
        {
            VStack
            {
                Toggle(isOnFlashlight ? "Виключити фонарик" : "Включити фонарик", isOn: $isOnFlashlight)
                    .foregroundColor(isOnFlashlight ? Color.black : Color.white)
                    .padding()
                    .onChange(of: isOnFlashlight)
                    { newValue in
                        if newValue
                        {
                            turnOnFlashlight()
                        }
                        else
                        {
                            turnOffFlashlight()
                        }
                    }
                    .onAppear
                    {
                        setupFlashlight()
                    }
                
                     
                Image(systemName: isOnFlashlight ? "flashlight.on.fill" : "flashlight.off.fill")
                    .resizable()
                    .frame(width: 70, height: 160)
                    .foregroundColor(isOnFlashlight ? Color.black : Color.white)
                
            } //VStack

        } //ScrollView
        .frame(maxWidth: .infinity, maxHeight: .infinity)
        .background(isOnFlashlight ? Color.white : Color.black)
        .navigationBarTitle("Спалах", displayMode: .inline)
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
                message: Text("Тут ви можете включити або виключити фонарик"))
        }//.alert
    }
    
    // Налаштування фонарика
    func setupFlashlight()
    {
        guard let device = AVCaptureDevice.default(for: AVMediaType.video) else
        {
            print("Фонарик не знайдено!")
            return
        }
            
        do
        {
            let avInput = try AVCaptureDeviceInput(device: device)
            avSession.addInput(avInput)
            try device.lockForConfiguration()
            device.torchMode = .off
            device.unlockForConfiguration()
        }
        catch
        {
            print("Помилка налаштування фонарика: \(error.localizedDescription)")
        }
    }
    
    // Включення фонарика
    func turnOnFlashlight()
    {
            guard let device = AVCaptureDevice.default(for: AVMediaType.video)
            else
        {
            print("Фонарик не знайдено!")
            return
        }
            
        do
        {
            try device.lockForConfiguration()
            device.torchMode = .on
            device.unlockForConfiguration()
            print("Фонарик працює!")
        }
        catch
        {
            print("Помилка включення фонарика: \(error.localizedDescription)")
        }
    }
    
    // Виключення фонарика
    func turnOffFlashlight()
    {
            guard let device = AVCaptureDevice.default(for: AVMediaType.video)
            else
        {
            print("Фонарик не знайдено!")
            return
        }
            
        do
        {
            try device.lockForConfiguration()
            device.torchMode = .off
            device.unlockForConfiguration()
            print("Фонарик виключен!")
        }
        catch
        {
            print("Помилка виключення фонарика: \(error.localizedDescription)")
        }
    }
}

#Preview 
{
    FlashView()
}
