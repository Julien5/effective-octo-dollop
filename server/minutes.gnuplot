set terminal pngcairo size 800,400 enhanced font 'Verdana,12'
set output '{out}'
set datafile separator comma

set boxwidth 0.05
set style fill solid
set xrange [0:24]
set yrange [0:100]
set grid
set title "{date}"
unset key

set label 1 at  10, 90 '{ntours} tours'
set label 2 at  10, 80 '{nminutes} minutes'

plot "{in}" using ($1/60):($2) with boxes