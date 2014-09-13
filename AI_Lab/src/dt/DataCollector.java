package dt;

import java.awt.Color;
import java.io.IOException;
import java.io.PrintStream;
import java.text.NumberFormat;
import java.util.Locale;

import robocode.AdvancedRobot;
import robocode.BulletHitBulletEvent;
import robocode.BulletHitEvent;
import robocode.BulletMissedEvent;
import robocode.DeathEvent;
import robocode.HitByBulletEvent;
import robocode.HitRobotEvent;
import robocode.RobocodeFileOutputStream;
import robocode.ScannedRobotEvent;
import robocode.WinEvent;
import robocode.util.Utils;

public class DataCollector extends AdvancedRobot {

	private double energy, heat, power, enemyEnergy, bHeight, bWidth, y, x;
	private String bulletHit, hitBy, distance, energyDown;
	PrintStream writer = null;
	private boolean overwrite, locked, moving;
	NumberFormat f;
	private int min, max;
	
    public void run() 
    {
    	locked = false;
    	moving = false;
    	power = 0.1;
    	enemyEnergy = 100;
    	min = 100;
    	max = 100;
    	bHeight = getBattleFieldHeight();
		bWidth = getBattleFieldWidth();
		distance = "?";
    	bulletHit = "?";
    	energyDown = "?";
    	hitBy = "?";
		overwrite = (getRoundNum() == 0) ? true : false;
    	f = NumberFormat.getNumberInstance(Locale.US);    
    	// Locale.US usa o formato correto para os numeros (10.1 ao inves de 10,1)
    	f.setMaximumFractionDigits(2);
    	
    	setColors(Color.orange, Color.orange, Color.red);
    	
    	setAdjustGunForRobotTurn(true);
    	setAdjustRadarForGunTurn(true);
    	setAdjustRadarForRobotTurn(true);
    	
    	setDebugProperty("Bullet Hit", bulletHit);
    	setDebugProperty("Hit By", hitBy);
    	setDebugProperty("Distance", distance);
    	
    	try {
			this.writer = new PrintStream(new RobocodeFileOutputStream(getDataFile("data.db").getAbsolutePath(),!overwrite));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
			
		if (overwrite)
		{
			String text = "robDTDB" + "\n" + 
						  "energy numerical " +
						  "heat numerical " +
						  "distance numerical " +
						  "enemyEnergy numerical " +
						  "energyDown symbolic " +
						  "bulletHit symbolic " +
						  "hitBy symbolic " +
						  "moving symbolic " +
						  "locked symbolic " +
						  "action symbolic";	
			
			writeToFile(text);
		}
    	
		setTurnRadarRight(Double.POSITIVE_INFINITY);
		
        while (true) 
        {
        	y = getY();
    		x = getX();
    		
    		if (!locked && getGunTurnRemaining() == 0 && getRadarTurnRemaining() == 0)
    			setTurnRadarRight(90);
    		
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
        	
        	if (getDistanceRemaining() == 0)
        		moving = false;
        	else
        		moving = true;
        }
    }
    
    public void onScannedRobot(ScannedRobotEvent e) {
//    	Nao precisa chamar execute neste metodo.
		this.distance = f.format(e.getDistance());
		
		if (e.getEnergy() < enemyEnergy)
			energyDown = "true";
		else
			energyDown = "false";
		
		this.enemyEnergy = e.getEnergy();

    	locked = false;
		
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
		{
			locked = true;
			setFire(power);
		}
//		else
//			out.println(getGunTurnRemaining() + " " + locked);
		
		collector();
    }
    
    public void onHitByBullet(HitByBulletEvent e)
    {
    	this.hitBy = "Bullet";
    	collector();
    }
    
    public void onHitRobot(HitRobotEvent e)
    {
    	this.hitBy = "Robot";    	
    	collector();
    }
    
    public void onBulletHit(BulletHitEvent e)
    {
    	this.bulletHit = "Robot";
    	collector();
    }
    
    public void onBulletMissed(BulletMissedEvent e)
    {
    	this.bulletHit = "Missed";
    	collector();
    }
    
    public void onBulletHitBullet(BulletHitBulletEvent e)
    {
    	this.bulletHit = "Bullet";
    	collector();
    }
    
    public void onDeath(DeathEvent e)    
    {
//    	out.println("Death " + getTime());
    	if (getRoundNum() == getNumRounds())
    		writer.print("\n");
    	if (writer != null) 
    		writer.close();    	
    }
    
    public void onWin(WinEvent e)
    {
//    	out.println("Win " + getTime());
    	if (getRoundNum() == getNumRounds())
    		writer.print("\n");
    	if (writer != null) 
    		writer.close();
    }
    
    public void collector()
    {
    	this.energy = getEnergy();
    	this.heat = getGunHeat();
    	
//    	if (energy <= goal)    	
//    	if (getTime() % 200 == 0)
    	if (energy < min || energy > max)
    	{
    		writeToFile("\n" + f.format(energy));
    		writeToFile(f.format(heat));
    		writeToFile(distance);
    		writeToFile(f.format(enemyEnergy));
    		writeToFile(energyDown);
    		writeToFile(bulletHit);
    		writeToFile(hitBy);
    		writeToFile(String.valueOf(moving));
    		writeToFile(String.valueOf(locked));
    		writeToFile("Acao");
    		
//	    	String txt = f.format(energy) + " " + 
//				 	   	 f.format(heat) + " " +
//				 	   	 distance + " " +
//				 	   	 f.format(enemyEnergy) + " " +
//				 	   	 bulletHit + " " +
////				 	   	 hitBy + " \n";
////	    				 Action nao pode ter somente valores indefinidos (para testar torna power o padrao pra todos)
//				 	   	 hitBy + " Acao \n";
//				 	   	 					 
//	    	
//	    	writeToFile(txt);
    		
    		if (energy < min)
    			min = (int) energy - 10;
    		
    		if (energy > max)
    			max = (int) energy + 10;
	    }

    	distance = "?";
    	bulletHit = "?";
    	energyDown = "?";
    	hitBy = "?";
    }
    
    public void writeToFile(String txt)
    {
//    	writer.append(txt);
    	writer.printf("%1$-10s", txt);
    }
}