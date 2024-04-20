#include "config_data.hpp"
#include "comparator.hpp"

int main(int argc, char const *argv[])
{
    config_data conf_zero("Linux", "/home/oboskovic/Desktop/projects/kernel-comparator/examples/linux-headers-6.5.0-18-generic/.config");
    config_data conf_one("Linux2", "/home/oboskovic/Desktop/projects/kernel-comparator/examples/linux-headers-6.5.0-28-generic/.config");

    // conf_zero.print_data();

    // conf_zero.export_html_data();

    comparator::compare_configs(conf_zero, conf_one);

    return 0;
}
