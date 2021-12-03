#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char get_column_commonality(char *bits[], unsigned array_size, unsigned column,
                            unsigned length) {
    int common = 0;
    for (int i = 0; i < array_size; i++) {
        if (bits[i] != NULL) {
            if (bits[i][column] == '1') {
                common++;
            } else {
                common--;
            }
        }
    }

    return (common >= 0) ? '1' : '0';
}

void chars_to_binary(char *bits, unsigned length, unsigned *output) {
    for (int c = 0; c < length; c++) {
        *output = (*output << 1) | ((bits[c] == '1') ? 1 : 0);
    }
}

void part2() {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;

    fp = fopen("input.txt", "r");
    size_t length = getline(&line, &len, fp) - 1;
    size_t array_size = 1000;

    char *bits_oxygen[array_size];
    char *bits_co2[array_size];
    for (int i = 0; i < array_size; i++) {
        bits_oxygen[i] = (char *)malloc(sizeof(char) * length);
        bits_co2[i] = (char *)malloc(sizeof(char) * length);
    }

    rewind(fp);
    unsigned n = 0;
    while (getline(&line, &len, fp) != -1) {
        line[strcspn(line, "\n")] = 0;
        memcpy(bits_oxygen[n], line, length);
        memcpy(bits_co2[n], line, length);
        n++;
    }
    fclose(fp);

    unsigned oxygen = 0, co2 = 0;
    unsigned oxygen_left = array_size;
    unsigned co2_left = array_size;
    char *last_oxygen, *last_co2;

    for (int i = 0; i < length; i++) {
        char common_oxygen =
            get_column_commonality(bits_oxygen, array_size, i, length);

        char common_co2 =
            get_column_commonality(bits_co2, array_size, i, length);

        for (int j = 0; j < array_size; j++) {
            if (bits_oxygen[j] != NULL &&
                !(bits_oxygen[j][i] == common_oxygen) && oxygen_left) {
                bits_oxygen[j] = NULL;
                oxygen_left--;
            } else if (bits_oxygen[j] != NULL && oxygen_left) {
                last_oxygen = bits_oxygen[j];
            }

            if (bits_co2[j] != NULL && (bits_co2[j][i] == common_co2) &&
                co2_left) {
                bits_co2[j] = NULL;
                co2_left--;
            } else if (bits_co2[j] != NULL && co2_left) {
                last_co2 = bits_co2[j];
            }
        }

        if (oxygen_left == 1) {
            oxygen_left = 0;
            chars_to_binary(last_oxygen, length, &oxygen);
        }

        if (co2_left == 1) {
            co2_left = 0;
            chars_to_binary(last_co2, length, &co2);
        }

        if (co2_left == 1 && oxygen_left == 1) break;
    }

    printf("oxygen: %u co2: %u life support: %u\n", oxygen, co2, oxygen * co2);
}

void part1() {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;

    fp = fopen("input.txt", "r");
    size_t length = getline(&line, &len, fp) - 1;

    int common[length];
    for (int i = 0; i < length; i++) common[i] = 0;

    rewind(fp);
    while (getline(&line, &len, fp) != -1) {
        line[strcspn(line, "\n")] = 0;

        for (int i = 0; i < length; i++) {
            if (line[i] == '1') {
                common[i]++;
            } else {
                common[i]--;
            }
        }
    }
    fclose(fp);
    free(line);

    unsigned long gamma = 0;
    unsigned long epsilon = 0;
    for (int i = 0; i < length; i++) {
        if (common[i] > 0) {
            gamma = (gamma << 1) | 1;
            epsilon <<= 1;
        } else {
            gamma <<= 1;
            epsilon = (epsilon << 1) | 1;
        }
    }

    printf("gamma: %lu epsilon: %lu power: %lu\n", gamma, epsilon,
           gamma * epsilon);
}

int main() {
    part1();
    part2();
}
