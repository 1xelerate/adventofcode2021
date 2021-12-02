#include <iostream>
#include <vector>

int main() {
    std::vector<int> values;
    int total = 0;
    int t;
    while (std::cin >> t) {
        values.push_back(t);
    }

    int previous = values[0] + values[1] + values[2];
    for (int i = 1; i < values.size() - 2; i++) {
        int next = values[i] + values[i + 1] + values[i + 2];
        if (next > previous) total++;

        previous = next;
    }

    std::cout << total << std::endl;
}
