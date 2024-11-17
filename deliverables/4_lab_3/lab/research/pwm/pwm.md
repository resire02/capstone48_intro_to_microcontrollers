## Pulse Width Modulation

### PWM Introduction

#### What is Pulse Width Modulation?

Pulse Width Modulation (PWM) is a technique used to generate variable output voltage by rapidly
switching a pin between high and low states at a fixed **frequency**. The **duty cycle** (percentage of the time 
the pin is high) determines the average voltage output. As the relative on-time of the signal increases or decreases,
the average voltage of the signal also changes. This average voltage provides an equivalent lower power, 
while still keeping the full voltage during the pulse's on-state. This is useful for applications like motor 
speed control, LED dimming, and audio synthesis. 

#### Frequency
Frequency measures how fast the signal is alternating between HIGH and LOW. It is measured in Hz.
Its inverse is the full period time interval. 

```
    Frequency = (1 / Period) Hz
```

#### Duty Cycle
The duty cycle is the fraction of time the signal is "high" versus "low". It is expressed
as a percentage. In motors and heating applications, the duty cycle dictates the power.
The duty cycle formula is as follows:

```
    Duty Cycle = (Time On) / (Period) * 100%
```

