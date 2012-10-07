;	Universidade Federal da Bahia
;	Departamento de Ciência da Computação
;
;	Disciplina:	MAT149 Linguagens de montagem
;	Alunos: 	Anna Luiza e Victor Santos
;	Professor:	Luiz Eduardo
;
;	Calcula distâncias geodésicas
;
;	30 de Junho de 2012
;
;	tasm  GeoCalc /z
;	tlink GeoCalc+DateTime+ScreKeyb+IntNum+FpuNum+FileDisk /3

		INCLUDE	XCall.mac
		INCLUDE	Macros.mac

		.MODEL SMALL
		.386
		DOSSEG
		.STACK	256
		.DATA

						DD	12 DUP (?)

cabecalho				DB	'Universidade Federal da Bahia'
						DB	30 DUP (' ')
cabDay					DB	2  DUP ('0')
						DB	'/'
cabMonth				DB	2  DUP ('0')
						DB	'/'
cabYear					DB	4  DUP ('0')
						DB	'  '
cabHours				DB	2  DUP ('0')
						DB	':'
cabMinutes				DB	2  DUP ('0')
						DB	':'
cabSeconds				DB	2  DUP ('0')
						DB	13,10
						DB	'Departamento de Ciencia da Computacao',13,10
						DB	'MATA49 Programacao de software basico',13,10
						DB	13,10,'Calculo de distancias geodesicas',13,10

tamCabecalho			EQU	$-cabecalho
msgInicial				DB	13,10,'Localidade origem ou <ENTER>=FIM                   : '
tamInicial				EQU $-msgInicial
pedeLatitudeOrigem		DB	'Latitude da origem (graus minutos orientacao)      : '
tamPedeLatitudeOrigem	EQU	$-pedeLatitudeOrigem
pedeLongitudeOrigem		DB	'Longitute da origem (graus minutos orientacao)     : '
tamPedeLongitudeOrigem	EQU	$-pedeLongitudeOrigem
pedeLatitude			DB	'Latitude da localidade (graus minutos orientacao)  : '
tamPedeLatitude			EQU	$-pedeLatitude
pedeLongitude			DB	'Longitute da localidade (graus minutos orientacao) : '
tamPedeLongitude		EQU	$-pedeLongitude
erroLatitude			DB	'Latitude incorreta.',13,10
tamErroLatitude			EQU $-erroLatitude
erroLongitude			DB	'Longitude incorreta.',13,10
tamErroLongitude		EQU $-erroLongitude
pedeOrigem				DB	'Nova localidade origem ou <ENTER> para continuar   : '
tamPedeOrigem			EQU $-pedeOrigem
pedeModo				DB	13,10,'Arquivo de coordenadas ou localidade ou <ENTER>=FIM: '
tamPedeModo				EQU $-pedeModo
pedeRelatorio DB		13,10,'Arquivo para gravar relatorio ou <ENTER> = monitor : '
tamPedeRelatorio		EQU $-pedeRelatorio
dadosLocalidadeOrigem 	DB 	13,10,'Localidade origem             Latitude    Longitude',13,10
tamDadosLocalidadeOrigem EQU $-dadosLocalidadeOrigem
dadosLocalidade 		DB 	13,10,13,10,'Localidade                    Latitude    Longitude    Distancia(km)',13,10
tamDadosLocalidade 		EQU $-dadosLocalidade
espacoVazio				DB '     '
tamEspacoVazio 			EQU $-espacoVazio

raioTerra 				DQ 	6371
noventaGraus 			DQ 	1.5707963267948966192313216916398
cos_a 					DQ 	?
sen_a 					DQ 	?
a 						DQ	?
b 						DQ 	?
c 						DQ 	?
lat 					DQ 	?
latOrigem 				DQ 	?
lon 					DQ 	?
lonOrigem				DQ 	?

handArquivoR 			DD 	?
handArquivo 			DD 	?
rc						DD	?
tamanho					DD	?
inteiro					DD	?
integer					DW  ?
nomeArq 				DB 30 DUP (?)
latitude 				DB 30 DUP (?)
longitude 				DB 30 DUP (?)
modo 					DB 30 DUP (?)
numero 					DB 3 DUP (?)
pulaLinha 				DB 13,10
relatorioCriado 		DB 0
mode 					DB	?

