## purpose

changes the `SndVol.exe` (Windows Volume Mixer) window from a dialog to a regular window. makes it resizable and minimizable by changing its `GWL_STYLE` and overriding its `WindowProc`


## build

build with

	Build.Release.bat

## output files

the project produce `SndVol.exe` and `SndVolEx.dll`

this project's `SndVol.exe` runs Windows' `SndVol.exe` and loads `SndVolEx.dll` in it that changes the window


## arguments

the app accept these arguments

keep loader window open to allow pinning to taskbar

	SndVol --wait