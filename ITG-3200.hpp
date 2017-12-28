/*
 * name:        ITG-3200
 * description: Single-chip, digital-output, 3-axis MEMS gyro
 * manuf:       InvenSense Inc.
 * version:     0.1
 * url:         https://www.invensense.com/products/motion-tracking/3-axis/itg-3200/
 * date:        2016-08-01
 * author       https://chisl.io/
 * file:        ITG-3200.hpp
 */

#include <cinttypes>

/* Derive from class ITG_3200_Base and implement the read and write functions! */

/* ITG-3200: Single-chip, digital-output, 3-axis MEMS gyro */
class ITG_3200_Base
{
public:
	/* Pure virtual functions that need to be implemented in derived class: */
	virtual uint8_t read8(uint16_t address, uint16_t n=8) = 0;  // 8 bit read
	virtual void write(uint16_t address, uint8_t value, uint16_t n=8) = 0;  // 8 bit write
	virtual uint16_t read16(uint16_t address, uint16_t n=16) = 0;  // 16 bit read
	virtual void write(uint16_t address, uint16_t value, uint16_t n=16) = 0;  // 16 bit write
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                            REG WhoAmI                                             *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG WhoAmI:
	 * verify the identity of the device.
	 */
	struct WhoAmI
	{
		static const uint16_t __address = 0;
		
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t mask = 0b10000000; // [7]
		};
		/* Bits ID: */
		/* Contains the I2C address of the device, which can also be changed by writing to this register.  */
		struct ID
		{
			static const uint8_t dflt = 0b110100; // 6'b110100
			static const uint8_t mask = 0b01111110; // [1,2,3,4,5,6]
		};
		/* Bits unused_1: */
		struct unused_1
		{
			static const uint8_t mask = 0b00000001; // [0]
		};
	};
	
	/* Set register WhoAmI */
	void setWhoAmI(uint8_t value)
	{
		write(WhoAmI::__address, value, 8);
	}
	
	/* Get register WhoAmI */
	uint8_t getWhoAmI()
	{
		return read8(WhoAmI::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                      REG SampleRateDivider                                       *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG SampleRateDivider:
	 * This register determines the sample rate of the ITG-3200 gyros. The gyros outputs are sampled internally at
	 * either 1kHz or 8kHz, determined by the DLPF_CFG setting (see register 22). This sampling is then filtered
	 * digitally and delivered into the sensor registers after the number of cycles determined by this register.
	 * The sample rate is given by the following formula:
	 * Fsample = Finternal / (divider+1),
	 * where Finternal is either 1kHz or 8kHz
	 */
	struct SampleRateDivider
	{
		static const uint16_t __address = 21;
		
		/* Bits SampleRateDivider: */
		struct SampleRateDivider_
		{
			/* Mode:rw */
			static const uint8_t dflt = 0b00000000; // 8'h0
			static const uint8_t mask = 0b11111111; // [0,1,2,3,4,5,6,7]
		};
	};
	
	/* Set register SampleRateDivider */
	void setSampleRateDivider(uint8_t value)
	{
		write(SampleRateDivider::__address, value, 8);
	}
	
	/* Get register SampleRateDivider */
	uint8_t getSampleRateDivider()
	{
		return read8(SampleRateDivider::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                             REG DLPF                                              *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/* REG DLPF:
	 */
	struct DLPF
	{
		static const uint16_t __address = 22;
		
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t mask = 0b11100000; // [5,6,7]
		};
		/* Bits FS_SEL: */
		/*
		 * Set the full-scale range of the gyro sensors. The power-on-reset value of FS_SEL is 00h.
		 * Set to 03h for proper operation.
		 */
		struct FS_SEL
		{
			static const uint8_t dflt = 0b11; // 2'b11
			static const uint8_t mask = 0b00011000; // [3,4]
			static const uint8_t Normal = 0b11; // +/- 2000°/sec
		};
		/* Bits DLPF_CFG: */
		struct DLPF_CFG
		{
			static const uint8_t mask = 0b00000111; // [0,1,2]
			static const uint8_t DLPF_256 = 0; // 256Hz, Internal Sample Rate=8kHz
			static const uint8_t DLPF_188 = 1; // 188Hz, Internal Sample Rate= 1kHz
			static const uint8_t DLPF_98 = 2; // 98Hz, Internal Sample Rate= 1kHz
			static const uint8_t DLPF_42 = 3; // 42Hz, Internal Sample Rate= 1kHz
			static const uint8_t DLPF_20 = 4; // 20Hz, Internal Sample Rate= 1kHz
			static const uint8_t DLPF_10 = 5; // 10Hz, Internal Sample Rate= 1kHz
			static const uint8_t DLPF_5 = 6; // 5Hz, Internal Sample Rate= 1kHz
			static const uint8_t reserved_0 = 7; // 
		};
	};
	
	/* Set register DLPF */
	void setDLPF(uint8_t value)
	{
		write(DLPF::__address, value, 8);
	}
	
	/* Get register DLPF */
	uint8_t getDLPF()
	{
		return read8(DLPF::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                    REG InterruptConfiguration                                     *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG InterruptConfiguration:
	 * This register configures the interrupt operation of the device. The interrupt output pin (INT) configuration can be set, the interrupt latching/clearing method can be set, and the triggers for the interrupt can be set.<br>
	 * Note that if the application requires reading every sample of data from the ITG-3200 part, it is best to enable the raw data ready interrupt (RAW_RDY_EN). This allows the application to know when new sample data is available.
	 */
	struct InterruptConfiguration
	{
		static const uint16_t __address = 23;
		
		/* Bits ACTL: */
		/* Logic level for INT output pin  */
		struct ACTL
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b10000000; // [7]
			static const uint8_t ActiveLow = 0b1; // 
			static const uint8_t ActiveHigh = 0b0; // 
		};
		/* Bits OPEN: */
		/* Drive type for INT output pin  */
		struct OPEN
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b01000000; // [6]
			static const uint8_t OpenDrain = 0b1; // 
			static const uint8_t PushPull = 0b0; // 
		};
		/* Bits LATCH_INT_EN: */
		/* Latch mode  */
		struct LATCH_INT_EN
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00100000; // [5]
			static const uint8_t Latch = 0b1; // Latch until interrupt is cleared, 0=50us pulse
		};
		/* Bits INT_ANYRD_2CLEAR: */
		/* Latch clear method  */
		struct INT_ANYRD_2CLEAR
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00010000; // [4]
			static const uint8_t Any = 0b1; // Any register read,
			static const uint8_t StatusRegister = 0b0; // Status register read only
		};
		/* Bits reserved_0: */
		struct reserved_0
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00001000; // [3]
		};
		/* Bits ITG_RDY_EN: */
		/* Enable interrupt when device is ready (PLL ready after changing clock source)  */
		struct ITG_RDY_EN
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000100; // [2]
		};
		/* Bits reserved_1: */
		struct reserved_1
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000010; // [1]
		};
		/* Bits RAW_RDY_EN: */
		/* Enable interrupt when data is available  */
		struct RAW_RDY_EN
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000001; // [0]
		};
	};
	
	/* Set register InterruptConfiguration */
	void setInterruptConfiguration(uint8_t value)
	{
		write(InterruptConfiguration::__address, value, 8);
	}
	
	/* Get register InterruptConfiguration */
	uint8_t getInterruptConfiguration()
	{
		return read8(InterruptConfiguration::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                       REG InterruptStatus                                        *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG InterruptStatus:
	 * Whenever one of the interrupt sources is triggered, the corresponding bit will be set. The polarity of the interrupt pin (active high/low) and the latch type (pulse or latch) has no affect on these status bits.
	 */
	struct InterruptStatus
	{
		static const uint16_t __address = 26;
		
		/* Bits RAW_DATA_RDY: */
		/* Raw data is ready */
		struct RAW_DATA_RDY
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000001; // [0]
		};
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000010; // [1]
		};
		/* Bits ITG_RDY: */
		/* PLL ready */
		struct ITG_RDY
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000100; // [2]
		};
		/* Bits unused_1: */
		struct unused_1
		{
			static const uint8_t dflt = 0b00000; // 5'b0
			static const uint8_t mask = 0b11111000; // [3,4,5,6,7]
		};
	};
	
	/* Set register InterruptStatus */
	void setInterruptStatus(uint8_t value)
	{
		write(InterruptStatus::__address, value, 8);
	}
	
	/* Get register InterruptStatus */
	uint8_t getInterruptStatus()
	{
		return read8(InterruptStatus::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                           REG TEMP_OUT                                            *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG TEMP_OUT:
	 * 16-bit temperature data (2's complement format)
	 * At any time, these values can be read from the device; however it is best to use the interrupt function to determine when new data is available
	 */
	struct TEMP_OUT
	{
		static const uint16_t __address = 27;
		
		/* Bits TEMP_OUT: */
		struct TEMP_OUT_
		{
			/* Mode:r */
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
	};
	
	/* Set register TEMP_OUT */
	void setTEMP_OUT(uint16_t value)
	{
		write(TEMP_OUT::__address, value, 16);
	}
	
	/* Get register TEMP_OUT */
	uint16_t getTEMP_OUT()
	{
		return read16(TEMP_OUT::__address, 16);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                          REG GYRO_XOUT                                           *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG GYRO_XOUT:
	 * 16-bit X gyro output data (2's complement format)
	 * At any time, these values can be read from the device; however it is best to use the interrupt function to determine when new data is available
	 */
	struct GYRO_XOUT
	{
		static const uint16_t __address = 29;
		
		/* Bits GYRO_XOUT: */
		struct GYRO_XOUT_
		{
			/* Mode:r */
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
	};
	
	/* Set register GYRO_XOUT */
	void setGYRO_XOUT(uint16_t value)
	{
		write(GYRO_XOUT::__address, value, 16);
	}
	
	/* Get register GYRO_XOUT */
	uint16_t getGYRO_XOUT()
	{
		return read16(GYRO_XOUT::__address, 16);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                          REG GYRO_YOUT                                           *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG GYRO_YOUT:
	 * 16-bit Y gyro output data (2's complement format)
	 * At any time, these values can be read from the device; however it is best to use the interrupt function to determine when new data is available
	 */
	struct GYRO_YOUT
	{
		static const uint16_t __address = 31;
		
		/* Bits GYRO_YOUT: */
		struct GYRO_YOUT_
		{
			/* Mode:r */
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
	};
	
	/* Set register GYRO_YOUT */
	void setGYRO_YOUT(uint16_t value)
	{
		write(GYRO_YOUT::__address, value, 16);
	}
	
	/* Get register GYRO_YOUT */
	uint16_t getGYRO_YOUT()
	{
		return read16(GYRO_YOUT::__address, 16);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                          REG GYRO_ZOUT                                           *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG GYRO_ZOUT:
	 * 16-bit Y gyro output data (2's complement format)
	 * At any time, these values can be read from the device; however it is best to use the interrupt function to determine when new data is available
	 */
	struct GYRO_ZOUT
	{
		static const uint16_t __address = 33;
		
		/* Bits GYRO_ZOUT: */
		struct GYRO_ZOUT_
		{
			/* Mode:r */
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
	};
	
	/* Set register GYRO_ZOUT */
	void setGYRO_ZOUT(uint16_t value)
	{
		write(GYRO_ZOUT::__address, value, 16);
	}
	
	/* Get register GYRO_ZOUT */
	uint16_t getGYRO_ZOUT()
	{
		return read16(GYRO_ZOUT::__address, 16);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                       REG PowerManagement                                        *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG PowerManagement:
	 * Setting the SLEEP bit in the register puts the device into very low power sleep mode. In this mode, only the serial interface and internal registers remain active, allowing for a very low standby current. Clearing this bit puts the device back into normal mode. To save power, the individual standby selections for each of the gyros should be used if any gyro axis is not used by the application.
	 */
	struct PowerManagement
	{
		static const uint16_t __address = 62;
		
		/* Bits CLK_SEL: */
		struct CLK_SEL
		{
			static const uint8_t dflt = 0b000; // 3'b0
			static const uint8_t mask = 0b00000111; // [0,1,2]
			static const uint8_t Internal = 0; // Internal oscillator
			static const uint8_t PLLX = 1; // PLL with X Gyro reference
			static const uint8_t PLLY = 2; // PLL with Y Gyro reference
			static const uint8_t PLLZ = 3; // PLL with Z Gyro reference
			static const uint8_t PLL_EXT_32k = 4; // PLL with external 32.768kHz reference
			static const uint8_t PLL_EXT_19M = 5; // PLL with external 19.2MHz reference
			static const uint8_t Reserved_0 = 6; // 
			static const uint8_t Reserved_1 = 7; // 
		};
		/* Bits STBY_ZG: */
		struct STBY_ZG
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00001000; // [3]
		};
		/* Bits STBY_YG: */
		struct STBY_YG
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00010000; // [4]
		};
		/* Bits STBY_XG: */
		struct STBY_XG
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00100000; // [5]
		};
		/* Bits SLEEP: */
		/*
		 * Puts the device into very low power sleep mode. In this mode, only the serial interface
		 * and internal registers remain active, allowing for a very low standby current.
		 * Clearing this bit puts the device back into normal mode. To save power, the individual
		 * standby selections for each of the gyros should be used if any gyro axis is not used
		 * by the application.
		 */
		struct SLEEP
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b01000000; // [6]
		};
		/* Bits H_RESET: */
		struct H_RESET
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b10000000; // [7]
		};
	};
	
	/* Set register PowerManagement */
	void setPowerManagement(uint8_t value)
	{
		write(PowerManagement::__address, value, 8);
	}
	
	/* Get register PowerManagement */
	uint8_t getPowerManagement()
	{
		return read8(PowerManagement::__address, 8);
	}
	
};
