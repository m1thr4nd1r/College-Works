package {
	
	import Door.Door;
	
	import Enemy.*;
	
	import View.*;
	
	import flash.display.DisplayObject;
	import flash.display.Shape;
	import flash.display.Stage;
	import flash.display.StageAlign;
	import flash.display.StageScaleMode;
	import flash.events.Event;
	import flash.media.scanHardware;
	
	public function main(stage:Stage):void{
		
		initStage(stage);
		
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
		var qntCrystal:TextArea = new TextArea(200, 10, "Cristais: ");
		var lifePoints:TextArea = new TextArea(390, 10, "LifePoints: ");
		var score:TextArea = new TextArea(590, 10, "Score: ");	
		
		/* Mapa
		------------------------------*/
		var map:Map = new Map(35, 20);
		
		/* Inimigos
		-----------------------------*/
		var enemies:Array = new Array(20);
		for (var i:int = 0; i < enemies.length; i++)
		{
			if ((i == 3) || (i == 6))
				enemies[i] = new E_Strong(map,10,10,"Fogo");
			//if ((i == 5) || (i == 7))
				//enemies[i] = new E_Fast(map,10,10,"Fogo");
			else
				enemies[i] = new E_Common(map,10,10,"Fogo");
		}
		/* Butões
		------------------------------*/
		var button:UserInterface = new UserInterface(0, 390, map, new BookButon(), new BookButon(), new BookButon());
		
		/* Porta
		------------------------------*/
		var pos:Array = map.getEnd();
		pos[0]*=50 - 2;
		pos[1]*=50 + 6;
		var door:Door = new Door(pos[1],pos[0]);

		drawObjects();
		
		function initStage(stage:Stage){
			stage.align = StageAlign.TOP_LEFT;
			stage.scaleMode = StageScaleMode.NO_SCALE;
		}
		
		function drawObjects(){
			stage.addChildAt(DrawBackground(stage.stageWidth, stage.stageHeight), 0);
			stage.addChild(magicPoints);
			stage.addChild(qntCrystal);
			stage.addChild(lifePoints);
			stage.addChild(score);
			stage.addChild(map);
			stage.addChild(button);
			stage.addChild(door);
			//var en:Enemy = new Enemy(map,10,10,10,10,"Fogo");
			//en.addEventListener(Event.ENTER_FRAME,en.update);
			//stage.addChild(en);
			
			// Codigo para (tentar) botar varios inimigos no mapa
			
			var count:int = 0;
			var time:int = 10;
			var limit:int = enemies.length
			while (count < limit)
			{
				if ((enemies[count] != null) && (time == 60))
				{
					stage.addChild(enemies[count]);
					time = 0;
					count++;
				}
				time++;
			}			
		}
	}
}