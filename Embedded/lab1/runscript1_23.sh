#!/bin/bash
if [ -f "out" ]; then
   rm out
fi

exe="~/Embedded/lab_material/1/phods3 >> out"

for ((i=1; i <= 100; i++))
do
    /bin/bash -c "$exe"
done

/bin/bash -c "python3 calc.py out"