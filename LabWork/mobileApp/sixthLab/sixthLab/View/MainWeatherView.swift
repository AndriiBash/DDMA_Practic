//
//  MainWeatherView.swift
//  sixthLab
//
//  Created by Андрiй on 07.10.2023.
//

import SwiftUI

struct MainWeatherView: View
{
    @State private var cityStatic = ""
    @State private var cityWeather = ""
    @State private var country = ""
    @State private var mainRain = ""
    @State private var desctiptionRain = ""
    
    @State private var humidity:    Int = 0
    @State private var windSpeed:   Double = 0.0
    @State private var temperature: Double = 0.0
    
    //@StateObject private var locationManager = LocationManager()
    @StateObject private var locationManager = LocationManager()
    
    
    let layot = [GridItem(.adaptive(minimum: screen.width/2.4))]
    
    var body: some View
    {
        VStack
        {
            ScrollView(showsIndicators: false)
            {
               // Spacer()
                
                VStack
                {
                    Text(!country.isEmpty ? "\(country)/\(cityStatic) \(getFlag(country: country))" : "Почніть шукати місто")
                        .font(.title2.bold())
                        .padding(.vertical)
                    
                    if !country.isEmpty
                    {
                        VStack
                        {
                            LazyVGrid(columns: layot, spacing: 20)
                            {
                                WeatherInfoGrid(image: "thermometer.medium", title: "Температура", information: String(format: "%.2f °C", temperature - 273.15))
                                WeatherInfoGrid(image: "humidity.fill", title: "Вологість",information: String(humidity) + "%")
                                WeatherInfoGrid(image: "wind", title: "Швидкість вітру", information: String(format: "%.0f", windSpeed) + " м/с")
                                WeatherInfoGrid(image: "aqi.low", title: "???", information: String(format: "%.0f", windSpeed) + "кг/с")
                            }
                            .padding(.vertical)
                            .background(Color("Chernika"))
                            .cornerRadius(12)
                            .shadow(radius: 12)
                        }//VStack with info
                        
                        Text("☁️ Взагалі: \(mainRain) [\(desctiptionRain)]")
                            .padding(.top, 12)
                            .padding(.bottom, 16)
                            .font(.subheadline.bold())
                    }
                    
                }//VStack
                .frame(maxWidth: .infinity)
                .background(Color("DeepIndigo"))
                .foregroundColor(.white)
                .font(.body.bold())
                .cornerRadius(12)
                .padding(.top, 15)
                .padding(.horizontal)
                .shadow(radius: 14)
            }//ScrollView
            .frame(maxWidth: .infinity, maxHeight: .infinity)
            
            VStack
            {
                HStack
                {
                    HStack
                    {
                        Image(systemName: "magnifyingglass")
                            .foregroundColor(.gray)
                        TextField("Пошук міста", text: $cityWeather)
                            .submitLabel(.done)
                            .onSubmit
                            {
                                getCurrentWeather()
                                print(cityWeather)
                            }//onSubmit
                        
                        if !cityWeather.isEmpty
                        {
                            Button
                            {
                                withAnimation(Animation.easeInOut(duration: 0.5))
                                {
                                    cityWeather = ""
                                    country = ""
                                }
                            }
                            label:
                            {
                                Image(systemName: "xmark.circle.fill")
                                    .foregroundColor(.gray)
                            }//Button
                        }//if with button
                        
                        
                    } //HStack
                    .padding(.horizontal, 6)
                    .padding(.vertical, 16)
                    .background(RoundedRectangle(cornerRadius: 12)
                        .fill(Color.white.opacity(0.9))
                        .shadow(radius: 12)
                        .foregroundColor(Color.black)
                    )
                    Button
                    {
                        cityWeather = locationManager.userCity ?? ""
                        getCurrentWeather()
                    }
                    label:
                    {
                        Image(systemName: "location.fill")
                            .foregroundColor(Color.black)
                            .aspectRatio(contentMode: .fit)
                            .padding(.horizontal, 17)
                            .padding(.vertical, 17)
                    }//Button for search user location
                    .background(Color.white)
                    .cornerRadius(100)
                    .shadow(radius: 12)
                    
                }// HStack with TextField
            }//VStack with TextField
            .padding()
            .background(.ultraThinMaterial)

        }//HStack
        //.padding(.top, 12)
        .background(
                    LinearGradient(
                        gradient: Gradient(colors: [Color("UpBlue"), Color("DownBlue")]),
                        startPoint: .top,
                        endPoint: .bottom
                    )
                )
    }
    
    // Geter flags from name emoju
    func getFlag(country: String) -> String
    {
        let base : UInt32 = 127397
        var s = ""
        for v in country.unicodeScalars
        {
            s.unicodeScalars.append(UnicodeScalar(base + v.value)!)
        }
        return String(s)
    }
    
    // getter current info weather
    func getCurrentWeather()
    {
        let urlstring = "https://api.openweathermap.org/data/2.5/weather?q="+cityWeather+"&appid=ffe6d300f48841172ae985a4d1f3c576"
        let url=URL(string: urlstring)!
        let request = URLRequest(url: url)
        
        let task=URLSession.shared.dataTask(with: request)
        { d,response,error in
                do
                {
                    let json = try JSONSerialization.jsonObject(with: d!, options: .mutableContainers) as! Dictionary<String, Any>
                
                    if json["weather"] is [[String: Any]]
                    {
                        let weather = json["weather"] as! Array<Dictionary<String, Any>>
                        let main = json["main"] as! Dictionary<String, Any>
                        let sys = json["sys"] as! Dictionary <String, Any>
                        let wind = json["wind"] as! Dictionary <String, Any>
                        
                        withAnimation(Animation.easeOut(duration: 0.5))
                        {
                            country = sys["country"] as! String
                            temperature = main["temp"] as! Double
                            humidity = main["humidity"] as! Int
                            windSpeed = wind["speed"] as! Double
                            mainRain = weather[0]["main"] as! String
                            desctiptionRain = weather[0]["description"] as! String
                            cityStatic = cityWeather
                        }
                    
                    }
                    else
                    {
                        print("error parse")
                        // if 'weather' = nil
                    }
                  
                }
                catch
                {
                    print("Can't parse response")
                }
            }
        task.resume()
    }
}



#Preview
{
    MainWeatherView()
}

