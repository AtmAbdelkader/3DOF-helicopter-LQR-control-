![image](https://github.com/AtmAbdelkader/3DOF-helicopter-LQR-control-/assets/128811093/8850c60c-751a-4089-8a72-4c7e5e7c30ba)# Introduction


The scope of this simple project is the development of a mathematical model and control system for the three-degree-of-freedom (3-DOF) helicopter. This system provides a good simplification of a real-world tandem helicopter for evaluating the performance of various automated control principles. A mathematical model of the system has been developed. This mathematical model is linearized and the LQR controller is developed. Then they are implemented on the model and evaluated for their performance.

## SYSTEM_DESCRIPTION AND ARUINO(MEGA) WIRING

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

1/ Open-loop test:
First we test this system on open loop and we find that this system is unstable


--> test_pitch:

<p align="center">
    <img width=80% src="https://github.com/AtmAbdelkader/3DOF-helicopter-LQR-control-/blob/main/test_pitch.png">
</p>

--> test_roll:

<p align="center">
    <img width=80% src="https://github.com/AtmAbdelkader/3DOF-helicopter-LQR-control-/blob/main/test_roll.png">
=</p>

--> test_yaw:

<p align="center">
    <img width=80% src="https://github.com/AtmAbdelkader/3DOF-helicopter-LQR-control-/blob/main/test_yaw.png">
</p>
