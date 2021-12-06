// first time writing in Go :)~
package main

import (
    "bufio"
    "fmt"
    "os"
    "strings"
    "strconv"
)

type Cord struct {
    x int 
    y int
}


func main() {
    file, _ := os.Open("input.txt");
    defer file.Close();

    var diagram = make(map[Cord]int)
    overlaps := 0
    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        cords := strings.Split(scanner.Text(), " -> ")
        string_cord := strings.Split(cords[0], ",") 
        string_cord2 := strings.Split(cords[1], ",") 

        num1, _ := strconv.Atoi(string_cord[0])
        num2, _ := strconv.Atoi(string_cord[1])
        num3, _ := strconv.Atoi(string_cord2[0])
        num4, _ := strconv.Atoi(string_cord2[1])

        cord1 := Cord {num1, num2}
        cord2 := Cord {num3, num4}

        for cord1 != cord2 {
            diagram[cord1]++ 
            if diagram[cord1] == 2 {
                overlaps++
            }

            if cord1.x < cord2.x {
                cord1.x++
            } else if cord1.x > cord2.x {
                cord1.x--;
            }

            if cord1.y < cord2.y {
                cord1.y++;
            } else if cord1.y > cord2.y {
                cord1.y--;
            }
        }
        
        diagram[cord1]++ 
        if diagram[cord1] == 2 {
            overlaps++
        }
    }

    fmt.Println(overlaps);
}
