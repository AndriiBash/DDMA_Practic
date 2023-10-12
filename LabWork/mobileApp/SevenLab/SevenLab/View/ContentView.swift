//
//  ContentView.swift
//  SevenLab
//
//  Created by Андрiй on 11.10.2023.
//

import SwiftUI
import MapKit
import CoreLocation

struct ContentView: View
{
    @State private var locationManager = CLLocationManager()
    @State private var mapType: MKMapType = .standard
    @State private var rotation: Double = 0
    @State private var pitch: Double = 0

    var body: some View
    {
        VStack
        {
            MapView(mapType: $mapType, rotation: $rotation, pitch: $pitch)
                .accentColor(Color.pink)
                .ignoresSafeArea()
                .onAppear
            {
                locationManager.desiredAccuracy = kCLLocationAccuracyNearestTenMeters
                locationManager.requestWhenInUseAuthorization()
                locationManager.startUpdatingLocation()
            }
            
            Picker("Режим мапи", selection: $mapType)
            {
                Text("Звичайний").tag(MKMapType.standard)
                Text("Супутний").tag(MKMapType.satellite)
                Text("Гібрид").tag(MKMapType.hybrid)
            }
            .padding(.horizontal)
            .pickerStyle(SegmentedPickerStyle())
            
            HStack
            {
                Text("Нахил мапи")
                Slider(value: $rotation, in: 0.0...360.0, step: 1)
            }// HStack
            .padding()
            
            HStack
            {
                Text("Подача мапи")
                Slider(value: $pitch, in: 0.0...50.0, step: 1)
            }// HStack
            .padding()
        }// VStack
    }
}

#Preview
{
    ContentView()
}

