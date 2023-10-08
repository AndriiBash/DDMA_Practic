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
    
    @State private var humidity: Int = 0
    @State private var windSpeed:   Double = 0.0
    @State private var temperature: Double = 0.0
    
    var body: some View
    {
        VStack
        {
            VStack
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
            }//VStack with TextField
            .padding(.horizontal, 12)
            
            ScrollView(showsIndicators: false)
            {
                VStack
                {
                    VStack
                    {
                        
                        if country != ""
                        {
                            Text("\(country)/\(cityStatic) \(getFlag(country: country))")
                                .font(.title.bold())
                                .padding(.top, 12)
                                .padding(.horizontal)
                            
                            Text("🌡 Температура: \(String(format: "%.2f °C", temperature - 273.15))")
                                .padding(.top, 12)
                                .padding(.horizontal)
                                .frame(maxWidth: .infinity, alignment: .leading)
                            
                            Text("💦 Вологість: \(humidity)%")
                                .padding(.top, 12)
                                .padding(.horizontal)
                                .frame(maxWidth: .infinity, alignment: .leading)

                            Text("🌀 Швидкість вітру: \(windSpeed) м/с")
                                .padding(.top, 12)
                                .padding(.horizontal)
                                .frame(maxWidth: .infinity, alignment: .leading)
                            
                            Text("☁️ Взагалі: \(mainRain) [\(desctiptionRain)]")
                                .padding(.top, 12)
                                .padding(.bottom, 16)
                                .padding(.horizontal)
                                .frame(maxWidth: .infinity, alignment: .leading)
                        }
                        else
                        {
                            Text("Почніть шукати місто")
                                .font(.title2.bold())
                                .padding(.vertical, 15)
                        }
                        
                    }//VStack with info
                    .foregroundColor(.white)
                    .font(.body.bold())
                    .frame(maxWidth: .infinity)
                    .background(.black.opacity(0.15))
                    .cornerRadius(14)
                    .shadow(radius: 12)
                }//VStack
                .frame(maxWidth: .infinity, maxHeight: .infinity)
                .padding()
                
            }//ScrollView
        }//HStack
        .padding(.top, 10)
        .background(
                    LinearGradient(
                        gradient: Gradient(colors: [Color("DeepRed"), Color("DeepPurple")]), // Задайте цвета градиента
                        startPoint: .topLeading, // Начальная точка градиента
                        endPoint: .bottomTrailing // Конечная точка градиента
                    )
                )
    }
    
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
                        // случай, когда 'weather' равен nil или не имеет ожидаемого типа
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
