class ReservasController < ApplicationController
	def index
		@title = 'Página Inicial'
		@reservas = Reserva.find(:all)

		respond_to do |format|
			format.html
			format.xml { render :xml => @reservas }
		end

		render :action => 'index'
	end
end
