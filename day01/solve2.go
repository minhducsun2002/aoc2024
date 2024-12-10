package main

func solve2(first, second []int) {
	counts := map[int]int{}

	for _, n := range second {
		counts[n]++
	}

	sum := 0
	for _, n := range first {
		c, ok := counts[n]
		if !ok {
			c = 0
		}

		sum += c * n
	}

	println(sum)
}
