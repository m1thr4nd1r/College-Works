class SiteController < ApplicationController
	def index
		@title = 'Página Inicial'
		render :action => 'index'
	end
end
