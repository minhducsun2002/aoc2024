import { countDistinctPoints, dig, getStartingPoints, readF } from "./util.ts";

const matrix = readF('./input.txt');
const startingList = getStartingPoints(matrix)

solve1();
solve2();

function solve1() {
    let solve1 = 0;
    for (const point of startingList) {
        const res = dig(matrix, point);
        solve1 += countDistinctPoints(res);
    }
    console.log(solve1);
}

function solve2() {
    let count = 0;
    for (const point of startingList) {
        dig(matrix, point, () => count++);
    }

    console.log(count);
}