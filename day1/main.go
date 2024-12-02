package main

import (
	"os"
	"strconv"
	"strings"
)

func main() {
	dat, err := os.ReadFile("input.txt")
	if err != nil {
		panic(err)
	}

	numText := strings.Fields(string(dat))
	first := make([]int, 0)
	second := make([]int, 0)
	for idx, num := range numText {
		i, err := strconv.Atoi(num)
		if err != nil {
			panic(err)
		}

		if idx%2 == 0 {
			first = append(first, i)
		} else {
			second = append(second, i)
		}
	}

	solve1(first, second)
	solve2(first, second)
}
