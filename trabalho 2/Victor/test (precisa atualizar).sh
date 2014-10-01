gcc -g lexico.c
./a.out sample1.in > sample1.sol
./a.out sample2.in > sample2.sol
./a.out sample3.in > sample3.sol
./a.out sample4.in > sample4.sol
./a.out sample5.in > sample5.sol
./a.out sample6.in > sample6.sol
./a.out sample7.in > sample7.sol
./a.out sample8.in > sample8.sol
./a.out sample9.in > sample9.sol
./a.out sample10.in > sample10.sol
./a.out samples.in > samples.sol
./a.out strings.in > strings.sol
./a.out char.in > char.sol
./a.out numbers.in > numbers.sol
./a.out separators.in > separators.sol
./a.out test.in > test.sol
./a.out maximos.in > maximos.sol
./a.out sala.in > sala.sol
./a.out sala2.in > sala2.sol
./a.out sala3.in > sala3.sol
./a.out sala4.in > sala4.sol
./a.out sala5.in > sala5.sol
echo "Sample 1"
diff sample1.sol sample1.out
echo "Sample 2"
diff sample2.sol sample2.out
echo "Sample 3"
diff sample3.sol sample3.out
echo "Sample 4"
diff sample4.sol sample4.out
echo "Sample 5"
diff sample5.sol sample5.out
echo "Sample 6"
diff sample6.sol sample6.out
echo "Sample 7"
diff sample7.sol sample7.out
echo "Sample 8"
diff sample8.sol sample8.out
echo "Sample 9"
diff sample9.sol sample9.out
echo "Sample 10"
diff sample10.sol sample10.out
echo "Samples"
diff samples.sol samples.out
echo "Strings"
diff strings.sol strings.out
echo "Numbers"
diff numbers.sol numbers.out
echo "Char"
diff char.sol char.out
echo "Separators"
diff separators.sol separators.out
echo "Teste"
diff test.sol test.out
echo "Maximos"
diff maximos.sol maximos.out
echo "Sala"
diff sala.sol sala.out
echo "Sala 2"
diff sala2.sol sala2.out
echo "Sala 3"
diff sala3.sol sala3.out
echo "Sala 4"
diff sala4.sol sala4.out
echo "Sala 5"
diff sala5.sol sala5.out