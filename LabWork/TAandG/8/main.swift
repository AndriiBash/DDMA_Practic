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
}// strcut Edge

func printPaths(graph: [Edge])
{
    for edge in graph
    {
        print("\(edge.source) edge - in \(edge.destination) edhe (road : \(edge.weight))")
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
    
    while let current = getMinDistanceVertex(distances: distances, visited: visited) 
    {
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
            else if edge.destination == current
            {
                let newDistance = distances[current]! + edge.weight
                if newDistance < distances[edge.source]!
                {
                    distances[edge.source] = newDistance
                }
            }
        }
    }

    return distances
}// func dijkstra(graph: [Edge], start: Int, end: Int) -> [Int: Int]


func floydWarshall(graph: [Edge], start: Int, end: Int) -> (Int, [Int])
{
    var distanceMatrix: [[Int]] = Array(repeating: Array(repeating: Int.max, count: 6), count: 6)
    var nextVertex: [[Int]] = Array(repeating: Array(repeating: -1, count: 6), count: 6)

    for edge in graph
    {
        distanceMatrix[edge.source - 1][edge.destination - 1] = edge.weight
        nextVertex[edge.source - 1][edge.destination - 1] = edge.destination - 1
    }

    for i in 0..<6 
    {
        distanceMatrix[i][i] = 0
    }

    for k in 0..<6 
    {
        for i in 0..<6
        {
            for j in 0..<6
            {
                if distanceMatrix[i][k] != Int.max && distanceMatrix[k][j] != Int.max && distanceMatrix[i][k] + distanceMatrix[k][j] < distanceMatrix[i][j] {
                    distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j]
                    nextVertex[i][j] = nextVertex[i][k]
                }
            }
        }
    }

    var path: [Int] = []
    var current = start - 1
    let target = end - 1
    
    if nextVertex[current][target] == -1
    {
        return (Int.max, [])
    }
    
    while current != target
    {
        path.append(current + 1)
        current = nextVertex[current][target]
    }
    path.append(target + 1)

    return (distanceMatrix[start - 1][end - 1], path)
}// func floydWarshall(graph: [Edge], start: Int, end: Int) -> (Int, [Int])


func getMinDistanceVertex(distances: [Int: Int], visited: Set<Int>) -> Int?
{
    var minVertex: Int? = nil
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
}// func getMinDistanceVertex(distances: [Int: Int], visited: Set<Int>) -> Int?


func main()
{
    let edges: [Edge] =
    [
        Edge(source: 1, destination: 2, weight: 5),
        Edge(source: 1, destination: 3, weight: 7),
        Edge(source: 1, destination: 4, weight: 5),
        Edge(source: 1, destination: 6, weight: 2),
        Edge(source: 2, destination: 4, weight: 1),
        Edge(source: 2, destination: 6, weight: 13),
        Edge(source: 3, destination: 4, weight: 5),
        Edge(source: 3, destination: 5, weight: 2),
        Edge(source: 4, destination: 5, weight: 5),
        Edge(source: 5, destination: 6, weight: 19)
    ]

    printPaths(graph: edges)
    
    let userEdge = getUserEdge()
    let dijkstraDistances = dijkstra(graph: edges, start: userEdge.0, end: userEdge.1)
    print("Shortest distance from \(userEdge.0) to \(userEdge.1) using Dijkstra is \(dijkstraDistances[userEdge.1]!)")
    
    let (shortestDistance, _) = floydWarshall(graph: edges, start: userEdge.0, end: userEdge.1)
    
    if shortestDistance == Int.max
    {
        print("There is no path from \(userEdge.0) to \(userEdge.1) using Floyd-Warshall")
    } 
    else
    {
        print("Shortest distance from \(userEdge.0) to \(userEdge.1) using Floyd-Warshall is \(shortestDistance)")
    }

    }// func main()


main()
