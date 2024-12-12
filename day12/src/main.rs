mod solve1;
mod solve2;

use std::fs;
use crate::solve1::solve1;
use crate::solve2::solve2;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let file = fs::read_to_string("./input.txt")?;
    let lines = file.lines();
    let lines: Vec<_> = lines.filter(|x| {!x.is_empty()}).collect();

    println!("{}", solve1(lines.clone()));
    println!("{}", solve2(lines.clone()));

    Ok(())
}
