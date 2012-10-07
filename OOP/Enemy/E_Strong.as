package Enemy
{
	import Door.Door;
	
	import flash.display.MovieClip;
	import flash.events.Event;
	
	public class E_Strong extends Enemy
	{
		public function E_Strong(map:Map, life:*, rate:int,  element:String)
		{
			super(map, life, rate, element);
		}
		
		override public function update(e:Event)
		{
			if (!isDead())
			{
				var pos = map.getEnd();
				pos[0]*=50;
				pos[1]*=50;
				pos[1]+=40;
				if ((this.x <= pos[1]) && (this.y <= pos[0]))
				{
					this.x+= int(Enemy.Enemy.speed/2);
					trace("Velocidade Forte: " + Enemy.Enemy.speed/2)
					trace("X: " + this.x + " Final_X: " + pos[1] + " Y: " + this.y + " Final_Y: " + pos[0])
				}
				else
					super.kill(this);
			}
			else
				super.kill(this);			
		}
		
		override public function isDead():Boolean
		{
			return super.isDead();
		}	
		
		override public function isOnRange(door:Door.Door):void
		{
			super.isOnRange(door);
		}
		
		override public function attack(door:Door = null)
		{
			if (door != null)
				door._life = door._life - Enemy.Enemy.damage * 5;
		}
	}
}