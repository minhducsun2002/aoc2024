package nodomain.aoc2024

val directions = listOf(
    // row, column
    Pair(-1, 0), // up
    Pair(0, +1), // right
    Pair(+1, 0), // down
    Pair(0, -1), // left
)

fun locateStarting(matrix: List<List<String>>): Pair<Int, Int> {
    val rows = matrix.size
    val columns = matrix[0].size

    for (row in 0..<rows) {
        for (column in 0..<columns) {
            if (matrix[row][column] == "^") {
                return Pair(row, column)
            }
        }
    }

    throw IllegalArgumentException("starting point not found")
}

fun solve1(matrix: List<List<String>>): Int {
    val map = matrix.map { list -> ArrayList(list.map { 0 }) }
    walk(matrix, locateStarting(matrix)) { row, column, _ ->
        map[row][column] = 1
        true
    }


    return map.sumOf { line -> line.sum() }
}

fun walk(matrix: List<List<String>>, start: Pair<Int, Int>, call: (row: Int, col: Int, direction: Int) -> Boolean) {
    var sRow = start.first
    var sCol = start.second

    var directionIndex = 0
    while (nextWithinBounds(matrix, Pair(sRow, sCol), directionIndex)) {
        if (nextCollides(matrix, Pair(sRow, sCol), directionIndex)) {
            directionIndex = (directionIndex + 1) % directions.size
            continue
        }

        if (!call(sRow, sCol, directionIndex)) {
            return
        }

        sRow += directions[directionIndex].first
        sCol += directions[directionIndex].second
    }

    call(sRow, sCol, directionIndex)
}

fun nextWithinBounds(matrix: List<List<String>>, current: Pair<Int, Int>, nextDirection: Int): Boolean {
    val rows = matrix.size
    val columns = matrix[0].size

    val dir = directions[nextDirection]
    val nextRow = current.first + dir.first
    val nextColumn = current.second + dir.second
    return !(nextRow < 0 || nextRow >= rows || nextColumn < 0 || nextColumn >= columns)
}

fun nextCollides(matrix: List<List<String>>, current: Pair<Int, Int>, nextDirection: Int): Boolean {
    val dir = directions[nextDirection]
    val nextRow = current.first + dir.first
    val nextColumn = current.second + dir.second

    return matrix[nextRow][nextColumn] == "#"
}