geoCoordOrigem 			EQU $
geoCoordLocalOrigem 	DB 30 DUP (?) ; nome da localidade
geoCoordLatGraOrigem 	DB ? ; latitude graus (0-90)
geoCoordLatMinOrigem 	DB ? ; latitude minutos (0-59)
geoCoordLatOriOrigem 	DB ? ; latitude orientação ('N'|'S')
geoCoordLonGraOrigem 	DB ? ; longitude graus (0-180)
geoCoordLonMinOrigem 	DB ? ; longitude minutos (0-59)
geoCoordLonOriOrigem 	DB ? ; longitude orientação ('E'|'W')

geoCoord 				EQU $
geoCoordLocal 			DB 30 DUP (?) ; nome da localidade
geoCoordLatGra 			DB ? ; latitude graus (0-90)
geoCoordLatMin 			DB ? ; latitude minutos (0-59)
geoCoordLatOri 			DB ? ; latitude orientação ('N'|'S')
geoCoordLonGra 			DB ? ; longitude graus (0-180)
geoCoordLonMin 			DB ? ; longitude minutos (0-59)
geoCoordLonOri 			DB ? ; longitude orientação ('E'|'W')

		.CODE	
		EXTRN	AscToInt:FAR,IntToAsc:FAR
		EXTRN	AscToFpu:FAR,FpuToAsc:FAR
		EXTRN	GetDateAsc:FAR,GetTimeAsc:FAR
		EXTRN	DateToAsc:FAR,TimeToAsc:FAR
		EXTRN	ScreenClear:FAR,ScreenWrite:FAR,KeyboardRead:FAR
		EXTRN	FileCreate:FAR,FileOpen:FAR,FileRead:FAR,FileWrite:FAR,FileClose:FAR

Geocalc:

		INIPROG

		XCALL	GetDateAsc,cabDay,cabMonth,cabYear
		XCALL	GetTimeAsc,cabHours,cabMinutes,cabSeconds

imprimeCabecalho:
;		Imprime o cabecalho do programa
		MOV		tamanho,tamCabecalho
		ID 		cabecalho,tamanho
		
recebeLocalizacaoOrigem:
;		Pede o nome da localidade de origem
		MOV		tamanho,tamInicial
		XCALL 	ScreenWrite,msgInicial,tamanho

		MOV 	tamanho, 30
		XCALL	KeyboardRead,geoCoordLocalOrigem,tamanho		
;		Se digitar enter, sai do programa
		CMP		tamanho,2
		JNG		Final
;		Remove o lixo lido do nome da localidade
		MOV     EDI,tamanho
		MOV     geoCoordLocalOrigem[EDI-2],0
		MOV		geoCoordLocalOrigem[EDI-1],0

recebeLatitudeOrigem:
;		Recebe a latitude da localizacao origem
		MOV     tamanho,tamPedeLatitudeOrigem
		XCALL   ScreenWrite,pedeLatitudeOrigem,tamanho
		LEA     ESI,latitude
		MOV     tamanho,SIZE latitude
		XCALL   KeyboardRead,latitude,tamanho
		CMP     tamanho,2
; 		Caso seja enter, volta a pedir a latitude da cidade origem
		JNG     recebeLatitudeOrigem
;		Remove o lixo da variavel lida
		MOV     EDI,tamanho
		MOV     latitude[EDI-2],0
		MOV		latitude[EDI-1],0
		
latitudeGrausOrigem:
;		Converte o grau, da latitude de origem lida, em inteiro e verifica se o valor é valido
		MOV		tamanho,30
		XCALL   AscToInt,[ESI],tamanho,inteiro,rC
		CMP     rC,0
		JNE     ErrLatitudeInvalidaOrigem
		MOV     EAX,inteiro
		CMP     EAX,0
		JL      ErrLatitudeInvalidaOrigem
		CMP     EAX,90
		JG      ErrLatitudeInvalidaOrigem
		MOV     geoCoordLatGraOrigem,AL
		
		INC		tamanho
		ADD     ESI,tamanho
		
latitudeMinutosOrigem:
;		Converte o minuto, da latitude de origem lido, em inteiro, verifica se o valor é valido
		MOV		tamanho,30
		SUB		tamanho,3
		XCALL   AscToInt,[ESI],tamanho,inteiro,rC
		CMP     rC,0
		JNE     ErrLatitudeInvalidaOrigem
		MOV     EAX,inteiro
		CMP     EAX,0
		JL      ErrLatitudeInvalidaOrigem
		CMP     EAX,59
		JG      ErrLatitudeInvalidaOrigem
		CMP		geoCoordLatGraOrigem,90
