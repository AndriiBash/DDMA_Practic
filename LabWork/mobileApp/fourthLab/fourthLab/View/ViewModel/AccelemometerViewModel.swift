//
//  AccelemometerModel.swift
//  fourthLab
//
//  Created by Андрiй on 01.10.2023.
//

import Foundation
import CoreMotion

class AccelerometerViewModel: ObservableObject
{
    private let motionManager = CMMotionManager()
    
    @Published var xAcceleration: Double = 0.0
    @Published var yAcceleration: Double = 0.0
    @Published var zAcceleration: Double = 0.0
    
    init()
    {
        if motionManager.isAccelerometerAvailable {
            motionManager.accelerometerUpdateInterval = 1 // Інтервал оновлення (в секундах)
            motionManager.startAccelerometerUpdates(to: .main)
            { accelerometerData, error in
                if let data = accelerometerData
                {
                    self.xAcceleration = data.acceleration.x
                    self.yAcceleration = data.acceleration.y
                    self.zAcceleration = data.acceleration.z
                }
            }
        }
    }
}
