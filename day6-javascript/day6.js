const fs = require('fs');

// greedy
function part1(inputs) {
    for (let i = 0; i < 80; i++) {
        length = inputs.length;
        for (let s = 0; s < length; s++) {
            if (inputs[s] === 0) {
                inputs[s] = 6;
                inputs.push(8);
            } else {
                inputs[s]--;
            }
        }
    }

    console.log(inputs.length)
}

// recursive
function accumulate_fish(life_left, cycles) {
    if (cycles === 0) return 0;

    if (life_left === 0) {
        return 1 +
            (accumulate_fish(8, cycles - 1) + accumulate_fish(6, cycles - 1));
    }

    return accumulate_fish(life_left - 1, cycles - 1);
}

// matrix multiplication
function part2(inputs) {
    let m = [0, 0, 0, 0, 0, 0, 0, 0, 0];
    for (let i = 0; i < inputs.length; i++) {
        m[inputs[i]]++;
    }

    for (let days = 0; days < 256; days++) {
        let m0 = m[0];
        m[0] = m[1];
        m[1] = m[2];
        m[2] = m[3];
        m[3] = m[4];
        m[4] = m[5];
        m[5] = m[6];
        m[6] = m[7] + m0;
        m[7] = m[8];
        m[8] = m0;
    }

    let fishes = 0;
    for (let i = 0; i < m.length; i++) {
        fishes += m[i];
    }

    console.log(fishes);
}

let inputs = fs.readFileSync('input.txt')
                 .toString()
                 .trim()
                 .split(',')
                 .map(x => parseInt(x));

part2(inputs);
