

<!-- PageNumber="Side 1" -->


<figure>

infineon

</figure>


BTS7004-1EPP

PROFET™+2 12V
Smart High-Side Power Switch


<figure>

O
Qualified

AEC

·

V

RoHS

</figure>


# 1 Overview


## Potential Applications

· Suitable for driving 15 A resistive, inductive and capacitive loads

· Replaces electromechanical relays, fuses and discrete circuits

· Suitable for driving glow plug, heating loads, DC motor and for power
distribution


## 1x 4.4 ml2


<table>
<tr>
<td>Package</td>
<td>PG-TSDSO-14</td>
</tr>
<tr>
<td>Marking</td>
<td>7004-1P</td>
</tr>
</table>


<figure>

JA
Infineon
TSDSO-14

</figure>


<figure>
<figcaption>Figure 1 BTS7004-1EPP Application Diagram. Further information in Chapter 10</figcaption>

VBAT

ZWIRE

Optional

Optional

Cvs

CVSGND

T1

Logic Supply

J

RGND

VDD

GND

VS

GPIO

RIN

IN

ROL

GPIO

RDEN

DEN

OUT

PROFET™+2
12V

RPD

COUT0

Dz2

Cvs2

Microcontroller

ZWIRE

ADC

RADE

RIS PROT

IS

VSS

CSENSE

DZ1

RSENSE

ZLOAD*

Logic GND

Power GND

Optional

Chassis GND

*See Chapter 1 „Potential Applications“

App_CM_JNTDIO_CVG.ent

</figure>


<!-- PageFooter="Data Sheet www.infineon.com" -->
<!-- PageNumber="1" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 2" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


### Overview


#### Basic Features

· High-Side Switch with Diagnosis and Embedded Protection

· Part of PROFET™+2 12V Family

· ReverseON for low power dissipation in Reverse Polarity

· Green Product (RoHS compliant)


#### Protection Features

· Absolute and dynamic temperature limitation with controlled reactivation

· Overcurrent protection (tripping) with Intelligent Latch

· Undervoltage shutdown

· Overvoltage protection with external components (as shown in Figure 37)


#### Diagnostic Features

· Proportional load current sense

· Open Load in ON and OFF state

· Short circuit to ground and battery


#### Product Validation

Qualified for automotive applications. Product validation according to AEC-Q100 Grade 1.


#### Description

The BTS7004-1EPP is a Smart High-Side Power Switch, providing protection functions and diagnosis.


<table>
<caption>Table 1 Product Summary</caption>
<tr>
<th>Parameter</th>
<th>Symbol</th>
<th>Values</th>
</tr>
<tr>
<td>Minimum Operating voltage</td>
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
<td>Minimum Overvoltage protection (T) ≥ 25 ℃)</td>
<td>VDS(CLAMP)_25</td>
<td>35 V</td>
</tr>
<tr>
<td>Maximum current in OFF mode (T) ≤ 85 ℃)</td>
<td>"VS(OFF)_85</td>
<td>0.5 µA</td>
</tr>
<tr>
<td>Maximum operative current</td>
<td>İGND(ON_D)</td>
<td>3 mA</td>
</tr>
<tr>
<td>Typical ON-state resistance (T) = 25 ℃)</td>
<td>RDS(ON)_25</td>
<td>4.4 m22</td>
</tr>
<tr>
<td>Maximum ON-state resistance (T) = 150 ℃)</td>
<td>RDS(ON)_150</td>
<td>8 m22</td>
</tr>
<tr>
<td>Nominal load current (TA = 85 ℃)</td>
<td>IL(NOM)</td>
<td>15 A</td>
</tr>
<tr>
<td>Minimum overload detection current</td>
<td>IL(OVL0)_-40</td>
<td>107 A</td>
</tr>
<tr>
<td>Typical current sense ratio at /L = IL(NOM)</td>
<td>KILIS</td>
<td>20000</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="2" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 3" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


## Block Diagram and Terms


### 2 Block Diagram and Terms


#### 2.1 Block Diagram


<figure>
<figcaption>Figure 2 Block Diagram of BTS7004-1EPP</figcaption>

VS

Supply Voltage
Monitoring

Overvoltage
Protection

Internal Power Supply

Channel

Intelligent Restart
Control

Voltage Sensor

Overtemperature

T

Overvoltage
Clamping

IS

SENSE Output

Driver
Logic

Gate Control
+
Chargepump

Overcurrent
Protection

IN

ESD
Protection
+
Input Logic

ReverseON
InverseON

OUT

DEN

Load Current Sense

Output Voltage Limitation

Internal Reverse
Polarity Protection

GND Circuitry

GND

Block_HEAT1ch.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="3" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 4" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


## Block Diagram and Terms


### 2.2 Terms

Figure 3 shows all terms used in this data sheet, with associated convention for positive values.


<figure>
<figcaption>Figure 3 Voltage and Current Convention</figcaption>

Ivs

☒

VsIs

VS

/IN

☒
IN

VDS

/DEN

☒
DEN

IL

Vs

OUT
☒

VIN

VDEN

/Is

☒
IS

VOUT

GND

VIS

☒

IGND

Terms_1CH.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="4" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 5" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


Pin Configuration


# 3 Pin Configuration


## 3.1 Pin Assignment


<figure>
<figcaption>Figure 4 Pin Configuration</figcaption>

GND

1

14

OUT

IN

2

13

OUT

DEN

3

12

OUT

IS

4

VS

11

n.c.

n.c.

5

10

OUT

n.c.

6

9

OUT

n.c.

7

exposed pad (bottom)

8

OUT

PinOut_PROFET1ch_PDH.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="5" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 6" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->
<!-- PageHeader="Pin Configuration" -->


## 3.2 Pin Definitions and Functions


<table>
<caption>Table 2 Pin Definition</caption>
<tr>
<th>Pin</th>
<th>Symbol</th>
<th>Function</th>
</tr>
<tr>
<td>EP</td>
<td>VS (exposed pad)</td>
<td>Supply Voltage Battery voltage</td>
</tr>
<tr>
<td>1</td>
<td>GND</td>
<td>Ground Signal ground</td>
</tr>
<tr>
<td>2</td>
<td>IN</td>
<td>Input Channel Digital signal to switch ON the channel ("high" active) If not used: connect to GND pin or to module ground with resistor RIN = 4.7 k£2</td>
</tr>
<tr>
<td>3</td>
<td>DEN</td>
<td>Diagnostic Enable Digital signal to enable device diagnosis ("high" active) and to clear the protection latch of channel If not used: connect to GND pin or to module ground with resistor RDEN = 4.7 kQ2</td>
</tr>
<tr>
<td>4</td>
<td>IS</td>
<td>SENSE current output Analog/digital signal for diagnosis If not used: left open</td>
</tr>
<tr>
<td>5-7,11</td>
<td>n.c.</td>
<td>Not connected, internally not bonded</td>
</tr>
<tr>
<td>8-10, 12- 14</td>
<td>OUT</td>
<td>Output Protected high-side power output channel1)</td>
</tr>
</table>

1\) All output pins of the channel must be connected together on the PCB. All pins of the output are internally connected
together. PCB traces have to be designed to withstand the maximum current which can flow.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="6" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 7" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


### General Product Characteristics


#### 4 General Product Characteristics


##### 4.1 Absolute Maximum Ratings - General

Table 3
Absolute Maximum Ratings1)

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
<td colspan="2"></td>
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
<td>Load Dump Voltage</td>
<td>V BAT(LD)</td>
<td>–</td>
<td>–</td>
<td>35</td>
<td>V</td>
<td>suppressed Load Dump acc. to ISO16750-2 (2010). Ri = 202</td>
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
<td>t ≤ 2 min TA = +25 ℃ Setup as described in Chapter 10</td>
<td>P_4.1.0.5</td>
</tr>
<tr>
<td>Current through GND Pin</td>
<td>IGND</td>
<td>-50</td>
<td>–</td>
<td>50</td>
<td>mA</td>
<td>RGND according to Chapter 10</td>
<td>P_4.1.0.9</td>
</tr>
<tr>
<td colspan="8">Logic &amp; control pins (Digital Input = DI) DI = IN, DEN</td>
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
<td>/DI(REV)</td>
<td>-1</td>
<td>–</td>
<td>10</td>
<td>mA</td>
<td>2) t ≤ 2 min</td>
<td>P_4.1.0.36</td>
</tr>
<tr>
<td colspan="8">IS pin</td>
</tr>
<tr>
<td>Voltage at IS Pin</td>
<td>VIS</td>
<td>-1.5</td>
<td>–</td>
<td>VS</td>
<td>V</td>
<td>lis = 10 µA</td>
<td>P_4.1.0.16</td>
</tr>
<tr>
<td>Current through IS Pin</td>
<td>'Is</td>
<td>-25</td>
<td>–</td>
<td>"IS(SAT),M AX</td>
<td>mA</td>
<td>–</td>
<td>P_4.1.0.18</td>
</tr>
<tr>
<td colspan="8">Temperatures</td>
</tr>
<tr>
<td>Junction Temperature</td>
<td>TJ</td>
<td>-40</td>
<td>–</td>
<td>150</td>
<td>℃</td>
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
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="7" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 8" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


###### General Product Characteristics

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
<td>ESD Susceptibility</td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
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
<td>ESD Susceptibility OUT vs GND and VS connected (HBM)</td>
<td>VESD(HBM)_OU T</td>
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
<td>ESD Susceptibility Corner Pins (CDM) (pins 1, 7, 8, 14)</td>
<td>VESD(CDM)_CR N</td>
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


####### Notes

1\. Stresses above the ones listed here may cause permanent damage to the device. Exposure to absolute
maximum rating conditions for extended periods may affect device reliability.

2\. Integrated protection functions are designed to prevent IC destruction under fault conditions described in the
data sheet. Fault conditions are considered as "outside" normal operating range. Protection functions are
not designed for continuous repetitive operation.


##### 4.2 Absolute Maximum Ratings - Power Stages


###### 4.2.1 Power Stage - 4 m22

Table 4
Absolute Maximum Ratings1)

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
<td>150</td>
<td>mJ</td>
<td>/L =2*/L(NOM) TJ(0) = 150 ℃ Vs = 28 V</td>
<td>P_4.2.11.1</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="8" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 9" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


### General Product Characteristics

Table 4
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
<td>Maximum Energy Dissipation Repetitive Pulse</td>
<td>EAR</td>
<td>–</td>
<td>–</td>
<td>44</td>
<td>mJ</td>
<td>IL= IL(NOM) TJ(0) = 85 ℃ Vs = 13.5 V 1M cycles</td>
<td>P_4.2.11.4</td>
</tr>
<tr>
<td>Load Current</td>
<td>V/11</td>
<td>-</td>
<td>-</td>
<td>I L(OVL0),MAX</td>
<td>A</td>
<td>–</td>
<td>P_4.2.11.3</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


#### 4.3 Functional Range


<table>
<caption>Table 5 Functional Range - Supply Voltage and Temperature1)</caption>
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
<td>Supply Voltage Range for Normal Operation</td>
<td>VS(NOR)</td>
<td>6</td>
<td>13.5</td>
<td>18</td>
<td>V</td>
<td>–</td>
<td>P_4.3.0.1</td>
</tr>
<tr>
<td>Lower Extended Supply Voltage Range for Operation</td>
<td>VS(EXT,LOW)</td>
<td>3.1</td>
<td>–</td>
<td>6</td>
<td>V</td>
<td>2)3) (parameter deviations possible)</td>
<td>P_4.3.0.2</td>
</tr>
<tr>
<td>Supply Voltage Range reached after Overload Protection activation leading to "Undervoltage on Vs" condition</td>
<td>VS(EXT,CVG)</td>
<td>–</td>
<td>–</td>
<td>3.1</td>
<td>V</td>
<td>CVSGND is required when the Overload Protection is triggered (see Chapter 8.2) and the observed number of retries is different from what specified in Chapter 8.3.1</td>
<td>P_4.3.0.7</td>
</tr>
<tr>
<td>Upper Extended Supply Voltage Range for Operation</td>
<td>VS(EXT,UP)</td>
<td>18</td>
<td>–</td>
<td>28</td>
<td>V</td>
<td>3) (parameter deviations possible)</td>
<td>P_4.3.0.3</td>
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


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="9" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 10" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


