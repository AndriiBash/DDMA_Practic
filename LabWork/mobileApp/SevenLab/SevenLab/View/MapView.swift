//
//  MapView.swift
//  SevenLab
//
//  Created by Андрiй on 11.10.2023.
//

import SwiftUI
import MapKit
import CoreLocation

struct MapView: UIViewRepresentable
{
    @Binding var mapType: MKMapType
    @Binding var rotation: Double
    @Binding var pitch: Double
    
    func makeUIView(context: Context) -> MKMapView
    {
        let mapView = MKMapView()
        return mapView
    }
        
    func updateUIView(_ uiView: MKMapView, context: Context)
    {
        uiView.showsUserLocation = true
                        
        DispatchQueue.main.async
        {
            uiView.mapType = mapType
            uiView.camera.heading = rotation
            uiView.camera.pitch = pitch
        }
    }
    
}