;		Se o valor do grau da latitude de origem for 90, entao o minuto da mesma so pode ser 0
;		caso contrario, deve exibir erro
		JNE		guardaLatitudeMinutosOrigem
		CMP		AL,0
		JNE		ErrLatitudeInvalidaOrigem
		
guardaLatitudeMinutosOrigem:
;		Guarda o valor do minuto da latitude de origem
		MOV     geoCoordLatMinOrigem,AL

		INC		tamanho
		ADD 	ESI, tamanho	

latitudeOrientacaoOrigem:
;		Transforma o valor da orientação da latitude de origem em maiusculo, e compara com valores validos
		AND		BYTE PTR [ESI],11011111b
		CMP 	[ESI], BYTE PTR 'N'
		JE      guardaOrientacaoLatOrigem
		CMP 	[ESI], BYTE PTR 'S'
		JE      guardaOrientacaoLatOrigem
		JMP		ErrLatitudeInvalidaOrigem
		
guardaOrientacaoLatOrigem:
;		Se o valor da orientacao da latitude de origem é valido entao, o guarda na sua variavel
		PUSH	[ESI]
		LEA		EDI,geoCoordLatOriOrigem
		POP		[EDI]
		
recebeLongitudeOrigem:
;		Recebe a longitude da localizacao de origem
		MOV     tamanho,tamPedeLongitudeOrigem
		XCALL   ScreenWrite,pedeLongitudeOrigem,tamanho
		LEA     ESI,longitude
		MOV     tamanho,SIZE longitude
		XCALL   KeyboardRead,longitude,tamanho
		CMP     tamanho,2
; 		Caso seja enter, volta a pedir a longitude
		JNG     recebeLongitudeOrigem
;		Remove o lixo da variavel lida
		MOV     EDI,tamanho
		MOV     longitude[EDI-2],0
		MOV		longitude[EDI-1],0
		
longitudeGrausOrigem:
;		Converte o grau, da longitude de origem lida, em inteiro e verifica se o valor é valido
		MOV		tamanho,30
		XCALL   AscToInt,[ESI],tamanho,inteiro,rC
		CMP     rC,0
		JNE     ErrLongitudeInvalidaOrigem
		MOV     EAX,inteiro
		CMP     EAX,0
		JL      ErrLongitudeInvalidaOrigem
		CMP     EAX,180
		JG      ErrLongitudeInvalidaOrigem
		MOV     geoCoordLonGraOrigem,AL

		INC		tamanho
		ADD     ESI,tamanho

		
longitudeMinutosOrigem:
;		Converte o minuto, da longitude de origem lida em inteiro, verifica se o valor é valido
		MOV		tamanho,30
		XCALL   AscToInt,[ESI],tamanho,inteiro,rC
		CMP     rC,0
		JNE     ErrLongitudeInvalidaOrigem
		MOV     EAX,inteiro
		CMP     EAX,0
		JL      ErrLongitudeInvalidaOrigem
		CMP     EAX,59
		JG      ErrLongitudeInvalidaOrigem
		CMP		geoCoordLonGraOrigem,180
;		Se o valor do grau da longitude de origem for 180, entao o minuto da mesma so pode ser 0
;		caso contrario, deve exibir erro
		JNE		guardaLongitudeMinutosOrigem
		CMP		AL,0
		JNE		ErrLongitudeInvalidaOrigem
		
guardaLongitudeMinutosOrigem:
;		Guarda o valor do minuto da longitude de origem
		MOV     geoCoordLonMinOrigem,AL
		
		INC		tamanho
		ADD		ESI,tamanho
		
longitudeOrientacaoOrigem:
;		Transforma o valor da orientação da longitude de origem em maiusculo, e compara com valores validos		
		AND		BYTE PTR [ESI],11011111b
		CMP 	[ESI], BYTE PTR 'E'
		JE      guardaOrientacaoLonOrigem
		CMP 	[ESI], BYTE PTR 'W'
		JE      guardaOrientacaoLonOrigem
		JMP		ErrLongitudeInvalidaOrigem
		
guardaOrientacaoLonOrigem:
;		Se o valor da orientacao da longitude de origem é valido entao, o guarda na sua variavel
		PUSH	[ESI]
		LEA		EDI,geoCoordLonOriOrigem
		POP		[EDI]
		JMP		recebeModo
		
ErrLatitudeInvalidaOrigem:
;		Exibe mensagem de erro na latitude origem e volta a pedi-la		
		MOV 	tamanho, tamErroLatitude
		XCALL 	ScreenWrite,erroLatitude,tamanho
		JMP		recebeLatitudeOrigem
		
