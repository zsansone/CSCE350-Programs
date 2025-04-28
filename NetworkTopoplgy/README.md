CSCE350 Zachary Sansone

To use the network topology checker, put an adjacency matrix consiting of 0s and 1s in the input.txt. At the bottom of this readme are 4 test matricies (mesh, star, ring and none respectively) but any will work. Ensure that there are no extra lines after the matrix or there will be a segmentation fault. 

Run the program with ./run.sh which will automatically display the output text in the terminal. You can also open the output.txt file to read the output.

If there are permission erros, run chmod +x run.sh and then rerun the bash script. 

0 1 1 1 1
1 0 1 1 1
1 1 0 1 1
1 1 1 0 1
1 1 1 1 0

0 1 0 0 0
1 0 1 1 1
0 1 0 0 0
0 1 0 0 0
0 1 0 0 0

0 1 0 0 1
1 0 1 0 0
0 1 0 1 0
0 0 1 0 1
1 0 0 1 0

0 1 0 1 0
1 0 0 0 0
0 0 0 1 1
1 0 1 0 0
0 0 1 0 0
