

<!-- PageNumber="Side 1" -->


<figure>

infineon

</figure>


BTS7020-2EPA

PROFET™+2 12V
Smart High-Side Power Switch


<figure>

O
Qualified

AEC

·

Y

RoHS

</figure>


2x 20 ml2


<table>
<tr>
<td>Package</td>
<td>PG-TSDSO-14</td>
</tr>
<tr>
<td>Marking</td>
<td>7020-2A</td>
</tr>
</table>


# 1 Overview


## Potential Applications

· Suitable for resistive, inductive and capacitive loads

· Replaces electromechanical relays, fuses and discrete circuits

· Driving capability suitable for 5 A loads and high inrush current loads such
as 2 x P27W + R5W lamps or equivalent electronic loads (e.g. LED modules)


<figure>

JA
Infineon
TSDSO-14

</figure>


<figure>
<figcaption>Figure 1 BTS7020-2EPA Application Diagram. Further information in Chapter 10</figcaption>

VBAT

ZWIRE

Optional

Optional

Cvs

CVSGNDI

T1

Logic Supply

RGND

VDD

GND

VS

GPIO

RIN

IN0

ROL

GPIO

RIN

IN1

GPIO

RDEN

DEN

OUT0

GPIO

ROSEL

DSEL

PROFET™+2
12V

RPD

COUT0

Cvs2

Microcontroller

ZWIRE

Dz2

OUT1

ADC

RADC

RIS PRO

1

IS

COUT1

ZWIRE

VSS

CSENSE

DZ1

SENSE

LOAD*

ZLOAD

Logic GND

Power GND

Optional

Chassis GND

*See Chapter 1 „Potential Applications“

App_2CH_INTDID_CVG_LDLml

</figure>


<!-- PageFooter="Data Sheet www.infineon.com" -->
<!-- PageNumber="1" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 2" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


### Overview


## Basic Features

· High-Side Switch with Diagnosis and Embedded Protection

· Part of PROFET™+2 12V Family

· ReverseON for low power dissipation in Reverse Polarity

· Switch ON capability while Inverse Current condition (InverseON)

· Green Product (RoHS compliant)


## Protection Features

· Absolute and dynamic temperature limitation with controlled restart

· Overcurrent protection (tripping) with Intelligent Restart Control

· Undervoltage shutdown

· Overvoltage protection with external components


## Diagnostic Features

· Proportional load current sense

· Open Load in ON and OFF state

· Short circuit to ground and battery


## Product Validation

Qualified for automotive applications. Product validation according to AEC-Q100 Grade 1.


## Description

The BTS7020-2EPA is a Smart High-Side Power Switch, providing protection functions and diagnosis. The
device is integrated in SMART7 technology.


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
<td>VS</td>
<td>28 V</td>
</tr>
<tr>
<td>Minimum Overvoltage protection (T) ≥ 25 ℃)</td>
<td>VDS(CLAMP)_25</td>
<td>35 V</td>
</tr>
<tr>
<td>Maximum current in Sleep mode (T) ≤ 85 ℃)</td>
<td>IVS(SLEEP)_85</td>
<td>0.6 µA</td>
</tr>
<tr>
<td>Maximum operative current</td>
<td>IGND(ACTIVE)</td>
<td>4 mA</td>
</tr>
<tr>
<td>Maximum ON-state resistance (T) = 150 ℃)</td>
<td>RDS(ON)_150</td>
<td>23.7 ml2</td>
</tr>
<tr>
<td>Nominal load current (TA = 85 ℃)</td>
<td>L(NOM)</td>
<td>5 A</td>
</tr>
<tr>
<td>Typical current sense ratio at /L = IL(NOM)</td>
<td>KILIS</td>
<td>3700</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="2" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 3" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


# Block Diagram and Terms


## 2 Block Diagram and Terms


### 2.1 Block Diagram


<figure>
<figcaption>Figure 2 Block Diagram of BTS7020-2EPA</figcaption>

VS

☒

Supply Voltage
Monitoring

Overvoltage
Protection

Internal Power Supply

Intelligent Restart
Control

Channel 1

Channel 0

IS
☒

SENSE Output

Voltage Sensor

T

Overtemperature

T

IN0
☒

Overvoltage
Clamping

\+

IN1
☒

ESD
Protection
+
Input Logic

Driver
Logic

Gate Control
+
Chargepump

DEN
☒

Overcurrent
Protection

OUT1

DSEL
☒

ReverseON
InverseON

☒
OUT0

Internal Reverse
Polarity Protection

Load Current Sense

GND Circuitry

Output Voltage Limitation

GND
☒

Block_PROFET 2ch_REVON.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="3" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 4" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


# Block Diagram and Terms


## 2.2 Terms

Figure 3 shows all terms used in this data sheet, with associated convention for positive values.


<figure>
<figcaption>Figure 3 Voltage and Current Convention</figcaption>

Ivs

☒
VS

VsIs

/INn

☒
INn

VDSn

IDEN

☒
DEN

/Ln

Vs

/DSEL

OUTn
☒

☒
DSEL

VINn

VDEN

/Is

☒
IS

VDSEL

VOUTn

GND

VIS

☒

IGND

1

Terms_PROFET.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="4" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 5" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->

Pin Configuration


# 3 Pin Configuration


## 3.1 Pin Assignment


<figure>
<figcaption>Figure 4 Pin Configuration</figcaption>

GND

1

14

OUT0

IN0

2

13

OUT0

DEN

3

12

OUT0

IS

4

VS

11

n.c.

DSEL

5

10

OUT1

IN1

6

9

OUT1

n.c.

7

exposed pad (bottom)

8

OUT1

PinOut_PROFET2ch.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="5" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 6" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->
<!-- PageHeader="Pin Configuration" -->


## 3.2 Pin Definitions and Functions


<table>
<tr>
<th>Table 2</th>
<th>Pin Definition</th>
<th></th>
</tr>
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
<td>2,6</td>
<td>INn</td>
<td>Input Channel n Digital signal to switch ON channel n ("high" active) If not used: connect with a 10 kQ2 resistor either to GND pin or to module ground</td>
</tr>
<tr>
<td>3</td>
<td>DEN</td>
<td>Diagnostic Enable Digital signal to enable device diagnosis ("high" active) and to clear the protection counter of channel selected with DSEL pin If not used: connect with a 10 kQ2 resistor either to GND pin or to module ground</td>
</tr>
<tr>
<td rowspan="2">4</td>
<td rowspan="2">IS</td>
<td>SENSE current output</td>
</tr>
<tr>
<td>Analog/digital signal for diagnosis If not used: left open</td>
</tr>
<tr>
<td>5</td>
<td>DSEL</td>
<td>Diagnosis Selection Digital signal to select one channel to perform ON and OFF state diagnosis ("high" active) If not used: connect with a 10 kQ2 resistor either to GND pin or to module ground</td>
</tr>
<tr>
<td>7,11</td>
<td>n.c.</td>
<td>Not connected, internally not bonded</td>
</tr>
<tr>
<td>8-10, 12- 14</td>
<td>OUTn</td>
<td>Output n Protected high-side power output channel n1)</td>
</tr>
</table>

1\) All output pins of the channel must be connected together on the PCB. All pins of the output are internally connected
together. PCB traces have to be designed to withstand the maximum current which can flow.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="6" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 7" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


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
<td>Load Dump Voltage</td>
<td>V BAT(LD)</td>
<td>–</td>
<td>–</td>
<td>35</td>
<td>V</td>
<td>suppressed Load Dump acc. to ISO16750-2 (2010). Ri = 222</td>
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
<td>t ≤ 2 min TA =+25 ℃ Setup as described in Chapter 10</td>
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
<td colspan="8">Logic &amp; control pins (Digital Input = DI) DI = INn, DEN, DSEL</td>
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
<td colspan="8">IS pin</td>
</tr>
<tr>
<td>Voltage at IS Pin</td>
<td>VIS</td>
<td>-1.5</td>
<td>–</td>
<td>Vs</td>
<td>V</td>
<td>lis = 10 µA</td>
<td>P_4.1.0.16</td>
</tr>
<tr>
<td>Current through IS Pin</td>
<td>Is</td>
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
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="7" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 8" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


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
<td>V ESD(HBM)_OU T</td>
<td>-4</td>
<td>–</td>
<td>4</td>
<td>kV</td>
<td>HBM3)</td>
<td>P_4.1.0.22</td>
</tr>
<tr>
<td>ESD Susceptibility all Pins (CDM)</td>
<td>V ESD(CDM)</td>
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

2\) Maximum VDI to be considered for Latch-Up tests: 5.5 V.

3\) ESD susceptibility, Human Body Model "HBM", according to AEC Q100-002.

4\) ESD susceptibility, Charged Device Model "CDM", according to AEC Q100-011.


####### Notes

1\. Stresses above the ones listed here may cause permanent damage to the device. Exposure to absolute
maximum rating conditions for extended periods may affect device reliability.

2\. Integrated protection functions are designed to prevent IC destruction under fault conditions described in the
data sheet. Fault conditions are considered as "outside" normal operating range. Protection functions are
not designed for continuous repetitive operation.


##### 4.2 Absolute Maximum Ratings - Power Stages


###### 4.2.1 Power Stage - 20 ml2

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
<td>42</td>
<td>mJ</td>
<td>IL=2*IL(NOM) TJ(0) = 150 ℃ Vs = 28 V</td>
<td>P_4.2.4.1</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="8" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 9" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


####### General Product Characteristics

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
<td>18</td>
<td>mJ</td>
<td>IL= IL(NOM) TJ(0) = 85 ℃ Vs = 13.5 V 1M cycles</td>
<td>P_4.2.4.2</td>
</tr>
<tr>
<td>Load Current</td>
<td>/LI</td>
<td>-</td>
<td>-</td>
<td>IL(OVL),M AX</td>
<td>A</td>
<td>–</td>
<td>P_4.2.4.3</td>
</tr>
</table>

1\) Not subject to production test, specified by design.


##### 4.3 Functional Range


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
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 10" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


#### General Product Characteristics


##### 4.4 Thermal Resistance

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
<td>1.8</td>
<td>3</td>
<td>K/W</td>
<td>2)</td>
<td>P_4.4.0.1</td>
</tr>
<tr>
<td>Thermal Resistance Junction-to-Case</td>
<td>RthJC</td>
<td>–</td>
<td>1.1</td>
<td>1.9</td>
<td>K/W</td>
<td>2) simulated at exposed pad</td>
<td>P_4.4.0.2</td>
</tr>
<tr>
<td>Thermal Resistance Junction-to-Ambient</td>
<td>RthJA</td>
<td>–</td>
<td>31.1</td>
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


###### 4.4.1 PCB Setup


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
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 11" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


####### General Product Characteristics


<figure>
<figcaption>Figure 7 PCB setup for thermal simulations</figcaption>

E

JEDEC 1s0p / 600mm2

JEDEC 1s0p / footprint
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


###### 4.4.2 Thermal Impedance

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="11" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 12" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


####### General Product Characteristics


<figure>
<figcaption>Figure 9 Typical Thermal Impedance. PCB setup according Chapter 4.4.1</figcaption>

BTS7020-2EPx

100

10

ZthJA (K/W)

TA = 105℃

1

2s2p

1sOp - 600 mm2

1s0p - 300 mm2

1s0p - footprint

0.1

0.0001

0.001

0.01

0.1

1

10

100

1000

Time (s)

</figure>


<figure>
<figcaption>Figure 10 Thermal Resistance on 1s0p PCB with various cooling surfaces</figcaption>

BTS7020-2EPx

130

1sOp - Ta = 105℃

120

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
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 13" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->

Logic Pins


##### 5 Logic Pins

The device has 4 digital pins for direct control.


###### 5.1 Input Pins (INn)

The input pins IN0, IN1 activate the corresponding output channel. The input circuitry is compatible with 3.3V
and 5V microcontroller (see Chapter 10 for the complete application setup overview). The electrical
equivalent of the input circuitry is shown in Figure 11. In case the pin is not used, it must be connected with a
10 kQ2 resistor either to GND pin or to module ground.


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
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 14" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->

Logic Pins


###### 5.2 Diagnosis Pin

