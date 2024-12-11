package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
	"time"
)

func main() {
	f, err := os.ReadFile("./input.txt")
	if err != nil {
		panic(err)
	}

	numsText := strings.Fields(string(f))
	var list []int
	for _, num := range numsText {
		n, _ := strconv.Atoi(num)
		list = append(list, n)
	}

	start := time.Now()
	sum1 := solve1(list)
	fmt.Printf("%d (%v)\n", sum1, time.Since(start))
	sum2 := solve2(list)
	fmt.Printf("%d (%v)\n", sum2, time.Since(start))
}
