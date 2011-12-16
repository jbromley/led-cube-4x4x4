v 20110115 2
C 40000 40000 0 0 0 title-B.sym
C 56100 49100 1 0 1 jumper-1.sym
{
T 55800 49600 5 8 0 0 0 6 1
device=JUMPER
T 56300 49100 5 10 1 1 0 6 1
refdes=J1
T 56800 50000 5 10 1 1 0 6 1
value=8-15V in
T 56100 49100 5 10 0 0 0 6 1
footprint=HEADER2_1
}
C 40700 49500 1 0 0 jumper-1.sym
{
T 41000 50000 5 8 0 0 0 0 1
device=JUMPER
T 40400 49500 5 10 1 1 0 0 1
refdes=J3
T 40700 49500 5 10 0 0 0 0 1
footprint=HEADER2_1
T 40200 50400 5 10 1 1 0 0 1
value=5V in
}
C 54100 49500 1 0 1 lm7805-1.sym
{
T 52500 50800 5 10 0 0 0 6 1
device=7805
T 52700 50500 5 10 1 1 0 0 1
refdes=U3
T 53900 50500 5 10 1 1 0 6 1
value=7805T
T 54100 49500 5 10 0 0 0 6 1
footprint=TO220
}
T 50100 40900 9 16 1 0 0 0 1
4x4x4 LED Cube
C 54800 50000 1 90 1 capacitor-2.sym
{
T 54100 49800 5 10 0 0 270 2 1
device=POLARIZED_CAPACITOR
T 54400 49800 5 10 1 1 0 6 1
refdes=C6
T 53900 49800 5 10 0 0 270 2 1
symversion=0.1
T 54400 49300 5 10 1 1 0 6 1
value=1000uF
T 54800 50000 5 10 0 0 0 6 1
footprint=RCY400P
}
C 52400 50100 1 90 1 capacitor-2.sym
{
T 51700 49900 5 10 0 0 270 2 1
device=POLARIZED_CAPACITOR
T 51900 49800 5 10 1 1 0 6 1
refdes=C7
T 51500 49900 5 10 0 0 270 2 1
symversion=0.1
T 52400 50100 5 10 0 0 0 6 1
footprint=RCY400P
T 52000 49400 5 10 1 1 0 6 1
value=10uF
}
C 52400 50500 1 0 1 5V-plus-1.sym
C 52300 48400 1 0 1 gnd-1.sym
N 52500 50100 52200 50100 4
N 54600 50000 54600 50100 4
N 53300 49500 53300 49100 4
N 56000 49100 52200 49100 4
N 52200 48700 52200 49200 4
N 52200 50100 52200 50500 4
C 41200 50500 1 0 0 5V-plus-1.sym
C 41300 49200 1 0 0 gnd-1.sym
N 40800 50500 41400 50500 4
N 40800 49500 41400 49500 4
C 46700 41600 1 0 0 mega16-dip40.sym
{
T 50100 49300 5 10 1 1 0 6 1
refdes=U1
T 47000 49800 5 10 0 0 0 0 1
device=ATMega16-DIP40
T 47000 50000 5 10 0 0 0 0 1
footprint=DIP40
}
C 44900 48600 1 90 0 crystal-1.sym
{
T 44400 48800 5 10 0 0 90 0 1
device=CRYSTAL
T 44600 49000 5 10 1 1 180 0 1
refdes=U2
T 44200 48800 5 10 0 0 90 0 1
symversion=0.1
}
C 43600 49300 1 0 0 capacitor-1.sym
{
T 43800 50000 5 10 0 0 0 0 1
device=CAPACITOR
T 43800 49800 5 10 1 1 0 0 1
refdes=C1
T 43800 50200 5 10 0 0 0 0 1
symversion=0.1
}
C 43600 48200 1 0 0 capacitor-1.sym
{
T 43800 48900 5 10 0 0 0 0 1
device=CAPACITOR
T 43800 48700 5 10 1 1 0 0 1
refdes=C2
T 43800 49100 5 10 0 0 0 0 1
symversion=0.1
}
C 42500 48700 1 0 0 gnd-1.sym
N 42600 49000 42600 49500 4
N 42600 49500 43600 49500 4
N 43600 48400 43200 48400 4
N 43200 48400 43200 49500 4
C 46300 50500 1 0 0 5V-plus-1.sym
C 50300 50500 1 0 0 5V-plus-1.sym
N 50500 50500 50500 48700 4
N 50500 48700 50400 48700 4
C 46600 49600 1 90 0 resistor-2.sym
{
T 46250 50000 5 10 0 0 90 0 1
device=RESISTOR
T 46400 50100 5 10 1 1 180 0 1
refdes=R17
}
C 43500 50300 1 0 0 switch-pushbutton-no-1.sym
{
T 43900 50600 5 10 1 1 0 0 1
refdes=S1
T 43900 50900 5 10 0 0 0 0 1
device=SWITCH_PUSHBUTTON_NO
}
N 46500 44700 46500 49600 4
N 46500 48100 46700 48100 4
N 44800 49500 44800 49300 4
N 43200 49500 43200 50300 4
N 43200 50300 43500 50300 4
C 48400 50500 1 0 0 5V-plus-1.sym
N 48600 50500 48600 49500 4
C 50900 50500 1 0 0 5V-plus-1.sym
N 51100 49100 51100 50500 4
C 51300 48200 1 90 0 capacitor-1.sym
{
T 50600 48400 5 10 0 0 90 0 1
device=CAPACITOR
T 51500 48500 5 10 1 1 180 0 1
refdes=C5
T 50400 48400 5 10 0 0 90 0 1
symversion=0.1
}
C 45200 47700 1 0 0 resistor-2.sym
{
T 45600 48050 5 10 0 0 0 0 1
device=RESISTOR
T 45400 48000 5 10 1 1 0 0 1
refdes=R22
}
C 45200 47100 1 0 0 resistor-2.sym
{
T 45600 47450 5 10 0 0 0 0 1
device=RESISTOR
T 45400 47400 5 10 1 1 0 0 1
refdes=R23
}
C 44900 48000 1 180 0 led-1.sym
{
T 44100 47400 5 10 0 0 180 0 1
device=LED
T 44100 47600 5 10 1 1 180 0 1
refdes=LED1
T 44100 47200 5 10 0 0 180 0 1
symversion=0.1
}
C 44900 47400 1 180 0 led-1.sym
{
T 44100 46800 5 10 0 0 180 0 1
device=LED
T 44100 47000 5 10 1 1 180 0 1
refdes=LED2
T 44100 46600 5 10 0 0 180 0 1
symversion=0.1
}
C 44600 46600 1 0 0 switch-pushbutton-no-1.sym
{
T 45000 46900 5 10 1 1 0 0 1
refdes=S2
T 45000 47200 5 10 0 0 0 0 1
device=SWITCH_PUSHBUTTON_NO
}
C 48400 40700 1 0 0 gnd-1.sym
N 44500 49500 45600 49500 4
N 44800 48400 44800 48600 4
N 44500 50300 45800 50300 4
N 45800 50300 45800 49500 4
N 45800 49500 46500 49500 4
N 44500 48400 46700 48400 4
N 45600 49500 45600 48700 4
N 45600 48700 46700 48700 4
N 46700 47500 46100 47500 4
N 46100 47500 46100 47800 4
N 46100 47200 46700 47200 4
N 46700 46600 45600 46600 4
N 45200 47800 44900 47800 4
N 45200 47200 44900 47200 4
C 43200 46300 1 0 0 gnd-1.sym
N 44000 47800 43300 47800 4
N 43300 47800 43300 46600 4
N 44000 47200 43300 47200 4
N 44600 46600 43300 46600 4
N 48500 41600 48500 41000 4
C 42100 44700 1 90 0 AVR_ISP6-1.sym
{
T 40800 45700 5 10 1 1 180 6 1
refdes=J2
T 40650 45000 5 10 0 0 90 0 1
device=HEADER6
T 40450 45000 5 10 0 0 90 0 1
footprint=CON_HDR-254P-3C-2R-6N__Molex_8624-Series
}
N 46700 45700 42800 45700 4
N 42800 45700 42800 44300 4
N 42800 44300 41200 44300 4
N 41200 44300 41200 44700 4
N 41500 44700 41500 44500 4
N 41500 44500 42600 44500 4
N 42600 44500 42600 45400 4
N 42600 45400 46700 45400 4
C 41000 46700 1 0 0 5V-plus-1.sym
C 42200 45800 1 0 0 gnd-1.sym
N 41200 46700 41200 46100 4
N 41800 46100 42300 46100 4
N 41800 44700 46500 44700 4
N 46700 46000 42600 46000 4
N 42600 46000 42600 46500 4
N 42600 46500 41500 46500 4
N 41500 46500 41500 46100 4
C 43900 43200 1 0 1 npn-2.sym
{
T 43300 43700 5 10 0 0 0 6 1
device=NPN_TRANSISTOR
T 43300 43700 5 10 1 1 0 6 1
refdes=Q1
}
C 44900 42400 1 0 1 npn-2.sym
{
T 44300 42900 5 10 0 0 0 6 1
device=NPN_TRANSISTOR
T 44300 42900 5 10 1 1 0 6 1
refdes=Q2
}
C 43900 41600 1 0 1 npn-2.sym
{
T 43300 42100 5 10 0 0 0 6 1
device=NPN_TRANSISTOR
T 43300 42100 5 10 1 1 0 6 1
refdes=Q3
}
C 44900 40700 1 0 1 npn-2.sym
{
T 44300 41200 5 10 0 0 0 6 1
device=NPN_TRANSISTOR
T 44300 41200 5 10 1 1 0 6 1
refdes=Q4
}
C 44900 43600 1 0 0 resistor-2.sym
{
T 45300 43950 5 10 0 0 0 0 1
device=RESISTOR
T 45100 43900 5 10 1 1 0 0 1
refdes=R18
}
C 44900 42800 1 0 0 resistor-2.sym
{
T 45300 43150 5 10 0 0 0 0 1
device=RESISTOR
T 45100 43100 5 10 1 1 0 0 1
refdes=R19
}
C 44900 42000 1 0 0 resistor-2.sym
{
T 45300 42350 5 10 0 0 0 0 1
device=RESISTOR
T 45100 42300 5 10 1 1 0 0 1
refdes=R20
}
C 44900 41100 1 0 0 resistor-2.sym
{
T 45300 41450 5 10 0 0 0 0 1
device=RESISTOR
T 45100 41400 5 10 1 1 0 0 1
refdes=R21
}
C 42800 40200 1 0 0 gnd-1.sym
C 48700 49700 1 0 0 capacitor-1.sym
{
T 48900 50400 5 10 0 0 0 0 1
device=CAPACITOR
T 48900 50200 5 10 1 1 0 0 1
refdes=C4
T 48900 50600 5 10 0 0 0 0 1
symversion=0.1
}
N 48700 49900 48600 49900 4
N 49600 49900 49700 41600 4
N 42900 40500 42900 43200 4
N 42900 43200 43400 43200 4
N 44400 42400 42900 42400 4
N 43400 41600 42900 41600 4
N 44400 40700 42900 40700 4
N 46700 43300 45800 43300 4
N 45800 43300 45800 43700 4
N 45800 42900 46700 42900 4
N 46700 42900 46700 43000 4
N 46700 42700 45800 42700 4
N 45800 42700 45800 42100 4
N 46700 42400 46300 42400 4
N 46300 42400 46300 41200 4
N 46300 41200 45800 41200 4
N 44900 42100 43900 42100 4
N 44900 43700 43900 43700 4
C 40300 41600 1 0 0 connector4-1.sym
{
T 42100 42500 5 10 0 0 0 0 1
device=CONNECTOR_4
T 40300 43000 5 10 1 1 0 0 1
refdes=CONN2
}
N 43400 44200 42000 44200 4
N 42000 44200 42000 42700 4
N 44400 43400 42300 43400 4
N 42300 43400 42300 42400 4
N 42300 42400 42000 42400 4
N 43400 42600 42600 42600 4
N 42600 42600 42600 42100 4
N 42600 42100 42000 42100 4
N 42000 41800 44400 41800 4
C 56600 42700 1 0 1 connector16-1.sym
{
T 54700 47600 5 10 0 0 0 6 1
device=CONNECTOR_16
T 56500 47800 5 10 1 1 0 6 1
refdes=CONN1
}
C 51800 47400 1 0 0 resistor-2.sym
{
T 52200 47750 5 10 0 0 0 0 1
device=RESISTOR
T 52000 47700 5 10 1 1 0 0 1
refdes=R1
}
C 53000 47100 1 0 0 resistor-2.sym
{
T 53400 47450 5 10 0 0 0 0 1
device=RESISTOR
T 53200 47400 5 10 1 1 0 0 1
refdes=R2
}
C 51800 46800 1 0 0 resistor-2.sym
{
T 52200 47150 5 10 0 0 0 0 1
device=RESISTOR
T 52000 47100 5 10 1 1 0 0 1
refdes=R3
}
C 53000 46500 1 0 0 resistor-2.sym
{
T 53400 46850 5 10 0 0 0 0 1
device=RESISTOR
T 53200 46800 5 10 1 1 0 0 1
refdes=R4
}
C 51800 46200 1 0 0 resistor-2.sym
{
T 52200 46550 5 10 0 0 0 0 1
device=RESISTOR
T 52000 46500 5 10 1 1 0 0 1
refdes=R5
}
C 53000 45900 1 0 0 resistor-2.sym
{
T 53400 46250 5 10 0 0 0 0 1
device=RESISTOR
T 53200 46200 5 10 1 1 0 0 1
refdes=R6
}
C 51800 45600 1 0 0 resistor-2.sym
{
T 52200 45950 5 10 0 0 0 0 1
device=RESISTOR
T 52000 45900 5 10 1 1 0 0 1
refdes=R7
}
C 53000 45300 1 0 0 resistor-2.sym
{
T 53400 45650 5 10 0 0 0 0 1
device=RESISTOR
T 53200 45600 5 10 1 1 0 0 1
refdes=R8
}
C 51800 45000 1 0 0 resistor-2.sym
{
T 52200 45350 5 10 0 0 0 0 1
device=RESISTOR
T 52000 45300 5 10 1 1 0 0 1
refdes=R9
}
C 53000 44700 1 0 0 resistor-2.sym
{
T 53400 45050 5 10 0 0 0 0 1
device=RESISTOR
T 53200 45000 5 10 1 1 0 0 1
refdes=R10
}
C 51800 44400 1 0 0 resistor-2.sym
{
T 52200 44750 5 10 0 0 0 0 1
device=RESISTOR
T 52000 44700 5 10 1 1 0 0 1
refdes=R11
}
C 53000 44100 1 0 0 resistor-2.sym
{
T 53400 44450 5 10 0 0 0 0 1
device=RESISTOR
T 53200 44400 5 10 1 1 0 0 1
refdes=R12
}
C 51800 43800 1 0 0 resistor-2.sym
{
T 52200 44150 5 10 0 0 0 0 1
device=RESISTOR
T 52000 44100 5 10 1 1 0 0 1
refdes=R13
}
C 53000 43500 1 0 0 resistor-2.sym
{
T 53400 43850 5 10 0 0 0 0 1
device=RESISTOR
T 53200 43800 5 10 1 1 0 0 1
refdes=R14
}
C 51800 43200 1 0 0 resistor-2.sym
{
T 52200 43550 5 10 0 0 0 0 1
device=RESISTOR
T 52000 43500 5 10 1 1 0 0 1
refdes=R15
}
C 53000 42900 1 0 0 resistor-2.sym
{
T 53400 43250 5 10 0 0 0 0 1
device=RESISTOR
T 53200 43200 5 10 1 1 0 0 1
refdes=R16
}
N 50400 47500 51800 47500 4
N 52700 47500 54800 47500 4
N 53000 47200 50400 47200 4
N 53900 47200 54800 47200 4
N 50400 46900 51800 46900 4
N 52700 46900 54800 46900 4
N 50400 46600 53000 46600 4
N 53900 46600 54800 46600 4
N 54800 46300 52700 46300 4
N 51800 46300 50400 46300 4
N 50400 46000 53000 46000 4
N 53900 46000 54800 46000 4
N 54800 45700 52700 45700 4
N 51800 45700 50400 45700 4
N 50400 45400 53000 45400 4
N 53900 45400 54800 45400 4
N 54800 45100 52700 45100 4
N 54800 44800 53900 44800 4
N 54800 44200 53900 44200 4
N 54800 43600 53900 43600 4
N 54800 43000 53900 43000 4
C 40600 48800 1 0 0 5V-plus-1.sym
C 40700 47200 1 0 0 gnd-1.sym
C 41000 47700 1 90 0 capacitor-1.sym
{
T 40300 47900 5 10 0 0 90 0 1
device=CAPACITOR
T 40500 48100 5 10 1 1 180 0 1
refdes=C3
T 40100 47900 5 10 0 0 90 0 1
symversion=0.1
}
N 40800 48800 40800 48600 4
N 40800 47700 40800 47500 4
T 50400 40100 9 10 1 0 0 0 1
1
T 51900 40100 9 10 1 0 0 0 1
1
T 50000 40400 9 10 1 0 0 0 1
led-cube-4x4x4.sch
T 53900 40100 9 10 1 0 0 0 1
J. Bromley
T 53900 40400 9 10 1 0 0 0 1
1
N 52700 44500 54800 44500 4
N 52700 43900 54800 43900 4
N 52700 43300 54800 43300 4
N 51800 45100 50400 45100 4
N 50400 45100 50400 44600 4
N 53000 44800 50600 44800 4
N 50600 44800 50600 44300 4
N 50600 44300 50400 44300 4
N 51800 44500 50800 44500 4
N 50800 44000 50800 44500 4
N 50800 44000 50400 44000 4
N 53000 44200 51000 44200 4
N 51000 44200 51000 43700 4
N 51000 43700 50400 43700 4
N 51800 43900 51200 43900 4
N 51200 43900 51200 43400 4
N 51200 43400 50400 43400 4
N 53000 43600 51400 43600 4
N 51400 43600 51400 43100 4
N 51400 43100 50400 43100 4
N 51800 43300 51600 43300 4
N 51600 43300 51600 42800 4
N 51600 42800 50400 42800 4
N 53000 43000 51800 43000 4
N 51800 43000 51800 42500 4
N 51800 42500 50400 42500 4
N 51100 48200 51100 48100 4
N 51100 48100 50400 48100 4
C 51200 47800 1 0 1 gnd-1.sym
N 50400 48400 50700 48400 4
N 50700 48400 50700 49100 4
N 50700 49100 51100 49100 4
N 48500 41600 49700 41600 4
C 54900 50100 1 0 0 switch-spst-1.sym
{
T 55300 50800 5 10 0 0 0 0 1
device=SPST
T 55200 50400 5 10 1 1 0 0 1
refdes=S3
}
N 56000 50100 55700 50100 4
N 54100 50100 54900 50100 4
N 44400 41800 44400 41700 4
