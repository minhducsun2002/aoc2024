package main

func solve2(reports [][]int) {
	sum := 0
	for _, report := range reports {
		if check2(report) {
			sum += 1
		}
	}

	println(sum)
}

func remove(slice []int, s int) []int {
	return append(slice[:s:s], slice[s+1:]...)
}

func check2(report []int) bool {
	l := len(report)
	for i := 0; i < l; i++ {
		newReport := remove(report, i)
		if check1(newReport) {
			return true
		}
	}

	return false
}
