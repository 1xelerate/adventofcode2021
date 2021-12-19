use std::{cmp, fs};

fn main() {
    let input = fs::read_to_string("input.txt").expect("no input file");
    let mut positions: Vec<i32> = input.trim().split(',').flat_map(|x| x.parse()).collect();

    positions.sort();
    part1(&positions);
    part2(&positions);
}

// Distance between each position using median of all points
fn part1(positions: &Vec<i32>) {
    let mid = positions.len() / 2;
    let median = positions.get(mid).unwrap();

    let mut fuel_needed = 0;
    for &x in positions {
        fuel_needed += (x - median).abs();
    }

    println!(
        "Part 1: Converge on position: {}, using a total of {} fuel",
        median, fuel_needed
    );
}

// Increasing distance between each position using mean of all points
fn part2(positions: &Vec<i32>) {
    let mean: f64 = positions.iter().sum::<i32>() as f64 / positions.len() as f64;

    let lower = mean.floor() as i32;
    let upper = lower + 1;

    let lower_fuel: i32 = positions
        .iter()
        .map(|&x| (x - lower).abs())
        .map(|fuel| (fuel * (fuel + 1)) / 2)
        .sum();

    let upper_fuel: i32 = positions
        .iter()
        .map(|&x| (x - upper).abs())
        .map(|fuel| (fuel * (fuel + 1)) / 2)
        .sum();

    println!(
        "Part 2: Need a total of {} fuel",
        cmp::min(lower_fuel, upper_fuel)
    );
}
