# save as a plot.gp
# run : gnuplot plot.gp

# Set the output file type
set terminal png


titles = "Rainbow Linas Magma GrayL GrayNL2 GrayNL3 GraySqrt Green"




# remove legend
unset key 

# remove upper and right axis
set border 3 back 
set xtics nomirror
set ytics nomirror


set xlabel "gradient position"
set ylabel "color intensity" 


set yrange [-0.1:1.1]


# https://stackoverflow.com/questions/14946530/loop-structure-inside-gnuplot
do for [n=0:7] {
	# Set the output file name
  	outfile = sprintf('%d.png',n)
  	set output outfile
  	
  	# Set the intput file name
  	infile = sprintf('%d.txt',n)

	# title of the image for the array of strings
	sTitle = sprintf(" RGB profiles of the %s colormap", word(titles,n+1) )
	set title sTitle
	# sTitle = sprintf(" RGB profiles of the %d colormap",  n) 	
	
  	
  	
	# Now plot the data with lines and points
	plot infile using 1:2 with lines linecolor rgb 'red' title 'R', \
     	'' using 1:3 w lines linecolor rgb 'green' title 'G', \
     	'' using 1:4 w lines linecolor rgb 'blue' title 'B',\
     	'' using 1:5 w lines linecolor rgb 'black' title 'Y'
	
  
}