ErrLongitudeInvalidaOrigem:
;		Exibe mensagem de erro na longitude origem e volta a pedi-la		
		MOV 	tamanho, tamErroLongitude
		XCALL 	ScreenWrite,erroLongitude,tamanho
		JMP		recebeLongitudeOrigem
		
recebeModo:
; 		Recebe o modo de funcionamento do programa (modo interativo ou modo lotes)
			
;		Limpa as variaveis modo e geoCoordLocal	
		LEA		ESI,modo
		CALL	limpaLocal
		
		LEA		ESI,geoCoordLocal
		CALL	limpaLocal
;		Pede o modo de execução do programa
		MOV		tamanho,tamPedeModo
		XCALL 	ScreenWrite,pedeModo,tamanho
		MOV 	tamanho, 30
		XCALL	KeyboardRead,modo,tamanho		
		CMP		tamanho,2
		JNG		Final
;		Caso nao seja enter, limpa o lixo da variavel lida
		MOV     EDI,tamanho
		MOV     modo[EDI-2],0
		MOV		modo[EDI-1],0
;		Tenta abrir o arquivo com o nome informado
		XCALL 	FileOpen,handArquivo,modo
		CMP		handArquivo,0
		JNL		modoLote
;		Caso nao consiga, entao o modo é interativo
		MOV		mode,1
		
		LEA		ESI,modo
		LEA		EDI,geoCoordLocal
		
		CALL	copy
		
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
		JMP		calculaRadianoLatOrigem
		
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

modoLote:
;		Caso o modo seja em lote
		MOV		mode,0
;		Limpa a variavel de geoCoordLocal
		LEA		ESI,geoCoordLocal
		CALL	limpaLocal
;		Le os dados do arquivo
		MOV		tamanho,30
		XCALL	FileRead,handArquivo,geoCoordLocal,tamanho
		CMP		tamanho,0
		JE		achouEOF
		MOV		tamanho,1
		XCALL	FileRead,handArquivo,geoCoordLatGra,tamanho
		XCALL	FileRead,handArquivo,geoCoordLatMin,tamanho
		XCALL	FileRead,handArquivo,geoCoordLatOri,tamanho
		XCALL	FileRead,handArquivo,geoCoordLonGra,tamanho
		XCALL	FileRead,handArquivo,geoCoordLonMin,tamanho
		XCALL	FileRead,handArquivo,geoCoordLonOri,tamanho
		
calculaRadianoLatOrigem:
;		Calcula o valor em radiano da latitude da origem
		FINIT
		MOV		AL,geoCoordLatMinOrigem
		MOV		integer,AX
		FILD	integer
		MOV		integer,60
		FILD	integer
		FDIVP	st(1),st
		MOV		AL,geoCoordLatGraOrigem
		MOV		integer,AX
		FILD	integer
		FADD	
		FLDPI	
		FMULP
		MOV		integer,180
		FILD	integer
		FDIVP	st(1),st
		CMP		geoCoordLatOriOrigem,'S'
		JNE		calculaRadianoLonOrigem
		FCHS
		
calculaRadianoLonOrigem:
;		Calcula o valor em radiano da longitude da origem
		FSTP	latOrigem
		MOV		AL,geoCoordLonMinOrigem
		MOV		integer,AX
		FILD	integer
		MOV		integer,60
		FILD	integer
		FDIVP	st(1),st
		MOV		AL,geoCoordLonGraOrigem
		MOV		integer,AX
		FILD	integer
		FADD	
		FLDPI	
		FMULP
		MOV		integer,180
		FILD	integer
		FDIVP	st(1),st	
		CMP		geoCoordLonOriOrigem,'W'
		JNE		calculaRadianoLat
		FCHS
		
calculaRadianoLat:
;		Calcula o valor em radiano da latitude da localidade destino
		FSTP	lonOrigem
		MOV		AL,geoCoordLatMin
		MOV		integer,AX
		FILD	integer
		MOV		integer,60
		FILD	integer
		FDIVP	st(1),st
		MOV		AL,geoCoordLatGra
		MOV		integer,AX
		FILD	integer
		FADD	
		FLDPI	
		FMULP
		MOV		integer,180
		FILD	integer
		FDIVP	st(1),st
		CMP		geoCoordLatOri,'S'
		JNE		calculaRadianoLon
		FCHS
		
