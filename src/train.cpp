// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

void Train::addCar(bool light) {
  Car* newCar = new Car{light, nullptr, nullptr};
  if (first == nullptr) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
  }
}

int Train::getLength() {
  if (first == nullptr) {
    return 0;
  }

  first->light = true;
  int steps = 0;
  Car* current = first;

  while (true) {
    current = current->next;
    steps++;
    countOp++;

    if (current->light) {
      current->light = false;

      Car* check = current;
      for (int i = 0; i < steps; ++i) {
        check = check->prev;
        countOp++;
      }

      if (!check->light) {
        check->light = true;
        return steps;
      }

      for (int i = 0; i < steps; ++i) {
        check = check->next;
        countOp++;
      }
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
