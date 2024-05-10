#!/bin/bash
gcc -Wall -shared -o lib/libefce.so -fPIC src/efce.c >> log/error-report.log && \
  gcc -Wall -L/home/ubuntu/ExcelFormulaCalculationEngine/lib -o bin/tests test/tests.c -lmunit -lefce >> log/error-report.log && \
  ./bin/tests | tee log/test-report.log
