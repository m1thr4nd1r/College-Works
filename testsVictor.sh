cd trabalho1/Victor

CMD="sh test.sh"
$CMD
RESULT=$?
if [ $RESULT -ne 0 ]; then
	return 1
fi
return 0