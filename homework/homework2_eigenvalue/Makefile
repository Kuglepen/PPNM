CXX = g++
CXXFLAGS = -std=c++23 -O2 -Wall -Wextra

# BUILD
all: main

main: main.o jacobi.o matrix.o
	$(CXX) $(CXXFLAGS) $^ -o $@

main.o: main.cc matrix.h jacobi.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

jacobi.o: jacobi.cc matrix.h jacobi.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

matrix.o: matrix.cc matrix.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# CLEAN
clean:
	rm -f *.o main waves.dat *.txt *.png

# TASK 1 + 3
test:
	./main

# CONVERGENCE IN dr
convergence_dr:
	@echo "Running convergence in dr..."
	> out.dr.txt
	for dr in 0.5 0.3 0.2 0.1 0.05; do \
		echo "Running dr=$$dr"; \
		./main -rmax 20 -dr $$dr >> out.dr.txt ; \
	done
	grep RESULT out.dr.txt | sed -E 's/.*dr=([^ ]+).*E0=([^ ]+).*/\1 \2/' > data_dr.txt
	@echo "Saved cleaned data → data_dr.txt"

# CONVERGENCE IN rmax
convergence_rmax:
	@echo "Running convergence in rmax..."
	> out.rmax.txt
	for rmax in 5 10 15 20 30; do \
		echo "Running rmax=$$rmax"; \
		./main -rmax $$rmax -dr 0.1 >> out.rmax.txt ; \
	done
	grep RESULT out.rmax.txt | sed -E 's/.*rmax=([^ ]+).*E0=([^ ]+).*/\1 \2/' > data_rmax.txt
	@echo "Saved cleaned data → data_rmax.txt"

# TIMING
timing:
	@echo "Measuring scaling (using ./main built-in test)..."
	./main > out.times.txt
	# Extract only the numeric lines "nn   t" (nn starts with digits)
	grep -E '^[[:space:]]*[0-9]+' out.times.txt > data_times.txt || true
	@echo "Saved timing -> data_times.txt (numeric lines)"

# PLOTTING 
plot_dr:
	gnuplot plot_dr.gp
	@echo "Saved → fig_dr.png"

plot_rmax:
	gnuplot plot_rmax.gp
	@echo "Saved → fig_rmax.png"

plot_waves:
	gnuplot plot_waves.gp
	@echo "Saved → fig_waves.png"

plots: plot_dr plot_rmax plot_waves

