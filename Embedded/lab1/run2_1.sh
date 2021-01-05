#!/bin/bash
if [ -f "out" ]; then
   rm out
fi

exe="~/Embedded/Lab1/LAB1/tables1 >> out"   #change with your path

for ((i=1; i <= 10; i++))
do
    /bin/bash -c "$exe"
done

/bin/bash -c "python3 calc.py out"