The Diagnosis Enable (DEN) pin controls the diagnosis circuitry and the protection circuitry. When DEN pin is
set to "high", the diagnosis is enabled (see Chapter 9.2 for more details). When it is set to "low", the diagnosis
is disabled (IS pin is set to high impedance).

The Diagnosis Selection (DSEL) pin selects the channel where diagnosis is performed (see Chapter 9.1.1).

The transition from "high" to "low" of DEN pin clears the protection latch of the channel selected with DSEL
pin depending on the logic state of IN pin and DEN pulse length (see Chapter 8.3 for more details). The internal
structure of diagnosis pins is the same as the one of input pins. See Figure 11 for more details.


###### 5.3 Electrical Characteristics Logic Pins

Vs = 6 V to 18 V, T] = - 40 °C to +150 ℃
Typical values: Vs = 13.5 V, TJ= 25 ℃

Digital Input (DI) pins = IN, DEN, DSEL


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
<td>DI(TH)</td>
<td>0.8</td>
<td>1.3</td>
<td>2</td>
<td>V</td>
<td>See Figure 11 and Figure 12</td>
<td>P_5.4.0.1</td>
</tr>
<tr>
<td>Digital Input Clamping Voltage</td>
<td>VDI(CLAMP1)</td>
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
<td>DI(H)</td>
<td>2</td>
<td>10</td>
<td>25</td>
<td>HA</td>
<td>VDI = 2 V See Figure 11 and Figure 12</td>
<td>P_5.4.0.5</td>
</tr>
<tr>
<td>Digital Input Current ("low")</td>
<td>DI(L)</td>
<td>2</td>
<td>10</td>
<td>25</td>
<td>HA</td>
<td>VDI = 0.8 V See Figure 11 and Figure 12</td>
<td>P_5.4.0.6</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="14" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 15" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


Power Supply


##### 6 Power Supply

The BTS7020-2EPA is supplied by Vs, which is used for the internal logic as well as supply for the power output
stages. Vs has an undervoltage detection circuit, which prevents the activation of the power output stages and
diagnosis in case the applied voltage is below the undervoltage threshold.


###### 6.1 Operation Modes

BTS7020-2EPA has the following operation modes:

· Sleep mode

· Active mode

· Stand-by mode

The transition between operation modes is determined according to these variables:

· Logic level at INn pins

· Logic level at DEN pin

The state diagram including the possible transitions is shown in Figure 13. The behavior of BTS7020-2EPA as
well as some parameters may change in dependence from the operation mode of the device. Furthermore,
due to the undervoltage detection circuitry which monitors Vs supply voltage, some changes within the same
operation mode can be seen accordingly.

There are three parameters describing each operation mode of BTS7020-2EPA:

· Status of the output channels

· Status of the diagnosis

· Current consumption at VS pin (measured by lys in Sleep mode, IGND in all other operative modes)

Table 8 shows the correlation between operation modes, Vs supply voltage, and the state of the most
important functions (channel status, diagnosis).


<figure>
<figcaption>Figure 13 Operation Mode State Diagram</figcaption>

Unsupplied

Power-up

Vs > VS (OP)

IN = „high“

IN = „low“
& DEN = „low“

Sleep

IN = „low“
& DEN = „low“

IN = „low“ &
DEN = „high“

IN = „high“

Active

Stand-by

DEN = „high

IN = „low“
& DEN = „high“

DEN = „low“

PowerSupply_OpMode_PROFET.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="15" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 16" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->
<!-- PageHeader="Power Supply" -->


<table>
<caption>Table 8 Device function in relation to operation modes and Vs voltage</caption>
<tr>
<th>Operative Mode</th>
<th>Function</th>
<th>Vs in undervoltage</th>
<th>Vs not in undervoltage</th>
</tr>
<tr>
<td rowspan="2">Sleep</td>
<td>Channels</td>
<td>OFF</td>
<td>OFF</td>
</tr>
<tr>
<td>Diagnosis</td>
<td>OFF</td>
<td>OFF</td>
</tr>
<tr>
<td rowspan="2">Active</td>
<td>Channels</td>
<td>OFF</td>
<td>available</td>
</tr>
<tr>
<td>Diagnosis</td>
<td>OFF</td>
<td>available in OFF and ON states</td>
</tr>
<tr>
<td rowspan="2">Stand-by</td>
<td>Channels</td>
<td>OFF</td>
<td>OFF</td>
</tr>
<tr>
<td>Diagnosis</td>
<td>OFF</td>
<td>available in OFF state</td>
</tr>
</table>


####### 6.1.1 Unsupplied

In this state, the device is either unsupplied (no voltage applied to VS pin) or the supply voltage is below the
undervoltage threshold.


####### 6.1.2 Power-up

The Power-up condition is entered when the supply voltage (Vs) is applied to the device. The supply is rising
until it is above the undervoltage threshold Vs(op) therefore the internal Power-On signals are set.


####### 6.1.3 Sleep mode

The device is in Sleep mode when all Digital Input pins (INn, DEN, DSEL) are set to "low". When BTS7020-2EPA
is in Sleep mode, all outputs are OFF. The current consumption is minimum (see parameter /VS(SLEEP)). No
Overtemperature or Overload protection mechanism is active when the device is in Sleep mode. The device
can go in Sleep mode only if the protection is not active (counter = 0, see Chapter 8.3.1 for further details).


####### 6.1.4 Stand-by mode

The device is in Stand-by mode as long as DEN pin is set to "high" while input pins are set to "low". All channels
are OFF therefore only Open Load in OFF diagnosis is possible. Depending on the load condition, either a fault
current /IS(FAULT) or an Open Load in OFF current /IS(OLOFF) may be present at IS pin. In such situation, the current
consumption of the device is increased.


####### 6.1.5 Active mode

Active mode is the normal operation mode of BTS7020-2EPA. The device enters Active mode as soon as one IN
pin is set to "high". Device current consumption is specified with /GND(ACTIVE) (measured at GND pin because the
current at VS pin includes the load current). Overload, Overtemperature and Overvoltage protections are
active. Diagnosis is available.


###### 6.2 Undervoltage on Vs

Between Vs(OP) and Vs(uv) the undervoltage mechanism is triggered. If the device is operative (in Active mode)
and the supply voltage drops below the undervoltage threshold Vs(uv), the internal logic switches OFF the
output channels.

As soon as the supply voltage Vs is above the operative threshold Vs(op), the channels having the corresponding
input pin set to "high" are switched ON again. The restart is delayed with a time tDELAY(Uv) which protects the
device in case the undervoltage condition is caused by a short circuit event (according to AEC-Q100-012), as
shown in Figure 14.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="16" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 17" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


####### Power Supply

If the device is in Sleep mode and one input is set to "high", the corresponding channel is switched ON if
Vs> Vs(OP) without waiting for DELAY(UV)-


<figure>
<figcaption>Figure 14 Vs undervoltage behavior</figcaption>

Vs

VS(OP)

VS(UV)

VS(HYS)

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
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 18" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->

Power Supply


###### 6.3 Electrical Characteristics Power Supply

Vs = 6 V to 18 V, TJ =- 40 °C to +150 ℃
Typical values: Vs = 13.5 V, T =25 ℃

Typical resistive loads connected to the outputs for testing (unless otherwise specified):

RL = 3.3 22


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
<td>Vs decreasing IN = "high" From Vps ≤ 0.5 V to VDS = VS See Figure 14</td>
<td>P_6.4.0.1</td>
</tr>
<tr>
<td>Power Supply Minimum Operating Voltage</td>
<td>VS(OP)</td>
<td>2.0</td>
<td>3.0</td>
<td>4.1</td>
<td>V</td>
<td>Vs increasing IN = "high" From VDs = Vs to VDS ≤ 0.5V See Figure 14</td>
<td>P_6.4.0.3</td>
</tr>
<tr>
<td>Power Supply Undervoltage Shutdown Hysteresis</td>
<td>VS(HYS)</td>
<td>–</td>
<td>0.7</td>
<td>–</td>
<td>V</td>
<td>1) VS(OP) - VS(UV) See Figure 14</td>
<td>P_6.4.0.6</td>
</tr>
<tr>
<td>Power Supply Undervoltage Recovery Time</td>
<td>ťDELAY(UV)</td>
<td>2.5</td>
<td>5</td>
<td>7.5</td>
<td>ms</td>
<td>dVs/dt ≤0.5V/us Vs2 -1 V See Figure 14</td>
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


###### 6.4 Electrical Characteristics Power Supply - Product Specific

Vs = 6 V to 18 V, T] =- 40 °C to +150 ℃

Typical values: Vs = 13.5 V, TJ= 25 ℃

Typical resistive loads connected to the outputs for testing (unless otherwise specified):

RL=3.3Ω


####### 6.4.1 BTS7020-2EPA

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="18" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 19" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->

Power Supply


<table>
<caption>Table 10 Electrical Characteristics: Power Supply BTS7020-2EPA</caption>
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
<td>Power Supply Current Consumption in Sleep Mode with Loads at TJ ≤ 85 ℃</td>
<td>VS(SLEEP)_85</td>
<td>–</td>
<td>0.03</td>
<td>0.6</td>
<td>µA</td>
<td>1) Vs = 18 V VOUT = 0 V IN = DEN = "low" TJ ≤ 85℃</td>
<td>P_6.5.4.1</td>
</tr>
<tr>
<td>Power Supply Current Consumption in Sleep Mode with Loads at TJ = 150 ℃</td>
<td>VS(SLEEP)_150</td>
<td>-</td>
<td>4</td>
<td>16</td>
<td>µA</td>
<td>Vs = 18 V VOUT = 0 V IN = DEN = "low" TJ=150 ℃</td>
<td>P_6.5.4.2</td>
</tr>
<tr>
<td>Operating Current in Active Mode (all Channels ON)</td>
<td>IGND(ACTIVE)</td>
<td>–</td>
<td>3</td>
<td>4</td>
<td>mA</td>
<td>Vs = 18 V IN = DEN = "high"</td>
<td>P_6.5.4.3</td>
</tr>
<tr>
<td>Operating Current in Stand- by Mode</td>
<td>İGND(STBY)</td>
<td>–</td>
<td>1.2</td>
<td>1.8</td>
<td>mA</td>
<td>Vs = 18 V IN = "low" DEN = "high"</td>
<td>P_6.5.4.5</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="19" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 20" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


#### Power Stages


##### 7 Power Stages

The high-side power stages are built using a N-channel vertical Power MOSFET with charge pump.


###### 7.1 Output ON-State Resistance

The ON-state resistance RDS(ON) depends mainly on junction temperature TJ. Figure 15 shows the variation of
RDS(ON) across the whole Ty range. The value "2" on the y-axis corresponds to the maximum RDS(ON) measured
at TJ = 150 ℃.


<figure>
<figcaption>Figure 15 RDS(ON) variation factor</figcaption>

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


###### 7.2 Switching loads


####### 7.2.1 Switching Resistive Loads

When switching resistive loads, the switching times and slew rates shown in Figure 16 can be considered. The
switch energy values EON and EOFF are proportional to load resistance and times ton and tOFF.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="20" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 21" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


######## Power Stages


<figure>
<figcaption>Figure 16 Switching a Resistive Load</figcaption>

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


####### 7.2.2 Switching Inductive Loads

When switching OFF inductive loads with high-side switches, the voltage VOUT drops below ground potential,
because the inductance intends to continue driving the current. To prevent the destruction of the device due
to overvoltage, a voltage clamp mechanism is implemented. The clamping structure limits the negative
output voltage so that VDs = VDS(CLAMP). Figure 17 shows a concept drawing of the implementation. The
clamping structure protects the device in all operation modes listed in Chapter 6.1.


<figure>
<figcaption>Figure 17 Output Clamp concept</figcaption>

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
<!-- PageNumber="21" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 22" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


######## Power Stages

During demagnetization of inductive loads, energy has to be dissipated in BTS7020-2EPA. The energy can be
calculated with Equation (7.1):

E = V
DS(CLAMP)
⋅

[
Vs - VDS(CLAMP)
RL
æ
è

⋅
ln
1
–

RL . IL
VS - VDS(CLAMP)
\+ 4 ]
(7.1)

The maximum energy, therefore the maximum inductance for a given current, is limited by the thermal design
of the component.


####### 7.2.3 Output Voltage Limitation

