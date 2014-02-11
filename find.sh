# this simple script searches for a list of files (say *.c files) containing a special string as input argument recursively 
# run by "./find.sh 'special string'"
find . -type f -name "*.c" -exec grep -ls $1 {} \;
