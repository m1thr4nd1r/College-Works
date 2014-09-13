package nn;

import java.awt.Color;
import java.io.IOException;
import java.io.PrintStream;
import java.text.NumberFormat;
import java.util.Locale;

import robocode.AdvancedRobot;
import robocode.DeathEvent;
import robocode.RobocodeFileOutputStream;
import robocode.ScannedRobotEvent;
import robocode.WinEvent;
import robocode.util.Utils;

public class NNDataCollector extends AdvancedRobot {

	private double energy, enemyEnergy, distance, EX, EY;
	private int min, max;
	double y,x,bHeight,bWidth;
	PrintStream writer = null;
	NumberFormat f;
	
    public void run() 
    {    	
    	enemyEnergy = 100;
    	EX = 0;
    	EY = 0;
    	distance = 0;
    	min = 100;
    	max = 100;
    	f = NumberFormat.getNumberInstance(Locale.US);    
    	// Locale.US usa o formato correto para os numeros (10.1 ao inves de 10,1)
    	f.setMaximumFractionDigits(2);
    	bHeight = getBattleFieldHeight();
		bWidth = getBattleFieldWidth();
    	
    	setColors(Color.orange, Color.orange, Color.red);
    	
    	setAdjustGunForRobotTurn(true);
    	setAdjustRadarForGunTurn(true);
    	setAdjustRadarForRobotTurn(true);
    	
    	try {
			this.writer = new PrintStream(new RobocodeFileOutputStream(getDataFile("training.txt").getAbsolutePath(), true));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
			
		setTurnRadarRight(Double.POSITIVE_INFINITY);
		//writer.println("--------------------" + Integer.toString(getRoundNum()) + "--------------------");
		writer.println("");
		
        while (true) 
        {
        	y = getY();
    		x = getX();
    		
    		setTurnRight(90);
    		
    		int amount = 36;
    		double heading = getHeading();
    		
    		x += (heading > 0 && heading < 180)? amount : -amount;
    		y -= (heading > 90 && heading < 270)? amount : -amount;
    		
    		if (x > 36 && x < bWidth - 36 && y > 36 && y < bHeight - 36)
    			setAhead(amount);
    		else
    			setAhead(-amount * 3);    		
    		
    		execute();
        }
    }
    
    public void onScannedRobot(ScannedRobotEvent e) {
//    	Nao precisa chamar execute neste metodo.
		this.distance = e.getDistance();		
		this.enemyEnergy = e.getEnergy();
		
		double absBearing=e.getBearingRadians()+getHeadingRadians();
		
		EX=getX()+e.getDistance()*Math.sin(absBearing);
		EY=getY()+e.getDistance()*Math.cos(absBearing);

    	double radarTurn =
		        // Absolute bearing to target
				getHeadingRadians() + e.getBearingRadians()
		        // Subtract current radar heading to get turn required
				- getRadarHeadingRadians();

		setTurnRadarRightRadians(Utils.normalRelativeAngle(radarTurn));

		double gunTurn = 
				getHeadingRadians() + e.getBearingRadians()
				- getGunHeadingRadians();
		
		setTurnGunRightRadians(Utils.normalRelativeAngle(gunTurn));
		
		if (Math.abs(getGunTurnRemaining()) < 1)
			setFire(1);
		
		collector();
    }
    
    public void onDeath(DeathEvent e)    
    {
    	if (getRoundNum() == getNumRounds())
    		writer.print("\n");
    	if (writer != null) 
    		writer.close();    	
    }
    
    public void onWin(WinEvent e)
    {
    	if (getRoundNum() == getNumRounds())
    		writer.print("\n");
    	if (writer != null) 
    		writer.close();
    }
    
    public void collector()
    {
    	this.energy = getEnergy();
    	
    	if (energy < min || energy > max)
    	{
    		double hip = Math.sqrt(Math.pow(bHeight, 2) + Math.pow(bWidth, 2));
    		double diffX = getX() - EX;
    		double diffY = getY() - EY;
    		int pos = getPos();
    		
    		/* Offensive && Power2
    			writeToFile(f.format(energy / 100) + ",");
				writeToFile(f.format(distance / hip) + ",");
				writeToFile(f.format(enemyEnergy / 100) + "\n");		
    		*/
    		
    		/* Power
    			writeToFile(f.format(Math.random()) + ",");
    			writeToFile(f.format(energy / 100) + ",");
				writeToFile(f.format(distance / hip) + ",");
				writeToFile(f.format(enemyEnergy / 100) + "\n");		
		    */
    		
    		// Movement
    		writeToFile(f.format(diffX / bWidth) + ",");
    		writeToFile(f.format(diffY / bHeight) + ",");
			writeToFile(f.format(distance / hip) + ",");
			
			if (distance / hip  < 0.2)
			{
				if ((diffY > 0 || diffX > 0) && pos != 0)
					writeToFile(1 + ",");
				else
					writeToFile(0 + ",");
				
				if ((diffY > 0 || diffX < 0) && pos != 1)
					writeToFile(1 + ",");
				else
					writeToFile(0 + ",");
				
				if ((diffY < 0 || diffX < 0) && pos != 2)
					writeToFile(1 + ",");
				else
					writeToFile(0 + ",");
				
				if ((diffY < 0 || diffX > 0) && pos != 3)
					writeToFile(1 + ",");
				else
					writeToFile(0 + ",");
				
				writeToFile(0 + "\n");
			}
			else
				writeToFile(0 + "," + 0 + "," + 0 + "," + 0 + "," + 1 + "\n");
    		
    		distance = 0;
    		
	    	if (energy < min)
    			min = (int) energy - 10;
    		
    		if (energy > max)
    			max = (int) energy + 10;
    	}
    }
    
    public int getPos()
    {
    	double x = getX();
    	double y = getY();
    	int pos = -1;
    	
    	x = Math.round(x / (bWidth / 5));
    	if (x % 2 == 0)
    		x = Math.min(Math.max(x-1, 1), 3);
		
    	y = Math.round(y / (bHeight / 5));
    	if (y % 2 == 0)
    		y = Math.min(Math.max(y-1, 1), 3);
    	
    	if (x == 3 && y == 3)
    		pos = 0;
    	else if (x == 1 && y == 3)
    		pos = 1;
    	else if (x == 1 && y == 1)
    		pos = 2;
    	else if (x == 3 && y == 1)
    		pos = 3;    	
    	
    	System.out.println("x = " + x + " y = " + y + " pos = " + pos);
    	
    	return pos;
    }
    
    public void writeToFile(String txt)
    {
    	writer.printf(txt);
    }
}