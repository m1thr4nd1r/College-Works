class SiteController < ApplicationController

	require 'rubygems'
	require 'json'
	require 'yaml'
	require 'net/http'
	require 'pp'
	require 'base64'
	#require 'httparty'

	@@base_url = "http://0.0.0.0:8080/services"
	
	def index

		@title = 'Página Inicial'
		@data = (params[:d]) ? Base64.decode64(params[:d]) : DateTime.now.strftime("%d/%m/%Y")
		
		@data = dataEn(@data)
		#puts YAML::dump(dataEn(@data))
		@reservas = reservas(@data)
		#puts YAML::dump(@reservas)
		@data = dataPtBR(@data)
		@salas = salas()
		labs = labsReservados();
		@labsRes = {}
		
		labs.each do|e,i|
			@labsRes[e['sala']['nome']] = {}
			@labsRes[e['sala']['nome']]['entregue'] = e['eChave'];
		end

		#Notifier.signup_email("euler.santana@yahoo.com").deliver
		
		respond_to do |format|
			format.html
			format.xml { render :xml => @reservas }
		end

	end

	def reservas(data)

		require 'open-uri'
		require 'json'

	   	url = "#{@@base_url}/reservas/#{data}" 
	   	#url = "#{base_url}/time"
		url = URI.parse(url)
	   	
	   	resp = Net::HTTP.get_response(url)
	   	dados = resp.body
		
	   	result = JSON.parse(dados)
		#puts YAML::dump(result)
	   	return result

	end

	def salas()

		require 'open-uri'
		require 'json'

	   	url = "#{@@base_url}/salas"
	   	
		url = URI.parse(url)
	   	
	   	resp = Net::HTTP.get_response(url)
	   	dados = resp.body
		
	   	result = JSON.parse(dados)
		#puts YAML::dump(result)
	   	return result

	end

	def labsReservados()

		require 'open-uri'
		require 'json'

	   	url = "#{@@base_url}/laboratorios"
	   	
		url = URI.parse(url)
	   	
	   	resp = Net::HTTP.get_response(url)
	   	dados = resp.body
		
	   	result = JSON.parse(dados)
		#puts YAML::dump(result)
	   	return result

	end

	def dataPtBR(data)
		month_names = [ "Janeiro",
					"Fevereiro",
					"Março",
					"Abril",
					"Maio",
					"Junho",
					"Julho",
					"Agosto",
					"Setembro",
					"Outubro",
					"Novembro",
					"Dezembro"]
	
		return data[8..9]+" de "+month_names[data[5..6].to_i-1]+" de "+data[0..3]
	end

	def dataEn(data)
		return data[6..10]+"-"+data[3..4]+"-"+data[0..1]
	end

end
