package main

func solve1(reports [][]int) {
	sum := 0
	for _, report := range reports {
		if check1(report) {
			sum += 1
		}
	}

	println(sum)
}

func check1(report []int) bool {
	if len(report) < 2 {
		return true
	}

	if !increasing(report) && !decreasing(report) {
		return false
	}

	for i := 0; i < len(report)-1; i++ {
		fi := report[i]
		se := report[i+1]
		diff := fi - se
		if diff < 0 {
			diff = -diff
		}

		if diff < 1 || diff > 3 {
			return false
		}
	}

	return true
}

func increasing(report []int) bool {
	for i := 0; i < len(report)-1; i++ {
		if report[i] > report[i+1] {
			return false
		}
	}

	return true
}

func decreasing(report []int) bool {
	for i := 0; i < len(report)-1; i++ {
		if report[i] < report[i+1] {
			return false
		}
	}

	return true
}