calculaRadianoLon:
;		Calcula o valor em radiano da longitude da localidade destino
		FSTP	lat
		MOV		AL,geoCoordLonMin
		MOV		integer,AX
		FILD	integer
		MOV		integer,60
		FILD	integer
		FDIVP	st(1),st
		MOV		AL,geoCoordLonGra
		MOV		integer,AX
		FILD	integer
		FADD	
		FLDPI	
		FMULP
		MOV		integer,180
		FILD	integer
		FDIVP	st(1),st
		CMP		geoCoordLonOri,'W'
		JNE		calculaVariaveis
		FCHS
		;----------------------------------------------------------------------------------------

calculaVariaveis:
;		Calcula b,c e A
		FSTP	lon
		
		FLD	    noventaGraus
		FLD	    latOrigem
		FSUB	
		FSTP	b
		FLD		noventaGraus
		FLD		lat
		FSUB	
		FSTP	c
		FLD		lonOrigem
		FLD		lon
		FSUB	
		FSTP	a
		
leiDosSenos:
;		Realiza lei dos senos em cima das variaveis calculadas acima
;		de forma a obter o cos de a
		FLD		b
		FCOS	
		FLD		c
		FCOS	
		FMUL
		FLD		b
		FSIN
		FLD		c
		FSIN
		FMUL
		FLD		a
		FCOS
		FMUL
		FADD
		FSTP	cos_a

leiDosCossenos:
;		Realiza lei dos senos em cima das variaveis calculadas acima
;		de forma a obter o sen de a
		FLD		cos_a
		FLD		cos_a
		FMUL	
		MOV		integer,1
		FILD	integer
		FSUBR	
		FSQRT
		FSTP	sen_a

calculaDistancia:		
;		Calcula o arctangente de a e entao multiplica pelo raio da Terra, achando a distancia
		FLD		sen_a
		FLD		cos_a
		FPATAN
		FILD	raioTerra
		FMUL
		FSTP	a
;		Caso o relatorio ja tenha sido criado, entao o programa vai pra parte correspondente
		CMP		relatorioCriado,1
		JE		armazenaLocalidade
		CMP		relatorioCriado,2
		JE		mostraLocalidade
		
recebeNomeRelatorio:
;		Caso o relatorio ja tenha sido criado, entao o programa vai pra parte correspondente		
		CMP		relatorioCriado,1
		JE		armazenaLocalidade
		CMP		relatorioCriado,2
		JE		mostraLocalidade
;		Pede o nome do arquivo de relatorio, caso nao tenha sido criado previamente
		MOV		tamanho,tampedeRelatorio
		XCALL 	ScreenWrite,pedeRelatorio,tamanho
		MOV 	tamanho, 30
		XCALL	KeyboardRead,nomeArq, tamanho		
		CMP		tamanho,2
;		Se for enter, entao é para exibir na tela
		JNG		cabecalhoResultado
;		Limpa o lixo da variavel lida
		MOV     EDI,tamanho
		MOV     nomeArq[EDI-2],0
		MOV		nomeArq[EDI-1],0
		XCALL   FileCreate,handArquivoR,nomeArq
;		Tenta criar um arquivo com o nome informado
		CMP     handArquivoR,0
;		Caso nao consiga, entao pede um novo nome de relatorio
		JL		recebeNomeRelatorio
;		Se conseguiu, o relatorio foi criado, e é para ser escrito num arquivo
		MOV		relatorioCriado,1
		
cabecalhoResultado:
;		Move o tamanho do cabecalho do resultado para tamanho, e vai para a parte correspondente
;		do programa, a depender do tipo de relatorio desejado
		MOV		tamanho,tamCabecalho
		CMP		relatorioCriado,1
		JE		armazenaCabecalho
		MOV		relatorioCriado,2

mostraCabecalho:
;		Escreve o cabecalho do relatorio na tela
		ID 		cabecalho,tamanho
		JMP		mostraDadosLocalidadeOrigem
		
mostraDadosLocalidadeOrigem:
;		Mostra o titulo de cada dado na tela
		MOV		tamanho,tamDadosLocalidadeOrigem
		XCALL   ScreenWrite,dadosLocalidadeOrigem,tamanho
		
mostraLocalidadeOrigem:
;		Escreve a localidade origem na tela
		MOV		tamanho,30
		XCALL	ScreenWrite,geoCoordLocalOrigem,tamanho
		JMP		latitudeLocalidadeOrigem
		
armazenaCabecalho:
;		Escreve o cabecalho do relatorio no arquivo
		XCALL	FileWrite,handArquivoR,cabecalho,tamanho
		
