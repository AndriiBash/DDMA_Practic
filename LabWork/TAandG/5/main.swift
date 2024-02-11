
//
//  main.swift
//  FastSwiftProj
//
//  Created by Андрiй on 15.01.2024.
//

import Foundation

struct Edge
{
    let source: Int
    let destination: Int
    let weight: Int
}// struct Edge


func printPaths(graph: [Edge])
{
    for edge in graph
    {
        print("\(edge.source) edge - in \(edge.destination) edhe (road \(edge.weight))")
    }
}// func printPaths(graph: [Edge])


func getUserEdge() -> (Int, Int)
{
    
    print("\nEnter the starting edge : ", terminator: "")
    
    guard let startEdgeString = readLine(),
          let startEdge = Int(startEdgeString)
    else
    {
        fatalError("\nInvalid input")
    }
    
    
    print("Enter the end edge : ", terminator: "")
    
    guard let endEdgeString = readLine(),
          let endEdge = Int(endEdgeString)
    else
    {
        fatalError("\nInvalid input")
    }
    return (startEdge, endEdge)
}// func getUserEdge() -> (Int, Int)



func dijkstra(graph: [Edge], start: Int, end: Int) -> [Int: Int]
{
    var distances: [Int: Int] = [:]
    var visited: Set<Int> = []
    
    for edge in graph
    {
        distances[edge.source] = Int.max
        distances[edge.destination] = Int.max
    }
    
    distances[start] = 0
    
    while !visited.contains(end)
    {
        let current = getMinDistanceVertex(distances: distances, visited: visited)
        visited.insert(current)
        
        for edge in graph
        {
            if edge.source == current
            {
                let newDistance = distances[current]! + edge.weight
                if newDistance < distances[edge.destination]!
                {
                    distances[edge.destination] = newDistance
                }
            }
        }
    }
    
    return distances
}// func dijkstra(graph: [Edge], start: Int, end: Int) -> [Int: Int]


func floydWarshall(graph: [Edge]) -> [[Int]]
{
    var distanceMatrix: [[Int]] = Array(repeating: Array(repeating: Int.max, count: 7), count: 7)
    
    for edge in graph
    {
        distanceMatrix[edge.source][edge.destination] = edge.weight
    }
    
    for i in 1...6 {
        distanceMatrix[i][i] = 0
    }
    
    for k in 1...6
    {
        for i in 1...6
        {
            for j in 1...6
            {
                if distanceMatrix[i][k] != Int.max && distanceMatrix[k][j] != Int.max && distanceMatrix[i][k] + distanceMatrix[k][j] < distanceMatrix[i][j]
                {
                    distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j]
                }
            }
        }
    }
    
    return distanceMatrix
}// func floydWarshall(graph: [Edge]) -> [[Int]]


func getMinDistanceVertex(distances: [Int: Int], visited: Set<Int>) -> Int
{
    var minVertex = -1
    var minDistance = Int.max
    
    for (vertex, distance) in distances
    {
        if !visited.contains(vertex) && distance < minDistance
        {
            minVertex = vertex
            minDistance = distance
        }
    }
    
    return minVertex
}// func getMinDistanceVertex(distances: [Int: Int], visited: Set<Int>) -> Int



func main()
{
    let edges: [Edge] =
    [
        Edge(source: 1, destination: 2, weight: 5),
        Edge(source: 1, destination: 6, weight: 2),
        Edge(source: 1, destination: 4, weight: 5),
        Edge(source: 1, destination: 3, weight: 7),
        Edge(source: 2, destination: 4, weight: 1),
        Edge(source: 2, destination: 6, weight: 13),
        Edge(source: 3, destination: 4, weight: 5),
        Edge(source: 6, destination: 5, weight: 10),
        Edge(source: 5, destination: 3, weight: 2),
        Edge(source: 5, destination: 4, weight: 5)
    ]

    printPaths(graph: edges)
    
    let userEdge = getUserEdge()

    
    let dijkstraDistances = dijkstra(graph: edges, start: userEdge.0, end: userEdge.1)
    
    print("Shortest distance from \(userEdge.0) to \(userEdge.1) using Dijkstra is \(dijkstraDistances[userEdge.1]!)")
    
    let floydWarshallDistances = floydWarshall(graph: edges)
    
    print("Shortest distance from \(userEdge.0) to \(userEdge.1) using Floyd-Warshall is \(floydWarshallDistances[userEdge.0][userEdge.1])")

}// func main()


main()

