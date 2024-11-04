# Project Description  

## Overview (ABET-2): 

Microchip is seeking to create an introductory lab course on working with microcontrollers and gathering input regarding the learning process from the capstone team during development. Microcontrollers serve an important purpose in modern computers, which is why it is important for students to know about them. As such, the purpose of the project is to identify and strengthen points of confusion in university-level microcontroller courses. The course will be using the Arduino and MPLABX environments to teach fundamental concepts and will be tailored toward university students in Engineering, Mechatronics, Life Sciences, and Computer Science fields.

## Global Trends (EM@FSE-e)

This project focuses on improving the effectiveness and quality of educational content on hardware concepts such as microcontrollers and embedded system design for beginner level students. This aligns with the overall push for accessible learning by bridging a gap from students to a complex and generally hard-to-access topic and equips students with hands-on learning experiences to foster interest and growth in technical fields.

## Market Analysis (EM@FSE-k)

WIth a unique focus on specialized learning that other market players might fall short of providing, Microchip University offers **free** online course content in a diverse number of topics within embedded control systems, including embedded software development, advanced C Programming, peripheral architecture, and embedded control IDE’s. The rise of online learning in recent years has opened doors for increased accessibility and flexibility, allowing learners to acquire specialized knowledge from anywhere in the world. Additionally, this project will contribute to enhancing the user experience, such as the Out-of-Box Experience (OBE), for new Microchip customers who are beginning their journey with embedded control systems.

## Security Considerations (SER-2)

As the project is open-source, any material developed will not be subject to special confidentiality agreements or expectations. All code is run locally on microcontrollers and associated boards provided to the team, so no external source should be able to interfere or interact with our personal environments where we develop code. External libraries used in the IDE have already been checked and others will not be needed to develop this basic microcontroller course. 

## Key Requirements (SER-2): 

The final goal is to deliver lab course materials for a **Microcontroller Lab Course** that can blend in with a full **Introduction to Microcontrollers** course. This material will be split up into two sections to be developed in each of the corresponding phases:

- Section 1: Arduino based materials  
- Section 2: MCC Melody / MPLABX based materials

	Both sections will cover IDE configuration and installation, basic GPIO operation such as LED control and switch reads, serial communication, I2C, SPI, and analog to digital conversion.  The documentation must provide walkthrough assistance in performing tasks required for lab instruction. An associated goal of the project will be to acquire our student perspective and input to improve the learning experience for course participants. This means that the manuals must document personal problems while performing the corresponding instructional lab tasks. As mentioned by our project sponsor, materials must maintain a focus on balance of text, pictures, and code snippets to generate the highest amount of understanding.

## Deliverables (SER-1): 

The Deliverables for this project will be individual lessons that will be covered in the lab manuals we will produce alongside the lessons. Each lesson in the lab manual will include a set of instructions on how to meet the objectives and outcomes of the lesson. The lab manuals will also contain Source code for the given activities in the lessons that will be well-commented to allow the user to learn and understand the code. Additionally, the lab manuals will include how to guides and troubleshooting tricks and tips.

## Acronyms and abbreviations (ABET-3): 

