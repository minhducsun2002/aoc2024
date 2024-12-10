package nodomain.aoc2024
import java.io.File
import kotlin.time.measureTimedValue

fun main() {
    val lines = File("./input.txt").readLines()
    val data = lines.map { line -> line.split("")}

    val (s1, time1) = measureTimedValue { solve1(data) }
    println("$s1 ($time1)")
    val (s2, time2) = measureTimedValue { solve2(data) }
    println("$s2 ($time2)")
}