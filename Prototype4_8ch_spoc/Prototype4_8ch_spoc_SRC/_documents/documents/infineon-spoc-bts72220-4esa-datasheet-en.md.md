

<!-- PageNumber="Side 1" -->


<figure>

infineon

</figure>


# BTS72220-4ESA

SPOC™ +2
Serial Interface Power Controller


<figure>

0
·
Qualified

PRO
SIL

ISO 26262
ready

AEC

V

RoHS

</figure>


## 1 Overview


### Potential Applications

· Suitable for resistive, inductive and capacitive loads

· Replaces electromechanical relays, fuses and discrete circuits

· Driving capability suitable for 7 A and 4 A loads and high inrush current
loads such as 65W bulb or equivalent electronic loads (e.g. LED modules)
and 42W bulb or equivalent electronic loads (e.g. LED modules)

2x 5.5 mΩ

2x 13.5 ml2


<table>
<tr>
<td>Package</td>
<td>PG-TSDSO-24</td>
</tr>
<tr>
<td>Marking</td>
<td>72220-4ESA</td>
</tr>
</table>


<figure>

J
Infineon

</figure>


<figure>
<figcaption>Figure 1 Application Diagram. Further information in Chapter 11</figcaption>

VBAT

Optional

ZWIRE

Fail-safe
Control

Optional

Logic Supply

Cvs1

CVSGND

RIN

REND

T1

CVDD

RVD

VDD

GND

VS

VDD

Ro

GPIO

RIN

IN0

GPIO

RIN

IN1

OUT0

Microcontroller

GPIO

RIN

INZ

OUT1

GPIO

RIN

IN3

+2

SPOC™M +

OUT2

RPD

RLHI

LHI

Dz2

Cvs2

CSN

RCSN

CSN

OUT3

SCLK

RSCLK

SCLK

MISO

Rso

SO

ZWIRE

ZWIRE

MOSI

Rs

SI

VSS

ADC

RADC

RIS PROT

IS

COUT

COUT

CADC

Dz1

RSENSE

COUT

COUT

ZLOAD*

ZLOAD*

Logic GND

Optional

Application_dich_nolDamit

Power GND

*See Chapter 1 „Potential Applications“

Chassis GND

** See Chapter 11.2 „External Components“

</figure>


<!-- PageFooter="Data Sheet www.infineon.com" -->
<!-- PageNumber="1" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 2" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


#### Overview


##### Basic Features

· High-Side Switch with Diagnosis and Embedded Protection

· Part of SPOC™ +2 Family

· Daisy Chain capable SPI interface

· 3.3 V and 5 V compatible logic pins

· Slew rate control for all Channels

· ReverseON for low power dissipation in Reverse Polarity

· Switch ON capability while Inverse Current condition (InverseON)

· Green Product (RoHS compliant)


##### Protection Features

· Absolute and dynamic temperature limitation with controlled restart

· Overcurrent protection (tripping) with Programmable Restart Control and Current Threshold

· Undervoltage shutdown

· Overvoltage protection with external components


##### Diagnostic Features

· Proportional load current sense multiplexed

· Open Load in ON and OFF state

· Short circuit to ground and battery

· Diagnosis feedback via SPI


##### Functional Safety Features

· Limp Home mode

· Monitoring of Input pin status (IN and LHI)

· Checksum verification of Configuration Registers

· Current Sense verification mode


##### Product Validation

Qualified for automotive applications. Product validation according to AEC-Q100 Grade 1.


##### Description

The BTS72220-4ESA is a Serial Interface Power Controller, providing protection functions and diagnosis. The
device is integrated in SMART7 technology.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="2" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 3" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Overview


<table>
<caption>Table 1 Product Summary</caption>
<tr>
<th>Parameter</th>
<th>Symbol</th>
<th>Values</th>
</tr>
<tr>
<td>Minimum Operating voltage (at switch ON)</td>
<td>VS(OP)</td>
<td>4.1 V</td>
</tr>
<tr>
<td>Minimum Operating voltage (cranking)</td>
<td>VS(UV)</td>
<td>3.1 V</td>
</tr>
<tr>
<td>Maximum Operating voltage</td>
<td>Vs</td>
<td>28 V</td>
</tr>
<tr>
<td>Digital Supply voltage</td>
<td>VD</td>
<td>3.3 V or 5 V</td>
</tr>
<tr>
<td>Minimum Overvoltage protection (T) ≥ 25 ℃)</td>
<td>VDS(CLAMP)_25</td>
<td>35 V</td>
</tr>
<tr>
<td>Maximum current in Sleep mode (T) ≤ 85 ℃)</td>
<td>IVS(SLEEP)_85</td>
<td>1.3 µA</td>
</tr>
<tr>
<td>Maximum operative current</td>
<td>IGND(ACTIVE)</td>
<td>7 mA</td>
</tr>
<tr>
<td>Maximum ON-state resistance (T] = 150 ℃) channels 0 and 3</td>
<td>RDS(ON)_150</td>
<td>9 m2</td>
</tr>
<tr>
<td>Maximum ON-state resistance (T) = 150 ℃) channels 1 and 2</td>
<td>RDS(ON)_150</td>
<td>22 m22</td>
</tr>
<tr>
<td>Nominal load current (TA = 85 ℃) channels 0 and 3</td>
<td>IL(NOM)</td>
<td>7 A</td>
</tr>
<tr>
<td>Nominal load current (TA = 85 ℃) channels 1 and 2</td>
<td>IL(NOM)</td>
<td>4 A</td>
</tr>
<tr>
<td>Typical current sense ratio at /L = IL(NOM) channels 0 and 3</td>
<td>KILIS</td>
<td>5500</td>
</tr>
<tr>
<td>Typical current sense ratio at /L = IL(NOM) channels 1 and 2</td>
<td>KILIS</td>
<td>2500</td>
</tr>
<tr>
<td>Serial Clock Frequency</td>
<td>fSCLK(max)</td>
<td>5 MHZ</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="3" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 4" -->


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


<figure>

<!-- PageHeader="Infineon" -->

</figure>


# Block Diagram and Terms


## 2 Block Diagram and Terms


### 2.1 Block Diagram


<figure>
<figcaption>Figure 2 Block Diagram of BTS72220-4ESA</figcaption>

VS

☒

Channel 0

VDD

☒

Channel 1

Channel 2

SO
☒

Channel 3

Voltage Sensor

SI
☒

Overtemperature

T

SCLK
☒

Driver
Logic

Gate Control
&
Chargepump

Overvoltage
Clamping

☒
OUT0

CSN
☒

ESD
Protection
+
I/O Logic

☒
OUT1

LHI
☒

ReverseON
In verseON

Overcurrent
Protection

☒

OUT2

IN0
☒

☒
OUT3

Output Voltage Limitation

IN1
☒

IN2
☒

Load Current Sense Multiplexer

IN3
☒

Internal Power Supply

Overvoltage Protection

IS
☒

Reverse Polarity
Protection

VS Monitoring

Limp Home Control

GND
☒

GND Circuitry

SPI Interface

Internal Logic Supply

BlockDiagram_4chnoED.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="4" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 5" -->


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


<figure>

Infineon

</figure>


# Block Diagram and Terms


## 2.2 Terms

Figure 3 shows all terms used in this data sheet, with associated convention for positive values.


<figure>
<figcaption>Figure 3 Voltage and Current Convention</figcaption>

Ivs

VSIS

☒

VS

/DD

☒
VDD

VDSn

Iso

Vs

☒
SO

İSI

VD

☒
SI

ISCLK

Vso

☒
SCLK

/ Ln

ICSN

VSI

☒
CSN

OUTn
☒

/LHI

VSCLK

☒
LHI

/INn

VCSN

☒
INn

/Is

VLHI

☒
IS

VOUTn

VINn

GND
☒

VIS

IGND

Terms_noED.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="5" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 6" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Pin Configuration


# 3 Pin Configuration


## 3.1 Pin Assignment


<figure>
<figcaption>Figure 4 Pin Configuration</figcaption>

(top view)

GND

1

24

OUT0

VDD

2

23

OUT0

SO

3

22

OUT0

SI

4

21

OUT0

SCLK

5

20

OUT1

CSN

6

LHI

7

VS

19

OUT1

18

OUT2

IN0

8

17

OUT2

IN1

9

16

OUT3

IN2

10

15

OUT3

IN3

11

14

OUT3

IS

12

13

OUT3

exposed pad (bottom)

Pin Out_SPOC_220_noED.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="6" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 7" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


## Pin Configuration


### 3.2 Pin Definitions and Functions


<table>
<caption>Table 2 Pin Definition</caption>
<tr>
<th>Pin</th>
<th>Symbol</th>
<th>I/O</th>
<th>Function</th>
</tr>
<tr>
<td>EP</td>
<td>VS (exposed pad)</td>
<td>-</td>
<td>Power Supply Voltage Battery voltage</td>
</tr>
<tr>
<td>1</td>
<td>GND</td>
<td>-</td>
<td>Ground</td>
</tr>
<tr>
<td>2</td>
<td>VDD</td>
<td>-</td>
<td>Digital Supply Voltage</td>
</tr>
<tr>
<td>3</td>
<td>SO</td>
<td>O ☐</td>
<td>Serial output of SPI interface</td>
</tr>
<tr>
<td>4</td>
<td>SI</td>
<td>I</td>
<td>Serial input of SPI interface ("high" active)</td>
</tr>
<tr>
<td>5</td>
<td>SCLK</td>
<td>I</td>
<td>Serial clock of SPI interface ("high" active)</td>
</tr>
<tr>
<td>6</td>
<td>CSN</td>
<td>I</td>
<td>Chip select of SPI interface ("low" active); integrated pull up to VDD</td>
</tr>
<tr>
<td>7</td>
<td>LHI</td>
<td>I</td>
<td>Limp Home activation signal ("high" active)</td>
</tr>
<tr>
<td>8,9</td>
<td>INn</td>
<td>I</td>
<td>Input Channel n</td>
</tr>
<tr>
<td>10,11</td>
<td></td>
<td></td>
<td>Digital signal to switch ON the channel n ("high" active) If not used: connect with a 10 kQ2 resistor either to GND pin or to module ground</td>
</tr>
<tr>
<td>12</td>
<td>IS</td>
<td>O</td>
<td>Current sense output signal</td>
</tr>
<tr>
<td>21-24</td>
<td>OUTn</td>
<td>O</td>
<td>Output n</td>
</tr>
<tr>
<td>19-20</td>
<td></td>
<td></td>
<td>Protected high-side power output of channel n1)</td>
</tr>
<tr>
<td>17-18</td>
<td></td>
<td></td>
<td></td>
</tr>
<tr>
<td>13-16</td>
<td></td>
<td></td>
<td></td>
</tr>
</table>

1\) All output pins of the channel must be connected together on the PCB. All pins of the output are internally connected
together. PCB traces have to be designed to withstand the maximum current which can flow.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="7" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 8" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


#### General Product Characteristics


##### 4 General Product Characteristics


###### 4.1 Absolute Maximum Ratings - General


####### Table 3 Absolute Maximum Ratings1)

TJ =- 40 °C to +150 ℃; all voltages with respect to ground, positive current flowing into pin
(unless otherwise specified)


<table>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Supply pins</td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
</tr>
<tr>
<td>Power Supply Voltage</td>
<td>Vs</td>
<td>-0.3</td>
<td>–</td>
<td>28</td>
<td>V</td>
<td>–</td>
<td>P_4.1.0.1</td>
</tr>
<tr>
<td>Digital Supply Voltage</td>
<td>VD</td>
<td>-0.3</td>
<td>–</td>
<td>5.5</td>
<td>V</td>
<td>–</td>
<td>P_4.1.0.29</td>
</tr>
<tr>
<td>Load Dump Voltage</td>
<td>VBAT(LD)</td>
<td>–</td>
<td>–</td>
<td>35</td>
<td>V</td>
<td>suppressed Load Dump acc. to ISO16750-2 (2010). Ri= 2 02</td>
<td>P_4.1.0.3</td>
</tr>
<tr>
<td>Supply Voltage for Short Circuit Protection</td>
<td>VBAT(SC)</td>
<td>0</td>
<td>–</td>
<td>24</td>
<td>V</td>
<td>Setup acc. to AEC-Q100-012</td>
<td>P_4.1.0.25</td>
</tr>
<tr>
<td>Reverse Polarity Voltage</td>
<td>-V BAT(REV)</td>
<td>–</td>
<td>–</td>
<td>16</td>
<td>V</td>
<td>t ≤ 2 min TA=+25 ℃ Setup as described in Chapter 11</td>
<td>P_4.1.0.5</td>
</tr>
<tr>
<td>Current through GND Pin</td>
<td>IGND</td>
<td>-50</td>
<td>–</td>
<td>50</td>
<td>mA</td>
<td>RGND according to Chapter 11</td>
<td>P_4.1.0.9</td>
</tr>
<tr>
<td>Current through VDD Pin</td>
<td>İVD(REV)</td>
<td>-10</td>
<td>–</td>
<td>30</td>
<td>mA</td>
<td>t ≤ 2 min</td>
<td>P_4.1.0.10</td>
</tr>
<tr>
<td>Counter Reset Delay Time after Fault Condition</td>
<td>tRETRY</td>
<td>50</td>
<td>–</td>
<td>–</td>
<td>ms</td>
<td>–</td>
<td>P_4.1.0.35</td>
</tr>
<tr>
<td colspan="8">Logic &amp; control pins (Digital Input = DI) DI = INn, CS, SCLK, SI, LHI</td>
</tr>
<tr>
<td>Current through DI Pin</td>
<td>IDI</td>
<td>-1</td>
<td>–</td>
<td>2</td>
<td>mA</td>
<td>2)</td>
<td>P_4.1.0.14</td>
</tr>
<tr>
<td>Current through DI Pin Reverse Battery Condition</td>
<td>DI(REV)</td>
<td>-1</td>
<td>–</td>
<td>10</td>
<td>mA</td>
<td>2) t ≤ 2 min</td>
<td>P_4.1.0.36</td>
</tr>
<tr>
<td colspan="8">Logic &amp; control pins (Digital Output = DO) DO = SO</td>
</tr>
<tr>
<td>Current through DO Pin</td>
<td>DO</td>
<td>-2</td>
<td>–</td>
<td>1</td>
<td>mA</td>
<td>2)</td>
<td>P_4.1.0.33</td>
</tr>
<tr>
<td>Current through DO Pin Reverse Battery Condition</td>
<td>DO(REV)</td>
<td>-10</td>
<td>–</td>
<td>1</td>
<td>mA</td>
<td>2) t ≤ 2 min</td>
<td>P_4.1.0.37</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="8" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 9" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


#### General Product Characteristics

Table 3
Absolute Maximum Ratings1) (continued)

TJ =- 40 °C to +150 ℃; all voltages with respect to ground, positive current flowing into pin
(unless otherwise specified)


<table>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>IS pin</td>
<td></td>
<td colspan="4"></td>
<td></td>
<td></td>
</tr>
<tr>
<td>Voltage at IS Pin</td>
<td>VIS</td>
<td>-1.5</td>
<td>–</td>
<td>Vs</td>
<td>V</td>
<td>/Is = 10 µA</td>
<td>P_4.1.0.16</td>
</tr>
<tr>
<td>Current through IS Pin</td>
<td>1 Is</td>
<td>-25</td>
<td>–</td>
<td>IS(SAT),M AX</td>
<td>mA</td>
<td>–</td>
<td>P_4.1.0.18</td>
</tr>
<tr>
<td>Temperatures</td>
<td colspan="5"></td>
<td></td>
<td></td>
</tr>
<tr>
<td>Junction Temperature</td>
<td>TJ</td>
<td>-40</td>
<td>–</td>
<td>150</td>
<td>ºC</td>
<td>–</td>
<td>P_4.1.0.19</td>
</tr>
<tr>
<td>Storage Temperature</td>
<td>TSTG</td>
<td>-55</td>
<td>–</td>
<td>150</td>
<td>ºC</td>
<td>–</td>
<td>P_4.1.0.20</td>
</tr>
<tr>
<td colspan="8">ESD Susceptibility</td>
</tr>
<tr>
<td>ESD Susceptibility all Pins (HBM)</td>
<td>VESD(HBM)</td>
<td>-2</td>
<td>–</td>
<td>2</td>
<td>kV</td>
<td>HBM3)</td>
<td>P_4.1.0.21</td>
</tr>
<tr>
<td>ESD Susceptibility OUTn vs GND and VS connected (HBM)</td>
<td>VESD(HBM)_OUT</td>
<td>-4</td>
<td>–</td>
<td>4</td>
<td>kV</td>
<td>HBM3)</td>
<td>P_4.1.0.22</td>
</tr>
<tr>
<td>ESD Susceptibility all Pins (CDM)</td>
<td>ESD(CDM)</td>
<td>-500</td>
<td>–</td>
<td>500</td>
<td>V</td>
<td>CDM4)</td>
<td>P_4.1.0.23</td>
</tr>
<tr>
<td>ESD Susceptibility Corner Pins (pins 1, 12, 13, 24)</td>
<td>VESD(CDM)_CRN</td>
<td>-750</td>
<td>–</td>
<td>750</td>
<td>V</td>
<td>CDM4)</td>
<td>P_4.1.0.24</td>
</tr>
</table>

1\) Not subject to production test - specified by design.

2\) Maximum Vpi to be considered for Latch-Up tests: 5.5 V.

3\) ESD susceptibility, Human Body Model "HBM", according to AEC Q100-002.

4\) ESD susceptibility, Charged Device Model "CDM", according to AEC Q100-011.


Notes

1\. Stresses above the ones listed here may cause permanent damage to the device. Exposure to absolute
maximum rating conditions for extended periods may affect device reliability.

2\. Integrated protection functions are designed to prevent IC destruction under fault conditions described in the
data sheet. Fault conditions are considered as "outside" normal operating range. Protection functions are
not designed for continuous repetitive operation.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="9" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 10" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


## General Product Characteristics


### 4.2 Absolute Maximum Ratings - Power Stages


#### 4.2.1 Power Stages - 5.5 m22 channels

Table 4
Absolute Maximum Ratings - 5.5 m22 channels1)

TJ =- 40 °C to +150 ℃; all voltages with respect to ground, positive current flowing into pin
(unless otherwise specified)


<table>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Maximum Energy Dissipation Single Pulse</td>
<td>EAS</td>
<td>–</td>
<td>–</td>
<td>100</td>
<td>mJ</td>
<td>/L =2*/L(NOM) TJ(0) = 150 ℃ Vs = 28 V</td>
<td>P_4.2.13.1</td>
</tr>
<tr>
<td>Maximum Energy Dissipation Repetitive Pulse</td>
<td>EAR</td>
<td>–</td>
<td>–</td>
<td>51</td>
<td>mJ</td>
<td>IL= IL(NOM) TJ(0) = 85 °℃ Vs = 13.5 V 1M cycles</td>
<td>P_4.2.13.2</td>
</tr>
<tr>
<td>Load Current</td>
<td>W11</td>
<td>-</td>
<td>–</td>
<td>/L(OVL),MAX</td>
<td>A</td>
<td>–</td>
<td>P_4.2.13.3</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


#### 4.2.2 Power Stages - 13.5 m22 channels

Table 5
Absolute Maximum Ratings - 13.5 m22 channels1)

TJ =- 40 °C to +150 ℃; all voltages with respect to ground, positive current flowing into pin
(unless otherwise specified)


<table>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Maximum Energy Dissipation Single Pulse</td>
<td>EAS</td>
<td>–</td>
<td>–</td>
<td>35</td>
<td>mJ</td>
<td>IL=2*IL(NOM) TJ(0) = 150 ℃ Vs = 28 V</td>
<td>P_4.2.14.1</td>
</tr>
<tr>
<td>Maximum Energy Dissipation Repetitive Pulse</td>
<td>EAR</td>
<td>–</td>
<td>–</td>
<td>15.5</td>
<td>mJ</td>
<td>IL= IL(NOM) TJ(0) = 85 ℃ Vs = 13.5 V 1M cycles</td>
<td>P_4.2.14.2</td>
</tr>
<tr>
<td>Load Current</td>
<td>V/11</td>
<td>-</td>
<td>–</td>
<td>IL(OVL),MAX</td>
<td>A</td>
<td>–</td>
<td>P_4.2.14.3</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="10" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 11" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


## General Product Characteristics


### 4.3 Functional Range


<table>
<caption>Table 6 Functional Range - Supply Voltages and Temperature1)</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Power Supply Voltage Range for Normal Operation</td>
<td>VS(NOR)</td>
<td>6</td>
<td>13.5</td>
<td>18</td>
<td>V</td>
<td>–</td>
<td>P_4.3.0.1</td>
</tr>
<tr>
<td>Lower Extended Power Supply Voltage Range for Operation</td>
<td>VS(EXT,LOW)</td>
<td>3.1</td>
<td>–</td>
<td>6</td>
<td>V</td>
<td>2)3) (parameter deviations possible)</td>
<td>P_4.3.0.2</td>
</tr>
<tr>
<td>Upper Extended Power Supply Voltage Range for Operation</td>
<td>VS(EXT,UP)</td>
<td>18</td>
<td>–</td>
<td>28</td>
<td>V</td>
<td>3) (parameter deviations possible)</td>
<td>P_4.3.0.3</td>
</tr>
<tr>
<td>Digital Supply Voltage Range</td>
<td>VD(NOR)</td>
<td>3.0</td>
<td>–</td>
<td>5.5</td>
<td>V</td>
<td>–</td>
<td>P_4.3.0.4</td>
</tr>
<tr>
<td>Junction Temperature</td>
<td>TJ</td>
<td>-40</td>
<td>–</td>
<td>150</td>
<td>ºC</td>
<td>–</td>
<td>P_4.3.0.5</td>
</tr>
</table>

1\) Not subject to production test - specified by design.

2\) In case of Vs voltage decreasing: VS(EXT,LOW), MIN = 3.1 V. In case of Vs voltage increasing: VS(EXT,LOW), MIN = 4.1 V.

3\) Protection functions still operative.

Note:
Within the functional or operating range, the IC operates as described in the circuit description. The
electrical characteristics are specified within the conditions given in the Electrical Characteristics
tables.


### 4.4 Thermal Resistance

Note:
This thermal data was generated in accordance with JEDEC JESD51 standards. For more
information, go to www.jedec.org.


<table>
<caption>Table 7 Thermal Resistance1)</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Thermal Characterization Parameter Junction-Top</td>
<td>YJTOP</td>
<td>–</td>
<td>0.6</td>
<td>1.1</td>
<td>K/W</td>
<td>2)</td>
<td>P_4.4.0.4</td>
</tr>
<tr>
<td>Thermal Resistance Junction-to-Case</td>
<td>RthJC</td>
<td>–</td>
<td>0.2</td>
<td>0.4</td>
<td>K/W</td>
<td>2) simulated at exposed pad</td>
<td>P_4.4.0.5</td>
</tr>
<tr>
<td>Thermal Resistance Junction to Ambient</td>
<td>RthJA</td>
<td>–</td>
<td>26</td>
<td>–</td>
<td>K/W</td>
<td>2)</td>
<td>P_4.4.0.6</td>
</tr>
</table>

1\) Not subject to production test - specified by design.

2\) According to Jedec JESD51-2,-5,-7 at natural convection on FR4 2s2p board; the Product (Chip + Package) was
simulated on a 76.2 × 114.3 × 1.5 mm board with 2 inner copper layers (2 x 70 um Cu, 2 x 35 um Cu). Where applicable
a thermal via array under the exposed pad contacted the first inner copper layer. Simulation done at TA = 105℃,
P DISSIPATION = 1 W.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="11" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 12" -->


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


<figure>

Infineon

</figure>


## General Product Characteristics


### 4.4.1 PCB Setup


<figure>
<figcaption>Figure 5 1s0p PCB Cross Section</figcaption>

70 um modeled (traces, cooling area)

1,5 mm

70 um, 5% metalization*

*: means percentual Cu metalization on each layer

PCB_Zth_1s0p.emf

</figure>


<figure>
<figcaption>Figure 6 2s2p PCB Cross Section</figcaption>

70 um modeled (traces)

1,5 mm

35 um, 90% metalization*

35 um, 90% metalization*

70 um, 5% metalization*

*: means percentual Cu metalization on each layer

PCB_Zth_2s2p.emf

</figure>


<figure>
<figcaption>Figure 7 PCB setup for thermal simulations</figcaption>

JEDEC 1sOp / 600mm2

JEDEC 1sOp / footprint
JEDEC 2s2p

PCB 1s0p + 600 mm2 cooling

PCB 2s2p / 1s0p footprint

PCB_sim_setup_TSDSO24.emf

</figure>


<figure>
<figcaption>Figure 8 Thermal vias on PCB for 2s2p PCB setup</figcaption>

Solder Pads and Vias

PCB_252p_vias_TSDS024.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="12" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 13" -->


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


<figure>

<!-- PageHeader="Infineon" -->

</figure>


## General Product Characteristics


### 4.4.2 Thermal Impedance


<figure>
<figcaption>Figure 9 Typical Thermal Impedance. PCB setup according Chapter 4.4.1</figcaption>

BTS72220-4ESx

100

10

ZthJA [K/W]

TAMBIENT = 105 ℃

1

0.1

2s2p

1sOp - 600 mm2

1sOp - 300 mm2

1s0p - footprint

0.01

0.0001

0.001

0.01

0.1

1

10

100

1000

Time [s]

</figure>


<figure>
<figcaption>Figure 10 Thermal Resistance on 1s0p PCB with various cooling surfaces</figcaption>

BTS72220-4ESx

90

1sOp - Ta = 105 ℃

80

70

RthJA [K/W]

60

50

40

30

0

100

200

300

400

500

600

Cooling area [mm2]

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="13" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 14" -->


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


<figure>

Infineon

</figure>


# Logic Pins


## 5 Logic Pins

The device has 9 digital pins to configure and control the device. They can be grouped based on their function
into input pins, SPI pins and Limp Home pin.


### 5.1 Input Pins (INn)

The input pins IN0 to IN3 activate the corresponding output channel, if the device is either in Sleep, Stand-by,
Ready or in Limp Home mode. The input circuitry is compatible with 3.3V and 5V microcontroller. The
electrical equivalent of the input circuitry is shown in Figure 11. In case the pin is not used, it must be
connected with a 10 kQ2 resistor either to GND pin or to module ground.


<figure>
<figcaption>Figure 11 Input circuitry</figcaption>

VS

IN

IDI

VS(CLAMP)

ESD

/DI

VDI (CLAMP)

VDI

GND

IGND

RGND

