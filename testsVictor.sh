CMD="cd trabalho1/Victor && sh test.sh"
RESULT=$?
if [ $RESULT -ne 0 ]; then
	exit 1
fi
exit 0