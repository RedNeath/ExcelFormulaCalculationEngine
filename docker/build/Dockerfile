FROM ubuntu:latest
LABEL authors="redneath"

RUN apt-get update &&\
    apt-get install build-essential -y &&\
    mkdir -p /home/ubuntu/ExcelFormulaCalculationEngine/bin

WORKDIR /home/ubuntu/ExcelFormulaCalculationEngine

ENTRYPOINT ["gcc"]
CMD ["-Wall", "-shared", "-o", "bin/libefce.so", "-fPIC", "src/efce.c", "src/context.c", "src/parser.c", "src/functions/functions_facade.c"]
