use std::collections::HashMap;

pub fn solve1(v: Vec<&str>) -> i32 {
    let line_count = v.len();
    let col_count = v[0].len();

    let mut matrix = vec![vec![0; col_count]; line_count];

    let regions = count_regions(&v, &mut matrix);

    let mut sum = 0;
    for region in regions {
        let (_, points) = region;
        sum += calculate_region(&v, &points, &matrix);
    }
    sum
}

fn calculate_region(v: &Vec<&str>, points: &Vec<(i32, i32)>, matrix: & Vec<Vec<i32>>) -> i32 {
    let mut perimeter = 0;
    let mut _ignore: char = ' ';
    for point in points {
        let (l_this, c_this) = point;
        let v_this = matrix[l_this.clone() as usize][c_this.clone() as usize];

        let directions: Vec<(i32, i32)> = vec![(-1, 0), (1, 0), (0, -1), (0, 1)]; // line, col

        let mut adj_region = 0;

        for (d_line, d_col) in directions {
            let (mut line, mut col) = point.clone();
            line += d_line;
            col += d_col;

            if access(v, line, col, &mut _ignore) {
                let adj = matrix[line as usize][col as usize];
                if adj == v_this {
                    adj_region += 1;
                }
            }
        }

        perimeter += 4 - adj_region;
    }

    perimeter * points.len() as i32
}

pub(crate) fn count_regions(v: &Vec<&str>, matrix: &mut Vec<Vec<i32>>) -> HashMap<i32, Vec<(i32, i32)>> {
    let mut next_id = 1;
    loop {
        let next_slot = get_next_empty_slot(v, matrix);
        if next_slot == (-1, -1) {
            break;
        }

        let mut current: char = ' ';
        let (line, col) = next_slot;
        access(v, line, col, &mut current);

        let (line, column) = next_slot;
        dig(v, matrix, next_id, current, line, column);
        next_id += 1;
    }

    let mut map: HashMap<i32, Vec<(i32, i32)>> = HashMap::new();

    for line in 0..matrix.len() {
        for col in 0..matrix[line].len() {
            let key = matrix[line][col];
            let m: &mut Vec<_> = map.entry(key).or_insert_with(|| vec![]);

            m.push((line as i32, col as i32))
        }
    }

    map
}

fn get_next_empty_slot(v: &Vec<&str>, matrix: &mut Vec<Vec<i32>>) -> (i32, i32) {
    for line in 0..v.len() {
        for col in 0..v[line].len() {
            if matrix[line][col] == 0 {
                return (line as i32, col as i32);
            }
        }
    }

    (-1, -1)
}

fn dig(v: &Vec<&str>, matrix: &mut Vec<Vec<i32>>, id: i32, key: char, start_line: i32, start_col: i32) {
    if matrix[start_line as usize][start_col as usize] != 0 {
        return
    }

    let cc = v[start_line as usize].as_bytes()[start_col as usize];
    if key as u8 != cc {
        return
    }

    // println!("region {} ({}) set at {},{}", id, key, start_col, start_line);
    matrix[start_line as usize][start_col as usize] = id;

    let directions: Vec<(i32, i32)> = vec![(-1, 0), (1, 0), (0, -1), (0, 1)]; // line, col

    for dir in directions.iter() {
        let (d_line, d_col) = dir;
        let (next_line, next_col) = (start_line + d_line, start_col + d_col);

        let mut adj = ' ';
        if access(v, next_line, next_col, &mut adj) {
            dig(v, matrix, id, cc as char, next_line, next_col);
        }
    }
}

pub(crate) fn access(v: &Vec<&str>, line: i32, col: i32, out: &mut char) -> bool {
    let line_count = v.len();
    let col_count = v[0].len();

    if line >= line_count as i32 || line < 0 || col >= col_count as i32 || col < 0 {
        return false;
    }

    let l = v[line as usize].as_bytes();
    *out = l[col as usize] as char;

    true
}