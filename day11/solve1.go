package main

import (
	"strconv"
)

func solve1(a []int) int {
	n := a
	for i := 0; i < 25; i++ {
		n = apply(n)
	}

	return len(n)
}

func apply(a []int) []int {
	var out []int
	for _, num := range a {
		if num == 0 {
			out = append(out, 1)
			continue
		}

		text := strconv.Itoa(num)
		if len(text)%2 == 0 {
			fi := text[0 : len(text)/2]
			se := text[len(text)/2:]

			fiN, _ := strconv.Atoi(fi)
			seN, _ := strconv.Atoi(se)
			out = append(out, fiN)
			out = append(out, seN)
			continue
		}

		out = append(out, num*2024)

	}
	return out
}
