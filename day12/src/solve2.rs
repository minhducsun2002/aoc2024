use std::collections::HashMap;

struct Line {
    start: (i32, i32),
    end: (i32, i32),
}

pub fn solve2(v: Vec<&str>) -> i32 {
    let line_count = v.len();
    let col_count = v[0].len();

    let mut matrix = vec![vec![0; col_count]; line_count];

    let regions = crate::solve1::count_regions(&v, &mut matrix);

    let mut sum = 0;
    for region in regions {
        let (_, points) = region;
        sum += calculate_region(&v, &points, &matrix);
    }
    sum
}

fn calculate_region(v: &Vec<&str>, points: &Vec<(i32, i32)>, matrix: & Vec<Vec<i32>>) -> i32 {
    let mut graph : HashMap<(i32, i32), Vec<(i32, i32)>> = HashMap::new();

    let mut _ignored: char = ' ';

    for point in points {
        let (l_this, c_this) = point;
        let v_this = matrix[l_this.clone() as usize][c_this.clone() as usize];

        let directions: Vec<(i32, i32)> = vec![  // line, col
            (-1, 0), // up
            (1, 0), // down
            (0, -1), // left
            (0, 1) // right
        ];
        let line_presets: Vec<_> = vec![
            Line { // top
                start: (0, 0),
                end: (0, 1),
            },
            Line { // bottom
                start: (1, 0),
                end: (1, 1),
            },
            Line { // left
                start: (0, 0),
                end: (1, 0),
            },
            Line { // right
                start: (0, 1),
                end: (1, 1),
            }
        ];

        for (idx, (d_line, d_col)) in directions.iter().enumerate() {
            let (line, col) = point.clone();
            let next_line = line + d_line;
            let next_col = col + d_col;

            if crate::solve1::access(v, next_line, next_col , &mut _ignored) {
                let adj = matrix[next_line as usize][next_col as usize];
                if adj != v_this {
                    add_edge(&mut graph, &line_presets[idx], point);
                }
            } else {
                add_edge(&mut graph, &line_presets[idx], point);
            }
        }
    }


    count_sides(&graph) * points.len() as i32
}

fn count_sides(graph: &HashMap<(i32, i32), Vec<(i32, i32)>>) -> i32 {
    let mut sum = 0;
    for (start, list) in graph {
        if list.len() > 2 {
            // two turning points
            sum += 2;
            continue;
        }

        let first = list.first().unwrap();
        let last = list.last().unwrap();

        let mut result = false;

        if start.0 == first.0 && start.0 == last.0 { // same line
            result = true;
        }

        if start.1 == first.1 && start.1 == last.1 { // same column
            result = true;
        }

        if !result {
            sum += 1;
        }
    }

    sum
}

fn add_edge(graph: &mut HashMap<(i32, i32), Vec<(i32, i32)>>, preset: &Line, base_point: &(i32, i32)) {
    let (line, col) = base_point;
    let (start_line, start_col) = preset.start;
    let (end_line, end_col) = preset.end;

    let start = (line + start_line, col + start_col);
    let end = (line + end_line, col + end_col);

    let line = Line { start, end };

    add_to_graph(graph, &line);
}

fn add_to_graph(graph: &mut HashMap<(i32, i32), Vec<(i32, i32)>>, line: &Line) {
    let start = line.start;
    let end = line.end;

    let start_list: &mut Vec<_> = graph.entry(start).or_insert_with(|| vec![]);
    start_list.push(end);

    let end_list = graph.entry(end).or_insert_with(|| vec![]);
    end_list.push(start);
}