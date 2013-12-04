using UnityEngine;
using System.Collections;

public class TriggerZone : MonoBehaviour {
	
	public AudioClip lockedSound;
	public GUIText textHints;
	public Light doorLight;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	
	
	void OnTriggerEnter(Collider col){
		if(col.gameObject.tag=="Player"){
			if(Inventory.charge==4){
			transform.FindChild("door").SendMessage("DoorCheck");
				if(GameObject.Find("PowerGUI")){
					Destroy(GameObject.Find("PowerGUI"));
					doorLight.color = Color.green;
				}
				else if(Inventory.charge > 0 && Inventory.charge < 4){
			textHints.SendMessage("Show Hint", "This door wont budge... The door has no charge...");
			transform.FindChild("door").audio.PlayOneShot(lockedSound);
		}
		}else{
				transform.FindChild("door").audio.PlayOneShot(lockedSound);
				col.gameObject.SendMessage("HUDon");
				textHints.SendMessage("ShowHint", "The door seems to be locked. Maybe that generator needs power");
			}

		}
	}
}
