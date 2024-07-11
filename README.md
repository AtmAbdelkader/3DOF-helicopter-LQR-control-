# Introduction


The scope of this simple project is the development of a mathematical model and control system for the three-degree-of-freedom (3-DOF) helicopter. This system provides a good simplification of a real-world tandem helicopter for evaluating the performance of various automated control principles. A mathematical model of the system has been developed. This mathematical model is linearized and the LQR controller is developed. Then they are implemented on the model and evaluated for their performance.

## SYSTEM_DESCRIPTION AND ARDUINO(MEGA) WIRING

1/ system description:

<p align="center">
    <img width=80% src="https://github.com/AtmAbdelkader/3DOF-helicopter-LQR-control-/blob/main/system_description.png">
</p>


2/ Arduino wiring:

<p align="center">
    <img width=80% src="https://github.com/AtmAbdelkader/3DOF-helicopter-LQR-control-/blob/main/arduino_wiring.png">
</p>


### MATLAB TEST
you can find all codes of MATLAB/Simulink in the official web_site of QUANSER : "https://www.quanser.com/"


---> closed_loop test:



1-> test_pitch:

<p align="center">
    <img width=80% src="https://github.com/AtmAbdelkader/3DOF-helicopter-LQR-control-/blob/main/test_LQR_pitch.png">
</p>

2-> test_roll:

<p align="center">
    <img width=80% src="https://github.com/AtmAbdelkader/3DOF-helicopter-LQR-control-/blob/main/test_LQR_roll.png">
=</p>

3-> test_yaw:

<p align="center">
    <img width=80% src="https://github.com/AtmAbdelkader/3DOF-helicopter-LQR-control-/blob/main/test_LQR_yaw.png">
</p>
