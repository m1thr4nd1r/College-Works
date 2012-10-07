;	Universidade Federal da Bahia
;	Departamento de Ciência da Computação
;
;	Disciplina:	MAT149 Linguagens de montagem
;	Alunos: 	Anna Luiza e Victor Santos
;	Professor:	Luiz Eduardo
;
;	Grava coordenadas geográficas
;
;	30 de Junho de 2012
;
;	tasm  GeoGrav /z
;	tlink GeoGrav+DateTime+ScreKeyb+IntNum+FileDisk /3

INCLUDE	XCall.mac
INCLUDE	Macros.mac

.MODEL SMALL
.386
DOSSEG
.STACK	256
.DATA

					DD	12 DUP (?)

cabecalho			DB	'Universidade Federal da Bahia'
					DB	30 DUP (' ')
cabDay				DB	2  DUP ('0')
					DB	'/'
cabMonth			DB	2  DUP ('0')
					DB	'/'
cabYear				DB	4  DUP ('0')
					DB	'  '
cabHours			DB	2  DUP ('0')
					DB	':'
cabMinutes			DB	2  DUP ('0')
					DB	':'
cabSeconds			DB	2  DUP ('0')
					DB	10,13
					DB	'Departamento de Ciencia da Computacao',10,13
					DB	'MATA49 Programacao de software basico',10,10,13
					DB	'Gravacao de coordenadas geograficas',10,13
tamCabecalho		EQU	$-cabecalho
msgInicial			DB	10,13,'Arquivo de coordenadas ou <ENTER> para abandonar: '
tamInicial			EQU $-msgInicial
pedeLocal			DB	10,13,'Nome da localidade                              : '
tamPedeLocal		EQU	$-pedeLocal
pedeLatitude		DB	'Latitude (graus,minutos, orientacao)            : '
tamPedeLatitude		EQU	$-pedeLatitude
pedeLongitude		DB	'Longitute (graus, minutos, orientacao)          : '
tamPedeLongitude	EQU	$-pedeLongitude
erroLatitude		DB	'Latitude incorreta.',10,13
tamErroLatitude		EQU $-erroLatitude
erroLongitude		DB	'Longitude incorreta.',10,13
tamErroLongitude	EQU $-erroLongitude

handArquivo 		DD 	?
rc					DD	?

geoCoord 			EQU $
geoCoordLocal 		DB 30 DUP (?) ; nome da localidade
geoCoordLatGra 		DB ? ; latitude graus (0-90)
geoCoordLatMin 		DB ? ; latitude minutos (0-59)
geoCoordLatOri 		DB ? ; latitude orientação ('N'|'S')
geoCoordLonGra 		DB ? ; longitude graus (0-180)
geoCoordLonMin 		DB ? ; longitude minutos (0-59)
geoCoordLonOri 		DB ? ; longitude orientação ('E'|'W')

inteiro				DD	?
tamanho				DD	?
pulaLinha	 		DB 10,13
numero 				DB 30 DUP (?)
nomeArq 			DB 30 DUP (?)
latitude 			DB 30 DUP (?)
longitude 			DB 30 DUP (?)

		.CODE	
		EXTRN	AscToInt:FAR,IntToAsc:FAR
		EXTRN	DateToBin:FAR,TimeToBin:FAR
		EXTRN	GetDateAsc:FAR,GetTimeAsc:FAR
		EXTRN	ScreenClear:FAR,ScreenWrite:FAR,KeyboardRead:FAR
		EXTRN	FileCreate:FAR,FileWrite:FAR,FileClose:FAR

Geograv:
		
	INIPROG

		XCALL	GetDateAsc,cabDay,cabMonth,cabYear
		XCALL	GetTimeAsc,cabHours,cabMinutes,cabSeconds

imprimeCabecalho:
;		Imprime o cabecalho do programa
		MOV		tamanho,tamCabecalho
		ID 		cabecalho,tamanho
		
pedeArquivoCoordenada:
;		Pede o nome do arquivo de cidades a ser gravado
		MOV		tamanho,tamInicial
		XCALL 	ScreenWrite,msgInicial,tamanho

recebeArquivoCoordenada:		
;		Le o nome do arquivo de cidades a ser gravado, sai do programa se receber enter
		MOV 	tamanho, 30
		XCALL	KeyboardRead,nomeArq, tamanho		
		CMP		tamanho,2
		JNG		Final

criaArquivoCoordenadas:
;		Remove o lixo da variavel lida, e tenta criar o arquivo com as cidades
		MOV     EDI,tamanho
		MOV     nomeArq[EDI-2],0
		MOV		nomeArq[EDI-1],0
		XCALL   FileCreate,handArquivo,nomeArq
		CMP     handArquivo,0
		JL      pedeArquivoCoordenada
	   
