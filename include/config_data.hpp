#ifndef _CONFIG_PARSER_HPP_
#define _CONFIG_PARSER_HPP_

#include <string>
#include <fstream>
#include <iostream>
#include <map>

class config_data
{
private:
    std::string config_name;
    std::map<std::string, std::string> data;

public:
    void set_name(std::string);
    std::string get_name();

    std::map<std::string, std::string> get_data();

    int load_config_data(std::string path);

    void print_data();

    void export_html_data();

    config_data(std::string name, std::string path);
    ~config_data();
};

#endif //_CONFIG_PARSER_HPP_
