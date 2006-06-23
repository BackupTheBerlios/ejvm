 
cd  /root/Desktop/EclipseWrkSpc/linux\-interpreter\-final/
chmod  u=+r interpreter-better.cpp

#rm  interpreter-better.cpp

#gcc -E -P -CC -ointerpreter-1.cpp  interpreter.cpp
gcc -E -P  -ointerpreter-1.cpp  interpreter.cpp

sed  -e 's/;/;\n/g' interpreter-1.cpp  > interpreter-2.cpp
#sed  -e 's/: /:\n/g' interpreter-2.cpp  > interpreter-3.cpp
 
echo \#include\"ejvm.h\" > interpreter-better.cpp 
echo \#include\"log.h\" >> interpreter-better.cpp 
 
 
cat interpreter-2.cpp >> interpreter-better.cpp 
 
chmod  u=+r interpreter-better.cpp 
 
rm interpreter-1.cpp interpreter-2.cpp ##interpreter-3.cpp 
 
