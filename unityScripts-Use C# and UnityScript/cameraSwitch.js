#pragma strict
private var cameraNum:int;
function Start ()
 {
	cameraNum=1;
	camera.rect=Rect(0,0,1,1);
}

function Update ()
 { 
    //
    
    //transform.LookAt(GameObject.Find("Ball").transform);
	GameObject.Find("active camera").guiText.text="Active camera"+cameraNum;

	//changes the camera when the c button is pressed
	if(Input.GetKeyUp(KeyCode.C))
	{
	cameraNum ++;
		if(cameraNum>3) cameraNum=1;
		var activeCamera:String="camera"+cameraNum;
	
		print(activeCamera);
		if(gameObject.name==activeCamera)
		{
			camera.rect=Rect(0, 0, 1, 1);
		}
		else
		{
		camera.rect=Rect(0, 0, 0, 0);
		
	}

} 

}

function changeCamera (newCamera:int)
{
cameraNum = newCamera;
var activeCamera:String="camera"+cameraNum;
		if(gameObject.name==activeCamera)
		{
			camera.rect=Rect(0, 0, 1, 1);
		}
		else
		{
		camera.rect=Rect(0, 0, 0, 0);
		}
}