#!/bin/bash

SUCCESS=0
FAILED=0

echo "1: test without flags"
./s21_cat ../common/test.txt > file1
cat ../common/test.txt > file2
out="$(diff -s file1 file2)"
if [ "Files file1 and file2 are identical" == "$out" ]; then
    echo "success"
    (( SUCCESS++ ))
else
    echo "failed"
    (( FAILED++ ))
fi

i=2
for var in -n -b -s -e -t
do
    echo "$i: test with $var"
    ./s21_cat $var ../common/test.txt > file1
    cat $var ../common/test.txt > file2
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

echo "Testing with non-existing files"
echo "$i: test cat -n ../common/tests.txt"
./s21_cat -n ../common/tests.txt
cat -n ../common/tests.txt
(( i++ ))

echo "$i: test with 2 flags -t -v"
./s21_cat -t -v ../common/test.txt > file1
cat -t -v ../common/test.txt > file2
out="$(diff -s file1 file2)"
if [ "Files file1 and file2 are identical" == "$out" ]; then
    echo "success"
    (( SUCCESS++ ))
else
    echo "failed"
    (( FAILED++ ))
fi
(( i++ ))

echo "$i: test with 2 flags -e -v"
./s21_cat -e -v ../common/test.txt > file1
cat -e -v ../common/test.txt > file2
out="$(diff -s file1 file2)"
if [ "Files file1 and file2 are identical" == "$out" ]; then
    echo "success"
    (( SUCCESS++ ))
else
    echo "failed"
    (( FAILED++ ))
fi
(( i++ ))

echo "$i: test with 2 files"
./s21_cat ../common/test.txt ../common/test.txt > file1
cat ../common/test.txt ../common/test.txt > file2
out="$(diff -s file1 file2)"
if [ "Files file1 and file2 are identical" == "$out" ]; then
    echo "success"
    (( SUCCESS++ ))
else
    echo "failed"
    (( FAILED++ ))
fi

echo "-------------"
echo "SUCCESSED: $SUCCESS"
echo "FAILED: $FAILED"

rm file1 file2