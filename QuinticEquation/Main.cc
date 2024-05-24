#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

struct QuinticEquation {
  double a, b, c, d, e, f;

  auto calculate(double x) -> double {
    return a * std::pow(x, 5) + b * std::pow(x, 4) + c * std::pow(x, 3) +
           d * std::pow(x, 2) + e * x + f;
  }

  auto solve(double min, double max, double step, double epsilon)
      -> std::vector<double> {
    auto prev = calculate(min);
    std::vector<double> roots;

    for (auto i = min + step; i <= max; i += step) {
      auto cur = calculate(i);
      if (cur == 0) {
        roots.push_back(i);
      }

      if (cur * prev < 0) {
        auto to = cur;
        auto from = prev;
        auto to_idx = i;
        auto from_idx = i - step;

        while (true) {
          auto avg = (to_idx + from_idx) / 2;
          auto avgc = calculate(avg);

          if (avgc == 0 || std::abs(avgc) <= epsilon) {
            roots.push_back(avg);
            break;
          }

          if (to * avgc < 0) {
            from_idx = avg;
            from = avgc;
          } else if (from * avgc < 0) {
            to_idx = avg;
            to = avgc;
          } else {
            roots.push_back(avg);
            break;
          }
        }
      }

      prev = cur;
    }

    return roots;
  }

private:
};

auto main() -> int {
  auto eq = QuinticEquation{1, 2, 3, 4, 5, 6};
  auto roots = eq.solve(-100, 100, 0.001, 0.0001);

  for (auto root : roots) {
    std::cout << root << std::endl;
  }

  return 0;
}