# General Product Characteristics


## 4.4 Thermal Resistance

Note:
This thermal data was generated in accordance with JEDEC JESD51 standards. For more
information, go to www.jedec.org.


<table>
<caption>Table 6 Thermal Resistance1)</caption>
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
<td>Y JTOP</td>
<td>–</td>
<td>3</td>
<td>5</td>
<td>K/W</td>
<td>2)</td>
<td>P_4.4.0.1</td>
</tr>
<tr>
<td>Thermal Resistance Junction-to-Case</td>
<td>RthJC</td>
<td>–</td>
<td>1.4</td>
<td>2.4</td>
<td>K/W</td>
<td>2) simulated at exposed pad</td>
<td>P_4.4.0.2</td>
</tr>
<tr>
<td>Thermal Resistance Junction-to-Ambient</td>
<td>RthJA</td>
<td>–</td>
<td>31.8</td>
<td>–</td>
<td>K/W</td>
<td>2)</td>
<td>P_4.4.0.3</td>
</tr>
</table>

1\) Not subject to production test - specified by design.

2\) According to Jedec JESD51-2,-5,-7 at natural convection on FR4 2s2p board; the Product (Chip + Package) was
simulated on a 76.2 × 114.3 x 1.5 mm board with 2 inner copper layers (2 x 70 um Cu, 2 x 35 um Cu). Where applicable
a thermal via array under the exposed pad contacted the first inner copper layer. Simulation done at TA = 105℃,
PDISSIPATION = 1 W.


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


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="10" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 11" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


#### General Product Characteristics


<figure>
<figcaption>Figure 7 PCB setup for thermal simulations</figcaption>

FE

JEDEC 1s0p / 600mm2

JEDEC 150p / footprint
JEDEC 252p

PCB 1s0p + 600 mm2 cooling

PCB 2s2p / 1s0p footprint

PCB_sim_setup_TSDSO14.emf

</figure>


<figure>
<figcaption>Figure 8 Thermal vias on PCB for 2s2p PCB setup</figcaption>

Solder Pads
Vias

PCB_2s2p_vias_TSDSO14.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="11" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 12" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


# General Product Characteristics


## 4.4.2 Thermal Impedance


<figure>
<figcaption>Figure 9 Typical Thermal Impedance. PCB setup according Chapter 4.4.1</figcaption>

BTS7004-1EPx

100

10

ZthJA (K/W)

TA = 105℃

1

2s2p

1sOp - 600 mm2

1s0p - 300 mm2

1s0p - footprint

0,1

0,0001

0,001

0,01

0,1

1

10

Time (s)

100

1000

</figure>


<figure>
<figcaption>Figure 10 Thermal Resistance on 1s0p PCB with various cooling surfaces</figcaption>

BTS7004-1EPx

120

1sOp - Ta = 105℃

110

100

90

RthJA (K/W)

80

70

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

Cooling area (mm2)

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="12" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 13" -->



<figure>

<!-- PageHeader="Infineon" -->

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->

Logic Pins


# 5 Logic Pins

The device has 2 digital pins.


## 5.1 Input Pin (IN)

The input pin IN activates the output channel. The input circuitry is compatible with 3.3V and 5V
microcontroller (see Chapter 10 for the complete application setup overview). The electrical equivalent of the
input circuitry is shown in Figure 11. In case the pin is not used, it should be pulled to module GND or device
GND pin via RIN = 4.7 kQ2.


<figure>
<figcaption>Figure 11 Input circuitry</figcaption>

VS

IN

IDI

VS(CLAMP)

ESD

/DI

VDI(CLAMP)

VDI

GND

IGND

RGND

Input_IN_INTDIO.emf

</figure>


The logic thresholds for "low" and "high" states are defined by parameters VDI(TH) and VDI(HYS). The relationship
between these two values is shown in Figure 12. The voltage VIN needed to ensure a "high" state is always
higher than the voltage needed to ensure a "low" state.


<figure>
<figcaption>Figure 12 Input Threshold voltages and hysteresis</figcaption>

VDI 4

VDI(TH ),MAX

VDI(TH)

VDI(HYS)

VD(TH ) MIN

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


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="13" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 14" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->

Logic Pins


## 5.2 Diagnosis Pin

The Diagnosis Enable (DEN) pin controls the diagnosis circuitry and can be used to reset the latched protection
(Protection circuitry not disabled by DEN). When DEN pin is set to "high", the diagnosis is enabled (see
Chapter 9.2 for more details). When it is set to "low", the diagnosis is disabled (IS pin is set to high
impedance).

The transition from "high" to "low" of DEN pin clears the protection latch of the channel depending on the
logic state of IN pin and DEN pulse length (see Chapter 8.3 for more details). The internal structure of
diagnosis pins is the same as the one of input pins. See Figure 11 for more details.


## 5.3 Electrical Characteristics Logic Pins

Vs = 6 V to 18 V, TJ =- 40 °C to +150 ℃
Typical values: Vs = 13.5 V, TJ= 25 ℃

Digital Input (DI) pins = IN, DEN


<table>
<caption>Table 7 Electrical Characteristics: Logic Pins - General</caption>
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
<td>VDI(TH)</td>
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
<td>DI(CLAMP2)</td>
<td>6.5</td>
<td>7.5</td>
<td>8.5</td>
<td>V</td>
<td>IDI = 2 mA See Figure 11 and Figure 12</td>
<td>P_5.4.0.3</td>
</tr>
<tr>
<td>Digital Input Hysteresis</td>
<td>VDI(HYS)</td>
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
<td>HA</td>
<td>VDI = 2 V See Figure 11 and Figure 12</td>
<td>P_5.4.0.5</td>
</tr>
<tr>
<td>Digital Input Current ("low")</td>
<td>/DI(L)</td>
<td>2</td>
<td>10</td>
<td>25</td>
<td>µA</td>
<td>VDI = 0.8 V See Figure 11 and Figure 12</td>
<td>P_5.4.0.6</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="14" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 15" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->

Power Supply


# 6 Power Supply

The BTS7004-1EPP is supplied by Vs, which is used for the internal logic as well as supply for the power output
stage. Vs has an undervoltage detection circuit, which prevents the activation of the power output stage and
diagnosis in case the applied voltage is below the undervoltage threshold (Vs < VS(op)). During power up, the
internal power on signal is set when supply voltage (Vs) exceeds the minimum operating voltage (Vs > VS(OP).


## 6.1 Operation Modes

BTS7004-1EPP has the following operation modes in case of Vs > VS(OP):

· OFF mode

· ON mode

· Diagnosis in ON mode

· Diagnosis in OFF mode

· Fault

The transition between operation modes is determined according to these variables:

· Logic level at IN pin

· Logic level at DEN pin

· Internal latch

· Sense current lis level

The truth table in case of Vs > Vs(op) is shown in Table 8. The behavior of BTS7004-1EPP as well as some
parameters may change in dependence on the operation mode of the device.

There are three parameters describing each operation mode of BTS7004-1EPP:

· Status of the output channel

· Status of the diagnosis

· Current consumption at VS pin (measured by lys in OFF mode, IGND in all other operative modes)


<table>
<caption>Table 8 Operation Mode truth table</caption>
<tr>
<th>IN</th>
<th>DEN</th>
<th>Internal latch</th>
<th>lis</th>
<th>Operative Mode</th>
<th>Comment</th>
</tr>
<tr>
<td>L</td>
<td>L</td>
<td>L</td>
<td>leakage</td>
<td>OFF</td>
<td>DMOS channel is OFF</td>
</tr>
<tr>
<td>L</td>
<td>L</td>
<td>H</td>
<td>leakage</td>
<td>OFF</td>
<td>DMOS channel is OFF</td>
</tr>
<tr>
<td rowspan="2">L</td>
<td>H</td>
<td>L</td>
<td>leakage</td>
<td rowspan="3">OFF_DIAG</td>
<td>Diagnostic in OFF-mode</td>
</tr>
<tr>
<td></td>
<td></td>
<td>open load</td>
<td>Diagnostic in OFF-mode</td>
</tr>
<tr>
<td>L</td>
<td>H</td>
<td>H</td>
<td>fault</td>
<td>Diagnostic in OFF-mode</td>
</tr>
<tr>
<td>H</td>
<td>L</td>
<td>L</td>
<td>leakage</td>
<td>ON</td>
<td>DMOS channel is ON, no diagnostic</td>
</tr>
<tr>
<td>H</td>
<td>L</td>
<td>H</td>
<td>leakage</td>
<td>fault</td>
<td>DMOS channel is switched OFF due to failure</td>
</tr>
<tr>
<td>H</td>
<td>H</td>
<td>L</td>
<td>Ils</td>
<td>ON_DIAG</td>
<td>DMOS channel is ON and diagnostic</td>
</tr>
<tr>
<td>H</td>
<td>H</td>
<td>H</td>
<td>fault</td>
<td>fault</td>
<td>DMOS channel is switched OFF due to failure</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="15" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 16" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->

Power Supply


### 6.1.1 OFF mode

When BTS7004-1EPP is in OFF mode, the output channel is OFF. The current consumption is minimum (see
parameter /vs(OFF). No Overtemperature, Overload protection mechanism and no diagnosis function is active
when the device is in OFF mode.


### 6.1.2 ON mode

ON (IN = High; DEN = Low) mode is the normal operation mode of BTS7004-1EPP. Device current consumption
is specified with IGND(ON_D) + /IS(OFF) (measured at GND pin because the current at VS pin includes the load
current). Overcurrent and Overtemperature protections are active. No diagnosis function is active.


### 6.1.3 OFF_Diag mode

The device is in OFF_Diag mode as long as DEN pin is set to "high" and IN pin is set to "low". The output
channel is OFF. If an open load case happens, an Open Load in OFF current /IS(OLOFF) may be present at IS pin.
In such situation, the current consumption of the device is increased.


### 6.1.4 ON_Diag mode

The device is in normal ON mode with current sense function. lis or /IS(FAULT) will be present at IS pin. Device
current consumption is specified with IGND(ON_D). Depending on the load condition, either a fault current
VIS(FAULT) or /Is current may be present at IS pin.


### 6.1.5 Fault mode

The device is in Fault mode as soon as a protection event happens which affects that the device switches off
due to its protection function. In Fault mode, a /IS(FAULT) signal is presenting at IS pin during the DEN signal is
"high".


## 6.2 Undervoltage on Vs

Between Vs(OP) and Vs(uv) the undervoltage mechanism is triggered. If the device is operative (in ON mode) and
the supply voltage drops below the undervoltage threshold Vs(uv), the internal logic switches OFF the output
channel.

As soon as the supply voltage Vs is above the operative threshold Vs(op), the channel is switched ON again. The
restart is delayed with a time tDELAY(Uv) which protects the device in case the undervoltage condition is caused
by a short circuit event (according to AEC-Q100-012), as shown in Figure 13.

If the device is in OFF mode and the input is set to "high", the channel will be switched ON if Vs > VS(op) without
waiting for tDELAY(UV)·

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="16" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 17" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


### Power Supply


<figure>
<figcaption>Figure 13 Vs undervoltage behavior</figcaption>

Vs

VS(OP)

1 VS(HYS)

Vs(Uv)

t

Channel
activation signal

t

VOUT

tDELAY(UV)

t

Power Supply_UVRVS.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="17" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 18" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->

Power Supply


## 6.3 Electrical Characteristics Power Supply

Vs = 6 V to 18 V, TJ =- 40 °C to +150 ℃

Typical values: Vs = 13.5 V, TJ= 25 °℃

Typical resistive load connected to the output for testing (unless otherwise specified):

RL = 2.1 22


<table>
<caption>Table 9 Electrical Characteristics: Power Supply - General</caption>
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
<td colspan="2">VS pin</td>
<td colspan="5"></td>
<td></td>
</tr>
<tr>
<td>Power Supply Undervoltage Shutdown</td>
<td>VS(UV)</td>
<td>1.8</td>
<td>2.3</td>
<td>3.1</td>
<td>V</td>
<td>Vs decreasing IN = "high" From Vps ≤ 0.5 V to VDS=Vs See Figure 13</td>
<td>P_6.4.0.1</td>
</tr>
<tr>
<td>Power Supply Minimum Operating Voltage</td>
<td>VS(OP)</td>
<td>2.0</td>
<td>3.0</td>
<td>4.1</td>
<td>V</td>
<td>Vs increasing IN = "high" From VDs = Vs to VDS ≤ 0.5V See Figure 13</td>
<td>P_6.4.0.3</td>
</tr>
<tr>
<td>Power Supply Undervoltage Shutdown Hysteresis</td>
<td>VS(HYS)</td>
<td>–</td>
<td>0.7</td>
<td>–</td>
<td>V</td>
<td>1) VS(OP) - Vs(Uv) See Figure 13</td>
<td>P_6.4.0.6</td>
</tr>
<tr>
<td>Power Supply Undervoltage Recovery Time</td>
<td>ťDELAY(UV)</td>
<td>2.5</td>
<td>5</td>
<td>7.5</td>
<td>ms</td>
<td>dVs/dt ≤0.5 V/us Vs2 -1V See Figure 13</td>
<td>P_6.4.0.7</td>
</tr>
<tr>
<td>Breakdown Voltage between GND and VS Pins in Reverse Battery</td>
<td>-VS(REV)</td>
<td>16</td>
<td>–</td>
<td>30</td>
<td>V</td>
<td>1) IGND(REV) = 7 mA TJ=150 ℃</td>
<td>P_6.4.0.9</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="18" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 19" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->

