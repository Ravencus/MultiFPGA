open_project -reset memory_kernel

add_files mem_sfpp.cpp

add_files -tb tb_mem_sfpp.cpp

set_top tb_mem_sfpp

# ############################
# solution

open_solution -reset "solution1" -flow_target vitis
set_part xczu7ev-ffvc1156-2-e

create_clock -period "200MHz"

csim_design