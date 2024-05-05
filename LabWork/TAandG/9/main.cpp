import Foundation

func main() 
{
    let workMatrix = [
        [0, 12, 9, 11, 2 , 2],
        [12, 0, 13, 9, 10, 7],
        [9, 13, 0, 5, 11, 6],
        [11, 9, 5, 0, 3, 17],
        [2, 10, 11, 3, 0, 13],
        [2, 7, 6, 17, 13, 0]
    ]
    
    let iterations = 1000 // Кількість ітерацій алгоритму Монте-Карло
    
    if let shortestRoute = monteCarloTSP(workMatrix: workMatrix, iterations: iterations) 
    {
        print("Shortest Route: \(shortestRoute)")
        print("Shortest Distance: \(calculateRouteDistance(route: shortestRoute, workMatrix: workMatrix))")
    } 
    else
    {
        print("No solution found.")
    }
}// func main()


func monteCarloTSP(workMatrix: [[Int]], iterations: Int) -> [Int]?
{
    var shortestDistance = Int.max
    var shortestRoute: [Int]?
    
    for _ in 1...iterations 
    {
        let route = generateRandomRoute(workMatrix: workMatrix)
        let distance = calculateRouteDistance(route: route, workMatrix: workMatrix)
        
        if distance < shortestDistance 
        {
            shortestDistance = distance
            shortestRoute = route
        }
    }
    
    return shortestRoute
}// func monteCarloTSP(workMatrix: [[Int]], iterations: Int) -> [Int]?


func generateRandomRoute(workMatrix: [[Int]]) -> [Int] 
{
    var cities = [Int](0..<workMatrix.count)
    cities.shuffle()
    return cities
}// func generateRandomRoute(workMatrix: [[Int]]) -> [Int]


func calculateRouteDistance(route: [Int], workMatrix: [[Int]]) -> Int
{
    var distance = 0
    for i in 0..<route.count - 1 
    {
        distance += workMatrix[route[i]][route[i + 1]]
    }
    return distance
}// func calculateRouteDistance(route: [Int], workMatrix: [[Int]]) -> Int


main()
