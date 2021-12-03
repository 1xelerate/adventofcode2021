use std::io;

fn main() {
    let (mut horizontal, mut depth, mut aim) = (0, 0, 0);

    let mut input = String::new();
    while let Ok(_) = io::stdin().read_line(&mut input) {
        if input.trim().is_empty() {
            break;
        }

        let value: u32 = (&input.trim()[input.len() - 2..]).parse().unwrap();

        match &input[0..(input.len() - 3)] {
            "forward" => {
                horizontal += value;
                depth += aim * value;
            }
            "down" => aim += value,
            "up" => aim -= value,
            _ => {}
        }
        input.clear();
    }

    println!("{}", horizontal * depth);
}
