package fuzzy;
import java.awt.Color;
import java.io.IOException;
import java.util.Random;

import robocode.BulletHitBulletEvent;
import robocode.BulletHitEvent;
import robocode.BulletMissedEvent;
import robocode.DeathEvent;
import robocode.HitByBulletEvent;
import robocode.MessageEvent;
import robocode.ScannedRobotEvent;
import robocode.TeamRobot;
import robocode.WinEvent;
import robocode.util.Utils;
import net.sourceforge.jFuzzyLogic.FIS;
import net.sourceforge.jFuzzyLogic.FunctionBlock;
import net.sourceforge.jFuzzyLogic.rule.Variable;

public class FuzzBot extends TeamRobot {

	FunctionBlock functionBlockShoot, functionBlockSpeed, functionBlockMove;
	private double previousShot, lastShot;
	private double[][] teamPos, teamHeading;
	private String target, lastScanned;
	private String[] teammates;
	private int messageIndex, lastScan;
	private boolean teamMove, previousHit;
	Random rand;
	private double[] moveTarget;
	private boolean flocking;
	
	public void run()
	{
		setAdjustGunForRobotTurn(true);
    	setAdjustRadarForGunTurn(true);
    	setAdjustRadarForRobotTurn(true);
    	setColors(Color.black, Color.red, Color.white);

    	teammates = getTeammates();
    	teamHeading = new double[teammates.length][2];
    	teamPos = new double[teammates.length][2];
    	moveTarget = new double[2];
    	teamMove = false;
    	messageIndex = 0;
    	target = "";
		
    	previousHit = false;
		previousShot = 0;
		lastShot = 0;
		rand = new Random();
		
		try {
			sendMessage(getTeammates()[1], rand.nextInt(3));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		FIS fis = FIS.load(getDataFile("fuzzbot.fcl").getAbsolutePath(), true);
		if (fis == null) { // Error while loading?
			System.err.println("Can't load file: 'fuzzbot.fcl'");
			return;
		}

		// Show ruleset
		functionBlockShoot = fis.getFunctionBlock("shoot");
		functionBlockSpeed = fis.getFunctionBlock("velocity");
		functionBlockMove = fis.getFunctionBlock("moveType");	
		
		// Scan para dar tempo das mensagens chegarem
		scan();
		
		while (true)
		{
			lastScan++;
			if (lastScan > 5) // 35
				setTurnRadarRight(Double.POSITIVE_INFINITY);
						
			if (messageIndex > 0)
			{
				try {
					broadcastMessage("P" + getX() + " " + getY());
					broadcastMessage("H" + Math.cos(getHeading()) + " " + Math.sin(getHeading()));
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				
				if (flocking)
					flock();
				else
				{
					double x = (moveTarget[0] - getX() < 0) ? moveTarget[0] + 100 : moveTarget[0] - 100;
					double y = (moveTarget[1] - getY() < 0) ? moveTarget[1] + 100 : moveTarget[1] - 100;
					goTo(x,y);
				}
				System.out.println("d: " + moveTarget[0] + " " + moveTarget[1]);
			}		
			
			lastShot++;
			execute();
		}
	}
	
	public void onMessageReceived(MessageEvent event)
	{
		String msg = String.valueOf(event.getMessage());
		
		//System.out.println("Msg recebida em: " + getTime() + " | Conteudo: " + msg + " | De: " + event.getSender());
		
		if (messageIndex == 0 && event.getSender().equals(teammates[1]))
		{
			if (msg.contains("F"))
			{
				teamMove = true;
				flocking = true;					
			}
			else
				teamMove = Boolean.valueOf(msg);
			messageIndex++;
		}
		else if (messageIndex > 0)
		{
			if (msg.contains("P") || msg.contains("H") || msg.contains("T"))
			{
				char choice = msg.charAt(0);
				msg = msg.substring(1);
				int index = msg.indexOf(' ');
				double x = Double.valueOf(msg.substring(0, index));
				double y = Double.valueOf(msg.substring(index+1));
				
				int i = 0;
				while (!event.getSender().equals(teammates[i]))
					i++;
				
				if (choice == 'P')
				{
					teamPos[i][0] = x;
					teamPos[i][1] = y;
				}
				else if (choice == 'H')
				{
					teamHeading[i][0] = x;
					teamHeading[i][1] = y;
				}
				else
				{
					moveTarget[0] = x;
					moveTarget[1] = y;					
				}
			}
			else			
				target = msg;
		}	
	}
	
	public double[] separate()
	{
		double[] c = {0,0};  
        for (int i = 0; i < teammates.length; i++)
        	if (!teammates[i].equals(this.getName()))
        	{
        		double distance = Math.sqrt(Math.pow(teamPos[i][0] - getX(), 2) + Math.pow(teamPos[i][1] - getY(), 2));
        		if (distance < 300)
        		{
	        		c[0] -= (getX() - teamPos[i][0]);
	        		c[1] -= (getX() - teamPos[i][1]);
        		}
        	}
        return c;
	}
	
	public double[] cohere()
	{
		double[] c = {0,0};
		for (int i = 0; i < teammates.length; i++)
        	if (!teammates[i].equals(this.getName()))
        	{
        		c[0] += teamPos[i][0];
        		c[1] += teamPos[i][1];
        	}
		
		c[0] =  (c[0] / teammates.length - 1) - getX();
		c[1] =  (c[1] / teammates.length - 1) - getY();
		
		return c; // RETURN (c - this.position) / 100  
		
	}
	
	public double[] align()
	{
		double[] c = {0,0};
		for (int i = 0; i < teammates.length; i++)
        	if (!teammates[i].equals(this.getName()))
        	{
        		c[0] += teamHeading[i][0];
        		c[1] += teamHeading[i][1];
        	}
		
		c[0] =  (c[0] / teammates.length - 1) - getX();
		c[1] =  (c[1] / teammates.length - 1) - getY();
    
		return c; //  RETURN (c - this.velocity) / 8
	}
	
	public void flock()
	{
		double[] s,c,a,v = {0,0};
		
		s = separate();
		c = cohere();
		a = align();
		
		v[0] = s[0] + c[0] + a[0];
		v[1] = s[1] + c[1] + a[1];
		
		System.out.println("flock: " + (v[0] + getX()) + " " + (v[1] + getY()));
		
		goTo(Math.abs(getX() + v[0]), Math.abs(getY() + v[1]));
	}
	
	public void onScannedRobot(ScannedRobotEvent e) 
	{
		if (!isTeammate(e.getName()))
		{
			lastScan = 0;			
			
			if (!teamMove && e.getName().equals(lastScanned) && !lastScanned.equals(target))
			{
				setTurnRadarRight(Double.POSITIVE_INFINITY);
				System.out.println("o + " + lastScanned);
			}
			else
			{
				lastScanned = e.getName();
				if (teamMove || lastScanned.equals(target))
				{
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
					Variable type = null;
					
					if (getTurnRemaining() < 1 && getDistanceRemaining() < 1 && !teamMove)
					{
						functionBlockMove.setVariable("energy", this.getEnergy());
						functionBlockMove.setVariable("lastShot", getTime() - this.lastShot);
					
						functionBlockMove.evaluate();
					
						type = functionBlockMove.getVariable("type");
							
						if (type.getValue() > 2)
						{
							move();
							setTurnRadarRight(360);
						}
						else if (type.getValue() > 1)
						{
							setTurnRightRadians(Math.cos(e.getBearingRadians()));
							setAhead(4 * e.getVelocity());
						}
						else
						{		
							setTurnRightRadians(Utils.normalRelativeAngle(e.getHeadingRadians() - getHeadingRadians()));
							setAhead(e.getVelocity() * 1000);
							setMaxVelocity(Math.abs(e.getVelocity()));
						}
					}
					
					double distance = e.getDistance() / this.getBattleFieldWidth();
										
					// Set inputs
					functionBlockShoot.setVariable("energy", this.getEnergy());
					functionBlockShoot.setVariable("distance", (previousHit) ? distance - 0.3 : distance);
			
					// Evaluate 
					functionBlockShoot.evaluate();
					
					Variable power = functionBlockShoot.getVariable("power");
								
		//			if (type == null)
		//				System.out.println("Power: " + power.getValue() + " | Distance: " + e.getDistance());
		//			else
		//				System.out.println("Power: " + power.getValue() + " |  Type: " + type.getValue() + " | Distance: " + e.getDistance());
					
					if (power.getValue() <= 1)
						setBulletColor(Color.YELLOW);
					else if (power.getValue() <= 2)
						setBulletColor(Color.ORANGE);
					else
						setBulletColor(Color.RED);
					
					setFire(power.getValue());					
				}
			}
		}
	}
	
	public void goTo(double targetX, double targetY) {
		double x = getX();
		double y = getY();
        double distance = Math.sqrt(Math.pow(targetX - x, 2) + Math.pow(targetY - y, 2));
        double angle = normalRelativeAngle(absoluteBearing(targetX, targetY, x, y) - getHeading());
        if (Math.abs(angle) > 90.0) {
            distance *= -1.0;
            if (angle > 0.0) {
                angle -= 180.0;
            }
            else {
                angle += 180.0;
            }
        }
        setTurnRight(angle);
        setAhead(distance);
        
        //setTurnRight(Math.acos(teamHeading[1][0]) - getHeading());
    }
	
	public double absoluteBearing(double tX, double tY, double sX, double sY) {
        return Math.toDegrees(Math.atan2(tX - sX, tY - sY));
	}
	
	public double normalRelativeAngle(double angle) 
	{
		double relativeAngle = angle % 360;
		if (relativeAngle <= -180)
			return 180 + (relativeAngle % 180);
		else if (relativeAngle > 180)
			return -180 + (relativeAngle % 180);
		else
			return relativeAngle;
	}
	
	public void move()
	{
		double x = getX();
		double y = getY();
		double angle = rand.nextDouble() * 90;
		double amount;
		boolean flag = false;
		double bWidth = getBattleFieldWidth();
		double bHeight = getBattleFieldHeight();
		
		do
		{
			amount = rand.nextDouble() * bHeight / 2;
			
			if ( (x + amount < bWidth - 36) &&
				      (y - amount > 36) )
				// 4 quadrante
				angle += 270;
			else if ( (x - amount > 36) &&
				      (y - amount > 36) )
				// 2 quadrante
				angle += 90;
			else if ( (x - amount > 36) &&
					  (y + amount < bHeight - 36) )
				// 3 quadrante
				angle += 180;
			else if ( (x + amount < bWidth - 36) &&
					  (y + amount < bHeight - 36) )
				flag = true;
			
			execute();
		} while (angle > 90 || flag);
		
		if (Math.abs(angle - getHeading()) > 180)
			setTurnLeft(360 - angle + getHeading());
		else
			setTurnRight(angle - getHeading());
			
		setAhead(10);	

		// Set inputs
		functionBlockSpeed.setVariable("distance", amount / bHeight);

		// Evaluate 
		functionBlockSpeed.evaluate();
		
		Variable speed = functionBlockSpeed.getVariable("speed");
		
		setMaxVelocity(speed.getValue());
		
		System.out.println("Max Speed:" + speed.getValue());
	}
		
	public void onWin(WinEvent e)
	{
		System.out.println("MaxLastShot : " + previousShot);		
	}
	 
	public void onDeath(DeathEvent e)
	{
		System.out.println("MaxLastShot : " + previousShot);
	}
	 
	public void onBulletHit(BulletHitEvent e)
    {
    	this.previousHit = true;
    }
	
	public void onBulletMissed(BulletMissedEvent e)
    {
		this.previousHit = false;
    }
    
    public void onBulletHitBullet(BulletHitBulletEvent e)
    {
    	this.previousHit = false;
    }
    
    public void onHitByBullet(HitByBulletEvent e)
    {
    	double interval = getTime() - lastShot;
    	previousShot = Math.max(previousShot, interval);
    	lastShot = 0;
    }    
}