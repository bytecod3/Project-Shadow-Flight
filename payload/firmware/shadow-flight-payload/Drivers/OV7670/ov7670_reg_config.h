/*
 * ov7670_reg_config.h
 *
 *  Created on: Sep 12, 2026
 *      Author: edwin.mwiti
 */

#ifndef OV7670_OV7670_REG_CONFIG_H_
#define OV7670_OV7670_REG_CONFIG_H_

#include "ov7670_regs.h"

#define REG_BATT 0xFF

const uint8_t OV7670_REGS[][2] =  {
		/* color mode */
		{COM7_REG, 		0x14}, // select QVGA, RGB
		{RGB444_REG, 	0x00}, // disable RGB444
		{COM15_REG, 0xD0}, // range 255, RGB565 output
		{TSLB_REG, 0x42}, // UYVY
		{COM13_REG, 0x80}, 	// gamma enable, uv auto adjust, UYVY
		{0xB0, 0x84}, // somehow important, I also dont know what it is for

		/* clock related */
		{COM3_REG, 0x04}, // DCW enable
		{COM14_REG, 0x19}, // manual scaling, pclk / 2
		{SCALING_XSC_REG, 0x3A}, // scaling_xsc
		{SCALING_YSC_REG, 0X35}, // scaling_ysc
		{SCALING_DCWCTR, 0x72}, // downsample by 2
		{SCALING_PCLK_DIV_REG, 0xF1}, // DSP clock /= 2

		/* windowing */
		{HSTART_REG, 0x16}, // hstart
		{HSTOP_REG, 0x19}, // hstop
		{HREF_REG, 0x80}, // href
		{VSTRT_REG, 0x03}, // vstart
		{VSTOP_REG, 0x7B}, // vstop
		{VREF_CONTROL_REG, 0x0A}, // VREF (VSTART_LOW, VSTOP_LOW)

		/* color matrix coefficient */
		#if 0
			{MTX1_REG, 0xB3},
			{MTX2_REG, 0xB3},
			{MTX3_REG, 0x00},
			{MTX4_REG, 0x3D},
			{MTX5_REG, 0xA7},
			{MTX6_REG, 0xE4},
			{MTXS_REG, 0x9E},
		#else
			{MTX1_REG, 0x80},
			{MTX2_REG, 0x80},
			{MTX3_REG, 0x00},
			{MTX4_REG, 0x22},
			{MTX5_REG, 0x5E},
			{MTX6_REG, 0x80},
			{MTXS_REG, 0x9E},

		#endif

		{COM16_REG, 0x38},	// edge enhancement, AWG gain enabled

		/* gamma curve */
		#if 1
			{GAM1_REG, 16},
			{GAM2_REG, 30},
			{GAM3_REG, 53},
			{GAM4_REG, 90},
			{GAM5_REG, 105},
			{GAM6_REG, 118},
			{GAM7_REG, 130},
			{GAM8_REG, 140},
			{GAM9_REG, 150},
			{GAM10_REG, 160},
			{GAM11_REG, 180},
			{GAM12_REG, 195},
			{GAM13_REG, 215},
			{GAM14_REG, 230},
			{GAM15_REG, 244},
			{SLOP_REG, 16},
		#else
			{GAM1_REG, 4},
			{GAM2_REG, 8},
			{GAM3_REG, 16},
			{GAM4_REG, 32},
			{GAM5_REG, 40},
			{GAM6_REG, 48},
			{GAM7_REG, 56},
			{GAM8_REG, 64},
			{GAM9_REG, 72},
			{GAM10_REG, 80},
			{GAM11_REG, 96},
			{GAM12_REG, 112},
			{GAM13_REG, 144},
			{GAM14_REG, 176},
			{GAM15_REG, 208},
			{SLOP_REG, 64},
		#endif

		/* frames per second */
		{CLKRC_REG, 0x00}, // pre-scaler 1/1

		/* others */
		{MVFP_REG, 0x31}, // mirror flip
		//{COM17_REG, 0x08}, // color bar

		{REG_BATT, REG_BATT}

};


#endif /* OV7670_OV7670_REG_CONFIG_H_ */
