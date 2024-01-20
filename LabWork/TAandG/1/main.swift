//
//  main.swift
//  FastSwiftProj
//
//  Created by Андрiй on 15.01.2024.
//

// Define the Markov algorithm rules
let rules: [String: String] =
[
    "0": "b",  // If in state 0, replace with "b"
    "b": "a",  // If in state b, replace with "a"
    "a": "c",  // If in state a, replace with "c"
    "c": "0"   // If in state c, replace with "0"
]

// Apply the Markov algorithm to the input string
func applyMarkovAlgorithm(_ input: String) -> String
{
    var currentState = "0"
    var result = ""

    for char in input
    {
        if let replacement = rules[String(char)]
        {
            currentState = replacement
            result += currentState
        }
    }

    return result
}// func applyMarkovAlgorithm(_ input: String) -> String {

func appendWordMarkov(_ word: String) -> (String, String)
{
    var P = Array(word)
    let bac = Array("bac")
    var state = 0

    for char in bac
    {
        P.insert(char, at: state)
        state += 1
    }

    return (String(P), applyMarkovAlgorithm(String(P)))
}// func appendWordMarkov(_ word: String) -> String

func main()
{
    print("Enter a p-word : ", terminator: "")
   
    let pWord = readLine()
    
    let result = appendWordMarkov(pWord ?? "nil")
    
    print("result word : \(result.0)")
    print("resulta after Markow algo : \(result.1)")
    
}// func main()

main()
