echo $1

if [ $1 -eq 1 ]; then
	$(tar -zcvf trabalho1.tgz trabalho1)
else 
	if [ $1 -eq 2 ]; then
		$(tar -zcvf trabalho2.tgz trabalho2)
	else
		$(tar -zcvf trabalho3.tgz trabalho3)
	fi
fi