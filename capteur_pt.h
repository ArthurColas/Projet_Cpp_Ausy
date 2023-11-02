#ifndef CAPTEUR_PT_H
#define CAPTEUR_PT_H

#define RESET_CMD 0xB6

#define OVERSAMPLING_P_NONE 0b000
#define OVERSAMPLING_P_x1   0b001
#define OVERSAMPLING_P_x2   0b010
#define OVERSAMPLING_P_x4   0b011
#define OVERSAMPLING_P_x8   0b100
#define OVERSAMPLING_P_x16  0b101

#define OVERSAMPLING_T_NONE 0b000
#define OVERSAMPLING_T_x1   0b001
#define OVERSAMPLING_T_x2   0b010
#define OVERSAMPLING_T_x4   0b011
#define OVERSAMPLING_T_x8   0b100
#define OVERSAMPLING_T_x16  0b101

#define T_STANDBY_0p5   0b000
#define T_STANDBY_62p5  0b001
#define T_STANDBY_125   0b010
#define T_STANDBY_250   0b011
#define T_STANDBY_500   0b100
#define T_STANDBY_1000  0b101
#define T_STANDBY_2000  0b110
#define T_STANDBY_4000  0b111

#define IIR_FILTER_OFF  0b000
#define IIR_FILTER_x2   0b001
#define IIR_FILTER_x4   0b010
#define IIR_FILTER_x8   0b011
#define IIR_FILTER_x16  0b100

#define SLEEP_MODE      0b00
#define FORCED_MODE 0b01
#define NORMAL_MODE 0b11
#define PORT_BMP 1
#define FLAG 0

/// Base registres

#define BMP280_ADDR 0x76

#define DIG_T1 0x88
#define DIG_T2 0x8A
#define DIG_T3 0x8C

#define DIG_P1 0x8E
#define DIG_P2 0x90
#define DIG_P3 0x92
#define DIG_P4 0x94
#define DIG_P5 0x96
#define DIG_P6 0x98
#define DIG_P7 0x9A
#define DIG_P8 0x9C
#define DIG_P9 0x9E

#define DEVICE_ID 0xD0
#define RESET 0xE0
#define STATUS 0xF3
#define CTRL_MEAS 0xF4
#define CONFIG 0xF5
#define PRESSURE_0 0xF7
#define PRESSURE_1 0xF8
#define PRESSURE_2 0xF9
#define TEMPERATURE_0 0xFA
#define TEMPERATURE_1 0xFB
#define TEMPERATURE_2 0xFC

#define RESET_CMD 0xB6

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <pigpio.h>

class capteur_pt {
public:

    capteur_pt();

    void closeBMP(int handle);
    unsigned int twosComplement(unsigned int input);
    int initBMP();
    double readTemperature(int handle);

    double getTemperature();
    double getPression();

private:
};

#endif

