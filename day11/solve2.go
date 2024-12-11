package main

import (
	"strconv"
)

var cache = map[int]map[int]int{}

func solve2(a []int) int {
	sum := 0

	for _, n := range a {
		sum += dig(n, 0, 75)
	}

	return sum
}

func access(num, depth int) int {
	l1, ok := cache[num]
	if !ok {
		return -1
	}

	l2, ok := l1[depth]
	if !ok {
		return -1
	}

	return l2
}

func set(num, depth, value int) {
	l1, ok := cache[num]
	if !ok {
		l1 = make(map[int]int)
		cache[num] = l1
	}

	l1[depth] = value
}

func dig(num int, level int, target int) int {
	var out []int
	if level >= target {
		return 1
	}

	// cache the computed responses
	// map[num][depth] will contain the number of descendant values after applying `depth` times on `num`
	depth := target - level
	if res := access(num, depth); res != -1 {
		return res
	}

	if num == 0 {
		out = append(out, 1)
	} else {
		text := strconv.Itoa(num)
		if len(text)%2 == 0 {
			fi := text[0 : len(text)/2]
			se := text[len(text)/2:]

			fiN, _ := strconv.Atoi(fi)
			seN, _ := strconv.Atoi(se)
			out = append(out, fiN)
			out = append(out, seN)
		} else {
			out = append(out, num*2024)
		}
	}

	sum := 0
	for _, num := range out {
		sum += dig(num, level+1, target)
	}

	set(num, depth, sum)

	return sum
}