Power Supply


## 6.4 Electrical Characteristics Power Supply - Product Specific

Vs = 6 V to 18 V, TJ =- 40 °C to +150 ℃

Typical values: Vs = 13.5 V, TJ= 25 ℃

Typical resistive load connected to the output for testing (unless otherwise specified):
RL = 2.1 22


### 6.4.1 BTS7004-1EPP


<table>
<caption>Table 10 Electrical Characteristics: Power Supply BTS7004-1EPP</caption>
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
<td>Supply Current Consumption in OFF Mode with Loads</td>
<td>VS(OFF)_85</td>
<td>–</td>
<td>0.05</td>
<td>0.5</td>
<td>µA</td>
<td>1) Vs = 18 V VOUT = 0 V IN = DEN = "low" TJ ≤85°℃</td>
<td>P_6.5.21.1</td>
</tr>
<tr>
<td>Supply Current Consumption in OFF Mode with Loads</td>
<td>Ivs(OFF)_150</td>
<td>–</td>
<td>5</td>
<td>20</td>
<td>µA</td>
<td>Vs = 18 V VOUT = 0 V IN = DEN = "low" TJ=150 ℃</td>
<td>P_6.5.21.2</td>
</tr>
<tr>
<td>Operating Current in ON_Diag Mode (Channel ON)</td>
<td>İGND(ON_D)</td>
<td>–</td>
<td>2</td>
<td>3</td>
<td>mA</td>
<td>Vs = 18 V IN = DEN = “high"</td>
<td>P_6.5.21.3</td>
</tr>
<tr>
<td>Operating Current in OFF_Diag Mode</td>
<td>‘GND(OFF_D)</td>
<td>–</td>
<td>1.2</td>
<td>1.8</td>
<td>mA</td>
<td>Vs = 18 V IN = "low"; DEN = "high"</td>
<td>P_6.5.21.5</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="19" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 20" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


# Power Stages


## 7 Power Stages

The high-side power stage is built using a N-channel vertical Power MOSFET with charge pump.


### 7.1 Output ON-State Resistance

The ON-state resistance RDS(ON) depends mainly on junction temperature TJ. Figure 14 shows the variation of
RDS(ON) across the whole T, range. The value "2" on the y-axis corresponds to the maximum RDS(ON) measured
at TJ = 150 ℃.


<figure>
<figcaption>Figure 14 RDS(ON) variation factor</figcaption>

RDS(ON) variation over TJ

2.20

Reference value:

2.00

"2"=RDS(ON),MAX@150 ℃

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

-40

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

When switching resistive loads, the switching times and slew rates shown in Figure 15 can be considered. The
switch energy values EON and EOFF are proportional to load resistance and times ton and tOFF.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="20" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 21" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


##### Power Stages


<figure>
<figcaption>Figure 15 Switching a Resistive Load</figcaption>

IN

VIN(TH)

VIN (HYS)

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

PDMOS

EON

EOFF

t

Power Stage_SwitchRes.emf

</figure>


#### 7.2.2 Switching Inductive Loads

When switching OFF inductive loads with high-side switches, the voltage VOUT drops below ground potential,
because the inductance intends to continue driving the current. To prevent the destruction of the device due
to overvoltage, a voltage clamp mechanism is implemented. The clamping structure limits the negative
output voltage so that VDs = VDS(CLAMP). Figure 16 shows a concept drawing of the implementation. The
clamping structure is available in all operation modes listed in Chapter 6.1.


<figure>
<figcaption>Figure 16 Output Clamp concept</figcaption>

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

OUT

VOUT

RSENSE

GND

L,

RL

RGND

PowerStage_Clamp_INTDIO_1CH.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="21" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 22" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


##### Power Stages

During demagnetization of inductive loads, energy has to be dissipated in BTS7004-1EPP. The energy can be
calculated with Equation (7.1):

VS-VDS(CLAMP)

E = VDS(CLAMP)
⋅
–
L
I
RL
· In(1
VS - VDS(CLAMP)
⎞
+
L
(7.1)

The maximum energy, therefore the maximum inductance for a given current, is limited by the thermal design
of the component. Please refer to Chapter 4.2 for the maximum allowed values of EAs (single pulse energy)
and EAR (repetitive energy).


#### 7.2.3 Output Voltage Limitation

To increase the current sense accuracy, Vps voltage is monitored. When the output current /_ decreases while
the channel is diagnosed (DEN pin set to "high" - see Figure 17) bringing Vps equal or lower than VDS(SLC), the
output DMOS gate is partially discharged. This increases the output resistance so that VDs = VDS(SLC) even for
very small output currents. The Vps increase allows the current sensing circuitry to work more efficiently,
providing better kILIs accuracy for output current in the low range.


<figure>
<figcaption>Figure 17 Output Voltage Limitation activation during diagnosis</figcaption>

IN

t

DEN

IL

t

VDS

t

Vs

VDS(SLC)

t

PowerStage_GBR_diag_HEAT.emf

</figure>


### 7.3 Advanced Switching Characteristics


#### 7.3.1 Inverse Current behavior

When VOUT > Vs, a current /INy flows into the power output transistor (see Figure 18). This condition is known
as "Inverse Current".

If the channel is in OFF state, the current flows through the intrinsic body diode generating high power losses
therefore an increase of overall device temperature. If the channel is in ON state, RDS(INV) can be expected and
power dissipation in the output stage is comparable to normal operation in RDS(ON).

During Inverse Current condition, the channel remains in ON or OFF state as long as |-4| |-[INV) .

With InverseON, it is possible to switch ON the channel during Inverse Current condition as long as |-| -|- L(INV]
(see Figure 19).

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="22" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 23" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

<!-- PageHeader="Infineon" -->

</figure>


##### Power Stages


<figure>
<figcaption>Figure 18 Inverse Current Circuitry</figcaption>

VBAT

Vs

Gate
Driver

Device
Logic

INV
Comp.

-IL

VOUT>VS

OUT

GND

RGND
RGND

PowerStage_Inverse_HEAT.emf

</figure>


<figure>
<figcaption>Figure 19 InverseON - Channel behavior in case of applied Inverse Current</figcaption>

IN

CASE 1 : Switch is ON

IN

CASE 2 : Switch is OFF

ON

OFF

t

t

IL

IL

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

IL

IL

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


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="23" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 24" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


# Power Stages


## 7.3.2 Cross Current robustness with H-Bridge configuration

When BTS7004-1EPP is used as high-side switch e.g. in a bridge configuration (therefore paired with a low-side
switch as shown in Figure 20), the maximum slew rate applied to the output by the low-side switch must be
lower than | dVOUT / dt |. Otherwise the output stage may turn ON in linear mode (not in RDS(ON)) while the low-
side switch is commutating. This creates an unprotected overheating for the DMOS due to the cross-
conduction current.


<figure>
<figcaption>Figure 20 High-Side switch used in Bridge configuration</figcaption>

VBAT

R/L cable

HSS 1

HSS 2

VS

VS

T

T

ON (DC)

IN

IN

OFF

OUT

OUT

dVour / dt

Current through Motor

Cross
Current

M

ON (PWM)

OFF

PowerStage_PassiveSlew_PROFET1Ch.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="24" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 25" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->

Power Stages


### 7.4 Electrical Characteristics Power Stages

Vs = 6 V to 18 V, T] = - 40 °C to +150 ℃

Typical values: Vs = 13.5 V, TJ= 25 °℃

Typical resistive load connected to the output for testing (unless otherwise specified):

RL = 2.1 22


<table>
<caption>Table 11 Electrical Characteristics: Power Stages - General</caption>
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
<td>/L = 5 mA TJ =- 40ºC See Figure 16</td>
<td>P_7.4.0.1</td>
</tr>
<tr>
<td>Drain to Source Clamping Voltage at TJ ≥ 25 °℃</td>
<td>VDS(CLAMP)_25</td>
<td>35</td>
<td>38</td>
<td>44</td>
<td>V</td>
<td>1) /L = 5 mA TJ ≥ 25°C See Figure 16</td>
<td>P_7.4.0.2</td>
</tr>
</table>

1\) Tested at TJ = 150°C.


#### 7.4.1 Electrical Characteristics Power Stages


<table>
<caption>Table 12 Electrical Characteristics: Power Stages</caption>
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
<td>70</td>
<td>130</td>
<td>μς</td>
<td>Vs = 13.5 V VOUT = 10% VS</td>
<td>P_7.4.5.1</td>
</tr>
<tr>
<td>Switch-OFF Delay</td>
<td>tOFF(DELAY)</td>
<td>10</td>
<td>50</td>
<td>160</td>
<td>μς</td>
<td>Vs = 13.5 V VOUT = 90% VS</td>
<td>P_7.4.5.2</td>
</tr>
<tr>
<td>Switch-ON Time</td>
<td>ton</td>
<td>50</td>
<td>130</td>
<td>210</td>
<td>μς</td>
<td>Vs = 13.5 V VOUT = 90% VS</td>
<td>P_7.4.5.3</td>
</tr>
<tr>
<td>Switch-OFF Time</td>
<td>tOFF</td>
<td>30</td>
<td>100</td>
<td>220</td>
<td>μς</td>
<td>Vs = 13.5 V VOUT = 10% VS</td>
<td>P_7.4.5.4</td>
</tr>
<tr>
<td>Switch-ON/OFF Matching ton - tOFF</td>
<td>Atsw</td>
<td>-60</td>
<td>25</td>
<td>90</td>
<td>μς</td>
<td>Vs = 13.5 V</td>
<td>P_7.4.5.5</td>
</tr>
<tr>
<td colspan="8">Voltage Slope</td>
</tr>
<tr>
<td>Switch-ON Slew Rate</td>
<td>(dV/dt) ON</td>
<td>0.16</td>
<td>0.27</td>
<td>0.39</td>
<td>V/us</td>
<td>Vs = 13.5 V VOUT = 30% to 70% of Vs</td>
<td>P_7.4.5.6</td>
</tr>
<tr>
<td>Switch-OFF Slew Rate</td>
<td>-(dV/dt) OFF</td>
<td>0.16</td>
<td>0.27</td>
<td>0.39</td>
<td>V/us</td>
<td>Vs = 13.5 V VOUT = 70% to 30% of Vs</td>
<td>P_7.4.5.7</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="25" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 26" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


# Power Stages


<table>
<caption>Table 12 Electrical Characteristics: Power Stages (continued)</caption>
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
<td>Slew Rate Matching (dV/dt) ON - (dV/dt) OFF</td>
<td>A(dV/dt)sw</td>
<td>-0.15</td>
<td>0</td>
<td>+0.15</td>
<td>V/us</td>
<td>Vs = 13.5 V</td>
<td>P_7.4.5.8</td>
</tr>
<tr>
<td colspan="8">Voltages</td>
</tr>
<tr>
<td>Output Voltage Drop Limitation at Small Load Currents</td>
<td>VDS(SLC)</td>
<td>2</td>
<td>10</td>
<td>20</td>
<td>mV</td>
<td>1) "OUT = "OUT(OL) =20 mA</td>
<td>P_7.4.5.9</td>
</tr>
</table>

