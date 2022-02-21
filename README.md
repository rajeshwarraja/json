# JavaScript Object Notation Data Interchange Format Library
The library implements [RFC8259](https://datatracker.ietf.org/doc/html/rfc8259) internet standard.

## Getting Started
The library provides `json::data` type which boxes numbers, strings, booleans, arrays and objects.

The instances of type `json::data` is serializable to and from C++ stream.

The following program:
``` c++ 
#include <json>

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
outputs:
``` json
{
  "employee" : {
    "id" : 1,
    "name" : "Doe, John",
    "age" : 30.500000,
    "active" : true,
    "reportee" : [
      "Emp 1",
      "Emp 2",
      "Emp 3"
    ]
  }
}
```

## Pretty Output Formatting
The library provides stream manipulators `json::pretty` and `json::nopretty` to toggle on and off pretty json output serialization respectively. The pretty json output serialization adds new line to object members and array elements, and each json object hierarchy is prefixed with two spaces.

## License
Refer [LICENSE](./LICENSE.md) for more information.