armazenaDadosLocalidadeOrigem:
;		Armazena o titulo de cada dado no arquivo
		MOV		tamanho,tamDadosLocalidadeOrigem
		XCALL   FileWrite,handArquivoR,dadosLocalidadeOrigem,tamanho

armazenaLocalidadeOrigem:
		;		Escreve a localidade origem no arquivo
		MOV		tamanho,30
		XCALL	FileWrite,handArquivoR,GeoCoordLocalOrigem,tamanho

latitudeLocalidadeOrigem:

		; ---------- Exibe os dados da latitude
		
		MOV		numero[0],0
		MOV		numero[1],0 ; Apagando o conteudo de numero
		MOV		numero[2],0
		
		MOV		AL,geoCoordLatGraOrigem
		MOV		inteiro,EAX
		MOV		tamanho,3
		XCALL	IntToAsc,inteiro,numero,tamanho
;		Guarda o numero 'inteiro' no arquivo ou exibe na tela a depende do que foi escolhido previamente
		CALL	guardaDado 
		
		MOV		numero[0],0
		MOV		numero[1],0 ; Apagando o conteudo de numero
		MOV		numero[2],0
		
		MOV		AL,geoCoordLatMinOrigem
		MOV		inteiro,EAX
		MOV		tamanho,3
		XCALL	IntToAsc,inteiro,numero,tamanho
;		Guarda o numero 'inteiro' no arquivo ou exibe na tela a depende do que foi escolhido previamente
		CALL	guardaDado
		
		MOV		tamanho,1
		MOV		numero,20h
;		Da um espaço entre o minuto da latitude da origem e a orientacao da mesma
		CALL	guardaDado
		
		CMP		relatorioCriado,1
;		Se o relatorio for um arquivo, ele pula para a parte correspondente
		JE		armazenaLatOriOrigem
		
mostraLatOriOrigem:
;		Mostra a orientacao da latitude da origem na tela
		XCALL	ScreenWrite,geoCoordLatOriOrigem,tamanho
		JMP 	longitudeLocalidadeOrigem
		
armazenaLatOriOrigem:
;		Guarda a orientacao da latitude da origem no arquivo
		XCALL	FileWrite,handArquivoR,geoCoordLatOriOrigem,tamanho
		
		; ----------
		
longitudeLocalidadeOrigem:
		
		CALL	daEspaco ; Da espaço entre a latitude e a longitude
				
		; ---------- Exibe os dados da longitude
		
		MOV		numero[0],0
		MOV		numero[1],0 ; Apagando o conteudo de numero
		MOV		numero[2],0
		
		MOV		AL,geoCoordLonGraOrigem
		MOV		inteiro,EAX
		MOV		tamanho,3
		XCALL	IntToAsc,inteiro,numero,tamanho
;		Guarda o numero 'inteiro' no arquivo ou exibe na tela a depende do que foi escolhido previamente
		CALL	guardaDado
		
		MOV		numero[0],0
		MOV		numero[1],0 ; Apagando o conteudo de numero
		MOV		numero[2],0
		
		MOV		AL,geoCoordLonMinOrigem
		MOV		inteiro,EAX
		MOV		tamanho,3
		XCALL	IntToAsc,inteiro,numero,tamanho
;		Guarda o numero 'inteiro' no arquivo ou exibe na tela a depende do que foi escolhido previamente
		CALL	guardaDado
		
		MOV		tamanho,1
		MOV		numero,20h
;		Da um espaço entre o minuto da longitude da origem e a orientacao da mesma
		CALL	guardaDado
;		Se o relatorio for um arquivo, ele pula para a parte correspondente
		CMP		relatorioCriado,1
		JE		armazenaLonOriOrigem
		
mostraLonOriOrigem:
;		Mostra a orientacao da longitude da origem na tela
		XCALL	ScreenWrite,GeoCoordLonOriOrigem,tamanho
		JMP		cabecalhoLocalidade

armazenaLonOriOrigem:
;		Guarda a orientacao da longitude da origem no arquivo		
		XCALL	FileWrite,handArquivoR,geoCoordLonOriOrigem,tamanho
		
		; ----------

cabecalhoLocalidade:

		CMP		relatorioCriado,1
		JE		armazenaDadosLocalidade
		
mostraDadosLocalidade:
;		Mostra o titulo de cada dado na tela
		MOV		tamanho,tamDadosLocalidade
		XCALL   ScreenWrite,dadosLocalidade,tamanho
		
