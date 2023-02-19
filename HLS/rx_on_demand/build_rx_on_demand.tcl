open_project -reset rx_on_demand

add_files rx_ctrl.cpp

add_files -tb rx_ctrl_tb.cpp
set_top rx_ctrl

# ############################
# solution

open_solution -reset "solution1" -flow_target vitis
set_part xczu9eg-ffvb1156-2-e

create_clock -period "200MHz"

csim_design

csynth_design

# cosim_design

export_design -format ip_catalog