#include <cstdint>
#include "a2s_info_l4d2.h"

namespace unit_test {

    void test_convert_from_array();
    void test_json();

}

namespace unit_test::detail {

    extern uint8_t a2s_info_example[];
    L4D2::a2s_info_Response gen_with_example_case();
    void show_attributes(const L4D2::a2s_info_Response& a2s_info_struct);

}
