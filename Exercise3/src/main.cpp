#include <iostream>
#include <cmath>
#include <optional>

struct QuadraticSolution
{
    float solution1;
    std::optional<float> solution2;
};

auto solve_quadratic = [](float a, float b, float c) -> std::optional<QuadraticSolution>
{
    if (a == 0) return std::nullopt;

    float p = b / a;
    float q = c / a;

    float discriminant = (p / 2) * (p / 2) - q;
    if (discriminant < 0) return std::nullopt;

    QuadraticSolution sol;

    sol.solution1 = -(p / 2) + std::sqrt((p * p / 4) - q);

    if (discriminant > 0)
    {
        sol.solution2 = -(p / 2) - std::sqrt((p * p / 4) - q);
    }
    else
    {
        sol.solution2 = std::nullopt;
    }

    return sol;
};

int main()
{
    auto sol1 = solve_quadratic(1, -1, -6);

    if (sol1.has_value())
    {
        std::cout << "x1: " << sol1.value().solution1;
        if (sol1.value().solution2.has_value())
            std::cout << " x2: " << sol1.value().solution2.value();

        std::cout << std::endl;
    }

    auto sol2 = solve_quadratic(1, 2, 1);

    if (sol2.has_value())
    {
        std::cout << "x1: " << sol2.value().solution1;
        if (sol2.value().solution2.has_value())
            std::cout << " x2: " << sol2.value().solution2.value();

        std::cout << std::endl;
    }

    auto sol3 = solve_quadratic(1, -4, 5);

    if (!sol3.has_value())
    {
        std::cout << "Has no real solution!";
    }
}
