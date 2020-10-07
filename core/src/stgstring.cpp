//
// Created by Dmitry Khrykin on 15.06.2020.
//

#include <sstream>

#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <codecvt>
#include <locale>
#include <regex>
#include <utf8proc.h>

#include "stgstring.h"

namespace stg {

    auto make_string_uuid() -> std::string {
        auto uuid = boost::uuids::random_generator()();

        std::stringstream sstream;
        sstream << uuid;

        return sstream.str();
    }

    namespace string {

        auto utf8_fold_case(const std::string &str) -> std::string {
            auto *c_str = reinterpret_cast<const utf8proc_uint8_t *>(str.c_str());
            auto *lowered = reinterpret_cast<char *>(utf8proc_NFKC_Casefold(c_str));

            return std::unique_ptr<char>(lowered).get();
        }

        auto wstring_from_utf8_string(const std::string &str) -> std::wstring {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            return converter.from_bytes(str);
        }

        auto utf8_string_from_wstring(const std::wstring &wstr) -> std::string {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            return converter.to_bytes(wstr);
        }

        void strip_bounding_whitespaces(std::string &str) {
            str = std::regex_replace(str, std::regex("^\\s*"), "");
            str = std::regex_replace(str, std::regex("\\s*$"), "");
        }

    }

}