| Acronym/abbreviation | Verbose name | Meaning and relevance |
| :---- | :---- | :---- |
| Curiosity Nano | AVR64DD32 Curiosity Nano evaluation kit | This is the main microcontroller we will be using for the duration of the project. More information about the board can be found at [https://www.microchip.com/en-us/development-tool/ev72y42a](https://www.microchip.com/en-us/development-tool/ev72y42a) |
| IDE | Integrated Developer Environment | Integrated Developer Environments are programs used to develop, run, and test code. In this case, an IDE made by Arduino will be used for developing and debugging code on the Curiosity Nano for the first half of the project |
| PWM | Pulse Width Modulation | This is a technique that is used to control the average power supplied to a load by varying the width of a pulse of constant amplitude. This is used to control the brightness of LEDs, the speed of motors and other external devices that need precise control of analog outputs. |
| ADC | Analog-to-Digital Converter | This converts an analog signal (continuous voltage or current)  into a digital signal (a sequence of binary numbers). This is used for taking in the input values of sensors and other components and changing them into a form that can be processed and used. |
| DAC | Digital-to-Analog Converter | This converts a digital signal (a sequence of binary numbers) into an analog signal (a continuous voltage or current). This is used to generate analog outputs such as audio signals, control voltages for motors and waveforms for signal generation. |
| UART | Universal Asynchronous Receiver/Transmitter | A serial communication protocol used to transmit data one bit at a time, asynchronously. This is used to communicate with sensors and displays. basic communication. |
| I2C | Inter-Integrated Circuit | A multi-master, multi-slave serial communication protocol. It  uses a shared bus for communication between devices. Is commonly used for connecting multiple devices  such as sensors, memory chips, and display drivers. |
| SPI | Serial Peripheral Interface | Communication protocol that allows devices to transfer data over short distances at high speeds. |
| MCC | MPLAB Code Configurator  | Graphical programming environment for generating code for embedded software projects. |
| MPLABX | MPLABX Integrated Development Environment | MPLAB X is the Integrated Development Environment that helps developers create programs for Microchip’s microcontrollers, microprocessors, and digital signal controllers. |

# Design and Architecture  

### Design Description (ABET-1, ABET-2)

The final deliverable consists of a modular collection of materials for guiding students in performing incremental lab exercises. Lab exercise should follow a structured format with a template that includes:

- Learning Objectives  
- Required Materials  
- Setup Instructions  
- Requirements  
- Submission Instructions  
- Rubric  
- Additional Reference Materials  
- Sources  
  Interaction with external systems will be described in detailed diagrams that may include a combination of the following elements:

- Schematics  
- State Diagrams  
- UML Class Diagrams  
- Sequence Diagrams

	Appendices will be included as required on a per-lab basis.

### Alternate Design Possibilities (EM@FSE-b)

Alternatively, the lab course materials may be combined into one general document with consolidated appendices to provide the students with one comprehensive resource. This would offer all relevant content in the same place.

# Implementation Strategy 

## High-level Work Breakdown Structure (SER-1): 

Deliverable 1: Lab Manuals

Task 1: Develop Lesson Plans

* Work Scope: Outline the objectives, learning outcomes, and key concepts for each lesson.  
* Skillset Required: Instructional design, subject matter expertise in microcontrollers.  
* Expected Time: 2 weeks

  Task 2: Create Lab Activities

* Work Scope: Develop hands-on experiments and exercises that reinforce the concepts learned in the lessons.  
* Skillset Required: Microcontroller programming, problem-solving, creativity.  
* Expected Time: 4 weeks

  Task 3: Write Lab Manual Instructions

* Work Scope: Write clear and concise instructions for each lab activity, including step-by-step procedures, expected results, and troubleshooting tips.  
* Skillset Required: Technical writing, instructional design.  
* Expected Time: 3 weeks

  Task 4: Review and Revise

* Work Scope: Review and revise the lab manuals for clarity, accuracy, and completeness.  
* Skillset Required: Subject matter expertise, proofreading.  
* Expected Time: 1 week  
  Deliverable 2: Source Code

  Task 1: Develop Code Examples

* Work Scope: Create well-commented source code examples that demonstrate the concepts covered in the lab manuals.  
* Skillset Required: Microcontroller programming, coding standards.  
* Expected Time: 6 weeks

  Task 2: Test and Debug

* Work Scope: Test the code examples to ensure they function correctly and are free of errors.  
* Skillset Required: Debugging skills, problem-solving.  
* Expected Time: 2 weeks  
  Task 3: Document Code

* Work Scope: Provide clear and concise documentation for the source code, including explanations of key functions and variables.  
* Skillset Required: Technical writing.  
* Expected Time: 1 week  
  Deliverable 3: Evaluation Materials

  Task 1: Develop Assessment Tools

* Work Scope: Create quizzes, assignments, or projects to assess students' understanding of the lab material.  
* Skillset Required: Assessment design, subject matter expertise.  
* Expected Time: 2 weeks  
  Task 2: Create Rubrics

* Work Scope: Develop rubrics or scoring guidelines for evaluating student work.  
* Skillset Required: Assessment design.  
* Expected Time: 1 week  
  Task 3: Review and Revise

* Work Scope: Review and revise the assessment materials for clarity, fairness, and alignment with the learning objectives.  
* Skillset Required: Subject matter expertise, assessment design.  
* Expected Time: 1 week  
  Deliverable 4: Supplementary Materials

  Task 1: Identify Relevant Resources

* Work Scope: Research and identify online tutorials, videos, or articles that can supplement the lab materials.  
* Skillset Required: Information retrieval, subject matter expertise.  
* Expected Time: 1 week  
  Task 2: Curate Resource Collection

* Work Scope: Organize and curate a collection of supplementary materials for students to access.  
* Skillset Required: Information management.  
* Expected Time: 1 week  
  Assumptions:

* Students have access to the necessary hardware and software for completing the labs.  
* Instructors are available to provide support and guidance to students.  
* The project timeline is flexible and can be adjusted as needed.  
  Potential Risks:

* Delays in acquiring necessary resources (hardware, software, etc.)  
* Unexpected technical difficulties with the microcontroller platform or development tools.  
* Changes in project scope or requirements that could impact the timeline.  
* 

## Schedule / Timeline (SER-1): 

The project is structured into two phases. Each phase focuses on developing lab activities and materials using microcontroller development environments. The first phase (September to December 2024\) will focus on introductory concepts in Arduino. The second phase will emphasize MCC Melody and MPLABX. Our deliverables have to-be-determined topics that will be decided as we gain experience in this field and work with our sponsor.

Phase 1 – Development of Adurino and Microcontroller Lab Materials (9/18/24 – 12/25/24?)

* Arduino IDE and DXCore Setup Deliverable – (9/24/24 \- 10/9/24)

  * Lab Documents, Learning Reflections

* Working with Arduino: GPIO and Serial Deliverable – (10/9/24 \- 10/23/24)

  * Lab Documents, Learning Reflections

* Topic To Be Determined Deliverable – (10/23/24 \- 11/6/24)

  * Lab Documents, Learning Reflections

* Topic To Be Determined Deliverable – (11/6/24 \- 11/20/24)

  * Lab Documents, Learning Reflections

* Topic To Be Determined Deliverable – (11/20/24 \- 12/4/24)

  * Lab Documents, Learning Reflections

* Topic To Be Determined Deliverable – (12/4/24 \- 12/18/24)

  * Lab Documents, Learning Reflections

Phase 2 – Development MCC Melody and MPLABX Lab Materials (1/1/25 – 4/20/25)

* Topic To Be Determined Deliverable – (1/1/25 \- 1/15/25)  
  * Submittables Unknown At This Time  
* Topic To Be Determined Deliverable – (1/15/25 \- 1/29/25)  
  * Submittables Unknown At This Time  
* Topic To Be Determined Deliverable – (1/29/25 \- 2/12/25)  
  * Submittables Unknown At This Time  
* Topic To Be Determined Deliverable – (2/12/25 \- 2/26/25)  
  * Submittables Unknown At This Time  
* Topic To Be Determined Deliverable – (2/26/25 \- 3/12/25)  
  * Submittables Unknown At This Time  
* Topic To Be Determined Deliverable – (3/12/25 \- 3/26/25)  
  * Submittables Unknown At This Time  
* Topic To Be Determined Deliverable – (3/26/25 \- 4/9/25)  
  * Submittables Unknown At This Time

Innovation Showcase (4/20/25)

## Required Hardware (SER-1, EM@FSE-o): 

 The capstone will require 4 Rev.3 Curiosity Nano Explorer Boards, which will be shipped and delivered to the capstone members. Additionally, 4 AVR64DD32 Curiosity Nano Debugging Kits will be provided by a Microchip representative to the capstone team in person. The capstone team will be allowed to keep the hardware after the end of the capstone. Additionally, a device capable of running the Arduino IDE for developing the code to put onto the boards will be necessary.

## Third party content (SER-1, EM@FSE-o): 

The capstone will require the Arduino IDE, which is under GNU Affero General Public License v3.0. The license allows commercial use modification, distribution, patent use, private use, but disallows liability and warranty. 

## Quality (SER-2): 

The Quality Goals for this project focus on ensuring the lab materials meet both functional and non-functional requirements. Functionally, the lbs must work as intended, with at least 90% of students completing them independently and providing clear, concise instructions. Non-functional goals include readable, reusable, and efficient code. This will be achieved by adhering to coding standards and style guides for both C++ (Arduino) and C, ensuring modularity and clear documentation.

The test strategy involves unit testing for individual functions, integration testing for hardware-software interaction, and performance testing to ensure efficient execution. User feedback will be used to evaluate clarity and usability. Through these methods, we will meet the sponsor’s expectations for both software functionality and overall lab experience.

## References/Sources of Information (EM@FSE-q)

Knowledge of hardware and microcontroller programming will be the most fundamental for this project, with the following links being provided by the sponsor: 

* [https://www.hackster.io/](https://www.hackster.io/)  
* [https://www.arduino.cc/](https://www.arduino.cc/)  
* [https://www.tinyml.org/](https://www.tinyml.org/)  
  In phase 2, we will also need to have more information about the specialized IDE (MPLABX) and its associated code configurator (MCC Melody), information about it can be found on Microchip’s website itself:

* [https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide)  
* [https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator/melody](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator/melody)


## Scalability (EM@FSE-J)

As this project is open-source and free, revenue is not really a factor as much as willingness from the participants creating the information. Scalability would be under less of a monetary constraint (unless it became difficult to supply boards to people developing the content) and more about whether the company or community around the content feel it is worth it to keep creating. 

## Other Special considerations (ABET-2): 

		An additional consideration for this project is the understanding of beginner and intermediate microcontroller concepts that will allow for a well developed lab materials that can cater to diverse groups of students. Phase 1 needs additional considerations for understanding the Arduino IDE, libraries, and Hardware components. Phase 2 will need a more in-depth understanding of lower-level microcontroller features such as serial communication, PWM, and ADC in C. 

# process 

## Process Description and justification (SER-1) 

Similarly to SCRUM methodologies, our project employs a rotating leadership model that allows each team member to gain technical expertise while taking on leadership roles in each iteration of the creational process. This rotation ensures that each one will be engaged in every aspect of the project, from content development to quality assurance. Additionally, it will foster a collaborative environment where every team member plays a critical role in the successful completion of the deliverables.

## Tools (SEr-1, EM@FSE-O): 

The main non-hardware tools used in this project will include the Arduino IDE, MCC Melody, and MPLABX. 

Important external links include: 

* [https://www.arduino.cc/](https://www.arduino.cc/)  
* [https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide)  
* [https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator/melody](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator/melody)

## Roles and Responsibilities (SER-1): 

Key roles in the project include a periodical team lead, a content developer, a document specialist, and a tester / validator. The team lead is in charge of communicating progress and challenges during the two-week period. The content developer is responsible for designing and building the lab exercises and educational materials. The document specialist maintains consistency and accessibility of all written materials. The tester and validation lead reviews content for effectiveness and accuracy to ensure educational standards are met.

## Location of Project Artifacts (SER-1): 

We will be developing our course material out of Google Drive and synchronizing its contents with the sponsor’s OneDrive. While this option was chosen for us as it was requested to be used by the sponsor, we believe it to be secure, available, and easily sortable to make our manual easy to put together more formally in the future. 

## Sponsor communications (ABEt-3): 

We will conduct meetings with our sponsor biweekly over Microsoft Teams. For any additional communication, we will be using email to communicate with our sponsor.

# Risk management 

## identified Potential risks (SER-2): 

A major potential risk is the possible damage to hardware components from either external sources or human error that may delay development time. Another potential risk is increased exposure to developmental bugs arising from development with low-level languages such as C. The group’s availability will also be another risk to consider as the capstone members generally have busy schedules this semester.

## mitigation strategies (SER-2): 

	The risks of this project are the following Hardware Failures, Complexity of Phase 2 Material, Ambiguity in Lab Instructions, and Software Bugs. For Hardware failure this involves the risk of sensors, motors, and other components malfunctioning or becoming unavailable. To mitigate this it is necessary to have multiple backup hardware components. For this project the team has 4 development boards and 4 Curiosity Nano. The next Risk is the Complexity of Phase 2 Material since it will be using a professional level development environment it may become too complex for some students. To address this, we will provide additional learning resources and simplified introduction materials. The next risk that we face is Ambiguity in Lab Instructions, which may cause students to struggle to complete the exercises from our lab materials. We will collect feedback and do testing on how well the instructions are to understand. The final risk is software bugs for this code issues are much harder to work find and fix. We will be conducting extensive unit testing and integration testing process.