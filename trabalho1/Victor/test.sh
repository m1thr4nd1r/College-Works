#! /bin/bash

gcc -g lexico.c
flag=true

#input="../Entradas/sample3.in"

for input in `ls ../Entradas/*.in`
do
	name=`basename ${input} .in`
	out="../Saidas/${name}.out"
	saida="./${name}.sol"

	$(./a.out ${input} > ${saida})	

	if [ -e $out ]; then
		diff=`diff ${saida} ${out}`
		#${diff}
		res=$?
		if [ $res -ne 0 ]; then
			echo $name "\n" $diff
			flag=false
		else
			$(rm ${saida})
		fi
	else
		out="../Saidas/${name}V.out"
		diff=`diff -N ${saida} ${out}`
		res=$?
		# echo $out $saida $diff
		if [ -e $out ] && [ $res -ne 0 ]; then
			echo $name "\n" $diff
			flag=false
		else
			$(rm ${saida})
		fi
	fi
done

if [ $flag ]; then
	return 1
else
	return 0
fi