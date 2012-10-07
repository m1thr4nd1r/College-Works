package{
	
	import View.*;
	
	import flash.display.MovieClip;
		
	public class UserInterface extends MovieClip{
		
		var magicBooks:Array = new Array();
		var map:Map;
		
		public function UserInterface(xPos, yPos:int, map:Map, torre1 = null, torre2 = null, torre3 = null, 
						   torre4 = null, torre5 = null, torre6:BookButon = null):void{
			super();
			
			x = xPos;
			y = yPos;
			this.map = map;
			
			magicBooks[0] = torre1;
			magicBooks[1] = torre2;
			magicBooks[2] = torre3;
			magicBooks[3] = torre4;
			magicBooks[4] = torre5;
			magicBooks[5] = torre6;
			
			creatingButtons();
		}
		
		public function creatingButtons():void{
			for(var i:uint = 0; i < 6 && magicBooks[i] != null; i++){
				magicBooks[i].definePosition(i*80 + 10, 0);
				magicBooks[i].addMapInstance(map);
				this.addChild(magicBooks[i]);
			}
		}
	}
}