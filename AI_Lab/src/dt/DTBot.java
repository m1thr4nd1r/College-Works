package dt;

import robocode.BulletHitBulletEvent;
import robocode.BulletHitEvent;
import robocode.BulletMissedEvent;
import robocode.HitByBulletEvent;
import robocode.HitRobotEvent;
import robocode.MessageEvent;
import robocode.ScannedRobotEvent;
import robocode.TeamRobot;
import robocode.util.Utils;

import java.awt.Color;
import java.io.*;
import java.text.NumberFormat;
import java.util.*;

import be.ac.ulg.montefiore.run.jadti.Attribute;
import be.ac.ulg.montefiore.run.jadti.AttributeSet;
import be.ac.ulg.montefiore.run.jadti.AttributeValue;
import be.ac.ulg.montefiore.run.jadti.DecisionTree;
import be.ac.ulg.montefiore.run.jadti.DecisionTreeBuilder;
import be.ac.ulg.montefiore.run.jadti.FileFormatException;
import be.ac.ulg.montefiore.run.jadti.Item;
import be.ac.ulg.montefiore.run.jadti.ItemSet;
import be.ac.ulg.montefiore.run.jadti.KnownNumericalValue;
import be.ac.ulg.montefiore.run.jadti.KnownSymbolicValue;
import be.ac.ulg.montefiore.run.jadti.NumericalValue;
import be.ac.ulg.montefiore.run.jadti.SymbolicAttribute;
import be.ac.ulg.montefiore.run.jadti.SymbolicValue;
import be.ac.ulg.montefiore.run.jadti.UnknownNumericalValue;
import be.ac.ulg.montefiore.run.jadti.UnknownSymbolicValue;
import be.ac.ulg.montefiore.run.jadti.io.ItemSetReader;

public class DTBot extends TeamRobot {

	private double energy, heat, bHeight, bWidth, y, x, enemyEnergy;
	private double[][] teamPos, teamHeading;
	private String bulletHit, hitBy, distance, energyDown, target;
	private String[] teammates;
	private boolean active, locked, moving, teamMove;
	private int lastScan, messageIndex;
	private Object lastScanned;
	NumberFormat f;
	DecisionTree tree;
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
    	messageIndex = 0;
    	teamMove = false;
    	flocking = false;
    	
    	locked = false;
    	moving = false;    	
    	enemyEnergy = 100;
    	active = true;
		locked = false;
		bHeight = getBattleFieldHeight();
		bWidth = getBattleFieldWidth();
		bulletHit = "?";
		hitBy = "?";
		distance = "?";
		energyDown = "?";
		Random rand = new Random();
				
		try {
			sendMessage(teammates[1], rand.nextInt(3));
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		f = NumberFormat.getNumberInstance(Locale.US);    
    	// Locale.US usa o formato correto para os numeros (10.1 ao inves de 10,1)
    	f.setMaximumFractionDigits(2);
    	
    	KnownSymbolicValue guessedGoalAttributeValue = null;
    	SymbolicAttribute goalAttribute = startRobot();
    	
		// Scan para dar tempo das mensagens chegarem
    	scan();
    	
//    	goTo(teamPos[1][0],teamPos[1][1]);
    	
    	while(true)
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
			}		
			
    		if (getDistanceRemaining() == 0)
    			moving = false;
    		
