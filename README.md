# Arduino Earthquake Detector

### What I did use?
- Arduino Nano (Personalized and Redesigned) and Arduino UNO
- ADXL335 3 Axis Accelerometer
- 2x16 LCD Display
- Led (Red and Green)
- Resistors
- Buzzer
- Jumper Cables
- Arduino IDE
- Altium Designer
- Processing 3
- Tinkercad

## Tinkercad Connection Diagram
<img src="https://i.hizliresim.com/d03z1y0.JPG"/>

```Bash
The sensitivity was very low when it was first turned on. In order to increase its sensitivity, 
the AREF pin is connected to the 3V3 pin and the analogue inputs are set to 3.3V instead of 5V. 
This made the ADXL335 work more smoothly.
```
## Conclusion and Discussion
> I had the opportunity to test the project with artificial vibrations and real earthquakes and the expected results were obtained. Thanks to its small design, it adapts well to the place where it is intended to be mounted. The fact that this place is the columns of the building will enable the sensor to work more accurately. In addition, with Arduino, we can adjust how natural gas, water or other smart home systems of important systems should behave in case of an earthquake. Vibration waves can be watched and recorded live on Processing with the help of a computer.
> I designed an additional circuit to further increase its sensitivity.
```Bash
The main logic of this circuit was this: to amplify only the useful part of the signal without amplifying harmful noise.
```

>To do this, the instrumental operational amplifier i.e. OPAMP, connected in differential mode, OP07 IC can be used as an example. It can be used in any OPAMP IC. Using the potentiometer, we must set the voltage V2 to be slightly lower than V1 and set the utility signal with a second potentiometer.
>The formula for the amplification coefficient is 
<br/>
<p align = "center">Vout = (V1-V2) * K <p/>