mostraLocalidade:
;		Escreve a localidade na tela	
		MOV		tamanho,30
		XCALL	ScreenWrite,GeoCoordLocal,tamanho
		JMP		latitudeLocalidade
		
armazenaDadosLocalidade:
;		Armazena o titulo de cada dado no arquivo
		MOV		tamanho,tamDadosLocalidade
		XCALL	FileWrite,handArquivoR,dadosLocalidade,tamanho
		
armazenaLocalidade:
;		Escreve a localidade no arquivo
		MOV		tamanho,30
		XCALL	FileWrite,handArquivoR,geoCoordLocal,tamanho
		
latitudeLocalidade:

		; ---------- Exibe os dados da latitude
		
		MOV		numero[0],0
		MOV		numero[1],0 ; Apagando o conteudo de numero
		MOV		numero[2],0
		
		MOV		AL,geoCoordLatGra
		MOV		inteiro,EAX
		MOV		tamanho,3
		XCALL	IntToAsc,inteiro,numero,tamanho
		CALL	guardaDado
		
		MOV		numero[0],0
		MOV		numero[1],0 ; Apagando o conteudo de numero
		MOV		numero[2],0
		
		MOV		AL,geoCoordLatMin
		MOV		inteiro,EAX
		MOV		tamanho,3
		XCALL	IntToAsc,inteiro,numero,tamanho
		CALL	guardaDado
		
		MOV		tamanho,1
		MOV		numero,20h
		CALL	guardaDado
		
		CMP		relatorioCriado,1
		JE		armazenaLatOri

mostraLatOri:
;		Mostra a orientacao da latitude na tela
		XCALL	ScreenWrite,geoCoordLatOri,tamanho
		JMP 	longitudeLocalidade
		
armazenaLatOri:
;		Guarda a orientacao da latitude no arquivo
		XCALL	FileWrite,handArquivoR,geoCoordLatOri,tamanho

		; ----------

longitudeLocalidade:

		CALL	daEspaco
				
		; ---------- Exibe os dados da longitude
				
		MOV		numero[0],0
		MOV		numero[1],0 ; Apagando o conteudo de numero
		MOV		numero[2],0		
				
		MOV		AL,geoCoordLonGra
		MOV		inteiro,EAX
		MOV		tamanho,3
		XCALL	IntToAsc,inteiro,numero,tamanho
		;		Guarda o numero 'inteiro' no arquivo ou exibe na tela a depende do que foi escolhido previamente
		CALL	guardaDado
		
		MOV		numero[0],0
		MOV		numero[1],0 ; Apagando o conteudo de numero
		MOV		numero[2],0
		
		MOV		AL,geoCoordLonMin
		MOV		inteiro,EAX
		MOV		tamanho,3
		XCALL	IntToAsc,inteiro,numero,tamanho
;		Guarda o numero 'inteiro' no arquivo ou exibe na tela a depende do que foi escolhido previamente
		CALL	guardaDado
		
		MOV		tamanho,1
		MOV		numero,20h
;		Da um espaço entre o minuto e a orientacao da longitude
		CALL	guardaDado
;		Se o relatorio for um arquivo, ele pula para a parte correspondente
		CMP		relatorioCriado,1
		JE		armazenaLonOri
		
mostraLonOri:
;		Mostra a orientacao da longitude na tela
		XCALL	ScreenWrite,geoCoordLonOri,tamanho
		CALL	daEspaco
		JMP		mostraDistancia

armazenaLonOri:
;		Guarda a orientacao da longitude no arquivo				
		XCALL	FileWrite,handArquivoR,geoCoordLonOri,tamanho
		CALL	daEspaco

armazenaDistancia:
;		Armazena a distancia no arquivo com 4 casas decimais
		LEA		ESI,modo
		CALL	limpaLocal
		MOV		tamanho,12
		MOV		inteiro,4
		
		XCALL	FpuToAsc,,a,modo,tamanho,,inteiro
		XCALL	FileWrite,handArquivoR,modo,tamanho
		
		MOV		tamanho,2
		XCALL	FileWrite,handArquivoR,pulaLinha,tamanho
		
		JMP		finalizando
		
mostraDistancia:
;		Mostra a distancia com 4 casas decimais
		LEA		ESI,modo
		CALL	limpaLocal
		MOV		tamanho,12
		MOV		inteiro,4
		
		XCALL	FpuToAsc,,a,modo,tamanho,,inteiro
		XCALL	ScreenWrite,modo,tamanho
		
		MOV		tamanho,2
		XCALL	ScreenWrite,pulaLinha,tamanho

		JMP		finalizando

