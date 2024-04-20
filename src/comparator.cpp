#include "comparator.hpp"

std::mutex g_mutex;

void comparator::add_config_to_set(std::set<std::string> *config_set, const std::map<std::string, std::string> &data)
{
    for (auto it = data.begin(); it != data.end(); it++)
    {
        g_mutex.lock();
        config_set->insert(it->first);
        g_mutex.unlock();
    }
}

void comparator::compare_configs(config_data &config_1, config_data &config_2)
{
    std::set<std::string> config_set;

    const auto &config_1_data = config_1.get_data();
    const auto &config_2_data = config_2.get_data();

    std::thread t1([&config_set, &config_1_data]()
                   { comparator::add_config_to_set(&config_set, std::ref(config_1_data)); });
    std::thread t2([&config_set, &config_2_data]()
                   { comparator::add_config_to_set(&config_set, std::ref(config_2_data)); });

    t1.join();
    t2.join();

    for (auto it = config_set.begin(); it != config_set.end(); it++)
    {
        if (config_1_data.find(it->data()) != config_1_data.end() && config_2_data.find(it->data()) != config_2_data.end())
        {
            if ((config_1_data.find(it->data()))->second != (config_2_data.find(it->data()))->second)
            {
                std::cout << it->data() << " : " << (config_1_data.find(it->data()))->second << " : " << (config_2_data.find(it->data()))->second << std::endl;
            }
        }

        // std::cout << it->data() << std::endl;
    }
}