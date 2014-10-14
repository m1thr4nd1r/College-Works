#! /bin/bash

gcc -g lexico.c

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
		fi
	else
		out="../Saidas/${name}V.out"
		diff=`diff -N ${saida} ${out}`
		res=$?
		# echo $out $saida $diff
		if [ -e $out ] && [ $res -ne 0 ]; then
			echo $name "\n" $diff
		fi
	fi
done