To increase the current sense accuracy, Vps voltage is monitored. When the output current /_ decreases while
the channel is diagnosed (DEN pin set to "high", channel selected with DSEL pins - see Figure 18) bringing Vos
equal or lower than VDS(SLC), the output DMOS gate is partially discharged. This increases the output resistance
so that VDs = VDS(SLC) even for very small output currents. The Vps increase allows the current sensing circuitry
to work more efficiently, providing better kILIs accuracy for output current in the low range.


<figure>
<figcaption>Figure 18 Output Voltage Limitation activation during diagnosis</figcaption>

IN

t

DEN

IL

tsIS(ON)

tsIS(OFF)

t

VDS

t

Vs

VDS(SLC)

t

PowerStage_GBR_diag.emf

</figure>


###### 7.3 Advanced Switching Characteristics


####### 7.3.1 Inverse Current behavior

When VOUT > Vs, a current /INy flows into the power output transistor (see Figure 19). This condition is known
as "Inverse Current".

If the channel is in OFF state, the current flows through the intrinsic body diode generating high power losses
therefore an increase of overall device temperature. This may lead to a switch OFF of unaffected channels due
to Overtemperature. If the channel is in ON state, RDS(INV) can be expected and power dissipation in the output
stage is comparable to normal operation in RDS(ON)-

During Inverse Current condition, the channel remains in ON or OFF state as long as /INV < /L(INV). If one channel
has inverse current applied, the neighbor channel is not influenced, meaning that switching ON and OFF
timings, protection (Overcurrent, Overtemperature) and current sensing (kILIs) are still within specified limits.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="22" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 23" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


######## Power Stages

With InverseON, it is possible to switch ON the channel during Inverse Current condition as long as /INV <IL(INV)
(see Figure 20).


<figure>
<figcaption>Figure 19 Inverse Current Circuitry</figcaption>

VBAT

Vs

Gate
Driver

Device
Logic

INV
Comp.

/INV

VINV = VOUT > VS

OUT

GND

RGND

PowerStage_InvCurr_INTDIO.emf

</figure>


<figure>
<figcaption>Figure 20 InverseON - Channel behavior in case of applied Inverse Current</figcaption>

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


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="23" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 24" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


#### Power Stages

Note:
No protection mechanism like Overtemperature or Overload protection is active during applied
Inverse Currents.


## 7.3.2 Switching Channels in Parallel

In case of appearance of a short circuit with connected in parallel to drive a single load, it may happen that the
two channels switch OFF asynchronously, therefore bringing an additional thermal stress to the channel that
switches OFF last. For this reason it is not recommended to use the device with channels in parallel.


## 7.3.3 Cross Current robustness with H-Bridge configuration

When BTS7020-2EPA is used as high-side switch e.g. in a bridge configuration (therefore paired with a low-side
switch as shown in Figure 21), the maximum slew rate applied to the output by the low-side switch must be
lower than | dVOUT / dt |.


<figure>
<figcaption>Figure 21 High-Side switch used in Bridge configuration</figcaption>

VBAT

R/L cable

VS

T

T

ON (DC)

IN0

IN1- OFF

OUT0

OUT1

| dVOUT / dt |

Current through Motor

Cross
Current

M

ON (PWM)

OFF

m

PowerStage_PassiveSlew_PROFET.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="24" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 25" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->

Power Stages


### 7.4 Electrical Characteristics Power Stages

Vs = 6 V to 18 V, TJ =- 40 ℃ to +150 ℃
Typical values: Vs = 13.5 V, T ] = 25 ℃

Typical resistive loads connected to the outputs for testing (unless otherwise specified):

RL = 3.3 22


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
<td>Drain to Source Clamping Voltage at TJ = - 40 °℃</td>
<td>VDS(CLAMP) _- 40</td>
<td>33</td>
<td>36.5</td>
<td>42</td>
<td>V</td>
<td>/L = 5 mA TJ =- 40ºC See Figure 17</td>
<td>P_7.4.0.1</td>
</tr>
<tr>
<td>Drain to Source Clamping Voltage at TJ ≥ 25 °℃</td>
<td>VDS(CLAMP)_25</td>
<td>35</td>
<td>38</td>
<td>44</td>
<td>V</td>
<td>1) /L = 5 mA TJ ≥ 25°C See Figure 17</td>
<td>P_7.4.0.2</td>
</tr>
</table>

1\) Tested at TJ = 150℃.


#### 7.4.1 Electrical Characteristics Power Stages - PROFET™


<table>
<caption>Table 12 Electrical Characteristics: Power Stages - PROFET™</caption>
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
<td colspan="2"></td>
<td></td>
<td></td>
<td></td>
</tr>
<tr>
<td>Switch-ON Delay</td>
<td>tON(DELAY)</td>
<td>10</td>
<td>35</td>
<td>60</td>
<td>μς</td>
<td>Vs = 13.5 V VOUT = 10% VS See Figure 16</td>
<td>P_7.4.1.1</td>
</tr>
<tr>
<td>Switch-OFF Delay</td>
<td>tOFF(DELAY)</td>
<td>10</td>
<td>25</td>
<td>50</td>
<td>μς</td>
<td>Vs = 13.5 V VOUT = 90% VS See Figure 16</td>
<td>P_7.4.1.2</td>
</tr>
<tr>
<td>Switch-ON Time</td>
<td>ton</td>
<td>30</td>
<td>60</td>
<td>110</td>
<td>μς</td>
<td>Vs = 13.5 V VOUT = 90% VS See Figure 16</td>
<td>P_7.4.1.3</td>
</tr>
<tr>
<td>Switch-OFF Time</td>
<td>tOFF</td>
<td>15</td>
<td>50</td>
<td>100</td>
<td>μς</td>
<td>Vs = 13.5 V VOUT = 10% VS See Figure 16</td>
<td>P_7.4.1.4</td>
</tr>
<tr>
<td>Switch-ON/OFF Matching ton - tOFF</td>
<td>Atsw</td>
<td>-20</td>
<td>20</td>
<td>60</td>
<td>μς</td>
<td>Vs = 13.5 V</td>
<td>P_7.4.1.5</td>
</tr>
<tr>
<td>Voltage Slope</td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
<td></td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="25" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 26" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


##### Power Stages


<table>
<caption>Table 12 Electrical Characteristics: Power Stages - PROFET™ (continued)</caption>
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
<td>Switch-ON Slew Rate</td>
<td>(dV/dt)ON</td>
<td>0.3</td>
<td>0.6</td>
<td>0.9</td>
<td>V/us</td>
<td>Vs = 13.5 V VOUT = 30% to 70% of Vs See Figure 16</td>
<td>P_7.4.1.6</td>
</tr>
<tr>
<td>Switch-OFF Slew Rate</td>
<td>-(dV/dt) OFF</td>
<td>0.3</td>
<td>0.6</td>
<td>0.9</td>
<td>V/μς</td>
<td>Vs = 13.5 V VOUT = 70% to 30% of Vs See Figure 16</td>
<td>P_7.4.1.7</td>
</tr>
<tr>
<td>Slew Rate Matching (dV/dt)ON - (dV/dt)OFF</td>
<td>A(dV/dt)sw</td>
<td>-0.15</td>
<td>0</td>
<td>0.15</td>
<td>V/μς</td>
<td>Vs = 13.5 V</td>
<td>P_7.4.1.8</td>
</tr>
<tr>
<td colspan="8">Voltages</td>
</tr>
<tr>
<td>Output Voltage Drop Limitation at Small Load Currents</td>
<td>VDS(SLC)</td>
<td>2</td>
<td>7</td>
<td>18</td>
<td>mV</td>
<td>1) DEN = "high" channel selected with DSEL pin 1L =/L(OL) = 20 mA See Figure 18</td>
<td>P_7.4.1.9</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


###### 7.5 Electrical Characteristics - Power Output Stages

Vs = 6 V to 18 V, T] =- 40 °C to +150 ℃

Typical values: Vs = 13.5 V, TJ=25 ℃

Typical resistive loads connected to the outputs for testing (unless otherwise specified):

RL= 3.3 2


####### 7.5.1 Power Output Stage - 20 m22


<table>
<caption>Table 13 Electrical Characteristics: Power Stages - 20 ml2</caption>
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
<td>12.7</td>
<td>–</td>
<td>mQ</td>
<td>1) TJ =25 ℃</td>
<td>P_7.5.4.1</td>
</tr>
<tr>
<td>ON-State Resistance at TJ = 150 ℃</td>
<td>RDS(ON)_150</td>
<td>–</td>
<td>–</td>
<td>23.7</td>
<td>mQ2</td>
<td>TJ =150 ℃ /L=4A</td>
<td>P_7.5.4.2</td>
</tr>
<tr>
<td>ON-State Resistance in Cranking</td>
<td>RDS(ON)_CRAN K</td>
<td>–</td>
<td>–</td>
<td>28.6</td>
<td>m22</td>
<td>TJ =150 ℃ Vs = 3.1 V / =1.5 A</td>
<td>P_7.5.4.3</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="26" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 27" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


##### Power Stages


<table>
<caption>Table 13 Electrical Characteristics: Power Stages - 20 ml2 (continued)</caption>
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
<td>ON-State Resistance in Inverse Current at Ty = 25 ℃</td>
<td>RDS(INV)_25</td>
<td>–</td>
<td>13.8</td>
<td>–</td>
<td>ΜΩ</td>
<td>1) TJ =25 ℃ Vs = 13.5 V /L =- 4A DEN = "low" see Figure 19</td>
<td>P_7.5.4.4</td>
</tr>
<tr>
<td>ON-State Resistance in Inverse Current at Ty = 150 ℃</td>
<td>RDS(INV)_150</td>
<td>–</td>
<td>–</td>
<td>28.6</td>
<td>m22</td>
<td>TJ=150 ℃ Vs = 13.5 V 1 =- 4A DEN = "low" see Figure 19</td>
<td>P_7.5.4.5</td>
</tr>
<tr>
<td>ON-State Resistance in Reverse Polarity at TJ = 25 ℃</td>
<td>RDS(REV)_25</td>
<td>–</td>
<td>13.8</td>
<td>–</td>
<td>m22</td>
<td>1) TJ = 25 ℃ Vs =- 13.5 V / =- 4A RSENSE = 1.2 k£2</td>
<td>P_7.5.4.6</td>
</tr>
<tr>
<td>ON-State Resistance in Reverse Polarity at TJ =150 ℃</td>
<td>RDS(REV)_150</td>
<td>–</td>
<td>–</td>
<td>49</td>
<td>mQ2</td>
<td>TJ=150 ℃ Vs =- 13.5 V / =- 4A RSENSE = 1.2 k£2</td>
<td>P_7.5.4.7</td>
</tr>
<tr>
<td>Nominal Load Current per Channel (all Channels Active)</td>
<td>IL(NOM)</td>
<td>-</td>
<td>5</td>
<td>-</td>
<td>A</td>
<td>1) TA = 85 ℃ TJ ≤ 150 ℃</td>
<td>P_7.5.4.8</td>
</tr>
<tr>
<td>Output Leakage Current at TJ ≤ 85℃</td>
<td>IL(OFF)_85</td>
<td>–</td>
<td>0.01</td>
<td>0.5</td>
<td>µA</td>
<td>1) VOUT = 0 V VIN = "low" TA ≤ 85℃</td>
<td>P_7.5.4.9</td>
</tr>
<tr>
<td>Output Leakage Current at TJ=150 ℃</td>
<td>IL(OFF)_150</td>
<td>–</td>
<td>2.2</td>
<td>6</td>
<td>µA</td>
<td>VOUT = 0 V VIN = "low" TA = 150 ℃</td>
<td>P_7.5.4.10</td>
</tr>
<tr>
<td>Inverse Current Capability</td>
<td>İL(INV)</td>
<td>-</td>
<td>5</td>
<td>-</td>
<td>A</td>
<td>1) VS &lt; VOUT IN = “high" see Figure 19</td>
<td>P_7.5.4.11</td>
</tr>
<tr>
<td>Voltage Slope</td>
<td></td>
<td colspan="6"></td>
</tr>
<tr>
<td>Passive Slew Rate (e.g. for Half Bridge Configuration)</td>
<td>IdVOUT / dt]</td>
<td>-</td>
<td>–</td>
<td>10</td>
<td>V/us</td>
<td>1) Vs = 13.5 V see Figure 21</td>
<td>P_7.5.4.12</td>
</tr>
<tr>
<td>Voltages</td>
<td></td>
<td colspan="6"></td>
</tr>
<tr>
<td>Drain Source Diode Voltage</td>
<td>|VDS(DIODE)|</td>
<td>–</td>
<td>650</td>
<td>700</td>
<td>mV</td>
<td>/ =- 190 mA TJ=150 ℃</td>
<td>P_7.5.4.13</td>
</tr>
<tr>
<td colspan="8">Switching Energy</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="27" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 28" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->

