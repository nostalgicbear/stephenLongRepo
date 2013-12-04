using UnityEngine;
using System.Collections;

public class MoveablePlatform : MonoBehaviour 
{

	public Transform origin;
	public Transform destination;
	public float slideSpeed = 0.03f;
	public bool switching;
	
	public bool touchingPlatform;
	
	void FixedUpdate()
	{
		if (transform.position == destination.position)	
		{
			switching = true;
		}
		else if (transform.position == origin.position)
		{
			switching = false;
		}
		
		if (switching)
		{
			transform.position = Vector3.MoveTowards(transform.position, origin.position, slideSpeed);
		}
		else
		{
			transform.position = Vector3.MoveTowards(transform.position, destination.position, slideSpeed);
		}
	}
}
