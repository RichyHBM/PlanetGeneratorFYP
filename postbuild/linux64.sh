#!/bin/sh

test -d ../build || mkdir -p ../build
cp -a ../Resources ../build/Resources
test -d ../bin || mkdir -p ../bin
test -d ../bin/Debug64 || mkdir -p ../bin/Debug64
test -d ../bin/Release64 || mkdir -p ../bin/Release64
cp -a ../Resources ../bin/Debug64/Resources
cp -a ../Resources ../bin/Release64/Resources

cp ../external/lib/linux/libsfml-system64.so ../bin/Debug64/libsfml-system64.so.2
cp ../external/lib/linux/libsfml-window64.so ../bin/Debug64/libsfml-window64.so.2
cp ../external/lib/linux/libAntTweakBar64.so ../bin/Debug64/libAntTweakBar64.so.1

cp ../external/lib/linux/libsfml-system64.so ../bin/Release64/libsfml-system64.so.2
cp ../external/lib/linux/libsfml-window64.so ../bin/Release64/libsfml-window64.so.2
cp ../external/lib/linux/libAntTweakBar64.so ../bin/Release64/libAntTweakBar64.so.1

touch ../bin/Debug64/runServer.sh
echo '#!/bin/sh' > ../bin/Debug64/runServer.sh
echo 'export LD_LIBRARY_PATH=.' >> ../bin/Debug64/runServer.sh
echo 'export set DISPLAY=":0.0"' >> ../bin/Debug64/runServer.sh
echo './Server $@' >> ../bin/Debug64/runServer.sh

touch ../bin/Release64/runServer.sh
echo '#!/bin/sh' > ../bin/Release64/runServer.sh
echo 'export LD_LIBRARY_PATH=.' >> ../bin/Release64/runServer.sh
echo 'export set DISPLAY=":0.0"' >> ../bin/Release64/runServer.sh
echo './Server $@' >> ../bin/Release64/runServer.sh


