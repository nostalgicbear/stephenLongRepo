/**
 * @file        HappyWaysCrecheApp.java
 * @author      Stephen Long
 * @assignment  Creche
 *
 */
package ie.wit.abs;
import ie.wit.abs.CrecheManager;

public class HappyWaysCrecheApp {
 
	public static void main( String args[] )
   {
		//createAFile q = new createAFile();
		//q.openFile();
		int option;
		CrecheManager manager = new CrecheManager();
		   do {
		   option = manager.menuMain();
		   
		   	switch(option)
		   		{
		   	case 1  : manager.registerAPerson(manager.getCreche());
		   			  break;
		   	case 2  : manager.registerChildWithParent(manager.getCreche());
		   		  break;
		   	case 3  :  manager.listPersons();
		   		      break;		 
		   	case 4  : manager.listChildrenOfParents(manager.getCreche());
		   		break;	
		   	case 5: manager.calcTotalWeeklyFee(manager.getCreche());
		   		break;
		   	case 6:
		   		manager.findPerson(manager.getCreche());
		   		break;
		   	case 7: 
		   		manager.removeAPerson(manager.getCreche());
		   		break;
		   	case 8: manager.searchPerson(manager.getCreche());
		   	break;
		   	case 9 : 
		   	//	q.close();
		   		System.exit(0);	
		   	//default : break;
		   		}
		   } while(option != 9);
	   } 			
   }
