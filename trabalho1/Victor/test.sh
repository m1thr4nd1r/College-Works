gcc -g lexico.c

./a.out ../Entradas/sample1.in > sample1.sol
./a.out ../Entradas/sample2.in > sample2.sol
./a.out ../Entradas/sample3.in > sample3.sol
./a.out ../Entradas/sample4.in > sample4.sol
./a.out ../Entradas/sample5.in > sample5.sol
./a.out ../Entradas/sample6.in > sample6.sol
./a.out ../Entradas/sample7.in > sample7.sol
./a.out ../Entradas/sample8.in > sample8.sol
./a.out ../Entradas/sample9.in > sample9.sol
./a.out ../Entradas/sample10.in > sample10.sol
./a.out ../Entradas/samples.in > samples.sol
./a.out ../Entradas/strings.in > strings.sol
./a.out ../Entradas/char.in > char.sol
./a.out ../Entradas/numbers.in > numbers.sol
./a.out ../Entradas/separators.in > separators.sol
./a.out ../Entradas/test.in > test.sol
./a.out ../Entradas/maximos.in > maximos.sol
./a.out ../Entradas/sala.in > sala.sol
./a.out ../Entradas/sala2.in > sala2.sol
./a.out ../Entradas/sala3.in > sala3.sol
./a.out ../Entradas/sala4.in > sala4.sol
./a.out ../Entradas/sala5.in > sala5.sol

echo "Sample 1"
diff -N -y -q sample1.sol ../Saidas/sample1.out
echo "Sample 2"
diff -N -y -q sample2.sol ../Saidas/sample2.out
echo "Sample 3"
diff -N -y -q sample3.sol ../Saidas/sample3V.out
echo "Sample 4"
diff -N -y -q sample4.sol ../Saidas/sample4V.out
echo "Sample 5"
diff -N -y -q sample5.sol ../Saidas/sample5V.out
echo "Sample 6"
diff -N -y -q sample6.sol ../Saidas/sample6V.out
echo "Sample 7"
diff -N -y -q sample7.sol ../Saidas/sample7V.out
echo "Sample 8"
diff -N -y -q sample8.sol ../Saidas/sample8V.out
echo "Sample 9"
diff -N -y -q sample9.sol ../Saidas/sample9V.out
echo "Sample 10"
diff -N -y -q sample10.sol ../Saidas/sample10V.out
echo "Samples"
diff -N -y -q samples.sol ../Saidas/samplesV.out
echo "Strings"
diff -N -y -q strings.sol ../Saidas/stringsV.out
echo "Numbers"
diff -N -y -q numbers.sol ../Saidas/numbersV.out
echo "Char"
diff -N -y -q char.sol ../Saidas/charV.out
echo "Separators"
diff -N -y -q separators.sol ../Saidas/separatorsV.out
echo "Teste"
diff -N -y -q test.sol ../Saidas/test.out
echo "Maximos"
diff -N -y -q maximos.sol ../Saidas/maximosV.out
echo "Sala"
diff -N -y -q sala.sol ../Saidas/salaV.out
echo "Sala 2"
diff -N -y -q sala2.sol ../Saidas/sala2V.out
echo "Sala 3"
diff -N -y -q sala3.sol ../Saidas/sala3V.out
echo "Sala 4"
diff -N -y -q sala4.sol ../Saidas/sala4V.out
echo "Sala 5"
diff -N -y -q sala5.sol ../Saidas/sala5V.out