recebeLocalizacao:
;		Limpa a variavel do nome das cidades
		LEA		ESI,geoCoordLocal
		CALL	limpaLocal
;		Pede o nome da localidade
		MOV		tamanho,tamPedeLocal
		XCALL 	ScreenWrite,pedeLocal,tamanho
;		Se digitar enter, sai do programa
		MOV 	tamanho, 30
		XCALL	KeyboardRead,geoCoordLocal,tamanho		
		CMP		tamanho,2
		JNG		Final
;		Remove o lixo lido do nome da localidade
		MOV     EDI,tamanho
		MOV     geoCoordLocal[EDI-2],0
		MOV		geoCoordLocal[EDI-1],0

recebeLatitude:
;		Recebe a latitude da localizacao
		MOV     tamanho,tamPedeLatitude
		XCALL   ScreenWrite,pedeLatitude,tamanho
		LEA     ESI,latitude
		MOV     tamanho,SIZE latitude
		XCALL   KeyboardRead,latitude,tamanho
		CMP     tamanho,2 
; 		Caso seja enter, volta a pedir a latitude
		JNG     recebeLatitude
;		Remove o lixo da variavel lida
		MOV     EDI,tamanho
		MOV     latitude[EDI-2],0
		MOV		latitude[EDI-1],0
		
latitudeGraus:
;		Converte o grau da latitude lido em inteiro e verifica se o valor é valido
		MOV		tamanho,30
		XCALL   AscToInt,[ESI],tamanho,inteiro,rC
		CMP     rC,0
		JNE     ErrLatitudeInvalida
		MOV     EAX,inteiro
		CMP     EAX,0
		JL      ErrLatitudeInvalida
		CMP     EAX,90
		JG      ErrLatitudeInvalida
		MOV     geoCoordLatGra,AL
		
		INC		tamanho
		ADD     ESI,tamanho
		
latitudeMinutos:
;		Converte o minuto da latitude lido em inteiro, verifica se o valor é valido
		MOV		tamanho,30
		SUB		tamanho,3
		XCALL   AscToInt,[ESI],tamanho,inteiro,rC
		CMP     rC,0
		JNE     ErrLatitudeInvalida
		MOV     EAX,inteiro
		CMP     EAX,0
		JL      ErrLatitudeInvalida
		CMP     EAX,59
		JG      ErrLatitudeInvalida
		CMP		geoCoordLatGra,90
;		Se o valor do grau da latitude for 90, entao o minuto da mesma so pode ser 0
;		caso contrario, deve exibir erro
		JNE		guardaLatitudeMinutos
		CMP		AL,0
		JNE		ErrLatitudeInvalida
		
guardaLatitudeMinutos:
;		Guarda o valor do minuto da latitude
		MOV     geoCoordLatMin,AL

		INC		tamanho
		ADD 	ESI, tamanho	

latitudeOrientacao:
;		Transforma o valor da orientação da latitude em maiusculo, e compara com valores validos
		AND		BYTE PTR [ESI],11011111b
		CMP 	[ESI], BYTE PTR 'N'
		JE      guardaOrientacaoLat
		CMP 	[ESI], BYTE PTR 'S'
		JE      guardaOrientacaoLat	
		JMP		ErrLatitudeInvalida
		
guardaOrientacaoLat:
;		Se o valor da orientacao da latitude é valido entao, o guarda na sua variavel
		PUSH	[ESI]
		LEA		EDI,geoCoordLatOri
		POP		[EDI]
		
recebeLongitude:
;		Recebe a longitude da localizacao
		MOV     tamanho,tamPedeLongitude
		XCALL   ScreenWrite,pedeLongitude,tamanho
		LEA     ESI,longitude
		MOV     tamanho,SIZE longitude
		XCALL   KeyboardRead,longitude,tamanho
		CMP     tamanho,2
; 		Caso seja enter, volta a pedir a longitude
		JNG     recebeLongitude
;		Remove o lixo da variavel lida
		MOV     EDI,tamanho
		MOV     longitude[EDI-2],0
		MOV		longitude[EDI-1],0
		
longitudeGraus:
;		Converte o grau, da longitude lido, em inteiro e verifica se o valor é valido
		MOV		tamanho,30
		XCALL   AscToInt,[ESI],tamanho,inteiro,rC
		CMP     rC,0
		JNE     ErrLongitudeInvalida
		MOV     EAX,inteiro
		CMP     EAX,0
		JL      ErrLongitudeInvalida
		CMP     EAX,180
		JG      ErrLongitudeInvalida
		MOV     geoCoordLonGra,AL

		INC		tamanho
		ADD     ESI,tamanho

		
