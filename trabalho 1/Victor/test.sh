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
diff sample1.sol ../Saidas/sample1.out
echo "Sample 2"
diff sample2.sol ../Saidas/sample2.out
echo "Sample 3"
diff sample3.sol ../Saidas/sample3.v
echo "Sample 4"
diff sample4.sol ../Saidas/sample4.v
echo "Sample 5"
diff sample5.sol ../Saidas/sample5.v
echo "Sample 6"
diff sample6.sol ../Saidas/sample6.v
echo "Sample 7"
diff sample7.sol ../Saidas/sample7.v
echo "Sample 8"
diff sample8.sol ../Saidas/sample8.v
echo "Sample 9"
diff sample9.sol ../Saidas/sample9.v
echo "Sample 10"
diff sample10.sol ../Saidas/sample10.v
echo "Samples"
diff samples.sol ../Saidas/samples.v
echo "Strings"
diff strings.sol ../Saidas/strings.v
echo "Numbers"
diff numbers.sol ../Saidas/numbers.v
echo "Char"
diff char.sol ../Saidas/char.v
echo "Separators"
diff separators.sol ../Saidas/separators.v
echo "Teste"
diff test.sol ../Saidas/test.out
echo "Maximos"
diff maximos.sol ../Saidas/maximos.v
echo "Sala"
diff sala.sol ../Saidas/sala.v
echo "Sala 2"
diff sala2.sol ../Saidas/sala2.v
echo "Sala 3"
diff sala3.sol ../Saidas/sala3.v
echo "Sala 4"
diff sala4.sol ../Saidas/sala4.v
echo "Sala 5"
diff sala5.sol ../Saidas/sala5.v