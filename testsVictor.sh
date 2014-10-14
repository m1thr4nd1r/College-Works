CMD="cd trabalho1/Victor && sh test.sh"
RESULT=$?
if [ $RESULT -ne 0 ]; then
	return 1
fi
return 0