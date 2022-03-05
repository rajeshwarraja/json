// JavaScript Object Notation Data Interchange Format Library
// https://datatracker.ietf.org/doc/html/rfc8259
//
// The MIT License
// Copyright © 2022 Rajeshwar Raja
// Permission is hereby granted, free of charge, to any person obtaining a copy of 
// this software and associated documentation files (the “Software”), to deal in the Software 
// without restriction, including without limitation the rights to use, copy, modify, 
// merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit 
// persons to whom the Software is furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all copies 
// or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
// FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
// DEALINGS IN THE SOFTWARE.
//

#ifndef _JSON_H_
#define _JSON_H_

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
	constexpr const char* _patternWhitespaces = " \t\n\r";

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
	constexpr const char* _reverseSolidus = "\\";
	constexpr const char* _backspace = "\b";
	constexpr const char* _formFeed = "\f";
	constexpr const char* _lineFeed = "\n";
	constexpr const char* _carriageReturn = "\r";
	constexpr const char* _tab = "\t";
}

namespace json {
	namespace formatter {
		constexpr static size_t tab_width = 2;
		constexpr static std::ios_base::fmtflags pretty_flag = std::ios_base::fmtflags(0x9000);
		const static int indent_depth = std::ios_base::xalloc();
		inline long& indent(std::ostream& out) { return out.iword(indent_depth); }
	}
	inline std::ostream& pretty(std::ostream& out) { out.setf(formatter::pretty_flag); return out; }
	inline std::ostream& nopretty(std::ostream& out) { out.unsetf(formatter::pretty_flag); return out; }

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
		operator const char* () const {
			if (_type == _Type::Null) return nullptr;
			validate(_Type::String);
			return _value.c_str();
		}
		operator std::vector<data>() const { validate(_Type::Array); return _elements; }

		size_t length() const {
			if (_type != _Type::Array) throw std::invalid_argument("Unsupported object type; expected JSON array");
			return _elements.size();
		}

		const data& operator[](int index) const {
			if (_type != _Type::Array) throw std::invalid_argument("Unsupported object type; expected JSON array");
			if (_elements.size() <= index) throw std::invalid_argument("Index out-of-bounds");
			return _elements[index];
		}

		data& operator[](int index) {
			if (_type != _Type::Array) { reset(); _type = _Type::Array; }
			if (_elements.size() < index)
				_elements.resize(index + size_t(1));
			if (_elements.size() == index)
				_elements.push_back(json::data());
			return _elements[index];
		}

		bool has(const char* name) const {
			const auto itr = std::find_if(_members.begin(), _members.end(), [&](const auto& pair) { return pair.first == name; });
			return itr != _members.end();
		}

		const data& operator[](const char* name) const {
			if (_type != _Type::Object) throw std::invalid_argument("Unsupported object type; expected JSON object");
			const auto itr = std::find_if(_members.begin(), _members.end(), [&](const auto& pair) { return pair.first == name; });
			if (itr == _members.end()) throw std::invalid_argument("Member does not exists");
			return itr->second;
		}

		data& operator[](const char* name) {
			if (_type != _Type::Object) { reset(); _type = _Type::Object; }
			auto itr = std::find_if(_members.begin(), _members.end(), [&](const auto& pair) { return pair.first == name; });
			if (itr == _members.end()) {
				_members.push_back(std::make_pair(name, data()));
				return _members.back().second;
			}
			return itr->second;
		}

		bool operator==(const data& other) const {
			return _type == other._type && _value == other._value && _elements == other._elements && _members == other._members;
		}

		bool operator!=(const data& other) const {
			return !(*this == other);
		}

		friend std::ostream& operator<<(std::ostream& out, const data& json) { return json.toStream(out); }
		friend std::istream& operator>>(std::istream& in, data& json) { return json.fromStream(in); }

		static json::data emptyArray() { json::data arr; arr._type = _Type::Array; return arr; }

	private:
		_Type _type;
		std::string _value;
		std::vector<data> _elements;
		std::vector<std::pair<std::string, data>> _members;

		inline void validate(_Type type) const {
			if (_type != type)
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
			if (!text) return;
			_type = _Type::String;
			_value = text;
		}

		inline void set(bool flag) {
			reset();
			_type = _Type::Boolean;
			_value = flag ? grammar::_valueTrue : grammar::_valueFalse;
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
			const auto pretty = (out.flags() & formatter::pretty_flag) == formatter::pretty_flag;
			using namespace grammar;
			switch (_type) {
			default:
			case _Type::Null:
				out << _valueNull;
				break;
			case _Type::Number:
			case _Type::Boolean:
				out << _value;
				break;
			case _Type::String:
				out << _doubleQuotes;
				std::for_each(begin(_value), end(_value), [&](const auto& ch) {
					if (is_escaped(ch)) out << _reverseSolidus;
					if (is(_tab, ch)) out << 't';
					else if (is(_carriageReturn, ch)) out << 'r';
					else if (is(_lineFeed, ch)) out << 'n';
					else if (is(_formFeed, ch)) out << 'f';
					else if (is(_backspace, ch)) out << 'b';
					else out << ch;
					});
				out << _doubleQuotes;
				break;
			case _Type::Array:
				out << _beginArray;
				formatter::indent(out) += 1;
				std::for_each(_elements.begin(), _elements.end(), [&](const auto& element) {if (element != _elements.front()) out << _valueSeparator; if (pretty) out << std::endl << std::string(formatter::indent(out) * formatter::tab_width, u8' '); out << element; });
				formatter::indent(out) -= 1;
				if (pretty) out << std::endl << std::string(formatter::indent(out) * formatter::tab_width, u8' ');
				out << _endArray;
				break;
			case _Type::Object:
				out << _beginObject;
				formatter::indent(out) += 1;
				std::for_each(_members.begin(), _members.end(), [&](const auto& pair) { if (pair != _members.front()) out << _valueSeparator; if (pretty) out << std::endl << std::string(formatter::indent(out) * formatter::tab_width, u8' '); out << _doubleQuotes << pair.first << _doubleQuotes << _nameSeparator << (pretty? u8" " : u8"") << pair.second; });
				formatter::indent(out) -= 1;
				if (pretty) out << std::endl << std::string(formatter::indent(out) * formatter::tab_width, u8' ');
				out << _endObject;
				break;
			}
			return out;
		}

