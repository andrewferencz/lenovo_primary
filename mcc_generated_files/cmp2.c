#include "cmp2.h"

void CMP2_Initialize(void)
{           

    // Disable the CMP module before the initialization
    DACCTRL1Lbits.DACON = 0;
	
	
	// Comparator Register settings
	DACCTRL1L = 0x00; //CLKDIV 1:1; DACON disabled; DACSIDL disabled; FCLKDIV 1:1; CLKSEL AFVCO/2 - Auxiliary VCO Clock; 
	DACCTRL2L = 0x55; //TMODTIME 85; 
	DACCTRL2H = 0x8A; //SSTIME 138; 
	DAC2CONH = 0x00; //TMCB 0; 
	DAC2CONL = 0x8208; //CMPPOL Non Inverted; HYSPOL Rising Edge; HYSSEL None; DACEN enabled; FLTREN disabled; CBE disabled; IRQM Interrupts are disabled; INSEL CMP2B; DACOEN enabled; 

	//Slope Settings
	SLP2CONH = 0x00; //HME disabled; PSE Negative; SLOPEN disabled; TWME disabled; 
	SLP2CONL = 0x00; //HCFSEL None; SLPSTRT None; SLPSTOPB None; SLPSTOPA None; 
	SLP2DAT = 0x00; //SLPDAT 0; 
	DAC2DATL = 0x00; //DACDATL 0; 
	DAC2DATH = 0x00; //DACDATH 0; 
    
	
     DACCTRL1Lbits.DACON = 1;

}
