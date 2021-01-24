program.exe: A_graphs_percolation_nodes_edges.cc
	g++ -o program.exe A_graphs_percolation_nodes_edges.cc

clean:
	rm -f *.exe