package test;

import java.awt.event.KeyEvent;

import static java.awt.event.KeyEvent.*;
import robocode.ScannedRobotEvent;
import robocode.TeamRobot;

public class Test extends TeamRobot {
	
	double bHeight, bWidth, y, x;
	
	public void run()
	{
		bHeight = getBattleFieldHeight();
		bWidth = getBattleFieldWidth();
		
		goTo(bWidth / 2, bHeight / 2);
		
		while (true)
		{
			//broadcastMessage("T" + Math.cos(getHeading()) + " " + Math.sin(getHeading()));
			scan();
		}		
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
	
	public void onScannedRobot(ScannedRobotEvent e) 
	{
		
	}	
		
	public void onKeyPressed(KeyEvent e) 
	{
		if (e.getKeyCode() == VK_ENTER)
			scan();
		else if (e.getKeyCode() == VK_CONTROL)
			execute();
		else if (e.getKeyCode() == VK_SPACE)
			execute();
	}
}