1\) Not subject to production test - specified by design


## 7.5 Electrical Characteristics - Power Output Stages

Vs = 6 V to 18 V, T] =- 40 ℃ to +150 ℃

Typical values: Vs = 13.5 V, TJ= 25 ℃

Typical resistive load connected to the output for testing (unless otherwise specified):

RL = 2.12


### 7.5.1 Power Output Stage - 4 m22


<table>
<caption>Table 13 Electrical Characteristics: Power Stages - 4 m22</caption>
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
<td>4.4</td>
<td>–</td>
<td>m22</td>
<td>1) TJ =25 ℃</td>
<td>P_7.5.11.1</td>
</tr>
<tr>
<td>ON-State Resistance at TJ=150 ℃</td>
<td>RDS(ON)_150</td>
<td>-</td>
<td>-</td>
<td>8</td>
<td>m22</td>
<td>TJ=150 ℃</td>
<td>P_7.5.11.2</td>
</tr>
<tr>
<td>ON-State Resistance in Cranking</td>
<td>RDS(ON)_CRAN K</td>
<td>–</td>
<td>–</td>
<td>10</td>
<td>mQ2</td>
<td>TJ =150 ℃ Vs = 3.1 V</td>
<td>P_7.5.11.3</td>
</tr>
<tr>
<td>ON-State Resistance in Inverse Current at Ty = 25 ℃</td>
<td>RDS(INV)_25</td>
<td>–</td>
<td>4.5</td>
<td>–</td>
<td>m22</td>
<td>1) TJ =25 ℃ Vs = 13.5 V /L =- 4A DEN = "low" see Figure 18</td>
<td>P_7.5.11.4</td>
</tr>
<tr>
<td>ON-State Resistance in Inverse Current at TJ = 150 ℃</td>
<td>RDS(INV)_150</td>
<td>–</td>
<td>–</td>
<td>10</td>
<td>mQ2</td>
<td>TJ =150 ℃ Vs = 13.5 V /L =- 4A DEN = "low" see Figure 18</td>
<td>P_7.5.11.5</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="26" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 27" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->

Power Stages


<table>
<caption>Table 13 Electrical Characteristics: Power Stages - 4 m22 (continued)</caption>
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
<td>ON-State Resistance in Reverse Polarity at TJ = 25 ℃</td>
<td>RDS(REV)_25</td>
<td>–</td>
<td>9.5</td>
<td>–</td>
<td>m22</td>
<td>1) TJ =25 ℃ Vs =- 13.5 V /L =- 4A see Figure 29</td>
<td>P_7.5.11.6</td>
</tr>
<tr>
<td>ON-State Resistance in Reverse Polarity at TJ = 150 ℃</td>
<td>RDS(REV)_150</td>
<td>–</td>
<td>–</td>
<td>16</td>
<td>m22</td>
<td>TJ =150 ℃ Vs =- 13.5 V /L =- 4A</td>
<td>P_7.5.11.7</td>
</tr>
<tr>
<td>Nominal Load Current</td>
<td>IL(NOM)</td>
<td>–</td>
<td>15</td>
<td>–</td>
<td>A</td>
<td>1) TA = 85 ℃ TJ ≤150℃</td>
<td>P_7.5.11.8</td>
</tr>
<tr>
<td>Output Leakage Current at TJ ≤ 85℃</td>
<td>IL(OF)_85</td>
<td>–</td>
<td>0.05</td>
<td>0.5</td>
<td>µA</td>
<td>1) VOUT = 0 V VIN = "low" TA ≤ 85℃</td>
<td>P_7.5.11.9</td>
</tr>
<tr>
<td>Output Leakage Current at TJ =150 ℃</td>
<td>IL(OFF)_150</td>
<td>–</td>
<td>–</td>
<td>15</td>
<td>µA</td>
<td>VOUT = 0 V VIN = "low" TA = 150 ℃</td>
<td>P_7.5.11.10</td>
</tr>
<tr>
<td>Inverse Current Capability</td>
<td>IL(INV)</td>
<td>–</td>
<td>-15</td>
<td>–</td>
<td>A</td>
<td>1) VS &lt; VOUT IN = "high" see Figure 18</td>
<td>P_7.5.11.11</td>
</tr>
<tr>
<td>Voltage Slope</td>
<td colspan="7"></td>
</tr>
<tr>
<td>Passive Slew Rate (e.g. for Half Bridge Configuration)</td>
<td>IdVOUT / dt]</td>
<td>-</td>
<td>–</td>
<td>10</td>
<td>V/μς</td>
<td>1) Vs = 13.5 V see Figure 20</td>
<td>P_7.5.11.12</td>
</tr>
<tr>
<td colspan="8">Voltages</td>
</tr>
<tr>
<td>Drain Source Diode Voltage</td>
<td>IV DS(DIODE)</td>
<td>–</td>
<td>550</td>
<td>700</td>
<td>mV</td>
<td>/_ =- 190 mA TJ=150 ℃</td>
<td>P_7.5.11.13</td>
</tr>
<tr>
<td colspan="8">Switching Energy</td>
</tr>
<tr>
<td>Switch-ON Energy</td>
<td>EON</td>
<td>–</td>
<td>1.4</td>
<td>–</td>
<td>mJ</td>
<td>1) Vs = 18 V see Figure 15</td>
<td>P_7.5.11.14</td>
</tr>
<tr>
<td>Switch-OFF Energy</td>
<td>E OFF</td>
<td>–</td>
<td>1.65</td>
<td>–</td>
<td>mJ</td>
<td>1) Vs = 18 V see Figure 15</td>
<td>P_7.5.11.15</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="27" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 28" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


<!-- PageHeader="Protection" -->


# 8 Protection

The BTS7004-1EPP is protected against Overtemperature, Overload, Reverse Battery (with ReverseON) and
Overvoltage. Overtemperature and Overload protections are working when the device is in ON or ON_Diag
mode but not during InverseON and ReverseON function. Overvoltage protection works in all operation
modes. Reverse Battery protection works when the GND and VS pins are reverse supplied.


## 8.1 Overtemperature Protection

The device incorporates both an absolute (TJ(ABS) and a dynamic (TJ(DYN) temperature protection circuitry for
the channel. An increase of junction temperature T, above either one of the two thresholds (TJ(ABS) or TJ(DYN))
switches OFF the overheated channel to prevent destruction. The channel remains switched OFF until
junction temperature has reached the "Reactivation" condition described in Table 14. The behavior is shown
in Figure 21 (absolute Overtemperature Protection) and Figure 22 (dynamic Overtemperature Protection).
TJ(REF) is the reference temperature used for dynamic temperature protection.


<figure>
<figcaption>Figure 21 Overtemperature Protection (Absolute)</figcaption>

IN

t

DEN

t

IL

IL(OVL 0)

IL(NOM)

t

TJ

TJ(ABS)

Is

t

Is = IL/KILIS

/IS(FAULT)

t

Internal
latch

0

1

t

Over_Temperature_Behaviour.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="28" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 29" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


### Protection


<figure>
<figcaption>Figure 22 Overtemperature Protection (Dynamic)</figcaption>

IN

t

DEN

t

1

IL(OVL)

t

TJ

T(ABS)

Tx(DYN)

T (REF)

t

Is

LIKILIS

IS(FAULT)

t

Internal
Latch

0

1

t

</figure>


When the Overtemperature protection circuitry allows the channel to be switched ON again, the Intelligent
Latch strategy described in Chapter 8.3 is followed.


## 8.2 Overload Protection

The BTS7004-1EPP is protected in case of Overload or short circuit to ground. Two Overload thresholds are
defined (see Figure 23) and selected automatically depending on the voltage Vos across the power DMOS:

· IL(OVLO) when VDs < 13 V

· IL(OVL1) When VDs > 22 V

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="29" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 30" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


### Protection


<figure>
<figcaption>Figure 23 Overload Current Thresholds</figcaption>

Overload threshold variation ("1" = IL(OVLo) typ @ VDs =5 V)

1.1

IL(OVLO)

1

0.9

0.8

0.7

0.6

L(OVL1)

0.5

0.4

0.3

0.2

0.1

0

4

6

8

10

12

14

16

18

20

22

24

26

28

Drain Source Voltage (V)

</figure>


In order to allow a higher load inrush at low ambient temperature, Overload threshold is maximum at low
temperature and decreases when Ty increases (see Figure 24). IL(OVLO) typical value remains constant up to a
junction temperature of +75 ℃.


<figure>
<figcaption>Figure 24 Overload Current Thresholds variation with T,</figcaption>

IL(OVLO) Variation over T,

1.3

1.2

1.1

0

IL (OVLO) Variation factor

0.9

0.8

0.7

reference value

"1"= IL(OVLO) typ@-40 ℃

0.6

0.5

0.4

0.3

0.2

0.1

Typ

0.0

-40°℃

-20°℃

0°℃

20°℃

40℃

60℃

80°℃

100°C

120°℃

140℃

160℃

Junction Temperature (℃)

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="30" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 31" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


#### Protection

Power supply voltage Vs can increase above 18 V for short time, for instance in Load Dump or in Jump Start
condition. Whenever Vs > Vs(s), the overload detection current is set to IL(OVL_Js) as shown in Figure 25.


<figure>
<figcaption>Figure 25 Overload Detection Current variation with Vs voltage</figcaption>

/L(OVL)

/L(OVL_JS)

Vs(JS)

Vs

Protection_JS.emf

</figure>


When ILL(OVL) (either / L(OVLO) or /L(OVL1) the channel is switched OFF. The channel is allowed to be reactivated
according to the intelligent latch strategy described in Chapter 8.3.


## 8.3 Protection and Diagnosis in case of Fault

Any event that triggers a protection mechanism (either Overtemperature or Overload) has 2 consequences:

· The channel switches OFF and the internal latch is set to "1"

· If the diagnosis is active for the channel, a current /IS(FAULT) is provided by IS pin (see Chapter 9.2.2 for
further details)

The channel can be switched ON again if all the protection mechanisms fulfill the "reactivation" conditions
described in Table 14. Furthermore, the device has the intelligent latch to protect itself against unwanted
repetitive reactivation in fault condition.


<table>
<caption>Table 14 Protection "Reactivation" Condition</caption>
<tr>
<th>Fault condition</th>
<th>Switch OFF event</th>
<th>"Reactivation" condition</th>
</tr>
<tr>
<td>Overtemperature</td>
<td>TJ ≥ TJ(ABS) Or (TJ - TJ(REF) ≥ TJ(DYN)</td>
<td>TJ &lt;TJ(ABS) and (T) -TJ(REF) &lt;TJ(DYN) (including hysteresis)</td>
</tr>
<tr>
<td>Overload</td>
<td>IL≥ /L(OVL)</td>
<td>Device is OFF</td>
</tr>
</table>


### 8.3.1 Intelligent Latch Strategy

At normal condition, when IN is set to "high", the channel is switched ON. In case of fault condition the output
stage latches OFF. There are two ways to de-latch the switch.

With IN pin:

It is necessary to set the input pin to "low" for a time longer than tDELAY(LR) ("latch reset delay" time) to de-latch
the channel. The channel can be allowed to restart only if the "latch" conditions for the protection
mechanisms are fulfilled (see Table 14 ).

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="31" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 32" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


#### Protection

During the "latch reset delay" time, if the input is set to "high" the channel remains switched OFF and the timer
tDELAY(LR) is reset. The timer tDELAY(LR) restarts as soon as the input pin is set to "low" again.
The intelligent latch strategy is shown in Figure 28 (flowchart) and Figure 26 (timing diagram).

With DEN pin:

It is possible to "force" a reset of the internal latch without waiting for tDELAY(LR) by applying a pulse (rising edge
followed by a falling edge) to the DEN pin while IN pin is "low". The pulse applied to DEN pin must have a
duration longer than tDEN(LR) to ensure a reset of the internal latch.

The timing is shown in Figure 27.


<figure>
<figcaption>Figure 26 Intelligent Latch Timing Diagram</figcaption>

ÉDELAY (LR)

IN

t

Short circuit
to ground

t

IL

t

Internal
latch

0

1

0

1

t

DEN

t

ts IS(DIAG )

ton

/Is (FAULT)

,

IS (FAULT)

lis

t

Protection_Latch_Timing.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="32" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 33" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


<!-- PageHeader="Protection" -->


<figure>
<figcaption>Figure 27 Intelligent Latch Timing Diagram with Forced Reset</figcaption>

IN

t

Short circuit
to ground

1

t

t

Internal
latch

0

1

0

1

t <İDEN(LR)

t > tDEN(LR)

t

DEN

t

tsIS (DIAG)

ts IS(DIAG )

tsIS(DIAG)

IS (FAULT)

/IS (FAULT )

VIS (FAULT)

lis

t

Protection_Latch_DENforce.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="33" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 34" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


##### Protection


<figure>
<figcaption>Figure 28 Intelligent Latch Flowchart</figcaption>

START

IN is "high"

no

yes

yes

Latch = 1

no

Reactivation
condition fulfilled
(T, and / or AT / and / or
Overload)

no

yes

Latch = 0

Switch channel ON

Yes

DEN pulse > tDEN(LR)

Fault
(Overtemperature
or Overload)

no

no

yes

Switch channel OFF

Wait until
DEN pulse > tDEN(LR)

Latch = 1

Wait until IN is "low"
then start counting for
tDELAY(LR)

Set DEN to „high“

IN is "low"

no

yes

yes

De-latching with
DEN

no

Continue latching for
İDELAY(LR)

İDELAY(LR) elapsed

no

yes

Latch = 0

</figure>


Protection_PROFET_Flow_PDH.emf

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="34" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 35" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

<!-- PageHeader="Infineon" -->

</figure>


<!-- PageHeader="Protection" -->


## 8.4 Additional protections


### 8.4.1 Reverse Polarity Protection

In Reverse Polarity condition (also known as Reverse Battery), the output stage is switched ON (see parameter
RDS(REV)) because of ReverseON feature which limits the power dissipation in the output stage. Each ESD diode
of the logic contributes to total power dissipation. The reverse current through the output stage must be
limited by the connected load. The current through digital input pins has to be limited as well by an external
resistor (please refer to the Absolute Maximum Ratings listed in Chapter 4.1 and to Application Information in
Chapter 10).

Figure 29 shows a typical application including a device with ReverseON. A current flowing into GND pin (-/GND)
during Reverse Polarity condition is necessary to activate ReverseON, therefore a resistive path between
module ground and device GND pin must be present.


<figure>
<figcaption>Figure 29 Reverse Battery Protection (application example)</figcaption>

-VBAT(REV)

High-side
Channel

VS

Microcontroller

IDI

DO

RDI

DI

ReverseON

OUT

-/L

GND

IS

GND

L, C, R

-/Is

RSENSE

RGND

-IGND

Protection_RevBatt_HEAT.emf

</figure>


### 8.4.2 Overvoltage Protection

In the case of supply voltages between VS(EXT,UP) and VBAT(LD), the output transistor is still operational and
follows the input pin. In addition to the output clamp for inductive loads as described in Chapter 7.2.2, there
is a clamp mechanism available for Overvoltage protection for the logic circuit and the output channel,
monitoring the voltage between VS and GND pins (VS(CLAMP).

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="35" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 36" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


<!-- PageHeader="Protection" -->


## 8.5 Protection against loss of connection


### 8.5.1 Loss of Battery and Loss of Load

The loss of connection to battery or to the load has no influence on device robustness when load and wire
harness are purely resistive. In case of driving an inductive load, the energy stored in the inductance must be
handled. PROFET™+2 12V devices can handle the inductivity of the wire harness up to 10 uH with /L(NOM). In case
of applications where currents and/or the aforementioned inductivity are exceeded, an external suppressor
diode (like diode Dz2 shown in Chapter 10) is recommended to handle the energy and to provide a well-
defined path to the load current.


### 8.5.2 Loss of Ground

In case of loss of device ground, it is recommended to have a resistor connected between any Digital Input pin
and the microcontroller to ensure a channel switch OFF (as described in Chapter 10).

Note:
In case any Digital Input pin is pulled to ground (either by a resistor or active) a parasitic ground
path is available, which could keep the device operational during loss of device ground.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="36" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 37" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


# Protection


## 8.6 Electrical Characteristics Protection

Vs = 6 V to 18 V, TJ =- 40 ℃ to +150 ℃

Typical values: Vs = 13.5 V, TJ= 25 ℃

Typical resistive load connected to the output for testing (unless otherwise specified):

RL = 2.12


<table>
<caption>Table 15 Electrical Characteristics: Protection - General</caption>
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
<td>1)2) See Figure 21</td>
<td>P_8.6.0.1</td>
</tr>
<tr>
<td>Thermal Shutdown Hysteresis (Absolute)</td>
<td>THYS(ABS)</td>
<td>–</td>
<td>30</td>
<td>–</td>
<td>K</td>
<td>3) See Figure 21</td>
<td>P_8.6.0.2</td>
</tr>
<tr>
<td>Thermal Shutdown Temperature (Dynamic)</td>
<td>TJ(DYN)</td>
<td>–</td>
<td>80</td>
<td>–</td>
<td>K</td>
<td>3) See Figure 22</td>
<td>P_8.6.0.3</td>
</tr>
<tr>
<td>Power Supply Clamping Voltage at TJ = - 40 ℃</td>
<td>VS(CLAMP) _- 40</td>
<td>33</td>
<td>36.5</td>
<td>42</td>
<td>V</td>
<td>Ivs = 5 mA TJ =- 40 °℃ See Figure 16</td>
<td>P_8.6.0.6</td>
</tr>
<tr>
<td>Power Supply Clamping Voltage at TJ ≥ 25 ℃</td>
<td>VS(CLAMP)_25</td>
<td>35</td>
<td>38</td>
<td>44</td>
<td>V</td>
<td>2) Ivs = 5 mA TJ ≥ 25°℃ See Figure 16</td>
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


