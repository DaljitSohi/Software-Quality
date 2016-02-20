#!/bin/bash

make compile
for i in $(echo {1..1000});
do
	make login2
done
