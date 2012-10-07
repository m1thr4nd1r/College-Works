package View
{
	import flash.display.MovieClip;
	
	public class TextArea extends MovieClip{
		
		public function TextArea(xPos, yPos:int, defaltText:String):void{
			super();
			x = xPos;
			y = yPos;
				
			this.text.text = defaltText;
		}

		public function set setText(text:Object):void{
			
			this.text.text = String(text);
		}
		
		public function get getText():String{
			return this.text.text;
		}
	}
}