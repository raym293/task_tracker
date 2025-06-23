#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

int main() {
    std::ifstream f("data.json");
    json data = json::parse(f);
    std::cout << data["1"].dump(4) << '\n';
}