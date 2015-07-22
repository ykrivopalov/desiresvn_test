For makefiles or visual studio project files generation run `cmake ..`.

If cmake couldn't find Qt then specify qt path in parameters.
Ex.: `cmake -DCMAKE_PREFIX_PATH="C:\Qt\5.5\msvc2012" ..`

Qt binaries must be in system path before app execution.
Ex.:
```
set PATH=%PATH%;C:\Qt\5.5\msvc2012\bin
gui\Release\integrator_gui.exe
```
