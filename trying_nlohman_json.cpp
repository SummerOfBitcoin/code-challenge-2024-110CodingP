#include <iostream>
#include <string>
#include <stdexcept>
#include <json.hpp>
#include <fstream>

using json = nlohmann::json;

struct Test {
   std::string Name;
   std::string Val;
};

 void from_json(const json& j, Test& p) {
    j.at("Name").get_to(p.Name);
    j.at("Val").get_to(p.Val);
}

// template <typename T, size_t N>
// void from_json(const json& j, T  (&t)[N]) {
//     if (j.size()!=N) {
//         throw std::runtime_error("size!");
//     }
//     size_t index=0;
//     for (auto& item : j) {
//         from_json(item, t[index++]);
//     }
// }
int main() {
    std::ifstream f("test.json");
    json data = json::parse(f);
    Test my_array[2];
    from_json(data, my_array);
    std::cout<<my_array[0].Name<<std::endl;
    return 0;
}

// [
//     {
//       "Name": "Test",
//       "Val": "TestVal"
//     },
//     {
//       "Name": "Test2",
//       "Val": "TestVal2"
//     }
// ]