achouEOF:
;		Caso tenha achado o fim de arquivo ao ler os dados de um arquivo(atraves do modo lote)
		MOV		mode,1
;		Finaliza o modo lote
		XCALL 	FileClose,handArquivo
		MOV		handArquivo,0h
;		Fecha o arquivo e move 0 para seu handler
		
finalizando:

		CMP		mode,0
		JE		modoLote
;		Da loop caso esteja no modo lote, e ainda nao tenha terminado o arquivo
		
		MOV		handArquivo,0h
;		Caso nao entre no loop, o modo lote terminou, entao move 0 para o handler do arquivo deste modo

		CMP		relatorioCriado,1
;		Caso o relatorio nao seja um arquivo,realiza uma nova execucao
		JNE		novaExecucao
		
fechaArquivo:
;		Fecha o arquivo do relatorio
		MOV		tamanho,2
		XCALL	FileWrite,handArquivoR,pulaLinha,tamanho
		XCALL	FileClose,handArquivoR 
		MOV		handArquivoR,0h
			
novaExecucao:

		MOV		relatorioCriado,0
;		Pede uma nova localidade
		MOV		tamanho,2
		XCALL	ScreenWrite,pulaLinha,tamanho
		MOV		tamanho,tamPedeOrigem
		XCALL	ScreenWrite,pedeOrigem,tamanho
;		Limpa a variavel modo
		LEA		ESI,modo
		CALL	limpaLocal
;		Limpa a variavel com a localidade destino
		LEA		ESI,geoCoordLocal
		CALL	limpaLocal
;		Le a nova localidade
		MOV     tamanho,30
		XCALL   KeyboardRead,modo,tamanho
		CMP     tamanho,2
;		Se for enter, a localidade é a mesma de antes e re-executa o programa
		JNG     recebeModo

		LEA		ESI,geoCoordLocalOrigem
		CALL	limpaLocal
;		Limpa a localidade origem		
		LEA		ESI,modo
		LEA		EDI,geoCoordLocalOrigem
		
		CALL	copy
;		Se nao é pra utilizar a mesma localidade, entao copia modo para a variavel de localidade origem
		MOV     EDI,tamanho
		MOV     geoCoordLocalOrigem[EDI-2],0
		MOV		geoCoordLocalOrigem[EDI-1],0
;		Limpa lixo da variavel lida
		LEA		ESI,modo
		CALL	limpaLocal
;		Limpa a variavel modo
		JMP		recebeLatitudeOrigem
;		Pede a latitude dessa nova horigem, e re-executa o programa

guardaDado PROC NEAR
;	Guarda um dado no arquivo ou no terminal
;	+--------------------------------------------------------------+
;	| Chamada:	CALL	guardaDado,mode,numero,tamanho,handArquivoR |
;	+--------------------------------------------------------------+

		CMP		relatorioCriado,1
		JE		escreveDado

mostraDado:

		XCALL	ScreenWrite,numero,tamanho
		JMP		Fim

escreveDado:

		XCALL	FileWrite,handArquivoR,numero,tamanho
		
Fim:
		RET

ENDP

daEspaco PROC NEAR
;	Da um espaço entre o minuto e a orientacao de uma latitude ou longitude de uma localidade
;	+--------------------------------------------------------------+
;	| Chamada:	CALL	daEspaco,espacoVazio,tamEspacoVazio			|
;	+--------------------------------------------------------------+

		MOV		tamanho,tamEspacoVazio
		CMP		relatorioCriado,1
		JE		escreveEspacoVazio

mostraEspacoVazio:

		XCALL	ScreenWrite,espacoVazio,tamanho
		JMP		Fin

escreveEspacoVazio:

		XCALL	FileWrite,handArquivoR,espacoVazio,tamanho

Fin:
		RET
		
ENDP
		
limpaLocal PROC	NEAR
;	Limpa uma variavel de 30 bytes
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

copy PROC NEAR
;	Copia uma variavel de 30 bytes para outra de 30 bytes		
;	+--------------------------------------------------------------+
;	| Chamada:	CALL	copy		  								|
;	+--------------------------------------------------------------+

		MOV		CX,30
inicio:
		MOV 	EAX, [ESI]
		MOV	 	[EDI], EAX
		INC 	ESI
		INC 	EDI
		LOOP	inicio
		
		RET

ENDP

Final:

		XCALL 	FileClose,handArquivo
		XCALL 	FileClose,handArquivoR
		ENDPROG
		
END	Geocalc