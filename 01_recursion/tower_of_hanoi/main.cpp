//
// Created by keret on 2026. 02. 15..
//

#include <iostream>

void tower_of_hanoi(unsigned int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 1) {
        std::cout << "Move disk 1 from rod " << from_rod << " to rod: " << to_rod << std::endl;
        return;
    }
    tower_of_hanoi(n - 1, from_rod, aux_rod, to_rod);
    std::cout << "Move disk " << n << " from rod " << from_rod << " to rod: " << to_rod << std::endl;
    tower_of_hanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main(int argc, char *argv[]) {
    // Get disk count from arguments
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <disk_count>" << std::endl;
        return 0;
    }
    int disk_count = std::stoi(argv[1]);
    tower_of_hanoi(disk_count, 'A', 'C', 'B');
    return 0;
}