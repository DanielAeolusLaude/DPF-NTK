# DPF - DISTRHO Plugin Framework

DPF is designed to make development of new plugins an easy and enjoyable task.<br/>
It allows developers to create plugins with custom UIs using a simple C++ API.<br/>
The framework facilitates exporting various different plugin formats from the same code-base.<br/>

DPF can build for LADSPA, DSSI, LV2 and VST formats.<br/>
A JACK/Standalone mode is also available, allowing you to quickly test plugins.<br/>

Plugin DSP and UI communication is done via key-value string pairs.<br/>
You send messages from the UI to the DSP side, which is automatically saved in the host when required.<br/>

Getting time information from the host is possible.<br/>
It uses the same format as the JACK Transport API, making porting some code easier.<br/>


This repository includes the NTK Version of DPF, allowing to use NTK to build plugin UIs instead of OpenGL.<br/>
Due to NTK limitations it's only possible to build Linux plugins at the moment.
