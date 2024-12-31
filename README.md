# STM32F746NGH Bare Metal Programming

This is the repository of fundamental bare-metal drivers and programmes for the STM32F746NGH Discovery Board. 


## Using CMSIS header files

To use header files based on the Cortex Microcontroller Software Interface Standard (CMSIS) and STM32, we should include paths and symbols for the project.

For STM32CubeIDE, following the steps:
 1. Menu -> Projects -> C/C++ General tab -> Paths and Symbols
 2. Includes tab -> Add -> File Systems -> select folder "chip-header-files\CMSIS\Include"
 3. Includes tab -> Add -> File Systems -> select folder "chip-header-files\CMSIS\Device\ST\STM32F7xx\Include"
 4. Symbols tab -> Add -> Add name "STM32F746NGHx"
 5. Click Apply and Close
 
 
## Using USART communication over STLINK

According to the datasheet and schematic of STM32F74xxx, the pins used in F746 for VCP(Virtual COM port) connection are PA9 and PB7, which are USART1 TX and RX pins.