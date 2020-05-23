#!/bin/bash

s1="how"
s2="How"
test $s1 = $s2
echo $?

test $s1 != $s2
echo $?
