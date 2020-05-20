#!/bin/bash

test $1 -eq $2
echo $?

test $1 -gt $2
echo $?

test $1 -lt $2
echo $?
