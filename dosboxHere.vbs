Set oShell = CreateObject ("Wscript.Shell") 
Dim strArgs
strArgs = "cmd /c C:\amb_GAS\ASMBL\rsm.exe"
oShell.Run strArgs, 0, false