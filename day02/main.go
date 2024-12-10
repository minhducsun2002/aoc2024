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

	lines := strings.Split(string(dat), "\n")
	reports := make([][]int, 0)
	for _, l := range lines {
		nums := strings.Fields(l)
		out := make([]int, len(nums))
		for i, n := range nums {
			out[i], _ = strconv.Atoi(n)
		}

		reports = append(reports, out)
	}

	solve1(reports)
	solve2(reports)
}
