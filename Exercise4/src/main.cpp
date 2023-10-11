#include <functional>
#include <iostream>
#include <optional>

template<typename TValue>
class Maybe
{
    typedef std::function<std::optional<TValue>(const TValue, const TValue)> TOperation;
public:
    Maybe(TValue value) : value_(value) {}

    std::optional<TValue> bind(const TOperation op, const TValue other)
    {
        if (value_ == std::nullopt || other == std::nullopt) return std::nullopt;

        return op(value_.value(), other.value());
    }

private:
    const std::optional<TValue> value_;
};

auto divide = [](int left, int right) -> std::optional<int> 
{
    if (right == 0) return std::nullopt;

    return left / right;
};

auto print_result = [](const std::optional<int>& num) -> void
{
    if (num.has_value())
    {
        std::cout << num.value() << std::endl;
    }
    else 
    {
        std::cout << "Division by 0 not allowed" << std::endl;
    }
};

int main()
{
    print_result(divide(10, 2));
    print_result(divide(10, 0));
}
