//
// Created by F.Moitzi on 01.12.2021.
//

#ifndef ISING_ISING_HPP
#define ISING_ISING_HPP

void create_random_matrix(int *ising_matrix, long long int n);

void print_summary(int *ising_matrix, long long int n);

int get_energy_diff(const int *ising_matrix, int row, int col, int n);

#endif //ISING_ISING_HPP
