#ifndef MAIN_H  
#define	MAIN_H

/* this area sets up for testing, comment out all for production code*/
//#define HALFTEST
//#define DEBUGGING  //this skips looking for the minimum VAC to turn on
//#define LLCONLY 
//#define DISABLEPFCONLY
//#define DISABLELLCONLY


#include <xc.h> // include processor files - each processor file is guarded.  
#include "dsp.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "mcc_generated_files/pin_manager.h"

#ifndef EXTERN
#define EXTERN extern
#endif

void FASTSUM(volatile int16_t *, volatile int16_t *);

#define PWMCLOCK 500000000.0  //Hz

/* PFC contants and calculations */
#define PFC_FREQUENCY 125000
/* for 8x oversample, SCCP1 clock is 100MHz or 1/5 and we want 8 samples */
#define PFC_PERIOD ((const int)(PWMCLOCK/PFC_FREQUENCY/40)*40-1)
#define SCCP1PERIOD (const int) ((PFC_PERIOD+1)/40-1)
#define PFC_DUTYMAX ((const int)(0.8 * PFC_PERIOD))

//X is in Volts, result is 12bit ADC
#define VBUS_DIVIDER(X) ((const int)(X * 15.0/2015.0*4096.0/3.3 + 0.5))
//X is in Amps, results is 12bit ADC
#define IPFC_DIVIDER(X) ((const int)((X * 0.02 * 5110.0 / 499.0 * 4096/3.3 + 0.5)))
//X is in RMS voltage, result is 12bit
#define VACADC(X) ((const int)(X * 4096.0 / 3.3 * 0.901 * 15.0/2015.0)) //rms to average... 0.637/.707
#define IMAX (IPFC_DIVIDER(10.0)<<2)

#define PFC_K 89061254 //   //this gets us 550W means Vpid output = 22000...
#define MAXPOWER 17500 //

#ifndef HALFTEST
#define VTURNON 85.0   
#define VTURNOFF 80.0   
#define VBUSSETPOINT (const int)(VBUS_DIVIDER(390.0)<<2) //change to *4 to double gain
#else
#define VTURNON 45.0   
#define VTURNOFF 35.0   
#define VBUSSETPOINT (const int)(VBUS_DIVIDER(190.0)<<2) //change to *4 to double gain
#endif

#define VBUSOVP (const int)(VBUS_DIVIDER(435.0)<<3) //the highest value is 443 w/o saturation
/* end of PFC constants */

#define OTP_97DEGC_OFF 280
#define OTP_80DEGC_ON  438

/* end of LLC constants*/

/* pfc current PID values*/
#define PID_IPFC_KP 		0.15
#define PID_IPFC_KI 		0.02
#define PID_IPFC_KD 		0.0

#define PID_IPFC_A 		Q15(PID_IPFC_KP + PID_IPFC_KI + PID_IPFC_KD)
#define PID_IPFC_B 		Q15(-1 *(PID_IPFC_KP + 2 * PID_IPFC_KD))
#define PID_IPFC_C 		Q15(PID_IPFC_KD)

/* pfc voltage PID values*/
#define PID_VPFC_KP 		0.7
#define PID_VPFC_KI 		0.02
#define PID_VPFC_KD 		0.0

//pfc voltage PID with integrator
#define PID_VPFC_A 		Q15(PID_VPFC_KP + PID_VPFC_KI + PID_VPFC_KD)
#define PID_VPFC_B 		Q15(-PID_VPFC_KP)
#define PID_VPFC_C 		0

//pfc voltage PID w/o integrator
#define PID_VPFC_A_P		Q15(PID_VPFC_KP)
#define PID_VPFC_B_P 		Q15(-PID_VPFC_KP)
#define PID_VPFC_C_P 		0

//// PID defines for VOUT voltage PID
//#define PID_VCHAN_KP 	0.05
//#define PID_VCHAN_KI 	0.1
//#define PID_VCHAN_KD 	0.0
//
//#define PID_VCHAN_A 		Q15(PID_VCHAN_KP + PID_VCHAN_KI + PID_VCHAN_KD)
//#define PID_VCHAN_B 		Q15(-1 *(PID_VCHAN_KP + 2 * PID_VCHAN_KD))
//#define PID_VCHAN_C 		Q15(PID_VCHAN_KD)


//EXTERN fractional V_llcPIDABC[3] __attribute__((space(xmemory)));
//EXTERN fractional V_llcPIDHistory[3] __attribute__((space(ymemory)));

EXTERN fractional VpfcPIDABC[3] __attribute__((space(xmemory)));
EXTERN fractional VpfcPIDHistory[3] __attribute__((space(ymemory)));

