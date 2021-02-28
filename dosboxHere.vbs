Set oShell = CreateObject ("Wscript.Shell") 
Dim strArgs
strArgs = "cmd /c C:\amb_GAS\ASMBL\execs\rsm.exe"
oShell.Run strArgs, 0, false