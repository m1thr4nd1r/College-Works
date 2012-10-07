package Enemy
{
	import Door.Door;
	
	import fl.motion.Color;
	
	import flash.display.MovieClip;
	import flash.events.Event;
	
	public class Enemy extends MovieClip
	{
		protected static var damage:int;
		protected var map:Map;
		protected static var speed:int;
		protected var rate:int;
		protected var element:String;
		protected var life:int;
		//private var level:int;
		//private var rate:Number;
		//private var shield:int;
		
		public function Enemy(map:Map, life, rate:int, element:String)
		{
			super();
			Enemy.Enemy.damage = 2;
			Enemy.Enemy.speed = 4;
			this.rate = rate;
			this.element = element;
			this.life = life;
			this.map = map;
			var pos:Array = map.getStart();
			this.x = pos[1] * 50;
			this.y = pos[0] * 50;
			this.addEventListener(Event.ENTER_FRAME,update);
		}
		
		public function update(e:Event)
		{
			if (!isDead())
			{
				var pos = map.getEnd();
				pos[0]*=50;
				pos[1]*=50;
				pos[1]+=40;
				if ((this.x <= pos[1]) && (this.y <= pos[0]))
					this.x+= Enemy.Enemy.speed;
				else
					kill(this);
			}
			else
				kill(this);
		}
		
		public function kill(enemy:Enemy):void
		{
			this.removeEventListener(Event.ENTER_FRAME,update);
			this.parent.removeChild(enemy);
		}
				
		public function isDead():Boolean
		{
			if (this.life == 0)
				return true;
			return false;
		}	
		
		public function isOnRange(door:Door):void
		{
			var x:int = Math.abs(door._x - this.x);
			var y:int = Math.abs(door._y - this.y);
			var dist:int = Math.sqrt(Math.pow(x,2)+Math.pow(y,2));
		}
		
		public function attack(door:Door = null)
		{
			if (door != null)
				door._life = door._life - Enemy.Enemy.damage;
		}
		
		public function get _life():int {return this.life;}
		public function set _life(life:int) {this.life = life;}
		//public function get _speed():Number {return this.speed;}
		//pub/ic function get _damage():int {return this.damage;}
		public function get _x():int {return this.x;}
		public function get _y():int {return this.y;}
	}
}