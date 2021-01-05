#!/bin/bash
if [ -f "out" ]; then
   rm out
fi

if [ -f "temp" ]; then
   rm temp
fi

bx=(1 2 3 4 6 8 9 12 16 18 24 36 48 72 144)
by=(1 2 4 8 11 16 22 44 88 176)

for i in "${bx[@]}"
do
    for j in "${by[@]}"
    do
        echo "The block size is $i x $j "
        for ((k=1; k <= 50; k++))
        do
            exe="~/Embedded/lab_material/1/phods5 $i $j >> out"
            /bin/bash -c "$exe"
        done
        /bin/bash -c "python3 calc.py out"
        echo
    done
done

/bin/bash -c "python best.py temp case5"