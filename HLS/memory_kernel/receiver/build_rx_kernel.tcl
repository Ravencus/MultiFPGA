open_project -reset rx_kernel

add_files rx_kernel.cpp

set_top rx_kernel

# ############################
# solution

open_solution -reset "solution1" -flow_target vitis
set_part xczu9eg-ffvb1156-2-e

create_clock -period "100MHz"

# csim_design

csynth_design

# cosim_design

export_design -format ip_catalog