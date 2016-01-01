/*
 * device_spi.hpp
 *
 *  Created on: Dec 27, 2015
 *      Author: James
 */

#pragma once

#include <mal/device_defines.hpp>

namespace MAL
{
namespace F3C
{

}

namespace SPI
{

struct L3GD20
{
	enum class REG_ADDRESSES
		: uint8_t
		{
			WHO_AM_I = 0x0F,
		CTRL_REG1 = 0x20,
		CTRL_REG2 = 0x21,
		CTRL_REG3 = 0x22,
		CTRL_REG4 = 0x23,
		CTRL_REG5 = 0x24,
		DATACAPTURE = 0x25,
		OUT_TEMP = 0x26,
		OUT_X_L = 0x28,
		OUT_X_H = 0x29,
		OUT_Y_L = 0x2A,
		OUT_Y_H = 0x2B,
		OUT_Z_L = 0x2C,
		OUT_Z_H = 0x2D,
		FIFO_CTRL = 0x2E,
		FIFO_SRC = 0x2F,
		INT1_CFG = 0x30,
		INT1_SRC = 0x31,
		INT1_THS_XH = 0x32,
		INT1_THS_XL = 0x33,
		INT1_THS_YH = 0x34,
		INT1_THS_YL = 0x35,
		INT1_THS_ZH = 0x36,
		INT1_THS_ZL = 0x37,
		INT1_DURATION = 0x38
	};

	uint8_t WHO_AM_I;

	REGISTER
			uint8_t XEN :1;
			uint8_t YEN :1;
			uint8_t ZEN :1;
			uint8_t PD :1;
			uint8_t BW :2;
			uint8_t DR :2;
		NAMED_8
	CTRL_REG1;

	REGISTER
			uint8_t :2;
			uint8_t HPM :2;
			uint8_t HPCF :4;
		NAMED_8
	CTRL_REG2;

	REGISTER
			uint8_t I2_EMPTY :1;
			uint8_t I2_OVR :1;
			uint8_t I2_WTM :1;
			uint8_t I2_DRDY :1;
			uint8_t PP_OD :1;
			uint8_t HL_ACTIVE :1;
			uint8_t I1_BOOT :1;
			uint8_t I1_INT1 :1;
		NAMED_8
	CTRL_REG3;

	REGISTER
			uint8_t SIM :1;
			uint8_t :3;
			uint8_t FSD :2;
			uint8_t BLE :1;
			uint8_t BDU :1;
		NAMED_8
	CTRL_REG4;

	REGISTER
			uint8_t OUT_SEL_0 :1;
			uint8_t OUT_SEL_1 :1;
			uint8_t INT1_SEL_0 :2;
			uint8_t INT1_SEL_1 :1;
			uint8_t HPF_EN :1;
			uint8_t :1;
			uint8_t FIFO_EN :1;
			uint8_t BOOT :1;
		NAMED_8
	CTRL_REG5;

	uint8_t DATACAPTURE;
	uint8_t OUT_TEMP;

	REGISTER
			uint8_t XDA :1;
			uint8_t YDA :1;
			uint8_t ZDA :2;
			uint8_t XYZDA :1;
			uint8_t XOVR :1;
			uint8_t YOVR :1;
			uint8_t ZOVR :1;
			uint8_t XYZOVR :1;
		NAMED_8
	STATUS_REG;

	struct OUT_DATA
	{
		union
		{
			struct
			{
				uint8_t OUT_X_L;
				uint8_t OUT_X_H;
			};
			uint16_t OUT_X;
		};
		union
		{
			struct
			{
				uint8_t OUT_Y_L;
				uint8_t OUT_Y_H;
			};
			uint16_t OUT_Y;
		};
		union
		{
			struct
			{
				uint8_t OUT_Z_L;
				uint8_t OUT_Z_H;
			};
			uint16_t OUT_Z;
		};
	} OUT_DATA_REGS;

	REGISTER
			uint8_t WTM :5;
			uint8_t FIFO_MODE :3;
		NAMED_8
	FIFO_CTRL_REG;

	REGISTER
			uint8_t DATA_LEVEL :5;
			uint8_t EMPTY :1;
			uint8_t OVR :1;
			uint8_t WTM :1;
		NAMED_8
	FIFO_SRC_REG;

	REGISTER
			uint8_t XLIE :1;
			uint8_t XHIE :1;
			uint8_t YLIE :1;
			uint8_t YHIE :1;
			uint8_t ZLIE :1;
			uint8_t ZHIE :1;
			uint8_t LIR :1;
			uint8_t AND_OR :1;
		NAMED_8
	INT1_CFG;

	REGISTER
			uint8_t XL :1;
			uint8_t XH :1;
			uint8_t YL :1;
			uint8_t YH :1;
			uint8_t ZL :1;
			uint8_t ZH :1;
			uint8_t IA :1;
			uint8_t :1;
		NAMED_8
	INT1_SRC;

	uint8_t INT1_THS_XH;
	uint8_t INT1_THS_XL;

	uint8_t INT1_THS_YH;
	uint8_t INT1_THS_YL;

	uint8_t INT1_THS_ZH;
	uint8_t INT1_THS_ZL;

	REGISTER
			uint8_t DURATION :7;
			uint8_t WAIT :1;
		NAMED_8
	INT1_DURATION;
};

}
}
