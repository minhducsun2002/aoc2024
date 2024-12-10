import { readFileSync } from 'node:fs';

export function readF(file: string): string[][] {
    const data = readFileSync(file, 'utf8');
    const lines = data.split('\n').filter(Boolean);
    const matrix = lines.map(r => r.split(''));

    return matrix;
}

export function getStartingPoints(matrix: string[][]) {
    const out: { line: number, column: number }[] = []

    for (let l = 0; l < matrix.length; l++) {
        for (let c = 0; c < matrix[0].length; c++) {
            if (matrix[l][c] === '0') {
                out.push({ line: l, column: c });
            }
        }
    }

    return out;
}

export function dig(
    m: string[][],
    starting: { line: number, column: number },
    matchingCallback?: (stack: { line: number, column: number }[]) => void
) {
    const current = m[starting.line]?.[starting.column];
    return digInternal(
        m,
        starting,
        +current,
        [],
        matchingCallback
    )
}

export function countDistinctPoints(list: ReturnType<typeof dig>) {
    const count = new Set(
        list.map(r => r.line * 1e6 + r.column)
    );

    return count.size;
}

function digInternal(
    m: string[][],
    starting: { line: number, column: number },
    target: number,
    stack: { line: number, column: number }[],
    matchingCallback?: (stack: { line: number, column: number }[]) => void,
) {
    const current = m[starting.line]?.[starting.column];
    if (+current === target) {
        if (target === 9) {
            matchingCallback?.(
                [...stack, starting]
            )
            return [starting];
        }

        // move forward
        const directions = [
            { line: +1, column: 0 },
            { line: -1, column: 0 },
            { line: 0, column: 1 },
            { line: 0, column: -1 },
        ]

        let sum: (typeof starting)[] = [];
        for (const d of directions) {
            const nextItem = { line: starting.line + d.line, column: starting.column + d.column };
            sum = sum.concat(
                digInternal(
                    m,
                    nextItem,
                    target + 1,
                    [...stack, nextItem],
                    matchingCallback
                )
            );
        }
        return sum;
    } else {
        return [];
    }
}