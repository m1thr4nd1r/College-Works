package View{
	import Tower.*;
	
	import flash.display.DisplayObject;
	import flash.display.SimpleButton;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.text.TextField;
	
	public class BookButon extends SimpleButton{
			
		var map:Map;
		
		public function BookButon(upState = null, overState = null, downState = null, hitTestState :DisplayObject=null){
			
			super(upState, overState, downState, hitTestState);			
			this.addEventListener(MouseEvent.CLICK, mouseClicked);
		}
		
		public function definePosition(xPos, yPos:int){
			
			x = xPos;
			y = yPos;
		}
		
		public function addMapInstance(map:Map){
			this.map = map;
		}
		
		public function mouseClicked(e:MouseEvent){
			map.addTorre(new Tower(mouseX, mouseY, 10, 2, 20, "Fogo"));
		}
		
		/*public function mouseMoved(e:MouseEvent){
			this.addEventListener(Event.ENTER_FRAME, 
				function (newE:Event){
					var text:TextField = new TextField();
					traceName(e, text);
			});
		}
		
		public function traceName(e:MouseEvent, text:TextField){
			if(e.type == MouseEvent.MOUSE_OVER){
				text.x = e.localX;
				text.y = e.localY;
			}else{
				this.removeEventListener(Event.ENTER_FRAME, 
					function (newE:Event){
						var text:TextField = new TextField();
						traceName(e, text);
				});
			}
		}*/
	}
}