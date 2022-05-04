cd src 
gcc -c -g helper.c -o helper.o
ar rcs libhelper.a helper.o 
rm helper.o
mv libhelper.a ../obj
cd ..