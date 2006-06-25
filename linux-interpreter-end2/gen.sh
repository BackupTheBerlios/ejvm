ls -al 
cd ..

##cd  /root/Desktop/EclipseWrkSpc/linux\-interpreter\-end2/

chmod  u=+r ExecutionEng.cpp

rm  ExecutionEng.cpp

#gcc -E -P -CC -ointerpreter-1.cpp  interpreter.cpp
gcc -E -P  -ointerpreter-1.cpp  interpreter.cpp

sed  -e 's/;/;\n/g' interpreter-1.cpp  > interpreter-2.cpp
#sed  -e 's/: /:\n/g' interpreter-2.cpp  > interpreter-3.cpp
 
echo \#include\"ejvm.h\" > ExecutionEng.cpp 
echo \#include\"log.h\" >> ExecutionEng.cpp 
 
 
cat interpreter-2.cpp >> ExecutionEng.cpp 
 
chmod  u=+r ExecutionEng.cpp 
 
rm interpreter-1.cpp interpreter-2.cpp ##interpreter-3.cpp 
 
