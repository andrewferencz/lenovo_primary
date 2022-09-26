#include <xc.h>
#include "uart1.h"

/**
  Section: UART1 APIs
*/

void UART1_Initialize(void)
{
/**    
     Set the UART1 module to the options selected in the user interface.
     Make sure to set LAT bit corresponding to TxPin as high before UART initialization
*/
    // URXEN disabled; RXBIMD RXBKIF flag when Break makes low-to-high transition after being low for at least 23/11 bit periods; UARTEN enabled; MOD Asynchronous 8-bit UART; UTXBRK disabled; BRKOVR TX line driven by shifter; UTXEN disabled; USIDL disabled; WAKE disabled; ABAUD disabled; BRGH enabled; 
    // Data Bits = 8; Parity = None; Stop Bits = 1 Stop bit sent, 1 checked at RX;
    U1MODE = (0x8080 & ~(1<<15));  // disabling UARTEN bit
    // STSEL 1 Stop bit sent, 1 checked at RX; BCLKMOD disabled; SLPEN disabled; FLO Off; BCLKSEL FOSC/2; C0EN disabled; RUNOVF disabled; UTXINV disabled; URXINV disabled; HALFDPLX disabled; 
    U1MODEH = 0x00;
    // OERIE disabled; RXBKIF disabled; RXBKIE disabled; ABDOVF disabled; OERR disabled; TXCIE disabled; TXCIF disabled; FERIE disabled; TXMTIE disabled; ABDOVE disabled; CERIE disabled; CERIF disabled; PERIE disabled; 
    U1STA = 0x00;
    // URXISEL RX_ONE_WORD; UTXBE enabled; UTXISEL TX_BUF_EMPTY; URXBE enabled; STPMD disabled; TXWRE disabled; 
    U1STAH = 0x22;
    // BaudRate = 125000; Frequency = 100000000 Hz; BRG 199; 
    U1BRG = 199;
    // BRG 0; 
    U1BRGH = 0x00;
    // P1 0; 
    U1P1 = 0x00;
    // P2 0; 
    U1P2 = 0x00;
    // P3 0; 
    U1P3 = 0x00;
    // P3H 0; 
    U1P3H = 0x00;
    // TXCHK 0; 
    U1TXCHK = 0x00;
    // RXCHK 0; 
    U1RXCHK = 0x00;
    // T0PD 1 ETU; PTRCL disabled; TXRPT Retransmit the error byte once; CONV Direct logic; 
    U1SCCON = 0x00;
    // TXRPTIF disabled; TXRPTIE disabled; WTCIF disabled; WTCIE disabled; BTCIE disabled; BTCIF disabled; GTCIF disabled; GTCIE disabled; RXRPTIE disabled; RXRPTIF disabled; 
    U1SCINT = 0x00;
    // ABDIF disabled; WUIF disabled; ABDIE disabled; 
    U1INT = 0x00;
    
    U1MODEbits.UARTEN = 1;   // enabling UART ON bit
    U1MODEbits.UTXEN = 1;
    U1MODEbits.URXEN = 1;
}

uint8_t UART1_Read(void)
{
    while((U1STAHbits.URXBE == 1))
    {
        
    }

    if ((U1STAbits.OERR == 1))
    {
        U1STAbits.OERR = 0;
    }
    
    return U1RXREG;
}

void UART1_Write(uint8_t txData)
{
    while(U1STAHbits.UTXBF == 1)
    {
        
    }

    U1TXREG = txData;    // Write the data byte to the USART.
}

bool UART1_IsRxReady(void)
{
    return (U1STAHbits.URXBE == 0);
}

bool UART1_IsTxReady(void)
{
    return ((!U1STAHbits.UTXBF) && U1MODEbits.UTXEN );
}

bool UART1_IsTxDone(void)
{
    return U1STAbits.TRMT;
}


/*******************************************************************************

  !!! Deprecated API !!!
  !!! These functions will not be supported in future releases !!!

*******************************************************************************/

uint32_t __attribute__((deprecated)) UART1_StatusGet (void)
{
    uint32_t statusReg = U1STAH;
    return ((statusReg << 16 ) | U1STA);
}

void __attribute__((deprecated)) UART1_Enable(void)
{
    U1MODEbits.UARTEN = 1;
    U1MODEbits.UTXEN = 1; 
    U1MODEbits.URXEN = 1;
}

void __attribute__((deprecated)) UART1_Disable(void)
{
    U1MODEbits.UARTEN = 0;
    U1MODEbits.UTXEN = 0; 
    U1MODEbits.URXEN = 0;
}