Power Stages


<table>
<caption>Table 13 Electrical Characteristics: Power Stages - 20 ml2 (continued)</caption>
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
<td>Switch-ON Energy</td>
<td>EON</td>
<td>–</td>
<td>0.4</td>
<td>–</td>
<td>mJ</td>
<td>1) Vs = 18 V see Figure 16</td>
<td>P_7.5.4.14</td>
</tr>
<tr>
<td>Switch-OFF Energy</td>
<td>EOFF</td>
<td>–</td>
<td>0.55</td>
<td>–</td>
<td>mJ</td>
<td>1) Vs = 18 V see Figure 16</td>
<td>P_7.5.4.15</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="28" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 29" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


<!-- PageHeader="Protection" -->


# 8 Protection

The BTS7020-2EPA is protected against Overtemperature, Overload, Reverse Battery (with ReverseON) and
Overvoltage. Overtemperature and Overload protections are working when the device is not in Sleep mode.
Overvoltage protection works in all operation modes. Reverse Battery protection works when the GND and VS
pins are reverse supplied.


## 8.1 Overtemperature Protection

The device incorporates both an absolute (TJ(ABS) and a dynamic (TJ(DYN)) temperature protection circuitry for
each channel. An increase of junction temperature T, above either one of the two thresholds (TJ(ABS) or TJ(DYN)
switches OFF the overheated channel to prevent destruction. The channel remains switched OFF until
junction temperature has reached the "Restart" condition described in Table 14. The behavior is shown in
Figure 22 (absolute Overtemperature Protection) and Figure 23 (dynamic Overtemperature Protection).
TJ(REF) is the reference temperature used for dynamic temperature protection.


<figure>
<figcaption>Figure 22 Overtemperature Protection (Absolute)</figcaption>

IN

t

DEN

t

IL

/L(OVL)

t

TJ

TJ(ABS)

THYS(ABS)

tIs(FAULT)_D

t

lis

İIS(SAT)

/IS(FAUL T)

L/KILIS

t

Internal
counter

0

1

t

Protection_PROFET_OT_IRC.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="29" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 30" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


### Protection


<figure>
<figcaption>Figure 23 Overtemperature Protection (Dynamic)</figcaption>

IN

t

DEN

t

IL
/L(OVL)

t

TJ

TJ(ABS)

TJ(DYN)

TJ(REF)

lis

tIs(FAULT)_D

t

/IS(FAUL T)

IL | KILIS

t

In ter nal
counter

0

1

2

t

Protection_PROFET_dT_IRC.emf

</figure>


When the Overtemperature protection circuitry allows the channel to be switched ON again, the retry strategy
described in Chapter 8.3 is followed.


## 8.2 Overload Protection

The BTS7020-2EPA is protected in case of Overload or short circuit to ground. Two Overload thresholds are
defined (see Figure 24) and selected automatically depending on the voltage Vps across the power DMOS:

· IL(OVLO) when VDs < 13 V

· IL(OVL1) when VDs > 22 V

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="30" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 31" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


### Protection


<figure>
<figcaption>Figure 24 Overload Current Thresholds variation with VDs</figcaption>

Overload threshold variation ("1" = IL(ovL) typ @ VDs = 5 V)

1.1

IL(OVL0)

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
temperature and decreases when T, increases (see Figure 25). IL(OVLO) typical value remains constant up to a
junction temperature of +75 ℃.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="31" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 32" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


#### Protection


<figure>
<figcaption>Figure 25 Overload Current Thresholds variation with T,</figcaption>

IL(OVLO) variation over T,

1.3

1.2

1.1

1.0

IL(OVL0) variation factor

0.9

0.8

0.7

reference value

"1"= IL(OVLo) typ @-40 ℃

0.6

0.5

0.4

0.3

0.2

0.1

Typ

0.0

-40

-20

0

20

40

60

80

100

120

140

160

Junction Temperature (℃)

</figure>


Power supply voltage Vs can increase above 18 V for short time, for instance in Load Dump or in Jump Start
condition. Whenever Vs ≥ Vsus), the overload detection current is set to /L(OVL_Js) as shown in Figure 26.


<figure>
<figcaption>Figure 26 Overload Detection Current variation with Vs voltage</figcaption>

/L(VL)

/L(OVL_JS)

VS(JS)

Vs

Protection_JS.emf

</figure>


When IL ≥ IL(OVL) (either IL(OVLO) or /L(OVL1)), the channel is switched OFF. The channel is allowed to restart
according to the retry strategy described in Chapter 8.3.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="32" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 33" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->
<!-- PageHeader="Protection" -->


## 8.3 Protection and Diagnosis in case of Fault

Any event that triggers a protection mechanism (either Overtemperature or Overload) has 2 consequences:

· The affected channel switches OFF and the internal counter is incremented

· If the diagnosis is active for the affected channel, a current /IS(FAULT) is provided by IS pin (see Chapter 9.2.2
for further details)

The channel can be switched ON again if all the protection mechanisms fulfill the "restart" conditions
described in Table 14. Furthermore, the device has an internal retry counter (one for each channel) to
maximize the robustness in case of fault.


<table>
<caption>Table 14 Protection "Restart" Condition</caption>
<tr>
<th>Fault condition</th>
<th>Switch OFF event</th>
<th>"Restart" Condition</th>
</tr>
<tr>
<td>Overtemperature</td>
<td>TJ ≥ TJ(ABS) or (TJ - TJ(REF) ≥ TJ(DYN)</td>
<td>TJ &lt;TJ(ABS) and (T) -TJ(REF) &lt;TJ(DYN) (including hysteresis)</td>
</tr>
<tr>
<td>Overload</td>
<td>IL≥ /L(OVL)</td>
<td>/_ &lt; 50 mA Ty within TJ(ABS) and TJ(DYN) ranges (including hysteresis)</td>
</tr>
</table>


### 8.3.1 Retry Strategy

When IN is set to "high", the channel is switched ON. In case of fault condition the output stage is switched
OFF. The channel can be allowed to restart only if the "restart" conditions for the protection mechanisms are
fulfilled (see Table 14).

The channel is allowed to switch ON for n RETRY(CR) times before switching OFF. After a time tRETRY, if the input pin
is set to "high", the channel switches ON again for nRETRY(NT) times before switching OFF again ("retry" cycle).
After nRETRY(CYC) consecutive "retry" cycles, the channel latches OFF. It is necessary to set the input pin to "low"
for a time longer than tDELAY(CR) to de-latch the channel ("counter reset delay" time) and to reset the internal
counter to the default value.

During the "counter reset delay" time, if the input is set to "high" the channel remains switched OFF and the
timer counting tDELAY(CR) is reset, starting to count again as soon as the input pin is set to "low" again. If the
input pin remains "low" for a time longer than tDELAY(CR) the internal retry counter is reset to the default value,
allowing nRETRY(CR) retries at the next channel activation.

The retry strategy is shown in Figure 29 (flowchart), Figure 27 (timing diagram - input pin always "high") and
Figure 28 (timing diagram - channel controlled in PWM).

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="33" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 34" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


<!-- PageHeader="Protection" -->


<figure>
<figcaption>Figure 27 Retry Strategy Timing Diagram</figcaption>

IN

Short circuit
to ground

t

nRETRY(CYC)

t

"retry" cycle

nRETRY(CR)

nRETRY(NT)

nRETRY(NT)

IL

TRETRY

Y

tRETRY

K

tDELAY(CR)

t

×

\>

Internal
counter

0

1

nRETRY(CR)

nRETRY(CR) + nRETRY(NT)

nRETRY(CR) + (nRETRY(CYC) * nRETRY(NT))

0

t

DEN

/IS(FAUL T)

t

/Is

IL/ KILIS

IL / KILIS

t

Protection_PROFET_time_noPWM.emf

</figure>


<figure>
<figcaption>Figure 28 Retry Strategy Timing Diagram - Channel operated in PWM</figcaption>

IN

Short circuit
to ground

t

nRETRY(CYC)

t

"retry" cycle

nRETRY(CR)

nRETRY(NT)

nRETRY(NT)

IL

TRETRY

ÈRETRY

tDELAY(CR)

t

\>

<

\>

×

Internal
counter

0

1

nRETRY(CR)

nRETRY(CR) + nRETRY(NT)

nRETRY(CR) + (nRETRY(CYC) * nRETRY(NT))

0

t

Protection_PROFET_Timings.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="34" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 35" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


#### Protection


<figure>
<figcaption>Figure 29 Retry Strategy Flowchart</figcaption>

START

Channel remains OFF

IN is "high"

no

yes

"Retry" cycles =
nRETRY[CYC)

yes

no

ALL "Restart"
conditions fulfilled

no

Switch channel OFF

yes

no

Switch channel ON

IN is "high"

yes-

Channel remains ON

Fault
(Overtemperature or
Overload)

no

yes

Switch channel OFF

Counter++

"Retry" cycles++

Counter < nRETRY[CR)

yes

Wait for tRETRY

no

"Retry" cycles =
nRETRY[CYC)

no

yes

Wait until IN is "low" then
start counting for t DELAY(CR)

IN is "low"

no

yes

Continue counting for
tDELAY/CRI

tDELAY(CR) elapsed

no

yes

Counter = 0
"Retry" cycles = 0

Protection_PROFET_Flow.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="35" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 36" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


##### Protection

It is possible to "force" a reset of the internal counter without waiting for tDELAY(CR) by applying a pulse (rising
edge followed by a falling edge) to the DEN pin while IN pin is "low". The pulse applied to DEN pin must have
a duration longer than tDEN(CR) to ensure a reset of the internal counter. The DSEL pin must select the channel
that has to be de-latched and keep the same logic value while DEN pin toggles twice (rising edge followed by
a falling edge).

The timings are shown in Figure 30.


<figure>
<figcaption>Figure 30 Retry Strategy Timing Diagram with Forced Reset</figcaption>

IN

t

Short circuit
to ground

t

nRETRY(CR)

nRETRY(CR)

IL

MA

t

In ter nal
counter

0

1

nRETRY(CR)

0

1

nRETRY(CR)

0

t

DEN

tDEN(CR)

tDEN(CR)

tDEN(CR)

t

Protection_PROFET_DENforce_time2.emf

</figure>


## 8.4 Additional protections


### 8.4.1 Reverse Polarity Protection

In Reverse Polarity condition (also known as Reverse Battery), the output stages are switched ON (see
parameter RDS(REV) because of ReverseON feature which limits the power dissipation in the output stages.
Each ESD diode of the logic contributes to total power dissipation. The reverse current through the output
stages must be limited by the connected loads. The current through digital input pins has to be limited as well
by an external resistor (please refer to the Absolute Maximum Ratings listed in Chapter 4.1 and to Application
Information in Chapter 10).

Figure 31 shows a typical application including a device with ReverseON. A current flowing into GND pin (-/GND)
during Reverse Polarity condition is necessary to activate ReverseON, therefore a resistive path between
module ground and device GND pin must be present.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="36" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 37" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


#### Protection


<figure>
<figcaption>Figure 31 Reverse Battery Protection (application example)</figcaption>

BAT(REV)

High-side
Channel

VS

Microcontroller

IDI

DO

RDI

DI

ReverseON

OUTn

-IL

GND

IS

GND

L, C, R

-/Is

RSENSE

RGND

-IGND

Protection_RevBatt.emf

</figure>


### 8.4.2 Overvoltage Protection

In the case of supply voltages between VS(EXT,UP) and VBAT(LD), the output transistors are still operational and
follow the input pin. In addition to the output clamp for inductive loads as described in Chapter 7.2.2, there
is a clamp mechanism available for Overvoltage protection for the logic and the output channels, monitoring
the voltage between VS and GND pins (VS(CLAMP)).


## 8.5 Protection against loss of connection


### 8.5.1 Loss of Battery and Loss of Load

The loss of connection to battery or to the load has no influence on device robustness when load and wire
harness are purely resistive. In case of driving an inductive load, the energy stored in the inductance must be
handled. PROFET™+2 12V devices can handle the inductivity of the wire harness up to 10 UH with /L(NOM). In case
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
<!-- PageNumber="37" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 38" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->

Protection


## 8.6 Electrical Characteristics Protection

Vs = 6 V to 18 V, TJ =- 40 °C to +150 ℃

Typical values: Vs = 13.5 V, T ]= 25 ℃

Typical resistive loads connected to the outputs for testing (unless otherwise specified):

RL = 3.3 22


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
<td>℃</td>
<td>1)2) See Figure 22</td>
<td>P_8.6.0.1</td>
</tr>
<tr>
<td>Thermal Shutdown Hysteresis (Absolute)</td>
<td>HYS(ABS)</td>
<td>–</td>
<td>30</td>
<td>–</td>
<td>K</td>
<td>3) See Figure 22</td>
<td>P_8.6.0.2</td>
</tr>
<tr>
<td>Thermal Shutdown Temperature (Dynamic)</td>
<td>TJ(DYN)</td>
<td>–</td>
<td>80</td>
<td>–</td>
<td>K</td>
<td>3) See Figure 23</td>
<td>P_8.6.0.3</td>
</tr>
<tr>
<td>Power Supply Clamping Voltage at TJ = - 40 ℃</td>
<td>VS(CLAMP) _- 40</td>
<td>33</td>
<td>36.5</td>
<td>42</td>
<td>V</td>
<td>Ivs = 5 mA TJ =- 40 °℃ See Figure 17</td>
<td>P_8.6.0.6</td>
</tr>
<tr>
<td>Power Supply Clamping Voltage at TJ ≥ 25 ℃</td>
<td>VS(CLAMP)_25</td>
<td>35</td>
<td>38</td>
<td>44</td>
<td>V</td>
<td>2) Ivs = 5 mA TJ ≥ 25°℃ See Figure 17</td>
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


