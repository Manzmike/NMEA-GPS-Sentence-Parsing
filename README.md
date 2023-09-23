# NMEA GPS Sentence Parser

## Introduction

In this project, you will develop a program to parse (interpret) information output by a standard GPS receiver. These messages, or sentences, conform to a specification by the National Marine Electronics Association (NMEA). The primary goal is to build a parsing state machine that can take the NMEA GPS sentences one byte at a time and correctly interpret them.

## Specifications

### Input:
   - NMEA GPS sentences in ASCII form.
   - Each sentence starts with `$`, followed by a 5-character sequence starting with `GP`. Only four message types are valid: GPGGA, GPGSA, GPGSV, and GPRMC.
   - Each sentence has a variable amount of message data.
   - Sentences end with a `*` character followed by two checksum characters in hexadecimal format.
   - Messages where the calculated checksum doesn't match the received checksum should be ignored.

### Output:
   - For every valid NMEA GPS sentence, the program should print:
     - Message type (e.g., GPGGA, GPGSA, GPGSV, GPRMC)
     - Message data (excluding `$`, `*`, and the checksum)
     - Message checksum

### Functionality:
   - Your program should be built as a state machine that reads one byte at a time.
   - Calculate the checksum from the message data and verify it.
   - Light LEDs based on the message type:
     - Green LED for GPGGA or GPRMC
     - Yellow LED for GPGSA
     - Red LED for any other type.

### Development:
   - Implement the parser using a C++ class.
   - Use the provided Python script to send messages to your parser.
   - Use the provided preliminary program (serial_read_start.cpp) as a starting point.

## How to Run

Given the instruction:

```bash
> ./prog1 /dev/pts/2
