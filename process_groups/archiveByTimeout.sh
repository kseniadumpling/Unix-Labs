name=$1
path=$2
timeout=$3
counter=0

while [ ${timeout} -gt 1 ]
do
    tar -czf "${path}/${name}${counter}".tar.gz ${name}
    let counter++
    sleep ${timeout}
done