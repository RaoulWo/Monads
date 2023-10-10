#include <functional>
#include <iostream>
#include <string>

struct Vec2
{
    float x;
    float y;
};

struct Mat2x2
{
    Vec2 col1;
    Vec2 col2;
};
auto determinant = [](const Mat2x2& mat)
    {
        return mat.col1.x * mat.col2.y - mat.col1.y * mat.col2.x;
    };

auto is_invertible = [](const Mat2x2& mat)
    {
        return determinant(mat);
    };

auto inverse = [](const Mat2x2& mat)
    {
        float det = determinant(mat);

        Mat2x2 inverse;

        inverse.col1.x = (1 / det) * mat.col2.y;
        inverse.col1.y = -(1 / det) * mat.col1.y;
        inverse.col2.x = (-1 / det) * mat.col2.x;
        inverse.col2.y = (1 / det) * mat.col1.x;

        return inverse;
    };

class Result
{
public:
    Result() : error_message_("ERROR: Matrix not invertable") {}
    Result(const Mat2x2& mat) { mat_ = new Mat2x2(mat); }
    ~Result() { if (mat_ != nullptr) delete mat_; }

    Result bind(std::function<Result(const Mat2x2&)> func, const Mat2x2& mat)
    {
        if (!is_invertible(mat)) return Result();

        return Result(inverse(mat));
    }

    Mat2x2* value() const { return mat_; }
    std::string error() const { return error_message_; }

private:
    Mat2x2* mat_ = nullptr;
    std::string error_message_ = "";
};



int main()
{
    Mat2x2 mat;
    mat.col1.x = 1;
    mat.col1.y = 0;
    mat.col2.x = 0;
    mat.col2.y = 1;

    Result res;
    Result result = res.bind(inverse, mat);

    std::cout << result.value()->col1.x << " " << result.value()->col2.x << std::endl;
    std::cout << result.value()->col1.y << " " << result.value()->col2.y << std::endl;

    Mat2x2 mat2;
    mat2.col1.x = 0;
    mat2.col1.y = 0;
    mat2.col2.x = 0;
    mat2.col2.y = 0;

    Result res2;
    Result result2 = res2.bind(inverse, mat2);

    if (!is_invertible(mat2))
    {
        std::cout << result2.error() << std::endl;
    }
}