### 8.6.1 Electrical Characteristics Protection


<table>
<caption>Table 16 Electrical Characteristics: Protection</caption>
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
<td>Latch Reset Delay Time after Fault Condition</td>
<td>tDELAY(LR)</td>
<td>40</td>
<td>70</td>
<td>100</td>
<td>ms</td>
<td>1)</td>
<td>P_8.6.4.1</td>
</tr>
<tr>
<td>Minimum DEN Pulse Duration for Latch Reset</td>
<td>İDEN(LR)</td>
<td>50</td>
<td>100</td>
<td>150</td>
<td>us</td>
<td>2)</td>
<td>P_8.6.4.2</td>
</tr>
</table>

1\) Functional test only.

2\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="37" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 38" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->
<!-- PageHeader="Protection" -->


## 8.7 Electrical Characteristics Protection - Power Output Stages

Vs = 6 V to 18 V, TJ =- 40 °C to +150 ℃
Typical values: Vs = 13.5 V, T ]= 25 ℃

Typical resistive load connected to the output for testing (unless otherwise specified):

RL =2.12


### 8.7.1 Protection Power Output Stage - 4 m22


<table>
<caption>Table 17 Electrical Characteristics: Protection - 4 m22</caption>
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
<td>Overload Detection Current at TJ =- 40 °℃</td>
<td>IL(OVLO) _- 40</td>
<td>107</td>
<td>119.5</td>
<td>132</td>
<td>A</td>
<td>1) TJ =- 40 ℃ d//dt = 0.4 A/us see Figure 23 and Figure 24</td>
<td>P_8.7.11.1</td>
</tr>
<tr>
<td>Overload Detection Current at TJ = 25 ℃</td>
<td>I L(OVL0)_25</td>
<td>103</td>
<td>117.5</td>
<td>132</td>
<td>A</td>
<td>2) TJ = 25 ℃ d//dt = 0.4 A/us see Figure 23 and Figure 24</td>
<td>P_8.7.11.7</td>
</tr>
<tr>
<td>Overload Detection Current at TJ =150 ℃</td>
<td>/L(OVLO)_150</td>
<td>88</td>
<td>101</td>
<td>114</td>
<td>A</td>
<td>2) TJ=150 ℃ d//dt = 0.4 A/us see Figure 23 and Figure 24</td>
<td>P_8.7.11.8</td>
</tr>
<tr>
<td>Overload Detection Current at High VDs</td>
<td>IL(OVL1)</td>
<td>–</td>
<td>72</td>
<td>–</td>
<td>A</td>
<td>2) d//dt = 0.4 A/us see Figure 23</td>
<td>P_8.7.11.5</td>
</tr>
<tr>
<td>Overload Detection Current Jump Start Condition</td>
<td>L(OV_JS)</td>
<td>–</td>
<td>72</td>
<td>–</td>
<td>A</td>
<td>2) V=&gt;VS(JS) d//dt = 0.4 A/us see Figure 25</td>
<td>P_8.7.11.6</td>
</tr>
</table>

1\) Functional test only.

2\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="38" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 39" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


<!-- PageHeader="Diagnosis" -->


## 9 Diagnosis

For diagnosis purpose, the BTS7004-1EPP provides a sense current signal (/Is) at pin IS. In case of disabled
diagnostic (DEN pin set to "low"), IS pin becomes high impedance.

A sense resistor RSENSE must be connected between IS pin and module ground if the current sense diagnosis is
used. RSENSE Value has to be higher than 820 02 (or 400 02 when a central Reverse Battery protection is present
on the battery feed) to limit the power losses in the sense circuitry. A typical value is RSENSE = 1.2 kQ2.

Due to the internal connection between IS pin and Vs supply voltage, it is not recommended to connect the IS
pin to the sense current output of other devices, if they are supplied by a different battery feed.

See Figure 30 for details as an overview.


<figure>
<figcaption>Figure 30 Diagnosis Block Diagram</figcaption>

VS

Output Channel

T

Overtemperature

Latch

IS Pin Control
Logic

IN

OUT

DEN

KILIS

/IS(FAULT)

\+
VDS(OLOFF)

/IS(OLOFF)

MUX

IS

RSENSE

Diagnosis_HEAT_1CH.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="39" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 40" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->
<!-- PageHeader="Diagnosis" -->


### 9.1 Overview

Table 18 gives a quick reference to the state of the IS pin during BTS7004-1EPP operation.


<table>
<caption>Table 18 SENSE Signal, Function of Application Condition</caption>
<tr>
<th>Application Condition</th>
<th>Input level</th>
<th>DEN level</th>
<th>VOUT</th>
<th>Diagnostic Output</th>
</tr>
<tr>
<td>Normal operation</td>
<td rowspan="6">“low"</td>
<td rowspan="14">“high"</td>
<td>~ GND</td>
<td>Z VIS(FAULT) if latch # 0</td>
</tr>
<tr>
<td>Short circuit to GND</td>
<td>~ GND</td>
<td>Z JIS(FAULT) if latch # 0</td>
</tr>
<tr>
<td>Overtemperature</td>
<td>Z</td>
<td>/ IS(FAULT)</td>
</tr>
<tr>
<td>Short circuit to Vs</td>
<td>Vs</td>
<td>/IS(OLOFF) (/IS(FAULT) if latch # 0)</td>
</tr>
<tr>
<td>Open Load</td>
<td>&lt;Vs - VDS(OLOF) &gt; Vs - VDS(OLOF) 1)</td>
<td>Z !IS(OLOFF) (in both cases /IS(FAULT) if latch # 0)</td>
</tr>
<tr>
<td>Inverse current</td>
<td>VOUT &gt; Vs</td>
<td>‘S(OLOF) (/IS(FAULT) if latch # 0)</td>
</tr>
<tr>
<td>Normal operation</td>
<td rowspan="8">“high"</td>
<td>~ Vs</td>
<td>/Is = /L / KILIS</td>
</tr>
<tr>
<td>Overload</td>
<td>&lt; Vs</td>
<td>/ IS(FAULT)</td>
</tr>
<tr>
<td>Short circuit to GND</td>
<td>~ GND</td>
<td>/ IS(FAULT)</td>
</tr>
<tr>
<td>Overtemperature</td>
<td>Z</td>
<td>/ IS(FAULT)</td>
</tr>
<tr>
<td>Short circuit to Vs</td>
<td>VS</td>
<td>IS &lt; /1 / KILIS</td>
</tr>
<tr>
<td>Open Load</td>
<td>~ Vs 2 )</td>
<td>Is = 1 Is(EN)</td>
</tr>
<tr>
<td>Under load (e.g. Output Voltage Limitation condition)</td>
<td>~ VS3)</td>
<td>IS(EN) &lt;115&lt;/L(NOM) / KILIS</td>
</tr>
<tr>
<td>Inverse current</td>
<td>VOUT &gt; Vs</td>
<td>Is = IS (EN)</td>
</tr>
<tr>
<td>All conditions</td>
<td>n.a.</td>
<td>“low"</td>
<td>n.a.</td>
<td>Z</td>
</tr>
</table>

