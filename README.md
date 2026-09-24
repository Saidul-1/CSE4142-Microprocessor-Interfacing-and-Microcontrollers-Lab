# CSE4142: Microprocessor Interfacing and Microcontrollers Lab

## Overview

This repository contains the implementation of two fundamental communication protocols on STM32F446RETX microcontrollers:

- I2C Master-Slave Communication
- UART Transmitter-Receiver Communication

The project was developed as part of a Microcontroller Laboratory course with the goal of understanding low-level embedded communication. Instead of using STM32 HAL libraries, all peripherals were configured directly through STM32F446RETX memory-mapped registers.

The communication process was tested and verified using the debugging features of **STM32CubeIDE**, where register states and received data were monitored step-by-step.

---

## Objectives

- Implement communication protocols using direct register-level programming.
- Understand STM32F446RETX peripheral configuration.
- Configure GPIO pins for different alternate functions.
- Establish communication between multiple microcontrollers.
- Debug and verify embedded applications using STM32CubeIDE.

---

# Implemented Communication Protocols

## 1. I2C Master-Slave Communication

### Description

Two STM32F446RETX microcontrollers were configured to communicate using the I2C protocol.

One microcontroller operates as the **I2C Master**, responsible for initiating communication and transmitting data. The second microcontroller operates as the **I2C Slave**, which receives the transmitted data.

The implementation was performed by directly configuring the I2C1 peripheral registers.

### I2C Master Features

- I2C peripheral initialization
- GPIO configuration for I2C communication
- START condition generation
- Slave address transmission
- Byte-by-byte data transmission
- ACK status checking
- STOP condition generation

### I2C Slave Features

- Slave address configuration
- Address matching detection
- Data reception
- Received data storage for verification

### I2C Configuration

| Parameter | Value |
|-----------|-------|
| Microcontroller | STM32F446RETXxx |
| Peripheral | I2C1 |
| SCL Pin | PB8 |
| SDA Pin | PB9 |
| Alternate Function | AF4 |
| Slave Address | 0x12 |
| Communication Speed | 100 kHz |

### Data Transfer Example

The master continuously sends:

```
CSE-RU
```

The received data is inspected using STM32CubeIDE debugging tools.

---

# 2. UART Transmitter-Receiver Communication

## Description

UART communication was implemented between two STM32F446RETX microcontrollers.

One microcontroller works as a transmitter and sends serial data, while the other microcontroller receives and stores the incoming data.

The USART1 peripheral was configured manually using STM32F446RETX registers.

### UART Transmitter Features

- USART1 initialization
- GPIO alternate function configuration
- Baud rate configuration
- Transmitter enable
- Polling-based data transmission

### UART Receiver Features

- USART1 initialization
- Receiver enable
- Receive buffer monitoring
- Incoming data reading and storage

### UART Configuration

| Parameter | Value |
|-----------|-------|
| Microcontroller | STM32F446RETXxx |
| Peripheral | USART1 |
| TX Pin | PA9 |
| RX Pin | PA10 |
| Alternate Function | AF7 |
| Baud Rate | 9600 |
| Communication Mode | Polling |

### Data Transfer Example

The transmitter continuously sends:

```
CSE_RU
```

The received characters are verified using STM32CubeIDE debugging.

---

# Implementation Details

The project uses **bare-metal embedded C programming** without relying on hardware abstraction libraries.

The following STM32F446RETX peripherals were configured manually:

- RCC (Reset and Clock Control)
- GPIO
- I2C1
- USART1

## GPIO Configuration

Implemented configurations:

- Alternate Function Mode
- Open-drain output configuration for I2C
- Pull-up configuration
- UART alternate function mapping

## I2C Peripheral Configuration

Implemented:

- Peripheral clock enabling
- Software reset handling
- Clock frequency configuration
- Slave addressing
- Data register communication

## USART Peripheral Configuration

Implemented:

- Peripheral clock enabling
- Baud rate calculation
- Transmitter configuration
- Receiver configuration
- Data register communication

---

# Debugging and Verification

The communication systems were tested using **STM32CubeIDE debugging tools**.

Verification was performed by:

- Executing code step-by-step
- Monitoring peripheral registers
- Checking transmitted and received data
- Inspecting memory values during execution

---

# Hardware and Software Requirements

## Hardware

- STM32F446RETX Development Boards
- Communication wires for I2C/UART connection

## Software Tools

- STM32CubeIDE
- STM32F446RETX Reference Manual
- ARM Cortex-M Debugging Tools

---

# Key Learning Outcomes

- Developed practical understanding of embedded communication protocols.
- Implemented STM32 peripherals using register-level programming.
- Learned GPIO alternate function configuration.
- Worked with I2C master-slave architecture.
- Worked with UART serial communication.
- Gained experience in embedded debugging and verification.