    		if (active)
    		{
    			String result = think(guessedGoalAttributeValue, goalAttribute);
    			//out.println(result);
    			act(result);
    		}    		
    		execute();
		}
    }
	
	public void onMessageReceived(MessageEvent event)
	{
		String msg = String.valueOf(event.getMessage());
		
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
		
		System.out.println("Msg recebida em: " + getTime() + " | Team: " + teamMove + " | Target: " + target);
	}	
	
	private void goTo(double targetX, double targetY) {
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
	
	private double absoluteBearing(double tX, double tY, double sX, double sY) {
        return Math.toDegrees(Math.atan2(tX - sX, tY - sY));
	}
		
	private double normalRelativeAngle(double angle) 
	{
		double relativeAngle = angle % 360;
		if (relativeAngle <= -180)
			return 180 + (relativeAngle % 180);
		else if (relativeAngle > 180)
			return -180 + (relativeAngle % 180);
		else
			return relativeAngle;
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
			if (!teamMove && e.getName().equals(lastScanned) && !lastScanned.equals(target) && teammates.length != 0)
				setTurnRadarRight(Double.POSITIVE_INFINITY);
			else
			{
				lastScanned = e.getName();
				if (teamMove || lastScanned.equals(target))
				{
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
						locked = true;
				}
			}
		}
	}
	
	public void act(String action)
	{
		if (action.equals("Fire"))
		{
			setBulletColor(Color.ORANGE);
			setFire(1.0);
		}
		else if (action.equals("FireStrong"))
		{
			setBulletColor(Color.RED);
			setFire(1.5);
		}
		else if (action.equals("FireWeak"))
		{
			setBulletColor(Color.YELLOW);
			setFire(0.5);
		}
		else if (action.equals("Move") && !teamMove)
			move();
		else if (action.contains("Aim"))	
			setTurnRadarLeft(360);
		
		execute();
		active = true;		
	}
	
	public String think(KnownSymbolicValue guessedGoalAttributeValue, SymbolicAttribute goalAttribute)
	{
		active = false;
		Item i = null;
	
		i = createItem();
		guessedGoalAttributeValue = tree.guessGoalAttribute(i);
		return  goalAttribute.valueToString(guessedGoalAttributeValue);
	}
	
	public Item createItem()
	{
		NumericalValue e = new KnownNumericalValue(energy);
		NumericalValue he = new KnownNumericalValue(heat);
		
		NumericalValue d;
		if (distance.equals("?"))
			d = new UnknownNumericalValue();
		else
			d = new KnownNumericalValue(Double.valueOf(distance));
		
		NumericalValue eEnemy = new KnownNumericalValue(enemyEnergy);
		
		SymbolicValue eDown = null;
		if (energyDown.equals("?"))
			eDown = new UnknownSymbolicValue();
		else if (energyDown.equals("False"))
			eDown = new KnownSymbolicValue(0);
		else if (energyDown.equals("True"))
			eDown = new KnownSymbolicValue(1);
		
		SymbolicValue b = null;
		if (bulletHit.equals("?"))
			b = new UnknownSymbolicValue();
		else if (bulletHit.equals("Bullet"))
			b = new KnownSymbolicValue(2);
		else if (bulletHit.equals("Robot"))
			b = new KnownSymbolicValue(0);
		else if (bulletHit.equals("Missed"))
			b = new KnownSymbolicValue(1);
		
		SymbolicValue hi = null;
		if (hitBy.equals("?"))
			hi = new UnknownSymbolicValue();
		else if (hitBy.equals("Bullet"))
			hi = new KnownSymbolicValue(0);
		else if (hitBy.equals("Robot"))
			hi = new KnownSymbolicValue(1);
		
		SymbolicValue m;
		if (moving)
			m = new KnownSymbolicValue(0);
		else
			m = new KnownSymbolicValue(1);
		
		SymbolicValue l;
		if (locked)
			l = new KnownSymbolicValue(0);
		else
			l = new KnownSymbolicValue(1);
		
		AttributeValue a[] = {e, he, d, eEnemy, eDown, b, hi, m, l};
		
		return new Item(a);
	}
	
	public void move()
	{
		y = getY();
		x = getX();
		
		Random r = new Random();
		int amount = 36;
		
//		setTurnRight(90 * direction);
		
		double heading = getHeading();
		
		x += (heading > 0 && heading < 180)? amount : -amount;
		y -= (heading > 90 && heading < 270)? amount : -amount;
		
		if (x > 36 && x < bWidth - 36 && y > 36 && y < bHeight - 36)
			setAhead(amount);
		else
		{
			setAhead(-amount);
			setTurnRight(r.nextDouble() * 90 + 45);
		}
		
		moving = true;
				
//		execute();
	}
	
	public SymbolicAttribute startRobot()
	{
		ItemSet learningSet = null;
	
		try {
		    learningSet = ItemSetReader.read(new FileReader(getDataFile("data.db")));
		}
		catch(FileNotFoundException e) {
			e.printStackTrace();
		} catch (FileFormatException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		if (learningSet != null)
		{
			AttributeSet attributeSet = learningSet.attributeSet();
			
			Vector<Attribute> testAttributesVector = new Vector<Attribute>();
			testAttributesVector.add(attributeSet.findByName("energy"));
			testAttributesVector.add(attributeSet.findByName("heat"));
			testAttributesVector.add(attributeSet.findByName("distance"));
			testAttributesVector.add(attributeSet.findByName("enemyEnergy"));
			testAttributesVector.add(attributeSet.findByName("energyDown"));
			testAttributesVector.add(attributeSet.findByName("bulletHit"));
			testAttributesVector.add(attributeSet.findByName("hitBy"));
			testAttributesVector.add(attributeSet.findByName("moving"));
			testAttributesVector.add(attributeSet.findByName("locked"));
			
			AttributeSet testAttributes = new AttributeSet(testAttributesVector);
			SymbolicAttribute goalAttribute =
			    (SymbolicAttribute) learningSet.attributeSet().findByName("action");
		
			this.tree = buildTree(learningSet, testAttributes,
						      goalAttribute);
			
			return goalAttribute;
		}
		return null;
	}
	
	public void onHitByBullet(HitByBulletEvent e)
    {
		this.energy = getEnergy();
    	this.hitBy = "Bullet";
    }
    
    public void onHitRobot(HitRobotEvent e)
    {
    	this.energy = getEnergy();
    	this.hitBy = "Robot";
    }
    
    public void onBulletHitRobot(BulletHitEvent e)
    {
    	this.energy = getEnergy();
    	heat = getGunHeat();
		this.bulletHit = "Robot";
    }
    
    public void onBulletMissed(BulletMissedEvent e)
    {
    	this.energy = getEnergy();
    	heat = getGunHeat();
    	this.bulletHit = "Missed";
    }
    
    public void onBulletHitBullet(BulletHitBulletEvent e)
    {
    	this.energy = getEnergy();
    	heat = getGunHeat();
    	this.bulletHit = "Bullet";
    }
	
    /*
     * Build the decision tree.
     */
    static private DecisionTree buildTree(ItemSet learningSet, 
					  AttributeSet testAttributes, 
					  SymbolicAttribute goalAttribute) {
	DecisionTreeBuilder builder = 
	    new DecisionTreeBuilder(learningSet, testAttributes,
				    goalAttribute);
	
	return builder.build().decisionTree();
    }
}
