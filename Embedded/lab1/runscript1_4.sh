#!/bin/bash
if [ -f "out" ]; then
   rm out
fi

if [ -f "temp" ]; then
   rm temp
fi

for ((b=1; b <=16; b=2*b))
do
    echo "For block size = $b the timings are:"
    for ((i=1; i <= 10; i++))
    do
        exe="~/Embedded/lab_material/1/phods4 $b >> out"
        /bin/bash -c "$exe"
    done
    /bin/bash -c "python3 calc.py out"
    echo
done

/bin/bash -c "python3 best.py temp case4"