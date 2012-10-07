package Door
{
	import flash.display.MovieClip;
	
	public class Door extends MovieClip
	{
		private var life:int;
		
		public function Door(x,y,life:int = 100)
		{
			super();
			this.x = x;
			this.y = y;
			this.life = life;
		}
		
		public function isBroken():Boolean
		{
			if (this.life == 0)
				return true;
			return false;
		}
		
		public function get _life():int {return this.life;}
		public function set _life(life:int) {this.life = life;}
		public function get _x():int {return this.x;}
		public function get _y():int {return this.y;}
	}
}