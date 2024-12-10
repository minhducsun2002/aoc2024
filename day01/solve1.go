package main

import (
	"sort"
)

func solve1(first, second []int) {
	sort.Ints(first)
	sort.Ints(second)

	sum := 0

	for idx, num := range first {
		fi := num
		se := second[idx]

		diff := fi - se
		if diff < 0 {
			diff = -diff
		}

		sum += diff
	}

	println(sum)
}
