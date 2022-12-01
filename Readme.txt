Instruction for running graph.cpp

1. Compile graph.cpp (Command : g++ graph.cpp -o graph )
2. Add the queries in test.txt
    First Line : V X 
    NEXT X lines can be of three types
        1. add a b (add edge from a to b)
        2. rem a b (remove an edge from a to b)
        3. check a b (check if a, b edge is connected)
3. run the graph file
4. The output is printed in graph_output.txt
5. The output contains output yes/no for query output for check a b. 
6. If DEBUG in graph is set to 1, the Tree edges and non Tree edges at all level are printed.

How we checked for correctness and time analysis of the algorithm?
1. Using generateTest.py, we generate a graph of number of vertices and generate large queries of  add , remove and check queries.
2. We run the brute.cpp and graph.cpp and the output brute_output.txt and graph_output.txt 
2. Using run.sh, we do 100 such iterations.
3. we check the correctness of the algorithm , we run checker.py which checks the output by brute_output.txt and graph_output.txt
4. For time analysis, we created the graph of time vs number of vertices in the graph.