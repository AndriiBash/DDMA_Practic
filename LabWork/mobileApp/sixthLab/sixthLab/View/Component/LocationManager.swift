//
//  LocationManager.swift
//  sixthLab
//
//  Created by Андрiй on 11.10.2023.
//

import Foundation
import CoreLocation

class LocationManager: NSObject, ObservableObject, CLLocationManagerDelegate
{
    @Published var userCity: String?
    private var locationManager = CLLocationManager()
    
    override init() {
        super.init()
        self.locationManager.delegate = self
        self.locationManager.desiredAccuracy = kCLLocationAccuracyNearestTenMeters
        self.locationManager.requestAlwaysAuthorization()
        self.locationManager.startUpdatingLocation()
    }

    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation])
    {
        if let location = locations.last
        {
            let geocoder = CLGeocoder()
            geocoder.reverseGeocodeLocation(location)
            { placemarks, error in
                if let placemark = placemarks?.first
                {
                    if let city = placemark.locality
                    {
                        self.userCity = city
                    }
                }
            }
        }
    }//func locationManager
}