EXTERN fractional IpfcPIDABC[3] __attribute__((space(xmemory)));
EXTERN fractional IpfcPIDHistory[3] __attribute__((space(ymemory)));

EXTERN tPID VpfcPID;
EXTERN tPID IpfcPID;
EXTERN tPID V_llcPID;
EXTERN tPID I_llcPID;

EXTERN volatile bool statechanged, newadcdata;


//thermistor values in flash for quick translation
EXTERN const int therm[];

EXTERN volatile int16_t one_over_voltage; //the gain for the PFC
EXTERN volatile int16_t vac_average;
EXTERN volatile int16_t feedforward;
EXTERN volatile int16_t vacrms;
EXTERN volatile int16_t vrms_sq_factor;
EXTERN volatile int16_t powerlimit;
EXTERN volatile int16_t powerstate;
EXTERN volatile int16_t vbus_setpoint;
EXTERN volatile uint16_t currentlimitdynamic;
EXTERN volatile int16_t ipfc_zero_current;
EXTERN volatile bool currentcomparatortripped;
EXTERN volatile int16_t pfc_voltage_skip, pfc_voltage_counter, skipcycles;
EXTERN volatile int16_t an1_ipfc_dma[8];
EXTERN volatile bool lowvinstatus, ocpstatus;
EXTERN volatile int16_t lowvin_ms_counter, ocp_counter, ovp_counter;
EXTERN volatile bool txtrigger;

//adc values
EXTERN volatile int16_t vac_adc, temperature1_adc, vref_adc, 
        temperature2_adc, hvbus_adc, isenpfc_adc;

//EXTERN union rx_union {
//    uint8_t singles[32];
//    uint16_t doubles[16];
//} rx_array;
//
//EXTERN union tx_union {
//    uint8_t singles[32];
//    uint16_t doubles[16];
//} tx_array;

EXTERN volatile uint16_t rxdata[16];
EXTERN volatile bool newrxdata, rxtimeout;
EXTERN volatile int16_t rxtimeoutcounter;
EXTERN volatile uint16_t system_status_sec;
EXTERN volatile int16_t vmeashist[200];
EXTERN volatile int16_t vcontrolhist[200];
EXTERN volatile uint16_t vmeasindex, voutadc, vout_prev_adc, ioutadc;
EXTERN volatile uint8_t bufferin[20];
EXTERN volatile uint8_t bufferout[20];


EXTERN volatile uint16_t rxdata[16];
//EXTERN volatile int16_t uarttimeout;

//state variable definition

typedef enum {
    STANDBYPFC,
    FAULTPFC,
    OVPPFC,
    OTPPFC,
    NOTASTATEPFC,
    TRAPPEDFAULTPFC,
    VALIDATION,
    SOFTSTARTPFC,
    RUNNINGPFC
} pfcstates;

//typedef enum {
//    STANDBYLLC,
//    FAULTLLC,
//    NOTASTATELLC,
//    SOFTSTARTLLC,
//    RUNNINGLLC
//} llcstates;

EXTERN pfcstates systemstate_pfc;
EXTERN pfcstates oldstate_pfc;
//EXTERN llcstates systemstate_llc;
//EXTERN llcstates oldstate_llc;
EXTERN bool statechanged_pfc; //, statechanged_llc;

//enum rxindexes {
//    IOUT_ADC_INDEX,
//    VOUT_ADC_INDEX,
//    SYSTEMSTATUS_SEC,
//    CHECKSUM
//};

enum txindexes {
    VRMS,
    STATE,
    VPID_CONTROL,
    TEMP1,
    TEMP2
};

#define UART1_CONFIG_TX_BYTEQ_LENGTH (12+1)
#define UART1_CONFIG_RX_BYTEQ_LENGTH (12+1)

/** UART Driver Queue

  @Summary
    Defines the Transmit and Receive Buffers

*/

/* this was code that used uart as simple on/off*/
//#define DIS_LLCPWM {ENABLE_LLC_SetHigh();}  
//#define ENA_LLCPWM {ENABLE_LLC_SetLow();}
#define DIS_PFCPWM {PG2IOCONL |= 0b11<<12; PG3IOCONL |= 0b11<<12; }

#ifdef DISABLEPFCONLY  //for testing LLC only
#define ENA_PFCPWM {PG2IOCONL |= 0b11<<12; PG3IOCONL |= 0b11<<12; }
#else
#define ENA_PFCPWM {PG2IOCONL &= ~(0b11<<12); PG3IOCONL &= ~(0b11<<12);}
#endif


#endif	/* XC_HEADER_TEMPLATE_H */

