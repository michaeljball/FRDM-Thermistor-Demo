# FRDM-Thermistor-Demo

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
           


 
