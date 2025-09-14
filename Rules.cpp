#include "Rules.h"

std::unordered_map<std::string, std::unordered_map<std::string, int>> Rules = {
        {"Student", {{"MaxBooks", 3}, {"MaxDays", 14}}},
        {"Faculty", {{"MaxBooks", 10}, {"MaxDays", 30}}},
        {"Guest", {{"MaxBooks", 1}, {"MaxDays", 7}}}
};