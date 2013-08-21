class ReservaController < ApplicationController
	def index
		@data = params[:d]

		respond_to do |format|
			format.html
			format.xml { render :xml => @data }
		end
	end
end
