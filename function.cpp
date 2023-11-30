#include "functions.h"

std::pair<std::vector<std::vector<int>>, int> first_generation(int m, int n) {
    std::vector<std::vector<int>> arr(m, std::vector<int>(n, 0));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            arr[i][j] = static_cast<int>((n / static_cast<double>(m) * i + j) * 2);
        }
    }

    int target_element = 2 * n + 1;

    return {arr, target_element};
}

std::pair<std::vector<std::vector<int>>, int> second_generation(int m, int n) {
    std::vector<std::vector<int>> arr(m, std::vector<int>(n, 0));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            arr[i][j] = static_cast<int>((n / static_cast<double>(m) * (i + 1) * (j + 1)) * 2);
        }
    }

    int target_element = 16 * n + 1;

    return {arr, target_element};
}

void ladder(const std::vector<std::vector<int>>& arr, int target_element, int m, int n) {
    int i = 0;
    int j = n - 1;

    while (j > -1 && i < m) {
        int current_element = arr[i][j];
        if (current_element == target_element) {
            return;
        } else if (current_element < target_element) {
            i += 1;
        } else if (current_element > target_element) {
            j -= 1;
        }
    }
}

void binary(const std::vector<std::vector<int>>& arr, int target_element, int m, int n) {
    for (int i = 0; i < m; ++i) {
        binary_search(arr[i], target_element, 0, n - 1);
    }
}

void binary_search(const std::vector<int>& arr, int target_element, int up, int down) {
    if (up > down) {
        return;
    }

    int top = (up + down) / 2;

    if (arr[top] == target_element) {
        return;
    } else if (arr[top] > target_element) {
        binary_search(arr, target_element, up, top - 1);
    } else if (arr[top] < target_element) {
        binary_search(arr, target_element, top + 1, down);
    }
}

void exponential_search(const std::vector<std::vector<int>>& arr, int target_element, int m, int n) {
    int i = 0;
    int j = n - 1;

    while (j > -1) {
        int current_element = arr[i][j];

        if (current_element == target_element) {
            return;
        } else if (current_element > target_element) {
            j -= 1;
        } else if (current_element < target_element) {
            int down = 1;

            while (i + down < m && arr[i + down][j] < target_element) {
                down *= 2;
            }

            int up = i + down / 2;

            if (i + down < m) {
                down += i;
            } else if (i + down >= m) {
                down = m - 1;
            }

            if (up == down) {
                return;
            }

            int f = 0;

            while (f != 1) {
                int top = (up + down) / 2;
                current_element = arr[top][j];

                if (up >= down) {
                    break;
                } else if (current_element == target_element) {
                    return;
                } else if (target_element > current_element) {
                    up = top + 1;
                } else if (target_element < current_element) {
                    down = top - 1;
                }
            }

            i = up;
        }
    }
}

void getTimeForFirstGeneration() {
    std::cout << "\nFirst Generation" << std::endl;

    int column = 1 << 13;
    for (int x = 1; x <= 13; ++x) {
        int row = 1 << x;
        auto [a, target] = first_generation(row, column);

        std::cout << row << " * " << column << std::endl;

        double mean = 0;

        for (int i = 0; i < 100; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            ladder(a, target, row, column);
            auto end = std::chrono::high_resolution_clock::now();
            double q = std::chrono::duration<double>(end - start).count();
            mean += q;
        }

        std::cout << std::fixed << std::setprecision(10) << (mean / 100) << std::endl;
        mean = 0;

        for (int i = 0; i < 100; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            binary(a, target, row, column);
            auto end = std::chrono::high_resolution_clock::now();
            double q = std::chrono::duration<double>(end - start).count();
            mean += q;
        }

        std::cout << std::fixed << std::setprecision(10) << (mean / 100) << std::endl;
        mean = 0;

        for (int i = 0; i < 100; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            exponential_search(a, target, row, column);
            auto end = std::chrono::high_resolution_clock::now();
            double q = std::chrono::duration<double>(end - start).count();
            mean += q;
        }

        std::cout << std::fixed << std::setprecision(10) << (mean / 100) << std::endl;
    }
}

void getTimeForSecondGeneration() {
    std::cout << "\nSecond Generation" << std::endl;
    int column = 1 << 13;

    for (int q = 1; q <= 13; ++q) {
        int row = 1 << q;
        auto [a, target] = second_generation(row, column);

        std::cout << row << " * " << column << std::endl;

        double mean = 0;

        for (int i = 0; i < 100; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            ladder(a, target, row, column);
            auto end = std::chrono::high_resolution_clock::now();
            double q = std::chrono::duration<double>(end - start).count();
            mean += q;
        }

        std::cout << std::fixed << std::setprecision(10) << (mean / 100) << std::endl;
        mean = 0;

        for (int i = 0; i < 100; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            binary(a, target, row, column);
            auto end = std::chrono::high_resolution_clock::now();
            double q = std::chrono::duration<double>(end - start).count();
            mean += q;
        }

        std::cout << std::fixed << std::setprecision(10) << (mean / 100) << std::endl;
        mean = 0;

        for (int i = 0; i < 100; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            exponential_search(a, target, row, column);
            auto end = std::chrono::high_resolution_clock::now();
            double q = std::chrono::duration<double>(end - start).count();
            mean += q;
        }

        std::cout << std::fixed << std::setprecision(10) << (mean / 100) << std::endl;
    }
}
