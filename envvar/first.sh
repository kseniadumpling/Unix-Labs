str1="Hello"
str2="World"
echo "str1: $str1"
echo "str2: $str2"

concatStr="${str1}${str2}"
echo "concat strings: $concatStr"

subStr=$(echo $concatStr | cut -c 2-5)
echo "substring (characters from 2 to 5): $subStr"

newStr=${concatStr/Hello/Hi}
echo "changed string: $newStr"