Input_IN_INTDIO.emf

</figure>


The logic thresholds for "low" and "high" states are defined by parameters VDI(TH) and VDI(HYS). The relationship
between these two values is shown in Figure 12. The voltage VIN needed to ensure a "high" state is always
higher than the voltage needed to ensure a "low" state.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="14" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 15" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


#### Logic Pins


<figure>
<figcaption>Figure 12 Input Threshold voltages and hysteresis</figcaption>

VDI 4

VDI(TH ),MAX

VDI(TH)

VD(HYS)

VD(TH ), MIN

t

Internal channel
activation signal

0

x
☒

1

x
☒

0

t

Input_VDITH_2.emf

</figure>


There are two ways of using the input pins in combination with the register OUT by programming bit
HWCR . COL in register HWCR (see Table 35).

· HWCR. COL = 0B: A channel is switched ON either by the according OUT . OUTn bit or by the input pin.

· HWCR. COL = 1B: A channel is switched ON by the according OUT . OUTn bit only, when the input pin is
"high". In this configuration, a PWM signal can be applied to the input pin and the channel is activated by
the SPI register OUT (see Table 35).

The default state (HWCR. COL = 0g) is the OR-combination of the input signal and the SPI-bit. In Limp Home
mode (LHI pin set to "high") the combinatorial logic is in default state to enable a channel activation via the
input pins only. Figure 13 shows the complete input switch matrix.

The logic level of the input pins can be monitored via the input status monitor. In case of a "high" level on an
input pin, the corresponding ICS . INSTn bit is set and cleared on read.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="15" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 16" -->



<figure>

<!-- PageHeader="Infineon" -->

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


##### Logic Pins


<figure>
<figcaption>Figure 13 Input Switch Matrix</figcaption>

MUX#111

OUT2

OUT1

OUT3

OUT0

PCC0

&

&

&

&

IN0

ர

OR

TINO

&

JJ

Gate Control 0

OR

IN3

ர

OR

Gate Control 3

IN 1

&

J

IN1

ர

OR

TIN2

&

J

Gate Control 1

OR

IN2

ர

OR

Gate Control 2

IN 3

&

J

COL

PCC1

LogicPins_InputMatrix_4chnoED_PCC.emf

</figure>


### 5.2 Advanced Features Pins


#### 5.2.1 SPI Pins

The serial peripheral interface (SPI) is a full duplex synchronous serial slave interface, which uses four lines:
SO, SI, SCLK and CSN. See Chapter 10 for further information.


#### 5.2.2 Limp Home Input (LHI) Pin

For activating the fail-safe state, the device features a Limp Home Input pin. When the pin is set to "high" for
a time longer than tLHI(AC), the Limp Home mode will be activated. See Chapter 6.1.7 and Chapter 6.1.8 for
further information.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="16" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 17" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Logic Pins


### 5.3 Electrical Characteristics Logic Pins

VDD = 3.0 V to 5.5 V, Vs = 6 V to 18 V, TJ = - 40 °C to +150 ℃
Typical values: VDD = 5.0 V, Vs = 13.5 V, T] = 25 ℃

Digital Input (DI) pins = IN


<table>
<caption>Table 8 Electrical Characteristics: Logic Pins - General</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Digital Input Voltage Threshold</td>
<td>V DI(TH)</td>
<td>0.8</td>
<td>1.3</td>
<td>2</td>
<td>V</td>
<td>See Figure 11 and Figure 12</td>
<td>P_5.4.0.1</td>
</tr>
<tr>
<td>Digital Input Clamping Voltage</td>
<td>DI(CLAMP1)</td>
<td>-</td>
<td>7</td>
<td>-</td>
<td>V</td>
<td>1) IDI = 1 mA See Figure 11 and Figure 12</td>
<td>P_5.4.0.2</td>
</tr>
<tr>
<td>Digital Input Clamping Voltage</td>
<td>VDI(CLAMP2)</td>
<td>6.5</td>
<td>7.5</td>
<td>8.5</td>
<td>V</td>
<td>IDI = 2 mA See Figure 11 and Figure 12</td>
<td>P_5.4.0.3</td>
</tr>
<tr>
<td>Digital Input Hysteresis</td>
<td>DI(HYS)</td>
<td>–</td>
<td>0.25</td>
<td>–</td>
<td>V</td>
<td>1) See Figure 11 and Figure 12</td>
<td>P_5.4.0.4</td>
</tr>
<tr>
<td>Digital Input Current ("high")</td>
<td>IDI(H)</td>
<td>2</td>
<td>10</td>
<td>25</td>
<td>µA</td>
<td>VDI = 2 V See Figure 11 and Figure 12</td>
<td>P_5.4.0.5</td>
</tr>
<tr>
<td>Digital Input Current ("low")</td>
<td>DI(L)</td>
<td>2</td>
<td>10</td>
<td>25</td>
<td>µA</td>
<td>VDI = 0.8 V See Figure 11 and Figure 12</td>
<td>P_5.4.0.6</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


### 5.4 Electrical Characteristics Logic Pins - Advanced Features


<table>
<caption>Table 9 Electrical Characteristics: Logic Pins - Advanced</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>SPI pins</td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
</tr>
<tr>
<td>Digital Input Voltage Threshold of Pin CSN</td>
<td>VCSN(TH)</td>
<td>0.8</td>
<td>1.3</td>
<td>2</td>
<td>V</td>
<td>–</td>
<td>P_5.5.0.1</td>
</tr>
<tr>
<td>Digital Input Voltage Threshold of Pin SCLK</td>
<td>VSCLK(TH)</td>
<td>0.8</td>
<td>1.3</td>
<td>2</td>
<td>V</td>
<td>1)</td>
<td>P_5.5.0.2</td>
</tr>
<tr>
<td>Digital Input Voltage Threshold of Pin SI</td>
<td>VSI(TH)</td>
<td>0.8</td>
<td>1.3</td>
<td>2</td>
<td>V</td>
<td>–</td>
<td>P_5.5.0.3</td>
</tr>
<tr>
<td>Digital Input Clamping Voltage of Pin CSN</td>
<td>VCSN(CLAMP1)</td>
<td>-</td>
<td>7</td>
<td>-</td>
<td>V</td>
<td>2) ICSN = 1 mA</td>
<td>P_5.5.0.4</td>
</tr>
<tr>
<td>Digital Input Clamping Voltage of Pin CSN</td>
<td>VCSN(CLAMP2)</td>
<td>6.5</td>
<td>7.5</td>
<td>8.5</td>
<td>V</td>
<td>ICSN = 2 mA</td>
<td>P_5.5.0.5</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="17" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 18" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Logic Pins


<table>
<caption>Table 9 Electrical Characteristics: Logic Pins - Advanced (continued)</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Digital Input Clamping Voltage of Pin SCLK</td>
<td>VSCLK(CLAMP1)</td>
<td>-</td>
<td>7</td>
<td>-</td>
<td>V</td>
<td>2) ISCLK = 1 mA</td>
<td>P_5.5.0.6</td>
</tr>
<tr>
<td>Digital Input Clamping Voltage of Pin SCLK</td>
<td>VSCLK(CLAMP2)</td>
<td>6.5</td>
<td>7.5</td>
<td>8.5</td>
<td>V</td>
<td>ISCLK = 2 mA</td>
<td>P_5.5.0.7</td>
</tr>
<tr>
<td>Digital Input Clamping Voltage of Pin SI</td>
<td>VSI(CLAMP1)</td>
<td>-</td>
<td>7</td>
<td>-</td>
<td>V</td>
<td>2) Isı = 1 mA</td>
<td>P_5.5.0.8</td>
</tr>
<tr>
<td>Digital Input Clamping Voltage of Pin SI</td>
<td>VSI(CLAMP2)</td>
<td>6.5</td>
<td>7.5</td>
<td>8.5</td>
<td>V</td>
<td>Isı = 2 mA</td>
<td>P_5.5.0.9</td>
</tr>
<tr>
<td>Digital Input Hysteresis of Pin CSN</td>
<td>VCSN(HYS)</td>
<td>–</td>
<td>0.25</td>
<td>–</td>
<td>V</td>
<td>2) See Figure 12</td>
<td>P_5.5.0.11</td>
</tr>
<tr>
<td>Digital Input Hysteresis of Pin SCLK</td>
<td>VSCLK(HYS)</td>
<td>–</td>
<td>0.25</td>
<td>–</td>
<td>V</td>
<td>2) See Figure 12</td>
<td>P_5.5.0.13</td>
</tr>
<tr>
<td>Digital Input Hysteresis of Pin SI</td>
<td>VSI(HYS)</td>
<td>–</td>
<td>0.25</td>
<td>–</td>
<td>V</td>
<td>2) See Figure 12</td>
<td>P_5.5.0.15</td>
</tr>
<tr>
<td>Digital Input Current ("low") of Pin CSN</td>
<td>-CSN(L)</td>
<td>2</td>
<td>10</td>
<td>25</td>
<td>µA</td>
<td>VCSN = 0.5 V</td>
<td>P_5.5.0.10</td>
</tr>
<tr>
<td>Digital Input Current ("high") of Pin CSN</td>
<td>-CSN(H)</td>
<td>2</td>
<td>10</td>
<td>25</td>
<td>µA</td>
<td>VCSN = 2.6 V</td>
<td>P_5.5.0.12</td>
</tr>
<tr>
<td>Digital Input Current ("low") of Pin SCLK</td>
<td>İSCLK(L)</td>
<td>2</td>
<td>10</td>
<td>25</td>
<td>µA</td>
<td>VSCLK = 0.5 V</td>
<td>P_5.5.0.14</td>
</tr>
<tr>
<td>Digital Input Current ("high") of Pin SCLK</td>
<td>ISCLK(H)</td>
<td>2</td>
<td>10</td>
<td>25</td>
<td>µA</td>
<td>VSCLK = 2.6 V</td>
<td>P_5.5.0.16</td>
</tr>
<tr>
<td>Digital Input Current ("low") of Pin SI</td>
<td>İSI(L)</td>
<td>2</td>
<td>10</td>
<td>25</td>
<td>µA</td>
<td>VSI = 0.5 V</td>
<td>P_5.5.0.18</td>
</tr>
<tr>
<td>Digital Input Current ("high") of Pin SI</td>
<td>ISI(H)</td>
<td>2</td>
<td>10</td>
<td>25</td>
<td>µA</td>
<td>VSI = 2.6 V</td>
<td>P_5.5.0.20</td>
</tr>
<tr>
<td>Digital Output Voltage ("low") of Pin SO</td>
<td>VSO(L)</td>
<td>0</td>
<td>–</td>
<td>0.5</td>
<td>V</td>
<td>Iso = - 0.5 mA</td>
<td>P_5.5.0.22</td>
</tr>
<tr>
<td>Digital Output Voltage ("high") of Pin SO</td>
<td>VSO(H)</td>
<td>VD - 0.5 V</td>
<td>–</td>
<td>VD</td>
<td>V</td>
<td>Iso = 0.5 mA</td>
<td>P_5.5.0.23</td>
</tr>
<tr>
<td>Output Tristate Leakage Current of Pin SO</td>
<td>ISO(OFF)</td>
<td>-1</td>
<td>–</td>
<td>1</td>
<td>µA</td>
<td>VCSN = VDD Vso = 0 V or VCSN = VDD Vso = VD</td>
<td>P_5.5.0.24</td>
</tr>
<tr>
<td colspan="8">LHI pin</td>
</tr>
<tr>
<td>Digital Input Voltage Threshold of Pin LHI</td>
<td>LHI(TH)</td>
<td>1.4</td>
<td>1.9</td>
<td>2.6</td>
<td>V</td>
<td>–</td>
<td>P_5.5.0.25</td>
</tr>
<tr>
<td>Digital Input Clamping Voltage of Pin LHI</td>
<td>VLHI(CLAMP1)</td>
<td>-</td>
<td>7</td>
<td>-</td>
<td>V</td>
<td>2) /LHI = 1 mA</td>
<td>P_5.5.0.27</td>
</tr>
<tr>
<td>Digital Input Clamping Voltage of Pin LHI</td>
<td>VLHI(CLAMP2)</td>
<td>6.5</td>
<td>7.5</td>
<td>8.5</td>
<td>V</td>
<td>/LHI = 2 mA</td>
<td>P_5.5.0.28</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="18" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 19" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Logic Pins


<table>
<caption>Table 9 Electrical Characteristics: Logic Pins - Advanced (continued)</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Digital Input Hysteresis of Pin LHI</td>
<td>LHI(HYS)</td>
<td>–</td>
<td>0.25</td>
<td>–</td>
<td>V</td>
<td>2)</td>
<td>P_5.5.0.29</td>
</tr>
<tr>
<td>Digital Input Current ("high") of Pin LHI</td>
<td>LHI(H)</td>
<td>10</td>
<td>32</td>
<td>65</td>
<td>µA</td>
<td>VLHI = 5 V VDD = 0 V</td>
<td>P_5.5.0.30</td>
</tr>
<tr>
<td>Digital Input Current ("low") of Pin LHI</td>
<td>/LHI(L)</td>
<td>10</td>
<td>24</td>
<td>45</td>
<td>µA</td>
<td>VLHI = 0.8 V VDD = 0 V</td>
<td>P_5.5.0.32</td>
</tr>
</table>

1\) Functional test only.

2\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="19" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 20" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Power Supply


## 6 Power Supply

The BTS72220-4ESA is supplied by two supply voltages:

· Power Supply Voltage (Vs)

· Digital Supply Voltage (VDD)

The Vs supply line is connected to a battery feed and used for the driving circuitry of the power stages, while
VDD is used for the SPI logic and for driving SO pin. Vs and VDD supply voltages have an undervoltage detection
circuit, which prevents the activation of the associated function in case the measured voltage is below the
undervoltage threshold. More in detail:

· An undervoltage on Vpp supply prevents SPI communication. SPI registers are reset to their default values

· An undervoltage on Vs supply switches OFF all channels, even in Limp Home mode. The channels are
enabled again as soon as Vs VS(OP)

The voltage at pin Vs is also monitored. In case of a negative voltage transient on Vs resulting in Vs < VS(TP) when
the device is out of Sleep mode, any SPI command sent by the microcontroller is not accepted (see
Chapter 6.2 and Chapter 10.5 for further information). An overview of channel behavior according to
different Vs and VDD supply voltages is shown in Table 10.


<table>
<caption>Table 10 Device capability as function of Vs and VDD1)</caption>
<tr>
<th></th>
<th>VD = VD(PO) (VDD(PO) See P_6.4.1.1)</th>
<th>VD &gt; VD(PO)</th>
</tr>
<tr>
<td rowspan="4">V≤VS(TP) (VS(TP) see P_6.4.0.5)</td>
<td>Channels are OFF</td>
<td>Channels are OFF</td>
</tr>
<tr>
<td>SPI registers reset</td>
<td>SPI registers protected</td>
</tr>
<tr>
<td>SPI communication not available (fSCLK = 0 MHZ)</td>
<td>SPI communication available2) (fSCLK = 5 MHZ)</td>
</tr>
<tr>
<td>Limp Home mode not available</td>
<td>Limp Home mode not available</td>
</tr>
<tr>
<td rowspan="4">VS(TP) &lt;Vs = VS(UV) (Vs(Uv) see P_6.4.0.1)</td>
<td>Channels are OFF</td>
<td>Channels are OFF</td>
</tr>
<tr>
<td>SPI registers reset</td>
<td>SPI registers available</td>
</tr>
<tr>
<td>SPI communication not available (fSCLK = 0 MHZ)</td>
<td>SPI communication available (fSCLK = 5 MHZ)</td>
</tr>
<tr>
<td>Limp Home mode available (channels are OFF)</td>
<td>Limp Home mode available (channels are OFF)</td>
</tr>
<tr>
<td rowspan="4">VS &gt; VS(UV)3)</td>
<td>Channels cannot be controlled by SPI</td>
<td>Channels can be controlled by SPI</td>
</tr>
<tr>
<td>SPI registers reset</td>
<td>SPI registers available</td>
</tr>
<tr>
<td>SPI communication not available (fSCLK = 0 MHZ)</td>
<td>SPI communication available (fSCLK = 5 MHZ)</td>
</tr>
<tr>
<td>Limp Home mode available</td>
<td>Limp Home mode available</td>
</tr>
</table>

1\) Valid after a successful supply voltage ramp-up.

2\) Write commands are ignored. Furthermore the device responds with STDDIAG only.

3\) The undervoltage condition on VS supply must be considered. See Chapter 6.2.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="20" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 21" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->
<!-- PageHeader="Power Supply" -->


### 6.1 Operation Modes

BTS72220-4ESA has the following operation modes:

· Sleep mode

· Active mode

· Stand-by mode

· Ready mode

· Limp Home mode

· Limp Home Active mode

The transition between operation modes is determined according to these variables:

· Digital supply level (VDD)

· Logic level at INn pins

· Logic level at LHI pin

· Current sense multiplexer state (DCR . MUX)

· Output register state (OUT . OUTn)

· Configuration registers state

The state diagram including the possible transitions is shown in Figure 14. The behavior of BTS72220-4ESA as
well as some parameters may change in dependence from the operation mode of the device. Furthermore,
due to the undervoltage detection circuitry which monitors Vs supply voltage, some changes within the same
operation mode can be seen accordingly.

There are five parameters describing each operation mode of BTS72220-4ESA:

· Status of the output channels

· Status of SPI registers

· Status of SPI communication

· Current consumption at VS pin (measured by lys in Sleep mode, IGND in all other operative modes)

· Current consumption at VDD pin (/VDD)

Table 11 shows the correlation between operation modes, Vs and VDD supply voltages, and the state of the
most important functions (channel status, SPI communication and SPI registers).

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="21" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 22" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Power Supply


<figure>
<figcaption>Figure 14 Operation Mode state diagram</figcaption>

LHI = "high"

Unsupplied

Power-up

Stand-by

DCR. MUX = 111. or SPI_Reset

LHI = "low"

Sleep

DCR.MUX # 111g

LHI = "high"

OUT.OUTn = 1B
or INn = "high"

INn = "low" &
OUT.OUTn = 03

INn="low" or INn= "low" & SPI_Reset

OUT.OUTn = 0g or
SPI_Reset

INṋ= "high"

Limp Home

OUT.OUTn = 1B

DCR. MUX # 111_ or INn = "high"

Active

DCR - MUX - 111; &INn = "low"

Ready

LHI = "high"

INn = "low"

LHI = "high" & INn = "low"

INn = "high"

LHI = "high" & INn = "high"

Limp Home
Active

LHI = "low" & INn = "high"

Note: SPIbits which are not stated are considered to have the default value or are unchanged compared to the previous state. Supply voltages are
considered to be in operative range if not specified different. SPI_Reset is performed if VDD < VDD(PO) Or HWCR. RST = 1}
Dashed lines indicate transitions between modes which should not be used for normal operation.

PowerSupply_OpModes.emf

</figure>


<table>
<caption>Table 11 Device function in relation to operation modes, VDD and Vs voltages</caption>
<tr>
<th>Operative Mode</th>
<th>Function</th>
<th>VS SVS(TP)</th>
<th>VS(TP) ≤ V≤ VS(Uv)</th>
<th>Vs&gt;Vs(UV)</th>
</tr>
<tr>
<td rowspan="3">Sleep</td>
<td>Channels</td>
<td>OFF</td>
<td>OFF</td>
<td>OFF</td>
</tr>
<tr>
<td>SPI registers</td>
<td>available1)</td>
<td>available1)</td>
<td>available1)</td>
</tr>
<tr>
<td>SPI comm.</td>
<td>available1)</td>
<td>available1)</td>
<td>available1)</td>
</tr>
<tr>
<td rowspan="3">Stand-by</td>
<td>Channels</td>
<td>OFF</td>
<td>OFF</td>
<td>OFF</td>
</tr>
<tr>
<td>SPI registers</td>
<td>protected1)</td>
<td>available1)</td>
<td>available1)</td>
</tr>
<tr>
<td>SPI comm.</td>
<td>all commands rejected1)</td>
<td>available1)</td>
<td>available1)</td>
</tr>
<tr>
<td rowspan="3">Ready</td>
<td>Channels</td>
<td>OFF</td>
<td>OFF</td>
<td>OFF</td>
</tr>
<tr>
<td>SPI registers</td>
<td>protected1)</td>
<td>available1)</td>
<td>available1)</td>
</tr>
<tr>
<td>SPI comm.</td>
<td>all commands rejected1)</td>
<td>available1)</td>
<td>available1)</td>
</tr>
<tr>
<td rowspan="3">Active</td>
<td>Channels</td>
<td>OFF</td>
<td>OFF</td>
<td>follow SPI and/or Input pins</td>
</tr>
<tr>
<td>SPI registers</td>
<td>protected1)</td>
<td>available1)</td>
<td>available1)</td>
</tr>
<tr>
<td>SPI comm.</td>
<td>all commands rejected1)</td>
<td>available1)</td>
<td>available1)</td>
</tr>
<tr>
<td rowspan="3">Limp Home / Limp Home Active</td>
<td>Channels</td>
<td>OFF</td>
<td>OFF</td>
<td>follow Input pins</td>
</tr>
<tr>
<td>SPI registers</td>
<td>protected1)</td>
<td>reset (Diagnosis available)1)</td>
<td>reset (Diagnosis available)1)</td>
</tr>
<tr>
<td>SPI comm.</td>
<td>all commands rejected1)2)</td>
<td>read-only1)</td>
<td>read-only1)</td>
</tr>
</table>

1\) In case VDD > VDD(PO) otherwise not available or in reset.

2\) In case all input pins are set to "low", SPI communication is in read-only mode.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="22" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 23" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->
<!-- PageHeader="Power Supply" -->


#### 6.1.1 Unsupplied

In this state, the device is either unsupplied (no voltage applied to VS pin and VDD pin) or the supply voltages
are both below the corresponding undervoltage threshold.


#### 6.1.2 Power-up

The Power-up condition is entered when one of the supply voltages (Vs or VDD) is applied to the device. Both
supplies are rising until they are above the undervoltage thresholds Vs(op) and VDD(PO) therefore the internal
Power-On signals are set. The SPI interface can be accessed after wake up time twu(PO)-


#### 6.1.3 Sleep mode

