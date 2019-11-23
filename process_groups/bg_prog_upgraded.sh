# Run nohup COMMAND, ignoring hangup signals.
# This code just wait for one line in fg and after that literally does nothing
while [ true ] 
do
    if [[ $(ps -o stat= -p $$) =~ "+" ]] # check man ps
        then
            echo "Running in foreground. Please, say smth:"
            read
            if [ $? = 0 ] # if reading was successful
                then 
                    echo "Wow you've said smth!"
                    break

            fi
        else 
            echo "Running in background..."
            sleep 3
    fi
done
while :
do 
    echo "ok i'm done"
    sleep 3
done
