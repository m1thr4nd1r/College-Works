package Enemy
{
	import Door.Door;
	
	import flash.display.MovieClip;
	import flash.events.Event;
	
	public class E_Common extends Enemy
	{
		public function E_Common(map:Map, life:*, rate:int, element:String)
		{
			super(map, life, rate, element);
		}
		
		override public function update(e:Event)
		{
			super.update(e);
		}
		
		override public function isDead():Boolean
		{
			return super.isDead()
		}	
		
		override public function isOnRange(door:Door.Door):void
		{
			if (super.isOnRange(door))
				this.attack(door);
		}
		
		override public function attack(door:Door = null)
		{
			super.attack(door);
		}
	}
}