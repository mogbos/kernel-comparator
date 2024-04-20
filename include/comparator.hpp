#ifndef _COMPARATOR_HPP_
#define _COMPARATOR_HPP_

#include <iostream>
#include <set>
#include <thread>
#include <mutex>
#include "config_data.hpp"

namespace comparator
{
    void add_config_to_set(std::set<std::string> *config_set, const std::map<std::string, std::string> &data);

    void compare_configs(config_data &config_1, config_data &config_2);
}

#endif // _COMPARATOR_HPP_