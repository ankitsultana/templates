output=$(ls -1)
for x in $output; do
    y=$(find ~/.templates -samefile $x)
    if [ -z $y ]; then
        echo $x
    fi
done