### 8.6.1 Electrical Characteristics Protection - PROFET™


<table>
<caption>Table 16 Electrical Characteristics: Protection - PROFET™</caption>
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
<td>Automatic Retries in Case of Fault after a Counter Reset</td>
<td>nRETRY(CR)</td>
<td>-</td>
<td>5</td>
<td>-</td>
<td></td>
<td>1) See Figure 27 and Figure 28</td>
<td>P_8.6.1.1</td>
</tr>
<tr>
<td>Automatic Retries in Case of Fault after the First tRETRY Activation</td>
<td>nRETRY(NT)</td>
<td>-</td>
<td>1</td>
<td>-</td>
<td></td>
<td>1) See Figure 27 and Figure 28</td>
<td>P_8.6.1.3</td>
</tr>
<tr>
<td>Maximum "Retry" Cycles allowed before Channel Latch OFF</td>
<td>nRETRY(CYC)</td>
<td>-</td>
<td>2</td>
<td>-</td>
<td></td>
<td>1) See Figure 27 and Figure 28</td>
<td>P_8.6.1.4</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="38" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 39" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


#### Protection


<table>
<caption>Table 16 Electrical Characteristics: Protection - PROFET™ (continued)</caption>
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
<td>Auto Retry Time after Fault Condition</td>
<td>tRETRY</td>
<td>40</td>
<td>70</td>
<td>100</td>
<td>ms</td>
<td>1) See Figure 27 and Figure 28</td>
<td>P_8.6.1.5</td>
</tr>
<tr>
<td>Counter Reset Delay Time after Fault Condition</td>
<td>ťDELAY(CR)</td>
<td>40</td>
<td>70</td>
<td>100</td>
<td>ms</td>
<td>1) See Figure 27 and Figure 28</td>
<td>P_8.6.1.6</td>
</tr>
<tr>
<td>Minimum DEN Pulse Duration for Counter Reset</td>
<td>İDEN(CR)</td>
<td>50</td>
<td>100</td>
<td>150</td>
<td>μς</td>
<td>2) See Figure 30</td>
<td>P_8.6.1.7</td>
</tr>
</table>

1\) Functional test only.

2\) Not subject to production test - specified by design.


## 8.7 Electrical Characteristics Protection - Power Output Stages

Vs = 6 V to 18 V, TJ =- 40 °C to +150 ℃

Typical values: Vs = 13.5 V, TJ= 25 ℃

Typical resistive loads connected to the outputs for testing (unless otherwise specified):

RL = 3.3 22


### 8.7.1 Protection Power Output Stage - 20 m22


<table>
<caption>Table 17 Electrical Characteristics: Protection - 20 ml2</caption>
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
<td>Overload Detection Current at TJ =- 40 ℃</td>
<td>/L(OVLO) _- 40</td>
<td>65</td>
<td>72</td>
<td>80</td>
<td>A</td>
<td>1) TJ =- 40 °℃ d//dt = 0.4 A/us see Figure 24 and Figure 25</td>
<td>P_8.7.4.1</td>
</tr>
<tr>
<td>Overload Detection Current at TJ = 25 ℃</td>
<td>L(OVLO)_25</td>
<td>62</td>
<td>71</td>
<td>80</td>
<td>A</td>
<td>2) TJ =25 °℃ d//dt = 0.4 A/us see Figure 24 and Figure 25</td>
<td>P_8.7.4.7</td>
</tr>
<tr>
<td>Overload Detection Current at TJ = 150 ℃</td>
<td>/L(OVLO)_150</td>
<td>52</td>
<td>61</td>
<td>69</td>
<td>A</td>
<td>2) TJ = 150 ℃ d//dt = 0.4 A/us see Figure 24 and Figure 25</td>
<td>P_8.7.4.8</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="39" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 40" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


#### Protection


<table>
<caption>Table 17 Electrical Characteristics: Protection - 20 ml2 (continued)</caption>
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
<td>Overload Detection Current at High Vos</td>
<td>IL(OVL1)</td>
<td>–</td>
<td>40</td>
<td>–</td>
<td>A</td>
<td>2) d//dt = 0.4 A/us see Figure 24</td>
<td>P_8.7.4.5</td>
</tr>
<tr>
<td>Overload Detection Current Jump Start Condition</td>
<td>IL(OVL_JS)</td>
<td>–</td>
<td>40</td>
<td>–</td>
<td>A</td>
<td>2) Vs&gt;VS(JS) d//dt = 0.4 A/us see Figure 26</td>
<td>P_8.7.4.6</td>
</tr>
</table>

1\) Functional test only.

2\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="40" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 41" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


Diagnosis


## 9 Diagnosis

For diagnosis purpose, the BTS7020-2EPA provides a combination of digital and analog signals at pin IS. These
signals are generically named SENSE and written /Is. In case of disabled diagnostic (DEN pin set to "low"), IS
pin becomes high impedance.

A sense resistor RSENSE must be connected between IS pin and module ground if the current sense diagnosis is
used. RSENSE value has to be higher than 820 02 (or 400 02 when a central Reverse Battery protection is present
on the battery feed) to limit the power losses in the sense circuitry. A typical value is RSENSE = 1.2 k£2.

Due to the internal connection between IS pin and Vs supply voltage, it is not recommended to connect the IS
pin to the sense current output of other devices, if they are supplied by a different battery feed.

See Figure 32 for details as an overview.


<figure>
<figcaption>Figure 32 Diagnosis Block Diagram</figcaption>

VS

Channel 1
Channel 0

T

Overtemperature

Internal Counters

IS Pin Control
Logic

OUT1

INn

OUT0

DEN

IL / Klus

DSEL

MUX

VIS(FAULT)

\+
VDS(OLOFF)

MUX

/IS(OLOFF)

MUX

IS

RSENSE

Diagnosis_PROFET_2CH.emf

</figure>


### 9.1 Overview

Table 18 gives a quick reference to the state of the IS pin during BTS7020-2EPA operation.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="41" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 42" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->

Diagnosis


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
<td>Z /IS(FAULT) if counter &gt; 0</td>
</tr>
<tr>
<td>Short circuit to GND</td>
<td>~ GND</td>
<td>Z /IS(FAULT) if counter &gt; 0</td>
</tr>
<tr>
<td>Overtemperature</td>
<td>Z</td>
<td>IS(FAULT)</td>
</tr>
<tr>
<td>Short circuit to Vs</td>
<td>Vs</td>
<td>VIS(OLOFF) (/IS(FAULT) if counter &gt; 0)</td>
</tr>
<tr>
<td>Open Load</td>
<td>&lt; VS - VDS(OLOFF) &gt; Vs - VDS(OLOF) 1)</td>
<td>Z I IS(OLOFF) (in both cases /IS(FAULT) if counter &gt;0)</td>
</tr>
<tr>
<td>Inverse current</td>
<td>~ VINV = VOUT &gt; VS</td>
<td>VIS(OLOFF) (/IS(FAULT) if counter &gt; 0)</td>
</tr>
<tr>
<td>Normal operation</td>
<td rowspan="8">“high"</td>
<td>~ Vs</td>
<td>lis =1L / KILIS</td>
</tr>
<tr>
<td>Overcurrent</td>
<td>&lt; Vs</td>
<td>/ IS(FAULT)</td>
</tr>
<tr>
<td>Short circuit to GND</td>
<td>~ GND</td>
<td>/IS(FAULT)</td>
</tr>
<tr>
<td>Overtemperature</td>
<td>Z</td>
<td>IS (FAULT)</td>
</tr>
<tr>
<td>Short circuit to Vs</td>
<td>Vs</td>
<td>IS &lt; /L / KILIS</td>
</tr>
<tr>
<td>Open Load</td>
<td>~ V5 2 )</td>
<td>/ Is = IS (EN)</td>
</tr>
<tr>
<td>Under load (e.g. Output Voltage Limitation condition)</td>
<td>~ VS3)</td>
<td>IS(EN) &lt;155 /L(NOM) / KILIS</td>
</tr>
<tr>
<td>Inverse current</td>
<td>~ VINV = VOUT &gt; Vs</td>
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

3\) The output current has to be higher than /L(OL)-


#### 9.1.1 SENSE signal truth table

In case DEN is set to "high", the SENSE for the selected channel is enabled or disabled using DSEL pin. Table 19
gives the truth table.


<table>
<caption>Table 19 Diagnostic Truth Table</caption>
<tr>
<th>DEN</th>
<th>DSEL</th>
<th>IS</th>
</tr>
<tr>
<td>"low"</td>
<td>not relevant</td>
<td>Z</td>
</tr>
<tr>
<td>"high"</td>
<td>"low"</td>
<td>SENSE output 0</td>
</tr>
<tr>
<td>"high"</td>
<td>“high"</td>
<td>SENSE output 1</td>
</tr>
</table>


### 9.2 Diagnosis in ON state

A current proportional to the load current (ratio kILIs =/L/ /Is) is provided at pin IS when the following conditions
are fulfilled:

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="42" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 43" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


## Diagnosis

· The power output stage is switched ON with VDs < VDS(OLOFF)

· The diagnosis is enabled for that channel

. No fault (as described in Chapter 8.3) is present or was present and not cleared yet (see Chapter 9.2.2 for
further details)

If a "hard" failure mode is present or was present and not cleared yet a current /IS(FAULT) is provided at IS pin.


### 9.2.1 Current Sense (KILIS)

The accuracy of the sense current depends on temperature and load current. IIs increases linearly with /L
output current until it reaches the saturation current /IS(SAT). In case of Open Load at the output stage (/) close
to 0 A), the maximum sense current /IS(EN) (no load, diagnosis enabled) is specified. This condition is shown in
Figure 34. The blue line represents the ideal kjus line, while the red lines show the behavior of a typical
product.

An external RC filter between IS pin and microcontroller ADC input pin is recommended to reduce signal ripple
and oscillations (a minimum time constant of 1 us for the RC filter is recommended).

The kILIs factor is specified with limits that take into account effects due to temperature, supply voltage and
manufacturing process. Tighter limits are possible (within a defined current window) with calibration:

