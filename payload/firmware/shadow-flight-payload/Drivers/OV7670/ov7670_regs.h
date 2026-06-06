/*
 * ov7670_regs.h
 * @brief register addresses for OV7670
 *
 * @date: Jun 5, 2026
 * @author: edwin
 */

#ifndef OV7670_OV7670_REGS_H_
#define OV7670_OV7670_REGS_H_

#define GAIN_REG 				(0x00) /* gain control setting */
#define RED_GAIN_REG 			(0x01) /* red channel gain setting */
#define BLUE_GAIN_REG 			(0x02) /* blue channel gain setting */
#define VREF_CONTROL_REG 		(0x03) /* vertical frame control */
#define COM1_REG				(0x04) /* common control 1 */
#define BAVE_REG 				(0x05) /* U/B average level */
#define GB_AVE_REG 				(0x06) /* Y/Gb average level */
#define AECHH_REG				(0x07) /* exposure value */
#define RAVE_REG				(0x08) /* V/R average value */
#define COM2_REG				(0x09) /* common control 2 */
#define PID_REG					(0x0A) /* product ID number */
#define VER_REG					(0x0B) /* product ID number */
#define COM3_REG				(0x0C) /* common control 3 */
#define COM4_REG				(0x0D) /* common control 4 */
#define COM5_REG				(0x0E)  /* common control 5*/
#define COM6_REG 				(0x0F)  /* common control 6 */
#define AECH_REG				(0x10)   /* EXposure value */
#define CLKRC_REG				(0x11) /* clock selection and pre-scale */
#define COM7_REG				(0x12) /* common control 7 */
#define COM8_REG				(0x13)  /* common control 8 */
#define COM9_REG				(0x14) /* common control 9 */
#define COM10_REG				(0X15)  /* common control 10  */
#define HSTART_REG  			(0x16)   /*output format */
#define HSTOP_REG				(0x17)  /* output format */
#define VSTRT_REG  				(0x18)  /*output format */
#define VSTOP_REG  				(0x19)  /* output format */
#define PSHFT_REG  				(0x1A)	/* data format - pixel delay select */
#define MIDH_REG				(0x1C) /* manufacturer ID byte HIGH*/
#define MIDL_REG 				(0x1D)	/* manufacturer ID byte LOW */
#define MVFP_REG 				(0x1E)  /* mirror/flip enable  */
#define ADCCTR0					(0x20) /* ADC control */
#define AEW_REG					(0x24)  /* AGC/AEW stable operating region (upper limit) */
#define AEB_REG					(0x25)  /* AGC/AEB stable operating region (lower limit) */
#define VPT_REG					(0x26)  /* AGC/AEB fast mode operating region  */
#define BBIAS_REG 				(0x27)  /* B channel signal output bias */
#define GB_BIAS_REG				(0x28)  /* Gb channel signal output bias  */
#define EXHCH_REG				(0x2A)  /* dummy pixel insert MSB */
#define EXHCL_REG				(0x2B)	/* Dummy pixel insert LSB */
#define RBIAS_REG				(0x2C) /* R channel signal output bias */
#define ADVFL_REG   			(0x2D)  /*LSB of insert dummy lines in vertical direction) */
#define ADVFH_REG   			(0x2E)	/* MSB of insert dummy in vertical direction */
#define YAVE_REG				(0x2F)  /* Y/G channel average value */
#define HSYST_REG				(0x30)  /* HSYNC rising edge delay  */
#define HSYSEN_REG				(0x31) /* HSYNC falling edge delay  */
#define HREF_REG				(0x32)   /* HREF control  */
#define CHLF_REG				(0x33)  /* Array current control  */
#define ARBLM_REG				(0x34)  /* Array reference control  */
#define ADC_REG   				(0x35)  /* ADC control */
#define ACOM_REG 				(0x36)  /* ADC and analog common mode control  */
#define OFON_REG 				(0x39)  /* ADC offset control  */
#define TSLB_REG				(0x3A)  /* LIne buffer test option  */
#define COM11_REG				(0x3B)  /* common control 11 */
#define COM12_REG   			(0x3C) /* common control 12 */
#define COM13_REG   			(0x3D) /* common control 13 */
#define COM14_REG				(0x3E)  /* common control 14 */
#define EDGE_REG				(0x3F)  /* edge enhancement adjustment  */
#define COM15_REG				(0x40) /* common control 15 */
#define COM16_REG				(0x41) /* common control 16 */
#define COM17_REG 				(0x42)  /* common control 17 */
#define REG4B_REG				(0x4B)  /* register 4B */
#define DNSTH_REG				(0x4C)  /* de-noise strength */
#define MTX1_REG				(0x4F)  /* matrix coefficient 1 */
#define MTX2_REG				(0x50)  /* matrix coefficient 2 */
#define MTX3_REG				(0x51)  /* matrix coefficient 3 */
#define MTX4_REG				(0x52)  /* matrix coefficient 4 */
#define MTX5_REG				(0x53)  /* matrix coefficient 5 */
#define MTX6_REG				(0x54)  /* matrix coefficient 6 */
#define BRIGHT_REG				(0x55) /* brightness control */
#define CONTRAST_REG			(0x56)  /* contrast control */
#define CONTRAST_CENTER			(0x57) /* contrast center */
#define MTXS_REG				(0x58) /* matrix coefficient sign for coefficient 5 to 0 */
#define LCC1_REG 				(0x62)   /* lens correction option 1 */
#define LCC2_REG 				(0x63)   /* lens correction option 2 */
#define LCC3_REG 				(0x64)   /* lens correction option 3 */
#define LCC4_REG 				(0x65)   /* lens correction option 4 */
#define LCC5_REG 				(0x66)   /* lens correction option 5 */
#define MANU_REG				(0x67) /* manual U value */
#define MANV_REG				(0x68)  /*manual V value */
#define GFIX_REG				(0x69) /* fix gain control */
#define GGAIN_REG				(0x6A)  /* G channel AWB gain */
#define DBLV_REG				(0x6B)  /* PLL control */
#define AWBCTR3_REG  			(0x6C)  /* AWB control 3 */
#define AWBCTR2_REG				(0x6D) /* AWB control 2 */
#define AWBCTR1_REG				(0x6E) /* AWB control 1 */
#define AWBCTR0_REG				(0x6F) /* AWB control 0 */
#define SCALING_XSC_REG			(0x70) /* test pattern and horizontal scale factor */
#define SCALING_YSC_REG			(0x71)  /* test pattern and vertical scale factor */
#define SCALING_DCWCTR  		(0x72)  /* DCW control */
#define SCALING_PCLK_DIV_REG	(0x73) /* bypass clock divider */
#define REG74_REG				(0x74) /* register 74 */
#define REG75_REG				(0x75)  /* register 75  */
#define REG76_REG 				(0x76) /*register 76 */
#define REG77_REG				(0x77)  /* register 77 de-noise effect */
#define SLOP_REG				(0x7A)  /* gamma curve highest segment slope  */
#define GAM1_REG  				(0x7B)   /* gamma curve 1st segment input end-point 0x04 output value */
#define GAM2_REG 				(0x7C)   /* gamma curve 2nd segment input end-point 0x08 output value */
#define GAM3_REG  				(0x7D)   /* gamma curve 3rd segment input end-point 0x10 output value */
#define GAM4_REG  				(0x7E)   /* gamma curve 4th segment input end-point 0x20output value */
#define GAM5_REG  				(0x7F)   /* gamma curve 5th segment input end-point 0x28 output value */
#define GAM6_REG  				(0x80)   /* gamma curve 6th segment input end-point 0x30 output value */
#define GAM7_REG  				(0x81)   /* gamma curve 7th segment input end-point 0x38 output value */
#define GAM8_REG  				(0x82)   /* gamma curve 8th segment input end-point 0x40 output value */
#define GAM9_REG  				(0x83)   /* gamma curve 9th segment input end-point 0x48 output value */
#define GAM10_REG  				(0x84)   /* gamma curve 10th segment input end-point 0x50 output value */
#define GAM11_REG  				(0x85)   /* gamma curve 11th segment input end-point 0x60 output value */
#define GAM12_REG  				(0x86)   /* gamma curve 12th segment input end-point 0x70 output value */
#define GAM13_REG  				(0x87)   /* gamma curve 13th segment input end-point 0x90 output value */
#define GAM14_REG  				(0x88)   /* gamma curve 14th segment input end-point 0xB0 output value */
#define GAM15_REG  				(0x89)   /* gamma curve 15th segment input end-point 0xD0 output value */
#define RGB444_REG				(0x8C)  /* RGB444 enable */
#define DM_LNL_REG				(0x92) /* dummy line low 8 bits */
#define DM_LNH_REG				(0x93) /* dummy line high 8 bits */
#define LCC6_REG 				(0x94)	/* lens correction option 6 */
#define LCC7_REG				(0x95)  /* lens correction option 7  */
#define BD50ST_REG				(0x9D)  /* 50Hz banding filter value */
#define BD60ST_REG 				(0x9E)  /* 60Hz banding value */
#define HAECC1_REG				(0x9F) /* histogram-based AEC/AGC control 1 */
#define HAECC2_REG				(0XA0)  /* histogram-based AEC/AGC control 2  */
#define SCALING_PCLK_DELAY_REG  (0xA2)  /* pixel clock delay */
#define NT_CTRL_REG 			(0xA4)  /* auto-frame rate adjustment control */
#define BD50MAX_REG				(0xA5)  /* 50Hz banding step limit  */
#define HAECC3_REG				(0XA6)  /* histogram-based AEC/AGC control 3  */
#define HAECC4_REG				(0XA7)  /* histogram-based AEC/AGC control 4  */
#define HAECC5_REG				(0XA8)  /* histogram-based AEC/AGC control 5  */
#define HAECC6_REG				(0XA9)  /* histogram-based AEC/AGC control 6  */
#define HAECC7_REG				(0XAA)  /* histogram-based AEC/AGC control 7  */
#define BD60MAX_REG				(0xAB)  /* 60Hz banding step limit  */
#define STR_OPT_REG				(0xAC)  /* register AC */
#define STR_R_REG				(0xAD)  /* R gain for LED output frame */
#define STR_G_REG				(0xAE) /* G gain for LED output frame */
#define STR_B_REG				(0xAF)  /* B gain for LED output frame */
#define ABLC1_REG 				(0xB1)  /* ABLC enable  */
#define THL_ST_REG				(0xB2)  /* ABLC target */
#define THL_DLT_REG				(0xB5)  /* ABLC stable range */
#define AD_CHB_REG				(0xBE) /* blue channel black level compensation */
#define AD_CHR_REG  			(0xBF) /* Red channel black level compensation */
#define AD_CHGB_REG 			(0xC0)  /* Gb channel black level compensation */
#define AD_CHGR_REG  			(0xC1)  /* Gr channel black level compensation */
#define SATCTR_REG				(0xC9) /* saturation control */


#endif /* OV7670_OV7670_REGS_H_ */
