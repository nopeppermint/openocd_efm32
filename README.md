openocd_efm32
=============
First steps with openocd and efm32 with STM32F4Discovery and Olimex EM-32G880F128-STK

You find an example with Emblocks or you could flash your device in a terminal.

Discussion:
http://www.emblocks.org/forum/viewtopic.php?f=24&t=438
http://community.silabs.com/t5/32-Bit-Discussion/Program-Debug-EFM32-over-OpenOCD-with-an-ST-Link-V2/m-p/124380
https://www.olimex.com/forum/index.php?topic=771.0
_______________________________________________________
Bug in openocd-0.8.0

I tested this with the EM-32G880F128-STK Board and STM32F4Discovery Board.
I modified the file /openocd-0.8.0/scripts/target/efm32_stlink.cfg
-delete last line
cortex_m reset_config sysresetreq
because I alway get an error about "cortex_m"
http://sourceforge.net/p/openocd/mailman/message/32463675/
_______________________________________________________
To connect with the ST-LINK/V2 and the EFM32 
open openocd in a terminal with the following command:

Linux:
"openocd -f interface/stlink-v2.cfg -f target/efm32_stlink.cfg"

Windows x64 (in directory openocd-0.8.8/bin-x64):
"openocd-x64-0.8.0.exe -f interface/stlink-v2.cfg -f target/efm32_stlink.cfg"

Windows (in directory openocd-0.8.8/bin):
"openocd-0.8.0.exe -f interface/stlink-v2.cfg -f target/efm32_stlink.cfg"
_______________________________________________________
To erase and flash your device:
Linux:
open a second terminal

"telnet localhost 4444" 
"reset halt"
"flash write_image erase ../../bin/Debug/Basic_Example_EFM32G880F128-STK_EmBlocks.elf"
"reset"
now your device should run

Windows:
the same, but you have to do this with putty (insted of a second terminal)
_______________________________________________________
Useful commands:
//Reset device
"reset"

//halt device
"halt"

//actual events
"efm32.cpu eventlist"

//reset and halt device
"reset halt" 

//list all availlable flash (device must be in halt state)
flash list
"flash probe 0"

//erase sectors 0-255 (device must be in halt state)
"flash erase_sector 0 0 255"

//check if bank 0 is erased (device must be in halt state)
"flash erase_check 0"
_______________________________________________________________________________________
Useful Links:

EFM32 Openocd:
http://sourceforge.net/p/openocd/mailman/openocd-user/thread/5330AF5C.2000005@op.pl/

http://techwithdave.blogspot.ch/2013_07_01_archive.html

http://www.triplespark.net/elec/pdev/arm/stm32.html

Openocd install:
http://gnuarmeclipse.livius.net/blog/openocd-install/
