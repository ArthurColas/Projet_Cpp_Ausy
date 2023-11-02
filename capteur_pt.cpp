#include "capteur_pt.h"
#include <iostream>
#include <pigpio.h>

capteur_pt::capteur_pt() {

    int gpioStatus = gpioInitialise();
    if (gpioStatus < 0) {
        printf("Erreur d'init");
    }

}

void capteur_pt::closeBMP(int handle)
{
    i2cClose(handle);
}

unsigned int capteur_pt::twosComplement(unsigned int input)
{
    if (input > 32767)
        return input - (unsigned int)pow(2, 16);
    else
        return input;
}

int capteur_pt::initBMP()
{

    int handle = i2cOpen(PORT_BMP, BMP280_ADDR, FLAG);

    unsigned int ctrlMeasReg = NORMAL_MODE + (OVERSAMPLING_P_x16 << 2) + (OVERSAMPLING_T_x1 << 5);

    i2cWriteByteData(handle,CTRL_MEAS,ctrlMeasReg);

    unsigned int configReg = 0b000 + (IIR_FILTER_OFF << 2) + (T_STANDBY_1000 << 5);

    i2cWriteByteData(handle,CONFIG,configReg);

    return (handle);
}

double capteur_pt::readTemperature(int handle)
{
    unsigned int t1 = i2cReadWordData(handle, DIG_T1);
    unsigned int t2 = twosComplement(i2cReadWordData(handle, DIG_T2));
    unsigned int t3 = twosComplement(i2cReadWordData(handle, DIG_T3));

    char rawData[3];

    rawData[0] = i2cReadByteData(handle,TEMPERATURE_0);
    rawData[1] = i2cReadByteData(handle,TEMPERATURE_1);
    rawData[2] = i2cReadByteData(handle,TEMPERATURE_2);

    unsigned int adcT = (rawData[0] * (unsigned int)pow(2, 16) + rawData[1] * (unsigned int)pow(2, 8) + rawData[2]) >> 4;

    unsigned int var1 = ((adcT / 16384.0) - (t1 / 1024.0)) * t2;
    unsigned int var2 = ((adcT / 131072.0) - (t1 / 8192.0)) * (((adcT / 131072.0) - (t1 / 8192.0)) * t3);

    return ((double)(var1+var2) / 5120.0);
}

double capteur_pt::getTemperature() {

    int handle = initBMP();

    unsigned int t1 = i2cReadWordData(handle, DIG_T1);
    unsigned int t2 = twosComplement(i2cReadWordData(handle, DIG_T2));
    unsigned int t3 = twosComplement(i2cReadWordData(handle, DIG_T3));

    char rawData[3];

    rawData[0] = i2cReadByteData(handle,TEMPERATURE_0);
    rawData[1] = i2cReadByteData(handle,TEMPERATURE_1);
    rawData[2] = i2cReadByteData(handle,TEMPERATURE_2);

    unsigned int adcT = (rawData[0] * (unsigned int)pow(2, 16) + rawData[1] * (unsigned int)pow(2, 8) + rawData[2]) >> 4;

    unsigned int var1 = ((adcT / 16384.0) - (t1 / 1024.0)) * t2;
    unsigned int var2 = ((adcT / 131072.0) - (t1 / 8192.0)) * (((adcT / 131072.0) - (t1 / 8192.0)) * t3);

    closeBMP(handle);

    return ((double)(var1+var2) / 5120.0);

}

double capteur_pt::getPression() {

    int handle = initBMP();

    int p1 = i2cReadWordData(handle,DIG_P1);
    int p2 = twosComplement(i2cReadWordData(handle,DIG_P2));
    int p3 = twosComplement(i2cReadWordData(handle,DIG_P3));
    int p4 = twosComplement(i2cReadWordData(handle,DIG_P4));
    int p5 = twosComplement(i2cReadWordData(handle,DIG_P5));
    int p6 = twosComplement(i2cReadWordData(handle,DIG_P6));
    int p7 = twosComplement(i2cReadWordData(handle,DIG_P7));
    int p8 = twosComplement(i2cReadWordData(handle,DIG_P8));
    int p9 = twosComplement(i2cReadWordData(handle,DIG_P9));

        char rawData[3];

        rawData[0] = i2cReadByteData(handle,PRESSURE_0);
        rawData[1] = i2cReadByteData(handle,PRESSURE_1);
        rawData[2] = i2cReadByteData(handle,PRESSURE_2);

    int adcP = (rawData[0] * (int)pow(2, 16) + rawData[1] * (int)pow(2, 8) + rawData[2]) >> 4;

    int tFine = (int)readTemperature(handle)*5120.0;

    int var1 = (tFine / 2.0) - 64000.0;
    int var2 = (int)pow(var1,2) * p6 / 32768.0;

        var2 += var1 * p5 * 2.0;
    var2 = (var2 / 4.0) + (p4 * 65536.0);
    var1 = (p3 * (var1 * var1) / 524288.0 + (p2 * var1)) / 524288.0;
    var1 = (1.0 + (var1 / 32768.0)) * p1;

        double p = 1048576.0 - adcP;
    p = (p - (var2 / 4096.0)) * 6250.0 / var1;
    var1 = p9 * p * p / 2147483648.0;
    var2 = p * p8 / 32768.0;
    p += (var1 + var2 + p7) / 16.0;
    
        closeBMP(handle);

	return (double)(p / 100.0);
}
