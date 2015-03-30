#! /bin/bash

gcc -g lexico.c sintatico.c semantico.c
flag=true

#input="Entradas/sample3.in"

echo "Testando..."

for input in `ls Entradas/*.in`
do
	name=`basename ${input} .in`
	out="Saidas/${name}.out"
	saida="./${name}.sol"

	memcheck=`valgrind -q --error-exitcode=1 ./a.out ${input}` 
	res=$?
	if [ $res -ne 0 ]; then
		echo $memcheck "\n"
	else
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
			out="Saidas/${name}V.out"
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
	fi

done

echo "\nFim do Teste"

if [ $flag ]; then
	return 1
else
	return 0
fi