set datafile separator ","
set terminal png size 800,600
set output 'comparison_graph_SRN.png'
set title "Comparison between Horsepool and BoyerMoore"
set xlabel "Text Length"
set ylabel "Number of Comparisons"
set grid
plot "horspool_values_SRN.txt" using 2:3 with linespoints title "Horspool", \
     "boyermoore_values_SRN.txt" using 2:3 with linespoints title "Boyer-Moore"
