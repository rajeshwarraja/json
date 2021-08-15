// JavaScript Object Notation Data Interchange Format Library
// https://datatracker.ietf.org/doc/html/rfc8259

#include <regex>
#include <string>
#include <vector>
#include <iostream>

namespace json::grammar {
    // Structural Characters
    constexpr const char* _beginArray = "[";
    constexpr const char* _endArray = "]";
    constexpr const char* _beginObject = "{";
    constexpr const char* _endObject = "}";
    constexpr const char* _nameSeparator = ":";
    constexpr const char* _valueSeparator = ",";

    // Patterns
    constexpr const char* _patternWhitespaces = "[ \t\n\r]+";
    
    // Values
    constexpr const char* _valueFalse = "false";
    constexpr const char* _valueTrue = "true";
    constexpr const char* _valueNull = "null";

    // Digit
    constexpr const char* _digitStart = "+\\-\\d";
    constexpr const char* _digit = "+\\-\\d\\.eE";
    constexpr const char* _digitPattern = "[+-]?\\d+(?:(?:[eE][+-]?|\\.)\\d+)?";

    // String
    constexpr const char* _doubleQuotes = "\"";

    bool is_digit(const std::string& text) { return std::regex_match(text, std::regex(_digitPattern)); }

    bool is(const char* pattern, char ch) {
        return std::regex_match(&ch, &ch + 1, std::regex(std::string("[") + pattern + "]"));
    }
}

namespace json {
    class data {
        enum class _Type { Null, Boolean, Object, Array, Number, String };
    public:
        data() { reset(); }
        ~data() = default;
        data(const data& other) { operator=(other); }
        data& operator=(const data& other) { set(other); return *this; }
        data(const char* text) { operator=(text); }
        data& operator=(const char* text) { set(text); return *this; }
        data(bool flag) { operator=(flag); }
        data& operator=(bool flag) { set(flag); return *this; }
        data(int number) { operator=(number); }
        data& operator=(int number) { set(number); return *this; }
        data(double number) { operator=(number); }
        data& operator=(double number) { set(number); return *this; }

        operator bool() const { validate(_Type::Boolean); return _value == grammar::_valueTrue; }
        operator int() const { validate(_Type::Number); return std::atoi(_value.c_str()); }
        operator double() const { validate(_Type::Number); return std::atof(_value.c_str()); }
        operator const char*() const { 
            if(_type == _Type::Null) return nullptr;
            validate(_Type::String); 
            return _value.c_str(); 
        }

        bool operator==(const data& other) const {
            return _type == other._type && _value == other._value && _elements == other._elements && _members == other._members;
        }

        bool operator!=(const data& other) const {
            return !(*this != other);
        }

        friend std::ostream& operator<<(std::ostream& out, const data& json) { return json.toStream(out); }
        friend std::istream& operator>>(std::istream& in, data& json) { return json.fromStream(in); }

    private:
        _Type _type;
        std::string _value;
        std::vector<data> _elements;
        std::vector<std::pair<std::string, data>> _members;

        inline void validate(_Type type) const {
            if(_type != type)
                throw std::runtime_error("Json value is not of expected type");
        }

        inline void reset() {
            _type = _Type::Null;
            _value = "";
            _elements.clear();
            _members.clear();
        }

        inline void set(const data& other) {
            _type = other._type;
            _value = other._value;
            _elements = other._elements;
            _members = other._members;
        }

        inline void set(const char* text) {
            reset();
            if(!text) return;
            _type = _Type::String;
            _value = text;
        }

        inline void set(bool flag) {
            reset();
            _type = _Type::Boolean;
            _value = flag? grammar::_valueTrue : grammar::_valueFalse;
        }

        inline void set(int number) {
            reset();
            _type = _Type::Number;
            _value = std::to_string(number);
        }

        inline void set(double number) {
            reset();
            _type = _Type::Number;
            _value = std::to_string(number);
        }

        inline std::ostream& toStream(std::ostream& out) const {
            switch(_type) {
            default:
            case _Type::Null:
                out << grammar::_valueNull;
                break;
            case _Type::Number:
            case _Type::Boolean:
                out << _value;
                break;
            case _Type::String:
                out << grammar::_doubleQuotes;
                std::for_each(begin(_value), end(_value), [&](const auto& ch){ out << ch; });
                out << grammar::_doubleQuotes;
                break;
            }
            return out;
        }

        inline std::istream& fromStream(std::istream& in) {
            auto parsed = false;
            int ch;
            reset();
            while(-1 != (ch = in.peek())) {
                if(!parsed) {
                    if(grammar::is(grammar::_valueNull, ch)) {
                        std::string value;
                        while(-1 != (ch = in.peek())) {
                            if(!grammar::is(grammar::_valueNull, ch)) break;
                            value += (char)in.get();
                        }
                        if(grammar::_valueNull != value) throw std::invalid_argument("Unsupported data in input stream. NULL");
                        parsed = true;
                    } else if(grammar::is(grammar::_valueTrue, ch) || grammar::is(grammar::_valueFalse, ch)) {
                        while(-1 != (ch = in.peek())) {
                            if(!grammar::is(grammar::_valueTrue, ch) && !grammar::is(grammar::_valueFalse, ch)) break;
                            _value += (char)in.get();
                        }
                        if(grammar::_valueTrue != _value && grammar::_valueFalse != _value)
                            throw std::invalid_argument("Unsupported data in input stream. BOOL");
                        _type = _Type::Boolean;
                        parsed = true;
                    } else if(grammar::is(grammar::_digitStart, ch)) {
                        while(-1 != (ch = in.peek())) {
                            if(!grammar::is(grammar::_digit, ch)) break;
                            _value += (char)in.get();
                        }
                        if(!grammar::is_digit(_value))
                            throw std::invalid_argument("Unsupported data in input stream. NUMBER");
                        _type = _Type::Number;
                        parsed = true;
                    } else {
                        throw std::invalid_argument("Unsupported data in input stream");
                    }
                } else if(grammar::is(grammar::_patternWhitespaces, ch)) {
                    in.get(); // discard whitespaces
                } else {
                    throw std::invalid_argument("Unsupported data in input stream");
                }
            }
            return in;
        }
    };
}
