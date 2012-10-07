package View{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.display.Shape;
	
	/*Essa e um Classe "abstrata" para as Classe de Barra maiores, o Main dela 
	 * é sobrescrito, mas eu não sei se é nescessario :/ */
	
	public class Screen extends MovieClip{
		
		private var xPos, yPos, myWidth, myHeight:Number;
		
		public function Screen(x, y, width, height:Number):void{
			xPos = x;
			yPos = y;
			myWidth = width;
			myHeight = height;
		}
		
		public function drawObjects(obj:DisplayObject, nivel:Number = -1){
			(nivel == -1 ? addChild(obj) : addChildAt(obj,nivel));
		}
		
		public function main():void{};
		
		public function get _x():Number{return xPos;}
		public function get _y():Number{return yPos;}
		public function get _width():Number{return myWidth;}
		public function get _height():Number{return myHeight;}
	}
}