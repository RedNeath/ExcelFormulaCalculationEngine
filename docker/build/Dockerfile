FROM ubuntu:latest
LABEL authors="redneath"

RUN apt-get update &&\
    apt-get install build-essential -y &&\
    mkdir /home/ubuntu/ExcelFormulaCalculationEngine

WORKDIR /home/ubuntu/ExcelFormulaCalculationEngine

ENTRYPOINT ["gcc"]
CMD ["-Wall", "-shared", "-o", "bin/libefce.so", "-fPIC", "src/efce.c"]
