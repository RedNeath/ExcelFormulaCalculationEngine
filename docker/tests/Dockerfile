FROM ubuntu:latest
LABEL authors="redneath"

RUN apt-get update &&\
    apt-get install build-essential -y &&\
    mkdir -p /home/ubuntu/ExcelFormulaCalculationEngine/bin

WORKDIR /home/ubuntu/ExcelFormulaCalculationEngine

ENTRYPOINT ["gcc"]
CMD ["-Wall", "-shared", "-o", "lib/libefce.so", "-fPIC", "src/efce.c"]

ENTRYPOINT ["gcc"]
CMD ["-Wall", "-L/home/ubuntu/ExcelFormulaCalculationEngine/lib", "-o", "bin/tests", "tests/tests.c", "-lmunit", "-lefce", "&&", "./bin/tests"]
