#!/bin/bash
gcc -Wall -c -fPIC src/*.c >> log/error-report.log && \
  ar rcs lib/libefce.a *.o && \
  rm *.o && \
  gcc -Wall -L/home/ubuntu/ExcelFormulaCalculationEngine/lib -o bin/tests test/tests.c -lmunit -lefce >> log/error-report.log && \
  ./bin/tests | tee log/test-report.log