· A well-defined and precise current (/L(CAL) is applied at the output during End of Line test at customer side

. The corresponding current at IS pin is measured and the kILIs is calculated (KILIS @ IL(CAL))

. Within the current range going from / L(CAL)_ to / L(CAL)_H the KILIS is equal to KILIS @ L(CAL) with limits defined by
AKILIS

The derating of kILIs after calibration is calculated using the formulas in Figure 33 and it is specified by AKILIS

AK ILIS, MAX = 100 · MAX

KILIS@IL(CAL)_L
KILIS@IL(CAL)
1,
KILIS@IL(CAL)_H
KILIS@IL(CAL)
1

AK ILIS,MIN = 100 . MIN
KILIS@IL(CAL)_L
KILIS@IL(CAL)

1,
KILIS@IL(CAL)_H
KILIS@IL(CAL)
1

Figure 33 AKILIS calculation formulas

The calibration is intended to be performed at TA(CAL) = 25℃. The parameter AKILIs includes the drift
overtemperature as well as the drift over the current range from / L(CAL)_ to / L(CAL)_H.


<figure>
<figcaption>Figure 34 Current Sense Ratio in Open Load at ON condition</figcaption>

/Is

/IS(OL)

IS(EN)

L(OL)

IL

Diagnosis_OLON_adv.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="43" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 44" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


<!-- PageHeader="Diagnosis" -->


### 9.2.2 Fault Current (/IS(FAULT))

As soon a protection event occurs, changing the value of the internal retry counter (see Chapter 8.3 for more
details) from its reset state, a current /IS(FAULT) is provided by pin IS when DEN is set to "high" and the affected
channel is selected. The following 3 situations may occur:

. If the channel is ON and the number of retries is lower than "I RETRY(CR) + TRETRY(CYC) * TRETRY(NT)", the current
VIS(FAULT) is provided for a time tIS(FAULT)_D after the channel is allowed to restart, after which /Is = /L / KILIs (as
shown in Figure 35). During a retry cycle (while timer tRETRY is running) the current /IS(FAULT) is provided each
time the channel diagnosis is checked

. If the channel is ON and the number of retries is equal than "I RETRY(CR) + TRETRY(CYC) * TRETRY(NT)", the current
/IS(FAULT) is provided until the internal counter is reset (either by expiring of tDELAY(CR) time or by DEN pin
pulse, as described in Chapter 8.3.1)

. If the channel is OFF and the internal counter is not in the reset state, the current /IS(FAULT) is provided each
time the channel diagnosis is checked


<figure>
<figcaption>Figure 35 /IS(FAULT) at Load Switching</figcaption>

IN

IL(OVL)

IL

t

Mr

t

In ter nal
counter

0

1

2

0

t

DEN

tIs(FAUL T)_D

t

LIS(FAUL T)

IS(FAULT)

/Is

IL/ KILIS

t

Diagnosis_PROFET_JISFAULT_load.emf

</figure>


Figure 36 adds the behavior of SENSE signal to the timing diagram seen in Figure 28, while Figure 37 shows
the relation between /Is = 11 / KILIS, 'IS(SAT) and /IS(FAULT).

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="44" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 45" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


Diagnosis


<figure>
<figcaption>Figure 36 SENSE behavior in Fault condition</figcaption>

IN

Short circuit
to ground

t

nRETRY(CYC)

t

"retry" cycle

nRETRY(CR)

nRETRY(NT)

IL

nRETRY(NT)

TRETRY

tRETRY

tDELAY(CR)

t

Internal
counter

0

1

nRETRY(CR)

ØRETRY(CR) + "RETRY(NT)

'RETRY(CR) + (nRETRY(CYC) * [RETRY(NT)

0

t

DEN

VIS(FAUL T)

VIS(FAUL T)

IS(FAUL T)

t

lis

IL/KILIS

t

Diagnosis_PROFET_JISFAULT.emf

</figure>


<figure>
<figcaption>Figure 37 SENSE behavior - overview</figcaption>

/Is

/IS(SAT), max

/IS(SAT)

/IS(FAUL T), max

/IS(FAUL T)

/IS(SAT),min =
/IS(FAUL T),min

/L / KILIS

/L(OVL)

IL

Diagnosis_PROFET_JISFAULT_IISSAT.emf

</figure>


## 9.3 Diagnosis in OFF state

When a power output stage is in OFF state, the BTS7020-2EPA can measure the output voltage and compare
it with a threshold voltage. In this way, using some additional external components (a pull-down resistor and
a switchable pull-up current source), it is possible to detect if the load is missing or if there is a short circuit to
battery. If a Fault condition was detected by the device (the internal counter has a value different from the
reset value, as described in Chapter 9.2.2) a current /IS(FAULT) is provided by IS pin each time the channel
diagnosis is checked also in OFF state.

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="45" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 46" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


<!-- PageHeader="Diagnosis" -->


### 9.3.1 Open Load current (/Is(OLOFF))

In OFF state, when DEN pin is set to "high" and a channel is selected using DSEL pin, the Vos voltage is
compared with a threshold voltage VDS(OLOFF). If the load is properly connected and there is no short circuit to
battery, Vps ~ Vs therefore VDs > VDS(OLOFF). When the diagnosis is active and VDs ≤ VDS(OLOFF), a current /IS(OLOFF) iS
provided by IS pin. Figure 38 shows the relationship between /IS(OLOFF) and /IS(FAULT) as functions of VDs. The two
currents do not overlap making it always possible to differentiate between Open Load in OFF and Fault
condition.


<figure>
<figcaption>Figure 38 lIs in OFF State</figcaption>

his

VIS(FAUL T)

/IS(OLOFF)

VDS(OLOFF)

VDS

Diagnosis_PROFET_IISOL OFF.emf

</figure>


It is necessary to wait a time tIS(OLOFF)_D between the falling edge of the input pin and the sensing at pin IS for
Open Load in OFF diagnosis to allow the internal comparator to settle. In Figure 39 the timings for an Open
Load detection are shown - the load is always disconnected.


<figure>
<figcaption>Figure 39 Open Load in OFF Timings - load disconnected</figcaption>

IN

t

DEN

tis(OLOFF)_D

t

VOUT

~ Vs

VDS(OLOFF)

Load
connect ed

t

Ils

/IS(OLOFF)

|S(OL)

t

Diagnosis_PROFET_OLOFF_time.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="46" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 47" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


<!-- PageHeader="Diagnosis" -->


## 9.4 SENSE Timings

Figure 40 and Figure 42 show the timing during settling tsIS(ON) and disabling tsIS(OFF) of the SENSE (including
the case of load change). As a proper signal cannot be established before the load current is stable (therefore
before toN), tSIS(DIAG) = tSIS(ON) + tON·


<figure>
<figcaption>Figure 40 SENSE Settling / Disabling Timing</figcaption>

IN

OFF

ON

OFF

t

DEN

tO FF

t

IL

tsIS (LC)

tsIS (OFF)

tsIS (ON)

tsIS (OFF)

t

lis

İşIS (DIAG)

Diagnose_PROFET_SENSE_timings.emf

t

</figure>


<figure>
<figcaption>Figure 41 SENSE Timing with Small Load Current</figcaption>

IN

OFF

ON

OFF

t

DEN

t

IL

tsIS(ON)_SLC

tsIS(ON)

tsIS(LC)_SLC

t

lıs

t

Diagnose_PROFET_SENSE_timings_SLC.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="47" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 48" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

Infineon

</figure>


<!-- PageHeader="Diagnosis" -->


<figure>
<figcaption>Figure 42 SENSE Settling Timing - Channel Change</figcaption>

DEN

t

DSEL

t

IL0

L(CAL)

t

/L1

IL(CAL)_L

IL(CAL)_OL

tsIS(CC)

tsIS (OFF)

tsIS (ON)

tsIS(CC)_SLC

t

lIs

t

Diagnose_PROFET_SENSE_timings_CC.emf

</figure>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="48" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 49" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->

Diagnosis


## 9.5 Electrical Characteristics Diagnosis

Vs = 6 V to 18 V, TJ =- 40 °C to +150 ℃
Typical values: Vs = 13.5 V, T ]= 25 ℃

Typical resistive loads connected to the outputs for testing (unless otherwise specified):
RL = 3.3 22


<table>
<caption>Table 20 Electrical Characteristics: Diagnosis - General</caption>
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
<td>1) Vs = 8 V to 18 V RSENSE = 1.2 k£2 See Figure 37</td>
<td>P_9.6.0.13</td>
</tr>
<tr>
<td>SENSE Saturation Current</td>
<td>/ IS(SAT)</td>
<td>4.1</td>
<td>–</td>
<td>15</td>
<td>mA</td>
<td>1) Vs = 6 V to 18 V RSENSE = 1.2 k£2 See Figure 37</td>
<td>P_9.6.0.14</td>
</tr>
<tr>
<td>SENSE Leakage Current when Disabled</td>
<td>VIS(OFF)</td>
<td>–</td>
<td>0.01</td>
<td>0.5</td>
<td>µA</td>
<td>DEN = "low" IL≥ 1L(NOM) VIS = 0 V</td>
<td>P_9.6.0.2</td>
</tr>
<tr>
<td>SENSE Leakage Current when Enabled at TJ ≤ 85 ℃</td>
<td>‘S(EN)_85</td>
<td>–</td>
<td>0.2</td>
<td>1</td>
<td>µA</td>
<td>1) TJ ≤85℃ DEN = "high" 1=0A See Figure 34</td>
<td>P_9.6.0.3</td>
</tr>
<tr>
<td>SENSE Leakage Current when Enabled at TJ = 150 ℃</td>
<td>/IS(EN)_150</td>
<td>–</td>
<td>0.2</td>
<td>1</td>
<td>µA</td>
<td>TJ=150 ℃ DEN = "high" 1=0A See Figure 34</td>
<td>P_9.6.0.4</td>
</tr>
<tr>
<td>SENSE Operative Range for KILIS Operation (Vs- VIS)</td>
<td>VsIS_k</td>
<td>–</td>
<td>0.5</td>
<td>1</td>
<td>V</td>
<td>1) Vs =6V IN = DEN = “high" / ≤1.2 * |L(NOM)</td>
<td>P_9.6.0.6</td>
</tr>
<tr>
<td>SENSE Operative Range for Open Load at OFF Diagnosis (Vs - VIs)</td>
<td>VSIS_OL</td>
<td>–</td>
<td>0.5</td>
<td>1</td>
<td>V</td>
<td>1) Vs = 6 V IN = "low" DEN = "high"</td>
<td>P_9.6.0.7</td>
</tr>
<tr>
<td>SENSE Operative Range for Fault Diagnosis (Vs - VIs)</td>
<td>VSIS_F</td>
<td>–</td>
<td>0.5</td>
<td>1</td>
<td>V</td>
<td>1) Vs = 6V IN = "low" DEN = "high" counter &gt;0</td>
<td>P_9.6.0.8</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="49" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 50" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->

Diagnosis


<table>
<caption>Table 20 Electrical Characteristics: Diagnosis - General (continued)</caption>
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
<td>Power Supply to IS Pin Clamping Voltage at TJ =- 40 ℃</td>
<td>SIS(CLAMP) _- 40</td>
<td>33</td>
<td>36.5</td>
<td>42</td>
<td>V</td>
<td>lis = 1 mA TJ =- 40 ℃ See Figure 17</td>
<td>P_9.6.0.9</td>
</tr>
<tr>
<td>Power Supply to IS Pin Clamping Voltage at TJ ≥ 25℃</td>
<td>V SIS(CLAMP)_25</td>
<td>35</td>
<td>38</td>
<td>44</td>
<td>V</td>
<td>2) lis = 1 mA TJ ≥25℃ See Figure 17</td>
<td>P_9.6.0.10</td>
</tr>
</table>

1\) Not subject to production test - specified by design.

2\) Tested at TJ = 150°C.


### 9.5.1 Electrical Characteristics Diagnosis - PROFET™


