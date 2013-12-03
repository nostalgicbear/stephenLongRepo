package implementation_package;

public class Fixture {
	private Team home, away;
	private int week, homeScore, awayScore, id;
	
	//Constructor
	public Fixture(Team home, Team away, int week, int id){
		this.home = home;
		this.away = away;
		this.week = week;
		this.id = id;
	}

	//Getters and Setters
	public Team getHome() {
		return home;
	}

	public Team getAway() {
		return away;
	}

	public int getWeek() {
		return week;
	}

	public int getHomeScore() {
		return homeScore;
	}

	public void setHomeScore(int homeScore) {
		this.homeScore = homeScore;
	}

	public int getAwayScore() {
		return awayScore;
	}

	public void setAwayScore(int awayScore) {
		this.awayScore = awayScore;
	}
/*
 * calculate who should win based on form, table position,
 *  manager, key player, goal difference and home team 
 *  record score based on goal difference
 */
	public void predict() {
		int hTeam = 1,aTeam = 0;
		float hForm=0,aForm=0;
		char hfrm[] =home.getForm(), afrm[] =away.getForm();
		//test goal difference
		//if goal difference between sides is greater than 30 award 2 points
		if (home.getGoalDif()>= away.getGoalDif())
			if(home.getGoalDif()-away.getGoalDif()>30)
				hTeam+=2;
			else
				hTeam++;
		else
			if(home.getGoalDif()-away.getGoalDif()<-30)
				aTeam+=2;
			else
				aTeam++;
		//test key player
		if(home.getKeyPlayer().getRating() > away.getKeyPlayer().getRating())
			hTeam++;
		else 
			aTeam++;
		//test manager
		if(home.getManager().getRating()> away.getManager().getRating())
			hTeam++;
		else 
			aTeam++;
		//test form
		for(int i =0; i<6;i++){
			if(hfrm[i]=='W')
				hForm+=3;
			else if(hfrm[i]=='D')
				hForm++;
			if(afrm[i]=='W')
				aForm+=3;
			else if(afrm[i]=='D')
				aForm++;
		}
		hForm =hForm/18*100;
		aForm=(aForm/18)*100;
		hForm=(hForm +(100-aForm))/2;
		if(hForm>60)
			hTeam++;
		else if(hForm<40)
			aTeam++;
		//test points total
		if(home.getPoints()>away.getPoints())
			hTeam++;
		else if(home.getPoints()<away.getPoints())
			aTeam++;
		//predict score
		
		//
		//home win
		//
		if (hTeam>aTeam+1){
			//home team score
			if(home.getGoalDif()>50)
				homeScore=4;
			else if(home.getGoalDif()>30)
				homeScore=3;
			else if(home.getGoalDif()>20)
				homeScore=2;
			else 
				homeScore=1;
			//away team score
			if(away.getGoalDif()>30){
				if (home.getGoalDif()>50){
					awayScore=2;
					homeScore =3;
				}
					
				else if(home.getGoalDif()>30)
				{
					homeScore=1;
					awayScore=0;
				}
				else if(home.getGoalDif()>20)
					awayScore=1;
			}
			else if(away.getGoalDif()>20)
				if (home.getGoalDif()>50)
					awayScore=2;
				else if (home.getGoalDif()>30)
				awayScore=1;
			
		}
		
		//
		//away win
		//
		else if(hTeam+1<aTeam){
			//away score
			if(away.getGoalDif()>40)
				awayScore=4;
			else if(away.getGoalDif()>30)
				awayScore=3;
			else if(away.getGoalDif()>20)
				awayScore=2;
			else 
				awayScore=1;
			//home score
			if(home.getGoalDif()>30){
				if (away.getGoalDif()>40){
					awayScore=2;
					homeScore=1;
				}
					
				else if(away.getGoalDif()>30){
					awayScore =1;
					homeScore=0;
				}
				else if(away.getGoalDif()>20)
					homeScore=1;
			}
			else if(home.getGoalDif()>20)
				if (away.getGoalDif()>40)
					homeScore=2;
				else if (away.getGoalDif()>30)
				homeScore=1;
		}
		//
		//draw
		//
		else if(hTeam+1==aTeam||hTeam==aTeam+1)
			if(home.getGoalDif()+away.getGoalDif()>40)
				homeScore =awayScore=3;
			else if(home.getGoalDif()+away.getGoalDif()>30)
				homeScore =awayScore=2;
			else if(home.getGoalDif()+away.getGoalDif()>20)
				homeScore =awayScore=1;
			else 
				homeScore =awayScore=0;
			
		System.out.println(home.getName()+" "+homeScore+" - "+awayScore+" "+away.getName());
		
	}
	
	/*
	 * Used to complete a fixture between two teams and update the corresponding information
	 */	
	
	public void completeFixture(int homeScore, int awayScore){
		char[] hForm=home.getForm(),aForm=away.getForm();
		for(int i=0;i<5;i++){
			hForm[i]=hForm[i+1];
			aForm[i]=aForm[i+1];
		}
			
		
			
		if(homeScore > awayScore){
			home.setWins(home.getWins()+1);
			away.setLosses(away.getLosses()+1);	
			hForm[5]='W';
			aForm[5]='L';
			
		}else if(awayScore > homeScore){
			home.setLosses(home.getLosses()+1);
			away.setWins(away.getWins()+1);	
			hForm[5]='L';
			aForm[5]='W';
			
		} else{
			home.setDraws(home.getDraws()+1);
			away.setDraws(away.getDraws()+1);
			hForm[5]=aForm[5]='D';
		}
		home.setForm(hForm);
		away.setForm(aForm);
		home.setGoalFor(home.getGoalFor() + homeScore);
		home.setGoalAgainst(home.getGoalAgainst() + awayScore);
		home.updateGoalDif();
		away.setGoalFor(away.getGoalFor() + awayScore);
		away.setGoalAgainst(away.getGoalAgainst() + homeScore);
		away.updateGoalDif();
	}
	
}
