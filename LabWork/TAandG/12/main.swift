import Foundation

class Graph 
{
    var adjList: [String: [(String, Int)]] = [:]
    var vertices: [String: Int] = [:]
    
    func addVertex(_ vertex: String, weight: Int) 
    {
        vertices[vertex] = weight
        adjList[vertex] = []
    }
    
    func addEdge(from: String, to: String, weight: Int) 
    {
        adjList[from]?.append((to, weight))
    }
    
    func topologicalSort() -> [String]?
    {
        var stack: [String] = []
        var visited: Set<String> = []
        var inStack: Set<String> = []
        
        func dfs(_ vertex: String) -> Bool 
        {
            visited.insert(vertex)
            inStack.insert(vertex)
            
            for (neighbor, _) in adjList[vertex]!
            {
                if !visited.contains(neighbor)
                {
                    if dfs(neighbor)
                    {
                        return true
                    }
                }
                else if inStack.contains(neighbor)
                {
                    return true // Cycle detected
                }
            }
            
            inStack.remove(vertex)
            stack.append(vertex)
            return false
        }
        
        for vertex in vertices.keys 
        {
            if !visited.contains(vertex)
            {
                if dfs(vertex) 
                {
                    return nil // Cycle detected
                }
            }
        }
        
        return stack.reversed()
    }
    
    func calculateTimes() -> (earliestStart: [String: Int], earliestFinish: [String: Int], minDuration: Int)?
    {
        guard let topologicalOrder = topologicalSort() else
        {
            return nil
        }
        
        var earliestStart: [String: Int] = [:]
        var earliestFinish: [String: Int] = [:]
        
        for vertex in topologicalOrder 
        {
            earliestStart[vertex] = 0
            earliestFinish[vertex] = vertices[vertex]!
        }
        
        for vertex in topologicalOrder
        {
            for (neighbor, weight) in adjList[vertex]! 
            {
                if let currentStart = earliestStart[neighbor] 
                {
                    earliestStart[neighbor] = max(currentStart, earliestFinish[vertex]!)
                }
                else
                {
                    earliestStart[neighbor] = earliestFinish[vertex]!
                }
                earliestFinish[neighbor] = earliestStart[neighbor]! + vertices[neighbor]!
            }
        }
        
        let minDuration = earliestFinish.values.max()!
        return (earliestStart, earliestFinish, minDuration)
    }
}

// Create graph from the given data
let graph = Graph()

// Add vertices
graph.addVertex("s", weight: 7)
graph.addVertex("a", weight: 5)
graph.addVertex("b", weight: 9)
graph.addVertex("c", weight: 8)
graph.addVertex("d", weight: 8)
graph.addVertex("f", weight: 5)
graph.addVertex("m", weight: 5)
graph.addVertex("n", weight: 6)
graph.addVertex("t", weight: 4)

// Add edges
graph.addEdge(from: "s", to: "a", weight: 0)
graph.addEdge(from: "s", to: "b", weight: 0)
graph.addEdge(from: "a", to: "d", weight: 0)
graph.addEdge(from: "b", to: "d", weight: 0)
graph.addEdge(from: "b", to: "f", weight: 0)
graph.addEdge(from: "d", to: "c", weight: 0)
graph.addEdge(from: "d", to: "m", weight: 0)
graph.addEdge(from: "c", to: "n", weight: 0)
graph.addEdge(from: "f", to: "t", weight: 0)
graph.addEdge(from: "n", to: "t", weight: 0)

// Calculate times and print results
if let (earliestStart, earliestFinish, minDuration) = graph.calculateTimes() 
{
    print("Earliest Start Times: \(earliestStart)")
    print("Earliest Finish Times: \(earliestFinish)")
    print("Minimum Project Duration: \(minDuration)")
} 
else
{
    print("Cycle detected in the graph. Cannot proceed with calculations.")
}