<table>
<caption>Table 21 Electrical Characteristics: Diagnosis - PROFET™</caption>
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
<td>See Figure 37 and Figure 38</td>
<td>P_9.6.1.1</td>
</tr>
<tr>
<td>SENSE Open Load in OFF Current</td>
<td>/IS(OLOFF)</td>
<td>1.9</td>
<td>2.5</td>
<td>3.5</td>
<td>mA</td>
<td>See Figure 37 and Figure 38</td>
<td>P_9.6.1.2</td>
</tr>
<tr>
<td>SENSE Delay Time at Channel Switch ON after Last Fault Condition</td>
<td>tIS(FAULT)_D</td>
<td>–</td>
<td>500</td>
<td>–</td>
<td>μς</td>
<td>1) See Figure 35</td>
<td>P_9.6.1.3</td>
</tr>
<tr>
<td>SENSE Open Load in OFF Delay Time</td>
<td>tIS(OLOF)_D</td>
<td>30</td>
<td>70</td>
<td>120</td>
<td>μς</td>
<td>VDS &lt; VOL(OF) from IN falling edge to lis = IS(OLOFF), MIN * 0.9 DEN = "high" counter = 0 See Figure 39</td>
<td>P_9.6.1.4</td>
</tr>
<tr>
<td>Open Load Vps Detection Threshold in OFF State</td>
<td>VDS(OLOFF)</td>
<td>1.3</td>
<td>1.8</td>
<td>2.3</td>
<td>V</td>
<td>See Figure 38</td>
<td>P_9.6.1.5</td>
</tr>
<tr>
<td>SENSE Settling Time with Nominal Load Current Stable</td>
<td>tsIS(ON)</td>
<td>–</td>
<td>5</td>
<td>20</td>
<td>μς</td>
<td>1=1L(CAL) from DEN rising edge to /Is = 1L / (KILIS,MAX @ /1) * 0.9 See Figure 40</td>
<td>P_9.6.1.6</td>
</tr>
<tr>
<td>SENSE Settling Time with Small Load Current Stable</td>
<td>tsIS(ON)_SLC</td>
<td>–</td>
<td>–</td>
<td>60</td>
<td>μς</td>
<td>1) IL=1L(CAL)_OL from DEN rising edge to /Is = /L / (KILIS,MAX @ /1) * 0.9</td>
<td>P_9.6.1.13</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="50" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 51" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->

Diagnosis


<table>
<caption>Table 21 Electrical Characteristics: Diagnosis - PROFET™ (continued)</caption>
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
<td>SENSE Disable Time</td>
<td>İşIS(OFF)</td>
<td>–</td>
<td>5</td>
<td>20</td>
<td>μς</td>
<td>1) From DEN falling edge to lis = /Is(OFF) See Figure 40</td>
<td>P_9.6.1.8</td>
</tr>
<tr>
<td>SENSE Settling Time after Load Change</td>
<td>tsIS(LC)</td>
<td>–</td>
<td>5</td>
<td>20</td>
<td>μς</td>
<td>1) from / = L(CAL)_ to 1L=/L(CAL) (see AKILIS(NOM)) See Figure 40</td>
<td>P_9.6.1.9</td>
</tr>
<tr>
<td>SENSE Settling Time after Load Change with Small Load Current</td>
<td>tsIS(LC)_SLC</td>
<td>–</td>
<td>250</td>
<td>400</td>
<td>μς</td>
<td>1) DEN = "high" from Load Change tolls =/L/(KILIS@1) from IL(CAL) to LOCAL)_OL</td>
<td>P_9.6.1.14</td>
</tr>
<tr>
<td>SENSE Settling Time after Channel Change</td>
<td>tsIS(CC)</td>
<td>–</td>
<td>5</td>
<td>20</td>
<td>μς</td>
<td>1) Start channel: IL= IL(CAL) End channel: IL= 1L(CAL)_L (see AKILIS(NOM)) See Figure 42</td>
<td>P_9.6.1.10</td>
</tr>
<tr>
<td>SENSE Settling Time after Channel Change with Small Load Current</td>
<td>tsIS(CC)_SLC</td>
<td>–</td>
<td>–</td>
<td>60</td>
<td>μς</td>
<td>1) DEN = "high" from DSEL toggling to /Is = 1L/ (KILIS,MIN @ /1) * 1.1 Start channel: 1=1L(CAL) End Channel: IL=IL(CAL)_OL (see AKILIS(NOM) and AKILIS (OL))</td>
<td>P_9.6.1.15</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


## 9.6 Electrical Characteristics Diagnosis - Power Output Stages

Vs = 6 V to 18 V, T] = - 40 °C to +150 ℃

Typical values: Vs = 13.5 V, TJ = 25 ℃

Typical resistive loads connected to the outputs for testing (unless otherwise specified):

RL = 3.3 22

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="51" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 52" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->

Diagnosis


### 9.6.1 Diagnosis Power Output Stage - 20 ml2


<table>
<caption>Table 22 Electrical Characteristics: Diagnosis - 20 ml2</caption>
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
<td>6</td>
<td>14</td>
<td>28</td>
<td>mA</td>
<td>lis = /Is(OL) = 4 µA See Figure 34</td>
<td>P_9.7.4.1</td>
</tr>
<tr>
<td>Current Sense Ratio at IL = IL02</td>
<td>KILIS02</td>
<td>-29.5%</td>
<td>3700</td>
<td>+29.5%</td>
<td></td>
<td>/102 = 20 mA</td>
<td>P_9.7.4.6</td>
</tr>
<tr>
<td>Current Sense Ratio at 1L=/L05</td>
<td>KILIS05</td>
<td>-24.0%</td>
<td>3700</td>
<td>+24.0%</td>
<td></td>
<td>/L05 = 100 mA</td>
<td>P_9.7.4.9</td>
</tr>
<tr>
<td>Current Sense Ratio at 1L=/L08</td>
<td>KILIS08</td>
<td>-23.5%</td>
<td>3700</td>
<td>+23.5%</td>
<td></td>
<td>/L08 = 250 mA</td>
<td>P_9.7.4.12</td>
</tr>
<tr>
<td>Current Sense Ratio at 1=/L11</td>
<td>KILIS11</td>
<td>-12.0%</td>
<td>3700</td>
<td>+12.0%</td>
<td></td>
<td>/L11 = 1 A</td>
<td>P_9.7.4.15</td>
</tr>
<tr>
<td>Current Sense Ratio at /L=1L13</td>
<td>KILIS13</td>
<td>-7.3%</td>
<td>3700</td>
<td>+7.3%</td>
<td></td>
<td>/L13 = 2 A</td>
<td>P_9.7.4.17</td>
</tr>
<tr>
<td>Current Sense Ratio at 1=1115</td>
<td>KILIS15</td>
<td>-4.1%</td>
<td>3700</td>
<td>+4.1%</td>
<td></td>
<td>/115 = 4 A</td>
<td>P_9.7.4.19</td>
</tr>
<tr>
<td>Current Sense Ratio at 1=1L17</td>
<td>KILIS17</td>
<td>-3.7%</td>
<td>3700</td>
<td>+3.7%</td>
<td></td>
<td>/L17 = 7 A</td>
<td>P_9.7.4.21</td>
</tr>
<tr>
<td>SENSE Current Derating with Low Current Calibration</td>
<td>KILIS(OL)</td>
<td>-30</td>
<td>0</td>
<td>+30</td>
<td>%</td>
<td>1) IL(CAL)_OL = /L05 IL(CAL)_O_H = /L08 IL(CAL)_OLL = /102 TA(CAL) = 25 ℃ See Figure 33</td>
<td>P_9.7.4.27</td>
</tr>
<tr>
<td>SENSE Current Derating with Nominal Current Calibration</td>
<td>ILIS(NOM)</td>
<td>-4</td>
<td>0</td>
<td>+4</td>
<td>%</td>
<td>1) IL(CAL) = 115 /L(CAL)_H = /17 IL(CAL)_L = |13 TA(CAL) = 25 ℃ See Figure 33</td>
<td>P_9.7.4.29</td>
</tr>
</table>

1\) Not subject to production test - specified by design.


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="52" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 53" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


#### Application Information


##### 10 Application Information

Note:
The following information is given as a hint for the implementation of the device only and shall not
be regarded as a description or warranty of a certain functionality, condition or quality of the device.


##### 10.1 Application Setup


<figure>
<figcaption>Figure 43 BTS7020-2EPA Application Diagram</figcaption>

VBAT

ZWIRE

Optional

Optional

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

IN0

6

GPIO

RIN

IN1

GPIO

RDEN

DEN

OUT0

GPIO

ROSEL

DSEL

RPD

COUT0

DZ2

Cvs2

Microcontroller

PROFET™+2
12V

ZWRE

OUT1

ADC

RADC

RIS PROT

IS

COUT1

ZWIRE

VSS

CSENSE

Dzi

RSENSE

ZLOAD*

ZLOAD*

Logic GND

Power GND

Optional

Chassis GND

*See Chapter 1 „Potential Applications“

App_2CM_INTDO_CVG_LOml

</figure>

Note:
This is a very simplified example of an application circuit. The function must be verified in the real
application.


<table>
<caption>Table 23 Loads considered for Reverse Polarity setup (see P_4.1.0.5)</caption>
<tr>
<th>Output</th>
<th>RDS(ON),max @ T] =150 ℃</th>
<th>Load connected</th>
</tr>
<tr>
<td>20 ml2</td>
<td>23.7 m22</td>
<td>2x P27W + R5W</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="53" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 54" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


##### Application Information


### 10.2 External Components


<table>
<caption>Table 24 Suggested Component values</caption>
<tr>
<th>Reference</th>
<th>Value</th>
<th>Purpose</th>
</tr>
<tr>
<td>RIN</td>
<td>4.7 kQ</td>
<td>Protection of the microcontroller during Overvoltage and Reverse Polarity Necessary to switch OFF BTS7020-2EPA output during Loss of Ground</td>
</tr>
<tr>
<td>RDEN</td>
<td>4.7 kQ2</td>
<td>Protection of the microcontroller during Overvoltage and Reverse Polarity Necessary to switch OFF BTS7020-2EPA output during Loss of Ground</td>
</tr>
<tr>
<td>RDSEL</td>
<td>4.7 k22</td>
<td>Protection of the microcontroller during Overvoltage and Reverse Polarity Necessary to switch OFF BTS7020-2EPA output during Loss of Ground</td>
</tr>
<tr>
<td>RPD</td>
<td>47 kQ</td>
<td>Output polarization (pull-down) Ensures polarization of BTS7020-2EPA outputs to distinguish between Open Load and Short to Vs in OFF Diagnosis</td>
</tr>
<tr>
<td>ROL</td>
<td>1.5 kQ</td>
<td>Output polarization (pull-up) Ensures polarization of BTS7020-2EPA output during Open Load in OFF diagnosis</td>
</tr>
<tr>
<td>COUT</td>
<td>10 nF</td>
<td>Protection of BTS7020-2EPA output during ESD events and BCI</td>
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
<td>4.7 kQ</td>
<td>Protection during Overvoltage, Reverse Polarity, Loss of Ground Value to be tuned according to microcontroller specifications</td>
</tr>
<tr>
<td>DZ1</td>
<td>7 V Z-Diode</td>
<td>Protection of microcontroller during Overvoltage</td>
</tr>
<tr>
<td>RADC</td>
<td>4.7 kQ</td>
<td>Protection of microcontroller ADC input during Overvoltage, Reverse Polarity, Loss of Ground Value to be tuned according to microcontroller specifications</td>
</tr>
<tr>
<td>CSENSE</td>
<td>220 pF</td>
<td>Sense signal filtering A time constant (RADC * CSENSE) longer than 1 us is recommended</td>
</tr>
<tr>
<td>RGND</td>
<td>47 12</td>
<td>Protection in case of Overvoltage and Loss of Battery while driving inductive loads</td>
</tr>
</table>


## 10.3 Further Application Information

· Please contact us for information regarding the Pin FMEA

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="54" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 55" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


### Application Information

. For further information you may contact http://www.infineon.com/

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="55" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 56" -->


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


<figure>

<!-- PageHeader="Infineon" -->

</figure>


#### Package Outlines


##### 11 Package Outlines


<figure>
<figcaption>Figure 44 PG-TSDSO-14 (Thin (Slim) Dual Small Outline 14 pins) Package Outline</figcaption>

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

14x

0.67±0.25

0

SEATING COPLANARITY
PLANE

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

00

14

F

D

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
<figcaption>Figure 45 PG-TSDSO-14 (Thin (Slim) Dual Small Outline 14 pins) Package pads and stencil</figcaption>

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
<!-- PageNumber="56" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 57" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