		inline std::istream& fromStream(std::istream& in) {
			using namespace grammar;
			auto parsed = false;
			int ch;
			reset();
			while (-1 != (ch = in.peek())) {
				if (!parsed) {
					if (is(_valueNull, ch)) {
						std::string value;
						while (-1 != (ch = in.peek())) {
							if (!is(_valueNull, ch)) break;
							value += (char)in.get();
						}
						if (_valueNull != value) throw std::invalid_argument("Unsupported data in input stream. NULL");
						parsed = true;
					}
					else if (is(_valueTrue, ch) || is(_valueFalse, ch)) {
						while (-1 != (ch = in.peek())) {
							if (!is(_valueTrue, ch) && !is(_valueFalse, ch)) break;
							_value += (char)in.get();
						}
						if (_valueTrue != _value && _valueFalse != _value)
							throw std::invalid_argument("Unsupported data in input stream. BOOL");
						_type = _Type::Boolean;
						parsed = true;
					}
					else if (is(_digitStart, ch)) {
						while (-1 != (ch = in.peek())) {
							if (!is(_digit, ch)) break;
							_value += (char)in.get();
						}
						if (!is_digit(_value))
							throw std::invalid_argument("Unsupported data in input stream. NUMBER");
						_type = _Type::Number;
						parsed = true;
					}
					else if (is(_doubleQuotes, ch)) {
						in.get(); // discard starting quote
						auto escaped = false;
						while (-1 != (ch = in.peek())) {
							if (*_doubleQuotes == ch && !escaped) break;
							escaped = !escaped && *_reverseSolidus == ch;
							if (escaped) {
								in.get(); // discard
								ch = in.peek();
								if ('b' == ch) { in.get(); _value += _backspace; escaped = false; }
								else if ('f' == ch) { in.get(); _value += _formFeed; escaped = false; }
								else if ('n' == ch) { in.get(); _value += _lineFeed; escaped = false; }
								else if ('r' == ch) { in.get(); _value += _carriageReturn; escaped = false; }
								else if ('t' == ch) { in.get(); _value += _tab; escaped = false; }
							}
							else {
								_value += (char)in.get();
							}
						}
						if (!is(_doubleQuotes, ch))
							throw std::invalid_argument("Unsupported data in input stream. STRING");
						in.get(); // discard ending quote
						_type = _Type::String;
						parsed = true;
					}
					else if (is(_beginArray, ch)) {
						in.get(); // discard starting array
						std::vector<data> elements;
						while (-1 != (ch = in.peek()) && *_endArray != ch) {
							if (is(_valueSeparator, ch) || is(_patternWhitespaces, ch)) { in.get(); continue; } // discard value separator
							data element;
							in >> element;
							elements.push_back(element);
						}
						in.get(); // discard endign array
						_type = _Type::Array;
						_elements = std::move(elements);
						parsed = true;
					}
					else if (is(_beginObject, ch)) {
						in.get(); // discard starting object
						std::vector<std::pair<std::string, data>> member;
						while (-1 != (ch = in.peek()) && *_endObject != ch) {
							if (is(_valueSeparator, ch) || is(_patternWhitespaces, ch)) { in.get(); continue; } // discard value separator
							data name; in >> name;
							if (name._type != _Type::String)
								throw std::invalid_argument("Unsupported data in input stream. OBJECT_NAME");
							while (-1 != (ch = in.peek()) && is(_patternWhitespaces, ch)) in.get(); // discard name separator
							if (-1 != (ch = in.peek()) && is(_nameSeparator, ch)) {
								in.get(); // discard name separator;
							}
							else {
								throw std::invalid_argument("Unsupported data in input stream. OBJECT");
							}
							data value; in >> value;
							member.push_back(std::make_pair((std::string)name, value));
						}
						in.get(); // discard ending object
						_type = _Type::Object;
						_members = std::move(member);
						parsed = true;
					}
					else if (is(_patternWhitespaces, ch)) {
						in.get(); // discard whitespaces
					}
					else {
						throw std::invalid_argument("Unsupported data in input stream");
					}
				}
				else if (is(_patternWhitespaces, ch)) {
					in.get(); // discard whitespaces
				}
				else if (parsed) {
					return in;
				}
				else {
					throw std::invalid_argument("Unsupported data in input stream");
				}
			}
			return in;
		}

		static bool is_digit(const std::string& text) { return std::regex_match(text, std::regex(grammar::_digitPattern)); }

		static bool is(const char* pattern, char ch) {
			return std::regex_match(&ch, &ch + 1, std::regex(std::string("[") + pattern + "]"));
		}

		static bool is_escaped(char ch) {
			return *grammar::_doubleQuotes == ch || *grammar::_reverseSolidus == ch || *grammar::_backspace == ch || *grammar::_formFeed == ch
				|| *grammar::_lineFeed == ch || *grammar::_carriageReturn == ch || *grammar::_tab == ch;
		}
	};
}

#endif