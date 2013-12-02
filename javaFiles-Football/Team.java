package implementation_package;

import java.util.Arrays;

import abstract_package.Person;

public class Team {
	
	@Override
	public String toString() {
		return "Team [name=" + name + ", wins=" + wins + ", losses=" + losses
				+ ", draws=" + draws + ", teamId=" + teamId + ", goalDif="
				+ goalDif + ", keyPlayer=" + keyPlayer + ", manager=" + manager
				+ ", form=" + Arrays.toString(form) + "]";
	}

	private String name;
	private int wins, losses, draws, teamId, goalDif, goalFor,goalAgainst;
	private Person keyPlayer, manager;
	private char[] form = new char[6];
	
	//Constructor
	public Team(String name, int teamId, Person player, Person manager, int wins, int draws, int losses, int goalFor,int goalAgainst, char[] form){
		this.name = name;
		this.teamId = teamId;
		this.keyPlayer = player;
		this.manager = manager;
		this.wins = wins;
		this.draws = draws;
		this.losses = losses;
		this.goalFor =goalFor;
		this.goalAgainst=goalAgainst;
		this.goalDif = goalFor-goalAgainst;
		this.form = form;
		
	}
	
	public int getGoalFor() {
		return goalFor;
	}

	public void setGoalFor(int goalFor) {
		this.goalFor = goalFor;
	}

	public int getGoalAgainst() {
		return goalAgainst;
	}

	public void setGoalAgainst(int goalAgainst) {
		this.goalAgainst = goalAgainst;
	}

	//Returns how many games the team has played
	public int gamesPlayed(){
		int gamesPlayed = wins + losses + draws;
		return gamesPlayed;
	}
	
	//Returns the teams total points
	public int getPoints(){
		int points = (wins*3) + draws;
		return points;
	}
	
	public void updateGoalDif(){
		this.goalDif = goalFor-goalAgainst;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getWins() {
		return wins;
	}

	public void setWins(int wins) {
		this.wins = wins;
	}

	public int getLosses() {
		return losses;
	}

	public void setLosses(int losses) {
		this.losses = losses;
	}

	public int getDraws() {
		return draws;
	}

	public void setDraws(int draws) {
		this.draws = draws;
	}

	public int getTeamId() {
		return teamId;
	}

	public void setTeamId(int teamId) {
		this.teamId = teamId;
	}

	public int getGoalDif() {
		return goalDif;
	}

	public Person getKeyPlayer() {
		return keyPlayer;
	}

	public void setKeyPlayer(Person keyPlayer) {
		this.keyPlayer = keyPlayer;
	}

	public Person getManager() {
		return manager;
	}

	public void setManager(Person manager) {
		this.manager = manager;
	}

	public char[] getForm() {
		return form;
	}

	public void setForm(char[] form) {
		this.form = form;
	}
	
	
	
	
}
