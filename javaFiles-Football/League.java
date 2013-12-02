package implementation_package;

import java.util.ArrayList;
import java.util.HashMap;

import javax.swing.JOptionPane;
public class League {
	String name, description;
	HashMap<Integer, Team> teams = new HashMap<Integer, Team>();
	ArrayList<Fixture> fixtureList = new ArrayList<Fixture>();
	
	//Constructor
	public League(String name, String desc){
		this.name = name;
		this.description = desc;
	}
	
	
	public void addTeam(Team team){
		if(!teams.containsKey(team.getTeamId()))
			teams.put(team.getTeamId(),team);
		else	
			JOptionPane.showMessageDialog(null, "BOLD STEVEN YOU ADDED A DUPE TEAM ID");
		
	}
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}


	
	public HashMap<Integer, Team> getTeams() {
		System.out.print(teams);
		return teams;
	}
	public Team getTeam(int key){
		Team temp =teams.get(key);
		return temp;
	}


	public ArrayList<Fixture> getFixtureList() {
		return fixtureList;
	}

	
	
}
