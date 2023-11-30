#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <iostream>
#include <chrono>
#include <iomanip>

std::pair<std::vector<std::vector<int>>, int> first_generation(int m, int n);
std::pair<std::vector<std::vector<int>>, int> second_generation(int m, int n);
void ladder(const std::vector<std::vector<int>>& arr, int target_element, int m, int n);
void binary(const std::vector<std::vector<int>>& arr, int target_element, int m, int n);
void binary_search(const std::vector<int>& arr, int target_element, int up, int down);
void exponential_search(const std::vector<std::vector<int>>& arr, int target_element, int m, int n);
void getTimeForFirstGeneration();
void getTimeForSecondGeneration();
#endif
