import SwiftUI

struct ContentView: View {
    // Параметри, які вводить користувач
    @State private var d1: String = "100"
    @State private var d2: String = "80"
    @State private var d3: String = "60"
    @State private var d4: String = "40"
    @State private var d5: String = "20"
    @State private var d6: String = "10"
    
    @State private var l1: String = "100"
    @State private var l2: String = "150"
    @State private var l3: String = "200"
    @State private var l4: String = "250"
    @State private var l5: String = "300"
    @State private var l6: String = "350"

    var body: some View {
        VStack {
            Text("Введіть параметри для побудови моделі")
                .font(.title)
                .padding()
            
            HStack {
                TextField("D1", text: $d1)
                TextField("D2", text: $d2)
                TextField("D3", text: $d3)
            }
            .padding()

            HStack {
                TextField("L1", text: $l1)
                TextField("L2", text: $l2)
                TextField("L3", text: $l3)
            }
            .padding()

            HStack {
                TextField("D4", text: $d4)
                TextField("D5", text: $d5)
                TextField("D6", text: $d6)
            }
            .padding()

            HStack {
                TextField("L4", text: $l4)
                TextField("L5", text: $l5)
                TextField("L6", text: $l6)
            }
            .padding()

            Button("Побудувати модель")
            {
                // Обробка кнопки побудови
            }
            .padding()
            .buttonStyle(PlainButtonStyle())
            .background(Color.blue)
            .foregroundColor(.white)
            .cornerRadius(10)
            
            Spacer()
            
            // Відображення 2D-моделі на основі введених параметрів
            GeometryReader { geometry in
                let d1Value = Double(d1) ?? 100.0
                let d2Value = Double(d2) ?? 80.0
                let d3Value = Double(d3) ?? 60.0
                let d4Value = Double(d4) ?? 40.0
                let d5Value = Double(d5) ?? 20.0
                let d6Value = Double(d6) ?? 10.0

                let l1Value = Double(l1) ?? 100.0
                let l2Value = Double(l2) ?? 150.0
                let l3Value = Double(l3) ?? 200.0
                let l4Value = Double(l4) ?? 250.0
                let l5Value = Double(l5) ?? 300.0
                let l6Value = Double(l6) ?? 350.0

                Path { path in
                    // Початкова точка
                    path.move(to: CGPoint(x: 50, y: geometry.size.height - d1Value))
                    
                    // Лінії профілю
                    path.addLine(to: CGPoint(x: 50 + l1Value, y: geometry.size.height - d1Value))
                    path.addLine(to: CGPoint(x: 50 + l1Value, y: geometry.size.height - d2Value))
                    path.addLine(to: CGPoint(x: 50 + l1Value + l2Value, y: geometry.size.height - d2Value))
                    path.addLine(to: CGPoint(x: 50 + l1Value + l2Value, y: geometry.size.height - d3Value))
                    path.addLine(to: CGPoint(x: 50 + l1Value + l2Value + l3Value, y: geometry.size.height - d3Value))
                    path.addLine(to: CGPoint(x: 50 + l1Value + l2Value + l3Value, y: geometry.size.height - d4Value))
                    path.addLine(to: CGPoint(x: 50 + l1Value + l2Value + l3Value + l4Value, y: geometry.size.height - d4Value))
                    path.addLine(to: CGPoint(x: 50 + l1Value + l2Value + l3Value + l4Value, y: geometry.size.height - d5Value))
                    path.addLine(to: CGPoint(x: 50 + l1Value + l2Value + l3Value + l4Value + l5Value, y: geometry.size.height - d5Value))
                    path.addLine(to: CGPoint(x: 50 + l1Value + l2Value + l3Value + l4Value + l5Value, y: geometry.size.height - d6Value))
                    path.addLine(to: CGPoint(x: 50 + l1Value + l2Value + l3Value + l4Value + l5Value + l6Value, y: geometry.size.height - d6Value))
                    
                    // Замикання фігури
                    path.addLine(to: CGPoint(x: 50 + l1Value + l2Value + l3Value + l4Value + l5Value + l6Value, y: geometry.size.height))
                    path.addLine(to: CGPoint(x: 50, y: geometry.size.height))
                    path.closeSubpath()
                }
                .stroke(Color.red, lineWidth: 2)
            }
            .frame(height: 400)
            .padding()
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}

