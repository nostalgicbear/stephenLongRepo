using UnityEngine;
using System.Collections;

public class Shooter : MonoBehaviour {
		public float moveSpeed = 2f;
	
	
	void Update () {
		float h = Input.GetAxis("Horizontal") * Time.deltaTime * moveSpeed;
		float v = Input.GetAxis("Vertical") * Time.deltaTime * moveSpeed;
		transform.Translate(h, v, 0);

}
	}