The device is in Sleep mode when all Digital Input pins (INn, LHI) are set to "low" and DCR. MUX is still set to
111B. When BTS72220-4ESA is in Sleep mode, all outputs are OFF. The SPI registers can be programmed if VDD
\> VDD(PO). The current consumption is minimum (see parameter lys(SLEEP). No Overtemperature or Overload
protection mechanism is active when the device is in Sleep mode. The circuitry that monitors Vs versus Vs(Uv)
and Vs versus VS(TP) is disabled. This allows the programming of the registers even if Vs < VS(TP).


#### 6.1.4 Stand-by mode

The device is in Stand-by mode when DCR . MUX # 111B and no command to switch ON a channel was received
(either via SPI or via Input pins). All channels are OFF but the internal supply circuitry is working and therefore
the device current consumption is increased. A command to switch ON one or more outputs is accepted and
executed, bringing the device into Active mode. SPI communication is possible.


#### 6.1.5 Ready mode

In Ready mode, one or more outputs received a command to switch ON (either via SPI or via Input pins if
HWCR. COL = 1B). Nevertheless, all outputs are OFF because of DCR. MUX bits still set to 111B. It is necessary
to change the value of those bits to bring the device into Active mode and switch ON the channels.

Note:
Since OUT register is blanked with DCR . MUX = 111 B it is not possible to enter Active mode when
HWCR . COL bit is set to 1 B.


#### 6.1.6 Active mode

Active mode is the normal operation mode of BTS72220-4ESA when no Limp Home condition is set and one or
more outputs are switched ON. Device current consumption is specified by parameter I GND(ACTIVE). An
undervoltage condition on Vpp supply voltage brings the device into Sleep mode in case all Input pins are set
to "low".


#### 6.1.7 Limp Home mode

The device enters Limp Home mode when LHI pin is set to "high" for t > tLHI(AC). SPI registers are reset to the
default values when Limp Home mode is entered. The corresponding bit in the standard diagnosis
(STDDIAG. LHI) will be set to 1B once the LHI pin is set to "high" and latched until next STDDIAG
transmission. See Figure 15 for further information. SPI registers are available for read access. ERRDIAG,
STDDIAG, WRNDIAG and ICS can be used for diagnosis in Limp Home.

When the device is in transient protection (Vs VS(TP) and the LHI pin is set to "high", the STDDIAG. LHI bit
will be set but the device will not change its state to Limp Home mode. Furthermore STDDIAG . VSMON and
STDDIAG. TER bits will be set to report the battery transient protection.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="23" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 24" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Power Supply


<figure>
<figcaption>Figure 15 Limp Home Activation as function of Vs</figcaption>

Vs

VS(TP)

t

LHI
pin

t<tLHI(AC)

t

STDDIAG
. LHI

Read STDDIAG

Read STDDIAG

Read STDDIAG

t

SPI

İLHI(AC).

İLHI(AC ).

İLHI(AC),

comm.

available

read-only

available

all command rejected

registers

available

reset

available

protected

Note: Device out of Sleep mode when SPI comm. „available“

t

Power Supply_Limp HomeActive.emf

</figure>


#### 6.1.8 Limp Home Active mode

Limp Home Active mode is entered when the device is in Limp Home mode and one of the IN pins is set to
"high". Overload, Overtemperature and Overvoltage protections are active. Since SPI registers cannot be
written current sensing is not available.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="24" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 25" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Power Supply


#### 6.1.9 Definition of Operation modes transition times

The channel turn-ON time is as defined by parameter tON when BTS72220-4ESA is in Active mode or in Limp
Home mode. In all other cases, it is necessary to add the transition time required to reach one of the two
aforementioned operation modes (as shown in Figure 16).


<figure>
<figcaption>Figure 16 Transition Time diagram</figcaption>

İLHI(AC)

Unsupplied

twU(PO)

tTRANS2SLP

Stand-by

Sleep

[HI(AC) + +TRANS2SLP

tTRANS2STBY

İLHI(AC) + +TRANS2STBY

ton

ton + +TRANS2STBY

1 SPI frame

1 SPI frame

tOF

tOFF + +TRANS2SLP

Limp Home

tow + tTRANS2STBY

TOFF + + TRANS2SLP

Ready

tLHI(AC) + TRANS2STBY

Active

tOFF + +LHI(AC)

O

tOFF

İLHI(AC)

İLHI(AC)

Limp Home
Active

Note: Dashed lines indicate transition timings between modes which should not be used for normal operation.

PowerSupply_OpModes_Timings.emf

</figure>


### 6.2 Undervoltage on Vs

Between Vs(OP) and Vs(uv) the undervoltage mechanism is triggered. If the device is operative (in Active or Limp
Home Active mode) and the supply voltage drops below the undervoltage threshold Vs(uv), the internal logic
switches OFF the output channels. When the device is either in Stand-by, Active or Limp Home mode the bit
STDDIAG. VSMON is set and latched until readout. When the state is changed from Sleep to any other state,
a delay of t ≥ tTRANS2STBY has to be considered until STDDIAG. VSMON is valid.

As soon as the supply voltage Vs is above the operative threshold Vs(op), the channels having the corresponding
input pin set to "high" or the bit in the OUT register set to 1B are switched ON again. The restart is delayed with
a time tDELAY(UV) which protects the device in case the undervoltage condition is caused by a short circuit event
(according to AEC-Q100-012), as shown in Figure 17.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="25" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 26" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Power Supply


<figure>
<figcaption>Figure 17 Vs undervoltage behavior</figcaption>

Vs

VS(OP)

VS(UV)

VS(HY S)

VS(TP)

t

tDELAY(UV)

VOUT

t

STDDIAG.
VSMON

Read STDDIAG +

Read STDDIAG

t

STDDIAG.
TER

Read STDDIAG +

Read STDDIAG +

t

Opera tion
Mode

Stand-by

Active

Sleep

Ready

Active

t

Power Supply_UVRVS.emf

</figure>


## 6.3 Reset Condition

One of the following conditions reset the SPI registers to their default value:

· VDD is not present or below the undervoltage threshold VDD(PO)

\- SPI registers will be reset to their default values (in the first communication after reset the
STDDIAG. TER will be set to 1B).

\- Restart counters will not be reset if Vs is available or LHI is "high".

· LHI pin is set to "high" for t > tLHI(AC) and Vs > VS(TP)

\- Configuration registers will be reset to their default values. ERRDIAG and WRNDIAG will be reset.

\- Restart counters will be reset.

· Reset command (HWCR . RST = 1B) is executed and Vs > VS(TP)

\- Configuration registers will be reset to their default values. ERRDIAG, WRNDIAG and STDDIAG will not
be reset.

\- Restart counters will not be reset.

In case all Input pins are set to "low" after any reset condition, all channels are switched OFF.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="26" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 27" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Power Supply


### 6.4 Electrical Characteristics Power Supply

VDD = 3.0 V to 5.5 V, Vs = 6 V to 18 V, TJ = - 40 ℃ to +150 ℃
Typical values: VDD = 5.0 V, Vs = 13.5 V, T] =25 ℃

Typical resistive loads connected to the outputs for testing (unless otherwise specified):
5.5 mΩ: Ri = 2.4Ω

13.5 mΩ: Rt=3.4Ω


<table>
<caption>Table 12 Electrical Characteristics: Power Supply - General</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td colspan="6">VS pin</td>
<td colspan="2"></td>
</tr>
<tr>
<td>Power Supply Undervoltage Shutdown</td>
<td>VS(UV)</td>
<td>1.8</td>
<td>2.3</td>
<td>3.1</td>
<td>V</td>
<td>Vs decreasing IN = "high" or OUT . OUTn = 1B From Vps ≤ 0.5 Vto VDS = Vs See Figure 17</td>
<td>P_6.4.0.1</td>
</tr>
<tr>
<td>Power Supply Minimum Operating Voltage</td>
<td>VS(OP)</td>
<td>2.0</td>
<td>3.0</td>
<td>4.1</td>
<td>V</td>
<td>Vs increasing IN = "high"or OUT . OUTn = 1B From VDs = Vs to VDS ≤ 0.5 V See Figure 17</td>
<td>P_6.4.0.3</td>
</tr>
<tr>
<td>Power Supply Voltage Threshold for Battery Transients Protection</td>
<td>VS(TP)</td>
<td>0.6</td>
<td>1.0</td>
<td>1.8</td>
<td>V</td>
<td>Vs decreasing STDDIAG. VSMON = 1B STDDIAG . TER = 1B DCR. MUX #111B See Figure 17</td>
<td>P_6.4.0.5</td>
</tr>
<tr>
<td>Power Supply Undervoltage Shutdown Hysteresis</td>
<td>VS(HYS)</td>
<td>–</td>
<td>0.7</td>
<td>–</td>
<td>V</td>
<td>1) VS(OP) - VS(UV) See Figure 17</td>
<td>P_6.4.0.6</td>
</tr>
<tr>
<td>Power Supply Undervoltage Recovery Time</td>
<td>tDELAY(UV)</td>
<td>2.5</td>
<td>4</td>
<td>5.5</td>
<td>ms</td>
<td>1) dVs/dt ≤0.5V/us VS≥0V See Figure 17</td>
<td>P_6.4.0.10</td>
</tr>
<tr>
<td>Breakdown Voltage between GND and VS Pins in Reverse Battery</td>
<td>-VS(REV)</td>
<td>16</td>
<td>–</td>
<td>30</td>
<td>V</td>
<td>1) IGND(REV) = 14 mA TJ=150 ℃</td>
<td>P_6.4.0.9</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="27" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 28" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Power Supply


#### 6.4.1 Electrical Characteristics Power Supply - SPOC™


<table>
<caption>Table 13 Electrical Characteristics: Power Supply - SPOC™</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td colspan="2">VDD pin</td>
<td></td>
<td colspan="2"></td>
<td></td>
<td></td>
<td></td>
</tr>
<tr>
<td>Digital Supply Operating Voltage</td>
<td>VDD(OP)</td>
<td>2.45</td>
<td>4.3</td>
<td>5.5</td>
<td>V</td>
<td>1) fSCLK = 5 MHZ</td>
<td>P_6.4.1.1</td>
</tr>
<tr>
<td>Digital Supply Power-On Reset Threshold Voltage</td>
<td>VDD(PO)</td>
<td>1.4</td>
<td>1.9</td>
<td>2.3</td>
<td>V ☒</td>
<td>1) VDD increasing</td>
<td>P_6.4.1.9</td>
</tr>
<tr>
<td>Digital Supply Undervoltage Shutdown</td>
<td>VD(UV)</td>
<td>1.3</td>
<td>1.8</td>
<td>2.2</td>
<td>V</td>
<td>VDD decreasing OUT . OUTn = 1B From Vps ≤ 0.5 V to VDS = Vs</td>
<td>P_6.4.1.2</td>
</tr>
<tr>
<td>Digital Supply Undervoltage Shutdown Hysteresis</td>
<td>VD(HYS)</td>
<td>–</td>
<td>0.1</td>
<td>–</td>
<td>V ☒</td>
<td>1)</td>
<td>P_6.4.1.3</td>
</tr>
<tr>
<td>Digital Supply Clamping Voltage</td>
<td>VDD(CLAMP1)</td>
<td>–</td>
<td>6.5</td>
<td>–</td>
<td>V ☒</td>
<td>1) IDD = 1 mA</td>
<td>P_6.4.1.11</td>
</tr>
<tr>
<td>Digital Supply Clamping Voltage</td>
<td>VDD(CLAMP2)</td>
<td>6</td>
<td>7</td>
<td>8</td>
<td>V</td>
<td>IDD = 20 mA</td>
<td>P_6.4.1.12</td>
</tr>
<tr>
<td>Power-On Wake Up Time</td>
<td>twu(PO)</td>
<td>–</td>
<td>10</td>
<td>30</td>
<td>μς</td>
<td>1)</td>
<td>P_6.4.1.13</td>
</tr>
<tr>
<td>Transition Time to Stand-by Mode</td>
<td>tTRANS2STBY</td>
<td>5</td>
<td>10</td>
<td>30</td>
<td>μς</td>
<td>1)</td>
<td>P_6.4.1.4</td>
</tr>
<tr>
<td>Transition Time to Sleep Mode</td>
<td>+TRANS2SLP</td>
<td>1</td>
<td>5</td>
<td>60</td>
<td>μς</td>
<td>1)2)</td>
<td>P_6.4.1.5</td>
</tr>
<tr>
<td>Limp Home Acknowledgement Time</td>
<td>ELHI(AC)</td>
<td>10</td>
<td>20</td>
<td>40</td>
<td>μς</td>
<td>1)</td>
<td>P_6.4.1.6</td>
</tr>
</table>

1\) Not subject to production test - specified by design.

2\) If output channel enters inductive clamping, clamping time has to be added.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="28" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 29" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Power Supply


## 6.5 Electrical Characteristics Power Supply - Product Specific

VDD = 3.0 V to 5.5 V, Vs = 6 V to 18 V, TJ =- 40 °C to +150 ℃

Typical values: VDD = 5.0 V, Vs = 13.5 V, TJ = 25 ℃

Typical resistive loads connected to the outputs for testing (unless otherwise specified):
5.5 mΩ: R1 = 2.4Ω

13.5 mΩ: Rt = 3.4Ω


### 6.5.1 BTS72220-4ESA


<table>
<caption>Table 14 Electrical Characteristics: Power Supply BTS72220-4ESA</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Digital Supply Current Consumption in Normal Operation</td>
<td>/DD</td>
<td>–</td>
<td>80</td>
<td>200</td>
<td>µA</td>
<td>fSCLK = 0 MHZ V=&gt;VS(UV) VCSN = VDD = 5 V DCR . MUX # 111B</td>
<td>P_6.5.30.1</td>
</tr>
<tr>
<td>Digital Supply Current Consumption in Normal Operation during SPI Traffic (Average)</td>
<td>ID(ACTIVE)</td>
<td>–</td>
<td>2.5</td>
<td>–</td>
<td>mA</td>
<td>1)2) fSCLK = 5 MHZ Vs&gt;VS(UV) VD = 5 V VCSN = 0 V CL(SO) = 50 pF DCR . MUX # 111B</td>
<td>P_6.5.30.2</td>
</tr>
<tr>
<td>Digital Supply Current Consumption in Sleep Mode</td>
<td>IDD(SLEEP)</td>
<td>–</td>
<td>17</td>
<td>50</td>
<td>µA</td>
<td>fSCLK = 0 MHZ V=&gt;VS(UV) VCSN = VDD = 5 V DCR . MUX = 111B</td>
<td>P_6.5.30.3</td>
</tr>
<tr>
<td>Digital Supply Current Consumption in Sleep Mode</td>
<td>I DD(SLEEP)</td>
<td>–</td>
<td>17</td>
<td>35</td>
<td>HA</td>
<td>fSCLK = 0 MHZ V=&gt;VS(UV) VCSN = VDD = 5 V DCR . MUX = 111B TJ ≤ 85℃</td>
<td>P_6.5.30.12</td>
</tr>
<tr>
<td>Power Supply Current Consumption in Sleep Mode with Loads at TJ ≤ 85 ℃</td>
<td>IVS(SLEEP)_85</td>
<td>–</td>
<td>0.05</td>
<td>1.3</td>
<td>µA</td>
<td>2)3) Vs = 18 V VOUT = 0 V INx = "low" TJ ≤85℃</td>
<td>P_6.5.30.4</td>
</tr>
<tr>
<td>Power Supply Current Consumption in Sleep Mode with Loads at T ] = 150 ℃</td>
<td>IVS(SLEEP)_150</td>
<td>-</td>
<td>2</td>
<td>100</td>
<td>µA</td>
<td>Vs = 18 V VOUT = 0 V INx = "low" TJ=150 ℃</td>
<td>P_6.5.30.5</td>
</tr>
<tr>
<td>Operating Current in Active Mode (all Channels ON)</td>
<td>IGND(ACTIVE)</td>
<td>–</td>
<td>5</td>
<td>7</td>
<td>mA</td>
<td>Vs = 18 V VDD = 5V INx = “high" or OUT . OUTn = 1B</td>
<td>P_6.5.30.6</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="29" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 30" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Power Supply


<table>
<caption>Table 14 Electrical Characteristics: Power Supply BTS72220-4ESA (continued)</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Operating Current in Ready Mode</td>
<td>GND(READY)</td>
<td>–</td>
<td>80</td>
<td>200</td>
<td>HA</td>
<td>Vs = 18 V VCSN = VDD = 5 V ÉSCLK = 0 MHZ DCR . MUX = 111B OUT . OUTn = 1B</td>
<td>P_6.5.30.8</td>
</tr>
<tr>
<td>Operating Current in Stand- by Mode</td>
<td>GND(STBY)</td>
<td>–</td>
<td>1.25</td>
<td>2</td>
<td>mA</td>
<td>Vs = 18 V VDD = 5 V DCR . MUX # 111B</td>
<td>P_6.5.30.9</td>
</tr>
</table>

1\) Test pattern shifted-in on SI: 0101010101010101 and 1010101010101010.

2\) Not subject to production test - specified by design.

3\) If VD < VD(PO), LHI = "low" and any restart counter > 0, 1GND(STBY) has to be considered.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="30" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 31" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Power Stages


## 7 Power Stages

The high-side power stages are built using a N-channel vertical Power MOSFET with charge pump.


### 7.1 Output ON-State Resistance

The ON-state resistance RDS(ON) depends mainly on junction temperature TJ. Figure 18 shows the variation of
RDS(ON) across the whole T, range. The value "2" on the y-axis corresponds to the maximum RDS(ON) measured
at TJ = 150 ℃.


<figure>
<figcaption>Figure 18 RDS(ON) variation factor</figcaption>

RDS(ON) variation over T,

2.20

Reference value:

2.00

"2"=R
DS(ON),MAX@150 ℃

1.80

1.60

RDS(ON) variation factor

1.40

1.20

1.00

0.80

0.60

0.40

0.20

Typical

0.00

40

-30

-20

-10

0

10

20

30

40

50

60

70

80

90

100

110

120

130

140

150

160

Junction Temperature (℃)

</figure>


The behavior in Reverse Polarity is described in Chapter 8.4.1.


### 7.2 Switching loads


#### 7.2.1 Switching Resistive Loads

When switching resistive loads, the switching times and slew rates shown in Figure 19 can be considered. The
switch energy values EON and EOFF are proportional to load resistance and times ton and tOFF.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="31" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 32" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


##### Power Stages


<figure>
<figcaption>Figure 19 Switching a Resistive Load</figcaption>

IN
OUT . OUTn
VIN(TH)

1
VIN(HYS)

t

VOUT

90% of Vs

ton

tOFF(DELAY)

70% of Vs

70% of Vs

(dV/dt)ON

-(dV/dt)OFF

30% of Vs

30% of Vs

10% of Vs

tON(DELAY)

tOFF

t

POMOS

EON

EOFF

t

</figure>


#### 7.2.2 Switching Inductive Loads

When switching OFF inductive loads with high-side switches, the voltage Vour drops below ground potential,
because the inductance intends to continue driving the current. To prevent the destruction of the device due
to overvoltage, a voltage clamp mechanism is implemented. The clamping structure limits the negative
output voltage so that VDs = VDS(CLAMP). Figure 20 shows a concept drawing of the implementation. The
clamping structure protects the device in all operation modes listed in Chapter 6.1.


<figure>
<figcaption>Figure 20 Output Clamp concept</figcaption>

Vs

High-side
Channel

VS

VDS

VSIS(CLAMP)

VDS(CLAMP)

IS

IL

VS(CLAMP)

OUTn

VOUTη

RSENSE

GND

L,

RL

RGND

PowerStage_Clamp_INTDIO.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="32" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 33" -->


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


<figure>

Infineon

</figure>


##### Power Stages

During demagnetization of inductive loads, energy has to be dissipated in BTS72220-4ESA. The energy can be
calculated with Equation (7.1):

E = V
DS(CLAMP)
⋅

[
Vs - VDS(CLAMP)
RL

ln
⋅
–
æ
è
1
VS - VDS(CLAMP)
ö
+

RL . IL

⋅
L
(7.1)

The maximum energy, therefore the maximum inductance for a given current, is limited by the thermal design
of the component.


#### 7.2.3 Output Voltage Limitation

To increase the current sense accuracy, Vps voltage is monitored. When the output current /1 decreases while
the channel is diagnosed (channel selected via DCR. MUX - see Figure 21) bringing Vps equal or lower than
VDS(SLC), the output DMOS gate is partially discharged. This increases the output resistance so that VDs = VDS(SLC)
even for very small output currents. The Vps increase allows the current sensing circuitry to work more
efficiently, providing better kILIs accuracy for output current in the low range.


<figure>
<figcaption>Figure 21 Output Voltage Limitation activation during diagnosis</figcaption>

IN /
OUT. OUTn

t

CS

DCR. MUX

110

000

110

t

IL

t

VDS

tsIS(ON)

tsIS(OFF)

Vs

VDS(SLC)

t

PowerStage_GBR_diag.emf

</figure>


#### 7.2.4 Switching Capacitive Loads

When switching ON a capacitive load, the capacitance is causing a high inrush current. The current is
depending on the value of the capacitance, the ESR, the impedance of the system and the slew rate of the
driver. To improve the load driving capability, BTS72220-4ESA offers a slew rate control feature. When the slew
rate bit SRC . SRCn is set, the slew rate of the respective channel is reduced to the half (see Chapter 7.4.1).

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="33" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 34" -->


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


<figure>

<!-- PageHeader="Infineon" -->

</figure>


# Power Stages


## 7.3 Advanced Switching Characteristics


### 7.3.1 Inverse Current behavior

When VOUT > Vs, a current /INy flows into the power output transistor (see Figure 22). This condition is known
as "Inverse Current".

If the channel is in OFF state, the current flows through the intrinsic body diode generating high power losses
therefore an increase of overall device temperature. This may lead to a switch OFF of unaffected channels due
to Overtemperature. If the channel is in ON state, RDS(INV) can be expected and power dissipation in the output
stage is comparable to normal operation in RDS(ON)·

During Inverse Current condition, the channel remains in ON or OFF state as long as /INV </L(INV).
With InverseON, it is possible to switch ON the channel during Inverse Current condition as long as /INV < IL(INV)
(see Figure 23).


<figure>
<figcaption>Figure 22 Inverse Current Circuitry</figcaption>

VBAT

Vs

Gate
Driver

Device
Logic

INV
Comp.

/INV

VINV = VOUT> VS

OUT

GND

RGND

PowerStage_InvCurr_INTDIO.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="34" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 35" -->


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


<figure>

Infineon

</figure>


Power Stages


<figure>
<figcaption>Figure 23 InverseON - Channel behavior in case of applied Inverse Current</figcaption>

IN

CASE 1 : Switch is ON

IN

CASE 2 : Switch is OFF

ON

OFF

t

t

IL

L

NORMAL

NORMAL

NORMAL

NORMAL

t

t

INVERSE

INVERSE

DMOS state

DMOS state

ON

OFF

t

t

CASE 3 : Switch ON into Inverse Current

CASE 4 : Switch OFF into Inverse Current

IN

IN

OFF

ON

ON

OFF

t

t

L

IL

NORMAL

NORMAL

NORMAL

NORMAL

t

INVERSE

t

INVERSE

DMOS state

DMOS state

OFF

ON

ON

OFF

t

t

PowerStage_InvCurr_INVON.emf

</figure>

Note:
No protection mechanism like Overtemperature or Overload protection is active during applied
Inverse Currents.


### 7.3.2 Switching Channels in Parallel

When switching channels in parallel to drive a single load it may happen that the two channels switch OFF
asynchronously in case of a fault condition which brings additional stress to the channel that switches OFF
last. In order to avoid this condition, it is possible to synchronize the protection of two channels when used in
parallel. There are 2 bits in the SPI (PCS . PCCn), which allow to synchronize channels 0&3 and 1&2. When the
corresponding PCS . PCCn bit is set, the switch-OFF and restart of the channels are synchronized and the
current trip levels will be reduced to /L(OVL3). In case the current trip level for one channel is set to the low level
(OCR. OCTn = 1B), the current for both channels will be reduced to /L(OVL2). Since the restart counters of the
channels in parallel are synchronized, both channels will latch-OFF as soon one counter has reached
nRESTART(CR). Due to this reason it is recommended to clear counters before switching channels in parallel. In
case the slew rate adjustment for one channels is used, (SRC . SRCn = 1B), both channels operating in parallel
mode will use the adjusted slew rate. When channels are switched in parallel (PCS . PCCn = 1B), the Output
Voltage Drop Limitation at Small Load Currents is disabled. Therefore the current sense ratio specifications at
lower currents are not valid. See Chapter 9.7 for further information. To improve current sense accuracy in
parallel channel operation, parallel mode has to be deactivated (PCS . PCCn = 0B). Since the current sense of
the two channels used in parallel is not synchronized, the total current has to be calculated out of the current
sense reading of each single channel. Unless otherwise specified parameter deviations are possible when
parallel mode is activated.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="35" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 36" -->


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


<figure>

Infineon

</figure>


# Power Stages

When two channels are used in parallel, the total current capability /L(NOM) is doubled. It has to be ensured that
the outputs used in parallel mode are connected together with a symmetric and low impedance connection
either on the PCB or in the wire harness.


## 7.3.3 Cross Current robustness with H-Bridge configuration

When BTS72220-4ESA is used as high-side switch e.g. in a bridge configuration (therefore paired with a low-
side switch as shown in Figure 24), the maximum slew rate applied to the output by the low-side switch must
be lower than | dVOUT / dt |. Otherwise the output stage may turn ON in linear mode (not in RDS(ON)) while the
low-side switch is commutating. This creates an unprotected overheating for the DMOS due to the cross-
conduction current.


<figure>
<figcaption>Figure 24 High-Side switch used in Bridge configuration</figcaption>

VBAT

R/L cable

VS

T

T

ON (DC)

INx

INy

OFF

OUTx

OUTy

| dVour / dt |

Current through Motor

Cross
Current

M

ON (PWM)

OFF

Power Stage_Passive Slew_SPOC.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="36" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 37" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Power Stages


## 7.4 Electrical Characteristics Power Stages

VDD = 3.0 V to 5.5 V, Vs = 6 V to 18 V, TJ = - 40 °C to +150 ℃
Typical values: VDD = 5.0 V, Vs = 13.5 V, T ] = 25 ℃

Typical resistive loads connected to the outputs for testing (unless otherwise specified):
5.5 mΩ: Ri = 2.4Ω

13.5 mΩ: Rt= 3.4Ω


<table>
<caption>Table 15 Electrical Characteristics: Power Stages - General</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Voltages</td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
</tr>
<tr>
<td>Drain to Source Clamping Voltage at TJ = - 40 ℃</td>
<td>VDS(CLAMP) _- 40</td>
<td>33</td>
<td>36.5</td>
<td>42</td>
<td>V</td>
<td>/L = 5 mA TJ =- 40°C See Figure 20</td>
<td>P_7.4.0.1</td>
</tr>
<tr>
<td>Drain to Source Clamping Voltage at TJ ≥ 25 ℃</td>
<td>VDS(CLAMP)_25</td>
<td>35</td>
<td>38</td>
<td>44</td>
<td>V</td>
<td>1) /L = 5 mA TJ ≥25°C See Figure 20</td>
<td>P_7.4.0.2</td>
</tr>
</table>

1\) Tested at TJ = 150℃.


### 7.4.1 Electrical Characteristics Power Stages - SPOC™


<table>
<caption>Table 16 Electrical Characteristics: Power Stages - SPOC™</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Timings</td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
</tr>
<tr>
<td>Switch-ON Delay</td>
<td>tON(DELAY)</td>
<td>10</td>
<td>30</td>
<td>60</td>
<td>μς</td>
<td>Vs = 13.5 V VOUT = 10% Vs PCS . PCCn = 0B</td>
<td>P_7.4.2.1</td>
</tr>
<tr>
<td>Switch-ON Delay (parallel mode)</td>
<td>ŁON(DELAY)</td>
<td>10</td>
<td>40</td>
<td>80</td>
<td>μς</td>
<td>2) Vs = 13.5 V VOUT = 10% VS PCS . PCCn = 1B</td>
<td>P_7.4.2.16</td>
</tr>
<tr>
<td>Switch-OFF Delay</td>
<td>tOFF(DELAY)</td>
<td>10</td>
<td>30</td>
<td>60</td>
<td>μς</td>
<td>Vs = 13.5 V VOUT = 90% VS</td>
<td>P_7.4.2.2</td>
</tr>
<tr>
<td>Switch-ON Time</td>
<td>ton</td>
<td>20</td>
<td>55</td>
<td>100</td>
<td>μς</td>
<td>Vs = 13.5 V VOUT = 90% VS SRC . SRCn = 0B PCS . PCCn = 0B</td>
<td>P_7.4.2.3</td>
</tr>
<tr>
<td>Switch-ON Time (parallel mode)</td>
<td>ton</td>
<td>20</td>
<td>70</td>
<td>125</td>
<td>μς</td>
<td>2) Vs = 13.5 V VOUT = 90% VS SRC . SRCn = 0B PCS . PCCn = 1B</td>
<td>P_7.4.2.20</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="37" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 38" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Power Stages


