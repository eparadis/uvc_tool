# UVC camera tool

I use a Logitech C615 webcam for teleconferencing. It's a bit low-res now, but in it's day it was actually a pretty nice camera at a really good price. (I bought more than one!)
The problem is that Logitech has more or less dropped support for it despite it still working great as a plug-and-play camera on modern MacOS and Linux. This means there is no System Preferences extension or utility to control all the nifty features this camera has.
This tool is a simple command line program to let you quickly set various parameters of the camera. The most important, and the ones it'll focus on first, have to do with various exposure settings. Manual focus control is also handy to prevent focus-hunting, to use external lenses, to set a pair of cameras to the same distance for stereo vision, or to lock the focus for close-up work.

# Building

Use `build.sh` to build `config` and `example`

# Usage

Currently just running `config` will print out some diagnostic info and attempt to allow the camera to change it's frame rate to affect the exposure when using Auto Exposure.

`example` is more or less the example program from `libuvc`, the thing that makes this all possible.

# TODO

* Add a flag to enable all the debug messages instead of always printing them
* Accept a parameter on the command line of a positive or negative integer to bump the exposure up or down manually
* Expose other camera parameters like focus distance, shutter speed, contrast, brightness, background compensation, etc etc
