show_graph: montecarlo_result.csv
	python show_monte.py 13 1000000

monte_result:
	clang high_low_montecarlo.c; ./a.out;

high_low:
	clang high_low2.c; ./a.out;


