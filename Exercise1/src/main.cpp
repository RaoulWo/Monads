#include <algorithm>
#include <functional>
#include <fstream>
#include <iostream>
#include <numeric>
#include <optional>
#include <string>
#include <vector>

template<typename TValue>
class Maybe
{
    typedef std::function<std::optional<TValue>(const TValue)> TOperation;
public:
    Maybe(TValue value) : value_(value) {}

    std::optional<TValue> bind(const TOperation op)
    {
        if (value_ == std::nullopt) return std::nullopt;

        return op(value_.value());
    }

private:
    const std::optional<TValue> value_;
};

auto read_lines = [](const std::string& path) -> std::optional<std::vector<std::string>>
{
    std::ifstream stream(path);

    if (!stream.is_open()) return std::nullopt;

    std::vector<std::string> result;

    std::string line;
    while (std::getline(stream, line))
    {
        result.push_back(line);
    }

    return result;
};

auto is_numeric = [](const std::string& s) -> bool
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
};

auto transform_to_numeric_optionals = [](const std::vector<std::string>& lines)
{
    std::vector<std::optional<std::string>> optionals;

    std::transform(lines.begin(), lines.end(), std::back_inserter(optionals), [](const std::string& line)
    {
        return Maybe<std::string>{ line }.bind([](std::string s) -> std::optional<std::string>
        {
            if (!is_numeric(s)) return std::nullopt;

            return s;
        });
    });

    return optionals;
};

auto filter_optionals_without_value = [](const std::vector<std::optional<std::string>>& optionals)
{
    std::vector<std::optional<std::string>> values;

    // Filter out all optionals without value
    std::copy_if(optionals.begin(), optionals.end(), std::back_inserter(values), [](const std::optional<std::string>& optional)
    {
        return optional.has_value();
    });
    
    return values;
};

auto transform_to_numeric_strings = [](const std::vector<std::optional<std::string>> values)
{
    std::vector<std::string> result;

    std::transform(values.begin(), values.end(), std::back_inserter(result), [](const std::optional<std::string>& value)
    {
        return value.value();
    });

    return result;
};

auto transform_to_numbers = [](const std::vector<std::string>& strings)
{
        std::vector<int> result;

        std::transform(strings.begin(), strings.end(), std::back_inserter(result), [](const std::string& s) 
        {
                return std::stoi(s);
        });

        return result;
};

auto add_numbers = [](const std::vector<int>& numbers)
{
    return std::accumulate(numbers.begin(), numbers.end(), 0, [](int left, int right)
    {
        return left + right;
    });
};


int main()
{
    // Read file line by line.
    auto lines = read_lines("data/numbers_1.txt");
    if (!lines.has_value()) return EXIT_FAILURE;

    // Transform to numeric optionals.
    auto optionals = transform_to_numeric_optionals(lines.value());
    
    // Filter out all optionals without value.
    auto values = filter_optionals_without_value(optionals);

    // Transform the optionals to numeric strings.
    auto strings = transform_to_numeric_strings(values);

    // Transform the numeric strings to numbers.
    auto numbers = transform_to_numbers(strings);

    // Add the numbers.
    auto sum = add_numbers(numbers);

    std::cout << "Sum: " << sum << std::endl;
}
