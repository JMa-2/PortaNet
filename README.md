# *TABLE OF CONTENTS*
- [Introduction](#introduction)
- [Hardware](#hardware)
    - [Hardware General](#hardware-general)
    - [Hardware Tools](#hardware-tools)
    - [Schematic](#schematic)
    - [PCB Layout](#pcb-layout)
    - [BOM](#bom)
- [Software](#software)
    - [Software General](#software-general)
    - [Software Tools](#software-tools)
    - [Architecture](#architecture)
    - [Building](#building)
    - [Flashing](#flashing)
- [How to Use](#how-to-use)
    - [Use General](#use-general)
    - [PuTTy](#putty)
    - [Console Commands](#console-commands)
<br>
<br>
<br>

# *INTRODUCTION*
The PortaNet is a wifi access point (AP) using the Espressif ESP32-C3FH4 microcontroller. The PortaNet holds the shape and connection types of a typical USB stick. The AP's settings can be modified via a serial console. At this point PuTTy is the only tested terminal emulator software for use with PortaNet.

<br>

![PortaNet v4.0](images/PXL_20220605_001243593_cropped.jpg)

<br>
<br>
<br>

# *HARDWARE*
### Hardware General
The design critical components consist of the [Espressif ESP32-C3FH4](https://www.espressif.com/en/products/socs/esp32-c3). The ESP32-C3FH4 microcontroller is a ESP32-C3 variant with 4MB internal flash. Simply buying the "normal" ESP32-C3 variant will not suffice due to the lack of internal flash.

The design utilizes a 50 $\Omega$ impedance, 2.4 GHz wifi antenna. Antennas such as [this](https://www.amazon.com/gp/product/B07D1Z3W7T/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) and [this](https://www.amazon.com/gp/product/B0991PKTDL/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) have worked successfully. There is an unused $\pi$-matching circuit that could aid in supporting other antennas.

### Hardware Tools
KiCad v6 was utilized as the EDA tool. The KiCad project can be found in the [hardware directory.](hardware/kicad/PortaNet/) Additionally my [KiCad Library](http://192.168.1.19:3000/JMa/KiCad_Library) may contain needed symbols and footprints that the project references.

### Schematic
The current schematics can be seen [here](hardware/kicad/PortaNet_SCH_v4_1.pdf).

### PCB Layout
### BOM

<br>
<br>
<br>

# *SOFTWARE*
### Software General
### Software Tools
### Architecture
### Building
### Flashing

<br>
<br>
<br>

# *HOW TO USE*
### Use General
### PuTTy
### Console Commands

<br>
<br>
<br>