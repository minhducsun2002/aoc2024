const { readFileSync } = require('fs')
let data = readFileSync('./input.txt', 'utf8');

solve1(data);
solve2(data);

/**
 * @param {String} data
 */
function solve1(data) {
    let d = [...data.matchAll(/(mul\(\d{1,3},\d{1,3}\))/g)]
    let expressions = d.map(a => a[0]);

    solveExpressions(expressions)
}

/**
 * @param {String} data
 */
function solve2(data) {
    let d2 = [...data.matchAll(/(mul\(\d{1,3},\d{1,3}\))|(don't\(\))|(do\(\))/g)]
    d2 = d2.sort((a, b) => a.index - b.index)
    let inst = d2.map(a => a[0])


    let filtered = []
    let e = true;
    for (let i of inst) {
        if (i === `don't()`) {
            e = false;
        }
        if (i === `do()`) {
            e = true;
        }
        if (i.startsWith('mul')) {
            if (e) {
                filtered.push(i)
            }
        }
    }

    solveExpressions(filtered)
}

/**
 * @param {string[]} expressions
 */
function solveExpressions(expressions) {
    let sum = 0
    for (let exp of expressions) {
        let matches = [...exp.matchAll(/(\d+)/g)]
        let m = matches.map(a => a[0]);
        sum += (+m[0]) * (+m[1])
    }

    console.log(sum)
}