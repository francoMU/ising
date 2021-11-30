#include <random>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include "ising.hpp"


int main(int argc, char *argv[]) {

  constexpr auto steps = 100000000;

  constexpr long long int N = 100;
  constexpr auto size = N * N;
  constexpr double temperature = 0.01;

  constexpr auto J = 1.0;

  // allocate memory
  int *ising_matrix = new int[size];

  auto size_of = sizeof(ising_matrix[0]);
  std::cout << "Size of single element: " << size_of << std::endl;
  std::cout << "Size of matrix: " << ((double) size * size_of) / 1.0e6 << " Mb" << std::endl;

  auto start = std::chrono::high_resolution_clock::now();
  create_random_matrix(ising_matrix, size);
  auto stop = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time for random generation: " << duration.count() << " microseconds" << std::endl;
  //

  print_summary(ising_matrix, size);

  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<> distrib(0, N - 1);

  std::uniform_real_distribution<> r_dist(0, 1);

  int accepted = 0;
  int newed = 0;
  int old = 0;

  start = std::chrono::high_resolution_clock::now();
  for (auto i = 0; i < steps; i++) {

    int row = distrib(gen);
    int col = distrib(gen);

    auto val = J * get_energy_diff(ising_matrix, row, col, N);


    if (val <= 0.0) {

      /*
       * Accept
       */

      accepted++;
      ising_matrix[row + col * N] = ising_matrix[row + col * N] * -1;
    } else {

      /*
       * Metropolis move
       */

      double w = std::exp(-(double) val / temperature);
      auto r = r_dist(gen);

      if (r <= w) {
        newed++;
        ising_matrix[row + col * N] = ising_matrix[row + col * N] * -1;
      } else {
        old++;
      }

    }

  }

  stop = std::chrono::high_resolution_clock::now();

  duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << "Time for MC moves: " << duration.count() << " mircoseconds" << std::endl;

  std::cout << "Accepted: " << accepted << std::endl;
  std::cout << "New: " << newed << std::endl;
  std::cout << "Old: " << old << std::endl;

  print_summary(ising_matrix, size);

  // free matrix
  delete[] ising_matrix;

  return EXIT_SUCCESS;
}
