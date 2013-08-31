 PrimeFaces.locales['pt_BR'] = {  
    closeText: 'Fechar',  
    prevText: 'Anterior',  
    nextText: 'Próximo',  
    currentText: 'Come&ccedil;o',  
    monthNames: ['Janeiro','Fevereiro','Mar&ccedil;o','Abril','Maio','Junho','Julho','Agosto','Setembro','Outubro','Novembro','Dezembro'],  
    monthNamesShort: ['Jan','Fev','Mar','Abr','Mai','Jun', 'Jul','Ago','Set','Out','Nov','Dez'],  
    dayNames: ['Domingo','Segunda','Ter&ccedil;a','Quarta','Quinta','Sexta','S&aacute;bado'],  
    dayNamesShort: ['Dom','Seg','Ter','Qua','Qui','Sex','S&aacute;b'],  
    dayNamesMin: ['D','S','T','Q','Q','S','S'],  
    weekHeader: 'Semana',  
    firstDay: 1,  
    isRTL: false,  
    showMonthAfterYear: false,  
    yearSuffix: '',  
    timeOnlyTitle: 'S&oacute; Horas',  
    timeText: 'Tempo',  
    hourText: 'Hora',  
    minuteText: 'Minuto',  
    secondText: 'Segundo',  
    currentText: 'Data Atual',  
    ampm: false,  
    month: 'M&ecirc;s',  
    week: 'Semana',  
    day: 'Dia',  
    allDayText : 'Todo Dia'  
 };  

 function verifica(){

	 var rDialogo = $("#status_reserva");
	 if(rDialogo.is(":visible")){
		 rDialogo.css("max-height","800px");
	 }
	 else
	 {
		 rDialogo.css("max-height","50px");
	 }
	 
	 rDialogo = $("#add_reserva");
	 if(rDialogo.is(":visible")){
		 rDialogo.css("max-height","800px");
	 }
	 else
	 {
		 rDialogo.css("max-height","50px");
	 }
	 
 }
 
 $(document).ready(function(){
	 var close = $(".ui-dialog-titlebar-close");
	 
	 close.click(function(){
		 var dialogo = $(this).parent().parent().parent();
		 dialogo.css("max-height","50px");
	 });
	 
 });
 
 verifica();