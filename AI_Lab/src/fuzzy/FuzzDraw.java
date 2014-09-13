package fuzzy;

import net.sourceforge.jFuzzyLogic.FIS;
import net.sourceforge.jFuzzyLogic.FunctionBlock;
import net.sourceforge.jFuzzyLogic.Gpr;
import net.sourceforge.jFuzzyLogic.plot.JFuzzyChart;
import net.sourceforge.jFuzzyLogic.rule.Variable;

/**
 * Test parsing an FCL file
 * @author pcingola@users.sourceforge.net
 */
public class FuzzDraw {

	public static void main(String[] args) throws Exception {
		// Load from 'FCL' file
//		String fileName = "/home/m1thr4nd1r/Dropbox/Superior/Codigos/LabIA/data/Fuzzy/fuzzbot.fcl";
		String fileName = "D:\\Dropbox\\Superior\\Codigos\\Labia\\data\\Fuzzy\\fuzzbot.fcl";
		FIS fis = FIS.load(fileName, true);
		if (fis == null) { // Error while loading?
			System.err.println("Can't load file: '" + fileName + "'");
			return;
		}

		// Show ruleset
		FunctionBlock functionBlock = fis.getFunctionBlock("shoot");
		JFuzzyChart.get().chart(functionBlock);

		// Set inputs
		functionBlock.setVariable("energy", 96);
		functionBlock.setVariable("distance", 443.2 / 800);

		Variable p = functionBlock.getVariable("energy");
		
		Gpr.debug("energy[low]: " + p.getMembership("low"));
		Gpr.debug("energy[normal]: " + p.getMembership("normal"));
		Gpr.debug("energy[high]: " + p.getMembership("high"));
		
		p = functionBlock.getVariable("distance");
		
		Gpr.debug("distance[tiny]: " + p.getMembership("tiny"));
		Gpr.debug("distance[short]: " + p.getMembership("short"));
		Gpr.debug("distance[medium]: " + p.getMembership("medium"));
		Gpr.debug("distance[great]: " + p.getMembership("great"));
		Gpr.debug("distance[huge]: " + p.getMembership("huge"));
		
		// Evaluate 
		functionBlock.evaluate();

		// Show output variable's chart
		p = functionBlock.getVariable("power");
		JFuzzyChart.get().chart(p, p.getDefuzzifier(), true);
		
		Gpr.debug("power[minimum]: " + p.getMembership("minimum"));
		Gpr.debug("power[low]: " + p.getMembership("low"));
		Gpr.debug("power[normal]: " + p.getMembership("normal"));
		Gpr.debug("power[high]: " + p.getMembership("high"));
		Gpr.debug("power[maximum]: " + p.getMembership("maximum"));

		// Print ruleSet
//		System.out.println(functionBlock);
		System.out.println("Power:" + functionBlock.getVariable("power").getValue());
	}
}
