import Foundation

// Функція для максимізації прибутку
func maximizeProfit() 
{
    // Задані параметри
    let breadAUnitPrice = 2 // Ціна за одиницю хліба типу А
    let breadBUnitPrice = 6 // Ціна за одиницю хліба типу В
    
    // Запаси ресурсів
    let flour1Capacity = 600
    let flour2Capacity = 450
    let machineCapacity = 60
    let ovenCapacity = 120
    
    // Норми витрат
    let flour1UsageA = 1.2
    let flour2UsageA = 1.0
    let flour1UsageB = 0.9
    let flour2UsageB = 1.1
    let machineUsageA = 0.1
    let machineUsageB = 0.2
    let ovenUsageA = 0.2
    let ovenUsageB = 0.3
    
    // Мінімальна виробництва хліба типу А
    let minBreadAProduction = 100
    
    // Задаємо початкові значення
    var maxProfit = 0
    var optimalBreadAProduction = 0
    var optimalBreadBProduction = 0
    
    // Пробуємо всі можливі комбінації виробництва хліба
    for breadAProduction in minBreadAProduction...1000
    {
        for breadBProduction in 0...(1000 - breadAProduction)
        {
            // Перевіряємо, чи задовольняємо всі обмеження
            let flour1Usage = flour1UsageA * Double(breadAProduction) + flour1UsageB * Double(breadBProduction)
            let flour2Usage = flour2UsageA * Double(breadAProduction) + flour2UsageB * Double(breadBProduction)
            let machineUsage = machineUsageA * Double(breadAProduction) + machineUsageB * Double(breadBProduction)
            let ovenUsage = ovenUsageA * Double(breadAProduction) + ovenUsageB * Double(breadBProduction)
            
            if flour1Usage <= Double(flour1Capacity) && flour2Usage <= Double(flour2Capacity) &&
                machineUsage <= Double(machineCapacity) && ovenUsage <= Double(ovenCapacity) 
            {
                // Розраховуємо прибуток
                let profit = breadAProduction * breadAUnitPrice + breadBProduction * breadBUnitPrice
                // Оновлюємо максимальний прибуток та оптимальне виробництво хліба
                if profit > maxProfit 
                {
                    maxProfit = profit
                    optimalBreadAProduction = breadAProduction
                    optimalBreadBProduction = breadBProduction
                }
            }
        }
    }
    
    // Виводимо результати
    print("Оптимальне виробництво хліба:")
    print("Хліб типу A: \(optimalBreadAProduction) одиниць")
    print("Хліб типу B: \(optimalBreadBProduction) одиниць")
    print("Максимальний прибуток: \(maxProfit) д.е.")
}

// Викликаємо функцію для максимізації прибутку
maximizeProfit()
