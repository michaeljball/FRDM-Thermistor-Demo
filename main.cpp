/* FRDM-Thermistor-Demo
This is a Thermistor to Temerature conversion demo 
for the @NXP (@freescale) FRDM-K64F demo board
Much thanks to @Adafruit for this tutorial:
https://learn.adafruit.com/thermistor/using-a-thermistor

The 100K Thermistor is configured with a 4.7k series resistor 
tied to vcc (3.3v)  like this:

    +3.3v
      |
      \
      /  4.7k series resistor
      \
      /
      |
      .-----------O To Anlog pin on FRDM board
      |
      \
      /
  Thermistor  100k Nominal
      \
      /
      |
     ---
     GND
           

*/
 

#include "mbed.h"

#define THERMISTORNOMINAL 100000      // 100k 
// temp. for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25   
// The beta coefficient of the thermistor (usually 3000-4000)
#define BCOEFFICIENT 3950
// the value of the 'other' resistor
#define SERIESRESISTOR 4700    
  
AnalogIn Thermistor(A3);

   

Serial pc(USBTX, USBRX);


// This is the workhorse routine that calculates the temperature
// using the Steinhart-Hart equation for thermistors
// https://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation
float get_temperature()
{
    float temperature, resistance;
    float steinhart;
    int a;
    
    a = Thermistor.read_u16();       // Read 16bit Analog value
    pc.printf("Raw Analog Value for Thermistor = %d\r\n",a);
  
    /* Calculate the resistance of the thermistor from analog votage read. */
    resistance = (float) SERIESRESISTOR / ((65536.0 / a) - 1);
    pc.printf("Resistance for Thermistor = %f\r\n",resistance);
   
    steinhart = resistance / THERMISTORNOMINAL;         // (R/Ro)
    steinhart = log(steinhart);                         // ln(R/Ro)
    steinhart /= BCOEFFICIENT;                          // 1/B * ln(R/Ro)
    steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15);   // + (1/To)
    steinhart = 1.0 / steinhart;                        // Invert
    temperature = steinhart - 273.15;                              // convert to C

    return temperature;
}
   
 


int main()
{
    pc.baud(115200);    
    pc.printf("\r\nThermistor Test - Build " __DATE__ " " __TIME__ "\r\n");
  
    while(1) {  
       pc.printf("Temperature %f *C\r\n",get_temperature()); 

       wait(.5); 
    }
}
