//
// Created by F.Moitzi on 01.12.2021.
//

#include "ising.hpp"

#include <iostream>
#include <algorithm>
#include <random>


void create_random_matrix(int *ising_matrix, long long int n) {

  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(0, 1);

  for (long long int i = 0; i < n; i++) {
    ising_matrix[i] = distrib(gen) ? -1 : 1;
  }


}

void print_summary(int *ising_matrix, long long int n) {

  int number_of_ones = 0;

  for (long long int i = 0; i < n; i++) {

    if (ising_matrix[i] == 1) {
      number_of_ones++;
    }

  }

  std::cout << "Number of  1: " << number_of_ones << std::endl;
  std::cout << "Number of -1: " << n - number_of_ones << std::endl;

}

int get_energy_diff(const int *ising_matrix, int row, int col, int n) {

  int up, down, left, right;

  up = (row + n - 1) % n;
  left = (col + n - 1) % n;

  down = (row + 1) % n;
  right = (col + 1) % n;

  auto up_val = ising_matrix[up + col * n];
  auto down_val = ising_matrix[down + col * n];

  auto left_val = ising_matrix[row + left * n];
  auto right_val = ising_matrix[row + right * n];

  return ising_matrix[row + col * n] * (up_val + down_val + left_val + right_val);

}

