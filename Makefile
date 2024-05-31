wd != pwd

all:
	mkdir -p bin
	docker build -t excel-formula-calculation-engine ./docker/build
	docker run -d --rm \
		-v $(wd):/home/ubuntu/ExcelFormulaCalculationEngine \
		excel-formula-calculation-engine

tests:
	mkdir -p bin
	chmod a+x ./test/exec.sh
	if [ ! -d ./log ]; then mkdir log; touch ./log/error-report.log; fi
	docker build -t excel-formula-calculation-engine-tests ./docker/tests
	-docker stop efce_test
	-docker rm efce_test
	docker run -d --name efce_test \
		-v $(wd):/home/ubuntu/ExcelFormulaCalculationEngine \
		excel-formula-calculation-engine-tests
	docker logs -f efce_test

install: all
	echo "Don't forget to run this command as a superuser!"
	echo "Waiting for the compilation to end... If the process fails, try to edit the Makefile by increasing the \
waiting time"
	sleep 10
	rm /usr/local/lib/libefce.so -f
	cp bin/libefce.so /usr/local/lib/
	ldconfig # Updating the linker
