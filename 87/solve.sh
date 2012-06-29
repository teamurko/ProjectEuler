#!/bin/bash -e

ghc solution.hs
echo 'Runnning solution ...'
./solution | sed 's/,/ /g' | sed 's/\[//g' | sed 's/\]//g' | tr ' ' '\n' | sort | uniq | wc -l
rm solution solution.hi solution.o
