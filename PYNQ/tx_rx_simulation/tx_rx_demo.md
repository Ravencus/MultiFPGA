<!--
 * @Author: Zihan(Ravencus) Zheng
 * @Date: 2023-02-20 23:07:56
 * @LastEditors: Ravencus ravencus@gmail.com
 * @LastEditTime: 2023-02-20 23:14:03
 * @FilePath: /MultiFPGA/PYNQ/tx_rx_simulation/tx_rx_demo.md
 * @Description: 
 * 
-->
## Design under Test
* tx_on_demand
* rx_on_demand

## Brief Description
### tx_on_demand

1. Send four `ap_int<32> tmp = 7777` to indicate the start of transfer. (Why four?)
2. Send 1000 consecutive integers: `500, 499, ..., -498, -499`.
3. Write all sent data to a local buffer for comparison.

### rx_on_demand

1. Probing four `ap_int<32> tmp = 7777` to indicate the start of transfer.
2. Receive 1000 numbers.
3. Compare.

## Known Issue

1. Without the indicator the heads of the stream are unstable, i.e., duplicate numbers / unexpected large numbers.

2. Aurora clocking needs further study.

## Simulation Result
Shown in `rx_ctrl.ipynb` and `tx_ctrl.ipynb`
