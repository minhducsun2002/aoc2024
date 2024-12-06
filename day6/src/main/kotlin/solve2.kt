package nodomain.aoc2024

fun solve2(matrix: List<List<String>>): Int {
    val positions = listPositions(matrix)

    var sum = 0

    val cloned = matrix.map {ArrayList(it)}
    val start = locateStarting(matrix)
    for (i in 1..<positions.size) {
        val position = positions[i]
        val row = position.first
        val col = position.second

        cloned[row][col] = "#"
        if (loop(cloned, start)) {
            sum++
        }
        cloned[row][col] = "."
    }
    return sum
}

fun listPositions(matrix: List<List<String>>): List<Pair<Int, Int>> {
    val positions = matrix.map{ line -> ArrayList(line.map { _ -> false }) }
    val out = arrayListOf<Pair<Int, Int>>()
    walk(matrix, locateStarting(matrix)) { row, col, _ ->
        if (!positions[row][col]) {
            positions[row][col] = true
            out.add(Pair(row, col))
        }
        true
    }
    return out
}

fun loop(matrix: List<List<String>>, start: Pair<Int, Int>): Boolean {
    val cc = HashMap<Int, ArrayList<Int>>()
    var res = false
    walk(matrix, start) { row, col, dir ->
        val key = row * 1000 + col
        val list = cc.getOrPut(key) { ArrayList() }
        if (list.contains(dir)) {
            res = true
            return@walk false
        } else {
            list.add(dir)
        }
        true
    }

    return res
}