<table>
<caption>Table 16 Electrical Characteristics: Power Stages - SPOC™ (continued)</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Switch-ON Time</td>
<td>tON</td>
<td>30</td>
<td>75</td>
<td>150</td>
<td>μς</td>
<td>Vs = 13.5 V VOUT = 90% VS SRC . SRCn = 1B</td>
<td>P_7.4.2.4</td>
</tr>
<tr>
<td>Switch-OFF Time</td>
<td>tOFF</td>
<td>20</td>
<td>55</td>
<td>100</td>
<td>μς</td>
<td>Vs = 13.5 V VOUT = 10% VS SRC . SRCn = 0B</td>
<td>P_7.4.2.6</td>
</tr>
<tr>
<td>Switch-OFF Time</td>
<td>tOFF</td>
<td>30</td>
<td>75</td>
<td>150</td>
<td>μς</td>
<td>Vs = 13.5 V VOUT = 10% Vs SRC . SRCn = 1B</td>
<td>P_7.4.2.7</td>
</tr>
<tr>
<td>Switch-ON/OFF Matching ton - tOFF</td>
<td>Atsw</td>
<td>-50</td>
<td>0</td>
<td>50</td>
<td>μς</td>
<td>Vs = 13.5 V PCS . PCCn = 0B</td>
<td>P_7.4.2.9</td>
</tr>
<tr>
<td colspan="5">Voltage Slope</td>
<td></td>
<td colspan="2"></td>
</tr>
<tr>
<td>Switch-ON Slew Rate</td>
<td>(dV/dt)ON</td>
<td>0.3</td>
<td>0.6</td>
<td>0.9</td>
<td>V/us</td>
<td>Vs = 13.5 V VOUT = 30% to 70% of Vs SRC . SRCn = 0B</td>
<td>P_7.4.2.11</td>
</tr>
<tr>
<td>Switch-ON Slew Rate</td>
<td>(dV/dt)ON</td>
<td>0.15</td>
<td>0.3</td>
<td>0.45</td>
<td>V/us</td>
<td>Vs = 13.5 V VOUT = 30% to 70% of Vs SRC . SRCn = 1B</td>
<td>P_7.4.2.12</td>
</tr>
<tr>
<td>Switch-OFF Slew Rate</td>
<td>-(dV/dt) OFF</td>
<td>0.3</td>
<td>0.6</td>
<td>0.9</td>
<td>V/us</td>
<td>Vs = 13.5 V VOUT = 70% to 30% of Vs SRC . SRCn = 0B</td>
<td>P_7.4.2.14</td>
</tr>
<tr>
<td>Switch-OFF Slew Rate</td>
<td>-(dV/dt) OFF</td>
<td>0.125</td>
<td>0.3</td>
<td>0.45</td>
<td>V/us</td>
<td>Vs = 13.5 V VOUT = 70% to 30% of Vs SRC . SRCn = 1B</td>
<td>P_7.4.2.15</td>
</tr>
<tr>
<td>Slew Rate Matching</td>
<td>A(dV/dt)sw</td>
<td>-30</td>
<td>0</td>
<td>30</td>
<td>%</td>
<td>1) Vs = 13.5 V</td>
<td>P_7.4.2.17</td>
</tr>
<tr>
<td colspan="8">Voltages</td>
</tr>
<tr>
<td>Output Voltage Drop Limitation at Small Load Currents</td>
<td>VDS(SLC)</td>
<td>2</td>
<td>10</td>
<td>18</td>
<td>mV</td>
<td>2) 1L =/L(OL) = 20 mA</td>
<td>P_7.4.2.18</td>
</tr>
</table>

1\) A(dV/dt)sw=((dV/dt)ON - (dV/dt)OFF) / (((dV/dt)ON + (dV/dt)OFF) / 2).

2\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="38" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 39" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Power Stages


## 7.5 Electrical Characteristics - Power Output Stages

VDD = 3.0 V to 5.5 V, Vs = 6 V to 18 V, TJ = - 40 °C to +150 ℃

Typical values: VDD = 5.0 V, Vs = 13.5 V, T ] = 25 ℃

Typical resistive loads connected to the outputs for testing (unless otherwise specified):

5.5 mΩ: Ri = 2.4Ω

13.5 mΩ: Ri=3.4Ω


### 7.5.1 Power Output Stage - 5.5 ml2


<table>
<caption>Table 17 Electrical Characteristics: Power Stages - 5.5 ml2</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Output characteristics</td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
</tr>
<tr>
<td>ON-State Resistance at TJ = 25 ℃</td>
<td>RDS(ON)_25</td>
<td>–</td>
<td>5.5</td>
<td>–</td>
<td>ΜΩ</td>
<td>1) T] = 25 ℃</td>
<td>P_7.5.13.1</td>
</tr>
<tr>
<td>ON-State Resistance at TJ = 150 ℃</td>
<td>RDS(ON)_150</td>
<td>-</td>
<td>-</td>
<td>9</td>
<td>mQ</td>
<td>TJ = 150 ℃</td>
<td>P_7.5.13.2</td>
</tr>
<tr>
<td>ON-State Resistance in Cranking</td>
<td>RDS(ON)_CRANK</td>
<td>-</td>
<td>–</td>
<td>11.5</td>
<td>mQ</td>
<td>TJ =150 ℃ Vs = 3.1 V</td>
<td>P_7.5.13.3</td>
</tr>
<tr>
<td>ON-State Resistance in Inverse Current at Ty = 25 ℃</td>
<td>RDS(INV)_25</td>
<td>–</td>
<td>5.5</td>
<td>–</td>
<td>mQ</td>
<td>1) TJ = 25 ℃ IL =- IL(NOM)</td>
<td>P_7.5.13.4</td>
</tr>
<tr>
<td>ON-State Resistance in Inverse Current at TJ = 150 ℃</td>
<td>RDS(INV)_150</td>
<td>–</td>
<td>–</td>
<td>11.5</td>
<td>mQ2</td>
<td>1) TJ = 150 ℃ IL =- IL(NOM)</td>
<td>P_7.5.13.5</td>
</tr>
<tr>
<td>ON-State Resistance in Reverse Polarity at TJ = 25 ℃</td>
<td>RDS(REV)_25</td>
<td>–</td>
<td>11</td>
<td>–</td>
<td>mQ</td>
<td>1) TJ = 25 ℃ Vs =- 13.5 V IL= - IL(NOM) RSENSE = 1.2 k£2</td>
<td>P_7.5.13.6</td>
</tr>
<tr>
<td>ON-State Resistance in Reverse Polarity at TJ =150 ℃</td>
<td>RDS(REV)_150</td>
<td>–</td>
<td>–</td>
<td>18</td>
<td>m22</td>
<td>1) TJ =150 ℃ Vs =- 13.5 V IL =- L(NOM) RSENSE = 1.2 k£2</td>
<td>P_7.5.13.7</td>
</tr>
<tr>
<td>Nominal Load Current per Channel (all Channels Active)</td>
<td>IL(NOM)</td>
<td>-</td>
<td>7</td>
<td>-</td>
<td>A</td>
<td>1) TA = 85 ℃ TJ ≤150°℃</td>
<td>P_7.5.13.8</td>
</tr>
<tr>
<td>Output Leakage Current at TJ ≤ 85℃</td>
<td>L(OF)_85</td>
<td>–</td>
<td>0.08</td>
<td>0.5</td>
<td>µA</td>
<td>1) VOUT = 0 V VIN = "low" and OUT . OUTn = 0B TA ≤85°℃</td>
<td>P_7.5.13.9</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="39" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 40" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Power Stages


<table>
<caption>Table 17 Electrical Characteristics: Power Stages - 5.5 ml2</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Output Leakage Current at TJ =150 ℃</td>
<td>IL(OFF)_150</td>
<td>–</td>
<td>–</td>
<td>24</td>
<td>µA</td>
<td>VOUT = 0 V IN = "low" and OUT . OUTn = 0B TA = 150 ℃</td>
<td>P_7.5.13.10</td>
</tr>
<tr>
<td>Inverse Current Capability</td>
<td>IL(INV)</td>
<td>-</td>
<td>7</td>
<td>-</td>
<td>A</td>
<td>1) VS &lt; VOUT IN = "high" or OUT . OUTn = 1B</td>
<td>P_7.5.13.11</td>
</tr>
<tr>
<td colspan="8">Voltage Slope</td>
</tr>
<tr>
<td>Passive Slew Rate (e.g. for Half Bridge Configuration)</td>
<td>|dVOUT / dt |</td>
<td>–</td>
<td>–</td>
<td>10</td>
<td>V/us</td>
<td>1) Vs =13.5 V</td>
<td>P_7.5.13.12</td>
</tr>
<tr>
<td colspan="8">Voltages</td>
</tr>
<tr>
<td>Drain Source Diode Voltage</td>
<td>IV DS(DIODE)|</td>
<td>–</td>
<td>500</td>
<td>600</td>
<td>mV</td>
<td>1) /L =- 190 mA TJ =150 ℃</td>
<td>P_7.5.13.13</td>
</tr>
<tr>
<td colspan="8">Switching Energy</td>
</tr>
<tr>
<td>Switch-ON Energy</td>
<td>EON</td>
<td>–</td>
<td>0.57</td>
<td>–</td>
<td>mJ</td>
<td>1) Vs = 18 V SRC . SRCn = 0B PCS . PCCn = 0B</td>
<td>P_7.5.13.14</td>
</tr>
<tr>
<td>Switch-OFF Energy</td>
<td>EOFF</td>
<td>–</td>
<td>0.77</td>
<td>–</td>
<td>mJ</td>
<td>1) Vs = 18 V SRC . SRCn = 0B PCS . PCCn = 0B</td>
<td>P_7.5.13.15</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


## 7.5.2 Power Output Stage - 13.5 m22


<table>
<caption>Table 18 Electrical Characteristics: Power Stages - 13.5 ml2</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Output characteristics</td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
</tr>
<tr>
<td>ON-State Resistance at TJ =25 ℃</td>
<td>RDS(ON)_25</td>
<td>–</td>
<td>13.5</td>
<td>–</td>
<td>mQ</td>
<td>1) TJ =25 ℃</td>
<td>P_7.5.14.1</td>
</tr>
<tr>
<td>ON-State Resistance at TJ = 150 ℃</td>
<td>RDS(ON)_150</td>
<td>–</td>
<td>–</td>
<td>22</td>
<td>mQ</td>
<td>TJ = 150 ℃</td>
<td>P_7.5.14.2</td>
</tr>
<tr>
<td>ON-State Resistance in Cranking</td>
<td>RDS(ON)_CRANK</td>
<td>-</td>
<td>–</td>
<td>27</td>
<td>mQ</td>
<td>TJ =150 ℃ Vs = 3.1 V</td>
<td>P_7.5.14.3</td>
</tr>
<tr>
<td>ON-State Resistance in Inverse Current at T = 25 ℃</td>
<td>RDS(INV)_25</td>
<td>–</td>
<td>13.5</td>
<td>–</td>
<td>m2</td>
<td>1) TJ =25 ℃ IL= - IL(NOM)</td>
<td>P_7.5.14.4</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="40" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 41" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Power Stages


<table>
<caption>Table 18 Electrical Characteristics: Power Stages - 13.5 ml2 (continued)</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>ON-State Resistance in Inverse Current at TJ = 150 ℃</td>
<td>RDS(INV)_150</td>
<td>–</td>
<td>–</td>
<td>27</td>
<td>m22</td>
<td>1) TJ=150 ℃ IL= - IL(NOM)</td>
<td>P_7.5.14.5</td>
</tr>
<tr>
<td>ON-State Resistance in Reverse Polarity at TJ = 25 ℃</td>
<td>RDS(REV)_25</td>
<td>–</td>
<td>27</td>
<td>–</td>
<td>mQ</td>
<td>1) TJ =25 ℃ Vs =- 13.5 V IL= - IL(NOM) RSENSE = 1.2 kl2</td>
<td>P_7.5.14.6</td>
</tr>
<tr>
<td>ON-State Resistance in Reverse Polarity at TJ= 150 ℃</td>
<td>RDS(REV)_150</td>
<td>–</td>
<td>–</td>
<td>43</td>
<td>mQ</td>
<td>1) TJ =150 ℃ Vs =- 13.5 V IL= - IL(NOM) RSENSE = 1.2 k£2</td>
<td>P_7.5.14.7</td>
</tr>
<tr>
<td>Nominal Load Current per Channel (all Channels Active)</td>
<td>IL(NOM)</td>
<td>-</td>
<td>4</td>
<td>-</td>
<td>A</td>
<td>1) TA= 85 ℃ TJ ≤ 150 °℃</td>
<td>P_7.5.14.8</td>
</tr>
<tr>
<td>Output Leakage Current at TJ ≤ 85℃</td>
<td>L(OF)_85</td>
<td>–</td>
<td>0.04</td>
<td>0.2</td>
<td>µA</td>
<td>1) VOUT = 0 V VIN = "low" and OUT . OUTn = 0B TA ≤ 85℃</td>
<td>P_7.5.14.9</td>
</tr>
<tr>
<td>Output Leakage Current at TJ=150 ℃</td>
<td>IL(OFF)_150</td>
<td>–</td>
<td>–</td>
<td>16</td>
<td>µA</td>
<td>VOUT = 0 V VIN = "low" and OUT . OUTn = 0B TA = 150 ℃</td>
<td>P_7.5.14.10</td>
</tr>
<tr>
<td>Inverse Current Capability</td>
<td>İL(INV)</td>
<td>-</td>
<td>4</td>
<td>-</td>
<td>A</td>
<td>1) Vs &lt; VOUT IN = "high" or OUT . OUTn = 1B</td>
<td>P_7.5.14.11</td>
</tr>
<tr>
<td>Voltage Slope</td>
<td colspan="7"></td>
</tr>
<tr>
<td>Passive Slew Rate (e.g. for Half Bridge Configuration)</td>
<td>|dVOUT / dt |</td>
<td>–</td>
<td>–</td>
<td>10</td>
<td>V/us</td>
<td>1) Vs = 13.5 V</td>
<td>P_7.5.14.12</td>
</tr>
<tr>
<td colspan="8">Voltages</td>
</tr>
<tr>
<td>Drain Source Diode Voltage</td>
<td>IVDS(DIODE)</td>
<td>–</td>
<td>500</td>
<td>600</td>
<td>mV</td>
<td>1) /L =- 190 mA TJ=150 ℃</td>
<td>P_7.5.14.13</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="41" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 42" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Power Stages


<table>
<caption>Table 18 Electrical Characteristics: Power Stages - 13.5 ml2 (continued)</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Switching Energy</td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
</tr>
<tr>
<td>Switch-ON Energy</td>
<td>EON</td>
<td>–</td>
<td>0.43</td>
<td>–</td>
<td>mJ</td>
<td>1) Vs = 18 V SRC . SRCn = 0B PCS . PCCn = 0B</td>
<td>P_7.5.14.14</td>
</tr>
<tr>
<td>Switch-OFF Energy</td>
<td>EOFF</td>
<td>–</td>
<td>0.52</td>
<td>–</td>
<td>mJ</td>
<td>1) Vs = 18 V SRC . SRCn = 0B PCS . PCCn = 0B</td>
<td>P_7.5.14.15</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="42" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 43" -->


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


<figure>

Infineon

</figure>


<!-- PageHeader="Protection" -->


## 8 Protection

The BTS72220-4ESA is protected against Overtemperature, Overload, Reverse Battery (with ReverseON) and
Overvoltage. Overtemperature and Overload protections are working when the device is not in Sleep mode.
Overvoltage protection works in all operation modes. Reverse Battery protection works when the GND and VS
pins are reverse supplied.


### 8.1 Overtemperature Protection

The device incorporates both an absolute (TJ(ABS) and a dynamic (TJ(DYN) temperature protection circuitry for
each channel. An increase of junction temperature TJ above either one of the two thresholds (TJ(ABS) or TJ(DYN)
switches OFF the overheated channel to prevent destruction. The corresponding WRNDIAG . WRNn bits are set
and cleared on read. The channel remains switched OFF until junction temperature has reached the "Restart"
condition described in Table 19. The behavior is shown in Figure 25 (absolute Overtemperature Protection)
and Figure 26 (dynamic Overtemperature Protection). TJ(REF) is the reference temperature used for dynamic
temperature protection.


<figure>
<figcaption>Figure 25 Overtemperature Protection (Absolute)</figcaption>

IN /
OUT. OUTn

t

IL

/L(OVL)

t

TJ

TJ(ABS)

☒

☒

t

his

t

Internal
counter

0

1

2

t

WRNDIAG. WRNn

0

1

0

Read WRNDIAG

t

Protection_OT_Restart.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="43" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 44" -->


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


<figure>

Infineon

</figure>


# Protection


<figure>
<figcaption>Figure 26 Overtemperature Protection (Dynamic)</figcaption>

IN /
OUT. OUTn

t

IL

L(OVL)

t

TJ

TJ(ABS)

TJ(DYN)

TJ(start)
TJ(REF)

t

/Is

t

Internal
counter

0

1

2

3

4

5

6

nRESTART(CR) + 1

0

1

t

WRNDIAG. WRNn

0

1

0

1

1

0

1

Read WRNDIAG

Read WRNDIAG

t

ERRDIAG. ERRn

0

1

0

HWCR. CLC = 1B

t

Protection_dT_Restart.emf

</figure>


When the Overtemperature protection circuitry allows the channel to be switched ON again, the restart
strategy described in Chapter 8.3.1 is followed.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="44" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 45" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->
<!-- PageHeader="Protection" -->


## 8.2 Overload Protection

The BTS72220-4ESA is protected in case of Overload or short circuit to ground. Two Overload thresholds are
defined (see Figure 27) and selected automatically depending on the voltage Vps across the power DMOS:

· IL(OVLO) when VDS < 13 V

· IL(OVL1) when VDs > 22 V

In addition, the Overload threshold can be reduced by setting OCR . OCTn.


<figure>
<figcaption>Figure 27 Overload current thresholds</figcaption>

Overload threshold variation ("1" = IL(OVLO) @ VDs = 5 V)

1.1

L(OVLO)

OCR.OCTn = 0

1

OCR.OCTn = 1

0.9

0.8

0.7

L(OVL1)

0.6

0.5

0.4

0.3

0.2

0.1

0

4

8

12

16

20

24

28

Drain Source Voltage (V)

</figure>


When IL L(OVL) (either L(OVLO) or LOVLI), the channel is switched OFF. The channel is allowed to restart
according to the restart strategy described in Chapter 8.3.1.


## 8.3 Protection and Diagnosis in case of Fault

Any event that triggers a protection mechanism (either Overtemperature or Overload) has 3 consequences:

· The affected channel switches OFF and the internal counter is incremented

· The current sense of the affected channel is set to high impedance

· The corresponding WRNDIAG . WRNn are set to 1B and latched until readout.

The channel can be switched ON again if all the protection mechanisms fulfill the "restart" conditions
described in Table 19 and the internal restart counter is enabled (RCD . RCDn set to 0B).

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="45" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 46" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->
<!-- PageHeader="Protection" -->


<table>
<caption>Table 19 Protection "Restart" Condition</caption>
<tr>
<th>Fault condition</th>
<th>Switch OFF event</th>
<th>"Restart" Condition</th>
</tr>
<tr>
<td>Overtemperature</td>
<td>TJ≥ TJ(ABS) Or (TJ - TJ(REF) ≥ TJ(DYN)</td>
<td>TJ &lt;TJ(ABS) and (T) - TJ(REF) &lt;TJ(DYN) (including hysteresis) nRESTART &lt; nRESTART(CR) RCD . RCDn = 0</td>
</tr>
<tr>
<td>Overload</td>
<td>IL ≥/L(OVL)</td>
<td>/_ &lt; 50 mA T, within TJ(ABS) and TJ(DYN) ranges (including hysteresis) nRESTART &lt; nRESTART(CR) RCD. RCDn = 0</td>
</tr>
</table>


### 8.3.1 Restart Strategy

When INx or OUT . OUTn is set to "high", the corresponding channel is switched ON. In case of fault condition
the output stage is switched OFF. The channel is allowed to restart only in case the "restart" conditions for the
protection mechanisms are fulfilled (see Table 19). The WRNDIAG . WRNn is set during Overcurrent shutdown.
It is reset when the internal fault signal is cleared and the WRNDIAG is transmitted, unless latched state is
reached by exceeding nRESTART(CR). The next Overcurrent event set the WRNDIAG. WRNn again. In case the
automatic restarts are not required, they can be deactivated by setting RCD . RCDn to 1B. When RCD . RCDn is
set to 1B, the restart counter will be reset. When a channel reaches latched state, the corresponding
ERRDIAG. ERRn bit is set. The restart latch and counter are cleared by setting the SPI bit HWCR . CLC to 1B. If
the input pin is "high" or OUT. OUTn is still set to 1B, the channel is switched ON immediately after the
command that set HWCR. CLC bit to 1B. To ensure an adequate cool down after latch-OFF condition,
application software needs to wait for t > tRETRY before restarting the channel.
The restart strategy is shown in Figure 28.


<figure>
<figcaption>Figure 28 Restart Strategy timing diagram</figcaption>

IN/
OUT. OUTn

t

Short circuit
to ground

t

IL

1\)

t> tRETRY

L(OWL)

0

0

t

Internal
counter

0

1

2

3

4

5

6

nRESTART(CR) + 1

1

2

nRESTART(CR) + 1

1

0

0

0

t

WRNDIAG. WRNn

0

1

0

1

1

1

0

Read WRNDIAG

0

0

t

RCS. RCSn

0

1

2

3

4

5

6

7

1

2

7

1

0

HWCR. CLC = 1p

RCD. RCDn = 1}

HWCR. CLC = 1p

t

1\) Note: Maximum peak current depending onsystem impedance

Protection_Restart.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="46" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 47" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Protection


<figure>
<figcaption>Figure 29 Restart Strategy timing diagram in Limp Home</figcaption>

t<tDELAY(CR)

t≥ tDELAY(CR)

t ≥ tRETRY

İLHI(AC)

IN

t

LHI

t

Short circuit
to ground

t

IL

1\)

/L(OV)

t

Internal
counter

0123456

nRESTART(CR) + 1

0123456

nRESTART(CR) + 1

0123456
nRESTART(CR) + 1

t

WRNDIAG. WRNn

0

1

0

1

1

0

1

1

0

1

Read WRNDIAG

Read WRNDIAG

Read WRNDIAG

Read WRNDIAG

Read WRNDIAG

t

1\) Note: Maximum peak current depending on system impedance

Protection_Restart_LH.emf

</figure>


## 8.4 Additional protections


### 8.4.1 Reverse Polarity Protection

In Reverse Polarity condition (also known as Reverse Battery), the output stages are switched ON (see
parameter RDS(REV) because of ReverseON feature which limits the power dissipation in the output stages.
Each ESD diode of the logic contributes to total power dissipation. The reverse current through the output
stages must be limited by the connected loads. The current through digital power supply VDD and Digital Input
pins has to be limited as well by an external resistor (please refer to the Absolute Maximum Ratings listed in
Chapter 4.1 and to Application Information in Chapter 11).

Figure 30 shows a typical application including a device with ReverseON. A current flowing into GND pin
(-IGND) during Reverse Polarity condition is necessary to activate ReverseON, therefore a resistive path
between module ground and device GND pin must be present.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="47" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 48" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Protection


<figure>
<figcaption>Figure 30 Reverse Battery Protection (application example)</figcaption>

-VBAT(REV)

5V (reverse protected)

IVDD

VDD

RVDD

High-side Channel

VS

με

VDD

IDI

DO

RDI

DI

ReverseON

OUTn

-/OUT

GND

IS

GND

L, C, R

RSENSE

-his

RGN D

-IGND

Protection_RevBatt_SPI.emf

</figure>


## 8.4.2 Overvoltage Protection

In the case of supply voltages between VS(EXT,UP) and VBAT(LD), the output transistors are still operational and
follow the input pins or the OUT register. In addition to the output clamp for inductive loads as described in
Chapter 7.2.2, there is a clamp mechanism available for Overvoltage protection for the logic and the output
channels, monitoring the voltage between VS and GND pins (VS(CLAMP).

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="48" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 49" -->


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


<figure>

Infineon

</figure>


<!-- PageHeader="Protection" -->


### 8.5 Protection against loss of connection


#### 8.5.1 Loss of Battery and Loss of Load

The loss of connection to battery or to the load has no influence on device robustness when load and wire
harness are purely resistive. In case of driving an inductive load, the energy stored in the inductance must be
handled. BTS72220-4ESA can handle the inductivity of the wire harness up to 10 UH with /L(NOM). In case of
applications where currents and/or the aforementioned inductivity are exceeded, an external suppressor
diode (like diode Dz2 shown in Chapter 11) is recommended to handle the energy and to provide a well-
defined path to the load current.

Note:
In case of a lost battery connection the VS monitoring function protects the SPI registers as soon the
device is out of Sleep mode. This means that any command sent to the device will be ignored and the
device will just send back the STDDIAG. Furthermore, the status of the LHI pin is blanked, which
means that it is not possible to enter Limp Home mode.


#### 8.5.2 Loss of Ground

In case of loss of device ground, it is recommended to have a resistor connected between any Digital Input pin
and the microcontroller to ensure a channel switch OFF (as described in Chapter 11).

Note:
In case any Digital Input pin is pulled to ground (either by a resistor or active) a parasitic ground path
is available, which could keep the device operational during loss of device ground. The same
behavior applies for the SPI functionality.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="49" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 50" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->
<!-- PageHeader="Protection" -->


### 8.6 Electrical Characteristics Protection

VDD = 3.0 V to 5.5 V, Vs = 6 V to 18 V, TJ =- 40 °C to +150 ℃
Typical values: VDD = 5.0 V, Vs = 13.5 V, TJ=25 ℃

Typical resistive loads connected to the outputs for testing (unless otherwise specified):

5.5 mΩ: Ri = 2.4Ω

13.5 mΩ: Ri= 3.4Ω


<table>
<caption>Table 20 Electrical Characteristics: Protection - General</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Thermal Shutdown Temperature (Absolute)</td>
<td>TJ(ABS)</td>
<td>150</td>
<td>175</td>
<td>200</td>
<td>ºC</td>
<td>1)2) See Figure 25</td>
<td>P_8.6.0.1</td>
</tr>
<tr>
<td>Thermal Shutdown Hysteresis (Absolute)</td>
<td>HYS(ABS)</td>
<td>–</td>
<td>30</td>
<td>–</td>
<td>K</td>
<td>3) See Figure 25</td>
<td>P_8.6.0.2</td>
</tr>
<tr>
<td>Thermal Shutdown Temperature (Dynamic)</td>
<td>T TJ(DYN)</td>
<td>–</td>
<td>80</td>
<td>–</td>
<td>K</td>
<td>3) See Figure 26</td>
<td>P_8.6.0.3</td>
</tr>
<tr>
<td>Power Supply Clamping Voltage at TJ = - 40 ℃</td>
<td>VS(CLAMP) _- 40</td>
<td>33</td>
<td>36.5</td>
<td>42</td>
<td>V</td>
<td>Ivs = 5 mA TJ =- 40 °℃ See Figure 20</td>
<td>P_8.6.0.6</td>
</tr>
<tr>
<td>Power Supply Clamping Voltage at TJ ≥ 25 °℃</td>
<td>VS(CLAMP)_25</td>
<td>35</td>
<td>38</td>
<td>44</td>
<td>V</td>
<td>2) Ivs = 5 mA TJ≥25 ℃ See Figure 20</td>
<td>P_8.6.0.7</td>
</tr>
<tr>
<td>Power Supply Voltage Threshold for Overcurrent Threshold Reduction in case of Short Circuit</td>
<td>VS(JS)</td>
<td>20.5</td>
<td>22.5</td>
<td>24.5</td>
<td>V</td>
<td>3) Setup acc. to AEC- Q100-012</td>
<td>P_8.6.0.8</td>
</tr>
</table>

1\) Functional test only.

2\) Tested at TJ = 150℃ only.

3\) Not subject to production test - specified by design.


#### 8.6.1 Electrical Characteristics Protection - SPOC™


