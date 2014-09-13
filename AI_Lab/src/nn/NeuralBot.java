package nn;

import java.awt.Color;
import java.io.IOException;
import java.util.Random;

import org.neuroph.nnet.MultiLayerPerceptron;

import robocode.MessageEvent;
import robocode.RobotDeathEvent;
import robocode.ScannedRobotEvent;
import robocode.TeamRobot;
import robocode.util.Utils;

public class NeuralBot extends TeamRobot {

	private double hip, targetX, targetY, min;
	private double[][] teamPos, teamHeading;
	private String target;
	private String[] teammates;
	private Boolean teamMove;
	private int choice, votes, lastScan, scanned, enemies;
	private MultiLayerPerceptron power, movement;
	private int flocking;
		
	public void run()
	{	
		setAdjustGunForRobotTurn(true);
    	setAdjustRadarForGunTurn(true);
    	setAdjustRadarForRobotTurn(true);
    	setColors(Color.black, Color.red, Color.white);
    	
    	teammates = getTeammates();
    	teamHeading = new double[teammates.length][2];
    	teamPos = new double[teammates.length][2];
    	
    	teamMove = false;
    	votes = 0;
    	lastScan = 0;
    	hip = 0;
    	scanned = 0;
    	enemies = this.getOthers();
    	target = "";
    	min = 200;
    	targetX = 0; 
    	targetY = 0;
    	Random rand = new Random();
    	
    	int c = rand.nextInt(3);
    	
    	if (c == 0)
    		choice--;
    	else if (c == 1)
    	{
    		choice++;
    		flocking++;
    	}
    	else
    	{
    		choice++;
    		flocking--;
    	}    		
    	
    	hip = Math.sqrt(Math.pow(getBattleFieldHeight(), 2) + Math.pow(getBattleFieldWidth(), 2));
    	    	
		// load saved neural networks
		power = (MultiLayerPerceptron) MultiLayerPerceptron.createFromFile(getDataFile("Power2.nnet").getAbsolutePath());
		movement = (MultiLayerPerceptron) MultiLayerPerceptron.createFromFile(getDataFile("Movement.nnet").getAbsolutePath());
		
		// Scan para dar tempo das mensagens chegarem
		scan();
		
		String msg = "";		
		if (choice > 0)
			if (flocking > 0)
				msg = "trueF";
			else
				msg = "true";
		else
			msg = "false";
		
		teamMove = Boolean.valueOf(msg);

		try {
			broadcastMessage(teamMove);			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.println("Choice: " + choice + " | flocking: " + flocking + " | msg: " + msg + " | votes: " + votes);
		
		while (true)
		{
			lastScan++;
			if (lastScan > 5) // 35
				setTurnRadarRight(Double.POSITIVE_INFINITY);
			
			try {
				broadcastMessage("P" + getX() + " " + getY());
				broadcastMessage("H" + Math.cos(getHeading()) + " " + Math.sin(getHeading()));
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
						
			execute();
		}
	}
	
	public void onScannedRobot(ScannedRobotEvent e) 
	{
		if (!isTeammate(e.getName()))
		{
			if (!teamMove)
			{
				if (scanned < enemies)
				{
					scanned++;
					if (e.getEnergy() < min)
					{
						target = e.getName();
						min = e.getEnergy();
						System.out.println("Alvo: " + target);
					}
					setTurnRadarRight(Double.POSITIVE_INFINITY);
				}
				
				if (scanned == enemies)
				{
					try {
						broadcastMessage(target);
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					scanned++;
				}
			}
				
			if ((e.getName().equals(target) && scanned > enemies) || teamMove) 
			{			
//				---------- Mantendo a mira no inimigo ---------- 
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
		
//				--------------------------------------------------
		
//				Momento de ultimo scaneamento do inimigo (evita que o mesmo seja perdido)
				lastScan = 0;
	
				double energy = this.getEnergy() / 100;
				double distance = e.getDistance() / hip;
				double enemyEnergy = e.getEnergy() / 100;
				
				double absBearing=e.getBearingRadians()+getHeadingRadians();
				double EX=getX()+e.getDistance()*Math.sin(absBearing);
				double EY=getY()+e.getDistance()*Math.cos(absBearing);
				
				//System.out.println("Energy: " + energy + " | Distance: " + distance + " | EEnergy: " + enemyEnergy);
				
				power.setInput(energy, distance, enemyEnergy);		
				power.calculate();
				
				//double[] networkOutput = power.getOutput(); 
				//System.out.println("Output: " + networkOutput[0] +" | "+ networkOutput[1] + " | " + networkOutput[2] + " | " + networkOutput[3]);
				
				int max = getMax(power.getOutput());
				if (max == 0)
				{
					setBulletColor(Color.YELLOW);
					//System.out.println("AAAMMMMMMMMMAAAAAAARRRRREEEEEELLLLLOOOOOOO");
					setFire(1);			
				}
				else if (max == 1)
				{
					setBulletColor(Color.ORANGE);
					setFire(2);
				}
				else if (max == 2)
				{
					setBulletColor(Color.RED);
					setFire(3);
				}
				
				movement.setInput((getX() - EX) / getWidth(), (getY() - EY) / getHeight(), distance);
				movement.calculate();
				
				int pos = getMin(movement.getOutput());
				
				if (pos < 4 && getDistanceRemaining() < 0.5)
				{
					assignTarget(pos);
					//System.out.println("x = " + getX() + " y = " + getY() + " tX = " + targetX + " tY = " + targetY + " pos = " + pos);
					if (!teamMove)
						goTo(targetX, targetY);
					else if (flocking > 1)
						flock();
					else
						goTo_bck();
				}								
			}
		}
	}
	
	public void onRobotDeath(RobotDeathEvent event)
	{
		if (!isTeammate(event.getName()))
		{
	    	scanned = 0;
	    	min = 200;
	    	enemies = this.getOthers();
		}
	}
	
	public void assignTarget(int pos) 
	{
		double baseX = getBattleFieldWidth() / 5;
		double baseY = getBattleFieldHeight() / 5;
		
		if (pos == 0)
		{
			targetX = 3 * baseX; 
			targetY = 3 * baseY;
		}	
		else if (pos == 1)
		{
			targetX = 1 * baseX; 
			targetY = 3 * baseY; 
		}
		else if (pos == 2)
		{
			targetX = 1 * baseX; 
			targetY = 1 * baseY;
		}
		else if (pos == 3)
		{
			targetX = 3 * baseX; 
			targetY = 1 * baseY;
		}
		
		try {
			broadcastMessage("T" + targetX + " " + targetY);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public int getMax(double[] output) 
	{
		int max = output.length - 1;
		for (int i = output.length - 2; i > -1; i--)
			if (output[i] > output[max])
				max = i;
		
		return max;				
	}

	public int getMin(double[] output) 
	{
		int min = 0;
		for (int i = 1; i < output.length; i++)
			if (output[i] < output[min])
				min = i;
			
		return min;
	}
	
	public void goTo_bck() 
	{
		double x = getX();
		double y = getY();
        double distance = Math.sqrt(Math.pow(targetX - x, 2) + Math.pow(targetY - y, 2));
        double relativeAngle = (Math.toDegrees(Math.atan2(targetX - x, targetY - y)) - getHeading()) % 360;
        double angle = 0;
        
        if (relativeAngle <= -180)
            angle = 180 + (relativeAngle % 180);
        else if (relativeAngle > 180)
            angle = -180 + (relativeAngle % 180);
        else
            angle = relativeAngle;
        
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
	
	public void onMessageReceived(MessageEvent event)
	{
		String msg = String.valueOf(event.getMessage());
		
		if (msg.equals("0"))
		{
			choice--;
			votes++;
		}
		else if (msg.equals("1"))
		{
			choice++;
			flocking++;
			votes++;
		}
		else if (msg.equals("2"))
		{
			choice++;
			flocking--;
			votes++;
		}
		else if (msg.contains("P") || (msg.contains("H")))
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
			else
			{
				teamHeading[i][0] = x;
				teamHeading[i][1] = y;
			}
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
		
		goTo(Math.abs(getX() + v[0]), Math.abs(getY() + v[1]));
	}
}