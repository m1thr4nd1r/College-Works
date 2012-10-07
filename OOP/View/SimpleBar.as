package View {
	
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	
	/*Essa é a Classe um uma Barra de Estado, E quala Barra que mostra
	 *Um determinado Atributo de alguma coisa, no nosso caro seria a 
	 *quantidade de Cristal, e a quantidade de MP*/
	
	public class SimpleBar extends MovieClip{
		
		private var control:Class;
		private var method:String;
		private var minValue, maxValue, currentValue:int
		private var haveLimit:Boolean;
		
		public function SimpleBar(xPos:int, yPos:int, minValue = 0, maxValue:Number = 100, 
								  inMax = true, haveLimit:Boolean  = false):void{
			super();
			
			x = xPos;
			y = yPos;
			this.minValue = minValue;
			this.maxValue = maxValue;
			this.haveLimit = haveLimit;
			
			if(inMax)
				this.currentValue = maxValue;
			else
				this.currentValue = minValue;
			
			setValueAbsolute(this.currentValue);
			
			addEventListener(MouseEvent.CLICK, getClick);
			addEventListener(MouseEvent.MOUSE_OVER, getOver);	
		}
		
		public function setValueRelative(value:Number):Boolean{
			if((haveLimit && currentValue + value > maxValue) ||
				currentValue + value < minValue)
				return false;
			
			currentValue += value;
			gotoAndStop(calcFrame(currentValue));
			return true;
		}		
		
		public function setValueAbsolute(value:Number):Boolean{
			if((haveLimit && value > maxValue) || 
				value < minValue)
				return false;
			
			currentValue = value;
			gotoAndStop(calcFrame(currentValue));
			return true;
		}
		
		public function get getCurrentValue(){ return currentValue; }
		
		public function calcFrame(value:Number):int{
			return 50 - super.totalFrames*value /
						(maxValue - minValue);
		}
		
		public function getClick(e:MouseEvent):void{
			setValueRelative(-5);
		}
		
		public function getOver(e:MouseEvent):void{
			setValueRelative(5);
		}
		
	}
}