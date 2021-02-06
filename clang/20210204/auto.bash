for loop in $(ls program);do
	gcc -o out/${loop%.*} program/${loop}
done
