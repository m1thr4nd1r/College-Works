package{
	
	import Tower.Tower;
	
	import flash.display.Shader;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.MouseEvent;
	
	public class Map extends Sprite{

		private static var D:String = "DOWN";
		private static var U:String = "UP";
		private static var L:String = "LEFT";
		private static var R:String = "RIGTH";
		private static var S:String = "START";
		private static var E:String = "END";
		private static var tamSlices:uint = 50;
		
		private var map:Array = new Array();
		private var newTower:Tower = null;
		private var areaActive:Shape = new Shape();
		
		public function Map(xPos, yPos:int):void{
			x = xPos;
			y = yPos;
			
			map = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				   S, 1, 1, 1, 1, 1, 1, 1, 1, E,
				   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				   0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
			
			areaActive.graphics.beginFill(0x00DD33);
			areaActive.alpha = 0;
			areaActive.graphics.drawRect(0,0, tamSlices, tamSlices);
			areaActive.graphics.endFill();
			this.addChild(areaActive);
			
			drawMap();
			
			this.addEventListener(MouseEvent.CLICK, makeATower);
			this.addEventListener(MouseEvent.MOUSE_MOVE, waitMakeATower);
		}
		
		public function getStart():Array{
			for(var i:int = 0; i < map.length; i++)
				if (map[i] == S)
					return [i/10 + 1, i%10 + 1];
			return [-1, -1];
		}
		
		public function getEnd():Array{
			for(var i:int = 0; i < map.length; i++)
				if (map[i] == E)
					return [int (i/10) + 1, int(i%10) + 1];
			return [-1,-1];
		}
		
		public function getPosMap(x, y:uint):String{
			return String(map[x*10 + y]);
		}
		 
		public function drawMap(){
			
			for(var i:uint = 0; i < 7; i++){
				for(var j:uint = 0; j < 10; j++){
					
					if(map[i*10 + j] == 0){
						var slice:Shape = new Shape();
						slice.graphics.beginFill(0x999999);
						slice.graphics.drawRect(x+tamSlices*j, y+tamSlices*i, tamSlices, tamSlices);
						slice.graphics.endFill();
						this.addChildAt(slice,0);
					
					}else if(map[i*10 + j] == 1 || map[i*10 + j] is String){
						var area:Shape = new Shape();
						area.graphics.beginFill(0xFFD173);
						area.graphics.drawRect(x+tamSlices*j, y+tamSlices*i, tamSlices, tamSlices);
						area.graphics.endFill();
						this.addChildAt(area,0);
					}
				}
			}		
		}
		
		public function addTorre(tower:Tower):void{
			this.newTower = tower;
		}
		
		public function makeATower(e:MouseEvent):void{
			if(newTower != null){
				
				var ySliceCoo:uint = (e.localY -y)/tamSlices;
				var xSliceCoo:uint = (e.localX -x)/tamSlices;
				
				if(map[ySliceCoo*10 + xSliceCoo] == 0){
					areaActive.alpha = 0;
					var aTower:Tower = Tower(newTower);
					aTower.setPosition(x + xSliceCoo*tamSlices, y + ySliceCoo*tamSlices);
					this.addChild(aTower);
					newTower = null;
					map[ySliceCoo*10 + xSliceCoo] = 2;
				}
			}
		}
		
		public function waitMakeATower(e:MouseEvent){
			if(newTower != null){
			var ySliceCoo:uint = (mouseY -y)/tamSlices;
				var xSliceCoo:uint = (mouseX -x)/tamSlices;
					
				if(map[ySliceCoo*10 + xSliceCoo] == 0){
					areaActive.alpha = 1;
					areaActive.x = x + xSliceCoo*tamSlices; 
					areaActive.y = y + ySliceCoo*tamSlices;
				}else{
					areaActive.alpha = 0;
					areaActive.x = -tamSlices;
					areaActive.y = -tamSlices;
				}
			}
		}
	}
}