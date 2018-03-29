
all:
	@cd lib/ && make libScheduler.so
	@cd src/ && make ../bin/main_d	
	@echo
	@echo con biblioteca dinamica 
	@cd bin/ && ./main_d