// Вхідні дані
let сenoPricePerKg: Double = 1.2
let silagePricePerKg: Double = 0.8

let сenoNutrients: [String: Double] = ["кормові_єд.": 0.5, "білок": 40, "кальцій": 1.25, "фосфор": 2]
let silageNutrients: [String: Double] = ["кормові_єд.": 0.5, "білок": 10, "кальцій": 2.5, "фосфор": 1]

let maxСenoWeight: Double = 50
let maxSilageWeight: Double = 70

// Функція для обчислення вартості раціону
func calculateCost(сenoWeight: Double, silageWeight: Double) -> Double 
{
    return сenoPricePerKg * сenoWeight + silagePricePerKg * silageWeight
}

// Функція для перевірки, чи відповідає раціон усім вимогам
func meetsRequirements(сenoWeight: Double, silageWeight: Double) -> Bool 
{
    let totalNutrients = [
        "кормові_єд.": сenoNutrients["кормові_єд."]! * сenoWeight + silageNutrients["кормові_єд."]! * silageWeight,
        "білок": сenoNutrients["білок"]! * сenoWeight + silageNutrients["білок"]! * silageWeight,
        "кальцій": сenoNutrients["кальцій"]! * сenoWeight + silageNutrients["кальцій"]! * silageWeight,
        "фосфор": сenoNutrients["фосфор"]! * сenoWeight + silageNutrients["фосфор"]! * silageWeight
    ]
    
    return totalNutrients["кормові_єд."]! >= 30 &&
           totalNutrients["білок"]! >= 1000 &&
           totalNutrients["кальцій"]! >= 100 &&
           totalNutrients["фосфор"]! >= 80 &&
           сenoWeight <= maxСenoWeight &&
           silageWeight <= maxSilageWeight
}

// Пошук оптимального раціону
var minCost = Double.infinity
var optimalСenoWeight = 0.0
var optimalSilageWeight = 0.0

for сenoWeight in stride(from: 0.0, through: maxСenoWeight, by: 0.1) 
{
    for silageWeight in stride(from: 0.0, through: maxSilageWeight, by: 0.1) 
    {
        if meetsRequirements(сenoWeight: сenoWeight, silageWeight: silageWeight) 
        {
            let cost = calculateCost(сenoWeight: сenoWeight, silageWeight: silageWeight)
            if cost < minCost {
                minCost = cost
                optimalСenoWeight = сenoWeight
                optimalSilageWeight = silageWeight
            }
        }
    }
}

// Виведення результатів
if minCost != Double.infinity 
{
    print("Оптимальна кількість сіна свіжого: \(optimalСenoWeight) кг")
    print("Оптимальна кількість силосу: \(optimalSilageWeight) кг")
    print("Мінімальна вартість раціону: \(minCost) коп")
}
else
{
    print("Рішення не знайдено")
}
