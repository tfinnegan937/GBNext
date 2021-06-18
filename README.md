# GBNext

GBNext is a new Gameboy/Gameboy Color Emulator that strives to add never-before-seen texture-modification systems to the classic console.

Currently, the emulator is very early in development with only cartridge emulation, memory emulation, and the very beginnings of the CPU's
emulation completed.

Upon completion, however, I hope to create a system in which artists can design their own tiles and sprites using the full range of colors
offered by modern Windows, Linux, and MacOS screens, and map those tiles to existing tiles in a Gameboy ROM's memory. The idea is that
the equivalent of texture packs can be created for the Gameboy with features such as resolution-scaling (one pixel of a GB tile can map
to 4x as many pixels, for example) and one-to-one translations for operations between mapped pixels. 

The emulator follows a GUI-independent design philosophy. Currently, GBNext is designed to be run on a separate thread from whatever GUI
is applied, with functions allowing for the GUI wrapper to control emulation properties. Once completed, the Emulator should be platform-agnostic
and allow for the creation of various front-end interfaces. I intend to create a standard interface using Qt5 in another repository at a later
date.

This whole emulator is designed using Windows Subsystem for Linux hooked into CLion, with the latest Windows Insider Development Branch build that allows for the
display of linux GUI-applications.
