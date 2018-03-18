rm fresults/truedensities.txt
cat densities.txt | parallel --verbose ./runone.sh 

python3 analysis.py fresults/truedensities.txt > fins.txt

