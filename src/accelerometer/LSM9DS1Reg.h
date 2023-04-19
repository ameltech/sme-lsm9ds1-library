/*
 * LSM9DS1Reg.h
 *
 * Created: 26/04/2015 14:17:29
 *  Author: speirano
 */

#ifndef LSM9DS1_REG_H_
#define LSM9DS1_REG_H_

/* Accelerometer / Gyroscope */
#define LSM9DS1_AG_ADDRESS 0x6A

#define AG_WHO_AM_I 0x0F
#define AG_WHO_AM_I_RETURN 0x68

#define AG_CTRL_REG1_G 0x10
#define AG_ODR_SET 0x20

#define AG_STATUS_REG 0x27
#define AG_ACCELEROMETER_READY 0x01
#define AG_GYROSCOPE_READY 0x02
#define AG_ACC_X_L 0x28
#define AG_ACC_X_H 0x29
#define AG_ACC_Y_L 0x2A
#define AG_ACC_Y_H 0x2B
#define AG_ACC_Z_L 0x2C
#define AG_ACC_Z_H 0x2D

#define AG_GYR_X_L 0x18
#define AG_GYR_X_H 0x19
#define AG_GYR_Y_L 0x1A
#define AG_GYR_Y_H 0x1B
#define AG_GYR_Z_L 0x1C
#define AG_GYR_Z_H 0x1D
/* Magnetometer */

#define LSM9DS1_M_ADDRESS 0x1C

#define M_WHO_AM_I 0x0F
#define M_WHO_AM_I_RETURN 0x3D

#define M_CTRL_REG1_G 0x20
#define M_ODR_SET 0x20
#define M_CTRL_REG2_G 0x20
#define M_CTRL_REG3_G 0x22
#define M_CTRL_REG4_G 0x23
#define M_OPER_MODE_CONT 0x00
#define M_OPER_MODE_SINGLE 0x01
#define M_OPER_MODE_DIS 0x03

#define M_STATUS_REG 0x27
// #define M_ZYX_X_AXIS_READY    0x01
// #define M_ZYX_Y_AXIS_READY    0x02
// #define M_ZYX_Z_AXIS_READY    0x03
#define M_ZYX_AXIS_READY 0x08

#define M_X_L 0x28
#define M_X_H 0x29
#define M_Y_L 0x2A
#define M_Y_H 0x2B
#define M_Z_L 0x2C
#define M_Z_H 0x2D

/*Sensors Sensitivity */

/*
 * Linear acceleration : Reg6_XL  FS[1:0] = 00g +-2, 10+-4g 11+-8g
 * ranges:
 * +-2  g       mg/LSB = 0.061
 * +-4  g       mg/LSB = 0.122
 * +-8  g       mg/LSB = 0.244
 */
#define A_LSB_SENSITIVITY_2MG 0.061
#define A_LSB_SENSITIVITY_4MG 0.122
#define A_LSB_SENSITIVITY_8MG 0.244

/*
 * Angular rate: CTRL_REG1  FS_G[1:0] 00 245, 01 500, 11 2000
 * +-245    mdps/LSB = 8.75
 * +-500    mdps/LSB = 17.50
 * +-2000   mdps/LSB = 70
 */
#define G_LSB_SENSITIVITY_245MDPS 8.75
#define G_LSB_SENSITIVITY_500DPS 17.5
#define G_LSB_SENSITIVITY_2KMDPS 70
/*
 * Magnetic :  REG2_M FS[1:0] 00 +-4 01 +-8 10 +-12 11+-16
 * +-4       mgauss/LSB = 0.14
 * +-8       mgauss/LSB = 0.29
 * +-12      mgauss/LSB = 0.43
 * +-16      mgauss/LSB = 0.58
 */
#define M_LSB_SENSITIVITY_4MG 0.14
#define M_LSB_SENSITIVITY_8MG 0.29
#define M_LSB_SENSITIVITY_12MG 0.43
#define M_LSB_SENSITIVITY_16MG 0.58

enum e_LSM9DS1_ODR
{
    LSM9DS1_ODR_PW_DOWN = 0,
    LSM9DS1_ODR_010_HZ = 1,
    LSM9DS1_ODR_050_HZ = 2,
    LSM9DS1_ODR_119_HZ = 3,
    LSM9DS1_ODR_238_HZ = 4,
    LSM9DS1_ODR_476_HZ = 5,
    LSM9DS1_ODR_952_HZ = 6,
};

enum e_LSM9DS1_FS_G
{
    LSM9DS1_FS_G_0245_DPS = 0,
    LSM9DS1_FS_G_0500_DPS = 1,
    LSM9DS1_FS_G_2000_DPS = 3,
};

