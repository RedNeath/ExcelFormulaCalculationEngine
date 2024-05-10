wd != pwd

all:
	docker build -t excel-formula-calculation-engine ./docker/build
	docker run -d --rm \
		-v $(wd):/home/ubuntu/ExcelFormulaCalculationEngine \
		excel-formula-calculation-engine

tests:
	docker build -t excel-formula-calculation-engine ./docker/tests
	docker run -d --rm \
		-v $(wd):/home/ubuntu/ExcelFormulaCalculationEngine \
		excel-formula-calculation-engine

install:
	echo "Don't forget to run this command as a superuser!"
	docker build -t excel-formula-calculation-engine ./docker/build
	docker run excel-formula-calculation-engine
	rm /usr/local/lib/libefce.so -f
	cp bin/libefce.so /usr/local/lib/
	ldconfig # Updating the linker
