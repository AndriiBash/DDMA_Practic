import Foundation

// Вхідні дані
let supplyCapacities = [100, 160, 140, 120]
let demandCapacities = [150, 250, 120]

var transportCosts = [
    [19, 2, 3],
    [3, 4, 8],
    [4, 5, 6],
    [12, 7, 11]
]

// Функція для оптимізації транспортного плану
func optimizeTransportPlan(supplyCapacities: [Int], demandCapacities: [Int], transportCosts: inout [[Int]]) -> [[Int]]
{
    var result = Array(repeating: Array(repeating: 0, count: demandCapacities.count), count: supplyCapacities.count)
    
    var mutableTransportCosts = transportCosts
    
    var supply = supplyCapacities
    var demand = demandCapacities
    
    while !supply.isEmpty && !demand.isEmpty 
    {
        var minCost = Int.max
        var minCostIndex = (0, 0)
        
        for i in 0..<supply.count 
        {
            for j in 0..<demand.count {
                if mutableTransportCosts[i][j] < minCost
                {
                    minCost = mutableTransportCosts[i][j]
                    minCostIndex = (i, j)
                }
            }
        }
        
        let minSupply = min(supply[minCostIndex.0], demand[minCostIndex.1])
        
        result[minCostIndex.0][minCostIndex.1] = minSupply
        
        supply[minCostIndex.0] -= minSupply
        demand[minCostIndex.1] -= minSupply
        
        if supply[minCostIndex.0] == 0 
        {
            supply.remove(at: minCostIndex.0)
            mutableTransportCosts.remove(at: minCostIndex.0)
            result.remove(at: minCostIndex.0)
        }
        
        if demand[minCostIndex.1] == 0 
        {
            for i in 0..<mutableTransportCosts.count
            {
                mutableTransportCosts[i].remove(at: minCostIndex.1)
            }
            demand.remove(at: minCostIndex.1)
        }
    }
    
    return result
}

// Отримання оптимального транспортного плану
let transportPlan = optimizeTransportPlan(supplyCapacities: supplyCapacities, demandCapacities: demandCapacities, transportCosts: &transportCosts)

// Вивід результатов
print("Оптимальный план поставки:")
for (i, row) in transportPlan.enumerated() 
{
    for (j, amount) in row.enumerated()
    {
        if amount > 0 
        {
            print("Из точки \(i + 1) в точку \(j + 1): \(amount)")
        }
    }
}
