/*
 * File:   ADC.c
 * Author: Bui Duc Huy
 *
 * Created on March 15, 2020, 10:23 AM
 */
void ADC_Init()
{    
    TRISA = 0xFF;		/*Set as input port*/
    ADCON1 = 0x0E;      /*Ref vtg is VDD & Configure pin as analog pin*/    
    ADCON2 = 0x92;  	/*Right Justified, 4Tad and Fosc/32. */
    ADRESH=0;  			/*Flush ADC output Register*/
    ADRESL=0;   
}

int ADC_Read(int Channel)
{
    int digital;
    ADCON0 =(ADCON0 & 0b11000011)|((Channel<<2) & 0b00111100);

    /*channel 0 is selected i.e.(CHS3CHS2CHS1CHS0=0000)& ADC is disabled*/
    ADCON0 |= ((1<<ADON)|(1<<GO));/*Enable ADC and start conversion*/

    /*Wait for End of conversion i.e. Go/done'=0 conversion completed*/
    while(ADCON0bits.GO_nDONE==1);

    digital = (ADRESH*256) | (ADRESL);/*Combine 8-bit LSB and 2-bit MSB*/
    return(digital);
}