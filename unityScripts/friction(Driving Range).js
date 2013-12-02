#pragma strict

var collideGround:boolean=false;
var frictionForce : Vector3;

function Start () {

}
function Update () 
{
	// sets friction when the ball collides with the ground
	if(collideGround==true)
	{
		frictionForce = gameObject.rigidbody.velocity*-5;
        gameObject.rigidbody.AddForce(frictionForce);
	}
}
// detects whether ball is colliding with the ground
function OnCollisionEnter(other : Collision) 
{ 
    if (other.gameObject.tag == "Ground") 
    {
  		collideGround=true; 
  	}
  	else
  	{
  	collideGround=false;
  	}
  	if (other.gameObject.tag == "Target")
	{
	GameObject.Find("launcher").GetComponent(LauncherDrivingRange).increaseScore();
	}
	
}