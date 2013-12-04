var listenPort = 25000;
var maxClients = 3;

function OnPlayerDisconnected(player : NetworkPlayer) {
	//Network.RemoveRPCs(player); //may need to delete htis
    spm.deletePlayer(player);
}
 
function startServer() {
    Network.InitializeServer(maxClients, listenPort, false);    
}
 
function stopServer() {
    Network.Disconnect();
}

function OnApplicationQuit(){
	if(Network.isServer)
	{
		Network.Disconnect(100);
	}
}

function OnGUI ()
{
    if (Network.peerType == NetworkPeerType.Disconnected) {
        GUILayout.Label("Network server is not running.");
        if (GUILayout.Button ("Start Server"))
        {               
            startServer();  
        }
    }
    else {
        if (Network.peerType == NetworkPeerType.Connecting)
            GUILayout.Label("Network server is starting up...");
        else { 
            GUILayout.Label("Network server is running.");          
            showServerInformation();    
            showClientInformation();
        }
        if (GUILayout.Button ("Stop Server"))
        {               
            stopServer();   
        }
    }
}
 
function showClientInformation() {
    GUILayout.Label("Clients: " + Network.connections.Length + "/" + maxClients);
        for(var p: NetworkPlayer in Network.connections) {
        GUILayout.Label(" Player from ip/port: " + p.ipAddress + "/" + p.port); 
    }
}
 
function showServerInformation() {
    GUILayout.Label("IP: " + Network.player.ipAddress + " Port: " + Network.player.port);  
}

@script RequireComponent(ServerPlayerManager)
private var spm : ServerPlayerManager;
function Awake() {
    spm = gameObject.GetComponent(ServerPlayerManager);
}
 
function OnPlayerConnected(player: NetworkPlayer) { 
    spm.spawnPlayer(player);
}