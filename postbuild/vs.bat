@echo off
xcopy ..\\Resources ..\\build\\Resources /e /i /h /v /y
xcopy ..\\Resources ..\\bin\\Debug\\Resources /e /i /h /v /y
xcopy ..\\Resources ..\\bin\\Release\\Resources /e /i /h /v /y
copy ..\\external\\lib\\vs2010\\sfml-system-d-2.dll ..\\bin\\Debug\\sfml-system-d-2.dll /y /v
copy ..\\external\\lib\\vs2010\\sfml-window-d-2.dll ..\\bin\\Debug\\sfml-window-d-2.dll /y /v
copy ..\\external\\lib\\vs2010\\sfml-system-2.dll ..\\bin\\Release\\sfml-system-2.dll /y /v
copy ..\\external\\lib\\vs2010\\sfml-window-2.dll ..\\bin\\Release\\sfml-window-2.dll /y /v
exit %errorlevel%
