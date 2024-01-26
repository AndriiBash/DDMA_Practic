//
//  main.swift
//  FastSwiftProj
//
//  Created by Андрiй on 15.01.2024.
//

func ackermann(_ m: Int, _ n: Int) -> Int
{
    if m == 0
    {
        return n + 1
    }
    else if n == 0
    {
        return ackermann(m - 1, 1)
    }
    else
    {
        return ackermann(m - 1, ackermann(m, n - 1))
    }
} // func ackermann(_ m: Int, _ n: Int) -> Int

func main()
{
    print("Write n-value : ", terminator: "")
    let n = readLine()
    
    print("Write m-value : ", terminator: "")
    let m = readLine()

    
    let result = ackermann(Int(n!) ?? 0, Int(m!) ?? 0)
    print("A(\(n ?? "noValue"), \(m ?? "noValue")) = \(result)")

}// func main()

main()
