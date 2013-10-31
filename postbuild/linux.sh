#!/bin/sh

test -d ../build || mkdir -p ../build
cp -a ../Resources ../build/Resources
test -d ../bin || mkdir -p ../bin
test -d ../bin/Debug || mkdir -p ../bin/Debug
test -d ../bin/Release || mkdir -p ../bin/Release
cp -a ../Resources ../bin/Debug/Resources
cp -a ../Resources ../bin/Release/Resources

cp ../external/lib/linux/libsfml-system.so ../bin/Debug/libsfml-system.so.2
cp ../external/lib/linux/libsfml-window.so ../bin/Debug/libsfml-window.so.2

cp ../external/lib/linux/libsfml-system.so ../bin/Release/libsfml-system.so.2
cp ../external/lib/linux/libsfml-window.so ../bin/Release/libsfml-window.so.2

touch ../bin/Debug/runStandalone.sh
echo '#!/bin/sh' > ../bin/Debug/runStandalone.sh
echo 'export LD_LIBRARY_PATH=.' >> ../bin/Debug/runStandalone.sh
echo './StandAlone' >> ../bin/Debug/runStandalone.sh

touch ../bin/Release/runStandalone.sh
echo '#!/bin/sh' > ../bin/Release/runStandalone.sh
echo 'export LD_LIBRARY_PATH=.' >> ../bin/Release/runStandalone.sh
echo './StandAlone' >> ../bin/Release/runStandalone.sh