longitudeMinutos:
;		Converte o minuto, da longitude lido em inteiro, verifica se o valor é valido
		MOV		tamanho,30
		XCALL   AscToInt,[ESI],tamanho,inteiro,rC
		CMP     rC,0
		JNE     ErrLongitudeInvalida
		MOV     EAX,inteiro
		CMP     EAX,0
		JL      ErrLongitudeInvalida
		CMP     EAX,59
		JG      ErrLongitudeInvalida
		CMP		geoCoordLonGra,180
;		Se o valor do grau da longitude for 180, entao o minuto da mesma so pode ser 0
;		caso contrario, deve exibir erro
		JNE		guardaLongitudeMinutos
		CMP		AL,0
		JNE		ErrLongitudeInvalida
		
guardaLongitudeMinutos:
;		Guarda o valor do minuto da longitude
		MOV     geoCoordLonMin,AL
		
		INC		tamanho
		ADD		ESI,tamanho
		
longitudeOrientacao:
;		Transforma o valor da orientação da longitude em maiusculo, e compara com valores validos
		AND		BYTE PTR [ESI],11011111b
		CMP 	[ESI], BYTE PTR 'E'
		JE      guardaOrientacaoLon
		CMP 	[ESI], BYTE PTR 'W'
		JE      guardaOrientacaoLon
		JMP		ErrLongitudeInvalida
		
guardaOrientacaoLon:
;		Se o valor da orientacao da longitude é valido entao, o guarda na sua variavel
		PUSH	[ESI]
		LEA		EDI,geoCoordLonOri
		POP		[EDI]		

gravaDados:
;		Grava os dados no arquivo, de acordo com o template fornecido
		MOV		tamanho,30
		XCALL	FileWrite,handArquivo,geoCoordLocal,tamanho
		MOV		tamanho,1
		XCALL	FileWrite,handArquivo,geoCoordLatGra,tamanho
		XCALL	FileWrite,handArquivo,geoCoordLatMin,tamanho
		XCALL	FileWrite,handArquivo,geoCoordLatOri,tamanho
		XCALL	FileWrite,handArquivo,geoCoordLonGra,tamanho
		XCALL	FileWrite,handArquivo,geoCoordLonMin,tamanho
		XCALL	FileWrite,handArquivo,geoCoordLonOri,tamanho
		JMP		recebeLocalizacao
		
ErrLatitudeInvalida:
;		Exibe mensagem de erro na latitude e volta a pedi-la
		MOV 	tamanho, tamErroLatitude
		XCALL 	ScreenWrite,erroLatitude,tamanho
		JMP		recebeLatitude
		
ErrLongitudeInvalida:
;		Exibe mensagem de erro na longitude e volta a pedi-la		
		MOV 	tamanho, tamErroLongitude
		XCALL 	ScreenWrite,erroLongitude,tamanho
		JMP		recebeLongitude
		
Final:
		
		XCALL 	FileClose,handArquivo
		ENDPROG

; 		Funcao para limpar uma variavel de 30 bytes		
limpaLocal PROC	NEAR

;	+--------------------------------------------------------------+
;	| Chamada:	CALL	limpaLocal  								|
;	+--------------------------------------------------------------+

		MOV		BYTE PTR ESI[0],0
		MOV		BYTE PTR ESI[1],0
		MOV		BYTE PTR ESI[2],0
		MOV		BYTE PTR ESI[3],0
		MOV		BYTE PTR ESI[4],0
		MOV		BYTE PTR ESI[5],0
		MOV		BYTE PTR ESI[6],0
		MOV		BYTE PTR ESI[7],0
		MOV		BYTE PTR ESI[8],0
		MOV		BYTE PTR ESI[9],0
		MOV		BYTE PTR ESI[10],0
		MOV		BYTE PTR ESI[11],0
		MOV		BYTE PTR ESI[12],0
		MOV		BYTE PTR ESI[13],0
		MOV		BYTE PTR ESI[14],0
		MOV		BYTE PTR ESI[15],0
		MOV		BYTE PTR ESI[16],0
		MOV		BYTE PTR ESI[17],0
		MOV		BYTE PTR ESI[18],0
		MOV		BYTE PTR ESI[19],0
		MOV		BYTE PTR ESI[20],0
		MOV		BYTE PTR ESI[21],0
		MOV		BYTE PTR ESI[22],0
		MOV		BYTE PTR ESI[23],0
		MOV		BYTE PTR ESI[24],0
		MOV		BYTE PTR ESI[25],0
		MOV		BYTE PTR ESI[26],0
		MOV		BYTE PTR ESI[27],0
		MOV		BYTE PTR ESI[28],0
		MOV		BYTE PTR ESI[29],0
		
		RET

ENDP
		
END GeoGrav