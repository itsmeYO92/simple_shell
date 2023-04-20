#!/bin/bash

echo "TESTS"
echo "________ simple command__________"
echo "__bash__"
ls
echo "__simple shell__"
echo ls | ./a.out
echo exit | ./a.out
echo "__bash__"
/bin/ls
echo "__simple shell__"
echo "/bin/ls" | ./a.out
echo exit | ./a.out
