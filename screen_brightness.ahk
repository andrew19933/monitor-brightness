; This is script that allows me to increase monitor brightness using keyboard shortcuts.
; My hope is to be able to call the functions I built in moniBrightness.cpp (DLL, rather),
; but I haven't been able to get that to work for some reason.
;
; Written by Andrew Ballin -- April 2021

#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
#Warn  ; Enable warnings to assist with detecting common errors.
#SingleInstance Force
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.


; decreases monitor brightness
; CRTL + ALT + [
^![::
Run, "C:\Users\Andrew Ballin\Programming Projects\monitor brightness\decMoniBrightness.exe",, Hide
return

; increases monitor brightness
; CRTL + ALT + ]
^!]::
Run, "C:\Users\Andrew Ballin\Programming Projects\monitor brightness\incMoniBrightness.exe",, Hide
return


; TODO:
; -- get DLL call working (see 'Error Handling' and 'Performance' sections of https://www.autohotkey.com/docs/commands/DllCall.htm)
; ---- there is some VS command to generate a DLL
; ---- might be faster to just keep it like it is
; -- make little window quickly display the new brightness then close
; ---- would need to get DLL thing working so I can get out the new brightness
; ---- see sleep_hotkey for an example of creating a window