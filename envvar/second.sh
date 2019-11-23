var1=`expr 1 + 2`
echo "adding: 1+2 by expr. Result: $var1"

let var2=2*2
echo "multiplying: 2*2 by let. Result: $var2"

var3=$((8-6))
echo "substracting: 8-6 by double brackets. Result: $var3"

var4="scale=2; 5/4"
echo "dividing: 5/4 using bc. Result"
echo $var4 | bc

var5=$((2+2*2))
echo "calculate expression: 2+2*2 by double brackets. Result: $var5 "



