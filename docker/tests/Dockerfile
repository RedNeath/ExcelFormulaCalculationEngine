FROM ubuntu:latest
LABEL authors="redneath"

RUN apt-get update &&\
    apt-get install build-essential -y &&\
    mkdir -p /home/ubuntu/ExcelFormulaCalculationEngine/bin

WORKDIR /home/ubuntu/ExcelFormulaCalculationEngine

ENTRYPOINT ["./test/exec.sh"]
