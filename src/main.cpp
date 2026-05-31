/// Copyright 2022 NNTU-CS

#include <cstdlib>
#include <fstream>
#include <iostream>

#include "train.h"

int main() {
  constexpr int kRandomSeed = 42;
  constexpr int kMinTrainLength = 100;
  constexpr int kMaxTrainLength = 1000;
  constexpr int kStep = 100;

  std::ofstream out_file("result/data.csv");
  if (!out_file.is_open()) {
    std::cerr << "File error: Cannot open result/data.csv\n";
    return EXIT_FAILURE;
  }

  out_file << "Length,AllOff,AllOn,Random\n";

  std::srand(kRandomSeed);

  for (int n = kMinTrainLength; n <= kMaxTrainLength; n += kStep) {
    Train train_off;
    for (int i = 0; i < n; ++i) {
      train_off.addCar(false);
    }
    train_off.getLength();
    const int ops_off = train_off.getOpCount();

    Train train_on;
    for (int i = 0; i < n; ++i) {
      train_on.addCar(true);
    }
    train_on.getLength();
    const int ops_on = train_on.getOpCount();

    Train train_rand;
    for (int i = 0; i < n; ++i) {
      train_rand.addCar((std::rand() % 2) == 1);
    }
    train_rand.getLength();
    const int ops_rand = train_rand.getOpCount();

    out_file << n << "," << ops_off << "," << ops_on << "," << ops_rand << "\n";

    std::cout << "N: " << n << " | Off: " << ops_off
              << " | On: " << ops_on << " | Rand: " << ops_rand << '\n';
  }

  out_file.close();
  return EXIT_SUCCESS;
}
