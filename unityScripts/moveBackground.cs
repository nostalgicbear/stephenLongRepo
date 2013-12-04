using UnityEngine;
using System.Collections;

public class moveBackground : MonoBehaviour {

	
	public float Speed = 1f;
	
	private float switchDirection = -1f;
	public int bgIndex = 1;
	public int holeChance = 1;
	private tk2dSprite spriteFrame;
	private changeBGFrame checkHoleSpawn;
	
	void Start() {
		spriteFrame = GetComponent<tk2dSprite>();	
		checkHoleSpawn = transform.parent.GetComponent<changeBGFrame>();
	}

	// Update is called once per frame
	void Update () {
		//If x position is less than -20 move the ground back to right side of screen
		if(transform.position.x <= -14.5f){
			ResetBG();
			ChangeBG();
		}
		else { 
			MoveBG();
		}
	}
	/// <summary>
	/// Moves the BG.
	/// </summary>
	void MoveBG() {
			transform.Translate(Vector3.right * switchDirection * Speed * Time.deltaTime);
	}
	
	/// <summary>
	/// Resets the BG.
	/// </summary>
	void ResetBG(){
			transform.position = new Vector3(16.8f,1f,1f);
	}
	/// <summary>
	/// Changes the BG frame.
	/// </summary>
	void ChangeBG() {
		holeChance = Random.Range(1,4);
		if(holeChance == 1 && !checkHoleSpawn.holeSpawn) {
			spriteFrame.SetSprite(9);
			Debug.Log("Hole Spawned");
			checkHoleSpawn.holeSpawn = true;
		}
		else if(checkHoleSpawn.obstacleSpawn) {
			spriteFrame.SetSprite(1);
			checkHoleSpawn.obstacleSpawn = false;
		}
		else {
			bgIndex = Random.Range(2,8);
			spriteFrame.SetSprite(bgIndex);
			checkHoleSpawn.holeSpawn = false;
			checkHoleSpawn.obstacleSpawn = true;
		}
	}

}