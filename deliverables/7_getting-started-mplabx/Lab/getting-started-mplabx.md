# **Quick Start Guide**

### 

## Required Materials


## Learning Objective

## What is MPLAB X IDE?
In this section of the course, we will be learning how to use another embedded programming program, MPLAB X IDE. MPLAB X IDE is a proprietary integrated development environment designed to work with Microchip's line of microcontrollers. It is most commonly used in professional or settings due to its encompassing set of developer features.

## Why use MPLAB X IDE over Arduino IDE?
Leading up to this lab, you have been developing relatively simple programs using Arduino IDE. So why switch over to MPLAB X IDE? The reason ultimately comes down to differences in features:

- MPLAB X IDE's debugger offers deeper manipulation of embedded code including the ability to directly modify chip register values
- MPLAB X IDE's project based development makes it easier to build out multi file programs than Arduino IDE's sketch based development.
- MPLAB X IDE is often regarded as a more professional developer environment as opposed to Arduino IDE



## Installation Walkthrough

1. Go to the MPLAB X download page on microchips website at https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide
2. Download the MPLAB X IDE installer (Windows)
3. Open the installer once it has finished downloading

## Tour of the Source Files

## Discover Portal

In this section, we will open MPLAB Discover. It is a searchable catalog for exploring project examples, documentation, 
tutorials, videos, source code and other resources for microcontroller devices.

1. Locate the MPLAB Discover icon in the toolbar menu.

    <img src="images/d.png" alt="d" width="500"/>

2. This will open the Discover Portal. In the search bar, you can search for AVR64DD32 to find resources for the microcontroller.

    <img src="images/d_2.png" alt="d_2" width="500"/>

## Content Manager

In this section, we will open the MCC Content Manager to update all libraries, drivers, and peripheral code 
related to the AVR64DD32. You need to have internet access to perform the updates.

1. Locate the 'CM' icon in the toolbar menu. Alternatively, access it by navigating to Tools -> MCC Content Manager.

    <img src="images/cm.png" alt="c" width="400"/>    <img src ="images/cm_2.png" alt="c_2" height="300"/>

2. In the search filters, open the 'Select Device' pull down menu under 'Device', then type 'AVR64DD32' to 
find the microcontroller. Click on it to select.

    <img src="images/cm_3.png" alt="c_3" width="400"/>

3. Click the Select Latest Version(s) button at the top center to choose the most recent versions of the libraries.

    <img src="images/cm_4.png" alt="c_4" width="400"/>

4. After performing this selection, click on 'Apply'.

    <img src="images/cm_5.png" alt="c_5" width="400"/>

5. Allow a few seconds for the libraries and drivers to download and install.

## Appendix