<table>
<caption>Table 21 Electrical Characteristics: Protection - SPOC™</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Counter Reset Delay Time after Fault Condition in Limp Home</td>
<td>tDELAY(CR)</td>
<td>40</td>
<td>70</td>
<td>100</td>
<td>ms</td>
<td>1) LHI = “high" INx = "low"</td>
<td>P_8.6.2.1</td>
</tr>
<tr>
<td>Automatic Restarts in Case of Fault after a Counter Reset</td>
<td>nRESTART(CR)</td>
<td>-</td>
<td>6</td>
<td>-</td>
<td>-</td>
<td>1)</td>
<td>P_8.6.2.2</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="50" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 51" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->
<!-- PageHeader="Protection" -->


##### 8.7 Electrical Characteristics Protection - Power Output Stages

VDD = 3.0 V to 5.5 V, Vs = 6 V to 18 V, TJ = - 40 °C to +150 ℃
Typical values: VDD = 5.0 V, Vs = 13.5 V, T ]=25 ℃

Typical resistive loads connected to the outputs for testing (unless otherwise specified):

5.5 mΩ: Ri = 2.4Ω

13.5 mΩ: Ri= 3.4Ω


###### 8.7.1 Protection Power Output Stage - 5.5 ml2


<table>
<caption>Table 22 Electrical Characteristics: Protection - 5.5 ml2</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Overload Detection Current High Level</td>
<td>IL(OVL0)</td>
<td>104</td>
<td>116</td>
<td>130</td>
<td>A</td>
<td>1) OCR. OCTn= 0B TJ =- 40 °℃ to 50 ℃ d//dt = 0.4 A/us</td>
<td>P_8.7.13.3</td>
</tr>
<tr>
<td>Overload Detection Current High Level</td>
<td>I L(OVL0)</td>
<td>87</td>
<td>97</td>
<td>108</td>
<td>A</td>
<td>2) OCR. OCTn= 0B TJ=150 °℃ d//dt = 0.4 A/us</td>
<td>P_8.7.13.4</td>
</tr>
<tr>
<td>Overload Detection Current Low Level</td>
<td>L(OVL2)</td>
<td>47</td>
<td>56</td>
<td>67</td>
<td>A</td>
<td>2) OCR. OCTn= 1B d//dt = 0.4 A/us</td>
<td>P_8.7.13.2</td>
</tr>
<tr>
<td>Overload Detection Current High Level (parallel mode)</td>
<td>/L(OVL3)</td>
<td>55</td>
<td>77</td>
<td>88</td>
<td>A</td>
<td>2)3) OCR. OCTn= 0B PCS . PCCn= 1B d//dt = 0.4 A/us</td>
<td>P_8.7.13.6</td>
</tr>
<tr>
<td>Overload Detection Current at High VDs</td>
<td>IL(OVL1)</td>
<td>–</td>
<td>71</td>
<td>–</td>
<td>A</td>
<td>2) d//dt = 0.4 A/us</td>
<td>P_8.7.13.5</td>
</tr>
<tr>
<td>Overload Detection Current Jump Start Condition</td>
<td>IL(OVL_JS)</td>
<td>–</td>
<td>71</td>
<td>–</td>
<td>A</td>
<td>2) OCR . OCTn= 0B V=&gt;VS(JS) d//dt = 0.4 A/us</td>
<td>P_8.7.13.7</td>
</tr>
</table>

1\) Tested at TJ =- 40 °C.

2\) Not subject to production test - specified by design.

3\) L(OVL3) applies for one channel. Total current for two channels in parallel /L(OVL) ≤2 x / L(OVL3).


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="51" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 52" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->
<!-- PageHeader="Protection" -->


###### 8.7.2 Protection Power Output Stage - 13.5 ml2


<table>
<caption>Table 23 Electrical Characteristics: Protection - 13.5 ml2</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Overload Detection Current High Level</td>
<td>IL(OVL0)</td>
<td>55</td>
<td>62</td>
<td>69</td>
<td>A</td>
<td>1) OCR . OCTn= 0B T] =- 40 °℃ to 50 ℃ d//dt = 0.4 A/us</td>
<td>P_8.7.14.3</td>
</tr>
<tr>
<td>Overload Detection Current High Level</td>
<td>İL(OVLO)</td>
<td>46</td>
<td>52</td>
<td>58</td>
<td>A</td>
<td>2) OCR . OCTn= 0B TJ =150 ℃ d//dt = 0.4 A/us</td>
<td>P_8.7.14.4</td>
</tr>
<tr>
<td>Overload Detection Current Low Level</td>
<td>L(OVL2)</td>
<td>27</td>
<td>32</td>
<td>36</td>
<td>A</td>
<td>2) OCR . OCTn= 1B d//dt = 0.4 A/us</td>
<td>P_8.7.14.2</td>
</tr>
<tr>
<td>Overload Detection Current High Level (parallel mode)</td>
<td>İL(OVL3)</td>
<td>29</td>
<td>41</td>
<td>47</td>
<td>A</td>
<td>2)3) OCR. OCTn= 0B PCS . PCCn= 1B d//dt = 0.4 A/us</td>
<td>P_8.7.14.6</td>
</tr>
<tr>
<td>Overload Detection Current at High VDs</td>
<td>L(OVL1)</td>
<td>–</td>
<td>38</td>
<td>–</td>
<td>A</td>
<td>2) d//dt = 0.4 A/us</td>
<td>P_8.7.14.5</td>
</tr>
<tr>
<td>Overload Detection Current Jump Start Condition</td>
<td>IL(OVL_JS)</td>
<td>–</td>
<td>38</td>
<td>–</td>
<td>A</td>
<td>2) OCR. OCTn= 0B Vs&gt;VS(JS) d//dt = 0.4 A/us</td>
<td>P_8.7.14.7</td>
</tr>
</table>

1\) Tested at TJ =- 40 ℃.

2\) Not subject to production test - specified by design.

3\) L(OVL3) applies for one channel. Total current for two channels in parallel /L(OVL) ≤2 x / L(OVL3).


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="52" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 53" -->


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


<figure>

Infineon

</figure>


# Diagnosis


## 9 Diagnosis

For diagnosis purpose, the BTS72220-4ESA provides a current sense at pin IS as well as a diagnosis feedback
via SPI. In case of disabled diagnostic, IS pin becomes high impedance. The integrated current sense
multiplexer is controlled via SPI.

A sense resistor RSENSE must be connected between IS pin and module ground if the current sense diagnosis is
used. RSENSE value has to be higher than 820 02 (or 400 02 when a central Reverse Battery protection is present
on the battery feed) to limit the power losses in the sense circuitry. A typical value is RSENSE = 1.2 kQ2.

Due to the internal connection between IS pin and Vs supply voltage, it is not recommended to connect the IS
pin to the sense current output of other devices, if they are supplied by a different battery feed or using a
different sense concept.

See Figure 31 for details as an overview. For diagnosis feedback at different operation modes, please see
Chapter 9.2.


<figure>
<figcaption>Figure 31 Diagnosis block diagram</figcaption>

VS

liso

Latch

Temperature
Sensor

T

Gate
Control

OR

Overcurrent
Protection

OUT3

Load
Current
Sense

Latch

OUT2

OUT1

ERR0

Channel 0

OUT0

DCR. MUX

Vs

VDS(SB)

Current Sense Multiplexer

DCR.SBM

\+

IS

RSENSE

Diagnosis_4ch.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="53" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 54" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->
<!-- PageHeader="Diagnosis" -->


### 9.1 Overview

Table 24 gives a quick reference to the state of the IS pin during BTS72220-4ESA operation.


<table>
<caption>Table 24 Diagnosis feedback, Function of Operation Mode</caption>
<tr>
<th>Operation Mode</th>
<th>Input level OUT . OUTn</th>
<th>VOUT</th>
<th>Current sense lIs</th>
<th>WRNDIAG . WRNn</th>
<th>STDDIAG . SBM</th>
</tr>
<tr>
<td>Normal operation</td>
<td rowspan="6">Low / 0B OFF</td>
<td>~ GND</td>
<td>Z</td>
<td>0</td>
<td>1</td>
</tr>
<tr>
<td>Short circuit to GND</td>
<td>~ GND</td>
<td>Z</td>
<td>0</td>
<td>1</td>
</tr>
<tr>
<td>Overtemperature</td>
<td>Z</td>
<td>Z</td>
<td>1</td>
<td>x</td>
</tr>
<tr>
<td>Short circuit to Vs</td>
<td>Vs</td>
<td>Z</td>
<td>0</td>
<td>0</td>
</tr>
<tr>
<td>Open Load</td>
<td>&lt;Vs - VDS(SB) &gt; Vs - VDS(SB) 1)</td>
<td>Z Z</td>
<td>0 0</td>
<td>1 0</td>
</tr>
<tr>
<td>Sense verification2)</td>
<td>x</td>
<td>‘IS(VER)</td>
<td>x</td>
<td>0</td>
</tr>
<tr>
<td>Normal operation</td>
<td rowspan="8">High / 1B ON</td>
<td>~ Vs</td>
<td>Is = 1L(NOM) / KILIS</td>
<td>0</td>
<td>0</td>
</tr>
<tr>
<td>Overload</td>
<td>&lt; Vs</td>
<td>/Is = /L / KILIS</td>
<td>0</td>
<td>x</td>
</tr>
<tr>
<td>Short circuit to GND</td>
<td>~ GND</td>
<td>Z</td>
<td>1</td>
<td>1</td>
</tr>
<tr>
<td>Overtemperature</td>
<td>Z</td>
<td>Z</td>
<td>1</td>
<td>x</td>
</tr>
<tr>
<td>Short circuit to Vs</td>
<td>Vs</td>
<td>|S &lt; /L / KILIS</td>
<td>0</td>
<td>0</td>
</tr>
<tr>
<td>Open Load</td>
<td>~ V53)</td>
<td>/ Is = IS (EN)</td>
<td>0</td>
<td>0</td>
</tr>
<tr>
<td>Sense verification2)</td>
<td>x</td>
<td>/ IS(VER)</td>
<td>x</td>
<td>0</td>
</tr>
<tr>
<td>Under load (e.g. Output Voltage Limitation condition)</td>
<td>~ V54)</td>
<td>IS(EN) &lt;15 &lt;/L(NOM) / KILIS</td>
<td>0</td>
<td>0</td>
</tr>
</table>

1\) With additional pull-up resistor.

2\) DCR. MUX = 101B.

3\) The output current has to be smaller than / L(OL)-

4\) The output current has to be higher than / L(OL)-


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="54" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 55" -->


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


<figure>

Infineon

</figure>


<!-- PageHeader="Diagnosis" -->


### 9.2 Diagnosis Word at SPI

Diagnostic information about the status of each channel is provided through SPI. The fault flags, an OR
combination of the overtemperature flags and the Overload monitoring signals are provided in the WRNDIAG
register.

The Overload monitoring signals are latched in the WRNDIAG . WRNn bits and cleared each time the WRNDIAG
is transmitted via SPI unless the maximum number of restarts is reached and the channel protects itself. The
protection latches are cleared by SPI command HWCR . CLC.


### 9.3 Diagnosis in ON state

A current proportional to the load current (ratio kILIs =/L//Is) is provided at pin IS when the following conditions
are fulfilled:

· A power output stage is switched ON with VDs < VDS(SB)

· The diagnosis is enabled for that channel

· No fault (as described in Chapter 8.3) is present

If a "hard" failure mode is present or occurs for the channel selected using the DCR. MUX bits, the IS pin
remains in or changes to "high impedance" state.


#### 9.3.1 Current Sense (KILIS)

The accuracy of the sense current depends on temperature and load current. IIs increases linearly with IL
output current until it reaches the saturation current /IS(SAT). In case of Open Load at the output stage (/) close
to 0 A), the maximum sense current /IS(EN) (no load, diagnosis enabled) is specified. This condition is shown in
Figure 33. The blue line represents the ideal kILIs line, while the red lines show the behavior of a typical
product.

An external RC filter between IS pin and microcontroller ADC input pin is recommended to reduce signal ripple
and oscillations (a minimum time constant of 1 us for the RC filter is recommended).

The KILIs factor is specified with limits that take into account effects due to temperature, supply voltage and
manufacturing process. Tighter limits are possible (within a defined current window) with calibration:

· A well-defined and precise current (/L(CAL) is applied at the output during End of Line test at customer side

. The corresponding current at IS pin is measured and the KILIS is calculated (KILIS @ L(CAL)

. Within the current range going from / L(CAL)_ to /L(CAL)_H the KILIS is equal to KILIS @ L(CAL) with limits defined by
AKILIS

The derating of kILIs after calibration is calculated using the formulas in Figure 32 and it is specified by AKILIS

AK ILIS, MAX = 100 · MAX

KILIS@IL(CAL)
KILIS@IL(CAL)_L
1,
KILIS@IL(CAL)_H
KILIS@IL(CAL)
1)

AK ILIS,MIN = 100 . MIN

KILIS@IL(CAL)_L
KILIS@IL(CAL)

\- 1,
KILIS@IL(CAL)_H
1

KILIS@IL(CAL)

Figure 32 AKILIS calculation formulas

The calibration is intended to be performed at TA(CAL) = 25℃. The parameter AKILIs includes the drift
overtemperature as well as the drift over the current range from [CAL)_ to [CAL)_H.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="55" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 56" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Diagnosis


<figure>
<figcaption>Figure 33 Current Sense Ratio in Open Load at ON condition</figcaption>

/Is

/Is(OL)

/IS(EN)

/L(OL)

L

Diagnosis_OLO N.emf

</figure>


## 9.3.2 Current Sense Multiplexer

There is a current sense multiplexer implemented in the BTS72220-4ESA that routes the sense current of the
selected channel to the diagnosis pin IS. The channel is selected via SPI register DCR . MUX. The sense current
can also be disabled by SPI register DCR . MUX. For details on timing of the current sense multiplexer, refer to
Figure 34. In addition DCR . MUX is used in combination with other SPI bits to address further functions of the
device. To verify the function of the current sensing path in ON and OFF state, the device offers a sense
verification mode. In this mode a predefined current /IS(VER) is provided on the current sense pin independent
on the load condition of any channel. This enables the microcontroller to verify the sense path at any time. The
sense verification mode is enabled when DCR . MUX = 101 B.

All commands and functions involving the DCR . MUX bits are listed below:

· The main function of DCR . MUX is to switch the current sense multiplexer

· Executing PCS . CLCS = 1B clears the counter and latches OFF the channel selected by DCR . MUX

· Executing PCS . SRCS = 1B the slew rate of the channel selected by DCR . MUX will be changed. See
Chapter 7.4.1 for further information

· When reading RCS . RCSn bits, the status of the internal counter of the channel selected by DCR . MUX is
responded

· When setting DCR . MUX = 101B the sense verification mode is enabled

· When setting PCS . SRCS = 1b, the slew rate of the channel selected by DCR . MUX will be adjusted

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="56" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 57" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Diagnosis


<figure>
<figcaption>Figure 34 Current Sense Multiplexer Timings</figcaption>

CSN

DCR. MUX

110

001

010

110

tsI S(ON).

tsIS(CC)

tsIS (OFF)

t

VIS

t

Diagnosis_MuxTiming.emf

</figure>


## 9.4 Diagnosis in OFF state

When a power output stage is in OFF state, the BTS72220-4ESA can measure the output voltage and compare
it with a threshold voltage. In this way, using some additional external components (a pull-down resistor and
a switchable pull-up current source), it is possible to detect if the load is missing or if there is a short circuit to
battery.


### 9.4.1 Switch Bypass Monitor

To detect short circuit to Vs, there is a switch bypass monitor implemented. In case of short circuit between
the output pin OUT and VS in ON state, the current flows through the power transistor as well as through the
short circuit (bypass) with undefined share between the two. As a result, the current sense signal shows lower
values than expected by the load current. In OFF state, the output voltage remains close to Vs potential which
leads to a small Vps. The switch bypass monitor compares the threshold VDS(SB) with the voltage Vos across the
power transistor of that channel which is selected by the current sense multiplexer (DCR . MUX). The result of
the comparison can be read in the standard diagnosis STDDIAG . SBM. In addition the switch bypass monitor
can be used to detect an Open Load in OFF state. In this case a switchable pull-up resistor has to be placed to
pull the OUT to VS potential.


## 9.5 SENSE Timings

Figure 35 shows the timing during settling tsIS(ON) and disabling tsIS(OFF) of the SENSE (including the case of load
change). As a proper signal cannot be established before the load current is stable (therefore before toN),
‘SIS(DIAG) = tsIS(ON) + ton-


<figure>
<figcaption>Figure 35 SENSE Settling / Disabling Timing</figcaption>

IN

OUT. OUTn

OFF

ON

OFF

tOFF

t

SEN SE
EN ABLE

tON

tOFF (DELAY)

t

IL

tON(DELAY)

tsIS(DIAG)

tsIS(LC)

tsIS (OFF)

tsIS(ON)

tdi S(OFF)

t

his

t

Diagnosis_Sense Timing.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="57" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 58" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Diagnosis


### 9.6 Electrical Characteristics Diagnosis

VDD = 3.0 V to 5.5 V, Vs = 6 V to 18 V, TJ = - 40 °C to +150 ℃
Typical values: VDD = 5.0 V, Vs = 13.5 V, T ] =25 ℃

Typical resistive loads connected to the outputs for testing (unless otherwise specified):

5.5 mΩ: R1 = 2.4Ω

13.5 mΩ: Rt= 3.4Ω


<table>
<caption>Table 25 Electrical Characteristics: Diagnosis - General</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>SENSE Saturation Current</td>
<td>/IS(SAT)</td>
<td>4.2</td>
<td>–</td>
<td>15</td>
<td>mA</td>
<td>1) RSENSE = 1.2 k£2</td>
<td>P_9.6.0.12</td>
</tr>
<tr>
<td>SENSE Saturation Current</td>
<td>IS(SAT)</td>
<td>5</td>
<td>–</td>
<td>15</td>
<td>mA</td>
<td>1) RSENSE = 1.2 kΩ Vs = 8 V to 18 V</td>
<td>P_9.6.0.17</td>
</tr>
<tr>
<td>SENSE Leakage Current when Disabled</td>
<td>/IS(OFF)</td>
<td>–</td>
<td>0.01</td>
<td>0.5</td>
<td>µA</td>
<td>IL≥1L(NOM) VIS = 0 V DCR . MUX = 110B</td>
<td>P_9.6.0.2</td>
</tr>
<tr>
<td>SENSE Leakage Current when Enabled at TJ ≤ 85 ℃</td>
<td>/IS(EN)_85</td>
<td>–</td>
<td>0.2</td>
<td>1</td>
<td>µA</td>
<td>1) TJ ≤ 85℃ DCR . MUX ± &lt;110B,111B&gt; See Figure 33</td>
<td>P_9.6.0.3</td>
</tr>
<tr>
<td>SENSE Leakage Current when Enabled at TJ = 150 ℃</td>
<td>/IS(EN)_150</td>
<td>–</td>
<td>1</td>
<td>2</td>
<td>µA</td>
<td>TJ=150 ℃ DCR . MUX ¢ &lt;110B,111B&gt; See Figure 33</td>
<td>P_9.6.0.11</td>
</tr>
<tr>
<td>Saturation Voltage in KILIS Operation (Vs - VIS)</td>
<td>VSIS_k</td>
<td>–</td>
<td>0.5</td>
<td>1</td>
<td>V</td>
<td>1) Vs = 6V INx = "high" or OUT . OUTn = 1B IL ≤2* /L(NOM)</td>
<td>P_9.6.0.6</td>
</tr>
<tr>
<td>Power Supply to IS Pin Clamping Voltage at TJ =- 40 ℃</td>
<td>SIS(CLAMP) _- 40</td>
<td>33</td>
<td>36.5</td>
<td>42</td>
<td>V</td>
<td>lis = 1 mA TJ =- 40 °℃ See Figure 20</td>
<td>P_9.6.0.9</td>
</tr>
<tr>
<td>Power Supply to IS Pin Clamping Voltage at TJ ≥ 25℃</td>
<td>SIS(CLAMP)_25</td>
<td>35</td>
<td>38</td>
<td>44</td>
<td>V</td>
<td>2) lis = 1 mA TJ ≥ 25℃ See Figure 20</td>
<td>P_9.6.0.10</td>
</tr>
</table>

1\) Not subject to production test - specified by design.

2\) Tested at TJ = 150°C.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="58" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 59" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Diagnosis


#### 9.6.1 Electrical Characteristics Diagnosis - SPOC™


<table>
<caption>Table 26 Electrical Characteristics: Diagnosis - Thresholds, Timings</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Switch Bypass Monitor Threshold</td>
<td>VDS(SB)</td>
<td>1.3</td>
<td>1.9</td>
<td>2.5</td>
<td>V</td>
<td>OFF state</td>
<td>P_9.6.2.1</td>
</tr>
<tr>
<td>SENSE Settling Time with Nominal Load Current Stable</td>
<td>tsIS(ON)</td>
<td>–</td>
<td>8</td>
<td>20</td>
<td>μς</td>
<td>Vs = 13.5 V IL= IL(NOM) DCR . MUX: 110B &gt; 001B</td>
<td>P_9.6.2.2</td>
</tr>
<tr>
<td>SENSE Settling Time with Small Load Current Stable</td>
<td>tsIS(ON)_SLC</td>
<td>–</td>
<td>–</td>
<td>60</td>
<td>μς</td>
<td>2) Vs = 13.5 V IL=1L(CAL)_OL DCR . MUX: 110B &gt; 001B</td>
<td>P_9.6.2.10</td>
</tr>
<tr>
<td>SENSE Settling Time after Channel Change</td>
<td>tsIS(CC)</td>
<td>–</td>
<td>–</td>
<td>20</td>
<td>μς</td>
<td>1) Vs = 13.5 V IL= IL(NOM) DCR . MUX: 001B &gt; 010B</td>
<td>P_9.6.2.4</td>
</tr>
<tr>
<td>SENSE Settling Time after Channel Change with Small Load Current</td>
<td>tsIS(CC)_SLC</td>
<td>–</td>
<td>–</td>
<td>60</td>
<td>μς</td>
<td>2) Vs = 13.5 V Start channel: IL= IL(CAL) End channel: IL=1L(CAL)_OL DCR . MUX: 001B &gt; 010B</td>
<td>P_9.6.2.11</td>
</tr>
<tr>
<td>SENSE Disable Time</td>
<td>İşIS(OFF)</td>
<td>–</td>
<td>–</td>
<td>20</td>
<td>μς</td>
<td>1) Vs = 13.5 V L= /L(NOM) DCR . MUX: 010B &gt; 110B</td>
<td>P_9.6.2.5</td>
</tr>
<tr>
<td>SENSE Settling Time after Load Change</td>
<td>tsIS(LC)</td>
<td>–</td>
<td>–</td>
<td>20</td>
<td>μς</td>
<td>2)</td>
<td>P_9.6.2.6</td>
</tr>
<tr>
<td>SENSE Settling Time after Load Change with Small Load Current</td>
<td>tsIS(LC)_SLC</td>
<td>–</td>
<td>250</td>
<td>400</td>
<td>μς</td>
<td>2) Vs = 13.5 V from /1 = 1L(CAL) to IL=1L(CAL)_OL</td>
<td>P_9.6.2.12</td>
</tr>
<tr>
<td>SENSE Disable Time after Channel Deactivation</td>
<td>tdIs(OFF)</td>
<td>–</td>
<td>–</td>
<td>20</td>
<td>us</td>
<td>2)</td>
<td>P_9.6.2.7</td>
</tr>
<tr>
<td>SENSE Current in Sense Verification Mode</td>
<td>VIS(VER)</td>
<td>400</td>
<td>500</td>
<td>600</td>
<td>µA</td>
<td>DCR . MUX = 101B</td>
<td>P_9.6.2.8</td>
</tr>
</table>

1\) Production test for functionality within parameter limits.

2\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="59" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 60" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Diagnosis


# 9.7 Electrical Characteristics Diagnosis - Power Output Stages

VDD = 3.0 V to 5.5 V, Vs = 6 V to 18 V, TJ = - 40 °C to +150 ℃
Typical values: VDD = 5.0 V, Vs = 13.5 V, T ] = 25 ℃

Typical resistive loads connected to the outputs for testing (unless otherwise specified):

5.5 mΩ: Ri = 2.4Ω

13.5 mΩ: Rt =3.4Ω


## 9.7.1 Diagnosis Power Output Stage - 5.5 ml2


<table>
<caption>Table 27 Electrical Characteristics: Diagnosis - 5.5 m22 - high range1)</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Open Load Output Current at /Is = 4 µA</td>
<td>/L(OL)_4u</td>
<td>5</td>
<td>20</td>
<td>50</td>
<td>mA</td>
<td>2) lis = /Is(OL) = 4 µA</td>
<td>P_9.7.13.1</td>
</tr>
<tr>
<td>Current Sense Ratio at IL = IL02</td>
<td>KILIS02</td>
<td>-65%</td>
<td>5500</td>
<td>+65%</td>
<td></td>
<td>2) /102 = 20 mA</td>
<td>P_9.7.13.4</td>
</tr>
<tr>
<td>Current Sense Ratio at 1L=/L05</td>
<td>KILIS05</td>
<td>-60%</td>
<td>5500</td>
<td>+60%</td>
<td></td>
<td>2) /L05 = 100 mA</td>
<td>P_9.7.13.7</td>
</tr>
<tr>
<td>Current Sense Ratio at 1L=/L07</td>
<td>KILIS07</td>
<td>-55%</td>
<td>5500</td>
<td>+55%</td>
<td></td>
<td>2) /L07 = 250 mA</td>
<td>P_9.7.13.9</td>
</tr>
<tr>
<td>Current Sense Ratio at 1=1110</td>
<td>KILIS10</td>
<td>-40%</td>
<td>5500</td>
<td>+40%</td>
<td></td>
<td>2) /L10 = 1 A</td>
<td>P_9.7.13.12</td>
</tr>
<tr>
<td>Current Sense Ratio at 1=1L13</td>
<td>KILIS13</td>
<td>-24%</td>
<td>5500</td>
<td>+24%</td>
<td></td>
<td>2) /L13 = 2.8 A</td>
<td>P_9.7.13.15</td>
</tr>
<tr>
<td>Current Sense Ratio at 1L=1115</td>
<td>KILIS15</td>
<td>-8%</td>
<td>5500</td>
<td>+8%</td>
<td></td>
<td>/115 = 5.5 A</td>
<td>P_9.7.13.17</td>
</tr>
<tr>
<td>Current Sense Ratio at 1=1L17</td>
<td>KILIS17</td>
<td>-8%</td>
<td>5500</td>
<td>+8%</td>
<td></td>
<td>/L17 = 10 A</td>
<td>P_9.7.13.19</td>
</tr>
<tr>
<td>SENSE Current Derating with Low Current Calibration</td>
<td>AKILIS(C KILIS(OL)</td>
<td>-30</td>
<td>0</td>
<td>+30</td>
<td>%</td>
<td>2)3) IL(CAL)_OL = /L05 /L(CAL)_OL_H = /107 IL(CAL)_O_L = /LO2 TA(CAL) = 25 ℃</td>
<td>P_9.7.13.40</td>
</tr>
<tr>
<td>SENSE Current Derating with Nominal Current Calibration</td>
<td>Δk ILIS(NOM)</td>
<td>-9</td>
<td>0</td>
<td>+9</td>
<td>%</td>
<td>2)3) IL(CAL) = 1 115 IL(CAL)_H = 17 /L(CAL)_L = |13 TA(CAL) = 25 ℃</td>
<td>P_9.7.13.41</td>
</tr>
</table>

