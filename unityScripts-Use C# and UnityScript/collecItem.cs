using UnityEngine;
using System.Collections;

public class collecItem : MonoBehaviour {
	public int counter = 10;
	
	
	void Update(){
		guiText.text = "Score:" + counter;
	}
	void OnTriggerEnter (Collider other) {
		if(other.gameObject.name=="coin")
		{
		Destroy(other.gameObject);
		counter = counter -1;
			Debug.Log(counter);
		}
		else if(other.gameObject.name=="exit" && counter <=0)
		{
			Debug.Log("WELL DONE, YOU WON");
			Network.Disconnect(200);
		}
		
	}
	
	/*
	void EndGame(Collider col){
		if(counter<=0)
		{
			if(col.gameObject.name == "exit")
			{
				Debug.Log("Exit");
			}
			else{
				Debug.Log("Collect more ");
			}
		}
	}
	*/
	
}
