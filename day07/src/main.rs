use std::error::Error;
use std::fs;
use std::cmp::Ordering;

fn solve1_dig(expected: u64, arr: &Vec<u64>, current_result: u64, current_index: usize) -> Ordering {
    if current_index + 1 == arr.len() {
        return current_result.cmp(&expected);
    }

    let next = arr[current_index + 1];

    let plus = current_result + next;
    let mul = current_result * next;

    if solve1_dig(expected, arr, plus, current_index + 1) == Ordering::Equal {
        Ordering::Equal
    } else {
        solve1_dig(expected, arr, mul, current_index + 1)
    }
}

fn solve2_dig(expected: u64, arr: &Vec<u64>, current_result: u64, current_index: usize) -> Ordering {
    if current_index + 1 == arr.len() {
        return current_result.cmp(&expected);
    }

    let next = arr[current_index + 1];

    let plus = current_result + next;
    let mul = current_result * next;
    let append = current_result * 10_u64.pow((next as f64).log10().floor() as u32 + 1) + next;

    if solve2_dig(expected, arr, plus, current_index + 1) == Ordering::Equal {
        return Ordering::Equal
    }
    if solve2_dig(expected, arr, mul, current_index + 1) == Ordering::Equal {
        Ordering::Equal
    } else {
        solve2_dig(expected, arr, append, current_index + 1)
    }
}

fn main() -> Result<(), Box<dyn Error>> {
    let file = fs::read_to_string("./input.txt")?;
    let lines = file.lines();
    let lines : Vec<_> = lines.map(move |x| {
        let pieces = x.split(":").collect::<Vec<&str>>();
        let out = pieces[0].parse::<u64>().unwrap();
        let pieces = pieces[1].trim().split(" ").map(|x| x.parse::<u64>().unwrap()).collect::<Vec<u64>>();
        return (out, pieces)
    }).collect();

    let mut sum = 0;
    let mut sum2 = 0;

    for (expected, line) in lines {
        if solve1_dig(expected, &line, line[0], 0) == Ordering::Equal {
            sum += expected;
        }
        if solve2_dig(expected, &line, line[0], 0) == Ordering::Equal {
            sum2 += expected;
        }
    }

    println!("{}\n{}", sum, sum2);

    Ok(())
}
