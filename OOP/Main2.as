package {
	
	import View.*;
	
	import flash.display.DisplayObject;
	import flash.display.Shape;
	import flash.display.Stage;
	
	public function Main2(stage:Stage):void{
		
		/* Fundo
		------------------------------*/
		function DrawBackground(width, height:int):DisplayObject{
			var me:Shape = new Shape();
			me.graphics.beginFill(0x00FF00);
			me.graphics.drawRect(0,0,width,height);
			me.graphics.endFill();
			return me;
		}
		
		/* Barra Superior
		------------------------------*/
		var magicPoints:SimpleBar = new SimpleBar(10, 10);
		var qntCrystal:TextArea = new TextArea(200, 10, "qntcristal");
		var lifePoints:TextArea = new TextArea(390, 10, "lifepoints");
		var score:TextArea = new TextArea(590, 10, "score");	
		
		drawObjects();
		
		score.setText = String(1);
		
		function drawObjects(){
			stage.addChildAt(DrawBackground(stage.stageWidth, stage.stageHeight), 0);
			stage.addChild(magicPoints);
			stage.addChild(qntCrystal);
			stage.addChild(lifePoints);
			stage.addChild(score);
		}
	}
}