enum e_LSM9DS1_FS_XL
{
    LSM9DS1_FS_XL_02_G = 0,
    LSM9DS1_FS_XL_16_G = 1,
    LSM9DS1_FS_XL_04_G = 2,
    LSM9DS1_FS_XL_08_G = 3,
};

enum e_LSM9DS1_DCF_XL
{
    LSM9DS1_DCF_XL_ODR_D_50 = 0,
    LSM9DS1_DCF_XL_ODR_D_100 = 1,
    LSM9DS1_DCF_XL_ODR_D_9 = 2,
    LSM9DS1_DCF_XL_ODR_D_400 = 3,
};

enum e_LSM9DS1_DO_M
{
    LSM9DS1_DO_M_00_625_HZ = 0,
    LSM9DS1_DO_M_01_250_HZ = 1,
    LSM9DS1_DO_M_02_500_HZ = 2,
    LSM9DS1_DO_M_05_000_HZ = 3,
    LSM9DS1_DO_M_10_000_HZ = 4,
    LSM9DS1_DO_M_20_000_HZ = 5,
    LSM9DS1_DO_M_40_000_HZ = 6,
    LSM9DS1_DO_M_80_000_HZ = 7,
};

enum e_LSM9DS1_OM_M
{
    LSM9DS1_OM_M_LOW_POWER = 0,
    LSM9DS1_OM_M_MEDIUM_PERFORMANCE = 1,
    LSM9DS1_OM_M_HIGH_PERFORMANCE = 2,
    LSM9DS1_OM_M_ULTRA_HIGH_PERFORMANCE = 3,
};

enum e_LSM9DS1_FS_M
{
    LSM9DS1_FS_M_04_GAUSS = 0,
    LSM9DS1_FS_M_08_GAUSS = 1,
    LSM9DS1_FS_M_12_GAUSS = 2,
    LSM9DS1_FS_M_16_GAUSS = 3,
};

enum e_LSM9DS1_MD_M
{
    LSM9DS1_MD_M_CONTINUOS_CONVERSION_MODE = 0,
    LSM9DS1_MD_M_SINGLE_CONVERSION_MODE = 1,
    LSM9DS1_MD_M_POWER_DOWN_MODE_1 = 2,
    LSM9DS1_MD_M_POWER_DOWN_MODE_2 = 3,
};

enum e_LSM9DS1_OMZ_M
{
    LSM9DS1_OMZ_M_LOW_POWER = 0,
    LSM9DS1_OMZ_M_MEDIUM_PERFORMANCE = 1,
    LSM9DS1_OMZ_M_HIGH_PERFORMANCE = 2,
    LSM9DS1_OMZ_M_ULTRA_HIGH_PERFORMANCE = 3,
};

enum e_LSM9DS1_WHOAMI
{
    LSM9DS1_WHOAMI_XLG = 0x68,
    LSM9DS1_WHOAMI_M = 0x3D,
};

#pragma pack(1)

union u_LSM9DS1_REG_CTRL_REG1_M
{
    uint8_t byte;
    struct
    {
        unsigned self_test : 1;
        unsigned fast_odr : 1;
        unsigned output_data_rate : 3;
        unsigned operative_mode_xy : 2;
        unsigned temp_comp : 1;
    };
};

union u_LSM9DS1_REG_CTRL_REG2_M
{
    uint8_t byte;
    struct
    {
        unsigned zero_1 : 2;
        unsigned soft_rst : 1;
        unsigned reboot : 1;
        unsigned zero_2 : 1;
        enum e_LSM9DS1_FS_M full_scale : 2;
        unsigned zero_3 : 1;
    };
};

union u_LSM9DS1_REG_CTRL_REG3_M
{
    uint8_t byte;
    struct
    {
        unsigned operating_mode : 2;
        unsigned spi_interface_mode : 1;
        unsigned zero_1 : 2;
        unsigned low_power : 1;
        unsigned zero_2 : 1;
        unsigned i2c_disable : 1;
    };
};

union u_LSM9DS1_REG_CTRL_REG4_M
{
    uint8_t byte;
    struct
    {
        unsigned zero_1 : 1;
        unsigned big_little_endian : 1;
        unsigned operative_mode_z : 2;
        unsigned zero_2 : 4;
    };
};

union u_LSM9DS1_REG_CTRL_REG5_M
{
    uint8_t byte;
    struct
    {
        unsigned zero_1 : 6;
        unsigned block_data_update : 1;
        unsigned fast_read : 1;
    };
};

union u_LSM9DS1_REG_STATUS_REG_M
{
    uint8_t byte;
    struct
    {
        unsigned xda : 1;
        unsigned yda : 1;
        unsigned zda : 1;
        unsigned zyxda : 1;
        unsigned xor_ : 1;
        unsigned yor : 1;
        unsigned zor : 1;
        unsigned zyxor : 1;
    };
};
#pragma pack()

#endif /* LSM9DS1_REG_H_ */
