for   %%i in (protofile\*.proto) do ^
.\protoc -I=.\protofile --cpp_out=..\Young\protofile %%i
pause
