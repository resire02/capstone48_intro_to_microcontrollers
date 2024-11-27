# Self Learning Evaluation

**Capstone Member:**	Gonzalo Allendes  
**Sprint Name:**		Lab 3  
**Link to Taiga Task:**	[User Story 89 Task 99](https://tree.taiga.io/project/bookstrong-introduction-to-microcontroller/task/97)  
**Sprint Topic:**		Pulse Width Modulation
---

**What went well during the learning process?**  
The analogWrite() function already supports PWM. It is a very efficient function that enables PWM on pins without the need to 
implement external libraries. 

**Were there any topic(s) that were difficult to understand during the learning process?**   
 I had to review the main concepts behind PWM, but I found a source that covers the main concepts on PWM in Arduino [here](https://deepbluembedded.com/arduino-analogwrite/).

**What troubles/issues did you encounter while working with the Arduino system?**   
The function analogWrite() does not support writing three colors to the RGB LED at the same time.
You can do this with digitalWrite() but not analogWrite(). I found an external library that supports this type of operation.

**If you encountered any issues while working with Arduino, were you able to fix them? If so, what steps did you take to fix the issues you encountered?**    
Yes. The trickiest part is routing the TCA to port D. There will be a necessary explanation in the lab.
Depending on the pin, you need to either route the TCA to PORTA, PORTC, PORTD, or PORTF to enable PWM on the desired outputs.
There is a chart on page 162 of the Curiosity Nano datasheet with the corresponding timer/pin mapping.

**Anything important to note for development of the lab manual? This includes research, unusual problems, and external knowledge.**  
Unusual problems were covered in the previous questions.