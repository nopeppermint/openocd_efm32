openocd_efm32
=============

First steps with openocd and efm32 with STM32F4Discovery and Olimex EM-32G880F128-STK

I tested this with the EM-32G880F128-STK Board and STM32F4Discovery Board and I was able to reset and halt the device and read out some registers.
I modified the file /openocd-0.8.0/scripts/target/efm32_stlink.cfg
-delete last line
#cortex_m reset_config sysresetreq
because I alway get an error about "cortex_m"

Here you find a nice instruction how to install openocd

http://gnuarmeclipse.livius.net/blog/openocd-install/

To connect with the ST-LINK/V2 and the EFM32 open openocd in a terminal with the following command:

Linux:

"openocd -f interface/stlink-v2.cfg -f target/efm32_stlink.cfg"

Windows x64 (in directory openocd-0.8.8/bin-x64)

"openocd-x64-0.8.0.exe -f interface/stlink-v2.cfg -f target/efm32_stlink.cfg"

Windows (in directory openocd-0.8.8/bin)

"openocd-x64-0.8.0.exe -f interface/stlink-v2.cfg -f target/efm32_stlink.cfg"

Linux:

open a second Terminal

"telnet localhost 4444"

Windows:

the same, but you have to do this with putty for example


Useful Links:

EFM32 Openocd:
http://sourceforge.net/p/openocd/mailman/openocd-user/thread/5330AF5C.2000005@op.pl/

http://techwithdave.blogspot.ch/2013_07_01_archive.html

http://www.triplespark.net/elec/pdev/arm/stm32.html

Openocd install:
http://gnuarmeclipse.livius.net/blog/openocd-install/

Working example with Olimex Board (J-link, Colinkex):
https://github.com/nopeppermint/Olimex_EFM32_CoLinkEx_Example/tree/master/01_LCD_Example_EM-32G880F128-STK