1\) Parameter valid only if KRC . KRCn = 0B.

2\) Parameter valid only if PCS . PCCn = 0B.

3\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="60" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 61" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Diagnosis


<table>
<caption>Table 28 Electrical Characteristics: Diagnosis - 5.5 m22 - low range1)</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Open Load Output Current at /Is = 4 uA</td>
<td>L(OL)_4u</td>
<td>2</td>
<td>7</td>
<td>20</td>
<td>mA</td>
<td>2)3) lis = /Is(OL) = 4 uA</td>
<td>P_9.7.13.20</td>
</tr>
<tr>
<td>Current Sense Ratio at 1=1L01</td>
<td>KILIS01</td>
<td>-70%</td>
<td>1830</td>
<td>+70%</td>
<td></td>
<td>2)3) /L01 = 10 mA</td>
<td>P_9.7.13.22</td>
</tr>
<tr>
<td>Current Sense Ratio at /L=1L03</td>
<td>KILIS03</td>
<td>-65%</td>
<td>1830</td>
<td>+65%</td>
<td></td>
<td>2)3) /L03 = 30 mA</td>
<td>P_9.7.13.24</td>
</tr>
<tr>
<td>Current Sense Ratio at 1L=/L05</td>
<td>KILIS05</td>
<td>-55%</td>
<td>1830</td>
<td>+55%</td>
<td></td>
<td>2)3) /105 = 100 mA</td>
<td>P_9.7.13.27</td>
</tr>
<tr>
<td>Current Sense Ratio at 1L=/L07</td>
<td>KILIS07</td>
<td>-45%</td>
<td>1830</td>
<td>+45%</td>
<td></td>
<td>2)3) /L07 = 250 mA</td>
<td>P_9.7.13.30</td>
</tr>
<tr>
<td>Current Sense Ratio at 1=1110</td>
<td>KILIS10</td>
<td>-24%</td>
<td>1830</td>
<td>+24%</td>
<td></td>
<td>3) 1110 = 1 A</td>
<td>P_9.7.13.34</td>
</tr>
<tr>
<td>Current Sense Ratio at 1L=1112</td>
<td>KILIS12</td>
<td>-10%</td>
<td>1830</td>
<td>+10%</td>
<td></td>
<td>3) /112 = 2 A</td>
<td>P_9.7.13.36</td>
</tr>
<tr>
<td>Current Sense Ratio at 1L=1115</td>
<td>KILIS15</td>
<td>-8%</td>
<td>1830</td>
<td>+8%</td>
<td></td>
<td>3) /L15 = 5.5 A</td>
<td>P_9.7.13.39</td>
</tr>
<tr>
<td>SENSE Current Derating with Low Current Calibration</td>
<td>AKILIS(OL)</td>
<td>-30</td>
<td>0</td>
<td>+30</td>
<td>%</td>
<td>2)4) IL(CAL)_OL = /L03 IL(CAL)_OL_H =/L05 IL(CAL)_OL_L =/101 TA(CAL) = 25 ℃</td>
<td>P_9.7.13.42</td>
</tr>
<tr>
<td>SENSE Current Derating with Nominal Current Calibration</td>
<td>AKILIS(NOM)</td>
<td>-9</td>
<td>0</td>
<td>+9</td>
<td>%</td>
<td>4) IL(CAL) = / 12 /L(CAL)_H = 115 /L(CAL)_L = /L10 TA(CAL) = 25 ℃</td>
<td>P_9.7.13.43</td>
</tr>
</table>

1\) Parameter valid only if KRC . KRCn = 1B.

2\) Parameter valid only if PCS . PCCn = 0B.

3\) KILIs accuracy valid if 1 us RC filter is placed at ADC input.

4\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="61" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 62" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Diagnosis


## 9.7.2 Diagnosis Power Output Stage - 13.5 ml2


<table>
<caption>Table 29 Electrical Characteristics: Diagnosis - 13.5 ml2- high range1)</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Open Load Output Current at /Is = 4 uA</td>
<td>/L(OL)_4u</td>
<td>3</td>
<td>9</td>
<td>25</td>
<td>mA</td>
<td>2) lis = /Is(OL) = 4 uA</td>
<td>P_9.7.14.1</td>
</tr>
<tr>
<td>Current Sense Ratio at IL = IL01</td>
<td>KILIS01</td>
<td>-65%</td>
<td>2500</td>
<td>+65%</td>
<td></td>
<td>2) /L01 = 10 mA</td>
<td>P_9.7.14.3</td>
</tr>
<tr>
<td>Current Sense Ratio at 1L=/L03</td>
<td>KILIS03</td>
<td>-60%</td>
<td>2500</td>
<td>+60%</td>
<td></td>
<td>2) IL03 = 30 mA</td>
<td>P_9.7.14.5</td>
</tr>
<tr>
<td>Current Sense Ratio at IL = IL05</td>
<td>KILIS05</td>
<td>-55%</td>
<td>2500</td>
<td>+55%</td>
<td></td>
<td>2) /L05 = 100 mA</td>
<td>P_9.7.14.7</td>
</tr>
<tr>
<td>Current Sense Ratio at 1=/L07</td>
<td>KILIS07</td>
<td>-45%</td>
<td>2500</td>
<td>+45%</td>
<td></td>
<td>2) /L07 = 250 mA</td>
<td>P_9.7.14.9</td>
</tr>
<tr>
<td>Current Sense Ratio at 1=1110</td>
<td>KILIS10</td>
<td>-24%</td>
<td>2500</td>
<td>+24%</td>
<td></td>
<td>2) /110 = 1 A</td>
<td>P_9.7.14.12</td>
</tr>
<tr>
<td>Current Sense Ratio at /L=1L12</td>
<td>KILIS12</td>
<td>-8%</td>
<td>2500</td>
<td>+8%</td>
<td></td>
<td>/112 = 2 A</td>
<td>P_9.7.14.14</td>
</tr>
<tr>
<td>Current Sense Ratio at 1=1L15</td>
<td>KILIS15</td>
<td>-8%</td>
<td>2500</td>
<td>+8%</td>
<td></td>
<td>/115 = 5.5 A</td>
<td>P_9.7.14.17</td>
</tr>
<tr>
<td>SENSE Current Derating with Low Current Calibration</td>
<td>AKILIS(OL)</td>
<td>-30</td>
<td>0</td>
<td>+30</td>
<td>%</td>
<td>2)3) IL(CAL)_OL = /L03 L(CAL)_O_H = /L05 IL(CAL)_OL_L =/LOI TA(CAL) = 25 ℃</td>
<td>P_9.7.14.37</td>
</tr>
<tr>
<td>SENSE Current Derating with Nominal Current Calibration</td>
<td>AKILIS(NOM)</td>
<td>-9</td>
<td>0</td>
<td>+9</td>
<td>%</td>
<td>2)3) IL(CAL) = 12 IL(CAL)_H = /L15 LOCAL)_L = 1110 TA(CAL) = 25 ℃</td>
<td>P_9.7.14.38</td>
</tr>
</table>

1\) Parameter valid only if KRC . KRCn = 0B.

2\) Parameter valid only if PCS . PCCn = 0B.

3\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="62" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 63" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Diagnosis


<table>
<caption>Table 30 Electrical Characteristics: Diagnosis - 13.5 m22 - low range1)</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Open Load Output Current at /Is = 4 µA</td>
<td>L(OL)_4u</td>
<td>0.8</td>
<td>2.6</td>
<td>8</td>
<td>mA</td>
<td>2)3) "Is = /Is(OL) = 4 uA</td>
<td>P_9.7.14.18</td>
</tr>
<tr>
<td>Current Sense Ratio at 1=1400</td>
<td>KILISOO</td>
<td>-65%</td>
<td>830</td>
<td>+65%</td>
<td></td>
<td>2)3) /100 = 5 mA</td>
<td>P_9.7.14.19</td>
</tr>
<tr>
<td>Current Sense Ratio at 1=/L01</td>
<td>KILIS01</td>
<td>-60%</td>
<td>830</td>
<td>+60%</td>
<td></td>
<td>2)3) /LO1 = 10 mA</td>
<td>P_9.7.14.20</td>
</tr>
<tr>
<td>Current Sense Ratio at 1L=/L03</td>
<td>KILIS03</td>
<td>-55%</td>
<td>830</td>
<td>+55%</td>
<td></td>
<td>2)3) /103 = 30 mA</td>
<td>P_9.7.14.23</td>
</tr>
<tr>
<td>Current Sense Ratio at IL = IL05</td>
<td>KILIS05</td>
<td>-45%</td>
<td>830</td>
<td>+45%</td>
<td></td>
<td>2)3) /L05 = 100 mA</td>
<td>P_9.7.14.26</td>
</tr>
<tr>
<td>Current Sense Ratio at 1L=/L07</td>
<td>KILIS07</td>
<td>-30%</td>
<td>830</td>
<td>+30%</td>
<td></td>
<td>2)3) /L07 = 250 mA</td>
<td>P_9.7.14.29</td>
</tr>
<tr>
<td>Current Sense Ratio at 1L=/L08</td>
<td>KILIS08</td>
<td>-25%</td>
<td>830</td>
<td>+25%</td>
<td></td>
<td>3) /L08 = 450 mA</td>
<td>P_9.7.14.31</td>
</tr>
<tr>
<td>Current Sense Ratio at 1L=1110</td>
<td>KILIS10</td>
<td>-10%</td>
<td>830</td>
<td>+10%</td>
<td></td>
<td>3) /L10 = 1 A</td>
<td>P_9.7.14.33</td>
</tr>
<tr>
<td>Current Sense Ratio at IL = IL13</td>
<td>KILIS13</td>
<td>-8%</td>
<td>830</td>
<td>+8%</td>
<td></td>
<td>3) /113 = 2.8 A</td>
<td>P_9.7.14.36</td>
</tr>
<tr>
<td>SENSE Current Derating with Low Current Calibration</td>
<td>AKILIS(OL)</td>
<td>-30</td>
<td>0</td>
<td>+30</td>
<td>%</td>
<td>2)4) IL(CAL)_OL = /L01 IL(CAL)_OL_H =/L03 IL(CAL)_OL_L = LOO TA(CAL) = 25 ℃</td>
<td>P_9.7.14.39</td>
</tr>
<tr>
<td>SENSE Current Derating with Nominal Current Calibration</td>
<td>AKILIS(NOM)</td>
<td>-9</td>
<td>0</td>
<td>+9</td>
<td>%</td>
<td>4) L(CAL) = 10 IL(CAL)_H = /L13 /L(CAL)_L = /LOS TA(CAL) = 25 ℃</td>
<td>P_9.7.14.40</td>
</tr>
</table>

1\) Parameter valid only if KRC . KRCn = 1B.

2\) Parameter valid only if PCS . PCCn = 0B.

3\) KILIs accuracy valid if 1 us RC filter is placed at ADC input.

4\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="63" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 64" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Serial Peripheral Interface (SPI)


# 10 Serial Peripheral Interface (SPI)

The serial peripheral interface (SPI) is a full duplex synchronous serial slave interface, which uses four lines:
SO, SI, SCLK and CSN. Data is transferred by the lines SI and SO at the rate given by SCLK. The falling edge of
CSN indicates the beginning of an access. Data is sampled-in on line SI at the falling edge of SCLK and shifted
out on line SO at the rising edge of SCLK. Each access must be terminated by a rising edge of CSN. A modulo 8
counter ensures that data is taken only when a multiple of 8 bit has been transferred. The interface provides
daisy chain capability with modulo 8 bit SPI devices.


<figure>
<figcaption>Figure 36 Serial Peripheral Interface</figcaption>

SO

MSB

6

5

4

3

2

1

LSB

SI

MSB

6

5

4

3

2

1

LSB

CSN

SCLK

time

SPI_8bit.emf

</figure>


## 10.1 SPI Signal Description


### CSN - Chip Select Negated

The system microcontroller selects the BTS72220-4ESA by means of the CSN pin. Whenever the pin is in "low"
state, data transfer can take place. When CSN is in "high" state, any signals at the SCLK and SI pins are ignored
and SO is forced into a "high impedance" state.


### CSN "high" to "low" Transition

· The requested information is transferred into the shift register.

· SO changes from "high impedance" state to "low" state.


### CSN "low" to "high" Transition

· Command decoding is only done, when after the falling edge of CSN exactly a multiple (1, 2, 3, ... ) of eight
SCLK signals have been detected. In case of an incorrect SCLK count, the transmission error flag
(STDDIAG. TER) is set and the command is ignored.

· Data from shift register is transferred into the addressed register.


### SCLK - Serial Clock

This input pin clocks the internal shift register. The serial input (SI) transfers data into the shift register on the
falling edge of SCLK while the serial output (SO) shifts diagnostic information out on the rising edge of the
serial clock. It is essential that the SCLK pin is in "low" state whenever chip select CSN makes any transition,
otherwise the command may not be accepted.


### SI - Serial Input

Serial input data bits are shifted in at this pin, the most significant bit first. SI information is read on the falling
edge of SCLK. The input data consists of two parts, control bits followed by data bits. Please refer to
Chapter 10.5 for further information.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="64" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 65" -->



<figure>

<!-- PageHeader="Infineon" -->

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Serial Peripheral Interface (SPI)


## SO Serial Output

Data is shifted out serially at this pin, the most significant bit first. SO is in "high impedance" state until the
CSN pin goes to "low" state. New data will appear at the SO pin following the rising edge of SCLK.

Please refer to Chapter 10.5 for further information.


## 10.2 Daisy Chain Capability

The SPI of BTS72220-4ESA provides daisy chain capability for modulo 8 bit SPI devices. In this configuration
several devices are activated by the same CSN signal MCSN. The SI line of one device is connected with the SO
line of another device (see Figure 37), in order to build a chain. The end of the chain is connected to the output
and input of the master device, MO and MI respectively. The master device provides the master clock MCLK
which is connected to the SCLK line of each device in the chain.


<figure>
<figcaption>Figure 37 Daisy Chain Configuration</figcaption>

device 1

device 2

device 3

SI

SO

SI

SO

SI

SO

MOSI

SPI

SPI

SPI

CSN

SCLK

CSN

SCLK

CSN

SCLK

MISO

MCSN

MCLK

SPI_DaisyChain_1.emf

</figure>


In the SPI block of each device, there is one shift register where each bit from SI line is shifted in each SCLK.
The bit is shifted out on SO pin. After eight SCLK cycles, the data transfer for one device is finished. In single
chip configuration, the CSN line must turn "high" to make the device acknowledge the transferred data. In
daisy chain configuration, the data shifted out at device 1 has been shifted into device 2. When using three
devices in daisy chain, three times 8 bits have to be shifted through the devices. After that, the MCSN line must
turn "high" (see Figure 38).


<figure>
<figcaption>Figure 38 Data Transfer in Daisy Chain Configuration</figcaption>

MOSI

frame device 3

frame device 2

frame device 1

MISO

response device 3

response device 2

response device 1

MCSN

MSCLK

8 clocks

8 clocks

8 clocks

SPI_DaisyChain_2.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="65" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 66" -->



<figure>

<!-- PageHeader="Infineon" -->

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Serial Peripheral Interface (SPI)


## 10.3 Timing Diagrams


<figure>
<figcaption>Figure 39 Timing Diagram SPI Access</figcaption>

tCSN(LEAD)

tsCLK (P)

tCSN(LAG)

tCSN(TD)

CSN

VCSN(TH), max

VCSN(TH), min

tsCLK (H)

tsCLK (L)

SCLK

VSCLK (TH), max

VSCLK (TH), min

tsı(su)

tsi(H)

SI

VSI(TH), max

VSI(TH), min

tso(EN)

tso(v)

tso(DIS),

SO

VSO(H)

VSO(L)

SPI_Timings.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="66" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 67" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Serial Peripheral Interface (SPI)


## 10.4 Electrical Characteristics

VDD = 3.0 V to 5.5 V, Vs = 6 V to 18 V, TJ =- 40 °C to +150 ℃
Typical values: VDD = 5.0 V, Vs = 13.5 V, T ]=25 ℃


<table>
<caption>Table 31 Electrical Characteristics Serial Peripheral Interface (SPI)</caption>
<tr>
<th rowspan="2">Parameter</th>
<th rowspan="2">Symbol</th>
<th colspan="3">Values</th>
<th rowspan="2">Unit</th>
<th rowspan="2">Note or Test Condition</th>
<th rowspan="2">Number</th>
</tr>
<tr>
<th>Min.</th>
<th>Typ.</th>
<th>Max.</th>
</tr>
<tr>
<td>Timings</td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
</tr>
<tr>
<td>Enable Lead Time (falling CSN to rising SCLK)</td>
<td>tCSN(LEAD)</td>
<td>200</td>
<td>–</td>
<td>–</td>
<td>ns</td>
<td>1)</td>
<td>P_10.4.0.1</td>
</tr>
<tr>
<td>Enable Lag Time (falling SCLK to rising CSN)</td>
<td>[CSN(LAG)</td>
<td>200</td>
<td>–</td>
<td>–</td>
<td>ns</td>
<td>1)</td>
<td>P_10.4.0.2</td>
</tr>
<tr>
<td>Transfer Delay Time (rising CSN to falling CSN)</td>
<td>tCSN(TD)</td>
<td>500</td>
<td>–</td>
<td>–</td>
<td>ns</td>
<td>1)</td>
<td>P_10.4.0.3</td>
</tr>
<tr>
<td>Output Enable Time (falling CSN to SO valid)</td>
<td>tso(EN)</td>
<td>–</td>
<td>30</td>
<td>100</td>
<td>ns</td>
<td>1) CL(SO) = 50 pF</td>
<td>P_10.4.0.4</td>
</tr>
<tr>
<td>Output Disable Time (rising CSN to SO tristate)</td>
<td>tso(DIS)</td>
<td>–</td>
<td>30</td>
<td>100</td>
<td>ns</td>
<td>1) CL(SO) = 50 pF</td>
<td>P_10.4.0.5</td>
</tr>
<tr>
<td>Serial Clock Frequency</td>
<td>ÉSCLK</td>
<td>0</td>
<td>–</td>
<td>5</td>
<td>MHz</td>
<td>1)</td>
<td>P_10.4.0.6</td>
</tr>
<tr>
<td>Serial Clock Period</td>
<td>tSCLK(P)</td>
<td>200</td>
<td>–</td>
<td>–</td>
<td>ns</td>
<td>1)</td>
<td>P_10.4.0.7</td>
</tr>
<tr>
<td>Serial Clock "High" Time</td>
<td>tSCLK(H)</td>
<td>90</td>
<td>–</td>
<td>–</td>
<td>ns</td>
<td>1)</td>
<td>P_10.4.0.8</td>
</tr>
<tr>
<td>Serial Clock "Low" Time</td>
<td>tSCLK(L)</td>
<td>90</td>
<td>–</td>
<td>–</td>
<td>ns</td>
<td>1)</td>
<td>P_10.4.0.9</td>
</tr>
<tr>
<td>Data Setup Time (required Time SI to falling SCLK)</td>
<td>tsı(SU)</td>
<td>20</td>
<td>–</td>
<td>–</td>
<td>ns</td>
<td>1)</td>
<td>P_10.4.0.10</td>
</tr>
<tr>
<td>Data Hold Time (falling SCLK to SI)</td>
<td>tSI(H)</td>
<td>20</td>
<td>–</td>
<td>–</td>
<td>ns</td>
<td>1)</td>
<td>P_10.4.0.11</td>
</tr>
<tr>
<td>Output Data Valid Time with Capacitive Load</td>
<td>tso(v)</td>
<td>–</td>
<td>–</td>
<td>60</td>
<td>ns</td>
<td>1) CL(SO) = 50 PF</td>
<td>P_10.4.0.12</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="67" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 68" -->


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


<figure>

Infineon

</figure>


Serial Peripheral Interface (SPI)


## 10.5 SPI Protocol

The relationship between SI and SO content during SPI communication is shown in Figure 40. SI line
represents the frame sent from the uC and SO line is the answer provided by BTS72220-4ESA. The "previous
response" means that the frame sent back depends on the command frame sent from the uC before.


<figure>
<figcaption>Figure 40 Relationship between SI and SO during SPI communication</figcaption>

SI

frame A

frame B

frame C

SO

previous
response

response to
frame A

response to
frame B

SPI_SI2SO.emf

</figure>


The SPI protocol provides the answer to a command frame only with the next transmission triggered by the
uC. The responses of write commands are deterministic and can be decoded as STDDIAG or WRNDIAG frame.
For responses of read commands previous transmission has to be considered for decoding.

More in detail, the sequence of commands to "read" and "write" the content of a register will look as follows:


<figure>
<figcaption>Figure 41 Register content sent back to uC (a)</figcaption>

SI

write register A

write register B

read register A

new command

SO

previous
response

STDDIAG

WRNDIAG

register A
content

SPI_RWseq_a.emf

</figure>


<figure>
<figcaption>Figure 42 Register content sent back to uC (b)</figcaption>

SI

write register A

read register A

write register B

new command

SO

previous
response

STDDIAG

register A
content

WRNDIAG

SPI_RWseq_b.emf

</figure>


There are 3 special situations where the frame sent back to the uC doesn't depend on the previous received
frame:

. In case an error in transmission happened during the previous frame (for instance, the clock pulses were
not multiple of 8), shown in Figure 43

· When BTS72220-4ESA digital supply comes out of Power-On reset condition, as shown in Figure 44

· When Vs < VS(TP) and DCR . MUX # 111B, as shown in Figure 45

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="68" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 69" -->


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


<figure>

Infineon

</figure>


Serial Peripheral Interface (SPI)


<figure>
<figcaption>Figure 43 SPI response after an error in transmission</figcaption>

SI

frame A
(error in transmission)

(new command)

SO

(previous response)

STDDIAG + TER

SP_SO_TER.emf

</figure>


<figure>
<figcaption>Figure 44 SPI response after coming out of Power-On reset at VDD</figcaption>

VD
VDD (PO)

SI

frame A

frame B

frame C

SO

(SO="Z")

STDDIAG
\+ TER + SLP

response frame B

SP_SO_POR.emf

</figure>


<figure>
<figcaption>Figure 45 SPI response in case of voltage drop on battery</figcaption>

Vs

VS(TP),max
VS(TP),min

t

STDDIAG.
VSMON

0

x

1

x

1

0

t

SI

frame A

frame B

frame C

frame D

frame E

SO

(response)

(response to
frame A)

STDDIAG + TER
\+ VSMON

STDDIAG + TER
\+ VSM ON

(response to
frame D)

Note: Valid if the device is out of Sleep mode.

SPI_SO_VSMON.emf

</figure>


A summary of all possible SPI commands is presented in Table 32, including the answer that BTS72220-4ESA
will send back at the next transmission.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="69" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 70" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Serial Peripheral Interface (SPI)


