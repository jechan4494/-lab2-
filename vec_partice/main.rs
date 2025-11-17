use std::io;

fn read_vector(size: usize) -> Vec<i32> {
    loop {
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let nums: Vec<i32> = input
            .trim()
            .split_whitespace()
            .filter_map(|s| s.parse().ok())
            .collect();

        if nums.len() == size {
            return nums;
        } else {
            println!("{}개의 숫자를 입력하세요.", size);
        }
    }
}

fn read_matrix(rows: usize, cols: usize) -> Vec<Vec<i32>> {
    let mut matrix = Vec::new();
    for i in 0..rows {
        print!("행 {}: ", i + 1);
        io::Write::flush(&mut io::stdout()).unwrap();
        matrix.push(read_vector(cols));
    }
    matrix
}

fn add_matrices(a: &Vec<Vec<i32>>, b: &Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    let rows = a.len();
    let cols = a[0].len();
    let mut result = vec![vec![0; cols]; rows];
    for i in 0..rows {
        for j in 0..cols {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
    result
}

fn print_matrix(matrix: &Vec<Vec<i32>>) {
    for row in matrix {
        for val in row {
            print!("{:>5}", val);
        }
        println!();
    }
}

fn main() {
    println!("행 개수를 입력하세요: ");
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let rows: usize = input.trim().parse().unwrap();

    println!("열 개수를 입력하세요: ");
    input.clear();
    io::stdin().read_line(&mut input).unwrap();
    let cols: usize = input.trim().parse().unwrap();

    println!("\n행렬 A 입력:");
    let a = read_matrix(rows, cols);

    println!("\n행렬 B 입력:");
    let b = read_matrix(rows, cols);

    let result = add_matrices(&a, &b);

    println!("\n--- A + B 결과 ---");
    print_matrix(&result);
}

