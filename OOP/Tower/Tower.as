package Tower
{
	import Enemy.Enemy;
	
	import flash.display.MovieClip;
	import flash.events.Event;
	
	public class Tower extends MovieClip
	{
		private var damage:int;
		private var rate:Number;
		private var range:int;
		private var element:String;
		//private var level:int;
		//private var life:int;
		//private var shield:int;		
		
		public function Tower(x, y, damage, range: int, rate:Number, element:String)
		{
			super();
			this.damage = damage;
			this.rate = rate;
			this.range = range;
			this.element = element;
			this.x = x;
			this.y = y;
			//this.addEventListener(Event.ENTER_FRAME,update);
		}
		
		public function attack(enemies:Array)
		{
			var i:int;
			for (i = 0; i < enemies.length; i++)
				if ((enemies[i] != null) && (this.isOnRange(enemies[i])))
					enemies[i]._life(enemies[i]._life() - damage);
		}
		
		public function isOnRange(enemy:Enemy.Enemy):Boolean
		{
			var x1:int = Math.abs(enemy._x - this.x);
			var y1:int = Math.abs(enemy._y - this.y);
			var dist:int = Math.sqrt(Math.pow(x1,2)+Math.pow(y1,2));
			if (dist < range)
				return true;
			return false;
		}
		
		public function setPosition(x , y: int):void
		{
			this.x = x;
			this.y = y;
		}
	}
}