<table>
<caption>Table 32 SPI Command Summary</caption>
<tr>
<th>Requested Operation</th>
<th>Frame sent to SPOC™ (SI pin)</th>
<th>Frame received from SPOC™ (SO pin) with the next command</th>
</tr>
<tr>
<td>Write OUT register DCR . SWR = XB</td>
<td>100xddddB where: "xddddB" = new OUT register content ("XB" = don't care)</td>
<td>0 0ddddddB - STDDIAG or 01ddddddB - WRNDIAG (Standard Diagnosis or Warning Diagnosis will be sent alternating)</td>
</tr>
<tr>
<td>Read OUT register</td>
<td>0xxxaaaaB where: "aaaaB" = ADDR1 1) ("XB" = don't care)</td>
<td>1000ddddB ("ddddB"=OUT register content)</td>
</tr>
<tr>
<td>Read RCS register</td>
<td>0xxxaaaaB where: "aaaaB" = ADDR1 1) ("xB" = don't care)</td>
<td>10000dddB ("dddB" = RCS register content)</td>
</tr>
<tr>
<td>Write Configuration registers</td>
<td>11aaddddB where: "aaB" = ADDRO 1) "ddddB" = new register content</td>
<td>00ddddddB - STDDIAG 01ddddddB - WRNDIAG (Standard Diagnosis or Warning Diagnosis will be sent alternating)</td>
</tr>
<tr>
<td>Read Configuration registers</td>
<td>0xxxaaaaB where: "aaaaB" = ADDR1 1) ("XB" = don't care)</td>
<td>11aaddddB where: "aaB" = ADDRO 1) "ddddB" = register content</td>
</tr>
<tr>
<td>Read Warning Diagnosis</td>
<td>0xxxx001B ("xB" = don't care)</td>
<td>0100ddddB - WRNDIAG (Warning Diagnosis)</td>
</tr>
<tr>
<td>Read Standard Diagnosis</td>
<td>0xxxx010B ("xB" = don't care)</td>
<td>00ddddddB - STDDIAG (Standard Diagnosis)</td>
</tr>
<tr>
<td>Read Error Diagnosis</td>
<td>0xxxx011B ("XB" = don't care)</td>
<td>0100ddddB - ERRDIAG (Error Diagnosis)</td>
</tr>
</table>

1\) ADDR0 and ADDR1 are defined according to Table 33.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="70" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 71" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Serial Peripheral Interface (SPI)


## 10.6 SPI Diagnosis Registers


### 10.6.1 Diagnosis Registers - Read Commands


<table>
<tr>
<td>Name</td>
<td>7</td>
<td>6</td>
<td>5</td>
<td>4</td>
<td>3</td>
<td>2</td>
<td>1</td>
<td>0</td>
</tr>
<tr>
<td>WRNDIAG</td>
<td>0</td>
<td>X ☒</td>
<td>X ☒</td>
<td>X ☒</td>
<td>0</td>
<td>0</td>
<td>0</td>
<td>1</td>
</tr>
<tr>
<td>STDDIAG</td>
<td>0</td>
<td>X ☒</td>
<td>X ☒</td>
<td>X ☒</td>
<td>0</td>
<td>0</td>
<td>1</td>
<td>0</td>
</tr>
<tr>
<td>ERRDIAG</td>
<td>0</td>
<td>X ☒</td>
<td>X ☒</td>
<td>X ☒</td>
<td>0</td>
<td>0</td>
<td>1</td>
<td>1</td>
</tr>
</table>


### 10.6.2 Diagnosis Registers - Responses


<table>
<tr>
<th>Name</th>
<th>7</th>
<th>6</th>
<th>5</th>
<th>4</th>
<th>3</th>
<th>2</th>
<th>1</th>
<th>0</th>
<th>Default</th>
</tr>
<tr>
<td>WRNDIAG</td>
<td>0</td>
<td>1</td>
<td>0</td>
<td>0</td>
<td>WRNDIAG .</td>
<td>WRNn</td>
<td></td>
<td></td>
<td>40H</td>
</tr>
<tr>
<td>STDDIAG</td>
<td>0</td>
<td>0</td>
<td>STDDIAG . TER</td>
<td>STDDIAG . CSV</td>
<td>STDDIAG . LHI</td>
<td>STDDIAG . SLP</td>
<td>STDDIAG . SBM</td>
<td>STDDIAG . VSMON</td>
<td>24H</td>
</tr>
<tr>
<td>ERRDIAG</td>
<td>0</td>
<td>1</td>
<td>0</td>
<td>0</td>
<td>ERRDIAG .</td>
<td colspan="3">ERRn</td>
<td>40H</td>
</tr>
</table>


<table>
<tr>
<th>Field</th>
<th>Bits</th>
<th>Type</th>
<th>Description</th>
</tr>
<tr>
<td rowspan="3">STDDIAG. TER</td>
<td rowspan="3">5</td>
<td rowspan="3">r</td>
<td>Transmission Error</td>
</tr>
<tr>
<td>0B Previous transmission was successful (modulo 8 clocks received)</td>
</tr>
<tr>
<td>1B (default) Previous transmission failed or first transmission after Power-On reset or Vs &lt; VS(TP) if STDDIAG . VSMON = 1B</td>
</tr>
<tr>
<td rowspan="2">STDDIAG. CSV</td>
<td rowspan="2">4</td>
<td rowspan="2">r</td>
<td>Checksum Verification1) 0B (default) Checksum verification was pass or no checksum calculated</td>
</tr>
<tr>
<td>1B Previous checksum verification was fail</td>
</tr>
<tr>
<td>STDDIAG.LHI</td>
<td>3</td>
<td>r</td>
<td>Limp Home monitor 0B (default) "Low" level at pin LHI 1B "High" level at pin LHI</td>
</tr>
<tr>
<td>STDDIAG. SLP</td>
<td>2</td>
<td>r</td>
<td>Sleep mode monitor 0B Device out of Sleep mode 1B (default) Device is in Sleep mode</td>
</tr>
<tr>
<td>STDDIAG. SBM</td>
<td>1</td>
<td>r</td>
<td>Switch Bypass Monitor2) OB VDS &lt; VDS(SB) 1B VDS &gt; VDS(SB)</td>
</tr>
<tr>
<td rowspan="2">STDDIAG. VSMON</td>
<td rowspan="2">0</td>
<td rowspan="2">r</td>
<td>Vs monitor OB (default) Vs always &gt; Vs(uv) since last Standard Diagnosis readout</td>
</tr>
<tr>
<td>1B Vs &lt; Vs(uv) at least once or Vs &lt; VS(TP) if STDIAG . TER = 1B</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="71" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 72" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


#### Serial Peripheral Interface (SPI)


<table>
<tr>
<th>Field</th>
<th>Bits</th>
<th>Type</th>
<th>Description</th>
</tr>
<tr>
<td rowspan="2">WRNDIAG . WRNn n = 3 to 0</td>
<td rowspan="2">3:0</td>
<td rowspan="2">r</td>
<td>Warning Diagnosis of Channel n 0B (default) No failure</td>
</tr>
<tr>
<td>1B Overcurrent, Overtemperature or delta T detected</td>
</tr>
<tr>
<td>ERRDIAG. ERRn n = 3 to 0</td>
<td>3:0</td>
<td>r</td>
<td>Error Diagnosis of Channel n 0B (default) No failure 1B Channel latched OFF</td>
</tr>
</table>

1\) See Chapter 10.8 for details on checksum calculation.

2\) The switch bypass monitor compares the threshold VDS(SB) with the voltage Vps across the power transistor of that
channel which is selected by the current sense multiplexer (DCR . MUX).


## 10.7 SPI Configuration Registers

The following table provides an overview on the registers available and the available address space.


<table>
<caption>Table 33 Register Overview</caption>
<tr>
<th>Name</th>
<th>SWR 1)</th>
<th>RB</th>
<th>ADDR0</th>
<th>ADDR1</th>
<th>Content</th>
</tr>
<tr>
<td>OUT</td>
<td>x/0 2)</td>
<td>0</td>
<td>(na)</td>
<td>0000</td>
<td>Output configuration</td>
</tr>
<tr>
<td>RCS</td>
<td>1</td>
<td>0</td>
<td>(na)</td>
<td>1000</td>
<td>Restart counter status (read-only)</td>
</tr>
<tr>
<td>SRC</td>
<td>1</td>
<td>0</td>
<td>(na)</td>
<td>1001</td>
<td>Slew Rate Control register (read-only)</td>
</tr>
<tr>
<td>OCR</td>
<td>0</td>
<td>1</td>
<td>00</td>
<td>0100</td>
<td>Overcurrent threshold configuration</td>
</tr>
<tr>
<td>RCD</td>
<td>1</td>
<td>1</td>
<td>00</td>
<td>1100</td>
<td>Restart counter disable</td>
</tr>
<tr>
<td>KRC</td>
<td>0</td>
<td>1</td>
<td>01</td>
<td>0101</td>
<td>KILIS range control</td>
</tr>
<tr>
<td>PCS</td>
<td>1</td>
<td>1</td>
<td>01</td>
<td>1101</td>
<td>Parallel channel and Slew Rate control</td>
</tr>
<tr>
<td>HWCR</td>
<td>0</td>
<td>1</td>
<td>10</td>
<td>0110</td>
<td>Hardware configuration</td>
</tr>
<tr>
<td>ICS</td>
<td>1</td>
<td>1</td>
<td>10</td>
<td>1110</td>
<td>Input status &amp; checksum input</td>
</tr>
<tr>
<td>DCR</td>
<td>☒ x</td>
<td>1</td>
<td>11</td>
<td>x111</td>
<td>Diagnostic configuration and Swap bit</td>
</tr>
</table>

1\) DCR. SWR bit is only changed for write commands. For read commands it is used as part of the read address.

2\) For writing to OUT register DCR . SWR = x, for read address DCR . SWR = 0B.


<table>
<caption>Table 34 Configuration Registers - Write Commands RB-0</caption>
<tr>
<td>Bit</td>
<td></td>
<td>7</td>
<td>6</td>
<td>5</td>
<td>4</td>
<td>3</td>
<td>2</td>
<td>1</td>
<td>0</td>
</tr>
<tr>
<td>Name</td>
<td>SWR</td>
<td>7</td>
<td>RB</td>
<td>5</td>
<td>4</td>
<td>3</td>
<td>2</td>
<td>1</td>
<td>0</td>
</tr>
<tr>
<td>OUT</td>
<td>X ☒</td>
<td>1</td>
<td>0</td>
<td>0</td>
<td>☒ x</td>
<td>OUT . OUTn</td>
<td colspan="2"></td>
<td></td>
</tr>
</table>


<table>
<caption>Table 35 Configuration Registers - Write Commands RB-1</caption>
<tr>
<th>Bit</th>
<th></th>
<th>7</th>
<th>6</th>
<th>5</th>
<th>4</th>
<th>3</th>
<th>2</th>
<th>1</th>
<th>0</th>
</tr>
<tr>
<td>Name</td>
<td>SWR</td>
<td>7</td>
<td>RB</td>
<td colspan="2">ADDR0</td>
<td>3</td>
<td>2</td>
<td>1</td>
<td>0</td>
</tr>
<tr>
<td>OCR</td>
<td>0</td>
<td>1</td>
<td>1</td>
<td>0</td>
<td>0</td>
<td>OCR. OCTn</td>
<td colspan="2"></td>
<td></td>
</tr>
<tr>
<td>RCD</td>
<td>1</td>
<td>1</td>
<td>1</td>
<td>0</td>
<td>0</td>
<td>RCD . RCDn</td>
<td></td>
<td></td>
<td></td>
</tr>
<tr>
<td>KRC</td>
<td>0</td>
<td>1</td>
<td>1</td>
<td>0</td>
<td>1</td>
<td>KRC. KRCn</td>
<td></td>
<td></td>
<td></td>
</tr>
<tr>
<td>PCS</td>
<td>1</td>
<td>1</td>
<td>1</td>
<td>0</td>
<td>1</td>
<td>PCS . PCCn</td>
<td></td>
<td>PCS . CLCS</td>
<td>PCS . SRCS</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="72" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 73" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Serial Peripheral Interface (SPI)


<table>
<caption>Table 35 Configuration Registers - Write Commands RB-1</caption>
<tr>
<th>Bit</th>
<th></th>
<th>7</th>
<th>6</th>
<th>5</th>
<th>4</th>
<th>3</th>
<th>2</th>
<th>1</th>
<th>0</th>
</tr>
<tr>
<td>Name</td>
<td>SWR</td>
<td>7</td>
<td>RB</td>
<td colspan="2">ADDR0</td>
<td>3</td>
<td>2</td>
<td>1</td>
<td>0</td>
</tr>
<tr>
<td>HWCR</td>
<td>0</td>
<td>1</td>
<td>1</td>
<td>1</td>
<td>0</td>
<td>0</td>
<td>HWCR . COL</td>
<td>HWCR . RST</td>
<td>HWCR . CLC</td>
</tr>
<tr>
<td>ICS</td>
<td>1</td>
<td>1</td>
<td>1</td>
<td>1</td>
<td>0</td>
<td>ICS. CSRn 1)</td>
<td></td>
<td></td>
<td></td>
</tr>
<tr>
<td>DCR</td>
<td>X ☒</td>
<td>1</td>
<td>1</td>
<td>1</td>
<td>1</td>
<td>DCR. SWR</td>
<td>DCR . MUX</td>
<td></td>
<td></td>
</tr>
</table>

1\) See Chapter 10.8 for details on checksum calculation.


<table>
<caption>Table 36 Configuration Registers - Read Commands</caption>
<tr>
<th>Bit</th>
<th>7</th>
<th>6</th>
<th>5</th>
<th>4</th>
<th>3</th>
<th>2</th>
<th>1</th>
<th>0</th>
</tr>
<tr>
<th>Name</th>
<th>7</th>
<th>6</th>
<th>5</th>
<th>4</th>
<th></th>
<th colspan="3">ADDR1</th>
</tr>
<tr>
<td>OUT</td>
<td>0</td>
<td>☒</td>
<td>☒</td>
<td>☒</td>
<td>0</td>
<td>0</td>
<td>0</td>
<td>0</td>
</tr>
<tr>
<td>RCS</td>
<td>0</td>
<td>☒</td>
<td>☒</td>
<td>☒</td>
<td>1</td>
<td>0</td>
<td>0</td>
<td>0</td>
</tr>
<tr>
<td>SRC</td>
<td>0</td>
<td>☒</td>
<td>☒</td>
<td>☒</td>
<td>1</td>
<td>0</td>
<td>0</td>
<td>1</td>
</tr>
<tr>
<td>OCR</td>
<td>0</td>
<td>☒</td>
<td>☒</td>
<td>☒</td>
<td>0</td>
<td>1</td>
<td>0</td>
<td>0</td>
</tr>
<tr>
<td>RCD</td>
<td>0</td>
<td>☒</td>
<td>☒</td>
<td>☒</td>
<td>1</td>
<td>1</td>
<td>0</td>
<td>0</td>
</tr>
<tr>
<td>KRC</td>
<td>0</td>
<td>☒</td>
<td>☒</td>
<td>☒</td>
<td>0</td>
<td>1</td>
<td>0</td>
<td>1</td>
</tr>
<tr>
<td>PCS</td>
<td>0</td>
<td>☒</td>
<td>☒</td>
<td>☒</td>
<td>1</td>
<td>1</td>
<td>0</td>
<td>1</td>
</tr>
<tr>
<td>HWCR</td>
<td>0</td>
<td>☒</td>
<td>☒</td>
<td>☒</td>
<td>0</td>
<td>1</td>
<td>1</td>
<td>0</td>
</tr>
<tr>
<td>ICS</td>
<td>0</td>
<td>☒</td>
<td>☒</td>
<td>☒</td>
<td>1</td>
<td>1</td>
<td>1</td>
<td>0</td>
</tr>
<tr>
<td>DCR</td>
<td>0</td>
<td>☒</td>
<td>☒</td>
<td>☒</td>
<td>X ☒</td>
<td>1</td>
<td>1</td>
<td>1</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="73" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 74" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Serial Peripheral Interface (SPI)


<table>
<caption>Table 37 Configuration Registers - Responses</caption>
<tr>
<td>Bit</td>
<td>7</td>
<td>6</td>
<td>5</td>
<td>4</td>
<td>3</td>
<td>2</td>
<td>1</td>
<td>0</td>
<td></td>
</tr>
<tr>
<td>Name</td>
<td>7</td>
<td>6</td>
<td>5</td>
<td>4</td>
<td>3</td>
<td>2</td>
<td>1</td>
<td>0</td>
<td>Default</td>
</tr>
<tr>
<td>OUT</td>
<td>1</td>
<td>0</td>
<td>0</td>
<td>X ☒</td>
<td>OUT . OUTn</td>
<td></td>
<td></td>
<td></td>
<td>80H</td>
</tr>
<tr>
<td>RCS</td>
<td>1</td>
<td>0</td>
<td>0</td>
<td>0</td>
<td>0</td>
<td>RCS . RCSn</td>
<td></td>
<td></td>
<td>80H</td>
</tr>
<tr>
<td>SRC</td>
<td>1</td>
<td>0</td>
<td>0</td>
<td>1</td>
<td>SRC. SRCn</td>
<td></td>
<td></td>
<td></td>
<td>90H</td>
</tr>
<tr>
<td>OCR</td>
<td>1</td>
<td>1</td>
<td>0</td>
<td>0</td>
<td>OCR. OCTn</td>
<td></td>
<td></td>
<td></td>
<td>C0H</td>
</tr>
<tr>
<td>RCD</td>
<td>1</td>
<td>1</td>
<td>0</td>
<td>0</td>
<td>RCD . RCDn</td>
<td></td>
<td></td>
<td></td>
<td>C0H</td>
</tr>
<tr>
<td>KRC</td>
<td>1</td>
<td>1</td>
<td>0</td>
<td>1</td>
<td>KRC. KRCn</td>
<td></td>
<td></td>
<td></td>
<td>D0H</td>
</tr>
<tr>
<td>PCS</td>
<td>1</td>
<td>1</td>
<td>0</td>
<td>1</td>
<td>PCS . PCCn</td>
<td></td>
<td>0</td>
<td>0</td>
<td>D0H</td>
</tr>
<tr>
<td>HWCR</td>
<td>1</td>
<td>1</td>
<td>1</td>
<td>0</td>
<td>0</td>
<td>HWCR . COL</td>
<td>HWCR . SLP</td>
<td>0</td>
<td>E2H</td>
</tr>
<tr>
<td>ICS</td>
<td>1</td>
<td>1</td>
<td>1</td>
<td>0</td>
<td>ICS .INSTn</td>
<td></td>
<td></td>
<td></td>
<td>E0H</td>
</tr>
<tr>
<td>DCR</td>
<td>1</td>
<td>1</td>
<td>1</td>
<td>1</td>
<td>DCR. SWR</td>
<td>DCR . MUX</td>
<td></td>
<td></td>
<td>F7H</td>
</tr>
</table>


<table>
<tr>
<th>Field</th>
<th>Bits</th>
<th>Type</th>
<th>Description</th>
</tr>
<tr>
<td rowspan="3">RB</td>
<td rowspan="3">6</td>
<td rowspan="3">rw</td>
<td>Register Bank</td>
</tr>
<tr>
<td>0B (default) Read/write to OUT/RCS register</td>
</tr>
<tr>
<td>1B Read/write to other registers</td>
</tr>
<tr>
<td rowspan="3">OUT . OUTn n = 3 to 0</td>
<td rowspan="3">3:0</td>
<td rowspan="3">rw</td>
<td>Output Control Register of Channel n</td>
</tr>
<tr>
<td>0B (default) channel is OFF</td>
</tr>
<tr>
<td>1B Channel is ON</td>
</tr>
<tr>
<td rowspan="9">RCS. RCSn n = 2 to 0</td>
<td rowspan="9">2:0</td>
<td rowspan="9">r</td>
<td>Restart Counter Status of Channel selected via MUX</td>
</tr>
<tr>
<td>000B (default) Restart counter value = 0</td>
</tr>
<tr>
<td>001B Restart counter value = 1</td>
</tr>
<tr>
<td>010B Restart counter value = 2</td>
</tr>
<tr>
<td>011B Restart counter value = 3</td>
</tr>
<tr>
<td>100g Restart counter value = 4</td>
</tr>
<tr>
<td>101B Restart counter value = 5</td>
</tr>
<tr>
<td>110g Restart counter value = 6</td>
</tr>
<tr>
<td>111B Restart counter value = 7</td>
</tr>
<tr>
<td rowspan="3">SRC. SRCn n = 3 to 0</td>
<td rowspan="3">3:0</td>
<td rowspan="3">r</td>
<td>Set Slew Rate control for Channel n (read only)</td>
</tr>
<tr>
<td>0B (default) Normal Slew Rate</td>
</tr>
<tr>
<td>1B Adjusted Slew Rate</td>
</tr>
<tr>
<td rowspan="3">OCR. OCTn n = 3 to 0</td>
<td rowspan="3">3:0</td>
<td rowspan="3">rw</td>
<td>Set Overcurrent Level for Channel n</td>
</tr>
<tr>
<td>0B (default) High level of overcurrent threshold /L L(OVLO)</td>
</tr>
<tr>
<td>1B Low level of overcurrent threshold / L(OVL2)</td>
</tr>
<tr>
<td rowspan="3">RCD. RCDn n = 3 to 0</td>
<td rowspan="3">3:0</td>
<td rowspan="3">rw</td>
<td>Set Restart Strategy for Channel n</td>
</tr>
<tr>
<td>0B (default) Automatic restart mode</td>
</tr>
<tr>
<td>1B Latch mode</td>
</tr>
<tr>
<td rowspan="3">KRC. KRCn n = 3 to 0</td>
<td rowspan="3">3:0</td>
<td rowspan="3">rw</td>
<td>Set Current Sense Ratio Range for Channel n</td>
</tr>
<tr>
<td>0B (default) High range of current sense ratio</td>
</tr>
<tr>
<td>1B Low range of current sense ratio</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="74" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 75" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


## Serial Peripheral Interface (SPI)


<table>
<tr>
<th>Field</th>
<th>Bits</th>
<th>Type</th>
<th>Description</th>
</tr>
<tr>
<td rowspan="2">PCS. SRCS</td>
<td rowspan="2">0</td>
<td rowspan="2">w</td>
<td>Set Slew Rate control for Channel selected by DCR . MUX</td>
</tr>
<tr>
<td>0B (default) Normal Slew Rate 1B Adjusted Slew Rate</td>
</tr>
<tr>
<td rowspan="3">PCS. CLCS</td>
<td rowspan="3">1</td>
<td rowspan="3">w</td>
<td>Clear Restart Counters and Latches for Channel selected by DCR . MUX</td>
</tr>
<tr>
<td>0B (default) Restart counters and latches are untouched</td>
</tr>
<tr>
<td>1B Restart counters and latches are reset</td>
</tr>
<tr>
<td rowspan="5">PCS. PCCn n = 1 to 0</td>
<td rowspan="5">3:2</td>
<td rowspan="5">rw</td>
<td>Parallel Channel Configuration</td>
</tr>
<tr>
<td>00B (default) Channels are operating independent</td>
</tr>
<tr>
<td>01B OUT0 + OUT3 are in parallel configuration</td>
</tr>
<tr>
<td>10B OUT1 + OUT2 are in parallel configuration</td>
</tr>
<tr>
<td>11B B OUTO + OUT3 and OUT1 + OUT2 are in parallel configuration</td>
</tr>
<tr>
<td rowspan="3">HWCR. CLC</td>
<td rowspan="3">0</td>
<td rowspan="3">w</td>
<td>Clear Restart Counters and Latches</td>
</tr>
<tr>
<td>0B (default) Restart counters and latches are untouched</td>
</tr>
<tr>
<td>1B Restart counters and latches are reset for all channels</td>
</tr>
<tr>
<td rowspan="3">HWCR. RST</td>
<td rowspan="3">1</td>
<td rowspan="3">w</td>
<td>Reset Command</td>
</tr>
<tr>
<td>0B (default) Normal operation</td>
</tr>
<tr>
<td>1B Execute reset command</td>
</tr>
<tr>
<td rowspan="3">HWCR. SLP</td>
<td rowspan="3">1</td>
<td rowspan="3">r</td>
<td>Sleep Mode</td>
</tr>
<tr>
<td>0B Device is awake</td>
</tr>
<tr>
<td>1B (default) DCR . MUX = 111B</td>
</tr>
<tr>
<td>HWCR. COL</td>
<td>2</td>
<td>rw</td>
<td>Input Combinatorial Logic Configuration 0B (default) Input signal OR-combined with according OUT register bit1) 1B Input signal AND-combined with according OUT register bit</td>
</tr>
<tr>
<td rowspan="2">ICS. CSRn n = 3 to 0</td>
<td rowspan="2">3:0</td>
<td rowspan="2">w</td>
<td>Checksum Input Register</td>
</tr>
<tr>
<td>4 bit Checksum is written to this register</td>
</tr>
<tr>
<td rowspan="2">ICS.INSTn n = 3 to 0</td>
<td rowspan="2">3:0</td>
<td rowspan="2">r</td>
<td>Input Status Monitor Channel n 0B (default) Input signal is "low"</td>
</tr>
<tr>
<td>1B Input signal is "high"</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="75" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 76" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


## Serial Peripheral Interface (SPI)


<table>
<tr>
<th>Field</th>
<th>Bits</th>
<th>Type</th>
<th>Description</th>
</tr>
<tr>
<td rowspan="16">DCR. MUX</td>
<td rowspan="16">2:0</td>
<td rowspan="16">rw</td>
<td>Set Current Sense Multiplexer Configuration in OFF state 000g IS pin is "high impedance"</td>
</tr>
<tr>
<td>001B IS pin is "high impedance" 010g IS pin is "high impedance"</td>
</tr>
<tr>
<td>011B IS pin is "high impedance"</td>
</tr>
<tr>
<td>100g IS pin is "high impedance"</td>
</tr>
<tr>
<td>101B Current sense verification mode</td>
</tr>
<tr>
<td>110g IS pin is "high impedance"</td>
</tr>
<tr>
<td>111B Sleep mode (IS pin is "high impedance")</td>
</tr>
<tr>
<td>Set Multiplexer Configuration in ON state</td>
</tr>
<tr>
<td>000g Current sense of channel 0 is routed to IS pin</td>
</tr>
<tr>
<td>001B Current sense of channel 1 is routed to IS pin</td>
</tr>
<tr>
<td>010B Current sense of channel 2 is routed to IS pin</td>
</tr>
<tr>
<td>011B Current sense of channel 3 is routed to IS pin</td>
</tr>
<tr>
<td>100g IS pin is "high impedance"</td>
</tr>
<tr>
<td>101B Current sense verification mode</td>
</tr>
<tr>
<td>110g IS pin is "high impedance"</td>
</tr>
<tr>
<td>111B Sleep mode (IS pin is "high impedance")</td>
</tr>
<tr>
<td rowspan="3">DCR.SWR</td>
<td rowspan="3">3</td>
<td rowspan="3">rw</td>
<td>Switch Register</td>
</tr>
<tr>
<td>0B (default) Registers OUT, OCR, KRC, HWCR and DCR can be written</td>
</tr>
<tr>
<td>1B B Registers OUT, RCD, PCS, ICS and DCR can be written</td>
</tr>
</table>

1\) In Limp Home mode (LHI pin set to "high") the combinatorial logic is switched to OR-mode.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="76" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 77" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Serial Peripheral Interface (SPI)


### 10.8 SPI Checksum Verification

BTS72220-4ESA offers a simple parity check to identify unexpected content or unintended changes of
configuration registers. For the checksum calculation a subset of the configuration bits is used, which is
expected not to be changed periodically. The checksum calculation is an easy column parity calculation. The
configuration bits which are used for the calculation are shown in Table 39. The SPI master writes the result
to ICS . CSRn. After the 4bit checksum is written to ICS register, the device is doing once the comparison and
the result can be read within the next STDDIAG frame in the bit STDDIAG. CSV. The STDDIAG . CSV bit is
cleared with the next STDDIAG readout. In case the ICS register is not written, the checksum comparison is
disabled and the bit STDDIAG . CSV = 0B. If Limp Home mode is entered after ICS . CSRn is written but before
STDDIAG. CSV is read, the checksum verification is not valid. Same applies in case STDDIAG. TER and
STDDIAG. VSMON are set to 1B. In these cases checksum verification result shall be discarded.


<table>
<caption>Table 38 Conventions for parity calculation</caption>
<tr>
<th>Number of '1' in a column</th>
<th>Result with EVEN-parity</th>
<th>Result with ODD-parity</th>
</tr>
<tr>
<td>EVEN</td>
<td>0</td>
<td>1</td>
</tr>
<tr>
<td>ODD</td>
<td>1</td>
<td>0</td>
</tr>
</table>