1\) With additional pull-up resistor.

2\) The output current has to be smaller than /L(OL)-

3\) The output current has to be higher than / L(OL)-


### 9.2 Diagnosis in ON state

A current proportional to the load current (ratio kILIs =/L/ /Is) is provided at pin IS when the following conditions
are fulfilled:

· The power output stage is switched ON with VDs < VDS(OLOFF)

· The diagnosis is enabled

. No fault (as described in Chapter 8.3) is present or was present and not cleared yet (see Chapter 9.2.2 for
further details)

If a "hard" failure mode is present or was present and not cleared yet a current /IS(FAULT) is provided at IS pin.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="40" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 41" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


<!-- PageHeader="Diagnosis" -->


#### 9.2.1 Current Sense (KILIS)

The accuracy of the sense current depends on temperature and load current. lis increases linearly with IL
output current until it reaches the saturation current /IS(SAT). In case of Open Load at the output stage (/) close
to 0 A), the maximum sense current /IS(EN) (no load, diagnosis enabled) is specified. This condition is shown in
Figure 32. The blue line represents the ideal klus line, while the red lines show the behavior of a typical
product.

An external RC filter between IS pin and microcontroller ADC input pin is recommended to reduce signal ripple
and oscillations (a minimum time constant of 1 us for the RC filter is recommended).

The KILIs factor is specified with limits that take into account effects due to temperature, supply voltage and
manufacturing process. Tighter limits are possible (within a defined current window) with calibration:

· A well-defined and precise current (/L(CAL) is applied at the output during End of Line test at customer side

. The corresponding current at IS pin is measured and the kILIs is calculated (KILIS @ IL(CAL))

. Within the current range going from / L(CAL)_ to / L(CAL)_H the KILIS is equal to KILIS @ L(CAL) with limits defined by
AKILIS

The derating of kILIs after calibration is calculated using the formulas in Figure 31 and it is specified by AKILIS


<figure>

AKILIS, MAX = 100 · MAX

KILIS@IL(CAL)_L

1,
KILIS@IL(CAL)_H
KILIS@IL(CAL)

KILIS@IL(CAL)

1

AK ILIS, MIN = 100 · MIN

KILIS@IL(CAL)_L
KILIS@IL(CAL)

KILIS@IL(CAL)_H
1

1,

KILIS@IL(CAL)

Diagnosik_CHILIS ant

</figure>


Figure 31 AKILIs calculation formulas

The calibration is intended to be performed at TA(CAL) = 25℃. The parameter AKILIs includes the drift
overtemperature as well as the drift over the current range from /L(CAL)_ to /L(CAL)_H.


<figure>
<figcaption>Figure 32 Current Sense Ratio in Open Load at ON condition</figcaption>

/Is

/IS(OL)

IS(EN)

L(OL)

IL

Diagnosis_OLON_adv.emf

</figure>


#### 9.2.2 Fault Current (/IS(FAULT))

As soon as a protection event occurs, the value of the internal latch (see Chapter 8.3 for more details) is
changed from 0 to 1, a current /IS(FAULT) is provided by pin IS when DEN is set to "high" and the affected device
is switched OFF.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="41" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 42" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


##### Diagnosis

If internal latch is 1, and it is not reset, the current /IS(FAULT) is provided each time the device diagnosis is
activated by DEN=High.

Figure 33 shows the relation between /Is = IL / KILIS, 'IS(SAT) and /IS(FAULT).


<figure>
<figcaption>Figure 33 SENSE behavior - overview</figcaption>

lis

/IS (SAT).max

VIS (SAT)

/IS (FAULT).max

VIS (FAULT)

VIS (SAT).min
/IS(FAULT).min

ILI KLIS

İL(OVL).min

İL(OVL).max

IL

Diagnosis_HEAT_IISFAULT_IISSAT.emf

</figure>


### 9.3 Diagnosis in OFF state

When a power output stage is in OFF state, the BTS7004-1EPP can measure the drain-source voltage and
compare it with a threshold voltage. In this way, using some additional external components (a pull-down
resistor and a switchable pull-up current source), it is possible to detect if the load is missing or if there is a
short circuit to battery. If a Fault condition was detected by the device (if internal latch is 1, fault current is
provided by IS pin independent of drain-source or output voltage, as long as DEN=High) a current /Is(FAULT) iS
provided by IS pin each time the channel diagnosis is checked also in OFF state. See Chapter 9.2.2 for further
details.


#### 9.3.1 Open Load current (/Is(OLOFF))

In OFF state, when DEN pin is set to "high", the Vps voltage is compared with a threshold voltage VDS(OLOFF). If
the load is properly connected and there is no short circuit to battery, VDs ~ Vs therefore VDs > VDS(OLOFF). When
the diagnosis is active and VDs ≤ VDS(OLOFF), a current /IS(OLOFF) is provided by IS pin. Figure 34 shows the
relationship between /IS(OLOFF) and /IS(FAULT) as functions of Vps. The two currents do not overlap making it always
possible to differentiate between Open Load in OFF and Fault condition.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="42" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 43" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


<!-- PageHeader="Diagnosis" -->


<figure>
<figcaption>Figure 34 lIs in OFF State</figcaption>

his

/IS(FAUL T)

/IS(OLOFF)

VDS(OLOFF)

VDS

Diagnosis_PROFET_IISOL OFF.emf

</figure>


It is necessary to wait a time tIS(OLOFF)_D between the falling edge of the input pin and the sensing at pin IS for
Open Load in OFF diagnosis to allow the internal comparator to settle. In Figure 35 the timings for an Open
Load detection are shown - the load is always disconnected.


<figure>
<figcaption>Figure 35 Open Load in OFF Timings - load disconnected</figcaption>

IN

t

DEN

ts(OLOFF)_D

t

VOUT

~ Vs

VDS(OLOFF)

Load
connect ed

t

/Is

/IS(OLOFF)

/ S(OL)

t

Diagnosis_PROFET_OLOFF_time.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="43" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 44" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


<!-- PageHeader="Diagnosis" -->


## 9.4 SENSE Timings

Figure 36 shows the timing during settling tsIS(ON) and disabling tsIS(OFF) of the SENSE (including the case of load
change). As a proper signal cannot be established before the load current is stable (therefore before tON),
tsIS(DIAG) ≤3x(tON_max +tsIS(ON)_max).


<figure>
<figcaption>Figure 36 SENSE Settling / Disabling Timing</figcaption>

IN

OFF

ON

OFF

t

DEN

t

IL

tsIS (LC)

tsIS (OFF)

tsIS (ON)

tsIS (OFF)

t

lIs

tsIS (DIAG)

Diagnose_PROFET_SENSE_timings_Heat.emf

t

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="44" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 45" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->

Diagnosis


## 9.5 Electrical Characteristics Diagnosis

Vs = 6 V to 18 V, TJ =- 40 °C to +150 ℃
Typical values: Vs = 13.5 V, T ]= 25 ℃

Typical resistive load connected to the output for testing (unless otherwise specified):

RL = 2.12


<table>
<caption>Table 19 Electrical Characteristics: Diagnosis - General</caption>
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
<td>/ IS(SAT)</td>
<td>4.4</td>
<td>–</td>
<td>15</td>
<td>mA</td>
<td>1) VSIS = Vs - VIS≥ 2 V See Figure 33</td>
<td>P_9.6.0.1</td>
</tr>
<tr>
<td>SENSE Leakage Current when Disabled</td>
<td>/IS(OFF)</td>
<td>–</td>
<td>0.01</td>
<td>0.5</td>
<td>µA</td>
<td>DEN = "low" VIS = 0 V</td>
<td>P_9.6.0.2</td>
</tr>
<tr>
<td>SENSE Leakage Current when Enabled at TJ ≤ 85 ℃</td>
<td>/IS(EN)_85</td>
<td>–</td>
<td>0.2</td>
<td>1</td>
<td>µA</td>
<td>1) TJ ≤85°℃ DEN = "high" 1=0A See Figure 32</td>
<td>P_9.6.0.3</td>
</tr>
<tr>
<td>SENSE Leakage Current when Enabled at TJ = 150 ℃</td>
<td>/IS(EN)_150</td>
<td>–</td>
<td>0.2</td>
<td>1</td>
<td>HA</td>
<td>TJ=150 ℃ DEN = "high" IL = 0 A See Figure 32</td>
<td>P_9.6.0.4</td>
</tr>
<tr>
<td>SENSE Operative Range for KILIS Operation (Vs - VIs)</td>
<td>VSIS_k</td>
<td>–</td>
<td>0.5</td>
<td>1</td>
<td>V</td>
<td>1) Vs =6V IN = DEN = "high" IL ≤2* /L(NOM)</td>
<td>P_9.6.0.6</td>
</tr>
<tr>
<td>SENSE Operative Range for Open Load at OFF Diagnosis (Vs - VIS)</td>
<td>VSIS_OL</td>
<td>–</td>
<td>0.5</td>
<td>1</td>
<td>V</td>
<td>1) Vs =6V IN = "low" DEN = "high"</td>
<td>P_9.6.0.7</td>
</tr>
<tr>
<td>SENSE Operative Range for Fault Diagnosis (Vs - VIs)</td>
<td>VSIS_F</td>
<td>–</td>
<td>0.5</td>
<td>1</td>
<td>V</td>
<td>1) Vs = 6V IN = "low" DEN = "high" latch ± 0</td>
<td>P_9.6.0.8</td>
</tr>
<tr>
<td>Power Supply to IS Pin Clamping Voltage at TJ =- 40 ℃</td>
<td>SIS(CLAMP) _- 40</td>
<td>33</td>
<td>36.5</td>
<td>42</td>
<td>V</td>
<td>lis = 1 mA TJ =- 40 ℃ See Figure 16</td>
<td>P_9.6.0.9</td>
</tr>
<tr>
<td>Power Supply to IS Pin Clamping Voltage at TJ ≥ 25℃</td>
<td>SIS(CLAMP)_25</td>
<td>35</td>
<td>38</td>
<td>44</td>
<td>V</td>
<td>2) lis = 1 mA TJ ≥25℃ See Figure 16</td>
<td>P_9.6.0.10</td>
</tr>
</table>

1\) Not subject to production test - specified by design.

2\) Tested at TJ = 150°C.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="45" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 46" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->

Diagnosis


### 9.5.1 Electrical Characteristics Diagnosis


<table>
<caption>Table 20 Electrical Characteristics: Diagnosis</caption>
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
<td>SENSE Fault Current</td>
<td>/IS(FAULT)</td>
<td>4.4</td>
<td>5.5</td>
<td>10</td>
<td>mA</td>
<td>–</td>
<td>P_9.6.4.1</td>
</tr>
<tr>
<td>SENSE Open Load in OFF Current</td>
<td>"IS(OLOFF)</td>
<td>1.8</td>
<td>2.5</td>
<td>3.5</td>
<td>mA</td>
<td>–</td>
<td>P_9.6.4.2</td>
</tr>
<tr>
<td>SENSE Open Load in OFF Delay Time</td>
<td>tIS(OLOFF)_D</td>
<td>70</td>
<td>185</td>
<td>300</td>
<td>μς</td>
<td>VDS &lt; VOL(OF) from IN falling edge to VIS = RSENSE * 0.9 * /IS(OLOFF), MIN DEN = "high"</td>
<td>P_9.6.4.4</td>
</tr>
<tr>
<td>Open Load Vps Detection Threshold in OFF State</td>
<td>VDS(OLOFF)</td>
<td>1.3</td>
<td>1.8</td>
<td>2.3</td>
<td>V</td>
<td>–</td>
<td>P_9.6.4.5</td>
</tr>
<tr>
<td>SENSE Settling Time with Nominal Load Current Stable</td>
<td>İşIS(ON)</td>
<td>–</td>
<td>5</td>
<td>40</td>
<td>μς</td>
<td>IL=IL(NOM) DEN from "low" to “high"</td>
<td>P_9.6.4.6</td>
</tr>
<tr>
<td>SENSE Disable Time</td>
<td>İşIS(OFF)</td>
<td>–</td>
<td>5</td>
<td>20</td>
<td>μς</td>
<td>1) From DEN falling edge to lis = /IS(OFF) See Figure 36</td>
<td>P_9.6.4.8</td>
</tr>
<tr>
<td>SENSE Settling Time after Load Change</td>
<td>tsIS(LC)</td>
<td>–</td>
<td>5</td>
<td>20</td>
<td>μς</td>
<td>1) from /L = IL18 to I L = I L19 See Figure 36</td>
<td>P_9.6.4.9</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="46" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 47" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->

