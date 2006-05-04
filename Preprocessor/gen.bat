cd D:\My_Documents\EclipseWrkSpc\Preprocessor


attrib interpreter-3.c -r 
rm  interpreter-3.c 

gcc -E -P  -ointerpreter-1.c.  interpreter.c 

 sed  -e 's/;/;\n/g' interpreter-1.c  > interpreter-2.c
 sed  -e 's/:/:\n/g' interpreter-2.c  > interpreter-2.5.c

echo #include"interpereter.h" > interpreter-3.c

cat interpreter-2.5.c >> interpreter-3.c

attrib interpreter-3.c +r 

rm  interpreter-1.c
rm  interpreter-2.c
rm interpreter-2.5.c

