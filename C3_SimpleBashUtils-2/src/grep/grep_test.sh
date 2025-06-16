#!/bin/bash

SUCCESS=0
FAILED=0

echo "1: find 'i' without flags"
./s21_grep i ../common/test.txt > file1
grep i ../common/test.txt > file2
out="$(diff -s file1 file2)"
if [ "Files file1 and file2 are identical" == "$out" ]; then
    echo "success"
    (( SUCCESS++ ))
else
    echo "failed"
    (( FAILED++ ))
fi

i=2
for pattern in "my" "i" "l"
do
    for var in -i -v -c -l -n -h -s -o
    do
        echo "$i: test with flag $var and pattern $pattern"
        ./s21_grep $var $pattern ../common/test.txt > file1
        grep $var $pattern ../common/test.txt > file2
        out="$(diff -s file1 file2)"
        if [ "Files file1 and file2 are identical" == "$out" ]; then
            echo "success"
            (( SUCCESS++ ))
        else
            echo "failed"
            (( FAILED++ ))
        fi
        (( i++ ))
    done
done

echo "Testing with non-existing files"
echo "$i: test grep -n i ../common/tests.txt"
./s21_grep -n i ../common/tests.txt
grep -n i ../common/tests.txt
(( i++ ))

echo "Testing with empty files"
echo "$i: test grep -n i ../common/empty.txt"
./s21_grep -n i ../common/empty.txt > file1
grep -n i ../common/empty.txt > file2
out="$(diff -s file1 file2)"
if [ "Files file1 and file2 are identical" == "$out" ]; then
    echo "success"
    (( SUCCESS++ ))
else
    echo "failed"
    (( FAILED++ ))
fi
(( i++ ))

echo "Testing flags squezzed combinations..."
pattern="my"
for var in -iv -in -ic -lnh -nvi
do
    echo "$i: test with $var"
    ./s21_grep $var $pattern ../common/test.txt > file1
    grep $var $pattern ../common/test.txt > file2
    out="$(diff -s file1 file2)"
    if [ "Files file1 and file2 are identical" == "$out" ]; then
        echo "success"
        (( SUCCESS++ ))
    else
        echo "failed"
        (( FAILED++ ))
    fi
    (( i++ ))
done

filenames="../common/test.txt ../common/test2.txt"
flag_e="-ei"
flag_double_e="-etest -el"
flag_f="-f ../common/test2.txt"

echo "Testing flags e with 2 files..."

for var in $flag_e $flag_double_e
do
    echo "$i: test with $var"
    ./s21_grep $var $filenames > file1
    grep $var $filenames > file2
    out="$(diff -s file1 file2)"
    if [ "Files file1 and file2 are identical" == "$out" ]; then
        echo "success"
        (( SUCCESS++ ))
    else
        echo "failed"
        (( FAILED++ ))
    fi
    (( i++ ))
done

echo "$i: test flag -f"
./s21_grep -f ../common/test2.txt $filenames > file1
grep -f ../common/test2.txt $filenames > file2
out="$(diff -s file1 file2)"
if [ "Files file1 and file2 are identical" == "$out" ]; then
    echo "success"
    (( SUCCESS++ ))
else
    echo "failed"
    (( FAILED++ ))
fi

echo
echo "Testing all pair combinatios..."
for var1 in   -i -v -c -l -n -h -s
do
   for var2 in  -i -v -c -l -n -h -s
   do
       if [ $var1 != $var2 ]
       then
           LAST_TEST="-e i -e lol -e t $var1 $var2 ../common/test.txt "
           echo "./s21_grep $LAST_TEST"
           ./s21_grep $LAST_TEST > file1
           grep $LAST_TEST > file2
           out="$(diff -s file1 file2)"
           if [ "Files file1 and file2 are identical" == "$out" ]
               then
                   (( SUCCESS++ ))
               else
                   echo "./s21_grep $LAST_TEST failed\n"
                   (( FAILED++ ))
               fi
       fi
   done
done

echo "-------------"
echo "SUCCESSED: $SUCCESS"
echo "FAILED: $FAILED"

rm file1 file2