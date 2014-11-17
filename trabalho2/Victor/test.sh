#! /bin/bash

gcc -g lexico.c
flag=true

#input="../Entradas/sample3.in"

echo "Testando..."

for input in `ls ../../trabalho1/Entradas/*.in`
do
	name=`basename ${input} .in`
	out="../../trabalho1/Saidas/${name}.out"
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
		out="../../trabalho1/Saidas/${name}V.out"
		diff=`diff -N ${saida} ${out}`
		res=$?
		# echo $out $saida $diff
		if [ -e $out ]; then
			if [ $res -ne 0 ]; then
				echo $name "\n" $diff
				flag=false
			else
				$(rm ${saida})
			fi
		else
			$(mv ${saida} ${out})
		fi
	fi
done

for input in `ls ../Entradas/*.in`
do
	name=`basename ${input} .in`
	out="../Saidas/${name}.out"
	saida="./${name}.sol"

	echo $name : $(./a.out ${input})	
done

echo "\nFim do Teste"

if [ $flag ]; then
	return 1
else
	return 0
fi