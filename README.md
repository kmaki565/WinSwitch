WinSwitch
====
A keyboard based window switching tool  

## Goal for the program
I often open a lot of windows and keep them open. Sometimes the taskbar is full of window icons to overflow (I usually set the taskbar to the right side of desktop, and I would see a scroll bar in the taskbar). In such a scenario, I am frustrated that I have to move mouse cursor carefully to the icons to reach desired window. I can use Alt-tab, but yet I have to carefully watch the list of windows and find the target.
This tiny program is aimed to offer a relief for such scenario, enabling to choose window(s) with fewer keyboard types.
## Works on
Windows 7 or later (tested on Windows 10)
## Installation
None. Just double click WinSwitch.exe. You may want to run as a startup program.
## Dependencies
Microsoft Visual C++ 2013 Redistributable (x86)
## Build environment
Visual Studio Professional 2013
## Program description / Usage
When launched, the exe stays in the taskbar notification area.
It registers a hotkey (Alt+F1) during startup and unregisters it upon program termination.

To show the app window, you can press Alt+F1 anytime.
In the list control, all visible windows are listed up. You can search window by pressing the beginning character(s) of the process as you may do on Explorer. Also, you can "find" by window title (caption). Press F3 to invoke a find, and find next.

After desired window is selected, you can press enter to bring the window to foreground, or press F4 to close the window.

To terminate the exe, push X button in the dialog, or choose Exit from the taskbar icon.
