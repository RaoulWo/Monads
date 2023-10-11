#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

template <typename T>
struct Maybe
{
    std::optional<T> value;
};

auto read_file = [](const std::string& path) -> Maybe<std::string>
{
    std::ifstream stream(path);

    if (!stream.is_open()) return Maybe<std::string>{std::nullopt};

    std::string file;

    std::string line;
    while (std::getline(stream, line))
    {
        file.append(line);
    }

    return Maybe<std::string>{file};
};

auto is_ascii_char = [](const char c) -> bool
    {
        return !(static_cast<unsigned char>(c) > 127);
    };

auto is_ascii_string = [](const std::string& s) -> bool
    {
        return std::all_of(s.begin(), s.end(), is_ascii_char);
    };

auto process_file_content = [](const std::string& path) -> Maybe<std::string>
{
    auto file = read_file(path);

    if (!file.value.has_value()) return Maybe<std::string>{std::nullopt};
    if (!is_ascii_string(file.value.value())) return Maybe<std::string>{std::nullopt};

    return Maybe<std::string>{file.value.value()};
};



int main()
{
    auto content = process_file_content("data/file2.txt");

    if (content.value.has_value())
    {
        std::cout << content.value.value() << std::endl;
    }
    else 
    {
        std::cout << "Non ASCII format!" << std::endl;
    }
}