<table>
<caption>Table 39 Checksum calculation bit matrix</caption>
<tr>
<td>Name</td>
<td>3</td>
<td>2</td>
<td>1</td>
<td>0</td>
</tr>
<tr>
<td>OCR</td>
<td>OCT3</td>
<td>OCT2</td>
<td>OCT1</td>
<td>OCT0</td>
</tr>
<tr>
<td>RCD</td>
<td>RCD3</td>
<td>RCD2</td>
<td>RCD1</td>
<td>RCD0</td>
</tr>
<tr>
<td>KRC</td>
<td>KRC3</td>
<td>KRC2</td>
<td>KRC1</td>
<td>KRC0</td>
</tr>
<tr>
<td>SRC</td>
<td>SRC3</td>
<td>SRC2</td>
<td>SRC1</td>
<td>SRC0</td>
</tr>
<tr>
<td>HWCR/PCS</td>
<td>0</td>
<td>COL</td>
<td>PCC</td>
<td>PCC0</td>
</tr>
<tr>
<td>Parity</td>
<td>even</td>
<td>odd</td>
<td>even</td>
<td>odd</td>
</tr>
<tr>
<td>ICS</td>
<td>CSR3</td>
<td>CSR2</td>
<td>CSR1</td>
<td>CSR0</td>
</tr>
</table>


<table>
<caption>Table 40 Checksum calculation bit matrix example</caption>
<tr>
<td>Name</td>
<td>3</td>
<td>2</td>
<td>1</td>
<td>0</td>
</tr>
<tr>
<td>OCR</td>
<td>0</td>
<td>1</td>
<td>0</td>
<td>0</td>
</tr>
<tr>
<td>RCD</td>
<td>1</td>
<td>0</td>
<td>0</td>
<td>0</td>
</tr>
<tr>
<td>KRC</td>
<td>0</td>
<td>1</td>
<td>1</td>
<td>0</td>
</tr>
<tr>
<td>SRC</td>
<td>0</td>
<td>0</td>
<td>1</td>
<td>0</td>
</tr>
<tr>
<td>HWCR/PCS</td>
<td>0</td>
<td>0</td>
<td>0</td>
<td>0</td>
</tr>
<tr>
<td>Parity</td>
<td>even</td>
<td>odd</td>
<td>even</td>
<td>odd</td>
</tr>
<tr>
<td>ICS</td>
<td>1</td>
<td>1</td>
<td>0</td>
<td>1</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="77" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 78" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->

Serial Peripheral Interface (SPI)


# 10.9 SPI command quick list

A summary of the most used SPI commands (read and write operations) is shown in Table 154.


<table>
<caption>Table 41 SPI command quick list</caption>
<tr>
<th>Name</th>
<th>"read" command 1)</th>
<th>"write" command 2)</th>
<th>SWR 3)</th>
</tr>
<tr>
<td>OUT</td>
<td>0xxx0000B</td>
<td>10ddddddB</td>
<td>x ☒</td>
</tr>
<tr>
<td>RCS</td>
<td>0xxx1000B</td>
<td></td>
<td></td>
</tr>
<tr>
<td>SRC</td>
<td>0xxx1001B</td>
<td></td>
<td></td>
</tr>
<tr>
<td>OCR</td>
<td>0xxx0100B</td>
<td>1100ddddB</td>
<td>0</td>
</tr>
<tr>
<td>RCD</td>
<td>0xxx1100B</td>
<td>1100ddddB</td>
<td>1</td>
</tr>
<tr>
<td>KRC</td>
<td>0xxx0101B</td>
<td>1101ddddB</td>
<td>0</td>
</tr>
<tr>
<td>PCS</td>
<td>0xxx1101B</td>
<td>1101ddddB</td>
<td>1</td>
</tr>
<tr>
<td>HWCR</td>
<td>0xxx0110B</td>
<td>1110ddddB</td>
<td>0</td>
</tr>
<tr>
<td>ICS</td>
<td>0xxx1110B</td>
<td>1110ddddB</td>
<td>1</td>
</tr>
<tr>
<td>DCR</td>
<td>0xxxx111B</td>
<td>1111ddddB</td>
<td>x ☒</td>
</tr>
<tr>
<td colspan="4"></td>
</tr>
<tr>
<td>WRNDIAG</td>
<td>0xxx0001B</td>
<td></td>
<td></td>
</tr>
<tr>
<td>STDDIAG</td>
<td>0xxx0010B</td>
<td></td>
<td></td>
</tr>
<tr>
<td>ERRDIAG</td>
<td>0xxx0011B</td>
<td></td>
<td></td>
</tr>
</table>

1\) x = don't care bits.

2\) d = data bits.

3\) DCR. SWR bit needs to be set for writing a register. For reading a register the DCR . SWR bit is part of the read address.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="78" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 79" -->


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


<figure>

Infineon

</figure>


# Application Information


## 11 Application Information

Note:
The following information is given as a hint for the implementation of the device only and shall not
be regarded as a description or warranty of a certain functionality, condition or quality of the device.


### 11.1 Application setup - SPOC™


<figure>
<figcaption>Figure 46 Application Diagram</figcaption>

VBAT

Optional

ZWIRE

Fail-safe
Control

Optional

Logic Supply

Cvs1

CVSGND

RI

RGND

T1

CVDD

RVDO

VDD

GND

VS

ROL

VDD

GPIO

RIN

IN0

GPIO

RIN

IN1

OUT0

GPIO

Microcontroller

RIN

IN2

OUT1

GPIO

RIN

IN3

SPOC™ +2

OUT2

RPD

RLHI

LHI

Dz2

CSN

RCSN

CSN

OUT3

Cvs2

SCLK

RSCLK

SCLK

MISO

Rso

SO

ZWIRE

ZWIRE

MOS

RSI

SI

VSS

ADC

RADE

RIS PROT

IS

COUT

COUT

ZLOAD*

ZLOAD*

CADC

Dz1

RSENSE

COUT

COUT

Logic GND

Optional

Application_dich_nalDamit

Power GND

*See Chapter 1 „Potential Applications“
** See Chapter 11.2 „External Components“

Chassis GND

</figure>

Note:
This is a very simplified example of an application circuit. The function must be verified in the real
application.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="79" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 80" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Application Information


## 11.2 External Components


<table>
<caption>Table 42 Suggested Component values</caption>
<tr>
<th>Reference</th>
<th>Value</th>
<th>Purpose</th>
</tr>
<tr>
<td>RVDD</td>
<td>470 02</td>
<td>Device logic protection</td>
</tr>
<tr>
<td>RIN</td>
<td>4.7 kQ</td>
<td>Protection of the microcontroller during overvoltage, reverse polarity Guarantee BTS72220-4ESA output OFF during Loss of Ground</td>
</tr>
<tr>
<td>RIS_PROT</td>
<td>4.7 kQ</td>
<td>Protection resistor for overvoltage, reverse polarity and Loss of Ground Value to be tuned with uC specification</td>
</tr>
<tr>
<td>RSENSE</td>
<td>1.2 kQ</td>
<td>Sense resistor</td>
</tr>
<tr>
<td>RADC</td>
<td>4.7 kQ2</td>
<td>uC-ADC voltage spikes filtering</td>
</tr>
<tr>
<td>RCSN</td>
<td>1.2 kQ</td>
<td>Protection of the uC during overvoltage and reverse polarity</td>
</tr>
<tr>
<td>RSCLK</td>
<td>1.2 kΩ</td>
<td>Protection of the uC during overvoltage and reverse polarity</td>
</tr>
<tr>
<td>Rso</td>
<td>1.2 kQ</td>
<td>Protection of the uC during overvoltage and reverse polarity</td>
</tr>
<tr>
<td>RSI</td>
<td>1.2 kΩ</td>
<td>Protection of the uC during overvoltage and reverse polarity</td>
</tr>
<tr>
<td>RLHI</td>
<td>4.7 kQ</td>
<td>Protection of the uC during overvoltage and reverse polarity</td>
</tr>
<tr>
<td>CADC</td>
<td>220 pF</td>
<td>uC-ADC voltage spikes filtering A time constant (RADC * CADC) longer than 1 us is recommended</td>
</tr>
<tr>
<td>CVD</td>
<td>470 nF</td>
<td>Digital supply voltage spikes filtering and for improved robustness against battery voltage transients</td>
</tr>
<tr>
<td>CVS1</td>
<td>100 nF</td>
<td>Battery voltage spikes filtering</td>
</tr>
<tr>
<td>Cvs2</td>
<td>-</td>
<td>Filtering / buffer capacitor located at VBAT connector</td>
</tr>
<tr>
<td>CVSGND</td>
<td>22 nF</td>
<td>Battery voltage spikes filtering</td>
</tr>
<tr>
<td>COUT</td>
<td>10 nF</td>
<td>For improved electromagnetic compatibility (EMC)</td>
</tr>
<tr>
<td>RGND</td>
<td>47.02</td>
<td>Ground voltage spikes filtering for improved robustness against battery voltage transients</td>
</tr>
<tr>
<td>T1</td>
<td>BC 807</td>
<td>Switch the battery voltage for Open Load in OFF diagnosis</td>
</tr>
<tr>
<td>RPD</td>
<td>47 kQ</td>
<td>Output polarization (pull-down) Ensure polarization of BTS72220-4ESA output to distinguish between Open Load and Short to Vs in OFF diagnosis</td>
</tr>
<tr>
<td>ROL</td>
<td>1.5 kQ</td>
<td>Output polarization (pull-up) Ensure polarization of BTS72220-4ESA output during Open Load in OFF diagnosis</td>
</tr>
</table>

Note:
The suggested component values above are determined for typical applications with 5 V
microcontrollers. Based on the application circuit and the used components connected to
BTS72220-4ESA, it could be necessary to adjust the recommended values to stay below the
maximum ratings for all components under all operating conditions (e.g. reverse battery, transients
on battery, etc.).


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="80" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 81" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Application Information


## 11.3 Further Application Information

. Please contact us for information regarding the Pin FMEA

· For further information you may contact http://www.infineon.com/

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="81" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 82" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Package Outlines


## 12 Package Outlines


<figure>
<figcaption>Figure 47 PG-TSDSO-24 (Thin (Slim) Dual Small Outline 24 pins) Package drawing</figcaption>

(0.95)

0.05±0.05

STANDOFF

1\)

1.15 MAX.

8.65±0.1

1\)

D

3.9±0.1

0.1

2x

(0.2)

GAUGE

0.1

PLANE

2x

0.25

8

C

0.08

C

0.67+0.25

SEATING COPLANARITY
PLANE

24x

0

6±0.2

0.2

D

24x

0.25±0.05

2\)

0

0.25

M

A-B
C

24x

BOTTOM VIEW

2.77±0.1

A

0

0.15M

D

3\)

(0.05)

24

13

13

24

INDEX

1

12

12

1

MARKING

B

6.4±0.1

0.65

0

0.15
M

A-B

1\) DOES NOT INCLUDE PLASTIC OR METAL PROTRUSION OF 0.15 MAX. PER SIDE

2\) DAMBAR PROTUSION SHALL BE MAXIMUM 0.1MM TOTAL IN EXCESS OF LEAD WIDTH

3\) DISTANCE FROM CENERLINE EXPOSED PAD TO PACKAGE CENTERLINE
ALL DIMENSIONS ARE IN UNITS MM

THE DRAWING IS IN COMPLIANCE WITH ISO 128 & PROJECTION METHOD 1[

@
]

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="82" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 83" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Package Outlines


<figure>
<figcaption>Figure 48 PG-TSDSO-24 (Thin (Slim) Dual Small Outline 24 pins) Package pads and stencil</figcaption>

0.65

0.325

0.45

0.65

0.325

0.45

1.31

1.31

2.855

2.855

2.77

2.57

2.855

0.05

0.05

2.855

6.4

2.9

1.65

copper

solder mask

stencil apertures

ALL DIMENSIONS ARE IN UNITS MM

</figure>


# Green Product (RoHS compliant)

To meet the world-wide customer requirements for environmentally friendly products and to be compliant
with government regulations the device is available as a green product. Green products are RoHS-Compliant
(i.e Pb-free finish on leads and suitable for Pb-free soldering according to IPC/JEDEC J-STD-020).


# Further information on packages

https://www.infineon.com/packages

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="83" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 84" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->
<!-- PageHeader="Revision History" -->


## 13 Revision History


<table>
<caption>Table 43 BTS72220-4ESA - List of changes</caption>
<tr>
<th>Revision</th>
<th>Changes</th>
</tr>
<tr>
<td>1.10, 2021-03-23</td>
<td>General: Datasheet quality improved General: updated (ReverSave™ &gt; ReverseON) General: updated (channel description) Icon "PRO-SIL™ ISO 26262-ready" added to front page Chapter 1 updated (Package description) Chapter 1 updated (Potential Applications updated and Product Validation added) Harmonization of Application Diagram (Figure 1, Figure 46) P_4.4.0.4, P_4.4.0.5 updated (Typ. value and Max. value) P_6.4.0.10 updated (Note or Test Condition) P_6.4.1.5 updated (Max. value updated and footnote added) P_6.5.30.2 added P_9.6.0.6 updated parameter name P_9.6.0.17 added P_9.6.2.11 footnote removed Figure 14 and Figure 16 updated Figure 28 and Figure 29 updated Figure 33 updated Figure 37 and Figure 38 updated Chapter 10.4 typical value for VDD harmonized Chapter 11 updated (figures and descriptions)</td>
</tr>
<tr>
<td>1.00, 2018-06-11</td>
<td>Data Sheet available</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="84" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 85" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Table of Contents


## Table of Contents


<table>
<tr>
<td>1</td>
<td>Overview</td>
<td>1</td>
</tr>
<tr>
<td>2</td>
<td>Block Diagram and Terms</td>
<td>4</td>
</tr>
<tr>
<td>2.1</td>
<td>Block Diagram</td>
<td>4</td>
</tr>
<tr>
<td>2.2</td>
<td>Terms</td>
<td>5</td>
</tr>
<tr>
<td>3</td>
<td>Pin Configuration</td>
<td>6</td>
</tr>
<tr>
<td>3.1</td>
<td>Pin Assignment</td>
<td>6</td>
</tr>
<tr>
<td>3.2</td>
<td>Pin Definitions and Functions</td>
<td>7</td>
</tr>
<tr>
<td>4</td>
<td>General Product Characteristics</td>
<td>8</td>
</tr>
<tr>
<td>4.1</td>
<td>Absolute Maximum Ratings - General</td>
<td>8</td>
</tr>
<tr>
<td>4.2</td>
<td>Absolute Maximum Ratings - Power Stages</td>
<td>10</td>
</tr>
<tr>
<td>4.2.1</td>
<td>Power Stages - 5.5 m22 channels</td>
<td>10</td>
</tr>
<tr>
<td>4.2.2</td>
<td>Power Stages - 13.5 m22 channels</td>
<td>10</td>
</tr>
<tr>
<td>4.3</td>
<td>Functional Range</td>
<td>11</td>
</tr>
<tr>
<td>4.4</td>
<td>Thermal Resistance</td>
<td>11</td>
</tr>
<tr>
<td>4.4.1</td>
<td>PCB Setup</td>
<td>12</td>
</tr>
<tr>
<td>4.4.2</td>
<td>Thermal Impedance</td>
<td>13</td>
</tr>
<tr>
<td>5</td>
<td>Logic Pins</td>
<td>14</td>
</tr>
<tr>
<td>5.1</td>
<td>Input Pins (INn)</td>
<td>14</td>
</tr>
<tr>
<td>5.2</td>
<td>Advanced Features Pins</td>
<td>16</td>
</tr>
<tr>
<td>5.2.1</td>
<td>SPI Pins</td>
<td>16</td>
</tr>
<tr>
<td>5.2.2</td>
<td>Limp Home Input (LHI) Pin</td>
<td>16</td>
</tr>
<tr>
<td>5.3</td>
<td>Electrical Characteristics Logic Pins</td>
<td>17</td>
</tr>
<tr>
<td>5.4</td>
<td>Electrical Characteristics Logic Pins - Advanced Features</td>
<td>17</td>
</tr>
<tr>
<td>6</td>
<td>Power Supply</td>
<td>20</td>
</tr>
<tr>
<td>6.1</td>
<td>Operation Modes</td>
<td>21</td>
</tr>
<tr>
<td>6.1.1</td>
<td>Unsupplied</td>
<td>23</td>
</tr>
<tr>
<td>6.1.2</td>
<td>Power-up</td>
<td>23</td>
</tr>
<tr>
<td>6.1.3</td>
<td>Sleep mode</td>
<td>23</td>
</tr>
<tr>
<td>6.1.4</td>
<td>Stand-by mode</td>
<td>23</td>
</tr>
<tr>
<td>6.1.5</td>
<td>Ready mode</td>
<td>23</td>
</tr>
<tr>
<td>6.1.6</td>
<td>Active mode</td>
<td>23</td>
</tr>
<tr>
<td>6.1.7</td>
<td>Limp Home mode</td>
<td>23</td>
</tr>
<tr>
<td>6.1.8</td>
<td>Limp Home Active mode</td>
<td>24</td>
</tr>
<tr>
<td>6.1.9</td>
<td>Definition of Operation modes transition times</td>
<td>25</td>
</tr>
<tr>
<td>6.2</td>
<td>Undervoltage on Vs</td>
<td>25</td>
</tr>
<tr>
<td>6.3</td>
<td>Reset Condition</td>
<td>26</td>
</tr>
<tr>
<td>6.4</td>
<td>Electrical Characteristics Power Supply</td>
<td>27</td>
</tr>
<tr>
<td>6.4.1</td>
<td>Electrical Characteristics Power Supply - SPOC™</td>
<td>28</td>
</tr>
<tr>
<td>6.5</td>
<td>Electrical Characteristics Power Supply - Product Specific</td>
<td>29</td>
</tr>
<tr>
<td>6.5.1</td>
<td>BTS72220-4ESA</td>
<td>29</td>
</tr>
<tr>
<td>7</td>
<td>Power Stages</td>
<td>31</td>
</tr>
<tr>
<td>7.1</td>
<td>Output ON-State Resistance</td>
<td>31</td>
</tr>
<tr>
<td>7.2</td>
<td>Switching loads</td>
<td>31</td>
</tr>
<tr>
<td>7.2.1</td>
<td>Switching Resistive Loads</td>
<td>31</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="85" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 86" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Table of Contents


<table>
<tr>
<td>7.2.2</td>
<td>Switching Inductive Loads</td>
<td>32</td>
</tr>
<tr>
<td>7.2.3</td>
<td>Output Voltage Limitation</td>
<td>33</td>
</tr>
<tr>
<td>7.2.4</td>
<td>Switching Capacitive Loads</td>
<td>33</td>
</tr>
<tr>
<td>7.3</td>
<td>Advanced Switching Characteristics</td>
<td>34</td>
</tr>
<tr>
<td>7.3.1</td>
<td>Inverse Current behavior</td>
<td>34</td>
</tr>
<tr>
<td>7.3.2</td>
<td>Switching Channels in Parallel</td>
<td>35</td>
</tr>
<tr>
<td>7.3.3</td>
<td>Cross Current robustness with H-Bridge configuration</td>
<td>36</td>
</tr>
<tr>
<td>7.4</td>
<td>Electrical Characteristics Power Stages</td>
<td>37</td>
</tr>
<tr>
<td>7.4.1</td>
<td>Electrical Characteristics Power Stages - SPOC™</td>
<td>37</td>
</tr>
<tr>
<td>7.5</td>
<td>Electrical Characteristics - Power Output Stages</td>
<td>39</td>
</tr>
<tr>
<td>7.5.1</td>
<td>Power Output Stage - 5.5 ml2</td>
<td>39</td>
</tr>
<tr>
<td>7.5.2</td>
<td>Power Output Stage - 13.5 ml2</td>
<td>40</td>
</tr>
<tr>
<td>8</td>
<td>Protection</td>
<td>43</td>
</tr>
<tr>
<td>8.1</td>
<td>Overtemperature Protection</td>
<td>43</td>
</tr>
<tr>
<td>8.2</td>
<td>Overload Protection</td>
<td>45</td>
</tr>
<tr>
<td>8.3</td>
<td>Protection and Diagnosis in case of Fault</td>
<td>45</td>
</tr>
<tr>
<td>8.3.1</td>
<td>Restart Strategy</td>
<td>46</td>
</tr>
<tr>
<td>8.4</td>
<td>Additional protections</td>
<td>47</td>
</tr>
<tr>
<td>8.4.1</td>
<td>Reverse Polarity Protection</td>
<td>47</td>
</tr>
<tr>
<td>8.4.2</td>
<td>Overvoltage Protection</td>
<td>48</td>
</tr>
<tr>
<td>8.5</td>
<td>Protection against loss of connection</td>
<td>49</td>
</tr>
<tr>
<td>8.5.1</td>
<td>Loss of Battery and Loss of Load</td>
<td>49</td>
</tr>
<tr>
<td>8.5.2</td>
<td>Loss of Ground</td>
<td>49</td>
</tr>
<tr>
<td>8.6</td>
<td>Electrical Characteristics Protection</td>
<td>50</td>
</tr>
<tr>
<td>8.6.1</td>
<td>Electrical Characteristics Protection - SPOC™</td>
<td>50</td>
</tr>
<tr>
<td>8.7</td>
<td>Electrical Characteristics Protection - Power Output Stages</td>
<td>51</td>
</tr>
<tr>
<td>8.7.1</td>
<td>Protection Power Output Stage - 5.5 ml2</td>
<td>51</td>
</tr>
<tr>
<td>8.7.2</td>
<td>Protection Power Output Stage - 13.5 ml2</td>
<td>52</td>
</tr>
<tr>
<td>9</td>
<td>Diagnosis</td>
<td>53</td>
</tr>
<tr>
<td>9.1</td>
<td>Overview</td>
<td>54</td>
</tr>
<tr>
<td>9.2</td>
<td>Diagnosis Word at SPI</td>
<td>55</td>
</tr>
<tr>
<td>9.3</td>
<td>Diagnosis in ON state</td>
<td>55</td>
</tr>
<tr>
<td>9.3.1</td>
<td>Current Sense (KILIS)</td>
<td>55</td>
</tr>
<tr>
<td>9.3.2</td>
<td>Current Sense Multiplexer</td>
<td>56</td>
</tr>
<tr>
<td>9.4</td>
<td>Diagnosis in OFF state</td>
<td>57</td>
</tr>
<tr>
<td>9.4.1</td>
<td>Switch Bypass Monitor</td>
<td>57</td>
</tr>
<tr>
<td>9.5</td>
<td>SENSE Timings</td>
<td>57</td>
</tr>
<tr>
<td>9.6</td>
<td>Electrical Characteristics Diagnosis</td>
<td>58</td>
</tr>
<tr>
<td>9.6.1</td>
<td>Electrical Characteristics Diagnosis - SPOC™</td>
<td>59</td>
</tr>
<tr>
<td>9.7</td>
<td>Electrical Characteristics Diagnosis - Power Output Stages</td>
<td>60</td>
</tr>
<tr>
<td>9.7.1</td>
<td>Diagnosis Power Output Stage - 5.5 ml2</td>
<td>60</td>
</tr>
<tr>
<td>9.7.2</td>
<td>Diagnosis Power Output Stage - 13.5 ml2</td>
<td>62</td>
</tr>
<tr>
<td>10</td>
<td>Serial Peripheral Interface (SPI)</td>
<td>64</td>
</tr>
<tr>
<td>10.1</td>
<td>SPI Signal Description</td>
<td>64</td>
</tr>
<tr>
<td>10.2</td>
<td>Daisy Chain Capability</td>
<td>65</td>
</tr>
<tr>
<td>10.3</td>
<td>Timing Diagrams</td>
<td>66</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="86" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 87" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS72220-4ESA SPOC™ +2" -->


# Table of Contents


<table>
<tr>
<td>10.4</td>
<td>Electrical Characteristics</td>
<td>67</td>
</tr>
<tr>
<td>10.5</td>
<td>SPI Protocol</td>
<td>68</td>
</tr>
<tr>
<td>10.6</td>
<td>SPI Diagnosis Registers</td>
<td>71</td>
</tr>
<tr>
<td>10.6.1</td>
<td>Diagnosis Registers - Read Commands</td>
<td>71</td>
</tr>
<tr>
<td>10.6.2</td>
<td>Diagnosis Registers - Responses</td>
<td>71</td>
</tr>
<tr>
<td>10.7</td>
<td>SPI Configuration Registers</td>
<td>72</td>
</tr>
<tr>
<td>10.8</td>
<td>SPI Checksum Verification</td>
<td>77</td>
</tr>
<tr>
<td>10.9</td>
<td>SPI command quick list</td>
<td>78</td>
</tr>
<tr>
<td>11</td>
<td>Application Information</td>
<td>79</td>
</tr>
<tr>
<td>11.1</td>
<td>Application setup - SPOC™</td>
<td>79</td>
</tr>
<tr>
<td>11.2</td>
<td>External Components</td>
<td>80</td>
</tr>
<tr>
<td>11.3</td>
<td>Further Application Information</td>
<td>81</td>
</tr>
<tr>
<td>12</td>
<td>Package Outlines</td>
<td>82</td>
</tr>
<tr>
<td>13</td>
<td>Revision History</td>
<td>84</td>
</tr>
<tr>
<td></td>
<td>Table of Contents</td>
<td>85</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="87" -->
<!-- PageFooter="Rev. 1.10 2021-03-23" -->
<!-- PageBreak -->



<!-- PageNumber="Side 88" -->


Trademarks

All referenced product or service names and trademarks are the property of their respective owners.

Edition 2021-03-23
Published by
Infineon Technologies AG
81726 Munich, Germany

@ 2021 Infineon Technologies AG.
All Rights Reserved.

Do you have a question about any
aspect of this document?
Email: erratum@infineon.com

Document reference
Z8F65320941


## IMPORTANT NOTICE

The information given in this document shall in no
event be regarded as a guarantee of conditions or
characteristics ("Beschaffenheitsgarantie").

With respect to any examples, hints or any typical
values stated herein and/or any information regarding
the application of the product, Infineon Technologies
hereby disclaims any and all warranties and liabilities
of any kind, including without limitation warranties of
non-infringement of intellectual property rights of any
third party.

In addition, any information given in this document is
subject to customer's compliance with its obligations
stated in this document and any applicable legal
requirements, norms and standards concerning
customer's products and any use of the product of
Infineon Technologies in customer's applications.

The data contained in this document is exclusively
intended for technically trained staff. It is the
responsibility of customer's technical departments to
evaluate the suitability of the product for the intended
application and the completeness of the product
information given in this document with respect to
such application.

For further information on technology, delivery terms
and conditions and prices, please contact the nearest
Infineon Technologies Office (www.infineon.com).


# WARNINGS

Due to technical requirements products may contain
dangerous substances. For information on the types
in question please contact your nearest Infineon
Technologies office.

Except as otherwise explicitly approved by Infineon
Technologies in a written document signed by
authorized representatives of Infineon Technologies,
Infineon Technologies' products may not be used in
any applications where a failure of the product or any
consequences of the use thereof can reasonably be
expected to result in personal injury.
