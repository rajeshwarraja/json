# JavaScript Object Notation Data Interchange Format Library

## Getting Started
The library provides `json::data` type which boxes number, string, boolean, array and object.

The instances of type `json::data` is serializable to and from stream.

``` c++ 
#include <json>
#include <iostream>

int main(int argc, char*argv[]) {
    json::data json;
    auto& emp = json["employee"];
    emp["id"] = 1;
    emp["name"] = "Doe, John";
    emp["age"] = 30.5;
    emp["active"] = true;
    auto &reportee = emp["reportee"];
    reportee[0] = "Emp 1";
    reportee[1] = "Emp 2";
    reportee[2] = "Emp 3";
    std::cout << json::pretty << json << std::endl;
    return 0;
}
```