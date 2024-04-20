#include "config_data.hpp"

std::string comment_conf_str = "# CONFIG_";
std::string conf_str = "CONFIG_";

void config_data::set_name(std::string name)
{
    config_name = name;
}

std::string config_data::get_name()
{
    return config_name;
}

std::map<std::string, std::string> config_data::get_data()
{
    return data;
}

int config_data::load_config_data(std::string path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "Error opening file! (" << path << ")" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.substr(0, comment_conf_str.length()) == comment_conf_str)
        {
            size_t startPos = line.find("CONFIG_");
            size_t endPos = line.find_first_of(" \t", startPos);
            data.insert(std::pair<std::string, std::string>(line.substr(startPos, endPos - startPos), "n"));
        }
        else if (line.substr(0, conf_str.length()) == conf_str)
        {
            size_t startPos = line.find("CONFIG_");
            size_t endPos = line.find_first_of("=");
            data.insert(std::pair<std::string, std::string>(line.substr(startPos, endPos - startPos), line.substr(endPos + 1)));
        }
    }

    file.close(); // Close the file when done

    return 0;
}

void config_data::print_data()
{
    for (auto it = data.begin(); it != data.end(); it++)
    {
        std::cout << it->first << " : " << it->second << std::endl;
    }
}

void config_data::export_html_data()
{
    std::string filename = config_name + ".html";
    std::ofstream outputFile(filename.c_str());

    if (outputFile.is_open())
    {
        outputFile << "<html><head><title>" << config_name << "</title></head>"
                   << "<body>"
                   << "<style type=\"text/css\">.tg  {border-collapse:collapse;border-spacing:0;}"
                   << ".tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial,"
                   << " sans-serif;font-size:14px;overflow:hidden;padding:10px 5px;word-break:normal;}"
                   << ".tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial,"
                   << " sans-serif;font-size:14px;font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}"
                   << ".tg .tg-0lax{text-align:left;vertical-align:top}</style>"
                   << "<h1>" << config_name << "</h1>"
                   << "<table class=\"tg\">"
                   << "<thead>"
                   << "<tr>"
                   << "<th class=\"tg-0pky\">CONFIG_NAME</th><th class=\"tg-0pky\">VALUE</th>"
                   << "</tr>"
                   << "</thead>"
                   << "<tbody>";

        for (auto it = data.begin(); it != data.end(); it++)
        {
            outputFile << "<tr><td class=\"tg-0pky\">" << it->first << "</td><td class=\"tg-0pky\">" << it->second << "</td>";
        }

        outputFile << "</tbody></body>";
        outputFile.close();
    }
    else
    {
        // If the file couldn't be opened, print an error message
        std::cerr << "Error: Unable to open the file." << std::endl;
    }
}

config_data::config_data(std::string name, std::string path)
{
    set_name(name);
    load_config_data(path);
}

config_data::~config_data()
{
    config_name.clear();
    data.clear();
}