//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++ (supporting code)
// |  |  |__   |  |  | | | |  version 3.11.3
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2023 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT

#include "doctest_compatibility.h"

#define JSON_TESTS_PRIVATE
#include <nlohmann/json.hpp>
using nlohmann::json;

#include <clocale>

struct ParserImpl final: public nlohmann::json_sax<json>
{
    bool null() override
    {
        return true;
    }
    bool boolean(bool /*val*/) override
    {
        return true;
    }
    bool number_integer(json::number_integer_t /*val*/) override
    {
        return true;
    }
    bool number_unsigned(json::number_unsigned_t /*val*/) override
    {
        return true;
    }
    bool number_float(json::number_float_t /*val*/, const json::string_t& s) override
    {
        float_string_copy = s;
        return true;
    }
    bool string(json::string_t& /*val*/) override
    {
        return true;
    }
    bool binary(json::binary_t& /*val*/) override
    {
        return true;
    }
    bool start_object(std::size_t /*val*/) override
    {
        return true;
    }
    bool key(json::string_t& /*val*/) override
    {
        return true;
    }
    bool end_object() override
    {
        return true;
    }
    bool start_array(std::size_t /*val*/) override
    {
        return true;
    }
    bool end_array() override
    {
        return true;
    }
    bool parse_error(std::size_t /*val*/, const std::string& /*val*/, const nlohmann::detail::exception& /*val*/) override
    {
        return false;
    }

    ~ParserImpl() override;

    json::string_t float_string_copy;
};

ParserImpl::~ParserImpl() = default;

TEST_CASE("locale-dependent test (LC_NUMERIC=C")
{
    if (std::setlocale(LC_NUMERIC, "C") == nullptr)
    {
        WARN("could not set locale");
    }

    SECTION("parsing")
    {
        CHECK(json::parse("12.34").dump() == "12.34");
    }

    SECTION("SAX parsing")
    {
        ParserImpl sax {};
        json::sax_parse( "12.34", &sax );
        CHECK(sax.float_string_copy == "12.34");
    }
}

TEST_CASE("locale-dependent test (LC_NUMERIC=de_DE")
{
    if (std::setlocale(LC_NUMERIC, "de_DE") == nullptr)
    {
        WARN("could not set locale");
    }

    SECTION("parsing")
    {
        CHECK(json::parse("12.34").dump() == "12.34");
    }

    SECTION("SAX parsing")
    {
        ParserImpl sax {};
        json::sax_parse( "12.34", &sax );
        CHECK(sax.float_string_copy == "12.34");
    }
}
