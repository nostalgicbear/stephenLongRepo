#pragma strict
var players = new Hashtable();
var spawnObject: Transform;

function spawnPlayer(player : NetworkPlayer) {
    var ply : PlayerInfo = GameObject.FindObjectOfType(PlayerInfo);
    var go : GameObject = Network.Instantiate(ply.playerPrefab, spawnObject.position, Quaternion.identity, 0);
    players[player] = go;
}

function deletePlayer(player : NetworkPlayer) {
    var go : GameObject = players[player];
    Network.RemoveRPCs(go.networkView.viewID); 
    Network.Destroy(go); 
    players.Remove(player); 
}

@RPC
function handlePlayerInput(player: NetworkPlayer, vertical: float, horizontal: float) {
    var go : GameObject = players[player];
    go.transform.position = go.transform.position + Vector3.right*horizontal;

	go.transform.position = go.transform.position + Vector3.forward*vertical;
	if(Input.GetKey(KeyCode.B))
	{
		go.transform.Rotate(Vector3.up * 3);
	}
	
	
}