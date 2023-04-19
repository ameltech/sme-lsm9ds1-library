/*
 * LSM9DS1_Sensor.c
 *
 * Created: 05/01/2015 19:49:04
 *  Author: speirano
 */

#include "Wire.h"
#include "LSM9DS1Reg.h"
#include "LSM9DS1.h"

float a_lsb_sensitivity = A_LSB_SENSITIVITY_2MG; //  FC[1:0] register set to 0
inline float LSM9DS1_get_a_lsb_sensitivity(void)
{
    return a_lsb_sensitivity;
}

float g_lsb_sensitivity = G_LSB_SENSITIVITY_245MDPS; //  FC[1:0] register set to 0
inline float LSM9DS1_get_g_lsb_sensitivity(void)
{
    return g_lsb_sensitivity;
}

float m_lsb_sensitivity = M_LSB_SENSITIVITY_4MG; //  FC[1:0] register set to 0
inline float LSM9DS1_get_m_lsb_sensitivity(void)
{
    return m_lsb_sensitivity;
}

// Read a single byte from addressToRead and return it as a byte
byte LSM9DS1::readRegister(byte slaveAddress, byte regToRead)
{
    Wire.beginTransmission(slaveAddress);
    Wire.write(regToRead);
    Wire.endTransmission(false); // endTransmission but keep the connection active

    Wire.requestFrom(slaveAddress, 1); // Ask for 1 byte, once done, bus is released by default

    while (!Wire.available())
        ;               // Wait for the data to come back
    return Wire.read(); // Return this one byte
}

// Writes a single byte (dataToWrite) into regToWrite
bool LSM9DS1::writeRegister(byte slaveAddress, byte regToWrite, byte dataToWrite)
{
    uint8_t errorNo;
    Wire.beginTransmission(slaveAddress);

    if (!Wire.write(regToWrite))
    {
        return false;
    }
    if (!Wire.write(dataToWrite))
    {
        return false;
    }

    errorNo = Wire.endTransmission(); // Stop transmitting
    return (errorNo == 0);
}

LSM9DS1::LSM9DS1(unsigned int address) : _address(address)
{
    _ready_reg = 0;
    _status_reg = 0;
    _x = 0;
    _y = 0;
    _z = 0;
}

bool LSM9DS1::readInternal(unsigned char high_reg, unsigned char low_reg, int *value)
{
    uint16_t data = 0;
    unsigned char read = 0;
    int16_t signed_data = 0;

    for (;;)
    {
        read = readRegister(addr(), _status_reg);
        if (read & _ready_reg)
        {
            read = readRegister(addr(), low_reg);
            data = read; // LSB

            read = readRegister(addr(), high_reg);
            data |= read << 8; // MSB

            signed_data = data;
            *value = signed_data;
            return true;
        }
        else
        {
            delay(1);
        }
    }

    return false;
}

/*****************************************************************************/
/*                         Accelerometer / Gyroscope                         */
/*****************************************************************************/

LSM9DS1_A::LSM9DS1_A(void) : LSM9DS1(LSM9DS1_AG_ADDRESS)
{
    _ready_reg = AG_ACCELEROMETER_READY;
    _status_reg = AG_STATUS_REG;
}

bool LSM9DS1_A::begin(void)
{
    uint8_t data;

    data = readRegister(addr(), AG_WHO_AM_I);
    if (data == AG_WHO_AM_I_RETURN)
    {
        if (activate())
        {
            return true;
        }
    }
    return false;
}

bool LSM9DS1_A::activate(void)
{
    uint8_t data;

    data = readRegister(addr(), AG_CTRL_REG1_G);
    // data |= POWER_UP;
    data |= AG_ODR_SET;
    writeRegister(addr(), AG_CTRL_REG1_G, data);

    return true;
}

bool LSM9DS1_A::deactivate(void)
{
    uint8_t data;

    data = readRegister(addr(), AG_CTRL_REG1_G);
    data &= ~AG_ODR_SET;
    writeRegister(addr(), AG_CTRL_REG1_G, data);

    return true;
}

int LSM9DS1_A::readX()
{
    int data = 0;
    if (readInternal(AG_ACC_X_H, AG_ACC_X_L, &data))
    {
        _x = data;
    }
    // Decode Accel x-axis  [mdps measurement unit]
    return (a_lsb_sensitivity * _x);
}

int LSM9DS1_A::readY()
{
    int data = 0;
    if (readInternal(AG_ACC_Y_H, AG_ACC_Y_L, &data))
    {
        _y = data;
    }
    // Decode Accel y-axis  [mdps measurement unit]
    return (a_lsb_sensitivity * _y);
}

int LSM9DS1_A::readZ()
{
    int data = 0;
    if (readInternal(AG_ACC_Z_H, AG_ACC_Z_L, &data))
    {
        _z = data;
    }
    // Decode Accel z-axis  [mdps measurement unit]
    return (a_lsb_sensitivity * _z);
}

LSM9DS1_G::LSM9DS1_G(void) : LSM9DS1(LSM9DS1_AG_ADDRESS)
{
    _ready_reg = AG_GYROSCOPE_READY;
    _status_reg = AG_STATUS_REG;
}

