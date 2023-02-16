open_project -reset receiver

add_files rx_demo.cpp

add_files -tb rx_demo_tb.cpp

set_top rx_demo

# ############################
# solution

open_solution -reset "solution1" -flow_target vitis
set_part xczu9eg-ffvb1156-2-e

create_clock -period "200MHz"

csim_design

csynth_design

cosim_design

export_design -format ip_catalog