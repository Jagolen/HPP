# Script for checking format of A1.tar.gz file for Assignment 1 subimssion

# Remove old tmpdir_for_checking if it exists
rm -rf tmpdir_for_checking

echo Creating temporary directory tmpdir_for_checking

# Create new tmpdir_for_checking directory
mkdir tmpdir_for_checking || exit 1

echo Copying A1.tar.gz file into tmpdir_for_checking directory

# Copy the .tar.gz file into the tmpdir_for_checking directory
cp A1.tar.gz tmpdir_for_checking || exit 1

# cd into the tmpdir_for_checking directory
cd tmpdir_for_checking || exit 1

echo Unpacking the A1.tar.gz file
tar -xzf A1.tar.gz || exit 1

echo Doing cd into A1 directory
cd A1 || exit 1

echo Doing cd into part1 directory
cd part1 || exit 1

echo Checking that Makefile is available in part1 directory
ls Makefile || exit 1

cd .. || exit 1

echo Doing cd into part2 directory
cd part2 || exit 1

echo Checking that Makefile is available in part2 directory
ls Makefile || exit 1

echo Checking that stuff.c is available in part2 directory
ls stuff.c || exit 1

echo Checking that stuff.h is available in part2 directory
ls stuff.h || exit 1

echo Checking that themainprog.c is available in part2 directory
ls themainprog.c || exit 1

echo Checking that there are no .o files in the part2 directory
ls *.o 2> /dev/null && exit 1

cd .. || exit 1

echo Doing cd into part3 directory
cd part3 || exit 1

echo Checking that helloscript.sh is available in part3 directory
ls helloscript.sh || exit 1

echo Checking that run-pyramid.sh is available in part3 directory
ls run-pyramid.sh || exit 1

cd .. || exit 1

echo Checking that no pyramid executable files have been included
ls */pyramid* 2> /dev/null && exit 1

echo Doing cd into part4 directory
cd part4 || exit 1

echo Checking that file_from_vitsippa.txt is available in part4 directory
ls file_from_vitsippa.txt || exit 1

# If we get to this point, then all the different tests above have passed.
echo
echo Congratulations, your A1.tar.gz file seems OK!
echo