Diagnosis


## 9.6 Electrical Characteristics Diagnosis - Power Output Stages

Vs = 6 V to 18 V, TJ =- 40 °C to +150 ℃
Typical values: Vs = 13.5 V, T ] = 25 ℃

Typical resistive load connected to the output for testing (unless otherwise specified):
RL = 2.12


### 9.6.1 Diagnosis Power Output Stage - 4 m22


<table>
<caption>Table 21 Electrical Characteristics: Diagnosis - 4 m22</caption>
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
<td>60</td>
<td>90</td>
<td>120</td>
<td>mA</td>
<td>"Is = /Is(OL) = 4 µA see Figure 32</td>
<td>P_9.7.11.1</td>
</tr>
<tr>
<td>Current Sense Ratio at IL=/L04</td>
<td>KILIS04</td>
<td>-65%</td>
<td>20000</td>
<td>+65%</td>
<td></td>
<td>/L04 = 50 mA</td>
<td>P_9.7.11.8</td>
</tr>
<tr>
<td>Current Sense Ratio at 1L=/L07</td>
<td>KILIS07</td>
<td>-65%</td>
<td>20000</td>
<td>+65%</td>
<td></td>
<td>/L07 = 200 mA</td>
<td>P_9.7.11.11</td>
</tr>
<tr>
<td>Current Sense Ratio at 1L=1109</td>
<td>KILIS09</td>
<td>-55%</td>
<td>20000</td>
<td>+55%</td>
<td></td>
<td>/L09 = 450 mA</td>
<td>P_9.7.11.13</td>
</tr>
<tr>
<td>Current Sense Ratio at /L=1113</td>
<td>KILIS13</td>
<td>-40%</td>
<td>20000</td>
<td>+40%</td>
<td></td>
<td>/113 = 2 A</td>
<td>P_9.7.11.17</td>
</tr>
<tr>
<td>Current Sense Ratio at IL = IL16</td>
<td>KILIS16</td>
<td>-24%</td>
<td>20000</td>
<td>+24%</td>
<td></td>
<td>/L16 = 5.5 A</td>
<td>P_9.7.11.20</td>
</tr>
<tr>
<td>Current Sense Ratio at IL = IL18</td>
<td>KILIS18</td>
<td>-8%</td>
<td>20000</td>
<td>+8%</td>
<td></td>
<td>IL18 = 10 A</td>
<td>P_9.7.11.22</td>
</tr>
<tr>
<td>Current Sense Ratio at 1L=1119</td>
<td>KILIS19</td>
<td>-8%</td>
<td>20000</td>
<td>+8%</td>
<td></td>
<td>1) /119 = 15 A</td>
<td>P_9.7.11.23</td>
</tr>
<tr>
<td>SENSE Current Derating with Low Current Calibration</td>
<td>AKILIS (OL)</td>
<td>-30</td>
<td>0</td>
<td>+30</td>
<td>%</td>
<td>1) IL(CAL) = /107 IL(CAL)_H = /L09 /L(CAL)_L = /L04 TA(CAL) = 25 ℃</td>
<td>P_9.7.11.27</td>
</tr>
<tr>
<td>SENSE Current Derating with Nominal Current Calibration</td>
<td>AKILIS(NOM)</td>
<td>-4</td>
<td>0</td>
<td>+4</td>
<td>%</td>
<td>1) IL(CAL) = /L18 IL(CAL)_H = /L19 IL(CAL)_L = /L16 TA(CAL) = 25 ℃</td>
<td>P_9.7.11.29</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="47" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 48" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

Infineon

</figure>


# Application Information


## 10 Application Information

Note:
The following information is given as a hint for the implementation of the device only and shall not
be regarded as a description or warranty of a certain functionality, condition or quality of the device.


## 10.1 Application setup


<figure>
<figcaption>Figure 37 BTS7004-1EPP Application Diagram</figcaption>

VBAT

ZWIRE

Optional

[Optional

Cvs

CVSGND

T1

Logic Supply

RGND

VDD

GND

VS

GPIO

RIN

IN

ROL

GPIO

RDEN

DEN

OUT

PROFET™+2
12V

RPD

COUT0

ZWIRE

Dz2

Cvs2

Microcontroller

ADC

RADC

RIS PROT

IS

VSS

CSENSE

Dz1

RSENSE

ZLOAD*

Logic GND

Power GND

Optional

Chassis GND

*See Chapter 1 „Potential Applications“

App_ICH_INTDE)_CVG.Jernf

</figure>

Note:
This is a very simplified example of an application circuit. The function must be verified in the real
application.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="48" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 49" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


# Application Information


## 10.2 External Components


<table>
<caption>Table 22 Suggested Component values</caption>
<tr>
<th>Reference</th>
<th>Value</th>
<th>Purpose</th>
</tr>
<tr>
<td>RIN</td>
<td>4.7 kQ</td>
<td>Protection of the microcontroller during Overvoltage and Reverse Polarity Necessary to switch OFF BTS7004-1EPP output during Loss of Ground</td>
</tr>
<tr>
<td>RDEN</td>
<td>4.7 k22</td>
<td>Protection of the microcontroller during Overvoltage and Reverse Polarity Necessary to switch OFF BTS7004-1EPP output during Loss of Ground</td>
</tr>
<tr>
<td>RPD</td>
<td>47 kQ</td>
<td>Output polarization (pull-down) Ensures polarization of BTS7004-1EPP outputs to distinguish between Open Load and Short to Vs in OFF Diagnosis</td>
</tr>
<tr>
<td>ROL</td>
<td>1.5 kQ</td>
<td>Output polarization (pull-up) Ensures polarization of BTS7004-1EPP output during Open Load in OFF diagnosis</td>
</tr>
<tr>
<td>COUT</td>
<td>10 nF</td>
<td>Protection of BTS7004-1EPP output during ESD events and BCI</td>
</tr>
<tr>
<td>T1</td>
<td>BC 807</td>
<td>Switch the battery voltage for Open Load in OFF diagnosis</td>
</tr>
<tr>
<td>Cvs</td>
<td>100 nF</td>
<td>Filtering of voltage spikes on the battery line</td>
</tr>
<tr>
<td>CVSGND</td>
<td>47 nF</td>
<td>Buffer capacitor for fast transient See Table 5 (P_4.3.0.7) for the boundary conditions A placeholder on PCB layout is recommended</td>
</tr>
<tr>
<td>DZ2</td>
<td>33 V TVS Diode</td>
<td>Transient Voltage Suppressor diode Protection during Overvoltage and in case of Loss of Battery while driving an inductive load</td>
</tr>
<tr>
<td>Cvs2</td>
<td>–</td>
<td>Filtering / buffer capacitor located at VBAT connector</td>
</tr>
<tr>
<td>RSENSE</td>
<td>1.2 kQ</td>
<td>SENSE resistor</td>
</tr>
<tr>
<td>RIS_PROT</td>
<td>4.7 kQ2</td>
<td>Protection during Overvoltage, Reverse Polarity, Loss of Ground Value to be tuned according to microcontroller specifications</td>
</tr>
<tr>
<td>DZ1</td>
<td>7 V Z-Diode</td>
<td>Protection of microcontroller during Overvoltage</td>
</tr>
<tr>
<td>RADC</td>
<td>4.7 kQ2</td>
<td>Protection of microcontroller ADC input during Overvoltage, Reverse Polarity, Loss of Ground Value to be tuned according to microcontroller specifications</td>
</tr>
<tr>
<td>CSENSE</td>
<td>220 pF</td>
<td>Sense signal filtering A time constant (RADC + RIS_PROT) * CSENSE longer than 1 us is recommended</td>
</tr>
<tr>
<td>RGND</td>
<td>47 Ω</td>
<td>Protection in case of Overvoltage and Loss of Battery while driving inductive loads</td>
</tr>
</table>


## 10.3 Further Application Information

· Please contact us for information regarding the Pin FMEA

. For further information you may contact http://www.infineon.com/

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="49" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 50" -->


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


<figure>

<!-- PageHeader="Infineon" -->

</figure>


# Package Outlines


## 11 Package Outlines


<figure>
<figcaption>Figure 38 PG-TSDSO-14 (Thin (Slim) Dual Small Outline 14 pins) Package Outline</figcaption>

(0.95)

0.05±0.05

STANDOFF

1.15 MAX.

1\)

1\)

0.25

GAUGE

PLANE

4.9±0.1

0.1

(0.2)

D

3.9±0.1

2x

0.1

2x

8

C

0.08

C

0.67±0.25

0

SEATING COPLANARITY
PLANE

14x

6+0.2

0.2
D

14x

0.25±0.05

2\)

O

0.25

M

A-B
C

14x

BOTTOM VIEW

2.65±0.1

A

14

14

F

0

.

CICT

INDEX

4

Y

1

0

0.15M

D

MARKING

B

0.65

4±0.1

0

0.15M

A-B

1\) DOES NOT INCLUDE PLASTIC OR METAL PROTRUSION OF 0.15 MAX. PER SIDE

2\) DAMBAR PROTUSION SHALL BE MAXIMUM 0.1MM TOTAL IN EXCESS OF LEAD WIDTH
ALL DIMENSIONS ARE IN UNITS MM

THE DRAWING IS IN COMPLIANCE WITH ISO 128 & PROJECTION METHOD 1 [@]

</figure>


<figure>
<figcaption>Figure 39 PG-TSDSO-14 (Thin (Slim) Dual Small Outline 14 pins) Package pads and stencil</figcaption>

0.65

0.45

0.65

0.45

1.31

1.31

2.85

2.85

2.65

2.65

2.85

2.85

1.075

4

1.85

copper

solder mask

stencil apertures

ALL DIMENSIONS ARE IN UNITS MM

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="50" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 51" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


# Package Outlines


## Green product (RoHS compliant)

To meet the world-wide customer requirements for environmentally friendly products and to be compliant
with government regulations the device is available as a green product. Green products are RoHS-Compliant
(i.e Pb-free finish on leads and suitable for Pb-free soldering according to IPC/JEDEC J-STD-020).


## Further information on packages

https://www.infineon.com/packages

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="51" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 52" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->

Revision History


### 12 Revision History


