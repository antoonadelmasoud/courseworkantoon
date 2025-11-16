# Detailed Design Document

| **Author**              | ` Antoon Adel`                                       |
|:------------------------|:-----------------------------------------------------|
| **Status**              | `Draft`                          |
| **Version**             | `1.0`                                                |
| **Date**                | `16/11/2025`                                         |

## Introduction

This document provides a structured and comprehensive description of the test cases designed for the system under test.
It outlines the testing approach, methodology, and standards used to verify that all functional and non-functional requirements are met.
All test cases in this document are written using Robot Framework test case format, ensuring clarity, consistency, and full compatibility with automation workflows.
This document serves as a reference for developers, testers, and stakeholders to understand how the system will be validated and how test execution will be performed.
### Purpose

The purpose of this document is to define the testing objectives, approach, and structure for validating the system under test.
All test cases included in this plan must be written and documented using Robot Framework test case format, ensuring consistency, readability, and automation-readiness.
This document also ensures clear communication between QA and development teams, supports traceability, and provides a unified standard for test execution and reporting.

### Scope

The scope of this document covers the design, documentation, and execution of all automated test cases written using Robot Framework for the system under test.
This includes verifying that each module, feature, and interface behaves according to the defined requirements.

## Architectural Overview

@startuml
rectangle HMIApp #orange {
    rectangle Application

    rectangle MCU #green {
        rectangle LCD
        rectangle AlertLED
    }

    rectangle MCAL #skyblue {
        rectangle ADC
        rectangle DIO
        rectangle Register
    }

    Application -[hidden]-> MCU
    MCU -[hidden]-> MCAL
}
@enduml


### Assumptions & Constraints

@startuml
(*) --> init
--> configure
if LDR_value > High_Limit
  --> turn_on_alert
  --> (*)
else if LDR_value < Low_Limit
  --> turn_on_alert
  --> (*)
else
  --> turn_off_alert
  --> (*)
endif
@enduml


## Functional Description

Initialization: Sets up ADC, LCD, and DIO modules; prepares system for operation.

Sensor Acquisition: Reads LDR analog values via ADC; converts to raw value and percentage.

Threshold Monitoring: Compares LDR value with Low Limit (LL) and High Limit (LH).

Display Management: Updates LCD 16×2 with current LDR reading and configured limits using LCD_Screen(LL,LH,LDR).

Alert Mechanism: Activates LED/Buzzer when LDR reading is outside limits; deactivates when within limits.

Error Handling: Limits values to safe ranges; prevents LCD overflow and GPIO overcurrent.

Main Loop: Continuously reads sensor, processes data, updates display, and triggers alerts as needed.

## Implementation of the Module
This chapter discusses the detailed design of the module.

## Integration and Configuration
### Static Files
Typically a module consists of C and H files but other file types may exist. List all files that form this module

| File name | Contents                             |
|-----------|--------------------------------------|
| Main.ino | Application logic: integrates LCD, ADC, DIO modules         |
| DIO.c     | Source file: LED control, button reading, I/O init                |
| DIO.h    | Export interface: provides pin definitions & function APIs |
| LCD.c   | Source file: LCD initialization, commands, display logic |
| LCD.h    | Export interface for LCD driver functions |
| ADC.c    | Source file: ADC initialization and analog read function |
| ADC.h    | Export interface: ADC configuration & APIs |

### Include Structure
@startuml
package "HMI_LDR_Module" {
    
    [main.c] ..> [LCD.h] : includes
    [main.c] ..> [ADC.h] : includes
    [main.c] ..> [DIO.h] : includes
    [main.c] ..> [Config.h] : includes
    
    [LCD.c] ..> [LCD.h] : includes
    [ADC.c] ..> [ADC.h] : includes
    [DIO.c] ..> [DIO.h] : includes
    
    interface LCD_Interface
    interface ADC_Interface
    interface DIO_Interface

    LCD.c ..> LCD_Interface : provides
    ADC.c ..> ADC_Interface : provides
    DIO.c ..> DIO_Interface : provides
    
    note left of main.c
      Main application integrates
      all modules and runs the loop
    end note
}
@enduml

### Configuration
Any required hardware/software or system configuration that can be adjusted a header file shall be detailed in this section. This can be placed in the table below.
| Name | Value range | Description |
|------|-------------|-------------|
| MIN_LIMIT     |  0 – 1023           |  Minimum allowed threshold for LL and LH. Prevents values from decreasing below 0.           |
| MAX_LIMIT     |  0-1023           |   Maximum allowed threshold for LL and LH. Prevents values from exceeding the ADC max.          |
|  LH  |   0-1023 (default= 1000)          |  High limit threshold used to compare with sensor reading.           |
|  LL |    0-1023 (Defaut = 500)         |  Low limit threshold used to compare with sensor reading.           |
| sensor     |   0-1023          |   ADC reading value from channel 0.          |
| button1()     |  Pressed/Not Pressed           |    Increases high limit LH by +10 each press until MAX_LIMIT.         |
| button2()     | Pressed/Not Pressed            |   Decreases high limit LH by -10 each press until MIN_LIMIT.          |
|  button3() |    Pressed/Not Pressed         |  Increases low limit LL by +10 each press until MAX_LIMIT.           |
|  button4() |  Pressed/Not Pressed           |  Decreases low limit LL by -10 each press until MIN_LIMIT.           |
|  LCD_Display() |     --        |  Displays LL, LH, and Sensor values.           |
|  delay_ms_(100) |  1–1000 ms (Fixed 100 ms)      |System refresh delay between updates.  |

