# EZ-PD&trade; PMG1 MCU: I2C slave LED

This example demonstrates how the I2C block in the EZ-PD&trade; PMG1 MCU device can be used as a slave. An external I2C master sends commands, which are used to turn ON or OFF the user LED.

## Requirements

- [ModusToolbox&trade; software](https://www.cypress.com/products/modustoolbox-software-environment) v2.4 or later

  **Note:** This code example version requires ModusToolbox&trade; software version 2.3 or later and is not backward compatible with v2.2 or older versions.

- [Bridge Control Panel](https://www.cypress.com/products/psoc-programming-solutions) v1.22 or later
- Board support package (BSP) minimum required version: 1.0.0
- Programming language: C
- Associated parts: All [EZ-PD&trade; PMG1 MCU](https://www.cypress.com/PMG1) parts

## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm® embedded compiler v9.3.1 (`GCC_ARM`) - Default value of `TOOLCHAIN`
- Arm&reg; compiler v6.13 (`ARM`)
- IAR C/C++ compiler v8.42.2 (`IAR`)

## Supported kits (make variable 'TARGET')
- [EZ-PD&trade; PMG1-S0 MCU prototyping kit](https://www.cypress.com/CY7110) (`PMG1-CY7110`) - Default value of `TARGET`
- [EZ-PD&trade; PMG1-S1 MCU prototyping kit](https://www.cypress.com/CY7111) (`PMG1-CY7111`)
- [EZ-PD&trade; PMG1-S2 MCU prototyping kit](https://www.cypress.com/CY7112) (`PMG1-CY7112`) 
- [EZ-PD&trade; PMG1-S3 MCU prototyping kit](https://www.cypress.com/CY7113) (`PMG1-CY7113`)


## Hardware setup

This example uses the board's default configuration. See the kit user guide to ensure that the board is configured correctly.

The USB-C port on the board should be connected to a USB Type-C or USBPD-enabled power adapter for operation.

EZ-PD&trade; PMG1 MCU is connected to the KitProg3 via the 10-pin header which includes the I2C connections, SCL, and SDA. [Table 1](#table-1-KitProg3-I2C-SCL-and-SDA-connections) list the kits and connections with their corresponding port number.
These pins are configurable in the Device Configurator.

**Table 1. KitProg3 I2C SCL and SDA connections**

| KitProg3 pin connection  | I2C_SCL(J3.4) | I2C_SDA(J3.6) | SWDIO(J3.9) | SWDCLK(J3.7) |
| :-------  | :-------  | :-------  | :-------  | :--------  |
| PMG1-CY7110    | (J7.6)/(P2.3) | (J7.7)/(P2.2) | (J7.10)/(P0.0) | (J7.9)/(P0.1)    |
| PMG1-CY7111    | (J7.6)/(P5.1) | (J7.7)/(P5.0) | (J7.10)/(P1.4) | (J7.9)/(P1.0)    |
| PMG1-CY7112    | (J7.6)/(P0.1) | (J7.7)/(P0.0) | (J7.10)/(P2.0) | (J7.9)/(P2.1)    |
| PMG1-CY7113    | (J7.7)/(P4.0) | (J7.6)/(P4.1) | (J7.16)/(P1.2) | (J7.17)/(P1.1)    |


## Software setup

This example uses [Bridge Control Panel](https://www.cypress.com/products/psoc-programming-solutions) to send commands to KitProg3 on the kit. Bridge Control Panel is a tool included in the installation of PSOC&trade; Programmer. Once PSOC&trade; Programmer is installed, Bridge Control Panel can be accessed in the installation directory ( Example of an installation directory: *C:\Program Files (x86)\Cypress\Programmer\Bridge Control Panel\1.22.0\USBtoI2C.exe*). 

## Using the code example

Create the project and open it using one of the following:

<details><summary><b>In Eclipse IDE for ModusToolbox&trade; software</b></summary>

1. Click the **New Application** link in the **Quick Panel** (or, use **File** > **New** > **ModusToolbox Application**). This launches the [Project Creator](https://www.cypress.com/ModusToolboxProjectCreator) tool.

2. Pick a kit supported by the code example from the list shown in the **Project Creator - Choose Board Support Package (BSP)** dialog.

   When you select a supported kit, the example is reconfigured automatically to work with the kit. To work with a different supported kit later, use the [Library Manager](https://www.cypress.com/ModusToolboxLibraryManager) to choose the BSP for the supported kit. You can use the Library Manager to select or update the BSP and firmware libraries used in this application. To access the Library Manager, click the link from the **Quick Panel**.

   You can also just start the application creation process again and select a different kit.

   If you want to use the application for a kit not listed here, you may need to update the source files. If the kit does not have the required resources, the application may not work.

3. In the **Project Creator - Select Application** dialog, choose the example by enabling the checkbox.

4. (Optional) Change the suggested **New Application Name**.

5. The **Application(s) Root Path** defaults to the Eclipse workspace which is usually the desired location for the application. If you want to store the application in a different location, you can change the *Application(s) Root Path* value. Applications that share libraries should be in the same root path.

6. Click **Create** to complete the application creation process.

For more details, see the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.cypress.com/MTBEclipseIDEUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/ide_{version}/docs/mt_ide_user_guide.pdf*).

</details>

<details><summary><b>In command-line interface (CLI)</b></summary>

ModusToolbox&trade; software provides the Project Creator as both a GUI tool and the command line tool, "project-creator-cli". The CLI tool can be used to create applications from a CLI terminal or from within batch files or shell scripts. This tool is available in the *{ModusToolbox&trade; software install directory}/tools_{version}/project-creator/* directory.

Use a CLI terminal to invoke the "project-creator-cli" tool. On Windows, use the command line "modus-shell" program provided in the ModusToolbox&trade; software installation instead of a standard Windows command-line application. This shell provides access to all ModusToolbox&trade; software tools. You can access it by typing `modus-shell` in the search box in the Windows menu. In Linux and macOS, you can use any terminal application.

This tool has the following arguments:

Argument | Description | Required/optional
---------|-------------|-----------
`--board-id` | Defined in the `<id>` field of the [BSP](https://github.com/Infineon?q=bsp-manifest&type=&language=&sort=) manifest | Required
`--app-id`   | Defined in the `<id>` field of the [CE](https://github.com/Infineon?q=ce-manifest&type=&language=&sort=) manifest | Required
`--target-dir`| Specify the directory in which the application is to be created if you prefer not to use the default current working directory | Optional
`--user-app-name`| Specify the name of the application if you prefer to have a name other than the example's default name | Optional

<br>

The following example will clone the "[I2c slave LED](https://github.com/infineon/mtb-example-pmg1-i2c-slave-led)" application with the desired name "I2cSlaveLed" configured for the *PMG1-CY7110* BSP into the specified working directory, *C:/mtb_projects*:

   ```
   project-creator-cli --board-id PMG1-CY7110 --app-id mtb-example-pmg1-i2c-slave-led --user-app-name I2cSlaveLed --target-dir "C:/mtb_projects"
   ```

**Note:** The project-creator-cli tool uses the `git clone` and `make getlibs` commands to fetch the repository and import the required libraries. For details, see the "Project creator tools" section of the [ModusToolbox&trade; software user guide](https://www.cypress.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*).

</details>

<details><summary><b>In third-party IDEs</b></summary>

Use one of the following options:

- **Use the standalone [Project Creator](https://www.cypress.com/ModusToolboxProjectCreator) tool:**

   1. Launch Project Creator from the Windows Start menu or from *{ModusToolbox&trade; software install directory}/tools_{version}/project-creator/project-creator.exe*.

   2. In the initial **Choose Board Support Package** screen, select the BSP, and click **Next**.

   3. In the **Select Application** screen, select the appropriate IDE from the **Target IDE** drop-down menu.

   4. Click **Create** and follow the instructions printed in the bottom pane to import or open the exported project in the respective IDE.

<br>

- **Use command-line interface (CLI):**

   1. Follow the instructions from the **In command-line interface (CLI)** section to create the application, and then import the libraries using the `make getlibs` command.

   2. Export the application to a supported IDE using the `make <ide>` command.

   3. Follow the instructions displayed in the terminal to create or import the application as an IDE project.

For a list of supported IDEs and more details, see the "Exporting to IDEs" section of the [ModusToolbox&trade; software user guide](https://www.cypress.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*).

</details>


## Operation

1. Connect the EZ-PD&trade; PMG1 MCU kit to your PC using the provided USB cable through the KitProg3 USB connector.

2. Verify the power selection jumper (J5) is placed at position 2-3 to enable programming.

3. Program the board using one of the following:

   <details><summary><b>Using Eclipse IDE for ModusToolbox&trade; software</b></summary>

      1. Select the application project in the Project Explorer.

      2. In the **Quick Panel**, scroll down, and click **\<Application Name> Program (KitProg3_MiniProg4)**.
   </details>

   <details><summary><b>Using CLI</b></summary>

     From the terminal, execute the `make program` command to build and program the application using the default toolchain to the default target. The default toolchain and target are specified in the application's Makefile but you can override those values manually:
      ```
      make program TARGET=<BSP> TOOLCHAIN=<toolchain>
      ```

      Example:
      ```
      make program TARGET=PMG1-CY7110 TOOLCHAIN=GCC_ARM
      ```
   </details>


4. After programming, place the power selection jumper (J5) at position 1-2 and connect the USB Type-C connector (J10) on the kit to a USBPD source device via the USB Type-C to Type-C cable.
As soon as the kit is programmed and USBPD(J10) port is connected, LED3 will be in the OFF state at the start.

5. Open Bridge Control Panel and connect to KitProg3 under the listed ports. 

6. I2C pins from KitProg3 are already connected to the assigned pins on each EZ-PD&trade; PMG1 MCU prototyping kit. See the kit user guide for details.
 
7. Send the I2C commands on the Bridge Control Panel in the following format to turn ON the user LED: `w 08 00 01 00 17 p`. Similarly to turn OFF the user LED, send the following command from Bridge control Panel:  `w 08 00 01 01 17 p`

If the command is 0, the user LED will turn ON. If the command is 1, the user LED will turn OFF.

   <img src = "images/pmg1_bcp.png" width = "900"/>

## Debugging

You can debug the example to step through the code. In the IDE, use the **\<Application Name> Debug (KitProg3_MiniProg4)** configuration in the **Quick Panel**. For details, see the "Program and debug" section in the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.cypress.com/MTBEclipseIDEUserGuide).

## Design and implementation

**Figure 1. Firmware flowchart**

<img src = "images/flowchart.png" width = "300"/>
<br>

An SCB block configured as an EZI2C slave peripheral is used here. To implement the EZI2C slave peripheral based on the SCB hardware block, EZI2C slave peripheral driver library APIs are used. 

The EZI2C slave peripheral is initialized with the following settings:
   - The data rate is set to 100kbps.
   - The slave address is set to 0x08.
   - The clock input of the block is connected to a 12-MHz PERI-derived clock.
   - The Wake from Deep Sleep on address match is disabled
   - The number of addresses is set to 1.
   
The EZI2C requires the I2C master to start the operation with sending a base address that is one or two bytes before sending the data. Following the base address, there is a sequence of bytes wrriten into the buffer starting from the base address location. In this code example, base address is set to 0.

**Figure 2. EZI2C slave configuration for EZ-PD&trade; PMG1-S0 MCU**
<img src = "images/i2c_slave_configuration.png" />
<br>

**Note:** For EZ-PD&trade; PMG1-S0 MCU, SCB1 is used for EZI2C slave.

**Figure 3. I2C slave pin configuration for EZ-PD&trade; PMG1-S0 MCU**
<img src = "images/i2c_slave_pins.png" />
<br>

### Packet format sent by the master to the slave

The master sends a command packet to the slave via I2C to control the status of the LED. The packet must follow the format as specified, a `Start of Packet (SoP)` followed by the command and then the `End of Packet (EoP)`. The command is executed only if the SoP and EoP are correctly received.

| SoP  | LED status | EoP  |
|------|------------|------|
| 0x01 | 0x00 or 0x01 | 0x17 |


### Resources and settings

**Table 2. Application resources**

| Resource  | Alias/Object   | Purpose                                  |
| :-------  | :------------  | :------------------------------------    |
| LED (BSP) | CYBSP_USER_LED | User LED to indicate connection state    |
| SCB (BSP)	| CYBSP_EZI2C	  | I2C slave block used for reading commands|

## Related resources

Resources  | Links
-----------|----------------------------------
Application notes  | [AN232553](https://www.cypress.com/documentation/application-notes/an232553) - Getting started with EZ-PD&trade; PMG1 MCU on ModusToolbox&trade; <br> [AN232565](https://www.cypress.com/documentation/application-notes/an232565) - EZ-PD&trade; PMG1 MCU hardware design guidelines and checklist 
Code examples  | [Using ModusToolbox&trade; software](https://github.com/infineon/code-examples-for-ModusToolbox-software) on GitHub
Device documentation |  [EZ-PD&trade; PMG1 MCU datasheets](https://www.cypress.com/PMG1DS)                                                                       
Development kits | Visit www.cypress.com/microcontrollers-mcus-kits and use the options in the **Select your kit** section to filter kits by *Product family* or *Features*.                                        
Libraries on GitHub  | [mtb-pdl-cat2](https://github.com/infineon/mtb-pdl-cat2) - Peripheral driver library (PDL) and docs  <br> [mtb-hal-cat2](https://github.com/infineon/mtb-hal-cat2) - Hardware abstraction layer (HAL) library and docs   
Tools | [Eclipse IDE for ModusToolbox&trade; software](https://www.cypress.com/modustoolbox) <br> ModusToolbox&trade; software is a collection of easy-to-use software and tools enabling rapid development with Infineon MCUs, covering applications from embedded sense and control to wireless and cloud-connected systems using AIROC&trade; Wi-Fi and Bluetooth® connectivity devices.

<br>


## Other resources

Cypress provides a wealth of data at www.cypress.com to help you select the right device, and quickly and effectively integrate it into your design.

## Document history

Document title: *CE233649* - *EZ-PD&trade; PMG1 MCU: I2C slave LED*

| Version | Description of change |
| ------- | --------------------- |
| 1.0.0   | New code example      |
------

© Cypress Semiconductor Corporation, 2022. This document is the property of Cypress Semiconductor Corporation, an Infineon Technologies company, and its affiliates (“Cypress”). This document, including any software or firmware included or referenced in this document (“Software”), is owned by Cypress under the intellectual property laws and treaties of the United States and other countries worldwide. Cypress reserves all rights under such laws and treaties and does not, except as specifically stated in this paragraph, grant any license under its patents, copyrights, trademarks, or other intellectual property rights. If the Software is not accompanied by a license agreement and you do not otherwise have a written agreement with Cypress governing the use of the Software, then Cypress hereby grants you a personal, non-exclusive, nontransferable license (without the right to sublicense) (1) under its copyright rights in the Software (a) for Software provided in source code form, to modify and reproduce the Software solely for use with Cypress hardware products, only internally within your organization, and (b) to distribute the Software in binary code form externally to end users (either directly or indirectly through resellers and distributors), solely for use on Cypress hardware product units, and (2) under those claims of Cypress’s patents that are infringed by the Software (as provided by Cypress, unmodified) to make, use, distribute, and import the Software solely for use with Cypress hardware products. Any other use, reproduction, modification, translation, or compilation of the Software is prohibited.
<br>
TO THE EXTENT PERMITTED BY APPLICABLE LAW, CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH REGARD TO THIS DOCUMENT OR ANY SOFTWARE OR ACCOMPANYING HARDWARE, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  No computing device can be absolutely secure.  Therefore, despite security measures implemented in Cypress hardware or software products, Cypress shall have no liability arising out of any security breach, such as unauthorized access to or use of a Cypress product. CYPRESS DOES NOT REPRESENT, WARRANT, OR GUARANTEE THAT CYPRESS PRODUCTS, OR SYSTEMS CREATED USING CYPRESS PRODUCTS, WILL BE FREE FROM CORRUPTION, ATTACK, VIRUSES, INTERFERENCE, HACKING, DATA LOSS OR THEFT, OR OTHER SECURITY INTRUSION (collectively, "Security Breach").  Cypress disclaims any liability relating to any Security Breach, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any Security Breach.  In addition, the products described in these materials may contain design defects or errors known as errata which may cause the product to deviate from published specifications. To the extent permitted by applicable law, Cypress reserves the right to make changes to this document without further notice. Cypress does not assume any liability arising out of the application or use of any product or circuit described in this document. Any information provided in this document, including any sample design information or programming code, is provided only for reference purposes.  It is the responsibility of the user of this document to properly design, program, and test the functionality and safety of any application made of this information and any resulting product.  "High-Risk Device" means any device or system whose failure could cause personal injury, death, or property damage.  Examples of High-Risk Devices are weapons, nuclear installations, surgical implants, and other medical devices.  "Critical Component" means any component of a High-Risk Device whose failure to perform can be reasonably expected to cause, directly or indirectly, the failure of the High-Risk Device, or to affect its safety or effectiveness.  Cypress is not liable, in whole or in part, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any use of a Cypress product as a Critical Component in a High-Risk Device. You shall indemnify and hold Cypress, including its affiliates, and its directors, officers, employees, agents, distributors, and assigns harmless from and against all claims, costs, damages, and expenses, arising out of any claim, including claims for product liability, personal injury or death, or property damage arising from any use of a Cypress product as a Critical Component in a High-Risk Device. Cypress products are not intended or authorized for use as a Critical Component in any High-Risk Device except to the limited extent that (i) Cypress’s published data sheet for the product explicitly states Cypress has qualified the product for use in a specific High-Risk Device, or (ii) Cypress has given you advance written authorization to use the product as a Critical Component in the specific High-Risk Device and you have signed a separate indemnification agreement.
<br>
Cypress, the Cypress logo, and combinations thereof, WICED, ModusToolbox, PSoC, CapSense, EZ-USB, F-RAM, and Traveo are trademarks or registered trademarks of Cypress or a subsidiary of Cypress in the United States or in other countries. For a more complete list of Cypress trademarks, visit cypress.com. Other names and brands may be claimed as property of their respective owners.