###### Package Outlines


####### Green product (RoHS compliant)

To meet the world-wide customer requirements for environmentally friendly products and to be compliant
with government regulations the device is available as a green product. Green products are RoHS-Compliant
(i.e Pb-free finish on leads and suitable for Pb-free soldering according to IPC/JEDEC J-STD-020).


####### Further information on packages

https://www.infineon.com/packages

<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="57" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 58" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->

Revision History


##### 12 Revision History


<table>
<caption>Table 25 BTS7020-2EPA - List of changes</caption>
<tr>
<th>Revision</th>
<th>Changes</th>
</tr>
<tr>
<td>1.05, 2019-10-15</td>
<td>P_8.7.4.1, P_8.7.4.7, P_8.7.4.8 updated (added in Note or Test Condition: link to Figure 25) P_7.5.4.4, P_7.5.4.5 updated (added in Note or Test Condition: DEN = "low"; link to Figure 19) P_7.5.4.12 updated (added in Note or Test Condition: see Figure 21; deleted unnecessary space in Symbol: |dVOUT / dt | &gt; |dVOUT / dt|) P_8.7.4.6 updated (added in Note or Test Condition: see Figure 26) P_9.7.4.1 updated (added in Note or Test Condition: See Figure 34) P_9.7.4.6 updated (Min./Max .: - 45%/+45% &gt;-29.5%/+29.5%) P_9.7.4.9 updated (Min./Max .: - 38%/+38% &gt;-24.0%/+24.0%) P_9.7.4.12 updated (Min./Max .: - 34%/+34% -- 23.5%/+23.5%) P_9.7.4.15 updated (Min./Max .: - 22%/+22% &gt;-12.0%/+12.0%) P_9.7.4.17 updated (Min./Max .: - 9%/+9% -- 7.3%/+7.3%) P_9.7.4.19 updated (Min./Max .: - 6%/+6% &gt;-4.1%/+4.1%) P_9.7.4.21 updated (Min./Max .: - 5%/+5% &gt; -3.7%/+3.7%) P_7.5.4.11 updated (added in Note or Test Condition: see Figure 19) Figure 1, Figure 43 updated Chapter 1 updated (or LED equivalent &gt; or equivalent electronic loads (e.g. LED modules)) P_4.3.0.7 added Table 24 updated Chapter 5.1 updated (added: see Chapter 10 for the complete application setup overview)</td>
</tr>
<tr>
<td>1.04, 2019-06-26</td>
<td>Chapter 9.2 updated (2 V &gt; VDS(OLOF) General: updated (ReverSave™ &gt; ReverseON) Chapter 1 updated ((inserted headline "Product Validation"), (Qualified in accordance with AEC Q100 grade 1 &gt; Qualified for automotive applications. Product validation according to AEC-Q100 Grade 1.)) General: updated Product Name (PROFET™+2 &gt; PROFET™+2 12V) Page 1: updated figure product Table 24 updated punctuation</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="58" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 59" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->

Revision History


<table>
<caption>Table 25 BTS7020-2EPA - List of changes</caption>
<tr>
<th>Revision</th>
<th>Changes</th>
</tr>
<tr>
<td>1.03, 2018-10-18</td>
<td>Chapter 9.3.1 updated (typo) Page 1: updated (Package PG-TSDSO-14-22 &gt; Package PG-TSDSO-14) Figure 29 updated Figure 44 updated (PG-TSDSO-14-22 (Thin (Slim) Dual Small Outline 14 pins) Package Outline &gt; PG-TSDSO-14 (Thin (Slim) Dual Small Outline 14 pins) Package Outline) Figure 45 updated (PG-TSDSO-14-22 (Thin (Slim) Dual Small Outline 14 pins) Package pads and stencil &gt; PG-TSDSO-14 (Thin (Slim) Dual Small Outline 14 pins) Package pads and stencil) Table 1 updated ((Symbol: /VS(SLEEP) &gt; /VS(SLEEP)_85), (Parameter: Minimum Overvoltage protection (T) =25 ℃) &gt; Minimum Overvoltage protection (T] ≥ 25 ℃)) P_9.6.0.6 updated (Note or Test Condition: removed unnecessary line-break) Chapter 7.4.1 updated chapter title (PROFET &gt; PROFET™) Table 12 updated table title (PROFET &gt; PROFET™) Chapter 8.6.1 updated chapter title (PROFET &gt; PROFET™) Table 16 updated table title (PROFET &gt; PROFET™M) Chapter 9.5.1 updated chapter title (PROFET &gt; PROFET™) Table 21 updated table title (PROFET &gt; PROFET™) P_4.1.0.21, P_4.1.0.22, P_4.1.0.23, P_4.1.0.24 updated (footnote ESD standards) Table 1 updated (RDS(ON) &gt; RDS(ON)_150), (VDS(CLAMP) &gt; VDS(CLAMP)_25) Chapter 8.5.2 updated phrasing P_7.5.4.14 Table subheading "Switching Energy" added P_7.5.4.15 Table subheading "Switching Energy" added Chapter 6.4 added conditions Chapter 7.5 added conditions P_7.5.4.14 updated (Test condition: add "See Figure") P_7.5.4.15 updated (Test condition: add "See Figure") Chapter 8.7 added conditions Chapter 9.6 added conditions P_9.7.4.27 updated (Test condition: add "See Figure") P_9.7.4.29 updated (Test condition: add "See Figure") Chapter 7.3.1 typo corrected (link to Figure 19 added)</td>
</tr>
<tr>
<td>1.02, 2017-11-17</td>
<td>Table 6 footnote updated ("Specified RthJA value is" removed) Figure 17 symbol updated (VIS(CLAMP) &gt; VSIS(CLAMP)</td>
</tr>
<tr>
<td>1.01, 2017-10-24</td>
<td>Figures updated (straight lines for signals that are crossing, points for connections; typos, capitalization/lower case printing) Typos and misspelling corrected according to style guidelines, inconsistencies among document resolved P_4.1.0.36 updated (symbol: /DI &gt; /DI(REV)) P_5.4.0.5 symbol updated (/DI &gt; DI(H) P_5.4.0.6 symbol updated (/DI &gt;/DI(L) Chapter 7.3.3 updated Table 24 updated (RDSEL included)</td>
</tr>
<tr>
<td>1.00, 2017-08-24</td>
<td>Data Sheet available</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="59" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 60" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


###### Table of Contents


###### Table of Contents


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
<td>Power Stage - 20 ml2</td>
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
<td>11</td>
</tr>
<tr>
<td>5</td>
<td>Logic Pins</td>
<td>13</td>
</tr>
<tr>
<td>5.1</td>
<td>Input Pins (INn)</td>
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
<td>Unsupplied</td>
<td>16</td>
</tr>
<tr>
<td>6.1.2</td>
<td>Power-up</td>
<td>16</td>
</tr>
<tr>
<td>6.1.3</td>
<td>Sleep mode</td>
<td>16</td>
</tr>
<tr>
<td>6.1.4</td>
<td>Stand-by mode</td>
<td>16</td>
</tr>
<tr>
<td>6.1.5</td>
<td>Active mode</td>
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
<td>18</td>
</tr>
<tr>
<td>6.4.1</td>
<td>BTS7020-2EPA . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .</td>
<td>18 . . . . . . . . . . . . . . . . . .</td>
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
<td>Switching Channels in Parallel</td>
<td>24</td>
</tr>
<tr>
<td>7.3.3</td>
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
<td>Electrical Characteristics Power Stages - PROFET™</td>
<td>25</td>
</tr>
<tr>
<td>7.5</td>
<td>Electrical Characteristics - Power Output Stages</td>
<td>26</td>
</tr>
<tr>
<td>7.5.1</td>
<td>Power Output Stage - 20 ml2</td>
<td>26</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="60" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 61" -->



<figure>

Infineon

</figure>


<!-- PageHeader="BTS7020-2EPA PROFET™+2 12V" -->


####### Table of Contents


<table>
<tr>
<th>8</th>
<th>Protection</th>
<th>29</th>
</tr>
<tr>
<td>8.1</td>
<td>Overtemperature Protection</td>
<td>29</td>
</tr>
<tr>
<td>8.2</td>
<td>Overload Protection</td>
<td>30</td>
</tr>
<tr>
<td>8.3</td>
<td>Protection and Diagnosis in case of Fault</td>
<td>33</td>
</tr>
<tr>
<td>8.3.1</td>
<td>Retry Strategy</td>
<td>33</td>
</tr>
<tr>
<td>8.4</td>
<td>Additional protections</td>
<td>36</td>
</tr>
<tr>
<td>8.4.1</td>
<td>Reverse Polarity Protection</td>
<td>36</td>
</tr>
<tr>
<td>8.4.2</td>
<td>Overvoltage Protection</td>
<td>37</td>
</tr>
<tr>
<td>8.5</td>
<td>Protection against loss of connection</td>
<td>37</td>
</tr>
<tr>
<td>8.5.1</td>
<td>Loss of Battery and Loss of Load</td>
<td>37</td>
</tr>
<tr>
<td>8.5.2</td>
<td>Loss of Ground</td>
<td>37</td>
</tr>
<tr>
<td>8.6</td>
<td>Electrical Characteristics Protection</td>
<td>38</td>
</tr>
<tr>
<td>8.6.1</td>
<td>Electrical Characteristics Protection - PROFET™</td>
<td>38</td>
</tr>
<tr>
<td>8.7</td>
<td>Electrical Characteristics Protection - Power Output Stages</td>
<td>39</td>
</tr>
<tr>
<td>8.7.1</td>
<td>Protection Power Output Stage - 20 ml2</td>
<td>39</td>
</tr>
<tr>
<td>9</td>
<td>Diagnosis</td>
<td>41</td>
</tr>
<tr>
<td>9.1</td>
<td>Overview</td>
<td>41</td>
</tr>
<tr>
<td>9.1.1</td>
<td>SENSE signal truth table</td>
<td>42</td>
</tr>
<tr>
<td>9.2</td>
<td>Diagnosis in ON state</td>
<td>42</td>
</tr>
<tr>
<td>9.2.1</td>
<td>Current Sense (KILIS)</td>
<td>43</td>
</tr>
<tr>
<td>9.2.2</td>
<td>Fault Current (/IS(FAULT))</td>
<td>44</td>
</tr>
<tr>
<td>9.3</td>
<td>Diagnosis in OFF state</td>
<td>45</td>
</tr>
<tr>
<td>9.3.1</td>
<td>Open Load current (/IS(OLOFF))</td>
<td>46</td>
</tr>
<tr>
<td>9.4</td>
<td>SENSE Timings</td>
<td>47</td>
</tr>
<tr>
<td>9.5</td>
<td>Electrical Characteristics Diagnosis</td>
<td>49</td>
</tr>
<tr>
<td>9.5.1</td>
<td>Electrical Characteristics Diagnosis - PROFET™</td>
<td>50</td>
</tr>
<tr>
<td>9.6</td>
<td>Electrical Characteristics Diagnosis - Power Output Stages</td>
<td>51</td>
</tr>
<tr>
<td>9.6.1</td>
<td>Diagnosis Power Output Stage - 20 ml2</td>
<td>52</td>
</tr>
<tr>
<td>10</td>
<td>Application Information</td>
<td>53</td>
</tr>
<tr>
<td>10.1</td>
<td>Application Setup</td>
<td>53</td>
</tr>
<tr>
<td>10.2</td>
<td>External Components</td>
<td>54</td>
</tr>
<tr>
<td>10.3</td>
<td>Further Application Information</td>
<td>54</td>
</tr>
<tr>
<td>11</td>
<td>Package Outlines</td>
<td>56</td>
</tr>
<tr>
<td>12</td>
<td>Revision History</td>
<td>58</td>
</tr>
<tr>
<td></td>
<td>Table of Contents</td>
<td>60</td>
</tr>
</table>


<!-- PageFooter="Data Sheet" -->
<!-- PageNumber="61" -->
<!-- PageFooter="Rev. 1.05 2019-10-15" -->
<!-- PageBreak -->



<!-- PageNumber="Side 62" -->


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
Z8F65710319


###### IMPORTANT NOTICE

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


###### WARNINGS

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
