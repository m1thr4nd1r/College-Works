<ncl id="myNCLDocID">
	<head>
		<connectorBase id="connBaseId">
			<importBase alias="conn" documentURI="defaultConnBase.ncl">
			</importBase>
		</connectorBase>
		<regionBase id="regionBase0">
			<region height="100.00%" id="screenRegion" left="0.00%" top="0.00%" width="100.00%" zIndex="1">
				<region height="10.00%" id="rAnser1" left="0.00%" top="90.00%" width="25.00%" zIndex="2">
				</region>
				<region height="10.00%" id="rAnser2" left="25.00%" top="90.00%" width="25.00%" zIndex="2">
				</region>
				<region height="10.00%" id="rAnser3" left="50.00%" top="90.00%" width="25.00%" zIndex="2">
				</region>
				<region height="10.00%" id="rAnser4" left="75.00%" top="90.00%" width="25.00%" zIndex="2">
				</region>
				<region height="9.00%" id="rQuestion" left="0.00%" top="80.83%" width="100.00%" zIndex="2">
				</region>
				<region height="100.00%" id="rVideo" left="0.00%" top="0.00%" width="100.00%" zIndex="1">
				</region>
			</region>
		</regionBase>
		<descriptorBase id="descriptorBase1">
			<descriptor id="dVideo" region="rVideo">
			</descriptor>
			<descriptor explicitDur="5s" id="dQuestion" region="rQuestion">
			</descriptor>
			<descriptor id="dAnser1" region="rAnser1">
			</descriptor>
			<descriptor id="dAnser2" region="rAnser2">
			</descriptor>
			<descriptor id="dAnser3" region="rAnser3">
			</descriptor>
			<descriptor id="dAnser4" region="rAnser4">
			</descriptor>
			<descriptor explicitDur="3s" id="dMsg" region="rQuestion">
			</descriptor>
		</descriptorBase>
	</head>
	<body id="myBodyID">
		<media descriptor="dVideo" id="homem_de_aco" src="media/video1.mp4">
			<property name="height" value="100%">
			</property>
			<area begin="5s" id="aQuestion1">
			</area>
			<area begin="10s" id="aQuestion2">
			</area>
			<area begin="15s" id="aQuestion3">
			</area>
		</media>
		<port component="homem_de_aco" id="pStart">
		</port>
		<context id="cQuestion1">
			<port component="question1" id="pQuestion1">
			</port>
			<media descriptor="dQuestion" id="question1" src="perguntas/question1.html">
			</media>
			<media descriptor="dAnser1" id="q1Anser1" src="respostas/q1Anser1.html">
			</media>
			<media descriptor="dAnser2" id="q1Anser2" src="respostas/q1Anser2.html">
			</media>
			<media descriptor="dAnser3" id="q1Anser3" src="respostas/q1Anser3.html">
			</media>
			<media descriptor="dAnser4" id="q1Anser4" src="respostas/q1Anser4.html">
			</media>
			<link id="lQ11" xconnector="conn#onBeginStart">
				<bind component="question1" role="onBegin">
				</bind>
				<bind component="q1Anser1" role="start">
				</bind>
				<bind component="q1Anser2" role="start">
				</bind>
				<bind component="q1Anser3" role="start">
				</bind>
				<bind component="q1Anser4" role="start">
				</bind>
			</link>
			<link id="lQ12" xconnector="conn#onEndStop">
				<bind component="question1" role="onEnd">
				</bind>
				<bind component="q1Anser4" role="stop">
				</bind>
				<bind component="q1Anser3" role="stop">
				</bind>
				<bind component="q1Anser2" role="stop">
				</bind>
				<bind component="q1Anser1" role="stop">
				</bind>
			</link>
		</context>
		<context id="cQuestion2">
			<media descriptor="dQuestion" id="question2" src="perguntas/question2.html">
			</media>
			<media descriptor="dAnser1" id="q2Anser1" src="respostas/q2Anser1.html">
			</media>
			<media descriptor="dAnser2" id="q2Anser2" src="respostas/q2Anser2.html">
			</media>
			<media descriptor="dAnser3" id="q2Anser3" src="respostas/q2Anser3.html">
			</media>
			<media descriptor="dAnser4" id="q2Anser4" src="respostas/q2Anser4.html">
			</media>
			<port component="question2" id="pQuestion2">
			</port>
			<link id="lQ21" xconnector="conn#onBeginStart">
				<bind component="question2" role="onBegin">
				</bind>
				<bind component="q2Anser1" role="start">
				</bind>
				<bind component="q2Anser2" role="start">
				</bind>
				<bind component="q2Anser3" role="start">
				</bind>
				<bind component="q2Anser4" role="start">
				</bind>
			</link>
			<link id="lQ22" xconnector="conn#onEndStop">
				<bind component="question2" role="onEnd">
				</bind>
				<bind component="q2Anser4" role="stop">
				</bind>
				<bind component="q2Anser3" role="stop">
				</bind>
				<bind component="q2Anser2" role="stop">
				</bind>
				<bind component="q2Anser1" role="stop">
				</bind>
			</link>
		</context>
		<media descriptor="dMsg" id="msgAcertou" src="mensagens/acertou.html">
		</media>
		<media descriptor="dMsg" id="msgErrou" src="mensagens/errou.html">
		</media>
		<context id="cQuestion3">
			<media descriptor="dAnser2" id="q3Anser2" src="respostas/q3Anser2.html">
			</media>
			<media descriptor="dAnser1" id="q3Anser1" src="respostas/q3Anser1.html">
			</media>
			<media descriptor="dAnser4" id="q4Anser4" src="respostas/q3Anser4.html">
			</media>
			<media descriptor="dQuestion" id="question3" src="perguntas/question3.html">
			</media>
			<port component="question3" id="pQuestion3">
			</port>
			<media descriptor="dAnser3" id="q3Anser3" src="respostas/q3Anser3.html">
			</media>
			<link id="lQ31" xconnector="conn#onBeginStart">
				<bind component="question3" role="onBegin">
				</bind>
				<bind component="q3Anser1" role="start">
				</bind>
				<bind component="q3Anser2" role="start">
				</bind>
				<bind component="q3Anser3" role="start">
				</bind>
				<bind component="q4Anser4" role="start">
				</bind>
			</link>
			<link id="lQ32" xconnector="conn#onEndStop">
				<bind component="question3" role="onEnd">
				</bind>
				<bind component="q4Anser4" role="stop">
				</bind>
				<bind component="q3Anser3" role="stop">
				</bind>
				<bind component="q3Anser2" role="stop">
				</bind>
				<bind component="q3Anser1" role="stop">
				</bind>
			</link>
		</context>
		<link id="lC12" xconnector="conn#onBeginPause">
			<bind component="cQuestion1" interface="pQuestion1" role="onBegin">
			</bind>
			<bind component="homem_de_aco" interface="aQuestion1" role="pause">
			</bind>
		</link>
		<link id="lC13" xconnector="conn#onBeginSet_var">
			<bind component="cQuestion1" interface="pQuestion1" role="onBegin">
			</bind>
			<bind component="homem_de_aco" interface="height" role="set">
				<bindParam name="var" value="81%">
				</bindParam>
			</bind>
		</link>
		<link id="lC14" xconnector="conn#onEndSet_varResume">
			<bind component="cQuestion1" interface="pQuestion1" role="onEnd">
			</bind>
			<bind component="homem_de_aco" interface="aQuestion1" role="resume">
			</bind>
			<bind component="homem_de_aco" interface="height" role="set">
				<bindParam name="var" value="100%">
				</bindParam>
			</bind>
		</link>
		<link id="lC15" xconnector="conn#onKeySelectionStartPauseSet_var">
			<bind component="cQuestion1" interface="pQuestion1" role="onSelection">
				<bindParam name="keyCode" value="GREEN">
				</bindParam>
			</bind>
			<bind component="msgAcertou" role="start">
			</bind>
			<bind component="cQuestion1" interface="pQuestion1" role="pause">
			</bind>
			<bind component="score" interface="inc" role="set">
				<bindParam name="var" value="1">
				</bindParam>
			</bind>
		</link>
		<link id="lC16" xconnector="conn#onEndStop">
			<bind component="msgAcertou" role="onEnd">
			</bind>
			<bind component="cQuestion1" interface="pQuestion1" role="stop">
			</bind>
		</link>
		<link id="lC18" xconnector="conn#onKeySelectionStartPause">
			<bind component="cQuestion1" interface="pQuestion1" role="onSelection">
				<bindParam name="keyCode" value="BLUE">
				</bindParam>
			</bind>
			<bind component="msgErrou" role="start">
			</bind>
			<bind component="cQuestion1" interface="pQuestion1" role="pause">
			</bind>
		</link>
		<link id="lC17" xconnector="conn#onKeySelectionStartPause">
			<bind component="cQuestion1" interface="pQuestion1" role="onSelection">
				<bindParam name="keyCode" value="YELLOW">
				</bindParam>
			</bind>
			<bind component="msgErrou" role="start">
			</bind>
			<bind component="cQuestion1" interface="pQuestion1" role="pause">
			</bind>
		</link>
		<link id="lC19" xconnector="conn#onKeySelectionStartPause">
			<bind component="cQuestion1" interface="pQuestion1" role="onSelection">
				<bindParam name="keyCode" value="RED">
				</bindParam>
			</bind>
			<bind component="msgErrou" role="start">
			</bind>
			<bind component="cQuestion1" interface="pQuestion1" role="pause">
			</bind>
		</link>
		<link id="lC110" xconnector="conn#onEndStop">
			<bind component="msgErrou" role="onEnd">
			</bind>
			<bind component="cQuestion1" interface="pQuestion1" role="stop">
			</bind>
		</link>
		<link id="lC22" xconnector="conn#onBeginPause">
			<bind component="cQuestion2" interface="pQuestion2" role="onBegin">
			</bind>
			<bind component="homem_de_aco" interface="aQuestion2" role="pause">
			</bind>
		</link>
		<link id="lC23" xconnector="conn#onBeginSet_var">
			<bind component="cQuestion2" interface="pQuestion2" role="onBegin">
			</bind>
			<bind component="homem_de_aco" interface="height" role="set">
				<bindParam name="var" value="81%">
				</bindParam>
			</bind>
		</link>
		<link id="lC33" xconnector="conn#onBeginSet_var">
			<bind component="cQuestion3" interface="pQuestion3" role="onBegin">
			</bind>
			<bind component="homem_de_aco" interface="height" role="set">
				<bindParam name="var" value="81%">
				</bindParam>
			</bind>
		</link>
		<link id="lC24" xconnector="conn#onEndSet_varResume">
			<bind component="cQuestion2" interface="pQuestion2" role="onEnd">
			</bind>
			<bind component="homem_de_aco" interface="aQuestion2" role="resume">
			</bind>
			<bind component="homem_de_aco" interface="height" role="set">
				<bindParam name="var" value="100%">
				</bindParam>
			</bind>
		</link>
		<link id="lC25" xconnector="conn#onKeySelectionStartPauseSet_var">
			<bind component="cQuestion2" interface="pQuestion2" role="onSelection">
				<bindParam name="keyCode" value="BLUE">
				</bindParam>
			</bind>
			<bind component="msgAcertou" role="start">
			</bind>
			<bind component="cQuestion2" interface="pQuestion2" role="pause">
			</bind>
			<bind component="score" interface="inc" role="set">
				<bindParam name="var" value="1">
				</bindParam>
			</bind>
		</link>
		<link id="lC26" xconnector="conn#onEndStop">
			<bind component="msgAcertou" role="onEnd">
			</bind>
			<bind component="cQuestion2" interface="pQuestion2" role="stop">
			</bind>
		</link>
		<link id="lC27" xconnector="conn#onKeySelectionStartPause">
			<bind component="cQuestion2" interface="pQuestion2" role="onSelection">
				<bindParam name="keyCode" value="RED">
				</bindParam>
			</bind>
			<bind component="msgErrou" role="start">
			</bind>
			<bind component="cQuestion2" interface="pQuestion2" role="pause">
			</bind>
		</link>
		<link id="lC28" xconnector="conn#onKeySelectionStartPause">
			<bind component="cQuestion2" interface="pQuestion2" role="onSelection">
				<bindParam name="keyCode" value="YELLOW">
				</bindParam>
			</bind>
			<bind component="msgErrou" role="start">
			</bind>
			<bind component="cQuestion2" interface="pQuestion2" role="pause">
			</bind>
		</link>
		<link id="lC29" xconnector="conn#onKeySelectionStartPause">
			<bind component="cQuestion2" interface="pQuestion2" role="onSelection">
				<bindParam name="keyCode" value="GREEN">
				</bindParam>
			</bind>
			<bind component="msgErrou" role="start">
			</bind>
			<bind component="cQuestion2" interface="pQuestion2" role="pause">
			</bind>
		</link>
		<link id="lC210" xconnector="conn#onEndStop">
			<bind component="msgErrou" role="onEnd">
			</bind>
			<bind component="cQuestion2" interface="pQuestion2" role="stop">
			</bind>
		</link>
		<link id="lC11" xconnector="conn#onBeginStart">
			<bind component="homem_de_aco" interface="aQuestion1" role="onBegin">
			</bind>
			<bind component="cQuestion1" interface="pQuestion1" role="start">
			</bind>
		</link>
		<link id="lC21" xconnector="conn#onBeginStart">
			<bind component="homem_de_aco" interface="aQuestion2" role="onBegin">
			</bind>
			<bind component="cQuestion2" interface="pQuestion2" role="start">
			</bind>
		</link>
		<media id="score" src="score.lua">
			<property name="inc">
			</property>
			<property name="counter">
			</property>
		</media>
		<link id="link0" xconnector="conn#onCondGteBeginStart">
			<linkParam name="var" value="2">
			</linkParam>
			<bind component="homem_de_aco" interface="aQuestion3" role="onBegin">
			</bind>
			<bind component="score" interface="counter" role="attNodeTest">
			</bind>
			<bind component="cQuestion3" interface="pQuestion3" role="start">
			</bind>
		</link>
		<link id="link1" xconnector="conn#onBeginStart">
			<bind component="homem_de_aco" role="onBegin">
			</bind>
			<bind component="score" role="start">
			</bind>
		</link>
		<link id="link2" xconnector="conn#onEndStop">
			<bind component="homem_de_aco" role="onEnd">
			</bind>
			<bind component="score" role="stop">
			</bind>
		</link>
		<context id="cFinal1">
			<port component="msgFinal1" id="pFinal1">
			</port>
			<media descriptor="dVideo" id="videoFinal1" src="media/final1.mp4">
			</media>
			<media descriptor="dMsg" id="msgFinal1" src="mensagens/final1.html">
			</media>
			<link id="link4" xconnector="conn#onEndStart">
				<bind component="msgFinal1" role="onEnd">
				</bind>
				<bind component="videoFinal1" role="start">
				</bind>
			</link>
		</context>
		<link id="lFinalPadrao" xconnector="conn#onEndStart">
			<bind component="homem_de_aco" interface="aQuestion3" role="onEnd">
			</bind>
			<bind component="cFinal1" interface="pFinal1" role="start">
			</bind>
		</link>
		<link id="lFinal1" xconnector="conn#onKeySelectionStartAbort">
			<bind component="cQuestion3" interface="pQuestion3" role="onSelection">
				<bindParam name="keyCode" value="RED">
				</bindParam>
			</bind>
			<bind component="cFinal1" interface="pFinal1" role="start">
			</bind>
			<bind component="homem_de_aco" interface="aQuestion3" role="abort">
			</bind>
		</link>
		<link id="link7" xconnector="conn#onEndSet_varResume">
			<bind component="cQuestion3" interface="pQuestion3" role="onEnd">
			</bind>
			<bind component="homem_de_aco" interface="aQuestion3" role="resume">
			</bind>
			<bind component="homem_de_aco" interface="height" role="set">
				<bindParam name="var" value="100%">
				</bindParam>
			</bind>
		</link>
		<link id="link3" xconnector="conn#onBeginSet_varPause">
			<bind component="cQuestion3" interface="pQuestion3" role="onBegin">
			</bind>
			<bind component="homem_de_aco" interface="aQuestion3" role="pause">
			</bind>
			<bind component="homem_de_aco" interface="height" role="set">
				<bindParam name="var" value="81%">
				</bindParam>
			</bind>
		</link>
		<context id="cFinal2">
			<media descriptor="dVideo" id="videoFinal2" src="media/final2.mp4">
			</media>
			<port component="msgFinal2" id="pFinal2">
			</port>
			<media descriptor="dMsg" id="msgFinal2" src="mensagens/final2.html">
			</media>
			<link id="link8" xconnector="conn#onEndStart">
				<bind component="msgFinal2" role="onEnd">
				</bind>
				<bind component="videoFinal2" role="start">
				</bind>
			</link>
		</context>
		<link id="lFinal2" xconnector="conn#onKeySelectionStartAbort">
			<bind component="cQuestion3" interface="pQuestion3" role="onSelection">
				<bindParam name="keyCode" value="GREEN">
				</bindParam>
			</bind>
			<bind component="cFinal2" interface="pFinal2" role="start">
			</bind>
			<bind component="homem_de_aco" interface="aQuestion3" role="abort">
			</bind>
		</link>
		<context id="cFinal3">
			<media descriptor="dMsg" id="msgFinal3" src="mensagens/final3.html">
			</media>
			<media descriptor="dVideo" id="videoFinal3" src="media/final3.mp4">
			</media>
			<port component="msgFinal3" id="pFinal3">
			</port>
			<link id="link10" xconnector="conn#onEndStart">
				<bind component="msgFinal3" role="onEnd">
				</bind>
				<bind component="videoFinal3" role="start">
				</bind>
			</link>
		</context>
		<link id="lFinal3" xconnector="conn#onKeySelectionStartAbort">
			<bind component="cQuestion3" interface="pQuestion3" role="onSelection">
				<bindParam name="keyCode" value="YELLOW">
				</bindParam>
			</bind>
			<bind component="cFinal3" interface="pFinal3" role="start">
			</bind>
			<bind component="homem_de_aco" interface="aQuestion3" role="abort">
			</bind>
		</link>
		<context id="cFinal4">
			<media descriptor="dVideo" id="videoFinal4" src="media/final4.mp4">
			</media>
			<media descriptor="dMsg" id="msgFinal4" src="mensagens/final4.html">
			</media>
			<port component="msgFinal4" id="pFinal4">
			</port>
			<link id="link12" xconnector="conn#onEndStart">
				<bind component="msgFinal4" role="onEnd">
				</bind>
				<bind component="videoFinal4" role="start">
				</bind>
			</link>
		</context>
		<link id="lFinal4" xconnector="conn#onKeySelectionStartAbort">
			<bind component="cQuestion3" interface="pQuestion3" role="onSelection">
				<bindParam name="keyCode" value="BLUE">
				</bindParam>
			</bind>
			<bind component="homem_de_aco" interface="aQuestion3" role="abort">
			</bind>
			<bind component="cFinal4" interface="pFinal4" role="start">
			</bind>
		</link>
	</body>
</ncl>
