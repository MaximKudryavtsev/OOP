#pragma once

static const int MIN_PRIME_NUMBER = 2;
static const int MAX_UPPER_BOUND = 100000000;

std::set<int> GeneratePrimeNumbersSet(const int upperBound);
std::vector<bool> FindPrimeNumbersInRange(const int upperBound);
