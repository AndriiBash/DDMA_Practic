//
//  main.swift
//  FastSwiftProj
//
//  Created by Андрiй on 15.01.2024.
//

import Foundation

func findMinPositions(array: [Int]) -> [Int]
{
    var minPositions: [Int] = []
    
    guard !array.isEmpty else
    {
        return minPositions
    }

    // search min element in arrays
    let minValue = array.min()!

    // find min element position
    for (index, element) in array.enumerated()
    {
        if element == minValue
        {
            minPositions.append(index)
        }
    }

    return minPositions
}// func findMinPositions(array: [Int]) -> [Int]

func printResults(minPositions: [Int], numbers: [Int])
{
    if minPositions.isEmpty
    {
        print("Array is empty.")
    }
    else
    {
        print("Array : \(numbers)")
        print("Min value in array : \(numbers[minPositions[0]])")
        print("Position Min value in array : \(minPositions)")
    }
}// func printResults(minPositions: [Int], numbers: [Int])

func generateRandomArray(size: Int, maxValue: Int) -> [Int]
{
    var randomArray: [Int] = []
    
    for _ in 0..<size
    {
        randomArray.append(Int.random(in: 1...maxValue))
    }
    
    return randomArray
}// func generateRandomArray(size: Int, maxValue: Int) -> [Int]


func main()
{
    let arraySize = 20
    let maxValue = 100
    
    // generate array
    let randomNumbers = generateRandomArray(size: arraySize, maxValue: maxValue)
    
    // cout result
    printResults(minPositions: findMinPositions(array: randomNumbers), numbers: randomNumbers)
}// func main()

main()