bool LSM9DS1_G::begin(void)
{
    uint8_t data;

    data = readRegister(addr(), AG_WHO_AM_I);
    if (data == AG_WHO_AM_I_RETURN)
    {
        if (activate())
        {
            return true;
        }
    }
    return false;
}

bool LSM9DS1_G::activate(void)
{
    uint8_t data;

    data = readRegister(addr(), AG_CTRL_REG1_G);
    // data |= POWER_UP;
    data |= AG_ODR_SET;
    writeRegister(addr(), AG_CTRL_REG1_G, data);

    return true;
}

bool LSM9DS1_G::deactivate(void)
{
    uint8_t data;

    data = readRegister(addr(), AG_CTRL_REG1_G);
    data &= ~AG_ODR_SET;
    writeRegister(addr(), AG_CTRL_REG1_G, data);
    return true;
}

int LSM9DS1_G::readX()
{
    int data = 0;
    if (readInternal(AG_GYR_X_H, AG_GYR_X_L, &data))
    {
        _x = data;
    }
    // Decode Gyroscope x-axis  [mdps measurement unit]
    return (g_lsb_sensitivity * _x);
}

int LSM9DS1_G::readY()
{
    int data = 0;
    if (readInternal(AG_GYR_Y_H, AG_GYR_Y_L, &data))
    {
        _y = data;
    }
    // Decode Gyroscope y-axis  [mdps measurement unit]
    return (g_lsb_sensitivity * _y);
}

int LSM9DS1_G::readZ()
{
    int data = 0;
    if (readInternal(AG_GYR_Z_H, AG_GYR_Z_L, &data))
    {
        _z = data;
    }
    // Decode Gyroscope z-axis  [mdps measurement unit]
    return (g_lsb_sensitivity * _z);
}

/*****************************************************************************/
/*                                Magnetometer                               */
/*****************************************************************************/

LSM9DS1_M::LSM9DS1_M(void) : LSM9DS1(LSM9DS1_M_ADDRESS)
{
    _ready_reg = M_ZYX_AXIS_READY;
    _status_reg = M_STATUS_REG;
}

bool LSM9DS1_M::begin(void)
{
    uint8_t data;

    data = readRegister(addr(), M_WHO_AM_I);
    if (data == M_WHO_AM_I_RETURN)
    {
        if (activate())
        {
            return true;
        }
    }
    return false;
}

bool LSM9DS1_M::activate(void)
{
    uint8_t data;
    union u_LSM9DS1_REG_CTRL_REG1_M ctrl_reg1_m;
    union u_LSM9DS1_REG_CTRL_REG4_M ctrl_reg4_m;

    data = readRegister(addr(), M_CTRL_REG3_G);
    // data |= POWER_UP;
    // data |= 0x21;
    data &= ~M_OPER_MODE_DIS;
    // data &= (0xFC);

    writeRegister(addr(), M_CTRL_REG3_G, data);

    /* Magnetometer configuration registers */
    ctrl_reg1_m.byte = 0;
    ctrl_reg1_m.byte = LSM9DS1_DO_M_80_000_HZ;
    /* "LOW_POWER" permite operar o magnetômetro a 1 kHz. */
    /* q->ctrl_reg1_m.operative_mode_xy = LSM9DS1_OM_M_ULTRA_HIGH_PERFORMANCE; */
    ctrl_reg1_m.operative_mode_xy = LSM9DS1_OM_M_LOW_POWER;
    ctrl_reg1_m.fast_odr = 1;
    ctrl_reg1_m.temp_comp = 1;
    writeRegister(addr(), M_CTRL_REG1_G, data);

    ctrl_reg4_m.byte = 0;
    /* "LOW_POWER" permite operar o magnetômetro a 1 kHz. */
    /* ctrl_reg4_m.operative_mode_z = LSM9DS1_OMZ_M_ULTRA_HIGH_PERFORMANCE;*/
    ctrl_reg4_m.operative_mode_z = LSM9DS1_OMZ_M_LOW_POWER;
    writeRegister(addr(), M_CTRL_REG4_G, data);

    return true;
}

bool LSM9DS1_M::deactivate(void)
{
    uint8_t data;
    data = readRegister(addr(), M_CTRL_REG3_G);
    // data |= POWER_UP;
    // data |= 0x21;
    data |= M_OPER_MODE_DIS;
    writeRegister(addr(), M_CTRL_REG3_G, data);

    return true;
}

int LSM9DS1_M::readX()
{
    int data = 0;
    if (readInternal(M_X_H, M_X_L, &data))
    {
        _x = data;
    }
    // Decode magnetic x-axis  [mgauss measurement unit]
    return (m_lsb_sensitivity * _x);
}

int LSM9DS1_M::readY()
{
    int data = 0;
    if (readInternal(M_Y_H, M_Y_L, &data))
    {
        _y = data;
    }
    // Decode magnetic y-axis  [mgauss measurement unit]
    return (m_lsb_sensitivity * _y);
}

int LSM9DS1_M::readZ()
{
    int data = 0;
    if (readInternal(M_Z_H, M_Z_L, &data))
    {
        _z = data;
    }
    // Decode magnetic z-axis  [mgauss measurement unit]
    return (m_lsb_sensitivity * _z);
}

LSM9DS1_A smeAccelerometer;
LSM9DS1_M smeMagnetic;
LSM9DS1_G smeGyroscope;