<table>
<caption>Table 23 BTS7004-1EPP - List of changes</caption>
<tr>
<th>Revision</th>
<th>Changes</th>
</tr>
<tr>
<td>1.03, 2019-10-15</td>
<td>P_6.5.21.1 updated (Typ .: 0.01 µA &gt; 0.05 µA) P_8.7.11.1, P_8.7.11.7, P_8.7.11.8 updated (added in Note or Test Condition: link to Figure 24) P_7.5.11.5 updated (added in Note or Test Condition: see Figure 18) P_7.5.11.12 updated (added in Note or Test Condition: see Figure 20; deleted unnecessary space in Symbol: |dVOUT / dt | &gt; |dVOUT / dt|) P_8.7.11.6 updated (added in Note or Test Condition: see Figure 25) P_9.7.11.1 updated (added in Note or Test Condition: see Figure 32) Figure 1, Figure 37 updated P_4.3.0.7 added Table 22 updated Chapter 5.1 updated (added: see Chapter 10 for the complete application setup overview)</td>
</tr>
<tr>
<td>1.02, 2019-06-26</td>
<td>Chapter 9.2 updated (2 V &gt; VDS(OLOFF)) General: updated (ReverSave™ &gt; ReverseON) Chapter 1 updated ((inserted headline "Product Validation"), (Qualified in accordance with AEC Q100 grade 1 &gt; Qualified for automotive applications. Product validation according to AEC-Q100 Grade 1.)) General: updated Product Name (High Current PROFET™ 12V &gt; PROFET™+2 12V)</td>
</tr>
<tr>
<td>1.01, 2019-02-05</td>
<td>Figure 9, Figure 10 updated P_7.5.11.10 updated (Min./Typ./Max .: - / - / 10 µA &gt; - / - / 15 µA) Page 1: updated (figure product) Table 22 updated (punctuation) Chapter 9.3, Chapter 9.3.1 updated (typo) Page 1: updated (Package PG-TSDSO-14-22 &gt; Package PG-TSDSO-14) Figure 38 updated (PG-TSDSO-14-22 (Thin (Slim) Dual Small Outline 14 pins) Package Outline &gt; PG-TSDSO-14 (Thin (Slim) Dual Small Outline 14 pins) Package Outline) Figure 39 updated (PG-TSDSO-14-22 (Thin (Slim) Dual Small Outline 14 pins) Package pads and stencil &gt; PG-TSDSO-14 (Thin (Slim) Dual Small Outline 14 pins) Package pads and stencil) Table 1 updated (Parameter: Minimum Overvoltage protection (T] = 25 ℃) &gt; Minimum Overvoltage protection (TJ ≥ 25 ℃)) Table 1 updated (Symbol: /VS(OFF) &gt; |VS(OF)_85) P_6.5.21.1 updated (Symbol: /VS(OFF) &gt; /VS(OFF)_85) P_6.5.21.2 updated (Symbol: /VS(OFF) &gt; |VS(OF)_150) P_4.2.11.3 updated (Note or Test Condition: &gt; -) Figure Application Diagram, Figure 29, Figure 37 updated P_4.1.0.21, P_4.1.0.22, P_4.1.0.23, P_4.1.0.24 updated (footnote ESD standards) Table 1 updated (RDS(ON) &gt; RDS(ON)_150), (VDS(CLAMP) &gt; VDS(CLAMP)_25) Chapter 8.5.2 updated (phrasing) Chapter 6.4, Chapter 7.5, Chapter 8.7, Chapter 9.6 updated (added conditions) Figure 28 updated (Over Load &gt; Overload, deleted bow) P_9.6.4.8, P_9.6.4.9 updated (removed line before the footnote)</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="52" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 53" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->

Revision History


<table>
<caption>Table 23 BTS7004-1EPP - List of changes</caption>
<tr>
<th>Revision</th>
<th>Changes</th>
</tr>
<tr>
<td></td>
<td>Chapter 1 updated (Application &gt; Potential Applications) P_4.1.0.36 updated (Symbol: /DI &gt;/DI(REV)) P_4.4.0.1 updated (footnote) P_4.4.0.2 updated (footnote) P_4.4.0.3 updated (footnote) Chapter 5 updated (space) P_5.4.0.5 updated (Symbol: /DI &gt; /DI(H) P_5.4.0.6 updated (Symbol: [D] &gt; /DI(L)) Chapter 7.5 updated Figure 20 updated Figure 17, Figure 18 updated (filename) P_7.5.11.9 updated (min/typ/max: - /0.05/0.8 - - /0.05/0.5 µA) Figure 29, Figure 30 updated P_9.6.0.6 updated (removed unnecessary line-break) P_9.6.4.4 updated (test condition: symbol / S(OLOF),MIN) &gt; IS(OLOF),MIN) P_9.6.4.9 updated (test condition: from /L = /116 to /L = /118 &gt; from /L = /118 to /L = /119)</td>
</tr>
<tr>
<td>1.00, 2017-11-17</td>
<td>Data Sheet available</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="53" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 54" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->
<!-- PageHeader="Table of Contents" -->


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
<td>3</td>
</tr>
<tr>
<td>2.1</td>
<td>Block Diagram</td>
<td>3</td>
</tr>
<tr>
<td>2.2</td>
<td>Terms</td>
<td>4</td>
</tr>
<tr>
<td>3</td>
<td>Pin Configuration</td>
<td>5</td>
</tr>
<tr>
<td>3.1</td>
<td>Pin Assignment</td>
<td>5</td>
</tr>
<tr>
<td>3.2</td>
<td>Pin Definitions and Functions</td>
<td>6</td>
</tr>
<tr>
<td>4</td>
<td>General Product Characteristics</td>
<td>7</td>
</tr>
<tr>
<td>4.1</td>
<td>Absolute Maximum Ratings - General</td>
<td>7</td>
</tr>
<tr>
<td>4.2</td>
<td>Absolute Maximum Ratings - Power Stages</td>
<td>8</td>
</tr>
<tr>
<td>4.2.1</td>
<td>Power Stage - 4 m22</td>
<td>8</td>
</tr>
<tr>
<td>4.3</td>
<td>Functional Range</td>
<td>9</td>
</tr>
<tr>
<td>4.4</td>
<td>Thermal Resistance</td>
<td>10</td>
</tr>
<tr>
<td>4.4.1</td>
<td>PCB Setup</td>
<td>10</td>
</tr>
<tr>
<td>4.4.2</td>
<td>Thermal Impedance</td>
<td>12</td>
</tr>
<tr>
<td>5</td>
<td>Logic Pins</td>
<td>13</td>
</tr>
<tr>
<td>5.1</td>
<td>Input Pin (IN)</td>
<td>13</td>
</tr>
<tr>
<td>5.2</td>
<td>Diagnosis Pin</td>
<td>14</td>
</tr>
<tr>
<td>5.3</td>
<td>Electrical Characteristics Logic Pins</td>
<td>14</td>
</tr>
<tr>
<td>6</td>
<td>Power Supply</td>
<td>15</td>
</tr>
<tr>
<td>6.1</td>
<td>Operation Modes</td>
<td>15</td>
</tr>
<tr>
<td>6.1.1</td>
<td>OFF mode</td>
<td>16</td>
</tr>
<tr>
<td>6.1.2</td>
<td>ON mode</td>
<td>16</td>
</tr>
<tr>
<td>6.1.3</td>
<td>OFF_Diag mode</td>
<td>16</td>
</tr>
<tr>
<td>6.1.4</td>
<td>ON_Diag mode</td>
<td>16</td>
</tr>
<tr>
<td>6.1.5</td>
<td>Fault mode</td>
<td>16</td>
</tr>
<tr>
<td>6.2</td>
<td>Undervoltage on Vs</td>
<td>16</td>
</tr>
<tr>
<td>6.3</td>
<td>Electrical Characteristics Power Supply</td>
<td>18</td>
</tr>
<tr>
<td>6.4</td>
<td>Electrical Characteristics Power Supply - Product Specific</td>
<td>19</td>
</tr>
<tr>
<td>6.4.1</td>
<td>BTS7004-1EPP</td>
<td>19</td>
</tr>
<tr>
<td>7</td>
<td>Power Stages</td>
<td>20</td>
</tr>
<tr>
<td>7.1</td>
<td>Output ON-State Resistance</td>
<td>20</td>
</tr>
<tr>
<td>7.2</td>
<td>Switching loads</td>
<td>20</td>
</tr>
<tr>
<td>7.2.1</td>
<td>Switching Resistive Loads</td>
<td>20</td>
</tr>
<tr>
<td>7.2.2</td>
<td>Switching Inductive Loads</td>
<td>21</td>
</tr>
<tr>
<td>7.2.3</td>
<td>Output Voltage Limitation</td>
<td>22</td>
</tr>
<tr>
<td>7.3</td>
<td>Advanced Switching Characteristics</td>
<td>22</td>
</tr>
<tr>
<td>7.3.1</td>
<td>Inverse Current behavior</td>
<td>22</td>
</tr>
<tr>
<td>7.3.2</td>
<td>Cross Current robustness with H-Bridge configuration</td>
<td>24</td>
</tr>
<tr>
<td>7.4</td>
<td>Electrical Characteristics Power Stages</td>
<td>25</td>
</tr>
<tr>
<td>7.4.1</td>
<td>Electrical Characteristics Power Stages</td>
<td>25</td>
</tr>
<tr>
<td>7.5</td>
<td>Electrical Characteristics - Power Output Stages</td>
<td>26</td>
</tr>
<tr>
<td>7.5.1</td>
<td>Power Output Stage - 4 m22</td>
<td>26</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="54" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 55" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7004-1EPP PROFET™+2 12V" -->


### Table of Contents


<table>
<tr>
<th>8</th>
<th>Protection</th>
<th>28</th>
</tr>
<tr>
<td>8.1</td>
<td>Overtemperature Protection</td>
<td>28</td>
</tr>
<tr>
<td>8.2</td>
<td>Overload Protection</td>
<td>29</td>
</tr>
<tr>
<td>8.3</td>
<td>Protection and Diagnosis in case of Fault</td>
<td>31</td>
</tr>
<tr>
<td>8.3.1</td>
<td>Intelligent Latch Strategy</td>
<td>31</td>
</tr>
<tr>
<td>8.4</td>
<td>Additional protections</td>
<td>35</td>
</tr>
<tr>
<td>8.4.1</td>
<td>Reverse Polarity Protection</td>
<td>35</td>
</tr>
<tr>
<td>8.4.2</td>
<td>Overvoltage Protection</td>
<td>35</td>
</tr>
<tr>
<td>8.5</td>
<td>Protection against loss of connection</td>
<td>36</td>
</tr>
<tr>
<td>8.5.1</td>
<td>Loss of Battery and Loss of Load</td>
<td>36</td>
</tr>
<tr>
<td>8.5.2</td>
<td>Loss of Ground</td>
<td>36</td>
</tr>
<tr>
<td>8.6</td>
<td>Electrical Characteristics Protection</td>
<td>37</td>
</tr>
<tr>
<td>8.6.1</td>
<td>Electrical Characteristics Protection</td>
<td>37</td>
</tr>
<tr>
<td>8.7</td>
<td>Electrical Characteristics Protection - Power Output Stages</td>
<td>38</td>
</tr>
<tr>
<td>8.7.1</td>
<td>Protection Power Output Stage - 4 m22</td>
<td>38</td>
</tr>
<tr>
<td>9</td>
<td>Diagnosis</td>
<td>39</td>
</tr>
<tr>
<td>9.1</td>
<td>Overview</td>
<td>40</td>
</tr>
<tr>
<td>9.2</td>
<td>Diagnosis in ON state</td>
<td>40</td>
</tr>
<tr>
<td>9.2.1</td>
<td>Current Sense (KILIS)</td>
<td>41</td>
</tr>
<tr>
<td>9.2.2</td>
<td>Fault Current (/IS(FAULT))</td>
<td>41</td>
</tr>
<tr>
<td>9.3</td>
<td>Diagnosis in OFF state</td>
<td>42</td>
</tr>
<tr>
<td>9.3.1</td>
<td>Open Load current (/IS(OLOFF))</td>
<td>42</td>
</tr>
<tr>
<td>9.4</td>
<td>SENSE Timings</td>
<td>44</td>
</tr>
<tr>
<td>9.5</td>
<td>Electrical Characteristics Diagnosis</td>
<td>45</td>
</tr>
<tr>
<td>9.5.1</td>
<td>Electrical Characteristics Diagnosis</td>
<td>46</td>
</tr>
<tr>
<td>9.6</td>
<td>Electrical Characteristics Diagnosis - Power Output Stages</td>
<td>47</td>
</tr>
<tr>
<td>9.6.1</td>
<td>Diagnosis Power Output Stage - 4 m22</td>
<td>47</td>
</tr>
<tr>
<td>10</td>
<td>Application Information</td>
<td>48</td>
</tr>
<tr>
<td>10.1</td>
<td>Application setup</td>
<td>48</td>
</tr>
<tr>
<td>10.2</td>
<td>External Components</td>
<td>49</td>
</tr>
<tr>
<td>10.3</td>
<td>Further Application Information</td>
<td>49</td>
</tr>
<tr>
<td>11</td>
<td>Package Outlines</td>
<td>50</td>
</tr>
<tr>
<td>12</td>
<td>Revision History</td>
<td>52</td>
</tr>
<tr>
<td></td>
<td>Table of Contents</td>
<td>54</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="55" -->
<!-- PageFooter="Rev. 1.03 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 56" -->


Trademarks

All referenced product or service names and trademarks are the property of their respective owners.

Edition 2019-10-15
Published by
Infineon Technologies AG
81726 Munich, Germany

2019 Infineon Technologies AG.
All Rights Reserved.

Do you have a question about any
aspect of this document?
Email: erratum@infineon.com

Document reference
Z8F65709152


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


## WARNINGS

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
