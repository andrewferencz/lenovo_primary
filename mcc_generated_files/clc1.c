#include "clc1.h"

void CLC1_Initialize(void)
{
    // Set the CLC1 to the options selected in the User Interface

	CLC1CONL = 0x8880 & ~(0x8000);

    CLC1CONH = 0x00;

    CLC1SELL = 0x00;

    CLC1GLSL = 0x202;

    CLC1GLSH = 0x00;

    // Clear the CLC Rising Event interrupt flags
    IFS7bits.CLC1PIF = 0;
    // Enabling CLC1 Rising event interrupts.
    IEC7bits.CLC1PIE = 1;
	CLC1_Enable();
}

void __attribute__ ((weak)) CLC1_PositiveEdge_CallBack(void)
{
    // Add your custom callback code here
}

void __attribute__ ((weak)) CLC1_NegativeEdge_CallBack(void)
{
    // Add your custom callback code here
}

/* Rising Interrupt ISR */
void __attribute__ ( ( interrupt, no_auto_psv ) ) _CLC1PInterrupt (  )
{

    IFS7bits.CLC1PIF = 0;
}

void CLC1_NegativeEdge_Tasks ( void )
{
	if(IFS11bits.CLC1NIF)
	{
		// CLC1 NegativeEdge callback function 
		CLC1_NegativeEdge_CallBack();
		
		// clear the CLC1 interrupt flag
		IFS11bits.CLC1NIF = 0;
	}
}
bool CLC1_OutputStatusGet(void)
{
    return(CLC1CONLbits.LCOUT);

}
/**
 End of File
*/
