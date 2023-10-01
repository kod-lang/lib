@echo off

cd build/tests
ctest -C Debug --rerun-failed --output-on-failure
cd ..\..
